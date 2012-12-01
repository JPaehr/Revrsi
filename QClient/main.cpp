#include <QCoreApplication>
#include <iostream>
#include "client.h"

int main()
{
    std::cout << "Hallo Welt" << std::endl;
    Client meinCl("localhost");

    //recv in Thread
    meinCl.start();




    //senden
    meinCl.ausfuehren();
    return 0;
}
