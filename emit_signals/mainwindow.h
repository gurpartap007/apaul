#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
void play_button();
void pause_button();
void stop_button();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
