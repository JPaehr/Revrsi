#ifndef SERVER_GUI_H
#define SERVER_GUI_H

#include <QDialog>

namespace Ui {
class server_gui;
}

class server_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit server_gui(QWidget *parent = 0);
    ~server_gui();
    
private:
    Ui::server_gui *ui;
};

#endif // SERVER_GUI_H
