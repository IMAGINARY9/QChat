#include "chatserver.h"
#include "serverwindow.h"
#include "ui_serverwindow.h"
#include <QMessageBox>

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
    , m_chatServer(new ChatServer(this))
{
    ui->setupUi(this);
    connect(ui->startStopButton, &QPushButton::clicked, this, &ServerWindow::toggleStartServer);
    connect(m_chatServer, &ChatServer::logMessage, this, &ServerWindow::logMessage);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::toggleStartServer()
{
    int port = ui->portEdit->toPlainText().toInt();
    if(port == 0)
    {
        logMessage(QStringLiteral("Port is unvalible"));
        return;
    }
    if(m_chatServer->isListening()){
        m_chatServer->stopServer();
        ui->startStopButton->setText(tr("Start Server"));
        ui->portEdit->setReadOnly(false);
        logMessage(QStringLiteral("Server Stopped"));
    } else {

        if(!m_chatServer->listen(QHostAddress::Any, port)){
            QMessageBox::critical(this, tr("Error"), tr("Unable to start the server"));
            return;
        }
        logMessage(QStringLiteral("Server Started"));
        ui->startStopButton->setText(tr("Stop Server"));
    }
}

void ServerWindow::logMessage(const QString &msg)
{
    ui->logEditor->appendPlainText(msg + QLatin1Char('\n'));
}
