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
    number = 1;
    ui->number_label->setNum(number);
    create_connect();
    setup_sliders();
    enable_sliders(false);
}

Configurator::~Configurator()
{
    delete ui;
}

/*
 * Public slots
 */

void Configurator::set_sliders(){
    qDebug()<<"set slider";
    bool first_check = ui->major_check->isChecked();
    bool second_check = ui->minor_check->isChecked();
    if(first_check || second_check){
        enable_sliders(true);
        enable_editor_numbers(false);
        if(first_check && second_check){
            mls=2;
            ui->ten_thousand_slider->setMaximum(10);
            ui->hunder_thousand_slider->setEnabled(true);
        }else{
            mls=1;
            ui->ten_thousand_slider->setMaximum(6);
            ui->hunder_thousand_slider->setEnabled(false);

        }
    }else{
        enable_sliders(false);
        enable_editor_numbers(true);
        number = 1;
        ui->number_label->setNum(number);

    }
}

void Configurator::set_number(int num){
    unit = ui->unit_slider->value();
    ten = ui->ten_slider->value();
    hundred = ui->hundred_slider->value();
    thousand = ui->thousand_slider->value();
    ten_thousand = ui->ten_thousand_slider->value();
    hundred_thousand = ui->hunder_thousand_slider->value();
    number =unit+ten*10+hundred*100+thousand*1000+ten_thousand*10000+hundred_thousand*100000;
    if(mls==1 && number >= 65536*mls)
        number = 65536*mls;
    ui->number_label->setNum(number);
}


void Configurator::generate(){
    qDebug()<<"generate";

    QString uuid = ui->lineUUID->text();
    QString major = ui->lineMajor->text();
    QString minor = ui->lineMinor->text();
    if(!ui->major_check->isChecked() && !ui->minor_check->isChecked()){
        if(minor.compare("")!=0 && major.compare("")!=0 && uuid.compare("")!=0){
            if(correct_data(uuid,major,minor)){
                logic_instance->generate(uuid,major,minor,ui->horizontalSlider->value());
            }else{
                QMessageBox::warning(NULL,"Wrong Parameters","You have to insert correct parameters in order to generate the script");
            }
        }else{
                 QMessageBox::warning(NULL,"Please Insert all parameters","You cannot create an iBeacon without specifing all parameters");
        }
    }else{
        logic_instance->generate_list(uuid,ui->horizontalSlider->value(),number,ui->minor_check->isChecked());
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
    ui->thousand_slider->setValue(0);
    ui->ten_thousand_slider->setValue(0);
    ui->hunder_thousand_slider->setValue(0);
    enable_sliders(false);
    enable_editor_numbers(true);
    number = 1;

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

void Configurator::enable_sliders(bool enable){
    ui->unit_slider->setEnabled(enable);
    ui->ten_slider->setEnabled(enable);
    ui->hundred_slider->setEnabled(enable);
    ui->thousand_slider->setEnabled(enable);
    ui->ten_thousand_slider->setEnabled(enable);
    ui->hunder_thousand_slider->setEnabled(enable);
}


void Configurator::create_connect(){
    connect(logic_instance,SIGNAL(call_gui()),this,SLOT(loadBoxMessage()));
    connect(this->ui->unit_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->unit_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->ten_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->hundred_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->thousand_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->ten_thousand_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
    connect(this->ui->hunder_thousand_slider,SIGNAL(valueChanged(int)),this,SLOT(set_number(int)));
}

void Configurator::setup_sliders(){
    ui->unit_slider->setMaximum(10);
    ui->unit_slider->setSingleStep(1);
    ui->unit_slider->setTickInterval(1);
    ui->ten_slider->setMaximum(10);
    ui->ten_slider->setSingleStep(1);
    ui->ten_slider->setTickInterval(1);
    ui->hundred_slider->setMaximum(10);
    ui->hundred_slider->setSingleStep(1);
    ui->hundred_slider->setTickInterval(1);
    ui->thousand_slider->setMaximum(10);
    ui->thousand_slider->setSingleStep(1);
    ui->thousand_slider->setTickInterval(1);
    ui->ten_thousand_slider->setMaximum(10);
    ui->ten_thousand_slider->setSingleStep(1);
    ui->ten_thousand_slider->setTickInterval(1);
    ui->hunder_thousand_slider->setMaximum(10);
    ui->hunder_thousand_slider->setSingleStep(1);
    ui->hunder_thousand_slider->setTickInterval(1);
}

void Configurator::enable_editor_numbers(bool enable){
     ui->lineMajor->setEnabled(enable);
     ui->lineMinor->setEnabled(enable);
}

