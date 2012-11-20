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
    void change_field_size();
    void set_settings();
    
public:
    explicit new_game_settings(QWidget *parent = 0);

    int get_choosen_number();
    QPoint get_field_size();

    ~new_game_settings();
    
private:
    Ui::new_game_settings *ui;
    int player_number;
    int x_size;
    int y_size;
};

#endif // NEW_GAME_SETTINGS_H
