#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QMainWindow>
#include "generator_logic.h"

namespace Ui {
class Configurator;
}

class Configurator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Configurator(QWidget *parent = 0);
    ~Configurator();

public slots:
    void generate();
    void reset();
    void loadBoxMessage();

private:
    bool correct_data(QString UUID,QString major, QString minor);
    Ui::Configurator *ui;
    generator_logic* logic_instance;
};

#endif // CONFIGURATOR_H
