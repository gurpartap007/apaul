#include "bus.h"
#include "ui_bus.h"

bus::bus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bus)
{
    ui->setupUi(this);
}

bus::~bus()
{
    delete ui;
}
