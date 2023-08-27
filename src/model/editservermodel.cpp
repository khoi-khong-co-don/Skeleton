#include "editservermodel.h"

editServerItem::editServerItem(QString name, QString server, QString username, QString password, QString connect, QString login)
{
    m_name = name;
    m_server = server;
    m_username = username;
    m_password = password;
    m_connect = connect;
    m_login = login;
    qDebug() << __func__ << m_name;
}

QString editServerItem::name() const
{
    return m_name;
}

QString editServerItem::server() const
{
    return m_server;
}

QString editServerItem::username() const
{
    return m_username;
}

QString editServerItem::password() const
{
    return m_password;
}

QString editServerItem::connect() const
{
    return m_connect;
}

QString editServerItem::login() const
{
    return m_login;
}

void editServerItem::setName(QString name)
{
    m_name = name;
}

void editServerItem::setServer(QString server)
{
    m_server = server;
}

void editServerItem::setUsername(QString username)
{
    m_username = username;
}

void editServerItem::setPassword(QString password)
{
    m_password = password;
}

void editServerItem::setConnect(QString connect)
{
    m_connect = connect;
}

void editServerItem::setLogin(QString login)
{
    m_login = login;
}


EditServerModel::EditServerModel(QObject *parent)
{
    Q_UNUSED(parent)
}

int EditServerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_serverModel.count();
}


QVariant EditServerModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_serverModel.count())
        return QVariant();

    const editServerItem* item = m_serverModel[index.row()];
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
    return QVariant();
}

void EditServerModel::moveItem(int from, int to)
{
    if(from < m_serverModel.count() && to <m_serverModel.count() && from != to)
    {
        m_serverModel.move(from, to);
    }
}

QList<editServerItem*> EditServerModel::serverModel() const
{
    return m_serverModel;
}


void EditServerModel::addServer(editServerItem* item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_serverModel << item;
    endInsertRows();
}

QHash<int, QByteArray> EditServerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PasswordRole] = "password";
    roles[ServerRole] = "server";
    roles[UsernameRole] = "username";
    roles[ConnectRole] = "connect";
    roles[LoginRole] = "login";

    return roles;
}

Q_INVOKABLE QVariantMap EditServerModel::get(int row) const
{
    QHash<int, QByteArray> names = roleNames();
    QHashIterator<int, QByteArray> i(names);
    QVariantMap res;
    QModelIndex idx = index(row, 0);
    while(i.hasNext()) {
        i.next();
        QVariant data = idx.data(i.key());
        res[i.value()] = data;

    }
    //qDebug() << res;
    return res;
}
