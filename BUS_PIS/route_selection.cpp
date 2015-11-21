#include "route_selection.h"
#include "ui_route_selection.h"

extern char display[20];
extern char *ptr;
bool selection = 0;
QString path_code, route_no, destination_code, path_description, source_code, via_code, total_distance, number_of_stations,pre_recorded;
int row;

route_selection::route_selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::route_selection)
{
    ui->setupUi(this);

    //CONNECTING TO DATABASE
    //PICKING UP SQL STATEMENTS FROM SAVED FILE AND UPDATING DATABASE
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("BUS_PIS");
    db.setUserName("root");
    db.setPassword("terron");
    bool ok = db.open();
    qDebug() << ok;

    QStringList tables = db.tables();
    qDebug() << tables;

    QFileInfo info("/home/apaul/BUS_PIS_PROJECT/Resources/database/somnath/working_route.txt");
    QDateTime modifieddt = info.lastModified();

    QDate moddate = modifieddt.date();
    QTime modtime = modifieddt.time();
    QDate currentdat = QDate::currentDate();
    QTime currenttim = QTime::currentTime();

   if((currentdat >= moddate) && ((currenttim.minute() - modtime.minute()) < 10))
    {
        QFile file ("/home/apaul/BUS_PIS_PROJECT/Resources/database/somnath/working_route.txt");
     /*  if(file.exists())
        {
            qDebug() << "file exist of database";
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream in(&file);
            while(!in.atEnd())  {
               QString file_data = in.readLine();
               QSqlQuery query(file_data,db);
               //qDebug() << "executed a statement";
            }
        }*/
    }
   else
        qDebug() << "File was modified more than 10 minutes ago";

    //LISTING OF ALL ROUTES
    ui->comboBox->addItem("");
    QSqlQuery query1("select * from stop_master_table where stop_type = 'Destination'");
    while (query1.next()) {
            QString data_name = query1.value(0).toString();
            data_name = data_name + "-" + query1.value(1).toString();
            ui->comboBox->addItem(data_name);
        }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("path_master_table");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(model);

    ui->tableView->setModel(proxyModel);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(60);

    ui->comboBox->setEditable(true);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineedit_filtering(QString)));
    connect(this, SIGNAL(lineedit_filter(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_filtering(QString)));
    connect(this, SIGNAL(combobox_filter(QString)), proxyModel, SLOT(setFilterRegExp(QString)));

    keyb = new keyboard;
    ui->stackedWidget->addWidget(keyb);
    ui->stackedWidget->setCurrentWidget(keyb);

    connect(keyb, SIGNAL(value_changed(char)), this, SLOT(key_process(char)));
}

route_selection::~route_selection()
{
    delete ui;
}

void route_selection::key_process(char value)
{
    switch(value)
    {
        //ROUTE IS SELECTED
        case ENTER_CLICK:
            row = ui->tableView->selectionModel()->currentIndex().row();
            route_no = ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toString();
            path_description = ui->tableView->model()->data(ui->tableView->model()->index(row,2)).toString();
            path_code = ui->tableView->model()->data(ui->tableView->model()->index(row,3)).toString();
            source_code = ui->tableView->model()->data(ui->tableView->model()->index(row,4)).toString();
            destination_code = ui->tableView->model()->data(ui->tableView->model()->index(row,5)).toString();
            total_distance = ui->tableView->model()->data(ui->tableView->model()->index(row,6)).toString();

            if(row >= 0)
                emit this->route_selected(30);
            break;
        default:
            if(!selection)
                ui->lineEdit->setText(display);
            else
                ui->comboBox->setCurrentText(display);
            break;
    }
}

void route_selection::lineedit_filtering(QString value)
{
    //SEARCH FILTERING FOR DESTINATION
    proxyModel->setFilterKeyColumn(0);
    emit this->lineedit_filter(value);
}

void route_selection::combobox_filtering(QString value)
{
    //SEARCH FILTERING FOR ROUTES
    proxyModel->setFilterKeyColumn(5);
    QString temp_value = value.right(5);
    emit this->combobox_filter(temp_value);
}



