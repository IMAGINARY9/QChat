#include "chatserver.h"
#include "serverwindow.h"
#include "ui_serverwindow.h"
#include <QMessageBox>

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
    , m_chatServer(new ChatServer(this))
    , m_clientsModel(new QStringListModel(this))
{
    ui->setupUi(this);
    ui->sessionsView->setModel(m_clientsModel);

    connect(m_chatServer, &ChatServer::updateUsersList, this, &ServerWindow::updateClientsModel);

    connect(ui->startStopButton, &QPushButton::clicked, this, &ServerWindow::toggleStartServer);
    connect(m_chatServer, &ChatServer::logMessage, this, &ServerWindow::logMessage);

}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::toggleStartServer()
{
    int port = ui->portEdit->text().toInt();
    if(port == 0)
    {
        logMessage(QStringLiteral("Port is unvalible"));
        return;
    }
    if(m_chatServer->isListening()){
        m_chatServer->stopServer();
        ui->startStopButton->setText(tr("Start Server"));
        ui->portEdit->setEnabled(true);
        logMessage(QStringLiteral("Server Stopped"));
    } else {
        if(!m_chatServer->listen(QHostAddress::Any, port)){
            QMessageBox::critical(this, tr("Error"), tr("Unable to start the server"));
            return;
        }
        logMessage(QStringLiteral("Server Started"));
        ui->portEdit->setEnabled(false);
        ui->startStopButton->setText(tr("Stop Server"));
    }
}

void ServerWindow::logMessage(const QString &msg)
{
    ui->logEditor->appendPlainText(msg + QLatin1Char('\n'));
}

void ServerWindow::updateClientsModel(const QStringList &clients)
{
    m_clientsModel->setStringList(clients);
}

