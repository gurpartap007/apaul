#include <QCoreApplication>

#include "fortuneserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FortuneServer f;

    return a.exec();
}
