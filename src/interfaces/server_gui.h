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
    QVector<int> getGameValues();
signals:
    void startServer();

public slots:
    void setupServer();

private:
    Ui::server_gui *ui;
    int player_num;
    int width;
    int height;
    QVector<QString> player_names;
    bool serverIsRunning;
};

#endif // SERVER_GUI_H
