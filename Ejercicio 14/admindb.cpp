#include "admindb.h"
#include <QDebug>
#include <QSqlError>

AdminDB::AdminDB(QObject *parent) : QObject(parent) {
}

AdminDB::~AdminDB() {
    closeDB();
}

bool AdminDB::openDB(const QString &dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Error: no se pudo conectar a la base de datos.";
        qDebug() << db.lastError().text();
        return false;
    } else {
        qDebug() << "Conexión exitosa con la base de datos.";
        return true;
    }
}

void AdminDB::closeDB() {
    if (db.isOpen()) {
        db.close();
    }
}

QStringList AdminDB::validateUser(const QString &usuario, const QString &clave) {
    QStringList datosPersonales;

    if (!db.isOpen()) {
        qDebug() << "Error: la base de datos no está abierta.";
        return datosPersonales;
    }

    QSqlQuery query(db);
    query.prepare("SELECT nombre, apellido FROM usuarios WHERE usuario = :usuario AND clave = :clave");
    query.bindValue(":usuario", usuario);
    query.bindValue(":clave", clave);

    if (!query.exec()) {
        qDebug() << "Error en la ejecución de la consulta:";
        qDebug() << query.lastError().text();
    } else if (query.next()) {
        datosPersonales << query.value(0).toString(); // nombre
        datosPersonales << query.value(1).toString(); // apellido
    } else {
        qDebug() << "Usuario no válido o sin resultados.";
    }

    return datosPersonales;
}
