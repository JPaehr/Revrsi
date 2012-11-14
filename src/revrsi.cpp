#include "revrsi.h"
#include "ui_revrsi.h"
#define out qDebug()

using namespace std;

Revrsi::Revrsi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Revrsi)
{
    ui->setupUi(this);

    out << "\n\n\nOutput:\n";

    //Zentriere Fenster
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,700,500);
    ui->graphicsView->setScene(scene);

    QPen mypen = QPen(Qt::red);

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

    //Spiel Scenario
    int x = 8;
    int y = 8;
    int player = 1;
    int pos_x = 3;
    int pos_y = 4;

    QPixmap back_pic1;
    QPixmap back_pic2;
    if(!back_pic1.load("feld.png")){
        qWarning("Failed to load image");
    }
    if(!back_pic2.load("feld2.png")){
        qWarning("Failed to load image");
    }

    QVector<FieldItem *> fields;
    this->setupBackground(x,y,scene, &fields);

    /*for(int i=1;i<fields.size();i++){
        fields[i]->print_coords();
    }*/
    fields[0]->print_scale();

    //ui->graphicsView->update();
    this->setToken(pos_x,pos_y,player,this->scale, fields, scene);
}

Revrsi::~Revrsi()
{
    delete ui;
}

void Revrsi::setupBackground(int x, int y, QGraphicsScene *scene, QVector<FieldItem *> *fields)
{
    out << scene->sceneRect();

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
                int val_y = smaller_value/y*i_y;

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

                fields->push_back(item);
                scene->addItem(item);

            }
        }
}

void Revrsi::setToken(int x, int y, int player, double scale, QVector<FieldItem *> fields, QGraphicsScene *scene)
{
    int i = 0;
    QPixmap token_pic;

    if(player == 1){
        if(!token_pic.load("token1.png")){
            qWarning("Failed to load image");
        }
    }
    token_pic = token_pic.scaled(scale-10,scale-10);

    TokenItem *token_item = new TokenItem;

    for(i = 0;i<fields.size();i++){
        if(fields[i]->x() == x && fields[i]->y() == y){
            break;
        }
    }

    token_item->setPixmap(token_pic);
    token_item->setOffset(fields[i]->x_real()+10/2,fields[i]->y_real()+10/2);
    scene->addItem(token_item);

}

void Revrsi::set_scale(double scale)
{
    this->scale = scale;
}


