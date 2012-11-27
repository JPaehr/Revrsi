#include "revrsi.h"
#include "ui_revrsi.h"
#define out qDebug()

using namespace std;

Revrsi::Revrsi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Revrsi){

    // Initialisierungsvorgänge
    ui->setupUi(this);
    ngs = new new_game_settings;
    serverInterface = new server_gui;
    clientInterface = new client_gui;
    winInterface = new win_gui;
    this->height = 4;
    this->width = 4;
    this->player_num = 2;
    this->player_act = 1;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,700,500);
    ui->graphicsView->setScene(scene);

    this->logic = new Logic(this->width,this->width,this->player_num);
    logic->setInitStones();
    this->new_array = logic->getFields();
    this->setupBackground(this->width,this->height);
    this->init_placeTokens(logic);

    // Zentriere Fenster
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    // Connections
    connect(ui->actionNeu, SIGNAL(triggered()), this, SLOT(test_slot()));
    connect(ui->actionServer, SIGNAL(triggered()), this, SLOT(server_gui_slot()));
    connect(ui->actionClient, SIGNAL(triggered()), this, SLOT(client_gui_slot()));
    connect(this, SIGNAL(win(vector<int>)), this->winInterface, SLOT(win_slot(vector<int>)));

}

Revrsi::~Revrsi(){
    delete ui;
}

void Revrsi::test_slot(){
    this->ngs->exec();
    this->player_num = ngs->get_choosen_number();
    this->new_game();
}

void Revrsi::server_gui_slot(){
    this->serverInterface->show();
}
/**************************************************/
void Revrsi::field_clicked_slot(int x, int y){
    this->logic->setField(x,y);

    this->old_array = this->new_array;
    this->new_array = this->logic->getFields();
    for(uint i = 0 ; i<this->new_array.size() ; i++){
        for(uint ii = 0 ; ii<this->new_array[i].size() ; ii++){
            if(this->new_array[i][ii] != 0 && this->old_array[i][ii] == 0){
                this->setupToken(ii,i,this->new_array[i][ii]);
            }
            else if(this->new_array[i][ii] != this->old_array[i][ii] && this->old_array[i][ii] != 0){
                this->change_token(ii,i,this->new_array[i][ii]);
            }
        }
    }
    if(this->logic->getAktPlayer() == 1){
        ui->Akt_Spieler_Label->setText("Schwarz");
    }
    else if(this->logic->getAktPlayer() == 2){
        ui->Akt_Spieler_Label->setText("Orange");
    }
    else if(this->logic->getAktPlayer() == 3){
        ui->Akt_Spieler_Label->setText("Rot");
    }
    else if(this->logic->getAktPlayer() == 4){
        ui->Akt_Spieler_Label->setText("Blau");
    }
    //this->scene->addText("Test")->setPos(100,100);
    //QLabel *t = new QLabel("\t\t\t\t\t\t\n\n\n\n\n");
    //this->scene->addWidget(t);
    //this->fields[10]->setOpacity(0.5);
    this->win_vector = logic->win();

    if(this->win_vector[0] != -1){
        out << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        for(int i = 0; i < this->win_vector.size();i++){out << this->win_vector[i];}
        this->winInterface->show();
        emit this->win(this->win_vector);
}

}

void Revrsi::client_gui_slot(){
    this->clientInterface->show();
}
/**************************************************/

void Revrsi::init_placeTokens(Logic *logic){
    this->new_array = logic->getFields();
    for(uint i = 0 ; i<this->new_array.size() ; i++){
        for(uint ii = 0 ; ii<this->new_array[i].size() ; ii++){
            if(this->new_array[i][ii]){
                this->setupToken(ii,i,this->new_array[i][ii]);
            }
        }
    }
}

