#include "generator_logic.h"
#include <QDebug>
#include <QFile>
#include <QDir>


generator_logic::generator_logic(QObject *parent) :
    QObject(parent)
{
}

void generator_logic::generate(QString uuid, QString major, QString minor, int strength){
   qDebug()<<uuid;
   QDir().mkdir(uuid);
   QDir().mkdir(uuid+"/"+major);
   single_thread = new generator_thread(1,uuid,major,minor,strength);
   connect(single_thread,SIGNAL(finished()),this,SLOT(notify_finish_thread()));
   single_thread->run();

}

void generator_logic::notify_finish_thread(){
    emit call_gui();
}



void generator_logic::generate_list(QString uuid, int strength, int number, bool update_minor){
    QDir().mkdir(uuid);
    if(number <= generator_thread::NUMBER_LIMIT){
        QString zero = QString::number(0);
        QString other = QString::number(1);
           if(update_minor){
               QDir().mkdir(uuid+"/"+zero);
               single_thread = new generator_thread(number,uuid,zero,other,strength);
               single_thread->set_update_minor(true);
               connect(single_thread,SIGNAL(finished()),this,SLOT(notify_finish_thread()));
               single_thread->set_last(true);
               single_thread->run();
           }else{
               QDir().mkdir(uuid+"/"+zero);
               single_thread = new generator_thread(number,uuid,other,zero,strength);
               single_thread->set_update_minor(false);
               connect(single_thread,SIGNAL(finished()),this,SLOT(notify_finish_thread()));
               single_thread->run();
    }

    }else{
        int major_cycles = ((number -1)/generator_thread::NUMBER_LIMIT)+1;
        int last_cycle = number - (number/generator_thread::NUMBER_LIMIT)*generator_thread::NUMBER_LIMIT;
        QString zero = QString::number(0);
        qDebug()<<"major cycle"+QString::number(major_cycles);
        for(int i = 0;i < major_cycles;i++){
            int to_create;
            QDir().mkdir(uuid+"/"+QString::number(i));

            qDebug()<<"in loop";
            if(i == major_cycles -1){
                to_create = last_cycle;
                qDebug()<<"last";

            }else
                to_create = generator_thread::NUMBER_LIMIT;
            qDebug()<<"in loop 2";

            QString major_number = QString::number(i);
            generator_thread* thread = new generator_thread(to_create,uuid,major_number,zero,strength);
            connect(thread,SIGNAL(finished()),this,SLOT(notify_finish_thread()));
            thread->set_update_minor(true);
            qDebug()<<"in loop 3";

            if(i == major_cycles -1){
                thread->set_last(true);
                qDebug()<<"set last";

            }
            thread->run();
        }
    }
}




