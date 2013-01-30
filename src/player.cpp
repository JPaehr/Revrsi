#include "player.h"

player::player(){
    this->is_active = false;
}

player::~player(){}

void player::set_parents(QGraphicsItem *item){
    this->setParentItem(item);
    this->player_field.setParentItem(item);
    this->color.setParentItem(&this->player_field);
    this->activ_text.setParentItem(&this->player_field);
    this->name.setParentItem(&this->player_field);
    this->tokens.setParentItem(&this->player_field);
    this->kind_text.setParentItem(&this->player_field);
}

void player::setPlayerField(QPixmap pixmap){
    this->player_field.setPixmap(pixmap);
}

void player::setPlayerColor(QPixmap pixmap){
    this->color.setPixmap(pixmap);
}

void player::setActiveText(QString text){
    this->activ_text.setPlainText(text);
}

void player::setName(QString name){
    this->name.setPlainText(name);
}

void player::setActive(bool act){
    this->activ_text.setVisible(act);
    if( act ){
        this->tokens.setScale( qreal(0.8) );
        this->tokens.setPos( qreal( 20 ), qreal( 37 ));
        this->tokens.setVisible(true);
    }
}

void player::setTokens(int tokens){
    this->tokensnumber = tokens;
    QString tt;
    tt.setNum(this->tokensnumber);
    this->tokens.setPlainText(tt + " Steine");
}

void player::setTokensVisible(bool vis){
    this->tokens.setVisible(vis);
    this->tokens.setScale( 1 );
    this->tokens.setPos( 16, 23 );
}

void player::setKindText(QString text){
    this->kind_text.setPlainText(text);
}
