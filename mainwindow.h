#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArray>
#include <QMainWindow>
#include "ClientManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionconectar_triggered();
    void dataReceived(QByteArray data );

    void on_btnEnviar_clicked();

private:
    Ui::MainWindow *ui;
   ClientManager *_client;
};
#endif // MAINWINDOW_H
