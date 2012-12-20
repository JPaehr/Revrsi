#ifndef AI_SETTINGS_H
#define AI_SETTINGS_H

#include <QDialog>

namespace Ui {
class AI_settings;
}

class AI_settings : public QDialog
{
    Q_OBJECT
    
public:
    explicit AI_settings(QWidget *parent = 0);
    ~AI_settings();
    bool aiActivated(int ki_number);
    
private:
    Ui::AI_settings *ui;
};

#endif // AI_SETTINGS_H
