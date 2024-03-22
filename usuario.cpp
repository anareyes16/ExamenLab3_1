#include "usuario.h"
#include <QFile>
#include <QDataStream>
#include <QDir>


bool Users::crearUsuario(const Usuario &nuevoUsuario)
{
    QFile file("usuariosfile.us");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
    {
        return false;
    }

    QDataStream in(&file);
    file.seek(0);
    Usuario usuarioExistente;
    while (!in.atEnd())
    {
        if (!readUser(usuarioExistente, in))
        {
            return false;
        }
        if (usuarioExistente.usuario == nuevoUsuario.usuario) {
            file.close();
            return false;
        }
    }

    QDataStream out(&file);
    if (!writeUser(nuevoUsuario, out))
    {
        return false;
    }

    file.close();
    return true;
}

bool Users::login(const QString &usuario, const QString &cont)
{
    QFile file("usuariosfile.us");
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QDataStream in(&file);
    Usuario usuarioRegistrado;
    file.seek(0);
    while (!in.atEnd()) {
        if (!readUser(usuarioRegistrado, in))
        {
            return false;
        }
        if (usuarioRegistrado.usuario == usuario && usuarioRegistrado.cont == cont)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool Users::savefriends(QString name, QString namefriend)
{
    QString filename = "friends_" + name + ".fnd";
    QFile file(filename);
    if (file.open(QIODevice::Append)) {
        QDataStream out(&file);
        out << namefriend;
        file.close();
        return true;
    }
    return false;
}

QVector<QString> Users::readFriends(QString name)
{
    QVector<QString> friends;
    QString filename = "friends_" + name + ".fnd";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString friendName;
            in >> friendName;
            friends.append(friendName);
        }
        file.close();
    }
    return friends;
}

bool Users::saveMessage(const QString &sender, const QString &receiver, const QString &message, bool mio)
{
    if (!QDir().exists("mensajes"))
    {
        QDir().mkdir("mensajes");
    }
    QString filename = "messages_" + sender + "_" + receiver + ".msms";
    QFile file("mensajes/" + filename);
    if (file.open(QIODevice::Append))
    {
        QDataStream out(&file);
        if (mio){
        out << sender << message;
        }else{
        out << receiver << message;
        }
        file.close();
        return true;
    }
    return false;
}


QVector<QString> Users::readMessages(const QString &sender, const QString &receiver)
{
    QVector<QString> messages;
    QString filename = "mensajes/messages_" + sender + "_" + receiver + ".msms";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString senderName;
            QString message;
            in >> senderName >> message;
            messages.append(message);
        }
        file.close();
    }
    return messages;
}

QVector<QString> Users::senders(const QString &sender, const QString &receiver)
{
    QVector<QString> senderVect;
    QString filename = "mensajes/messages_" + sender + "_" + receiver + ".msms";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString senderName;
            QString message;
            in >> senderName >> message;
            senderVect.append(senderName);
        }
        file.close();
    }
    return senderVect;

}

bool Users::writeUser(const Usuario &user, QDataStream &out)
{
    out << user.nombre << user.usuario << user.cont << user.fecha;
    return true;
}

bool Users::readUser(Usuario &user, QDataStream &in)
{
    in >> user.nombre >> user.usuario >> user.cont >> user.fecha;
    return true;
}
