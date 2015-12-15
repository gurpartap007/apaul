#include "player.h"
#include "ui_player.h"
#include <QFileDialog>
#include <QScreen>
#include <QDateTime>
#include <QMessageBox>
#include <QDesktopWidget>

qint64 current_position = 0,bookmark_position = 0,bm_orig_count = 0,img_orig_count = 0;
bool image_view_click = 0,slice_item_click = 0;
QString video_location;

QString slice_folder;
qint64 slice_start_position = 0, slice_end_position = 0,slice_orig_count = 0;
bool video_available=false;
bool  video_fullscreen=true;
player::player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::player)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
 QDesktopWidget screen_player;

  //  ui->listView->hide();
    if(screen_player.width() == 1920)
    {
        this->setStyleSheet("QPushButton {font: 30pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        ui->listView->setStyleSheet("QListView {font: 44pt \"Arial\";}QListView{ background-color: rgb(179, 179, 179); }");
    }

   else if(screen_player.width() == 1366)
    {
        this->setStyleSheet("QPushButton {font: 22pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        ui->listView->setStyleSheet("QListView {font: 36pt \"Arial\";}QListView{ background-color: rgb(179, 179, 179); }");
    }
    else  if(screen_player.width() == 1360)
    {
        this->setStyleSheet("QPushButton {font: 22pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        ui->listView->setStyleSheet("QListView {font: 36pt \"Arial\";}QListView{ background-color: rgb(179, 179, 179); }");
       }
    else if(screen_player.width() == 1024)
    {
        this->setStyleSheet("QPushButton {font: 16pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        ui->listView->setStyleSheet("QListView {font: 32pt \"Arial\";}QListView{ background-color: rgb(179, 179, 179); }");
    }
    else if(screen_player.width() == 800)
    {
        this->setStyleSheet("QPushButton {font: 12pt \"Arial\";}QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        ui->listView->setStyleSheet("QListView {font: 28pt \"Arial\";}QListView{ background-color: rgb(179, 179, 179); }");
    }
   ////////////////////////////////////  RESIZING OF PLAYER BUTTONS ACCORDING TO RESOLTION   //////////////////////////
    ui->cl->setMinimumWidth(screen_player.width()/6); // CLEAR LOG BUTTON
    ui->cl->setMaximumHeight(screen_player.height()/10);
    ui->evs->setMinimumWidth(screen_player.width()/6); // END VIDEO SLICE BUTTON
    ui->evs->setMaximumHeight(screen_player.height()/10);
    ui->pause->setMinimumWidth(screen_player.width()/6); // VIDEO PAUSE BUTTON
    ui->pause->setMaximumHeight(screen_player.height()/10);
    ui->pb->setMinimumWidth(screen_player.width()/6); // PLACE BOOKMARK BUTTON
    ui->pb->setMaximumHeight(screen_player.height()/10);
    ui->play->setMaximumSize(screen_player.width()/6,screen_player.height()/10); // VIDEO PLAY BUTTON
    ui->ovf->setMinimumWidth(screen_player.width()/6); // OPEN VIDEO FILES BUTTON
    ui->ovf->setMaximumHeight(screen_player.height()/10);
    ui->sb->setMinimumWidth(screen_player.width()/6); // SAVE SESSION BUTTON
    ui->sb->setMaximumHeight(screen_player.height()/10);
    ui->svs->setMaximumSize(screen_player.width()/6,screen_player.height()/10); // SAVE VIDEO SLICE BUTTON
    ui->ts->setMinimumWidth(screen_player.width()/6);// TAKE VIDEO SCREENSHOT BUTTON
    ui->ts->setMaximumHeight(screen_player.height()/10);
    //////////////////////////////////  RESIZING OF BUTTONS ///////////////////////////////////////////////////////////////////
    folderpath = "/home/apaul/Pictures/Pictures-Bookmarks/";
    image_no = 1;
    slice_no = 1;

    //FFMPEG INITIALIZATION FOR SAVING VIDEO PART
    mSlicingProcess = new QProcess(this);

    imageObject = new QImage();
    mplayer = new QMediaPlayer;

    video_dialog = new QFileDialog(this,Qt::FramelessWindowHint);
    // this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // this->setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(mplayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(mplayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    //VIDEO WIDGET TO VIEW SAVED VIDEO
    videoWidget = new VideoWidget();
    videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    //videoWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    //  videoWidget->setMaximumSize(screen_player.width()*3/5,screen_player.height()*1/3);

    mplayer->setVideoOutput(videoWidget);

 //  ui->horizontalLayout->addWidget(videoWidget);

    connect(ui->listWidget_3, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onListWidget_3ItemClicked(QListWidgetItem*)));
    connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onListWidget_2ItemClicked(QListWidgetItem*)));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onListWidgetItemClicked(QListWidgetItem*)));
}

