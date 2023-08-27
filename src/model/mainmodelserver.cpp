#include "mainmodelserver.h"
#include <QtQuick>
#include <QDebug>
#include <QUrl>
modelServer::modelServer(QString name, QString server, QString username, QString password, QString connect, QString login)
{
    m_name = name;
    m_server = server;
    m_username = username;
    m_password = password;
    m_connect = connect;
    m_login = login;
}

QString modelServer::name() const
{
    return m_name;
}

QString modelServer::server() const
{
    return m_server;
}

QString modelServer::username() const
{
    return m_username;
}

QString modelServer::password() const
{
    return m_password;
}

QString modelServer::connect() const
{
    return m_connect;
}

QString modelServer::login() const
{
    return m_login;
}

QString modelServer::address() const
{
    qDebug() << "Address: " << QString::number(reinterpret_cast<quintptr>(this), 16);
    return QString::number(reinterpret_cast<quintptr>(this), 16);
}


MainModelServer::MainModelServer(QObject *parent)
{


    Q_UNUSED(parent)
}

int MainModelServer::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listMainModels.count();
}

QVariant MainModelServer::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_listMainModels.count())
        return QVariant();

    const modelServer* item = m_listMainModels[index.row()];
    if (role == NameRole)
        return item->name();
    else if (role == ServerRole)
        return item->server();
    else if (role == UsernameRole)
        return item->username();
    else if (role == PasswordRole)
        return item->password();
    else if (role == ConnectRole)
        return item->connect();
    else if (role == LoginRole)
        return item->login();
    else if (role == AddressRole)
        return item->address();
    return QVariant();
}

void MainModelServer::moveItem(int from, int to)
{
    if(from < m_listMainModels.count() && to <m_listMainModels.count() && from != to)
    {
        m_listMainModels.move(from, to);
    }
}

QList<modelServer*> MainModelServer::listMainModels() const
{
    return m_listMainModels;
}

//void MainModelServer::receMsg(const QString &msg)
//{
//      qDebug() << "Called the C++ slot with message:" << msg;
//}


void MainModelServer::addServer(modelServer* item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_listMainModels << item;
    endInsertRows();
}

QHash<int, QByteArray> MainModelServer::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PasswordRole] = "password";
    roles[ServerRole] = "server";
    roles[UsernameRole] = "username";
    roles[ConnectRole] = "connect";
    roles[LoginRole] = "login";
    roles[AddressRole] = "address";

    return roles;
}


