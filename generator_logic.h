#ifndef GENERATOR_LOGIC_H
#define GENERATOR_LOGIC_H

#include <QObject>

class generator_logic : public QObject
{
    Q_OBJECT
public:
    explicit generator_logic(QObject *parent = 0);
    void generate(QString uuid, QString major, QString minor);

signals:
    void call_gui();


public slots:

};

#endif // GENERATOR_LOGIC_H
