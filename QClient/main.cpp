#include <QCoreApplication>
#include <iostream>
#include "client.h"

int main()
{
    std::cout << "Hallo Welt" << std::endl;
    Client meinCl("localhost", 1);

    //recv in Thread
    meinCl.start();



    sleep(1);

    //senden
    meinCl.senden("");
    return 0;
}
