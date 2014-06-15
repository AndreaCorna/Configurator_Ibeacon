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
    connect(this->ui->major_check,SIGNAL(clicked()),this,SLOT(set_slider()));
    connect(this->ui->minor_check,SIGNAL(clicked()),this,SLOT(set_slider()));
    connect(this->ui->unit_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->unit_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->ten_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->hundred_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));

    ui->unit_slider->setEnabled(false);
    ui->ten_slider->setEnabled(false);
    ui->hundred_slider->setEnabled(false);


}

Configurator::~Configurator()
{
    delete ui;
}

/*
 * Public slots
 */

void Configurator::set_slider(){
    qDebug()<<"set slider";
    bool first_check = ui->major_check->isChecked();
    bool second_check = ui->minor_check->isChecked();
    if(first_check || second_check){
        ui->unit_slider->setEnabled(true);
        ui->ten_slider->setEnabled(true);
        ui->hundred_slider->setEnabled(true);
        if(first_check && second_check)
            mls=2;
        else
            mls=1;
    }else{
        ui->unit_slider->setEnabled(false);
        ui->ten_slider->setEnabled(false);
        ui->hundred_slider->setEnabled(false);
    }
}

void Configurator::set_number(int num){
    number =(num*65536*mls)/100;
    ui->number_label->setNum(number);
}


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
    ui->major_check->setChecked(false);
    ui->minor_check->setChecked(false);
    ui->unit_slider->setValue(0);
    ui->ten_slider->setValue(0);
    ui->hundred_slider->setValue(0);
    ui->unit_slider->setEnabled(false);
    ui->ten_slider->setEnabled(false);
    ui->hundred_slider->setEnabled(false);

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
