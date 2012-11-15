#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings(){
    delete ui;
}

int settings::get_x(){
    return(ui->lineEdit->text().toInt());
}

int settings::get_y(){
    return(ui->lineEdit->text().toInt());
}
