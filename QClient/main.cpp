#include <QCoreApplication>
#include <iostream>
#include "client.h"

int main()
{
    std::cout << "Hallo Welt" << std::endl;
    Client meinCl("localhost", 1);

    //recv in Thread
    meinCl.start();

    //senden
    //meinCl.senden("");

    //stein vom Client setzen syntax int x, int y -> kann erst aufgerufen werden wenn id bekannt
    meinCl.setStoneClient(2,2);

    while(1){
    }
    return 0;
}
