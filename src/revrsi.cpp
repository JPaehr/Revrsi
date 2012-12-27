#include "revrsi.h"
#include "ui_revrsi.h"
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;

Revrsi::Revrsi( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::Revrsi ){
    ui->setupUi( this );

    // Init Windows
    this->ais             = new AI_settings( this );
    this->ngs             = new new_game_settings( this );
    this->serverInterface = new server_gui( this );
    this->clientInterface = new client_gui( this );
    this->winInterface    = new win_gui( this );

    // Init GraphicsScene
    this->frame_scene = new QGraphicsScene( this );
    this->scene       = new QGraphicsScene( this );

    this->frame_scene->setSceneRect( 0,0,1000,1000 );
    this->scene->setSceneRect( 00,000,700,500 );
    ui->graphicsView->setScene( scene );

    this->sceneOffset_scale   = 1;
    this->sceneOffset_x       = 0;
    this->sceneOffset_y       = 0;

    //Init FieldSpecs
    this->height        = 8;
    this->width         = 8;
    this->player_num    = 2;
    this->player_act    = 1;


    //Init Booleans
    this->animatedPlayer= 0;
    this->direction     = 1;
    this->FieldBackSet  = false;
    this->firstRun      = true;
    this->NetGameStart  = false;
    this->NetMode       = false;
    this->clientInit    = false;
    this->serverInit    = false;
    this->serverMode    = false;
    this->skipTurn      = false;

    //Do the Rest
    this->setupBackgroundTheme(  );

    //Init Logic here is mandatory
    this->logic = new Logic( this->width,this->width,this->player_num );
    this->logic->setInitStones(  );
    this->new_array = logic->getFields(  );

    this->DelayedAnimationThread(  );

    // Zentriere Fenster
    QRect frect = frameGeometry(  );
    frect.moveCenter( QDesktopWidget(  ).availableGeometry(  ).center(  ) );
    move( frect.topLeft(  ) );

    // Connections
    // Connect Menu Items
    connect( ui->actionNeu,              SIGNAL( triggered(  ) ), this,      SLOT( new_game_slot(  ) ) );
    connect( ui->actionServer,           SIGNAL( triggered(  ) ), this,      SLOT( server_gui_slot(  ) ) );
    connect( ui->actionClient,           SIGNAL( triggered(  ) ), this,      SLOT( client_gui_slot(  ) ) );
    connect( ui->actionClient,           SIGNAL( triggered(  ) ), this,      SLOT( setNetModeEnabled(  ) ) );
    connect( ui->actionKI_Einstellungen, SIGNAL( triggered(  ) ), this->ais, SLOT( show(  ) ) );

    // Connect Toolbar Items
    connect( ui->actionLeft,     SIGNAL( triggered(  ) ), this, SLOT( step_left(  ) ) );
    connect( ui->actionRight,    SIGNAL( triggered(  ) ), this, SLOT( step_right(  ) ) );
    connect( ui->actionTop,      SIGNAL( triggered(  ) ), this, SLOT( step_top(  ) ) );
    connect( ui->actionDown,     SIGNAL( triggered(  ) ), this, SLOT( step_down(  ) ) );
    connect( ui->actionZoom,     SIGNAL( triggered(  ) ), this, SLOT( zoom_in(  ) ) );
    connect( ui->actionShrink,   SIGNAL( triggered(  ) ), this, SLOT( zoom_out(  ) ) );

    // Connect Delayed Animation Start
    //connect( this->atest, SIGNAL( delayedStart(  ) ), this, SLOT( warpStart(  ) ) );

    // Connect Win Vector
    connect( this, SIGNAL( win( QVector<int>, QVector<QString> ) ),this->winInterface, SLOT( win_slot( QVector<int>, QVector<QString> ) ) );

    // Connect Network
    connect( this->serverInterface, SIGNAL( startServer(  ) ),      this, SLOT( runServer(  ) ) );
    connect( this->clientInterface, SIGNAL( send_startClient(  ) ), this, SLOT( runClient(  ) ) );
    connect( this->clientInterface, SIGNAL( destroyed(  ) ),        this, SLOT( setNetModeDisabled(  ) ) ); //###Check

    this->new_game();
}

