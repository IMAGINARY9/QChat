#include "serverworker.h"

#include <QJsonDocument>
#include <QJsonObject>

ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
    , m_serverSocket(new QTcpSocket(this))
{
    connect(m_serverSocket, &QTcpSocket::readyRead, this, &ServerWorker::receiveJson);
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    connect(m_serverSocket, &QTcpSocket::errorOccurred, this, &ServerWorker::error);
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

QString ServerWorker::userName() const
{
    m_userNameLock.lockForRead();
    const QString result = m_userName;
    m_userNameLock.unlock();
    return result;
}

void ServerWorker::setUserName(const QString &userName)
{
    m_userNameLock.lockForWrite();
    m_userName = userName;
    m_userNameLock.unlock();
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    const QByteArray jsonData = QJsonDocument(json).toJson();
    emit logMessage(QLatin1String("Sending to ") + userName()
                    + QLatin1String(" - ") + QString::fromUtf8(jsonData));
    QDataStream socketStream(m_serverSocket);
    socketStream << jsonData;
}

void ServerWorker::disconnectFromClient()
{
    m_serverSocket->disconnectFromHost();
}

void ServerWorker::receiveJson()
{
    QByteArray jsonData;
    QDataStream socketStream(m_serverSocket);
    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    emit jsonReceived(jsonDoc.object());
                else
                    emit logMessage(QLatin1String("Invalid message: ")
                                    + QString::fromUtf8(jsonData));
            } else {
                    emit logMessage(QLatin1String("Invalid message: ")
                                + QString::fromUtf8(jsonData));
            }
        } else {
            break;
        }
    }
}
