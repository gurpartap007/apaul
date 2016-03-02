#include "scrolling.h"
#include "ui_scrolling.h"

scrolling::scrolling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scrolling)
{
    ui->setupUi(this);
}

scrolling::~scrolling()
{
    delete ui;
}
