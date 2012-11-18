#include "new_game_settings.h"
#include "ui_new_game_settings.h"

new_game_settings::new_game_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_game_settings)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(set_player_number()));
    this->player_number = 2;
    ui->two_player_btn->setChecked(true);
}

int new_game_settings::get_choosen_number(){
    return this->player_number;
}

new_game_settings::~new_game_settings()
{
    delete ui;
}

void new_game_settings::set_player_number()
{
    if(ui->two_player_btn->isChecked()){
        this->player_number = 2;
    }
    else if(ui->three_player_btn->isChecked()){
        this->player_number = 3;
    }
    else if(ui->four_player_btn->isChecked()){
        this->player_number = 4;
    }
    else{
        this->player_number = 2;
    }
    out << "New Game:  Players =" << this->player_number;
}