player::~player()
{
    delete model;
    mSlicingProcess->deleteLater();
    delete video_dialog;
    delete videoWidget;
    delete mplayer;
    delete ui;
}

void player::on_ovf_clicked()
{
    //OPENING VIDEO FILE
    if(!videoWidget->isHidden())
    videoWidget->hide();
    if(ui->listView->isHidden())
        ui->listView->show();
    slice_item_click = 0;
    QStringList video_files;
    folderpath = "/home/apaul/Downloads/Pictures-Bookmarks/";

    //////////////////////  LISTVIEW CODE //////////////////////////////////////////
    qDebug() << "INSIDE PLAYER" << player_video_location;
  //  model->setRootPath(player_video_location);
     model->setRootPath(player_video_location);
    model->setReadOnly(false);
    model->setFilter(QDir::Files | QDir::Dirs | QDir::NoDot);
    model->setNameFilters(QStringList{ "*" });
    model->setNameFilterDisables(false);
    ui->listView->setModel(model);
    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setRootIndex(model->index(model->rootPath()));

    ///////////////////// LISTVIEW  CODE /////////////////////////////////////////

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString dtstring = date.toString() + "-" + time.toString() + "/";
    folderpath = folderpath + dtstring;
    QDir dir(folderpath);
//////////////////////////////////////  VIDEO OPENING DIALOG  ///////////////////////////////////////////////
    /*
    video_dialog->setModal(true);
    video_dialog->setParent(this);
    //video_dialog->setOption(QFileDialog::DontUseNativeDialog,true);
    //video_dialog->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    video_dialog->exec();
    //video_dialog->raise();
    //video_dialog->showMaximized();
    video_files = video_dialog->selectedFiles();
    //video_files = video_dialog->selectedUrls();
    qDebug() << "debugging" << video_dialog->selectedUrls();
    qDebug() << video_files.at(0);
    //video_files << video_dialog->selectedFiles();
    //qDebug() << video_files;
    //video_dialog->setGeometry(0,0,1366,768);
    //video_location = video_dialog->getOpenFileName(this, tr("Open File"),
    //                     "/home/apaul/Videos", tr("Video-Files (*)"),0,QFileDialog::DontUseNativeDialog);*/
  //  mplayer->setMedia(QUrl::fromLocalFile(video_files.at(0)));
    //  if(mplayer->isVideoAvailable())
    {
    //    mplayer->play();
    //    video_available=true;
    }
    // QRect rect1(0,0,800,300);
    //ui->horizontalLayout->setGeometry(rect1);

}

void player::on_ts_clicked()
{
    QDesktopWidget screenshot;
    QDir dir(folderpath);
    dir.mkpath(folderpath);
    //TAKING A SNAPSHOT
    if(mplayer->isVideoAvailable() && !slice_item_click)
    {
        QString image_name = "image_" + QString::number(image_no) + ".jpg";

        originalPixmap = QPixmap(); // clear image for low memory situations
        // on embedded devices.
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen)
            originalPixmap = screen->grabWindow(0);
        QRect test_geometry(ui->line_3->geometry());
    qDebug() << ui->line_3->geometry();
    qDebug() << test_geometry;
    qDebug() << videoWidget->geometry();
       QRect rect(videoWidget->x(),(screenshot.height()*1/4)+13,videoWidget->width(),videoWidget->height());
       qDebug() << "Rect ........."<< rect;
     QPixmap cropped = originalPixmap.copy(rect);

       *imageObject = cropped.toImage();
        // *imageObject = originalPixmap.toImage();
        image_name =  image_name;
        imageObject->save(folderpath+ image_name);


        ui->listWidget_2->addItem(image_name);

        image_no++;
    }
    else
    {
        QMessageBox::information(this, tr("BUS PIS"),
                                 tr("You are viewing a slice right now"),
                                 QMessageBox::Ok);
    }
}