Revrsi::~Revrsi(  ){
    delete ui;
}

void Revrsi::addPlayersToList(  ){
    //Lade den dunklen Hintergrund, auf dem die playerFelder abgebildet werden
    QPixmap hintergrund;
    if( !hintergrund.load( ":/Player/PlayerFieldBackground.png" ) ){
        qWarning( "Failed to load image" );
    }

    //Erstelle Container für hintergrund und lade ihn hinein
    TokenItem *player_hintergrund   = new TokenItem;
    this->TokenContainer            = player_hintergrund;
    player_hintergrund->setPos( -25, 0 );
    player_hintergrund->setPixmap( hintergrund );
    this->scene->addItem( player_hintergrund );

    for( int i = 1; i <= this->player_num; i++ ){
        player *spieler = new player;

        //Bereite Alle SpielsteinBilder vor
        QPixmap token_pic;

        if( i == 1 ){
            if( !token_pic.load( ":/Tokens/Token4.png" ) ){
                qWarning( "Failed to load image" );
            }
        }
        if( i == 2 ){
            if( !token_pic.load( ":/Tokens/Token1.png" ) ){
                qWarning( "Failed to load image" );
            }
        }
        if( i == 3 ){
            if( !token_pic.load( ":/Tokens/Token2.png" ) ){
                qWarning( "Failed to load image" );
            }
        }
        if( i == 4 ){
            if( !token_pic.load( ":/Tokens/Token3.png" ) ){
                qWarning( "Failed to load image" );
            }
        }
        token_pic = token_pic.scaled( 15, 15 );

        //Setze Parent als Referenzposition. Für jeden Spieler gleich.
        spieler->set_parents( player_hintergrund );

        //Lade und Positioniere SpielerFeld
        QPixmap PlayerField;
        if( !PlayerField.load( ":/Player/PlayerField.png" ) ){
            qWarning( "Failed to load image" );
        }
        spieler->player_field.setPixmap( PlayerField );
        spieler->player_field.setPos( 12, i * 6 + ( i - 1 ) * PlayerField.height(  ) );

        spieler->setPlayerColor( token_pic );
        spieler->color.setPos( 4, 1 );

        spieler->setName( this->playerNames[i-1] );
        spieler->name.setPos( 18, -3 );
        spieler->setActiveText( "<<Aktiv>>" );
        spieler->activ_text.setPos( 11, 23 );
        spieler->activ_text.setVisible( false );
        spieler->tokens.setPos( 16, 23 );
        if( this->ais->aiActivated( i ) ){
            spieler->setKindText( "<<KI>>" );
            spieler->kind_text.setPos( 23, 15 );
            spieler->kind_text.setScale( qreal(0.8) );
        }

        if     ( this->player_num == 2 ){ spieler->setTokens( 2 ); }
        else if( this->player_num == 3 ){ spieler->setTokens( 3 ); }
        else if( this->player_num == 4 ){ spieler->setTokens( 4 ); }

        if( i == 1 ){ spieler->setTokensVisible( false ); }
        else{ spieler->setTokensVisible( true ); }

        this->p_fields.push_back( spieler );
    }
    this->p_fields[0]->setActive( true );

}

void Revrsi::AIClickSlot( int x, int y ){
    field_clicked_slot( x, y );
}

