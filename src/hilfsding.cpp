#include "hilfsding.h"
#include "ui_hilfsding.h"

hilfsding::hilfsding(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hilfsding)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pb1()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(pb2()));
}

hilfsding::~hilfsding()
{
    delete ui;
}

void hilfsding::pb1()
{emit pb1s(ui->lineEdit->text().toInt());
}

void hilfsding::pb2()
{emit pb2s(ui->lineEdit_2->text().toInt());

}
