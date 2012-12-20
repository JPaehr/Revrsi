#ifndef SERVER_GUI_H
#define SERVER_GUI_H

#include <QDialog>
#include <QMessageBox>

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
    int getWidth();
    int getHeight();
    int getPNum();
    QString getName();
    void setUILocked();
    void setUIUnLocked();
    QVector<QString> getAllNames();
signals:
    void startServer();
    void stopServer();
    void NetStartGame();

public slots:
    void setupServer();
    void NetSendStartGame();
    void terminateServer();
    void NetAddPlayerServer(QVector<QString>);

private:
    Ui::server_gui *ui;
    int player_num;
    int width;
    int height;
    //QVector<QString> player_names;
    QVector<QString> NetPlayerNames;
    bool serverIsRunning;
};

#endif // SERVER_GUI_H