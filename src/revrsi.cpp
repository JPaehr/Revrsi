#include "revrsi.h"
#include "ui_revrsi.h"
#define out qDebug()

using namespace std;

Revrsi::Revrsi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Revrsi)
{
    // Initialisierungsvorgänge
    ui->setupUi(this);
    settings *s = new settings;
    this->height = s->get_x();
    this->width = s->get_y();
    this->player_num = 2;
    this->player_act = 1;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,700,500);
    ui->graphicsView->setScene(scene);

    // Zentriere Fenster
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    out << "\n\n\nOutput:\n---------------";
    out << this->height;
    out << this->width;

    // Connections
    connect(ui->actionOptionen, SIGNAL(triggered()),s,SLOT(show()));

    //Setup Logic
    Logic *logic = new Logic(this->width-1,this->height-1,this->player_num);
    logic->setInitStones();
    this->new_array = logic->getFields();

    // Setup Spielfeld
    this->setupBackground(this->width,this->height);
    this->init_placeTokens(logic);

    /*QPen mypen = QPen(Qt::red);

    QPoint point1;
    point1 = QPoint(10,10);
    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    //QLineF TopLine(QPoint(00,600), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    out << "TopLeft:\t\t" << scene->sceneRect().topLeft();
    out << "TopRight:\t\t"<< scene->sceneRect().topRight();
    out << "BottomLeft:\t\t"<<scene->sceneRect().bottomLeft();
    out << "BottomRight:\t"<<scene->sceneRect().bottomRight();

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(BottomLine,mypen);
    */

    //ui->graphicsView->update();
    //this->new_game(logic);
}

Revrsi::~Revrsi()
{
    delete ui;
}

void Revrsi::init_placeTokens(Logic *logic){
    this->new_array = logic->getFields();
    for(int i = 0 ; i<this->new_array.size() ; i++){
        for(int ii = 0 ; ii<this->new_array[i].size() ; ii++){
            //out << "(" << i << "," <<  this->new_array[i][ii] << ")";
            if(this->new_array[i][ii]){
                this->setupToken(i,ii,this->new_array[i][ii]);
            }
        }

    }
    //out << this->new_array[2].size();
}

void Revrsi::new_game(Logic *logic){
    logic->~Logic();
    for(int i = 0; i<this->fields.size(); i++){
        this->fields[i]->~FieldItem();
    }
    this->fields.clear();
    for(int i = 0; i<this->tokens.size(); i++){
        this->tokens[i]->~TokenItem();
    }
    this->tokens.clear();


}

void Revrsi::placeTokens(Logic *logic){
    this->old_array = this->new_array;
    this->new_array = logic->getFields();

}

void Revrsi::setupBackground(int x, int y)
{
    //out << scene->sceneRect();

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

                this->fields.push_back(item);
                this->scene->addItem(item);

            }
        }
}

void Revrsi::setupToken(int x, int y, int player)
{
    int i = 0;
    QPixmap token_pic;

    if(player == 1){
        if(!token_pic.load("logo.png")){
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
    this->tokens.push_back(token_item);
    this->scene->addItem(token_item);

}

void Revrsi::set_scale(double scale)
{
    this->scale = scale;
}


