#ifndef USUARIO_H
#define USUARIO_H

#include <QStringListModel>
#include <QString>
#include <QVector>

struct Usuario {
    QString nombre;
    QString usuario;
    QString cont; //contrseña, no puedo poner la ñ
    QString fecha;
    QVector<QString> friends;
};

class Users {
public:
     bool crearUsuario(const Usuario& nuevoUsuario);
     bool login(const QString& usuario, const QString& cont);
     bool savefriends(QString name, QString namefriend);
     QVector<QString> readFriends(QString name);
    bool saveMessage(const QString& sender, const QString& receiver, const QString& message,bool mio);
     QVector<QString> readMessages(const QString& sender, const QString& receiver);
      QVector<QString> senders(const QString& sender, const QString& receiver);
private:
     bool writeUser(const Usuario& user, QDataStream& out);
     bool readUser(Usuario& user, QDataStream& in);
};


#endif // USUARIO_H
