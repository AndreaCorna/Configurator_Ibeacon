#include "generator_logic.h"
#include <QDebug>
#include <QFile>
generator_logic::generator_logic(QObject *parent) :
    QObject(parent)
{
}

void generator_logic::generate(QString uuid, QString major, QString minor, int strength){
   qDebug()<<uuid;
   QString file_name = "start_beacon_"+uuid+".sh";
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

