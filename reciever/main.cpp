#include "reciever.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    reciever w;
    w.show();

    return a.exec();
}
