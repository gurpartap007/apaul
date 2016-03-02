#include "player.h"
#include "ui_player.h"

player::player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::player)
{
    ui->setupUi(this);
}

player::~player()
{
    delete ui;
}
