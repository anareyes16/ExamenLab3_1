#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ChatItemWidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionconectar_triggered()
{
    _client = new ClientManager();
    connect(_client, &ClientManager::connected,[this]()
    {
        ui->centralwidget->setEnabled(true);
    });
    connect(_client, &ClientManager::disconnected,[this](){
        ui->centralwidget->setEnabled(false);
    });
    connect(_client, &ClientManager::dataReceived, this, &MainWindow::dataReceived) ;


    _client->connecToServer();
}

void MainWindow::dataReceived(QByteArray data)
{
    //ui->listMessages->addItem(data);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(data);
    auto listItemWidget = new QListWidgetItem();
listItemWidget->setSizeHint(QSize(0,65));
ui->listMessages->addItem(listItemWidget);
listItemWidget->setBackground(QColor(167, 255, 237));
ui->listMessages->setItemWidget(listItemWidget, chatWidget);
}


void MainWindow::on_btnEnviar_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message);
    ui->listMessages->addItem(message);
    ui->lnMessage->setText("");
   // ui->listMessages->addItem(message);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message, true); //true porque es "mi mensaje"
    auto listItemWidget = new QListWidgetItem();
listItemWidget->setSizeHint(QSize(0,65));
ui->listMessages->addItem(listItemWidget);

ui->listMessages->setItemWidget(listItemWidget, chatWidget);
}

