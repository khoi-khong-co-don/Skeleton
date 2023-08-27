#ifndef EditServerModel_H
#define EditServerModel_H
#include <QObject>
#include <QAbstractListModel>
#include <QDebug>

class editServerItem {
public:
    editServerItem(QString name, QString server, QString username, QString password, QString connect, QString login);

    QString name() const;

    QString server() const;

    QString username() const;

    QString password() const;

    QString connect() const;

    QString login() const;

    void setName(QString name);
    void setServer(QString server);
    void setUsername(QString username);
    void setPassword(QString password);
    void setConnect(QString connect);
    void setLogin(QString login);

private:
    QString m_name = "";
    QString m_server = "";
    QString m_username = "";
    QString m_password = "";
    QString m_connect = "";
    QString m_login = "";
};


class EditServerModel : public QAbstractListModel
{
    Q_OBJECT
   // Q_PROPERTY(QList<serverModel()> name READ name)
public:
    explicit EditServerModel(QObject *parent = nullptr);

    enum Roles {
        NameRole = Qt::UserRole + 1,
        ServerRole,
        UsernameRole,
        PasswordRole,
        ConnectRole,
        LoginRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void moveItem(int from, int to);
    void addServer(editServerItem* item);

    QList<editServerItem*> serverModel() const;

    Q_INVOKABLE QVariantMap get(int row) const;

//    signals:
//        void listMainModelsChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<editServerItem*> m_serverModel;

};


#endif // EditServerModel_H
