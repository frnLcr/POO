#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class Formulario : public QWidget
{
    Q_OBJECT

public:
    explicit Formulario(QWidget *parent = nullptr);

private slots:
    void slot_Guardar();

private:
    QLabel *lLegajo;
    QLabel *lNombre;
    QLabel *lApellido;
    QLineEdit *leLegajo;
    QLineEdit *leNombre;
    QLineEdit *leApellido;
    QPushButton *pbGuardar;
    QVBoxLayout *layout;
};

#endif // FORMULARIO_H
