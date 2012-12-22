#include "ai_settings.h"
#include "ui_ai_settings.h"

AI_settings::AI_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AI_settings)
{
    ui->setupUi(this);
}

AI_settings::~AI_settings()
{
    delete ui;
}

bool AI_settings::aiActivated(int ki_number){
    if(ki_number == 1){
        if(ui->ki1_cb->isChecked()){
            return true;
        }
    }
    else if(ki_number == 2){
        if(ui->ki2_cb->isChecked()){
            return true;
        }
    }
    else if(ki_number == 3){
        if(ui->ki3_cb->isChecked()){
            return true;
        }
    }
    else if(ki_number == 4){
        if(ui->ki4_cb->isChecked()){
            return true;
        }
    }
    return false;
}
