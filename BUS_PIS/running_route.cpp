#include "running_route.h"
#include "ui_running_route.h"
#include "struct.h"
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QDesktopWidget>

enum Path_Route_Table
{
    ROUTE_CODE,
    PATH_CODE,
    STOP_CODE,
    STOP_REFERENCE,
    DISTANCE_FROM_SOURCE,
    LATITUDE,
    LONGITUDE,
    HEADING_INFORMATION,
    HEADING_TOLERANCE,
    POSITION_TOLERANCE_LAT,
    POSITION_TOLERANCE_LONG,
    DISTANCE_TOLERANCE,
    APP_PERI,
    ENTRY_PERI,
    EXIT_PERI
};

enum Stop_Master_Table
{
    STOP_NAME,
    STP_CODE,
    STOP_REF,
    STOP_DESC,
    LAT,
    LONG,
    HEADING_INFO,
    HEADING_TOL,
    POSITION_TOL,
    DISTANCE_TOL,
    STOP_TYPE
};

extern QString path_code, route_no, destination_code, gps_file, path_description, source_code, via_code, total_distance, number_of_stations;
int entry_time,station_no = 0;
QStringList datalist,datalist_one,audio_list;
QString query_text;
QFont newFont1;
running_route::running_route(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::running_route)
{
    ui->setupUi(this);
    QDesktopWidget screen_running_route;
    if(screen_running_route.width() == 1920)
        this->setStyleSheet("QPushButton {font: 30pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    else if(screen_running_route.width() == 1366)
    {
        newFont1.setFamily("sans Serif");
        newFont1.setPointSize(48);
        this->setStyleSheet("QPushButton {font: 24pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    }
    else if(screen_running_route.width() == 1360)
    {
        newFont1.setFamily("Sans Serif");
        newFont1.setPointSize(48);

        this->setStyleSheet("QPushButton {font: 24pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    }
    else if(screen_running_route.width() == 800)
    {
        newFont1.setFamily("Sans Serif");
        newFont1.setPointSize(30);
        this->setStyleSheet("QPushButton {font: 12pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }QListWidget {font: 36pt \"Arial\";}");
    }
    else if(screen_running_route.width() == 1024)
    {
        newFont1.setFamily("Sans Serif");
        newFont1.setPointSize(40);
        this->setStyleSheet("QPushButton {font: 17pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); };QListWidget {font: 42pt \"Arial\";}");
        qDebug() << screen_running_route.width();
        qDebug() << "Inside 22 POINT ";
    }
}

running_route::~running_route()
{
    delete ui;
}

void running_route::initialise_fields()
{
    QDesktopWidget screen_route;
    //this->setStyleSheet("background-color: rgb(202, 244, 250);");
    //INITIALISE FIELDS TO GIVE ANNOUNCEMENT AND SKIP OPTION
    emit this->Journey_Start(4);
    //this->setMaximumSize(screen_route.width(),screen_route.height()*2/3);
    skipButton = new QPushButton("Skip");
    announceButton = new QPushButton("Announcement");
    connect(skipButton, SIGNAL(released()), this, SLOT (skip_event()));
    connect(announceButton, SIGNAL(released()), this, SLOT (announce_event()));
    widget = new QWidget;
    widgetLayout = new QHBoxLayout;
    widgetText = new QLabel;
    ui->label_2->setText(route_no);
    ui->label_2->setStyleSheet("color: rgb(0,0, 0);");
    query_text = "select stop from stop_master_table where stop_code = '" + destination_code + "'" ;
    QSqlQuery query(query_text);
    query.first();
    ui->label_4->setText(query.value(0).toString());

    QListWidgetItem *item = new QListWidgetItem;
    item->setText("");
    item->setBackgroundColor(QColor(179,179,179));
    ui->listWidget->addItem(item);

    entry_time = 1;
    station_no = 0;
    database_filling();
}

void running_route::on_et_clicked()
{
    ui->listWidget->clear();
    emit this->route_ended();
}

void running_route::skip_event()
{

    //SKIP STATION
    int rows = ui->listWidget->count();
    if(rows == 1)
        return;
    QListWidgetItem *currentItem = ui->listWidget->item(0);
    currentItem->setText(widgetText->text());
    //currentItem->setText("hello");
    if(rows >= 3)
    {
        QListWidgetItem *currentItem1 = ui->listWidget->item(2);
        widgetText->setText(currentItem1->text());
    }
    if(rows > 3)
    {
        for(int i=3;i<rows;i++)
        {
            QListWidgetItem * currentItem = ui->listWidget->takeItem(i);
            ui->listWidget->insertItem(i - 1, currentItem);
        }
    }
    ui->listWidget->takeItem(ui->listWidget->count()-1);
    route_path.Curr_stop++;
    route_path.Prev_stop++;
    route_path.Next_stop++;
    if(route_path.Next_stop >= station_no)
        on_et_clicked();
}

void running_route::announce_event()
{
    if(route_path.Next_stop == station_no)
        return;
    emit this->dis_ann_packet(20);
}

void running_route::database_filling()
{
    //HEADER STRUCTURE FILLING
    memset(route_path.Header.Route, '\0', DIG_MAX_ROUTE_NUM_LEN);
    memcpy(route_path.Header.Route, route_no.toStdString().c_str(), route_no.size());
    memset(route_path.Header.Description, '\0', DIG_MAX_PATH_DESC_LEN);
    memcpy(route_path.Header.Description, path_description.toStdString().c_str(), path_description.size());
    memset(route_path.Header.Code, '\0', DIG_MAX_PATH_CODE_LEN);
    memcpy(route_path.Header.Code, path_code.toStdString().c_str(), path_code.size());
    memset(route_path.Header.Source_Stop, '\0', DIG_STN_CODE);
    memcpy(route_path.Header.Source_Stop, source_code.toStdString().c_str(), source_code.size());
    memset(route_path.Header.Via_stop, '\0', DIG_STN_CODE);
    memcpy(route_path.Header.Via_stop, via_code.toStdString().c_str(), via_code.size());
    memset(route_path.Header.Destination_Stop, '\0', DIG_STN_CODE);
    memcpy(route_path.Header.Destination_Stop, destination_code.toStdString().c_str(), destination_code.size());
    route_path.Header.distance = total_distance.toFloat();

    //PATH ROUTE FILLING
    //query_text = "select * from path_route_table where Path_code = '" + path_code + "' and Route = '" + route_no + "'";// order by Distnace_from_source asc";
    query_text = "select * from path_route_table where Path_code = '" + path_code + "' and Route = '" + route_no + "' order by convert(Distnace_from_source,SIGNED INTEGER) asc";
    QSqlQuery query1(query_text);
    while(query1.next()){
        datalist.clear();
        QSqlRecord record = query1.record();
        for(int i=0; i < record.count(); i++)
            datalist << record.value(i).toString();

        uword temp_lat_long1, temp_lat_long2;

        memset(route_path.Stops[station_no].info.Code, '\0', DIG_STN_CODE);
        memcpy(route_path.Stops[station_no].info.Code, datalist[STOP_CODE].toStdString().c_str(), datalist[STOP_CODE].size());
        route_path.Stops[station_no].info.reference = datalist[STOP_REFERENCE].toInt();
        route_path.Stops[station_no].info.distance_frm_src = datalist[DISTANCE_FROM_SOURCE].toFloat();

        route_path.Stops[station_no].info.latit = datalist[LATITUDE].toFloat();
        temp_lat_long1 = (uword)(route_path.Stops[station_no].info.latit*10000);
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        route_path.Stops[station_no].info.latit = (float)temp_lat_long2;

        route_path.Stops[station_no].info.longit = datalist[LONGITUDE].toFloat();
        temp_lat_long1 = (uword)(route_path.Stops[station_no].info.longit*10000);
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        route_path.Stops[station_no].info.longit = (float)temp_lat_long2;

        route_path.Stops[station_no].info.heading_info = datalist[HEADING_INFORMATION].toFloat();
        route_path.Stops[station_no].info.heading_tolerance = datalist[HEADING_TOLERANCE].toFloat();
        route_path.Stops[station_no].info.position_tolerance_lat = datalist[POSITION_TOLERANCE_LAT].toFloat();
        route_path.Stops[station_no].info.position_tolerance_long = datalist[POSITION_TOLERANCE_LONG].toFloat();
        route_path.Stops[station_no].info.distance_tolerance = datalist[DISTANCE_TOLERANCE].toFloat();
        route_path.Stops[station_no].info.approaching_peri = datalist[APP_PERI].toInt();
        route_path.Stops[station_no].info.entry_peri = datalist[ENTRY_PERI].toInt();
        route_path.Stops[station_no].info.exit_peri = datalist[EXIT_PERI].toInt();
        QString  test_query = "select * from stop_master_table where stop_code = '" + datalist[STOP_CODE] + "'";
        QSqlQuery query2("select * from stop_master_table where stop_code = '" + datalist[STOP_CODE] + "'");
        query2.first();
        datalist_one.clear();
        QSqlRecord record1 = query2.record();
        for(int j=0; j < record1.count(); j++)
            datalist_one << record1.value(j).toString();
        memset(route_path.Stops[station_no].info.station_name, '\0', DIG_STN_NAME);
        memcpy(route_path.Stops[station_no].info.station_name, datalist_one[STOP_NAME].toStdString().c_str(), datalist_one[STOP_NAME].size());
        memset(route_path.Stops[station_no].info.station_type, '\0', DIG_STN_TYPE);
        memcpy(route_path.Stops[station_no].info.station_type, datalist_one[STOP_TYPE].toStdString().c_str(), datalist_one[STOP_TYPE].size());

        QListWidgetItem *new_item = new QListWidgetItem;
        if(entry_time == 1)
        {


            widgetText->setText(datalist_one[STOP_NAME]);
            widgetText->setFont(newFont1);
            //  QFont newFont("Sans Serif",36);
            skipButton->setFont(newFont1);
            skipButton->setStyleSheet("QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
            announceButton->setFont(newFont1);
            announceButton->setStyleSheet("QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
            widgetLayout->addWidget(widgetText);
            widgetLayout->addWidget(skipButton);
            widgetLayout->setAlignment(skipButton,Qt::AlignLeft);
            widgetLayout->addWidget(announceButton);
            widgetLayout->setAlignment(announceButton,Qt::AlignLeft);
            widgetLayout->addStretch();
            widgetLayout->setSizeConstraint(QLayout::SetMaximumSize);
            widget->setLayout(widgetLayout);
            widget->setStyleSheet("background-color: rgb(255, 148, 124);");
            ui->listWidget->addItem(new_item);
            ui->listWidget->setItemWidget(new_item,widget);
        }
        else
        {
            new_item->setText(datalist_one[STOP_NAME]);
            ui->listWidget->addItem(new_item);
        }
        entry_time++;
        station_no++;
    }
    route_path.Header.no_of_stns = station_no;
    route_path.Curr_stop = 0;
    route_path.Next_stop = 1;
    route_path.Prev_stop = -1;
}

void running_route::on_rf_clicked()
{
    //OPEN GPS SIMULATION FILE
    gps_file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            "/home/apaul/Downloads", tr("GPS-Files (*.txt)"),0,QFileDialog::DontUseNativeDialog);
    if(!gps_file.isEmpty())
        emit this->gps_file_selected();
}



void running_route::on_prm_clicked()
{
    emit this->Pre_Recorded_Display();
}
