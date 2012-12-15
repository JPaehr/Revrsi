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
    QGraphicsTextItem tokens;
    QGraphicsTextItem kind_text;

    void set_parents(QGraphicsItem *item);
    void setPlayerField(QPixmap pixmap);
    void setPlayerColor(QPixmap pixmap);
    void setActiveText(QString text);
    void setName(QString name);
    void setActive(bool act);
    void setTokens(int tokens);
    void setTokensVisible(bool vis);
    void setKindText(QString text);
private:
    int tokensnumber;
};

#endif // PLAYER_H
