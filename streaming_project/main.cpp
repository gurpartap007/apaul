#include "stream.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    stream w;
    w.show();

    return a.exec();
}