void Revrsi::change_token(int x, int y, int player){
    int i = 0;
    QPixmap token_pic;

    if(player == 1){
        if(!token_pic.load("token4.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 2){
        if(!token_pic.load("token1.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 3){
        if(!token_pic.load("token2.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 4){
        if(!token_pic.load("token3.png")){
            qWarning("Failed to load image");
        }
    }
    token_pic = token_pic.scaled(this->scale-10,this->scale-10);

    TokenItem *token_item = new TokenItem;

    for(i = 0;i<this->fields.size();i++){
        if(this->fields[i]->x() == x && this->fields[i]->y() == y){
            break;
        }
    }

    token_item->setPixmap(token_pic);
    token_item->setOffset(this->fields[i]->x_real()+10/2,this->fields[i]->y_real()+10/2);
    token_item->set_coords(x,y);

    //Suche passenden Token aus Tokenliste
    int j;
    for(j = 0; j < this->tokens.size(); j++){
        if(this->tokens[j]->get_coords() == QPoint(x, y)){
            break;
        }
    }

    //Remove Old Token (muss in fkt ausgelagert werden)
    this->tokens[j]->~TokenItem();
    this->tokens.remove(j);

    this->tokens.push_back(token_item);
    this->scene->addItem(token_item);
}

void Revrsi::new_game(){
    //Zerstöre logic Funktion mit alter initialisierung
    this->logic->~Logic();

    // Leere das HintergrundFeldArray ohne den Vector zu löschen
    for(int i = 0; i<this->fields.size(); i++){
        this->fields[i]->~FieldItem();
    }
    this->fields.clear();

    // Leere das TokenArray ohne den Vector zu löschen
    for(int i = 0; i<this->tokens.size(); i++){
        this->tokens[i]->~TokenItem();
    }
    this->tokens.clear();

    // Lese neue Spieldaten
    this->player_num = ngs->get_choosen_number();
    this->width = ngs->get_field_size().x();
    this->height = ngs->get_field_size().y();

    // Erstelle neue Logicklasse
    this->logic = new Logic(this->width,this->width,this->player_num);
    logic->setInitStones();
    this->new_array = logic->getFields();

    // Setup Background und InitStones
    this->setupBackground(this->width,this->height);
    this->init_placeTokens(logic);
}

void Revrsi::placeTokens(Logic *logic){
    this->old_array = this->new_array;
    this->new_array = logic->getFields();

}

void Revrsi::setupBackground(int x, int y){
    QPixmap back_pic1;
    QPixmap back_pic2;
    if(!back_pic1.load("feld.png")){
        qWarning("Failed to load image");
    }
    if(!back_pic2.load("feld2.png")){
        qWarning("Failed to load image");
    }

    int field_counter = 0;

    for(int i_y=0;i_y<=y-1;i_y++){


            for(int i_x=0;i_x<=x-1;i_x++){
                FieldItem *item = new FieldItem;
                int offset;
                int smaller_value;

                if(scene->sceneRect().bottomRight().x()>=scene->sceneRect().bottomLeft().y()){
                    offset = (scene->sceneRect().bottomRight().x()-scene->sceneRect().bottomLeft().y())/2;
                    smaller_value = scene->sceneRect().bottomLeft().y();
                }
                else{
                    offset = (scene->sceneRect().bottomRight().y()-scene->sceneRect().bottomRight().x())/2;
                    smaller_value = scene->sceneRect().bottomLeft().x();
                }
                int val_x = smaller_value/x*i_x+offset;
                int val_y = smaller_value/x*i_y;

                back_pic1 = back_pic1.scaled(QSize(smaller_value/x,smaller_value/x));
                back_pic2 = back_pic2.scaled(QSize(smaller_value/x,smaller_value/x));

                if(i_x % 2 == 0 && i_y % 2 == 0){
                    item->setPixmap(back_pic1);
                }
                else if(i_x % 2 == 0 && i_y % 2 == 1){
                    item->setPixmap(back_pic2);
                }
                else if(i_x % 2 == 1 && i_y % 2 == 0){
                    item->setPixmap(back_pic2);
                }
                else{
                    item->setPixmap(back_pic1);
                }

                item->setOffset(val_x,val_y);

                item->set_nr(field_counter++);
                item->set_coords(i_x,i_y);
                item->set_realcoords(val_x,val_y,smaller_value/x,smaller_value/x);
                item->set_scale(smaller_value/x);
                this->set_scale(smaller_value/x);

                connect(item, SIGNAL(FieldClicked(int, int)),this, SLOT(field_clicked_slot(int, int)));

                this->fields.push_back(item);
                this->scene->addItem(item);

            }
        }
}

void Revrsi::setupToken(int x, int y, int player){
    int i = 0;
    QPixmap token_pic;

    if(player == 1){
        if(!token_pic.load("token4.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 2){
        if(!token_pic.load("token1.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 3){
        if(!token_pic.load("token2.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 4){
        if(!token_pic.load("token3.png")){
            qWarning("Failed to load image");
        }
    }
    token_pic = token_pic.scaled(this->scale-10,this->scale-10);

    TokenItem *token_item = new TokenItem;

    for(i = 0;i<this->fields.size();i++){
        if(this->fields[i]->x() == x && this->fields[i]->y() == y){
            break;
        }
    }

    token_item->setPixmap(token_pic);
    token_item->setOffset(this->fields[i]->x_real()+10/2,this->fields[i]->y_real()+10/2);
    token_item->set_coords(x,y);
    this->tokens.push_back(token_item);
    this->scene->addItem(token_item);
}

/*void Revrsi::animtest(FieldItem *item)
{

}*/

void Revrsi::set_scale(double scale){
    this->scale = scale;
}