void player::onListWidget_3ItemClicked(QListWidgetItem *item)
{
    //SELECTING SLICE TO PLAY FROM LIST OF SAVED SLICES
    mplayer->pause();
    slice_item_click = 1;

    QString slice_name = item->text();
   mplayer->stop();
    mplayer->setMedia(QUrl::fromLocalFile(  slice_folder+slice_name));
    mplayer->play();
}

void player::onListWidget_2ItemClicked(QListWidgetItem *item)
{
    //SELECTING IMAGE FROM LIST OF SAVED IMAGES
    mplayer->pause();
    if(!image_view_click)
        current_position = mplayer->position();

    image_view_click = 1;

    QString image_name = item->text();

    mplayer->setMedia(QUrl::fromLocalFile(folderpath+ image_name));
    mplayer->play();
}

void player::onListWidgetItemClicked(QListWidgetItem *item)
{
    //SELECTING BOOKMARK FROM LIST OF SAVED BOOKMARKS
    if(!slice_item_click)
    {
        mplayer->pause();
        bookmark_time = item->text().split((" "),QString::SkipEmptyParts);
        current_position = (((bookmark_time[0].toInt() * 60) + bookmark_time[2].toInt()) * 1000) + bookmark_time[4].toInt();
        if(image_view_click)
        {
            image_view_click = 0;
            mplayer->setMedia(QUrl::fromLocalFile(video_location));
            mplayer->setPosition(current_position);
            mplayer->play();
        }
        else
        {
            mplayer->setPosition(current_position);
            mplayer->play();
        }
    }
    else
    {
        QMessageBox::information(this, tr("BUS PIS"),
                                 tr("Please reopen original video to access bookmarks"),
                                 QMessageBox::Ok);
    }
}

void player::on_play_clicked()
{
    //PLAY THE VIDEO
    if(image_view_click)
    {
        image_view_click = 0;
        mplayer->setMedia(QUrl::fromLocalFile(video_location));
        mplayer->setPosition(current_position);
        mplayer->play();
    }
    else
        mplayer->play();
}

void player::on_pause_clicked()
{
    mplayer->pause();
}

void player::on_pb_clicked()
{
    //PLACING A BOOKMARK
    if(mplayer->isVideoAvailable() && !slice_item_click)
    {
        bookmark_position = mplayer->position();
        qint16 seconds = bookmark_position / 1000;
        qint16 msecs = bookmark_position % 1000;
        qint16 minutes;
        if(seconds > 60)
        {
            minutes = seconds / 60;
            seconds = seconds % 60;
        }
        else
            minutes = 0;
        bookmark_name = QString::number(minutes) + " mins " + QString::number(seconds) + " secs " + QString::number(msecs) + " msecs ";
        ui->listWidget->addItem(bookmark_name);
    }
    else
    {
        QMessageBox::information(this, tr("BUS PIS"),
                                 tr("You are viewing a slice right now"),
                                 QMessageBox::Ok);
    }
}

void player::positionChanged(qint64 progress)
{
    //MOVING THE SLIDER FOR SEEKING IN VIDEO
    if (!ui->horizontalSlider->isSliderDown()) {
        ui->horizontalSlider->setValue(progress / 1000);
    }
}

void player::durationChanged(qint64 duration)
{
    ui->horizontalSlider->setMaximum(duration / 1000);
}

