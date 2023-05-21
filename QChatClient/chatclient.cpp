#include "chatclient.h"

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
    qDebug() << userName;
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
