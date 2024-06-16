#include <QApplication>
#include "login.h"
#include "formulario.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Login login;
    Formulario formulario;

    QObject::connect(&login, &Login::usuarioValido, [&]() {
        formulario.show();
    });

    login.show();

    return a.exec();
}
