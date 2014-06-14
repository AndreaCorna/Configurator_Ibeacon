#include "configurator.h"
#include "ui_configurator.h"
#include "QDebug"
#include "QMessageBox"

Configurator::Configurator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configurator)
{
    ui->setupUi(this);
}

Configurator::~Configurator()
{
    delete ui;
}

/*
 * Public slots
 */

void Configurator::generate(){
    qDebug()<<"generate";

    QString UUID = ui->lineUUID->text();
    QString major = ui->lineMajor->text();
    QString minor = ui->lineMinor->text();
    if(minor.compare("")!=0 && major.compare("")!=0 && UUID.compare("")!=0){

    }else{
         QMessageBox::warning(NULL,"Please Insert all parameters","You cannot create an iBeacon without specifing all parameters");
    }
}

void Configurator::reset(){
    qDebug()<<"reset";

}

void Configurator::loadBoxMessage(QString message,bool error){

}
