#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <QDialog>

namespace Ui {
class client_gui;
}

class client_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit client_gui(QWidget *parent = 0);
    ~client_gui();

signals:
    void send_startClient();

public slots:
    void startClient();
    
private:
    Ui::client_gui *ui;
};

#endif // CLIENT_GUI_H
