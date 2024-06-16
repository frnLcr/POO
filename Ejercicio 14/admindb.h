#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>

class AdminDB : public QObject {
    Q_OBJECT
public:
    AdminDB(QObject *parent = nullptr);
    ~AdminDB();

    bool openDB(const QString &dbPath);
    void closeDB();
    QStringList validateUser(const QString &usuario, const QString &clave);

private:
    QSqlDatabase db;
};

#endif // ADMINDB_H
