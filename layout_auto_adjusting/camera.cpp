#include "camera.h"
#include "ui_camera.h"

camera::camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
}

camera::~camera()
{
    delete ui;
}
