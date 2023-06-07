#include "chatclient.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringLiteral>

ChatClient::ChatClient(QObject *parent)
    : QObject{parent}
    , m_clientSocket(new QTcpSocket(this))
    , m_users(new QList<std::pair<QString, int>>())
    , m_loggedIn(false)
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);

    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);

    connect(m_clientSocket, &QAbstractSocket::errorOccurred, this, &ChatClient::error);

    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});

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

QString ChatClient::chatSelected(const QString &chatName)
{
    QString name = "";
    for (const std::pair<QString, int> &user : *m_users) {
        if (chatName == user.first
            || (user.second != 0 && user.first == chatName.left(chatName.indexOf(QString::number(user.second)) - 2)))
            name = user.first;
    }

    if (!name.isEmpty())
        m_recipientName = name;

    return name;
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

void ChatClient::unreadMessages(const QString &sender, bool isClear)
{
    for (std::pair<QString, int> &user : *m_users) {
        if (user.first == sender)
        {
            if (isClear) user.second = 0;
            else user.second++;
            break;
        }
    }
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
        std::pair<QString, int> user = std::make_pair(name, 0);
        m_users->push_back(user);
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

        std::pair<QString, int> user = std::make_pair(usernameVal.toString(), 0);
        m_users->push_back(user);

        emit updateUsersList(*m_users);

    // userLeft
    } else if (typeVal.toString().compare(QLatin1String("user disconnected"), Qt::CaseInsensitive) == 0) {
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;

        for (const std::pair<QString, int> &pair : *m_users) {
            if (pair.first == usernameVal.toString()) {
                m_users->removeAll(pair);
                break;
            }
        }

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
