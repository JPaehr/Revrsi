#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <QDialog>
#include <QMessageBox>
#include <QtGui>
#include <QApplication>

using namespace std;

namespace Ui {
class client_gui;
}

class client_gui :public QDialog
{
    Q_OBJECT
    
public:
    explicit client_gui(QWidget *parent = 0);
    ~client_gui();

    QVector<QString> getAllNames();
    bool finClientInterface;
    void setClientUnLocked();

signals:
    void send_startClient();
    void setLocked();
    void NetTerminateClient();
    void test_signal();
    void disconnect();
    void disableNetMode();

public slots:
    void startClient();
    void NetAddPlayer(QVector<QString>);
    void getPlayerNameOnChange(QString);
    QString getPlayerName();
    string getIP();
    void setLockedSL();
    void fin();

private:
    Ui::client_gui *ui;
    QVector<QString> NetPlayerNames;
    int playerCounter;
    QString ownName;
    int clientCounter;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CLIENT_GUI_H
