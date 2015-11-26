#include "dir.h"
#include "mainwindow.h"

dir::dir()
{
    QDir new_dir;
    QString folder_path;
    folder_path = "/home/apaul/Documents/qmkdir/example/";
    new_dir.mkpath(folder_path);
    qDebug() << folder_path;
}

dir::~dir()
{

}

