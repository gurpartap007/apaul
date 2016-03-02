#include "stream.h"
#include "ui_stream.h"

stream::stream(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stream)
{
    ui->setupUi(this);
}

stream::~stream()
{
    delete ui;
}
