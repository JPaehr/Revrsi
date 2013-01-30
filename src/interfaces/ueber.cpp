#include "ueber.h"
#include "ui_ueber.h"

ueber::ueber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ueber)
{
    ui->setupUi(this);
}

ueber::~ueber()
{
    delete ui;
}
