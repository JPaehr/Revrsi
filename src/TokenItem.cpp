#include "TokenItem.h"

TokenItem::TokenItem(){
}

void TokenItem::set_coords(int x, int y){
    this->x = x;
    this->y = y;
}

QPoint TokenItem::get_coords(){
    return QPoint(this->x, this->y);
}

TokenItem::~TokenItem(){
}
