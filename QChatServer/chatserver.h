#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QVector>
class QThread;
class ServerWorker;

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
    void userDisconnected(ServerWorker *sender, int threadIdx);
    void userError(ServerWorker *sender);
public slots:
    void stopServer();
signals:
    void logMessage(const QString &msg);
    void stopAllClients();
};

#endif // CHATSERVER_H
