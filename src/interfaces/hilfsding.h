#ifndef HILFSDING_H
#define HILFSDING_H

#include <QDialog>

namespace Ui {
class hilfsding;
}

class hilfsding : public QDialog
{
    Q_OBJECT
    
public:
    explicit hilfsding(QWidget *parent = 0);
    ~hilfsding();
        
public slots:
    void pb1();
    void pb2();
signals:
    void pb1s(int);
    void pb2s(int);

private:
    Ui::hilfsding *ui;
};

#endif // HILFSDING_H
