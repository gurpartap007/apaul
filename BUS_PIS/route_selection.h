#ifndef ROUTE_SELECTION_H
#define ROUTE_SELECTION_H

#include <QWidget>
#include "keyboard.h"
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

namespace Ui {
class route_selection;
}

class route_selection : public QWidget
{
    Q_OBJECT

public:
    explicit route_selection(QWidget *parent = 0);
    ~route_selection();
    keyboard *keyb;
    QSortFilterProxyModel *proxyModel;

signals:
    void lineedit_filter(QString value);
    void combobox_filter(QString value);
    void route_selected(qint64 option);

public slots:
    void key_process(char value);
    void lineedit_filtering(QString value);
    void combobox_filtering(QString value);

private:
    Ui::route_selection *ui;
};

#endif // ROUTE_SELECTION_H
