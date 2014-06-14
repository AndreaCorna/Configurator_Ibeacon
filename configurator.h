#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QMainWindow>

namespace Ui {
class Configurator;
}

class Configurator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Configurator(QWidget *parent = 0);
    ~Configurator();

private:
    Ui::Configurator *ui;
};

#endif // CONFIGURATOR_H
