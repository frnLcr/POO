#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkReply>
#include "admindb.h" // Incluir la cabecera de AdminDB

class Login : public QWidget {
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);

    void mostrarTemperatura(bool mostrar);

signals:
    void usuarioValido();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void slot_ValidarUsuario();
    void slot_alternarTemperatura();
    void slot_descargafinalizadaClima(QNetworkReply *reply);
    void slot_descargafinalizada(QNetworkReply *reply);

private:
    QLabel *lUsuario;
    QLabel *lClave;
    QLabel *lClima;
    QLineEdit *leUsuario;
    QLineEdit *leClave;
    QPushButton *pbValidar;
    QPushButton *pbAlternarTemperatura;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *managerClima;
    QImage im;
    AdminDB *adminDB; // Añadir el objeto AdminDB
};

#endif // LOGIN_H
