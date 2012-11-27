#include "win_gui.h"
#include "ui_win_gui.h"

win_gui::win_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::win_gui)
{
    ui->setupUi(this);
}

win_gui::~win_gui(){
    delete ui;
}


void win_gui::win_slot(std::vector<int> in_vector){
    win_vector = in_vector;
}
