#include "mpd.h"
#include "ui_mpd.h"

mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);
}

mpd::~mpd()
{
    delete ui;
}
