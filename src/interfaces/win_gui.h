#ifndef WIN_GUI_H
#define WIN_GUI_H

#include <QDialog>
#include <vector>

namespace Ui {
class win_gui;
}

class win_gui : public QDialog
{
    Q_OBJECT
public slots:
    void win_slot(QVector<int>);
public:
    explicit win_gui(QWidget *parent = 0);
    ~win_gui();
    
private:
    Ui::win_gui *ui;

    QVector<int> win_vector;
};

#endif // WIN_GUI_H
