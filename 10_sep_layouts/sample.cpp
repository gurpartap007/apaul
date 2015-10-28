#include "sample.h"
#include "ui_sample.h"

sample::sample(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sample)
{
    ui->setupUi(this);
}

sample::~sample()
{
    delete ui;
}
