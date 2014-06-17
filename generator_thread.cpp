#include "generator_thread.h"
#include <QDebug>
#include <QFile>
#include <QDir>

generator_thread::generator_thread(int number,QString uuid, QString major, QString minor,int strength_level){
    this->number_to_generate = number;
    this->uuid = uuid;
    this->major = major;
    this->minor = minor;
    this->strength_level = strength_level;
}


void generator_thread::run(){
    qDebug()<<"start run";
    if(number_to_generate == 1){
        qDebug()<<"1 iter";

        create_script(uuid,major,minor,strength_level);
        emit finished();

    }else if(number_to_generate <= 65536){
        qDebug()<<"più iteer";
        if(update_minor){
            qDebug()<<"in loop per piu";
            for(int i=0;i<number_to_generate;i++){
                create_script(uuid,major,QString::number(i),strength_level);
            }
            if(last){
                emit finished();
            }
        }else{
            for(int i=0;i<number_to_generate;i++){
                create_script(uuid,QString::number(i),minor,strength_level);
            }
            emit finished();

        }

    }

}

void generator_thread::set_update_minor(bool update){
    update_minor = update;
}

void generator_thread::set_last(bool is_last){
    last = is_last;
}


void generator_thread::create_script(QString uuid,QString major, QString minor, int strength){
    QString file_name;
    if(update_minor)
        file_name = uuid+"/"+major+"/start_beacon_"+major+"_"+minor+".sh";
    else
        file_name = uuid+"/"+minor+"/start_beacon_"+major+"_"+minor+".sh";

    //qDebug()<<file_name;
    QFile file(file_name);
    if(file.open(QIODevice::ReadWrite)){
         QTextStream output_stream(&file);
         QString command = "#!/bin/bash \nhciconfig hci0 up\nhciconfig hci0 leadv 3 \n";
         command.append(create_command_string(uuid));
         command.append(parse_int(major.toInt()));
         command.append(parse_int(minor.toInt()));
         command.append(QString::number(strength,16));
         command.append(" 00");
         //qDebug()<<command;
         output_stream<<command;
    }
    file.setPermissions(QFile::ExeGroup | QFile::ReadGroup | QFile::ReadOwner | QFile::ReadOther | QFile::WriteOwner | QFile::ExeUser);
}

QString generator_thread::create_command_string(QString uuid){
    QString command = "hcitool -i hci0 cmd 0x08 0x0008 1e 02 01 1a 1a ff 4c 00 02 15 ";
    //qDebug()<<command;
    QByteArray array = uuid.toAscii();
    for(int i=0;i<32;i = i+2){
       char first = array[i];
       char second = array[i+1];
       QString section = ""+first;
       section.append(second);
       command.append(section.toAscii().toHex());
       command.append(" ");
    }

    //command.append(uuid);
    //qDebug()<<command;

    return command;
}

QString generator_thread::parse_int(int number){

    QString number_string = QString::number(number,16);
    //qDebug()<<number_string;
    while(number_string.size()<4){
        number_string.prepend("0");
    }
    number_string.insert(2," ");
    number_string.append(" ");
    return number_string;
}
