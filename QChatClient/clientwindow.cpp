#include "chatclient.h"
#include "clientwindow.h"
#include "qmessagebox.h"
#include "ui_clientwindow.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QStringLiteral>
#include <QMap>

ClientWindow::ClientWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWindow)
    , m_chatClient(new ChatClient(this))
    , m_chatModels(new QMap<QString, QStandardItemModel *>())
    , m_usersModel(new QStringListModel(this))
{
    ui->setupUi(this);

    ui->usersView->setModel(m_usersModel);

    connect(m_chatClient, &ChatClient::connected, this, &ClientWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::loggedIn, this, &ClientWindow::loggedIn);
    connect(m_chatClient, &ChatClient::loginError, this, &ClientWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &ClientWindow::messageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &ClientWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &ClientWindow::error);

    connect(m_chatClient, &ChatClient::updateUsersList, this, &ClientWindow::updateUsersModel);

    connect(ui->connectionBox, &QCheckBox::toggled, this, &ClientWindow::changeConnection);

    connect(ui->sendButton, &QPushButton::clicked, this, &ClientWindow::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &ClientWindow::sendMessage);

    connect(ui->usersView, &QListView::clicked, this, &ClientWindow::openChat);
}

ClientWindow::~ClientWindow()
{
    for (QStandardItemModel *model : m_chatModels->values())
        delete model;
    delete m_chatModels;
    delete ui;
}

void ClientWindow::changeConnection()
{
    if(!ui->connectionBox->isChecked())
    {
        m_chatClient->disconnectFromHost();
        return;
    }

    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Connect to Sevrer")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty()) {
        ui->connectionBox->setCheckState(Qt::Unchecked);
        return;
    }
    bool ok;
    const int hostPort = QInputDialog::getInt(
        this
        , tr("Connect to Sevrer")
        , tr("Server Port")
        , 9000
        , 0 , 2147483647, 1
        , &ok
        );
    if (!ok) {
        ui->connectionBox->setCheckState(Qt::Unchecked);
        return;
    }
    ui->connectionBox->setEnabled(false);

    m_chatClient->connectToServer(QHostAddress(hostAddress), hostPort);
}

void ClientWindow::connectedToServer()
{
    const QString newUsername = QInputDialog::getText(
        this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty())
        return m_chatClient->disconnectFromHost();

    attemptLogin(newUsername);

}

void ClientWindow::attemptLogin(const QString &userName)
{
    m_chatClient->login(userName);
    ui->nameLabel->setText(userName);
}

void ClientWindow::openChat(const QModelIndex &index)
{
    QString chatName = m_usersModel->data(index).toString();

    QString userName = m_chatClient->chatSelected(chatName);
    if (!userName.isEmpty())
    {
        m_chatClient->unreadMessages(userName, true);
        ui->recepientLabel->setText(userName);
        if (!m_chatModels->keys().contains(userName)) {
            QStandardItemModel *newChatModel = new QStandardItemModel();
            m_chatModels->insert(userName, newChatModel);
            newChatModel->insertColumn(0);
        }

        QStandardItemModel * chatModel = m_chatModels->value(userName);
        ui->chatView->setModel(chatModel);
        ui->messageEdit->setEnabled(true);
        ui->sendButton->setEnabled(true);
        ui->chatView->setEnabled(true);
        return;
    }
    QMessageBox::critical(this, tr("Error"), "Can't find user with name " + chatName);
}

void ClientWindow::loggedIn()
{
    ui->connectionBox->setCheckState(Qt::Checked);
    ui->connectionBox->setEnabled(true);
}

void ClientWindow::loginFailed(const QString &reason)
{
    QMessageBox::critical(this, tr("Error"), reason);
    connectedToServer();
}

void ClientWindow::messageReceived(const QString &sender, const QString &text)
{
        if (ui->recepientLabel->text() != sender)
        m_chatClient->unreadMessages(sender, false);

        QFont boldFont;
        boldFont.setBold(true);

        if (!m_chatModels->keys().contains(sender)) {
            QStandardItemModel *newChatModel = new QStandardItemModel();
            m_chatModels->insert(sender, newChatModel);
            newChatModel->insertColumn(0);
        }

        QStandardItemModel *chatModel = m_chatModels->value(sender);

        int newRow = chatModel->rowCount();
        chatModel->insertRows(newRow, 2);
        QModelIndex index = chatModel->index(newRow, 0);
        chatModel->setData(index, sender + QLatin1Char(':'));
        chatModel->setData(index, int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        chatModel->setData(index, boldFont, Qt::FontRole);
        ++newRow;

        index = chatModel->index(newRow, 0);
        chatModel->setData(index, text);
        chatModel->setData(index, int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        ui->chatView->scrollToBottom();
}

void ClientWindow::sendMessage()
{
    QString text = ui->messageEdit->text();
    if (m_chatClient->sendMessage(text))
    {
        QStandardItemModel *chatModel = m_chatModels->value(ui->recepientLabel->text());

        const int newRow = chatModel->rowCount();
        chatModel->insertRow(newRow);
        QModelIndex index =  chatModel->index(newRow, 0);
        chatModel->setData(index, text);
        chatModel->setData(index, int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);

        ui->messageEdit->clear();
        ui->chatView->scrollToBottom();
    }
}

void ClientWindow::disconnectedFromServer()
{
    QMessageBox::warning(this, tr("Disconnected"), tr("You have disconnected from the server"));
    ui->connectionBox->setCheckState(Qt::Unchecked);
    ui->connectionBox->setEnabled(true);
    ui->messageEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->recepientLabel->setText("Friend's name");
    for (QStandardItemModel *model : m_chatModels->values())
        delete model;
    m_chatModels->clear();
    ui->chatView->setEnabled(false);

}

void ClientWindow::updateUsersModel(const QList<std::pair<QString, int>> &userNames)
{
    QStringList list;
    for (const std::pair<QString, int> &pair : userNames) {
        QString str = pair.first;
        if (pair.second != 0)
            str.append(" (" + QString::number(pair.second) + ") ");

        list.push_back(str);
    }
    m_usersModel->setStringList(list);
}

void ClientWindow::error(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
    disconnectedFromServer();
}

