#ifndef PRERECORDED_H
#define PRERECORDED_H

#include <QWidget>
#include "route_selection.h"

namespace Ui {
class PreRecorded;
}

class PreRecorded : public QWidget
{
    Q_OBJECT

public:
    explicit PreRecorded(QWidget *parent = 0);
    ~PreRecorded();
    void enable_back_button();

signals:
    void back_running_route();
    void dis_prr_packet(qint64 option);

private slots:
    void on_play_clicked();
    void on_back_clicked();

private:
    Ui::PreRecorded *ui;
};

#endif // PRERECORDED_H
