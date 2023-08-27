#ifndef MAINMODELSERVER_H
#define MAINMODELSERVER_H
#include <QAbstractListModel>
#include <QObject>

class modelServer  {

public:
    modelServer(QString name, QString server, QString username, QString password, QString connect, QString login);

    QString name() const;

    QString server() const;

    QString username() const;

    QString password() const;

    QString connect() const;

    QString login() const;

    QString address() const;

private:
    QString m_name = "";
    QString m_server = "";
    QString m_username = "";
    QString m_password = "";
    QString m_connect = "";
    QString m_login = "";
};



class MainModelServer : public QAbstractListModel
{
    Q_OBJECT
   // Q_PROPERTY( QList<modelServer> listMainModels READ listMainModels)
public:
    explicit MainModelServer(QObject *parent = nullptr);

    enum Roles {
        NameRole = Qt::UserRole + 1,
        ServerRole,
        UsernameRole,
        PasswordRole,
        ConnectRole,
        LoginRole,
        AddressRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void moveItem(int from, int to);
    void addServer(modelServer* item);

    QList<modelServer*> listMainModels() const;

//public slots:
//    void receMsg(const QString &msg);
signals:
       void sendMsg(const QString &msg);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<modelServer*> m_listMainModels;
};

#endif // MAINMODELSERVER_H
