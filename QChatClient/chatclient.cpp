#include "chatclient.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringLiteral>

ChatClient::ChatClient(QObject *parent)
    : QObject{parent}
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);

    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);

    connect(m_clientSocket, &QAbstractSocket::errorOccurred, this, &ChatClient::error);

    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});

    m_users = new QStringList();
}

ChatClient::~ChatClient()
{
    delete m_users;
}

QString ChatClient::userName() const
{
    return m_userName;
}

QString ChatClient::recipientName() const
{
    return m_recipientName;
}


void ChatClient::connectToServer(const QHostAddress &address, qintptr port)
{
    m_clientSocket->connectToHost(address, port);
}

void ChatClient::login(const QString &userName)
{
    m_userName = userName;
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        QDataStream clientStream(m_clientSocket);

        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("login");
        message[QStringLiteral("username")] = userName;

        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}

bool ChatClient::selectChat(const QString &chatName)
{
    if (chatName.isEmpty() || !m_users->contains(chatName))
        return false;

    m_recipientName = chatName;
    return true;
}

bool ChatClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return false;

    QDataStream clientStream(m_clientSocket);

    QJsonObject message;
    message[QStringLiteral("sender")] = m_userName;
    message[QStringLiteral("recipient")] = m_recipientName;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = text;

    clientStream << QJsonDocument(message).toJson();
    return true;
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
    m_users->clear();
    emit updateUsersList(*m_users);
}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;

    QDataStream socketStream(m_clientSocket);

    for (;;) {
        socketStream.startTransaction();

        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {

            QJsonParseError parseError;

            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError)
                if(jsonDoc.isObject())
                    jsonReceived(jsonDoc.object());
        } else
            break;
    }
}

void ChatClient::usersInit(const QJsonArray &usersArray)
{
    for (const QJsonValueConstRef &userName : usersArray) {
        QString name = userName.toString();
        if (name == m_userName)
            continue;
        m_users->push_back(name);
    }
    emit updateUsersList(*m_users);
}


void ChatClient::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;

    // login
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0)
    {
        if (m_loggedIn) return;

        const QJsonValue resVal = docObj.value(QLatin1String("success"));
        if (resVal.isNull() || !resVal.isBool())
            return;
        const bool loginSuccess = resVal.toBool();
        if (loginSuccess)
        {
            const QJsonValue arrayVal = docObj.value(QLatin1String("users"));
            if (arrayVal.isNull() || !arrayVal.isArray())
                return;
            usersInit(arrayVal.toArray());

            m_loggedIn = true;
            emit loggedIn();
            return;
        }

        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        m_loggedIn = false;
        emit loginError(reasonVal.toString());

    // userJoined
    } else if (typeVal.toString().compare(QLatin1String("new user"), Qt::CaseInsensitive) == 0) {
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;
        m_users->push_back(usernameVal.toString());
        emit updateUsersList(*m_users);

    // userLeft
    } else if (typeVal.toString().compare(QLatin1String("user disconnected"), Qt::CaseInsensitive) == 0) {
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;
        m_users->removeAll(usernameVal.toString());
        emit updateUsersList(*m_users);

    // message
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return;
        if (senderVal.isNull() || !senderVal.isString())
            return;
        emit messageReceived(senderVal.toString(), textVal.toString());
    }

}
