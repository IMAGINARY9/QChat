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
    ~ChatClient();
    QString userName() const;
    QString recipientName() const;
    QStringList users() const;

public slots:
    void connectToServer(const QHostAddress &address, qintptr port);
    void login(const QString &userName);
    bool selectChat(const QString &chatName);
    bool sendMessage(const QString &text);
    void disconnectFromHost();

private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socekError);
    void updateUsersList(const QStringList &userNames);
private:
    QTcpSocket *m_clientSocket;
    QString m_userName;
    QString m_recipientName;
    QStringList *m_users;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
    void usersInit(const QJsonArray &usersArray);
};

#endif // CHATCLIENT_H
