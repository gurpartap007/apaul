#include "prerecorded.h"
#include "ui_prerecorded.h"
#include "struct.h"


extern QString pre_recorded;

PreRecorded::PreRecorded(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreRecorded)
{
    ui->setupUi(this);
    if(!route_path.status.bits.route_info_avail)
        ui->back->setEnabled(true);
}

PreRecorded::~PreRecorded()
{
    delete ui;
}

void PreRecorded::on_play_clicked()
{
    switch(ui->listWidget->currentRow())
    {
        case 0:
            pre_recorded = "PR1";
            emit this->dis_prr_packet(25);
            break;
        case 1:
            pre_recorded = "PR2";
            emit this->dis_prr_packet(25);
            break;
        case 2:
            pre_recorded = "PR3";
            emit this->dis_prr_packet(25);
            break;
        default:
            break;
    }
}

void PreRecorded::on_back_clicked()
{
    emit this->back_running_route();
}

void PreRecorded::enable_back_button()
{
    ui->back->setEnabled(true);
}
