#ifndef GENERATOR_LOGIC_H
#define GENERATOR_LOGIC_H
#include "generator_thread.h"
#include <QObject>

class generator_logic : public QObject
{
    Q_OBJECT
public:
    explicit generator_logic(QObject *parent = 0);
    void generate(QString uuid, QString major, QString minor, int strength);
    void generate_list(QString uuid, int strength, int number, bool update_minor);

signals:
    void call_gui();


public slots:
    void notify_finish_thread();

private:
    QString create_command_string(QString uuid);
    QString parse_int(int number);
    void create_script(QString uuid,QString major, QString minor, int strength);
    generator_thread* single_thread;


};

#endif // GENERATOR_LOGIC_H