void player::seek(int seconds)
{
    mplayer->setPosition(seconds * 1000);
}

void player::on_sb_clicked()
{
    //SAVING THE BOOKMARK, SNAPSHOT AND VIDEO SLICES
    int row;
    if(ui->listWidget->count() > 0)
    {
        QString bkfile = folderpath + "bookmark_log.txt";
        QFile file(bkfile);
        if(!file.exists())
        {
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            row = 0;
        }
        else
        {
            file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
            row = (ui->listWidget->count() - (ui->listWidget->count() - bm_orig_count));
        }
        for(row = row; row < ui->listWidget->count(); row++)
        {
            QListWidgetItem *item = ui->listWidget->item(row);
            QTextStream out(&file);
            out << item->text().simplified() << "\n";
        }
        file.close();
    }

    if(ui->listWidget_2->count() > 0)
    {
        QString snapfile = folderpath + "snapshot_log.txt";
        QFile file1(snapfile);
        if(!file1.exists())
        {
            file1.open(QIODevice::WriteOnly | QIODevice::Text);
            row = 0;
        }
        else
        {
            file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
            row = (ui->listWidget_2->count() - (ui->listWidget_2->count() - img_orig_count));
        }
        for(row = row; row < ui->listWidget_2->count(); row++)
        {
            QListWidgetItem *item = ui->listWidget_2->item(row);
            QTextStream out(&file1);
            out << item->text().simplified() << "\n";
        }
        file1.close();
    }

    if(ui->listWidget_3->count() > 0)
    {
        QString slicefile = folderpath + "slice_log.txt";
        QFile file2(slicefile);
        if(!file2.exists())
        {
            file2.open(QIODevice::WriteOnly | QIODevice::Text);
            row = 0;
        }
        else
        {
            file2.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
            row = (ui->listWidget_3->count() - (ui->listWidget_3->count() - slice_orig_count));
        }
        for(row = row; row < ui->listWidget_3->count(); row++)
        {
            QListWidgetItem *item = ui->listWidget_3->item(row);
            QTextStream out(&file2);
            out << item->text().simplified() << "\n";
        }
        file2.close();

        bm_orig_count = ui->listWidget->count();
        img_orig_count = ui->listWidget_2->count();
        slice_orig_count = ui->listWidget_3->count();
    }
}

void player::on_ob_clicked()
{
    //OPENING SAVED BOOKMARKS
    if(mplayer->isVideoAvailable())
    {
        QMessageBox::information(this, tr("BUS PIS"),
                                 tr("Please make sure to open Bookmarks for the same video"),
                                 QMessageBox::Ok);

        QString bfile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home/apaul/Downloads/Pictures-Bookmarks", tr("Text-Files (*.txt)"),0,QFileDialog::DontUseNativeDialog);
        if(bfile.contains("bookmark", Qt::CaseSensitive))
        {
            QFile pfile(bfile);
            if (!pfile.open(QIODevice::ReadOnly |QIODevice::Text))
                return;
            QTextStream in(&pfile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QListWidgetItem *item = new QListWidgetItem;
                item->setText(line);
                ui->listWidget->addItem(item);
            }
            pfile.close();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("BUS PIS"),
                             tr("No Video Open"),
                             QMessageBox::Ok);
    }
}

