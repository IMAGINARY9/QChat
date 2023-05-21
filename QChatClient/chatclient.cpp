#include "chatclient.h"

#include <QJsonDocument>
#include <QJsonObject>

ChatClient::ChatClient(QObject *parent)
    : QObject{parent}
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);

    connect(m_clientSocket, &QAbstractSocket::errorOccurred, this, &ChatClient::error);

    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});

}

void ChatClient::connectToServer(const QHostAddress &address, qintptr port)
{
    m_clientSocket->connectToHost(address, port);
}

void ChatClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        QDataStream clientStream(m_clientSocket);

        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("username")] = userName;

        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
