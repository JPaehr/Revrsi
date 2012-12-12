#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <QDialog>
#include <QMessageBox>

using namespace std;

namespace Ui {
class client_gui;
}

class client_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit client_gui(QWidget *parent = 0);
    ~client_gui();

    QVector<QString> getAllNames();

signals:
    void send_startClient();
    void addPlayerS(std::vector<std::string>);
    void setLocked();

public slots:
    void startClient();
    void NetAddPlayer(QVector<QString>);
    void addPlayer(std::vector<std::string>);
    void getPlayerNameOnChange(QString);
    QString getPlayerName();
    string getIP();
    void setLockedSL();
    
private:
    Ui::client_gui *ui;
    QVector<QString> NetPlayerNames;
    int playerCounter;
    QString ownName;
    int clientCounter;
};

#endif // CLIENT_GUI_H
