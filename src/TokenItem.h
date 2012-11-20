#ifndef TOKENITEM_H
#define TOKENITEM_H

#include <QtGui>
#define out qDebug()

class TokenItem : public QGraphicsPixmapItem
{
public:
    TokenItem();
    void set_coords(int x, int y);
    QPoint get_coords();

    ~TokenItem();
private:
    int x;
    int y;
};

#endif // TOKENITEM_H
