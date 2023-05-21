#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
class QHostAddress;

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);
    //QString userName() const;
    //bool loggedIn() const;
public slots:
    void connectToServer(const QHostAddress &address, qintptr port);
    void login(const QString &userName);
    void disconnectFromHost();

signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void error(QAbstractSocket::SocketError socekError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
private:
    QTcpSocket *m_clientSocket;
    //QString m_userName;
    bool m_loggedIn;
};

#endif // CHATCLIENT_H
