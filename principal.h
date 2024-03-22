#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_btnLogIn_clicked();

    void on_btnSigIn_clicked();

    void on_btn_Back_clicked();

    void on_btn_AceptarI_clicked();

    void on_btn_Registrarme_clicked();

    void on_listView1_clicked(const QModelIndex &index);

    void on_btn_Hablar_clicked();

    void openMainWindow();

private:
    Ui::Principal *ui;
    void setupClient();
    QString name;
    QString name2;
private:
    void seupServer();
};

#endif // PRINCIPAL_H
