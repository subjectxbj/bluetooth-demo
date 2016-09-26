#ifndef BLUECONNECT_H
#define BLUECONNECT_H

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QtDBus/QtDBus>


typedef QMap<QString,QVariantMap > InterfacesMap;
typedef QMap<QDBusObjectPath,InterfacesMap> ObjectsMap;

Q_DECLARE_METATYPE(InterfacesMap)
Q_DECLARE_METATYPE(ObjectsMap)

class BlueConnect : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RoleNames {
        AddressRole = Qt::UserRole,
        NameRole = Qt::UserRole + 1,
    };

    explicit BlueConnect(QObject *parent=0);
    ~BlueConnect();

    Q_INVOKABLE void connect (uint index);
    Q_INVOKABLE void disconnect ();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;

private slots:
    void onInterfacesAdded(QDBusObjectPath path, QMap<QString,QVariantMap> interfaces);
    void onInterfacesRemoved(QDBusObjectPath path, QList<QString> interfaces);

private:
    void fetchDevices(void);
    void addDevice(QDBusObjectPath path);
    bool checkExistingDev(QDBusInterface *dev);

    QList<QDBusInterface *> devices;
    QDBusInterface *manager;
    QDBusInterface *connected;
    QHash<int, QByteArray> roles;
};

#endif // BLUECONNECT_H
