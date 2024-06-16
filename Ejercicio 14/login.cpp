#include "login.h"
#include <QGridLayout>
#include <QPainter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Login::Login(QWidget *parent) : QWidget(parent) {
    setMaximumSize(750, 500);
    setMinimumSize(250, 250);
    setWindowTitle("Ejercicio 14");

    lUsuario = new QLabel("Usuario:");
    leUsuario = new QLineEdit;
    lClave = new QLabel("Clave:");
    leClave = new QLineEdit;
    leClave->setEchoMode(QLineEdit::Password);
    pbValidar = new QPushButton("Validar");
    pbAlternarTemperatura = new QPushButton("Mostrar u ocultar Temperatura");
    lClima = new QLabel("");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(lUsuario, 0, 0);
    layout->addWidget(leUsuario, 0, 1);
    layout->addWidget(lClave, 1, 0);
    layout->addWidget(leClave, 1, 1);
    layout->addWidget(pbValidar, 2, 1, 1, 2);
    layout->addWidget(pbAlternarTemperatura, 3, 0, 1, 2);
    layout->addWidget(lClima, 4, 0, 1, 2);

    connect(pbValidar, SIGNAL(pressed()), this, SLOT(slot_ValidarUsuario()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(slot_ValidarUsuario()));
    connect(pbAlternarTemperatura, SIGNAL(pressed()), this, SLOT(slot_alternarTemperatura()));

    manager = new QNetworkAccessManager(this);
    managerClima = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargafinalizada(QNetworkReply*)));
    connect(managerClima, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargafinalizadaClima(QNetworkReply*)));

    QNetworkRequest requestClima(QUrl("https://api.weatherapi.com/v1/current.json?key=6ebf146961d24c06b6a02801241104&q=Cordoba&aqi=no"));
    managerClima->get(requestClima);

    QNetworkRequest request(QUrl("https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEjqKFbXPLmoTaXmgvFDJxcT2L3KWCdLrwI4FIi8rLxVAYBkmofOvzIpPXEAkU9Oba4OD2VF1zWVGQPMPnBcwojztewxcevaalMMEFWrFPq7UrEVsL-PmzGHbNgbUPipCmk2LUraHmBjNBg/s1600/Captura+de+pantalla+de+2016-07-19+23-58-04.png"));
    manager->get(request);

    adminDB = new AdminDB(this);
    adminDB->openDB("C:/Users/ignad/Documents/POO/Ejercicios/Ejercicio 14/Ejercicio14/db.sqlite");
}

void Login::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, im.scaled(this->width(), this->height()));
}

void Login::slot_descargafinalizadaClima(QNetworkReply *reply) {
    QByteArray jsonDevuelto = reply->readAll();
    qDebug() << jsonDevuelto;

    QJsonDocument doc = QJsonDocument::fromJson(jsonDevuelto);
    if (doc.isObject()) {
        QJsonObject currentObject = doc.object()["current"].toObject();
        if (currentObject.contains("temp_c")) {
            double temperatureC = currentObject["temp_c"].toDouble();
            qDebug() << "Temperature (Celsius):" << temperatureC;
            lClima->setText(QString("%1°C").arg(temperatureC));
            lClima->setVisible(true);
        } else {
            qDebug() << "Error: 'temp_c' key not found in 'current' object";
        }
    } else {
        qDebug() << "Error: Invalid JSON format";
    }
}

void Login::mostrarTemperatura(bool mostrar) {
    lClima->setVisible(mostrar);
}

void Login::slot_alternarTemperatura() {
    mostrarTemperatura(!lClima->isVisible());
}

void Login::slot_descargafinalizada(QNetworkReply *reply) {
    im = QImage::fromData(reply->readAll());
    this->repaint();
}

void Login::slot_ValidarUsuario() {
    QString usuario = leUsuario->text();
    QString clave = leClave->text();

    QStringList datos = adminDB->validateUser(usuario, clave);
    if (!datos.isEmpty()) {
        emit usuarioValido();
    } else {
        qDebug() << "Usuario no válido";
    }
}
