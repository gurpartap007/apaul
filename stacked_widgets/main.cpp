#include "widgetbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widgetbox w;
    w.show();

    return a.exec();
}
