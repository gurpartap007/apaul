#include "home.h"
#include "ui_home.h"
#include <QDesktopWidget>
#include <QDebug>

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    QDesktopWidget screen_home;
    QFont buttons_font;
    buttons_font.setFamily("Arial");

    //QSize icon_size(128,128);
    //ui->toolButton->setText("");
    ui->toolButton->setMaximumWidth(screen_home.width()*1/2);
    ui->toolButton->setMinimumHeight(screen_home.height()*1/3);
    //    this->setStyleSheet("QPushButton {font: 22pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    ui->toolButton_2->setMaximumWidth(screen_home.width()*1/2);
    ui->toolButton_2->setMinimumHeight(screen_home.height()*1/3);

    ui->toolButton_3->setMaximumWidth(screen_home.width()*1/2);
    ui->toolButton_3->setMinimumHeight(screen_home.height()*1/3);

    ui->toolButton_4->setMaximumWidth(screen_home.width()*1/2);
    ui->toolButton_4->setMinimumHeight(screen_home.height()*1/3);
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    this->setMinimumSize(screen_home.width(),screen_home.height()*3/4);
    if(screen_home.width() == 1366 )
        buttons_font.setPixelSize(52);
    else if(screen_home.width() == 1024 )
        buttons_font.setPixelSize(48);
    else if(screen_home.width() == 1920 )
        buttons_font.setPixelSize(72);
    else if(screen_home.width() == 800 )
    {
        buttons_font.setPixelSize(36);
        ui->toolButton->setIconSize(QSize(ui->toolButton->width()+50,ui->toolButton->height()+50));
        ui->toolButton_2->setIconSize(QSize(ui->toolButton->width()+50,ui->toolButton->height()+50));
        ui->toolButton_3->setIconSize(QSize(ui->toolButton->width()+50,ui->toolButton->height()+50));
        ui->toolButton_4->setIconSize(QSize(ui->toolButton->width()+50,ui->toolButton->height()+50));
    }

    ui->toolButton->setFont(buttons_font);
    ui->toolButton_2->setFont(buttons_font);
    ui->toolButton_3->setFont(buttons_font);
    ui->toolButton_4->setFont(buttons_font);


}

Home::~Home()
{
    delete ui;
}

void Home::on_toolButton_2_clicked()
{
    emit this->announcement_clicked();
}
