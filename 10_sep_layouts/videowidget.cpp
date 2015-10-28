#include "videowidget.h"
#include "ui_videowidget.h"

videowidget::videowidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videowidget)
{
    ui->setupUi(this);
    ui->pushButton->show();
}

videowidget::~videowidget()
{
    delete ui;
}
