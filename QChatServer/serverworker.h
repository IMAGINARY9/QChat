#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QReadWriteLock>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName() const;
    void setUserName(const QString &userName);
public slots:
    void disconnectFromClient();

signals:
    void disconnectedFromClient();
    void error();
private:
    QTcpSocket *m_serverSocket;
    QString m_userName;
    mutable QReadWriteLock m_userNameLock;
};

#endif // SERVERWORKER_H
