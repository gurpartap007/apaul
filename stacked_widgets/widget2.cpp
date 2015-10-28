#include "widget2.h"
#include "ui_widget2.h"

widget2::widget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget2)
{
    ui->setupUi(this);
}

widget2::~widget2()
{
    delete ui;
}
