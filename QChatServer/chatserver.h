#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QVector>
class QThread;
class ServerWorker;
class QJsonObject;
class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    ChatServer(QObject *parent = nullptr);
    ~ChatServer();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    const int m_idealThreadCount;
    QVector<QThread *> m_availableThreads;
    QVector<int> m_threadsLoad;
    QVector<ServerWorker *> m_clients;

private slots:
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    void broadcast(const QJsonObject &message, const QString &recipientName);
    void jsonReceived(ServerWorker *sender, const QJsonObject &json);
    void userDisconnected(ServerWorker *sender, int threadIdx);
    void userError(ServerWorker *sender);
public slots:
    void stopServer();
private:
    QStringList updateUsers();
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj);
    void sendJson(ServerWorker *destination, const QJsonObject &message);
signals:
    void updateUsersList(const QStringList &users);
    void logMessage(const QString &msg);
    void stopAllClients();
};

#endif // CHATSERVER_H
