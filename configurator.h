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
    void set_sliders();
    void set_number(int num);

private:
    bool correct_data(QString UUID,QString major, QString minor);
    void enable_sliders(bool enable);
    void create_connect();
    void setup_sliders();
    void enable_editor_numbers(bool enable);

    Ui::Configurator *ui;
    generator_logic* logic_instance;
    int mls;
    int number,unit,ten,hundred,thousand,ten_thousand,hundred_thousand;
};

#endif // CONFIGURATOR_H
