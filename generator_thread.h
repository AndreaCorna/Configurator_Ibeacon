#ifndef GENERATOR_THREAD_H
#define GENERATOR_THREAD_H

#include <QThread>
#include <QtCore>

class generator_thread: public QThread
{
public:
    generator_thread(int number,QString uuid, QString major, QString minor,int strength_level);
    void run();
    void set_update_minor(bool update);
    void set_last(bool is_last);

signals:
    void call_gui();


private:
    QString create_command_string(QString uuid);
    QString parse_int(int number);
    void create_script(QString uuid,QString major, QString minor, int strength);
    int number_to_generate;
    QString uuid;
    QString major;
    QString minor;
    int strength_level;
    bool update_minor;
    bool last;
};

#endif // GENERATOR_THREAD_H
