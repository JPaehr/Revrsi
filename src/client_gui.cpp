#include "client_gui.h"
#include "ui_client_gui.h"

client_gui::client_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_gui)
{
    ui->setupUi(this);
}

client_gui::~client_gui()
{
    delete ui;
}
