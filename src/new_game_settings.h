#ifndef NEW_GAME_SETTINGS_H
#define NEW_GAME_SETTINGS_H

#include <QDialog>

#include <QtGui>
#define out qDebug()

namespace Ui {
class new_game_settings;
}

class new_game_settings : public QDialog
{
    Q_OBJECT

public slots:
    void set_player_number();
    
public:
    explicit new_game_settings(QWidget *parent = 0);
    int get_choosen_number();
    ~new_game_settings();
    
private:
    Ui::new_game_settings *ui;
    int player_number;
};

#endif // NEW_GAME_SETTINGS_H
