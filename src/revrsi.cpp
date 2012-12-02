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
    this->FieldBackSet = false;
    this->height = 8;
    this->width = 8;
    this->player_num = 2;
    this->player_act = 1;
    sceneOffset_scale = 1;
    sceneOffset_x = 0;
    sceneOffset_y = 0;
    frame_scene = new QGraphicsScene(this);
    scene = new QGraphicsScene(this);
    frame_scene->setSceneRect(0,0,1000,1000);
    scene->setSceneRect(00,000,700,500);
    ui->graphicsView->setScene(scene);

    this->setupBackgroundTheme();


    this->logic = new Logic(this->width,this->width,this->player_num);
    logic->setInitStones();
    this->new_array = logic->getFields();
    this->setupBackground(this->width,this->height);
    this->init_placeTokens(logic);

    this->playerNames = ngs->get_player_names();
    this->addPlayersToList();

    // Zentriere Fenster
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    // Connections
    connect(ui->actionNeu, SIGNAL(triggered()), this, SLOT(test_slot()));
    connect(ui->actionServer, SIGNAL(triggered()), this, SLOT(server_gui_slot()));
    connect(ui->actionClient, SIGNAL(triggered()), this, SLOT(client_gui_slot()));

    connect(this, SIGNAL(win(QVector<int>)),this->winInterface, SLOT(win_slot(QVector<int>)));

    connect(ui->actionLeft,SIGNAL(triggered()),this,SLOT(step_left()));
    connect(ui->actionRight,SIGNAL(triggered()),this,SLOT(step_right()));
    connect(ui->actionTop,SIGNAL(triggered()),this,SLOT(step_top()));
    connect(ui->actionDown,SIGNAL(triggered()),this,SLOT(step_down()));
    connect(ui->actionZoom,SIGNAL(triggered()),this,SLOT(zoom_in()));
    connect(ui->actionShrink,SIGNAL(triggered()),this,SLOT(zoom_out()));
}


void Revrsi::step_left(){
    sceneOffset_x = sceneOffset_x + 10;
    scene->setSceneRect(sceneOffset_x, sceneOffset_y, scene->sceneRect().width(), scene->sceneRect().height());
}

void Revrsi::step_right(){
    sceneOffset_x = sceneOffset_x - 10;
    scene->setSceneRect(sceneOffset_x, sceneOffset_y, scene->sceneRect().width(), scene->sceneRect().height());
}

void Revrsi::step_top(){
    sceneOffset_y = sceneOffset_y + 10;
    scene->setSceneRect(sceneOffset_x, sceneOffset_y, scene->sceneRect().width(), scene->sceneRect().height());
}

void Revrsi::step_down(){
    sceneOffset_y = sceneOffset_y - 10;
    scene->setSceneRect(sceneOffset_x, sceneOffset_y, scene->sceneRect().width(), scene->sceneRect().height());
}

void Revrsi::zoom_in(){
    //sceneOffset_scale = sceneOffset_scale + 0.1;
    ui->graphicsView->scale(sceneOffset_scale+0.1,sceneOffset_scale + 0.1);
}

void Revrsi::zoom_out(){
    //sceneOffset_scale = sceneOffset_scale - 0.1;
    ui->graphicsView->scale(sceneOffset_scale - 0.1,sceneOffset_scale - 0.1);
}

Revrsi::~Revrsi(){
    delete ui;
}

/*void Revrsi::resizeEvent(QResizeEvent *){
    out << this->window()->size();
}*/

void Revrsi::test_slot(){
    this->ngs->exec();
    this->player_num = ngs->get_choosen_number();
    this->new_game();
}

void Revrsi::server_gui_slot(){
    this->serverInterface->show();
}

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
        ui->Akt_Spieler_Label->setText("Grün");
    }
    else if(this->logic->getAktPlayer() == 4){
        ui->Akt_Spieler_Label->setText("Blau");
    }

    for(int i = 1; i<=this->player_num; i++){
        if(i == logic->getAktPlayer()){
            this->p_fields[i-1]->setActive(true);
        }
        else{
            this->p_fields[i-1]->setActive(false);

        }
    }
    //this->scene->addText("Test")->setPos(100,100);
    //QLabel *t = new QLabel("\t\t\t\t\t\t\n\n\n\n\n");
    //this->scene->addWidget(t);
    //this->fields[10]->setOpacity(0.5);
    this->win_vector = logic->win();

    if(this->win_vector[0] != -1){
        QVector<int> vector_to_convert;
        for(int i = 0, size = this->win_vector.size(); i < size;i++){
            vector_to_convert.push_back(this->win_vector[i]);
        }
        this->winInterface->show();
        emit this->win(vector_to_convert);
}

}

