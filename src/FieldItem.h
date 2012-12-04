#ifndef FIELDITEM_H
#define FIELDITEM_H
#include <QtGui>
#include <vector>
#include <string>
#include <QObject>

class FieldItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
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

    ~FieldItem();
signals:
    void FieldClicked(int,int);
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
