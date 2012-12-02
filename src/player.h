#ifndef PLAYER_H
#define PLAYER_H

#include <QtGui>


class player : public QGraphicsPixmapItem
{
public:
    player();
    virtual ~player();
    bool is_active;
    QGraphicsPixmapItem player_field;
    QGraphicsPixmapItem color;
    QGraphicsTextItem activ_text;
    QGraphicsTextItem name;

    void set_parents(QGraphicsItem *item);
    void setPlayerField(QPixmap pixmap);
    void setPlayerColor(QPixmap pixmap);
    void setActiveText(QString text);
    void setName(QString name);
    void setActive(bool act);
};

#endif // PLAYER_H