void Revrsi::client_gui_slot(){
    this->clientInterface->show();
}

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
        if(!token_pic.load(":/Tokens/Token4.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 2){
        if(!token_pic.load(":/Tokens/Token1.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 3){
        if(!token_pic.load(":/Tokens/Token2.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 4){
        if(!token_pic.load(":/Tokens/Token3.png")){
            qWarning("Failed to load image");
        }
    }
    token_pic = token_pic.scaled(this->scale-10,this->scale-10,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

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

    //Leere das SpielerArray ohne den Vector zu löschen
    for(int i = 0; i<this->tokens.size(); i++){
        this->p_fields[i]->~player();
    }
    this->p_fields.clear();

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

    //Setup Players
    this->playerNames = ngs->get_player_names();
    this->addPlayersToList();
}

void Revrsi::placeTokens(Logic *logic){
    this->old_array = this->new_array;
    this->new_array = logic->getFields();
}

void Revrsi::setupBackground(int x, int y){
    QPixmap back_pic1;
    QPixmap back_pic2;
    if(!back_pic1.load(":/Field/feld.png")){
        qWarning("Failed to load image");
    }
    if(!back_pic2.load(":/Field/feld2.png")){
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
                if(this->FieldBackSet == false){this->setupFieldBack();this->FieldBackSet = true;}
                this->scene->addItem(item);

            }
        }
}

void Revrsi::setupToken(int x, int y, int player){
    int i = 0;
    QPixmap token_pic;

    if(player == 1){
        if(!token_pic.load(":/Tokens/Token4.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 2){
        if(!token_pic.load(":/Tokens/Token1.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 3){
        if(!token_pic.load(":/Tokens/Token2.png")){
            qWarning("Failed to load image");
        }
    }
    if(player == 4){
        if(!token_pic.load(":/Tokens/Token3.png")){
            qWarning("Failed to load image");
        }
    }

    token_pic = token_pic.scaled(this->scale-10,this->scale-10,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

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

void Revrsi::addPlayersToList(){
    //Lade den dunklen Hintergrund, auf dem die playerFelder abgebildet werden
    QPixmap hintergrund;
    if(!hintergrund.load(":/Player/PlayerFieldBackground.png")){
        qWarning("Failed to load image");
    }

    //Erstelle Container für hintergrund und lade ihn hinein
    TokenItem *player_hintergrund = new TokenItem;
    player_hintergrund->setPos(-25,0);
    player_hintergrund->setPixmap(hintergrund);
    this->scene->addItem(player_hintergrund);

    for(int i = 1; i<= this->player_num; i++){
        player *spieler = new player;

        //Bereite Alle SpielsteinBilder vor
        QPixmap token_pic;

        if(i == 1){
            if(!token_pic.load(":/Tokens/Token4.png")){
                qWarning("Failed to load image");
            }
        }
        if(i == 2){
            if(!token_pic.load(":/Tokens/Token1.png")){
                qWarning("Failed to load image");
            }
        }
        if(i == 3){
            if(!token_pic.load(":/Tokens/Token2.png")){
                qWarning("Failed to load image");
            }
        }
        if(i == 4){
            if(!token_pic.load(":/Tokens/Token3.png")){
                qWarning("Failed to load image");
            }
        }
        token_pic = token_pic.scaled(15,15);

        //Setze Parent als Referenzposition. Für jeden Spieler gleich.
        spieler->set_parents(player_hintergrund);

        //Lade und Positioniere SpielerFeld
        QPixmap PlayerField;
        if(!PlayerField.load(":/Player/PlayerField.png")){
            qWarning("Failed to load image");
        }
        spieler->player_field.setPixmap(PlayerField);
        spieler->player_field.setPos(12,i*6+(i-1)*PlayerField.height());

        spieler->setPlayerColor(token_pic);
        spieler->color.setPos(4,1);

        spieler->setName(this->playerNames[i-1]);
        spieler->name.setPos(18,-3);
        spieler->setActiveText("<<Aktiv>>");
        spieler->activ_text.setPos(11,23);
        spieler->activ_text.setVisible(false);

        this->p_fields.push_back(spieler);
    }
    this->p_fields[0]->setActive(true);

}

void Revrsi::setupBackgroundTheme(){

    QPixmap back_pic_theme;
    if(!back_pic_theme.load(":/Field/WoodenBackground.png")){
        qWarning("Failed to load image");
    }
    TokenItem *back = new TokenItem;
    back_pic_theme = back_pic_theme.scaled(1000,800, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    back->setPos(-100,-26);
    back->setPixmap(back_pic_theme);
    this->scene->addItem(back);
}

void Revrsi::setupFieldBack(){
    QPixmap field_back;
    if(!field_back.load(":/Field/FieldBackgroundShadow.png")){
        qWarning("Failed to load image");
    }
    TokenItem *fback = new TokenItem;
    field_back = field_back.scaled(this->scale*this->width+10,this->scale*this->height+10);
    fback->setPos(this->fields[0]->x_real(),this->fields[0]->y_real());
    fback->setPixmap(field_back);
    this->scene->addItem(fback);
}

/*void Revrsi::animtest(FieldItem *item)
{

}*/

void Revrsi::set_scale(double scale){
    this->scale = scale;
}

