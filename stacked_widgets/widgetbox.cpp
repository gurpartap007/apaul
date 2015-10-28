#include "widgetbox.h"
#include "ui_widgetbox.h"

widgetbox::widgetbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widgetbox)
{
    ui->setupUi(this);
    scene1 = new widget1;
    scene2 = new widget2;
    scene3 = new widget3;
    scene4 = new widget4;
    ui->stackedWidget->addWidget(scene1);
    ui->stackedWidget->addWidget(scene2);
    ui->stackedWidget->addWidget(scene3);
    ui->stackedWidget->addWidget(scene4);

}

widgetbox::~widgetbox()
{
    delete ui;
}

void widgetbox::on_widget1_clicked()
{
    ui->stackedWidget->setCurrentWidget(scene1);
}

void widgetbox::on_widget2_clicked()
{
    ui->stackedWidget->setCurrentWidget(scene2);
}

void widgetbox::on_widget3_clicked()
{
    ui->stackedWidget->setCurrentWidget(scene3);
}

void widgetbox::on_widget4_clicked()
{
    ui->stackedWidget->setCurrentWidget(scene4);

}
