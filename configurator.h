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

public slots:
    void generate();
    void reset();

private:
    void loadBoxMessage(QString message,bool error);
    Ui::Configurator *ui;
};

#endif // CONFIGURATOR_H
