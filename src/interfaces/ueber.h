#ifndef UEBER_H
#define UEBER_H

#include <QDialog>

namespace Ui {
class ueber;
}

class ueber : public QDialog
{
    Q_OBJECT
    
public:
    explicit ueber(QWidget *parent = 0);
    ~ueber();
    
private:
    Ui::ueber *ui;
};

#endif // UEBER_H
