#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H
#include <QDir>
#include <QTcpSocket>
#include <QWidget>

namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client, QWidget *parent = nullptr);
    ~ClientChatWidget();

private slots:
    void dataReceived();
    void on_btnEnviar_clicked();
    void clientDisconnected();

private:
    Ui::ClientChatWidget *ui;
    QTcpSocket *_client;
      QDir dir;
};

#endif // CLIENTCHATWIDGET_H
