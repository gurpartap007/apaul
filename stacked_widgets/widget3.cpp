#include "widget3.h"
#include "ui_widget3.h"

widget3::widget3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget3)
{
    ui->setupUi(this);
}

widget3::~widget3()
{
    delete ui;
}
