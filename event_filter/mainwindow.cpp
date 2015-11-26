#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->label->installEventFilter( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::eventFilter( QObject * watched, QEvent * event )
{
   QLabel *label = qobject_cast<QLabel *>(watched);
    if ( label && event->type() == QEvent::MouseButtonPress )
    {
        ui->lineEdit->setText("Ouch");
    }

    return QObject::eventFilter(watched, event);
}

