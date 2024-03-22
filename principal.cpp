#include "principal.h"
#include "ui_principal.h"
#include "usuario.h"
#include "qmessagebox.h"
#include "QDateTime"
#include <QFile>
#include <QDataStream>
#include <QStringListModel>
#include "mainwindow.h"


Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
   connect(ui->btn_Hablar, &QPushButton::clicked, this, &Principal::openMainWindow);
}

Principal::~Principal()
{
    delete ui;
}

void Principal::on_btnLogIn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void Principal::on_btnSigIn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Principal::on_btn_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Principal::on_btn_AceptarI_clicked()
{
    QStringList stringList;
    QStringList stringList2;
    Users obj;
    QString name = ui->LE_UserI->text().simplified();
    QString contrase = ui->LE_PassI->text().simplified();

    if (!obj.login(name, contrase)) {
        QMessageBox::warning(nullptr, "ERROR", "Could Not Find");
    } else {
        ui->stackedWidget->setCurrentIndex(3);
        //name2 = name;
        ui->label_10->setText(name);

        QVector<QString> amigos = obj.readFriends(name);

        for (const QString& amigo : amigos) {
            stringList2 << amigo;
        }

        QFile file("usuariosfile.us");
        QDataStream in(&file);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(nullptr, "ERROR", "Archivo no encontrado");
        }

        Usuario usuarioRegistrado;
        file.seek(0);

        while (!in.atEnd()) {
            in >> usuarioRegistrado.nombre >> usuarioRegistrado.usuario >> usuarioRegistrado.cont >> usuarioRegistrado.fecha >> usuarioRegistrado.friends;
            if (usuarioRegistrado.usuario != name) {
                stringList << usuarioRegistrado.usuario;
            }
        }
        file.close();

//        model.setStringList(stringList);
//        ui->listView1->setModel(&model);

//        model2.setStringList(stringList2);
//        ui->listaView2->setModel(&model2);
}}


void Principal::on_btn_Registrarme_clicked()
{
   Users obj;
    Usuario us;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    us.nombre = ui->LE_NombreR->text().simplified();
    us.usuario = ui->LE_UserR->text().simplified();
    us.cont = ui->LE_PassR->text().simplified();
  //  us.fecha = formattedDateTime;

    if(!obj.crearUsuario(us)){
        QMessageBox::warning(nullptr, "ERROR", "Ese usuario ya esta tomado");
    }else{
        QMessageBox::information(nullptr, "info", "¡Registro Exitoso!");
    }

}

void Principal::openMainWindow()
{
    // Crea una instancia de la segunda ventana
    MainWindow *mainWindow = new MainWindow(this);
    // Muestra la segunda ventana
    mainWindow->show();
}



