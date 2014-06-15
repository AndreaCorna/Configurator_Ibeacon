#include "generator_logic.h"
#include <QDebug>
#include <QFile>
generator_logic::generator_logic(QObject *parent) :
    QObject(parent)
{
}

void generator_logic::generate(QString uuid, QString major, QString minor){
   qDebug()<<uuid;
   QString file_name = "start_beacon_"+uuid+".sh";
   qDebug()<<file_name;
   QFile file(file_name);
   if(file.open(QIODevice::ReadWrite)){
        QTextStream output_stream(&file);
        output_stream<<"#!/bin/bash \nhciconfig hci0 up\n hciconfig hci0 leadv 3 \nhcitool -i hci0 cmd 0x08 0x0008 1e 02 01 1a 1a ff 4c 00 02 15 e2 c5 6d b5 df fb 48 d2 b0 60 d0 f5 a7 10 96 e0 00 00 00 00 bc 00";
   }
   file.setPermissions(QFile::ExeGroup | QFile::ReadGroup | QFile::ReadOwner | QFile::ReadOther | QFile::WriteOwner | QFile::ExeUser);
   emit call_gui();
}


