#include "widget4.h"
#include "ui_widget4.h"

widget4::widget4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget4)
{
    ui->setupUi(this);
}

widget4::~widget4()
{
    delete ui;
}
