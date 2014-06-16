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
   create_script(uuid,major,minor,strength);
   emit call_gui();
}

void generator_logic::create_script(QString uuid,QString major, QString minor, int strength){
    QString file_name = uuid+"/start_beacon_"+major+"_"+minor+".sh";
    qDebug()<<file_name;
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
         QTextStream output_stream(&file);
         QString command = "#!/bin/bash \nhciconfig hci0 up\nhciconfig hci0 leadv 3 \n";
         command.append(create_command_string(uuid));
         command.append(parse_int(major.toInt()));
         command.append(parse_int(minor.toInt()));
         command.append(QString::number(strength,16));
         command.append(" 00");
         qDebug()<<command;
         output_stream<<command;
    }
    file.setPermissions(QFile::ExeGroup | QFile::ReadGroup | QFile::ReadOwner | QFile::ReadOther | QFile::WriteOwner | QFile::ExeUser);
}


void generator_logic::generate_list(QString uuid, int strength, int number, bool update_minor){
    QDir().mkdir(uuid);
    if(number <= 65536){
        QString zero = QString::number(0);
        for(int i = 0; i<number;i++){
            QString other = QString::number(i);
            if(update_minor)
                create_script(uuid,zero,other,strength);
            else
                create_script(uuid,other,zero,strength);
        }
    }else{
        int major_cycles = ((number -1)/65536) + 1;
        for(int i = 0; i < major_cycles; i++){

        }
    }
    emit call_gui();

}


QString generator_logic::create_command_string(QString uuid){
    QString command = "hcitool -i hci0 cmd 0x08 0x0008 1e 02 01 1a 1a ff 4c 00 02 15 ";
    qDebug()<<command;
    for(int i=2;i<50;i = i+3){
        uuid.insert(i," ");
    }
    command.append(uuid);
    qDebug()<<command;

    return command;
}

QString generator_logic::parse_int(int number){

    QString number_string = QString::number(number,16);
    qDebug()<<number_string;
    while(number_string.size()<4){
        number_string.prepend("0");
    }
    number_string.insert(2," ");
    number_string.append(" ");
    return number_string;
}