void player::on_oss_clicked()
{
    //OPENING SAVED SNAPSHOTS
    if(!mplayer->isVideoAvailable())
    {
        QString bfile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home/apaul/Downloads/Pictures-Bookmarks", tr("Text-Files (*.txt)"),0,QFileDialog::DontUseNativeDialog);
        if(bfile.contains("snapshot", Qt::CaseSensitive))
        {
            QFile pfile(bfile);
            if (!pfile.open(QIODevice::ReadOnly |QIODevice::Text))
                return;
            QTextStream in(&pfile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QListWidgetItem *item = new QListWidgetItem;
                item->setText(line);
                ui->listWidget_2->addItem(item);
            }
            pfile.close();
        }
        if(!mplayer->isVideoAvailable())
        {
            bfile.resize(66);
            folderpath = bfile;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("BUS PIS");
        msgBox.setText("A Video File is already open");
        msgBox.setInformativeText("Do you want to close the video file?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes:
            mplayer->deleteLater();
            mplayer = new QMediaPlayer;
            connect(mplayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
            connect(mplayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
            connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
            mplayer->setVideoOutput(videoWidget);
            break;
        default:
            // should never be reached
            break;
        }
    }
}

void player::on_cl_clicked()
{
    //CLEAR BOOKMARKS, SNAPSHOS AND VIDEO SLICES
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    image_no = 1; slice_no = 1;

    mplayer->deleteLater();
    mplayer = new QMediaPlayer;
    connect(mplayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(mplayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    mplayer->setVideoOutput(videoWidget);
}

void player::on_ovs_clicked()
{
    //OPENING VIDEO SLICE
    if(!mplayer->isVideoAvailable())
    {
        QString bfile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home/apaul/Downloads/Pictures-Bookmarks", tr("Text-Files (*.txt)"),0,QFileDialog::DontUseNativeDialog);
        if(bfile.contains("slice", Qt::CaseSensitive))
        {
            QFile pfile(bfile);
            if (!pfile.open(QIODevice::ReadOnly |QIODevice::Text))
                return;
            QTextStream in(&pfile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QListWidgetItem *item = new QListWidgetItem;
                item->setText(line);
                ui->listWidget_3->addItem(item);
            }
            pfile.close();
        }
        if(!mplayer->isVideoAvailable())
        {
            bfile.resize(66);
            folderpath = bfile;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("BUS PIS");
        msgBox.setText("A Video File is already open");
        msgBox.setInformativeText("Do you want to close the video file?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes:
            mplayer->deleteLater();
            mplayer = new QMediaPlayer;
            connect(mplayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
            connect(mplayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
            connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
            mplayer->setVideoOutput(videoWidget);
            break;
        default:
            // should never be reached
            break;
        }
    }
}

void player::on_svs_clicked()
{
    //SET START OF VIDEO SLICE
    if(mplayer->isVideoAvailable())
    {
        ui->svs->setEnabled(0);
        slice_start_position = mplayer->position();
    }
    else
    {
        QMessageBox::warning(this, tr("BUS PIS"),
                             tr("No Video Open"),
                             QMessageBox::Ok);
    }

}

void player::on_evs_clicked()
{
    //SET END OF VIDEO SLICE
    if(!ui->svs->isEnabled())
    {
        QString slice_final_name;
       slice_folder = "/home/apaul/Downloads/saved_video_slices/";
        QString program = "/usr/bin/ffmpeg";
        QStringList arguments;

        slice_end_position = mplayer->position();
        QString slice_start_time,slice_end_time,total_command;
        qint16 minutes,seconds;

        QString slice_name = "slice_" + QString::number(slice_no) + ".mp4";

        seconds = slice_start_position / 1000;
        minutes = seconds / 60;
        if(minutes > 0)
            seconds = seconds % 60;
        if(seconds > 9)
        {
            if(minutes > 9)
                slice_start_time = "00:" + QString::number(minutes) + ":" + QString::number(seconds);
            else
                slice_start_time = "00:0" + QString::number(minutes) + ":" + QString::number(seconds);
        }
        else
        {
            if(minutes > 9)
                slice_start_time = "00:" + QString::number(minutes) + ":0" + QString::number(seconds);
            else
                slice_start_time = "00:0" + QString::number(minutes) + ":0" + QString::number(seconds);
        }

        seconds = slice_end_position / 1000;
        minutes = seconds / 60;
        if(minutes > 0)
            seconds = seconds % 60;
        if(seconds > 9)
        {
            if(minutes > 9)
                slice_end_time = "00:" + QString::number(minutes) + ":" + QString::number(seconds);
            else
                slice_end_time = "00:0" + QString::number(minutes) + ":" + QString::number(seconds);
        }
        else
        {
            if(minutes > 9)
                slice_end_time = "00:" + QString::number(minutes) + ":0" + QString::number(seconds);
            else
                slice_end_time = "00:0" + QString::number(minutes) + ":0" + QString::number(seconds);
        }
        QDir dir(slice_folder);
        dir.mkpath(slice_folder);
        slice_final_name = slice_folder + slice_name;
        arguments << "-i" << video_location << "-ss" << slice_start_time << "-to" << slice_end_time << "-c" << "copy" << "-y" << slice_final_name;

        mSlicingProcess->setProcessChannelMode(QProcess::MergedChannels);
        mSlicingProcess->start(program, arguments);

        ui->listWidget_3->addItem(slice_name);

        slice_no++;

        ui->svs->setEnabled(1);
    }
}

void player::enterEvent(QEvent *ev)
{
    QApplication::setOverrideCursor( QCursor(Qt::PointingHandCursor));
    /*  if(video_available && video_fullscreen )
    {
    ui->horizontalSlider->hide();
    ui->cl->hide();
    ui->evs->hide();
    ui->ovf->hide();
    ui->ts->hide();
    ui->pause->hide();
    ui->play->hide();
    ui->pb->hide();
    ui->sb->hide();
    ui->svs->hide();
    ui->line_2->hide();
    video_fullscreen=false;
    }
    else
    {
        ui->horizontalSlider->show();
        ui->cl->show();
        ui->evs->show();
        ui->ovf->show();
        ui->ts->show();
        ui->pause->show();
        ui->play->show();
        ui->pb->show();
        ui->sb->show();
        ui->svs->show();
        ui->line_2->show();
        video_fullscreen=true;
    }*/

}

void player::leaveEvent(QEvent *ev)
{
    QApplication::restoreOverrideCursor();
}

void player::mousePressEvent(QEvent *ev)
{
    qDebug()<< "showed MOuse Release Event";
    if(video_fullscreen)
    {
        ui->horizontalSlider->hide();
        ui->cl->hide();
        ui->evs->hide();
        ui->ovf->hide();
        ui->ts->hide();
        ui->pause->hide();
        ui->play->hide();
        ui->pb->hide();
        ui->sb->hide();
        ui->svs->hide();
        ui->line_2->hide();
        video_fullscreen=false;
    }
    else
    {
        ui->horizontalSlider->show();
        ui->cl->show();
        ui->evs->show();
        ui->ovf->show();
        ui->ts->show();
        ui->pause->show();
        ui->play->show();
        ui->pb->show();
        ui->sb->show();
        ui->svs->show();
        ui->line_2->show();
        video_fullscreen=true;
    }
}

void player::on_listView_clicked(const QModelIndex &index)
{


    QDir temporary;
if(index.row()==0)
{
temporary.setPath(player_video_location);
temporary.cdUp();
  //  qDebug() << model->fileInfo(index).absoluteDir();
qDebug() << temporary.absolutePath();
model->setRootPath(temporary.absolutePath());
ui->listView->setModel(model);
   ui->listView->setRootIndex(model->index(model->rootPath()));
return ;
}
//temporary.setPath(model->fileInfo(index).absoluteFilePath());
if(model->fileInfo(index).isDir())
{
    qDebug() << model->fileInfo(index).absoluteFilePath();
    model->setRootPath(model->fileInfo(index).absoluteFilePath());
    ui->listView->setModel(model);
       ui->listView->setRootIndex(model->index(model->rootPath()));
       return ;
}
    video_location = model->fileInfo(index).absoluteFilePath();
    mplayer->setMedia(QUrl::fromLocalFile(video_location));
    ui->listView->hide();
   ui->horizontalLayout->addWidget(videoWidget);
   if(videoWidget->isHidden())
       videoWidget->show();
    mplayer->play();
if(mplayer->state() == QMediaPlayer::StoppedState)
{

    QMessageBox::warning(this, tr("BUS PIS"),
                         tr("Not Valid video file "),
                         QMessageBox::Ok);
     //ui->listView->setRootIndex(model->index(model->rootPath()));
     return;
}

  // mplayer->play();
}
