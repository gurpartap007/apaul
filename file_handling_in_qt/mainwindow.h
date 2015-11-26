#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header.h"
#include "dir.h"
#include "file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QFile test_file;
    dir *dir_example;
    file *file_example;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
