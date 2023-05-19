#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

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

private slots:
    void toggleStartServer();
    void logMessage(const QString &msg);
};
#endif // SERVERWINDOW_H
