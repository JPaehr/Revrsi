#include "server_gui.h"
#include "ui_server_gui.h"

server_gui::server_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_gui)
{
    ui->setupUi(this);
}

server_gui::~server_gui()
{
    delete ui;
}
