
#include <QApplication>
#include "revrsi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Revrsi w;
    w.show();
    
    return a.exec();
}
