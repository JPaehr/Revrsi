#ifndef ALTERNATIVEMAIN_H
#define ALTERNATIVEMAIN_H
#include <QCoreApplication>
#include "socket.h"
#include <iostream>
#include "server.h"
#include <vector>
#include <string>
#include "superserver.h"
//#include <QObject>

class alternativeMAIN : public QObject
{
    Q_OBJECT
public:
    alternativeMAIN();
};

#endif // ALTERNATIVEMAIN_H
