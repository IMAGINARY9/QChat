#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include <QStringListModel>

class ChatClient;
class QStandardItemModel;

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
    QStringListModel *m_usersModel;
    //QString m_lastUserName;

private slots:
    void changeConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void openChat(const QModelIndex &index);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void updateUsersModel(const QStringList &userNames);
    //void userJoined(const QString &username);
    //void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
};
#endif // CLIENTWINDOW_H
