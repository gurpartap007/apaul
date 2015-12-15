#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QListWidgetItem>
#include "videowidget.h"
#include <QProcess>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QErrorMessage>

namespace Ui {
class player;
}

class player : public QWidget
{
    Q_OBJECT

public:
    explicit player(QWidget *parent = 0);
    QString player_video_location;
    ~player();
    VideoWidget *videoWidget;
    QMediaPlayer *mplayer;
    QFileDialog *video_dialog;
    QFileSystemModel *model;
private slots:
    void on_ovf_clicked();
    void on_ts_clicked();
    void onListWidget_3ItemClicked(QListWidgetItem* item);
    void onListWidget_2ItemClicked(QListWidgetItem* item);
    void onListWidgetItemClicked(QListWidgetItem* item);
    void on_play_clicked();
    void on_pause_clicked();
    void on_pb_clicked();
    void positionChanged(qint64 progress);
    void durationChanged(qint64 duration);
    void seek(int seconds);
    void on_sb_clicked();
    void on_ob_clicked();
    void on_oss_clicked();
    void on_cl_clicked();
    void on_ovs_clicked();
    void on_svs_clicked();
    void on_evs_clicked();
    void on_listView_clicked(const QModelIndex &index);

protected:
 void enterEvent(QEvent *ev);
 void leaveEvent(QEvent *ev);
 void mousePressEvent(QEvent *ev);
private:
    Ui::player *ui;
    QPixmap originalPixmap;
    QImage  *imageObject;
    QString folderpath;
    QString bookmark_name;
    QStringList bookmark_time;
    QProcess *mSlicingProcess;
    int image_no,slice_no;
};

#endif // PLAYER_H