void Revrsi::change_token( int x, int y, int player ){
    int i = 0;
    QPixmap token_pic;

    if( player == 1 ){
        if( !token_pic.load( ":/Tokens/Token4.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    if( player == 2 ){
        if( !token_pic.load( ":/Tokens/Token1.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    if( player == 3 ){
        if( !token_pic.load( ":/Tokens/Token2.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    if( player == 4 ){
        if( !token_pic.load( ":/Tokens/Token3.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    token_pic = token_pic.scaled( this->scale-10, this->scale-10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    TokenItem *token_item = new TokenItem;

    for( i = 0; i < this->fields.size(  ) ; i++ ){
        if( this->fields[i]->x(  ) == x && this->fields[i]->y(  ) == y ){
            break;
        }
    }

    token_item->setPixmap( token_pic );
    token_item->setOffset( this->fields[i]->x_real(  ) + 10/2, this->fields[i]->y_real(  ) + 10/2 );
    token_item->set_coords( x, y );

    //Suche passenden Token aus Tokenliste
    int j;
    for( j = 0; j < this->tokens.size(  ); j++ ){
        if( this->tokens[j]->get_coords(  ) == QPoint( x, y ) ){
            break;
        }
    }

    //Remove Old Token
    this->tokens[j]->~TokenItem(  );
    this->tokens.remove( j );

    //Add New Token
    this->tokens.push_back( token_item );
    this->scene->addItem( token_item );
}

void Revrsi::client_gui_slot(  ){
    this->clientInterface->show(  );
}

void Revrsi::closeEvent( QCloseEvent * ){
    atest->terminate(  );
    atest->wait(  );
    if( this->clientInit ){
        this->ClientThread->terminateClient(  );
    }
    if( this->serverInit ){
        this->ServerThread->NetStopServer(  );
    }
    this->close(  );
}

void Revrsi::createAIs(  ){
    for( int i = 1; i <= this->player_num; i++ ){
        if( this->ais->aiActivated( i ) ){
            AI_Thread *ai = new AI_Thread( this, 1 ,i );
            connect( this,  SIGNAL( emitField( vector<vector<int> > ) ), ai,     SLOT( setField( vector<vector<int> > ) ) );
            connect( ai,    SIGNAL( AIClicked( int, int ) ),             this,   SLOT( AIClickSlot( int,int ) ) );
            connect( this,  SIGNAL( emitAktPlayer( int ) ),              ai,     SLOT( setAktPlayer( int ) ) );
            this->ai_list.push_back( ai );
            ai->start(  );
        }
    }
}

void Revrsi::DelayedAnimationThread(  ){
    this->atest = new anim_test( this );
    atest->start(  );
}

void Revrsi::field_clicked_slot( int x, int y ){
    if( NetMode ){
        emit this->NetFieldClickedTransmit( x, y );
        return;
    }
    this->logic->setField( x, y );
    this->old_array = this->new_array;
    this->new_array = this->logic->getFields(  );
    for( uint i = 0; i<this->new_array.size(  ); i++ ){
        for( uint ii = 0; ii<this->new_array[i].size(  ); ii++ ){
            if( this->new_array[i][ii] != 0 && this->old_array[i][ii] == 0 ){
                this->setupToken( ii, i, this->new_array[i][ii] );
            }
            else if( this->new_array[i][ii] != this->old_array[i][ii] && this->old_array[i][ii] != 0 ){
                this->change_token( ii ,i, this->new_array[i][ii] );
            }
        }
    }
    if( this->logic->getAktPlayer(  ) == 1 ){
        ui->Akt_Spieler_Label->setText( "Schwarz" );
    }
    else if( this->logic->getAktPlayer(  ) == 2 ){
        ui->Akt_Spieler_Label->setText( "Orange" );
    }
    else if( this->logic->getAktPlayer(  ) == 3 ){
        ui->Akt_Spieler_Label->setText( "Grün" );  //###Check
    }
    else if( this->logic->getAktPlayer(  ) == 4 ){
        ui->Akt_Spieler_Label->setText( "Blau" );
    }

    for( int i = 1; i <= this->player_num; i++ ){
        if( i == logic->getAktPlayer(  ) ){
            this->p_fields[i-1]->setTokensVisible( false );
            this->p_fields[i-1]->setActive( true );
        }
        else{
            this->p_fields[i-1]->setActive( false );
            this->p_fields[i-1]->setTokensVisible( true );
        }
    }

    this->win_vector = logic->win(  );
    p_fields[0]->setTokens( this->win_vector[1] );
    p_fields[1]->setTokens( this->win_vector[2] );
    if( this->player_num == 3 ){
        p_fields[2]->setTokens( this->win_vector[3] );
    }
    if( this->player_num == 4 ){
        p_fields[3]->setTokens( this->win_vector[4] );
    }
    if( this->win_vector[0] != -1 ){
        if(this->skipTurn){
            return;
        }
        QVector<int> vector_to_convert;
        for( int i = 0, size = this->win_vector.size(  ); i < size; i++ ){ //###uint fix
            vector_to_convert.push_back( this->win_vector[i] );
        }
        this->winInterface->show(  );
        emit this->win( vector_to_convert, this->playerNames );
        this->skipTurn = true;
    }

    if( logic->getAktPlayer(  )-1 != this->animatedPlayer ){
        this->anim->setLoopCount( 0 );
        this->animatedPlayer = logic->getAktPlayer(  )-1;
        this->runPlayerFieldAnimation(  );
        connect( this->anim, SIGNAL( finished(  ) ), this, SLOT( switchOpacityWay(  ) ) );
    }
    emit emitAktPlayer( this->logic->getAktPlayer(  ) );
    emit emitField( this->logic->getFields(  ) );
}

void Revrsi::init_placeTokens(  ){
    if( !this->NetMode ){
        this->new_array = this->logic->getFields(  );
    }
    for( uint i = 0; i < this->new_array.size(  ); i++ ){
        for( uint ii = 0; ii < this->new_array[i].size(  ) ; ii++ ){
            if( this->new_array[i][ii] ){
                this->setupToken( ii, i, this->new_array[i][ii] );
            }
        }
    }
}

void Revrsi::new_game(  ){
    //Beende Animation
    if( !this->firstRun ){
        this->anim->setLoopCount( 0 );
    }

    //Zerstöre logic Funktion mit alter initialisierung
    this->logic->~Logic(  );

    // Leere das HintergrundFeldArray ohne den Vector zu löschen
    for( int i = 0; i < this->fields.size(  ); i++ ){
        this->fields[i]->~FieldItem(  );
    }
    this->fields.clear(  );

    // Leere das TokenArray ohne den Vector zu löschen
    for( int i = 0; i < this->tokens.size(  ); i++ ){
        this->tokens[i]->~TokenItem(  );
    }
    this->tokens.clear(  );

    //Leere das SpielerArray ohne den Vector zu löschen
    for( int i = 0; i < this->p_fields.size(  ); i++ ){
        this->p_fields[i]->~player(  );
    }
    this->p_fields.clear(  );

    //Leere das KIArray ohne den Vector zu löschen
    for( int i = 0; i < this->ai_list.size(  ); i++ ){
        if(this->ai_list[i]->isRunning()){
            this->ai_list[i]->terminate();
            //this->ai_list[i]->wait();
            this->ai_list[i]->~AI_Thread();
        }
        else{this->ai_list[i]->~AI_Thread();}
    }
    this->ai_list.clear(  );

    if( !this->firstRun ){
        this->TokenContainer->~TokenItem(  );
    }
    this->skipTurn = false;

    // Lese neue Spieldaten
    if( !this->firstRun && !this->NetMode ){
        this->player_num    = ngs->get_choosen_number(  );
        this->width         = ngs->get_field_size(  ).x(  );
        this->height        = ngs->get_field_size(  ).y(  );
    }

    // Erstelle neue Logicklasse
    if( !this->NetMode ){
        this->logic = new Logic( this->width,this->width,this->player_num );
        logic->setInitStones(  );
        this->new_array = logic->getFields(  );
    }

    //Setup Players
    if( !this->NetMode ){
        this->playerNames = ngs->get_player_names(  );
        this->logic->getAktPlayer(  );
        this->createAIs(  );
    }
    else{
        if( !serverMode ){
            this->playerNames = this->clientInterface->getAllNames(  );
        }
        else{
            this->playerNames = this->serverInterface->getAllNames(  );
        }
    }

    // Setup Background und InitStones
    this->setupBackground( this->width,this->height );
    this->init_placeTokens(  );

    //Transmit Field to AI
    if( !NetMode ){
        emit this->emitField( this->logic->getFields(  ) );
        emit this->emitAktPlayer( this->logic->getAktPlayer(  ) );
    }
    this->addPlayersToList(  );

    //Run Animation
    this->runPlayerFieldAnimation(  );
    connect( this->anim, SIGNAL( finished(  ) ), this, SLOT( switchOpacityWay(  ) ) );

    //Set First Run
    this->firstRun = false;
}

void Revrsi::new_game_slot(  ){
    this->ngs->exec(  );
    this->player_num = ngs->get_choosen_number(  );
    this->new_game(  );
}

void Revrsi::NetCreateConnectsSL(  ){
    connect( this,                          SIGNAL( NetFieldClickedTransmit( int, int ) ),  this->ClientThread, SLOT( NetFieldClicked( int, int ) ) );
    connect( this->ClientThread,            SIGNAL( NetNewFields(  ) ),                     this,               SLOT( NetNewFieldSL(  ) ) );
    connect( this->ClientThread,            SIGNAL( NetClientSendName( QString ) ),         this->ClientThread, SLOT( NetSendName( QString ) ) );
    connect( this->ClientThread->myClient,  SIGNAL( NetNewField(  ) ),                      this->ClientThread, SLOT( NetGetNewField(  ) ) );
    connect( this->ClientThread->myClient,  SIGNAL( NetServerWantGameStart(  ) ),           this,               SLOT( NetNewGame(  ) ) );
    connect( this->ClientThread->myClient,  SIGNAL( NetWinVector( QVector<int> ) ),         this,               SLOT( NetUpdateWinVector( QVector<int> ) ) );
    connect( this->ClientThread->myClient,  SIGNAL( NetAktPlayer( int ) ),                  this,               SLOT( NetUpdatePlayer( int ) ) );
    connect( this->ClientThread->myClient,  SIGNAL( NetGotID( int ) ),                      this->ClientThread, SLOT( NetGetID( int ) ) );
    connect( this->ClientThread->myClient,  SIGNAL( NetGameValues( int, int, int ) ),       this,               SLOT( NetSetGameValues( int, int, int ) ) );
    if( !serverMode ){
        connect( this->ClientThread->myClient, SIGNAL( NetPlayersNames( QVector<QString> ) ), this->clientInterface, SLOT( NetAddPlayer( QVector<QString> ) ) );
    }
    else{
        connect( this->ClientThread->myClient, SIGNAL( NetPlayersNames( QVector<QString> ) ), this->serverInterface, SLOT( NetAddPlayerServer( QVector<QString> ) ) );
    }
    this->ClientThread->setCreateConnectsState( true );
}

//Funktion die nach einem Click ausgeführt wird. Um neue Felder zu setzen
void Revrsi::NetNewFieldSL(  ){
    this->old_array = this->new_array;
    this->new_array = this->ClientThread->getFields(  );

    if( this->NetGameStart ){
        for( uint i = 0; i < this->new_array.size(  ); i++ ){
            for( uint ii = 0; ii < this->new_array[i].size(  ); ii++ ){
                if( this->new_array[i][ii] != 0 && this->old_array[i][ii] == 0 ){
                    this->setupToken( ii, i, this->new_array[i][ii] );
                }
                else if( this->new_array[i][ii] != this->old_array[i][ii] && this->old_array[i][ii] != 0 ){
                    this->change_token( ii, i, this->new_array[i][ii] );
                }
            }
        }
    }
}

void Revrsi::NetNewGame(  ){
    this->NetGameStart = true;
    if( !serverMode ){
        this->clientInterface->hide(  );
    }
    this->new_game(  );
}

void Revrsi::NetUpdatePlayer( int NetAktPlayer ){
    if( NetGameStart ){
        if( NetAktPlayer == 1 ){
            ui->Akt_Spieler_Label->setText( "Schwarz" );
        }
        else if( NetAktPlayer == 2 ){
            ui->Akt_Spieler_Label->setText( "Orange" );
        }
        else if( NetAktPlayer == 3 ){
            ui->Akt_Spieler_Label->setText( "Grün" ); //###Check
        }
        else if( NetAktPlayer == 4 ){
            ui->Akt_Spieler_Label->setText( "Blau" );
        }

        for( int i = 1; i <= this->player_num; i++ ){
            if( i == NetAktPlayer ){
                this->p_fields[i-1]->setActive( true );
                this->p_fields[i-1]->setTokensVisible( false );
            }
            else{
                this->p_fields[i-1]->setActive( false );
                this->p_fields[i-1]->setTokensVisible( true );
            }
        }
        if( NetAktPlayer-1 != this->animatedPlayer ){
            this->anim->setLoopCount( 0 );
            this->animatedPlayer = NetAktPlayer-1;
            this->runPlayerFieldAnimation(  );
            connect( this->anim,SIGNAL( finished(  ) ), this, SLOT( switchOpacityWay(  ) ) );
        }
    }
}

void Revrsi::NetSetGameValues( int width, int height, int player_num ){
    this->width = width;
    this->height = height;
    this->player_num = player_num;
}

void Revrsi::NetUpdateWinVector( QVector<int> WinVector ){
    if( WinVector[0] != -1 ){
        this->winInterface->show(  );
        emit this->win( WinVector, this->playerNames );
    }
    else{
        p_fields[0]->setTokens( WinVector[1] );
        p_fields[1]->setTokens( WinVector[2] );
        if( this->player_num == 3 ){
            p_fields[2]->setTokens( WinVector[3] );
        }
        if( this->player_num == 4 ){
            p_fields[3]->setTokens( WinVector[4] );
        }
    }
}

void Revrsi::runClient( QString ip, QString Name ){
    this->NetMode = true;
    if( !serverMode ){
        if( this->clientInit ){
            this->ClientThread->terminate(  );
        }
        this->ClientThread = new client_thread( this, this->clientInterface );
    }
    else{
        if( this->clientInit ){
            this->ClientThread->terminate(  );
        }
        this->ClientThread = new client_thread( this, this->serverInterface, ip.toStdString(  ), Name );
    }
    this->clientInit = true;

    connect( this->ClientThread,SIGNAL( NetCreateConnects(  ) ), this, SLOT( NetCreateConnectsSL(  ) ) );

    this->ClientThread->start(  );
}

void Revrsi::runPlayerFieldAnimation(  ){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
    this->p_fields[this->animatedPlayer]->player_field.setGraphicsEffect( effect );
    this->anim = new QPropertyAnimation( effect, "opacity" );
    anim->setDirection( QAbstractAnimation::Forward );
    this->direction = 1;
    anim->setStartValue( 0.5 );
    anim->setEndValue( 1 );
    anim->setDuration( 1200 );
    anim->setEasingCurve( QEasingCurve::InOutQuad );
    anim->start( QAbstractAnimation::KeepWhenStopped );
}

void Revrsi::runServer(  ){
    this->NetMode       = true;
    this->serverMode    = true;
    this->ServerThread  = new server_thread( this, this->serverInterface );

    connect( this->ServerThread, SIGNAL( NetStartServersClient( QString, QString ) ), this, SLOT( runClient( QString, QString ) ) );

    this->ServerThread->start(  );
    this->serverInit = true;

    connect( this->serverInterface,SIGNAL( NetStartGame(  ) ),this->ServerThread,SLOT( NetServerStartGame(  ) ) );
}

void Revrsi::server_gui_slot(  ){
    this->serverInterface->show(  );
}

void Revrsi::setNetModeEnabled(  ){
    this->NetMode = true;
}

void Revrsi::setNetModeDisabled(  ){
    this->NetMode = false;
}

void Revrsi::set_scale( double scale ){
    this->scale = scale;
}

void Revrsi::setupBackground( int x, int y ){
    QPixmap back_pic1;
    QPixmap back_pic2;

    if( !back_pic1.load( ":/Field/feld.png" ) ){
        qWarning( "Failed to load image" );
    }
    if( !back_pic2.load( ":/Field/feld2.png" ) ){
        qWarning( "Failed to load image" );
    }

    int field_counter = 0;

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    QVector<QGraphicsItemAnimation *> an_group;
    //QVector<QTimeLine *> t_group;
    for(int i = 0; i< this->t_group.size(); i++){
        this->t_group[i]->~QTimeLine();
    }
    this->t_group.clear();

    for( int i_y = 0; i_y <= y-1; i_y++ ){
        for( int i_x=0; i_x <= x-1; i_x++ ){
            FieldItem *item = new FieldItem;
            int offset;
            int smaller_value;

            if( scene->sceneRect(  ).bottomRight(  ).x(  ) >= scene->sceneRect(  ).bottomLeft(  ).y(  ) ){
                offset = ( scene->sceneRect(  ).bottomRight(  ).x(  ) - scene->sceneRect(  ).bottomLeft(  ).y(  ) ) /2;
                smaller_value = scene->sceneRect(  ).bottomLeft(  ).y(  );
            }
            else{
                offset = ( scene->sceneRect(  ).bottomRight(  ).y(  ) - scene->sceneRect(  ).bottomRight(  ).x(  ) ) /2;
                smaller_value = scene->sceneRect(  ).bottomLeft(  ).x(  );
            }
            int val_x = smaller_value/x*i_x+offset;
            int val_y = smaller_value/x*i_y;

            back_pic1 = back_pic1.scaled( QSize( smaller_value/x,smaller_value/x ) );
            back_pic2 = back_pic2.scaled( QSize( smaller_value/x,smaller_value/x ) );

            if( i_x % 2 == 0 && i_y % 2 == 0 ){
                item->setPixmap( back_pic1 );
            }
            else if( i_x % 2 == 0 && i_y % 2 == 1 ){
               item->setPixmap( back_pic2 );
            }
            else if( i_x % 2 == 1 && i_y % 2 == 0 ){
               item->setPixmap( back_pic2 );
            }
            else{
               item->setPixmap( back_pic1 );
            }

            item->set_nr( field_counter++ );
            item->set_coords( i_x, i_y );
            item->set_realcoords( val_x, val_y, smaller_value/x, smaller_value/x );//###fix
            //item->set_realcoords(0,0,0,0);
            item->set_scale( smaller_value/x );
            this->set_scale( smaller_value/x );

            connect( item, SIGNAL( FieldClicked( int, int ) ), this, SLOT( field_clicked_slot( int, int ) ) );

            this->fields.push_back( item );
            if( !this->FieldBackSet ){
                this->setupFieldBack(  );
                this->FieldBackSet = true;
            }
            this->scene->addItem( item );


            QGraphicsItemAnimation *an = new QGraphicsItemAnimation;
            QTimeLine *timer = new QTimeLine(1000);
            timer->setFrameRange(0, 100);
            an->setItem(item);
            an->setTimeLine(timer);

            /*for(float i = 26; i >= 1; i--){
                an->setPosAt((250-i*10.f) / 250.f, QPointF(val_x*(1/i), val_y*cos(2*M_PI*(0.01*i-1))));
                //cout << "1/i: " << 1/i << endl;
                //cout << "val x: "  << val_x << " val y: " << val_y << " x: " << val_x*(1/i)<< " y: " << val_y*cos(2*M_PI*(0.01*i-1)) << endl;
            }*/

            an->setPosAt(0.f / 250.f, QPointF(val_x*0, 0.00001*val_y));
            an->setPosAt(249.f / 250.f, QPointF(val_x, val_y));
            an_group.push_back(an);
            t_group.push_back(timer);
        }
    }
    group->start(  );
    this->atest->setTimerGroup(t_group);
    this->atest->start();
}

void Revrsi::setupBackgroundTheme(  ){
    QPixmap back_pic_theme;
    if( !back_pic_theme.load( ":/Field/WoodenBackground.png" ) ){
        qWarning( "Failed to load image" );
    }
    TokenItem *back = new TokenItem;
    back_pic_theme = back_pic_theme.scaled( 1000, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    back->setPos( -100, -26 );
    back->setPixmap( back_pic_theme );
    this->scene->addItem( back );
}

void Revrsi::setupFieldBack(  ){
    QPixmap field_back;
    if( !field_back.load( ":/Field/FieldBackgroundShadow.png" ) ){
        qWarning( "Failed to load image" );
    }
    TokenItem *fback = new TokenItem;
    field_back = field_back.scaled( this->scale * this->width + 10, this->scale * this->height + 10 );
    fback->setPos( this->fields[0]->x_real(  ), this->fields[0]->y_real(  ) );
    fback->setPixmap( field_back );
    fback->setOpacity( 0.75 );
    this->scene->addItem( fback );
}

void Revrsi::setupToken( int x, int y, int player ){
    int i = 0;
    QPixmap token_pic;

    if( player == 1 ){
        if( !token_pic.load( ":/Tokens/Token4.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    if( player == 2 ){
        if( !token_pic.load( ":/Tokens/Token1.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    if( player == 3 ){
        if( !token_pic.load( ":/Tokens/Token2.png" ) ){
            qWarning( "Failed to load image" );
        }
    }
    if( player == 4 ){
        if( !token_pic.load( ":/Tokens/Token3.png" ) ){
            qWarning( "Failed to load image" );
        }
    }

    token_pic = token_pic.scaled( this->scale-10, this->scale-10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    TokenItem *token_item = new TokenItem;

    for( i = 0; i < this->fields.size(  ); i++ ){
        if( this->fields[i]->x(  ) == x && this->fields[i]->y(  ) == y ){
            break;
        }
    }

    token_item->setPixmap( token_pic );
    token_item->setOffset( this->fields[i]->x_real(  ) + 10 / 2, this->fields[i]->y_real(  ) + 10 / 2 );
    token_item->set_coords( x, y );
    this->tokens.push_back( token_item );
    this->scene->addItem( token_item );
}

void Revrsi::step_left(  ){
    sceneOffset_x = sceneOffset_x + 10;
    scene->setSceneRect( sceneOffset_x, sceneOffset_y, scene->sceneRect(  ).width(  ), scene->sceneRect(  ).height(  ) );
}

void Revrsi::step_right(  ){
    sceneOffset_x = sceneOffset_x - 10;
    scene->setSceneRect( sceneOffset_x, sceneOffset_y, scene->sceneRect(  ).width(  ), scene->sceneRect(  ).height(  ) );
}

void Revrsi::step_top(  ){
    sceneOffset_y = sceneOffset_y + 10;
    scene->setSceneRect( sceneOffset_x, sceneOffset_y, scene->sceneRect(  ).width(  ), scene->sceneRect(  ).height(  ) );
}

void Revrsi::step_down(  ){
    sceneOffset_y = sceneOffset_y - 10;
    scene->setSceneRect( sceneOffset_x, sceneOffset_y, scene->sceneRect(  ).width(  ), scene->sceneRect(  ).height(  ) );
}

void Revrsi::stopServerSL(  ){ //###Check
    this->ServerThread->terminate(  );
    this->ServerThread->wait(  );
    this->serverInit = false;
}

void Revrsi::switchOpacityWay(  ){
    if( this->direction ){
        this->anim->setDirection( QAbstractAnimation::Backward );
        this->direction = 0;
    }
    else{
        this->anim->setDirection( QAbstractAnimation::Forward );
        this->direction = 1;
    }
    this->anim->start(  );
}

void Revrsi::warpStart(  ){
    this->new_game(  );
}

void Revrsi::zoom_in(  ){
    //sceneOffset_scale = sceneOffset_scale + 0.1;
    ui->graphicsView->scale( sceneOffset_scale + 0.1,sceneOffset_scale + 0.1 );
}

void Revrsi::zoom_out(  ){
    //sceneOffset_scale = sceneOffset_scale - 0.1;
    ui->graphicsView->scale( sceneOffset_scale - 0.1,sceneOffset_scale - 0.1 );
}
