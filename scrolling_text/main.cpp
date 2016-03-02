#include "scrolling.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    scrolling w;
    w.show();

    return a.exec();
}
