#include "new_game_settings.h"
#include "ui_new_game_settings.h"

new_game_settings::new_game_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_game_settings){
    ui->setupUi(this);

    connect(ui->new_game_settings_buttonbox,SIGNAL(accepted()),this, SLOT(set_settings()));
    connect(ui->two_player_btn,SIGNAL(clicked()),this,SLOT(change_field_size()));
    connect(ui->three_player_btn,SIGNAL(clicked()),this,SLOT(change_field_size()));
    connect(ui->four_player_btn,SIGNAL(clicked()),this,SLOT(change_field_size()));

    this->player_number = 2;
    ui->two_player_btn->setChecked(true);
}

int new_game_settings::get_choosen_number(){
    return this->player_number;
}

QPoint new_game_settings::get_field_size(){
    return QPoint(this->x_size, this->y_size);
}

QVector<QString> new_game_settings::get_player_names(){
    QVector<QString> names;
    names.push_back(ui->player1Name_lineEdit->text());
    names.push_back(ui->player2Name_lineEdit->text());
    names.push_back(ui->player3Name_lineEdit->text());
    names.push_back(ui->player4Name_lineEdit->text());
    return names;
}

new_game_settings::~new_game_settings(){
    delete ui;
}

void new_game_settings::closeEvent(QCloseEvent *){
    if(ui->two_player_btn->isChecked()){
        this->player_number = 2;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    else if(ui->three_player_btn->isChecked()){
        this->player_number = 3;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    else if(ui->four_player_btn->isChecked()){
        this->player_number = 4;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    else{
        this->player_number = 2;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    this->rejected();
}

void new_game_settings::set_settings(){
    if(ui->two_player_btn->isChecked()){
        this->player_number = 2;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    else if(ui->three_player_btn->isChecked()){
        this->player_number = 3;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    else if(ui->four_player_btn->isChecked()){
        this->player_number = 4;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    else{
        this->player_number = 2;
        this->x_size = ui->breite_spinbox->value();
        this->y_size = ui->hoehe_spinbox->value();
    }
    this->accepted();
}

void new_game_settings::change_field_size(){
    if(ui->two_player_btn->isChecked()){
        ui->breite_spinbox->setValue(8);
        ui->hoehe_spinbox->setValue(8);
    }
    else if(ui->three_player_btn->isChecked()){
        ui->breite_spinbox->setValue(9);
        ui->hoehe_spinbox->setValue(9);
    }
    else if(ui->four_player_btn->isChecked()){
        ui->breite_spinbox->setValue(10);
        ui->hoehe_spinbox->setValue(10);
    }
    else{
        ui->breite_spinbox->setValue(8);
        ui->hoehe_spinbox->setValue(8);
    }
}
