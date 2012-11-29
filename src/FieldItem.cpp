#include "FieldItem.h"

FieldItem::FieldItem(){
}

void FieldItem::set_nr(int val){
    nr = val;
}

void FieldItem::set_coords(int x, int y){
    Coords.resize(1);
    Coords[0] = x;
    Coords[1] = y;
}

void FieldItem::set_realcoords(int x, int y, int w, int h){
    RealCoords.setRect(x,y,w,h);
}

void FieldItem::set_scale(double scale){
    this->scale = scale;
}

void FieldItem::set_hb(int hb){
    this->hb = hb;
}

int FieldItem::x(){
    return this->Coords[0];
}

int FieldItem::y(){
    return this->Coords[1];
}

int FieldItem::x_real(){
    return this->RealCoords.x();
}

int FieldItem::y_real(){
    return this->RealCoords.y();
}

FieldItem::~FieldItem(){
}

void FieldItem::mousePressEvent(QGraphicsSceneMouseEvent *){ //void FieldItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
    emit FieldClicked(this->x(),this->y());
}
