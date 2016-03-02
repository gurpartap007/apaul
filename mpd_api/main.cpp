#include "mpd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mpd w;
    w.show();

    return a.exec();
}
