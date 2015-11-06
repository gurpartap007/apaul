#ifndef RUNNING_ROUTE_H
#define RUNNING_ROUTE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QHeaderView>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include "route_selection.h"
#include "mythread.h"

namespace Ui {
class running_route;
}

class running_route : public QWidget
{
    Q_OBJECT

public:
    explicit running_route(QWidget *parent = 0);
    ~running_route();

public slots:
    void initialise_fields();

signals:
    void Journey_Start(qint64 option);
    void Pre_Recorded_Display();
    void route_ended();
    void gps_file_selected();
    void dis_ann_packet(qint64 option);

public slots:
    void on_et_clicked();
    void skip_event();
    void announce_event();
    void database_filling();
    void on_rf_clicked();
    void on_prm_clicked();

private:
    Ui::running_route *ui;
    QPushButton *skipButton;
    QPushButton *announceButton;
    QWidget *widget;
    QHBoxLayout *widgetLayout;
    QLabel *widgetText;

};

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

#endif // RUNNING_ROUTE_H
