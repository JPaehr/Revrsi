#ifndef FIELDITEM_H
#define FIELDITEM_H
#include <QtGui>
#include <vector>
#include <string>
#define out qDebug()

class FieldItem : public QGraphicsPixmapItem
{

public:
    FieldItem();
    void set_nr(int val);
    void set_coords(int x, int y);
    void set_realcoords(int x, int y, int w, int h);
    void set_scale(double scale);
    int x();
    int y();
    int x_real();
    int y_real();
    void ger_realcoords();
    void print_coords();
    void print_scale();
    ~FieldItem();
private:
    int nr;
    double scale;
    std::string msg;
    std::vector<int> Coords;
    QRect RealCoords;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // FIELDITEM_H
