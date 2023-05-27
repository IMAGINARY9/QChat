#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWindow; }
QT_END_NAMESPACE

class ChatServer;
class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
    ChatServer *m_chatServer;
    QStringListModel *m_clientsModel;

private slots:
    void toggleStartServer();
    void logMessage(const QString &msg);

    void updateClientsModel(const QStringList &clients);
};
#endif // SERVERWINDOW_H
