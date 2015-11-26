#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gurpartap");
    db.setUserName("root");
    db.setPassword("terron");
    bool ok = db.open();
    qDebug() << ok;

    QStringList tables = db.tables();
    qDebug() << tables;
      QSqlQuery query("SELECT * FROM `students`");
      while (query.next()) {

              QString data1 = query.value(0).toString();
              QString data2 = query.value(1).toString();
              QString data3 = query.value(2).toString();
              QString data4 = query.value(3).toString();
              qDebug() << data1   << data2 << data3 << data4;
          }
      QSqlRecord rec = query.record();

      qDebug() << "Number of columns: " << rec.count();

      int nameCol = rec.indexOf("English"); // index of the field "name"
      while (query.next())
          qDebug() << query.value(nameCol).toString(); // output all names
}

MainWindow::~MainWindow()
{
    delete ui;
}
