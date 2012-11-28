#include "win_gui.h"
#include "ui_win_gui.h"
#include <QDebug>
#define out qDebug()

win_gui::win_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::win_gui)
{
    ui->setupUi(this);
}

win_gui::~win_gui(){
    delete ui;
}


void win_gui::win_slot(QVector<int> in_vector){
    win_vector = in_vector;
    out << "ssssssssssssssssssssssssssssssssssssssssssssss";

}
