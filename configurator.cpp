#include "configurator.h"
#include "ui_configurator.h"
#include "QDebug"
#include "QMessageBox"

Configurator::Configurator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configurator)
{
    ui->setupUi(this);
    logic_instance = new generator_logic();
    connect(logic_instance,SIGNAL(call_gui()),this,SLOT(loadBoxMessage()));
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

    QString uuid = ui->lineUUID->text();
    QString major = ui->lineMajor->text();
    QString minor = ui->lineMinor->text();
    if(minor.compare("")!=0 && major.compare("")!=0 && uuid.compare("")!=0){
        if(correct_data(uuid,major,minor)){
            logic_instance->generate(uuid,major,minor,ui->horizontalSlider->value());
        }else{
            QMessageBox::warning(NULL,"Wrong Parameters","You have to insert correct parameters in order to generate the script");
        }
    }else{
         QMessageBox::warning(NULL,"Please Insert all parameters","You cannot create an iBeacon without specifing all parameters");
    }
}

void Configurator::reset(){
    ui->lineMajor->clear();
    ui->lineMinor->clear();
    ui->lineUUID->clear();
    ui->horizontalSlider->setValue(50);
}

bool Configurator::correct_data(QString UUID,QString major, QString minor){
    int major_number = major.toInt();
    int minor_number = minor.toInt();
    int uuid_size = UUID.size();
    if( (major_number <0 || major_number >= 65536) ||
          (minor_number <0 || minor_number >= 65536)  ||
            uuid_size != 32)
        return false;
    return true;
}


void Configurator::loadBoxMessage(){
    reset();

    QMessageBox::information(NULL,"Creation Complete","The script was successfully created");
}
