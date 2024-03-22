#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class ChatItemWidget;
}

class ChatItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatItemWidget(QWidget *parent = nullptr,QString nombre="");
    ~ChatItemWidget();
    void setMessage(QString message, bool isMyMessage = false);

private:
    Ui::ChatItemWidget *ui;
    QString nombre;

};

#endif // CHATITEMWIDGET_H
