/** header file for the application with only one main window
 * @file mainwindow.h
 * @author gurpartap singh
 * @date 21/11/2015
 * @defgroup camera
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraInfo>

namespace Ui {
class MainWindow;
}
/** @brief Default constructor of Mainwindow class to display mainwindow */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    /** @brief default destructor of MainWindow Class */
    ~MainWindow();
/** main window private user interface
 * @ingroup camera
 * */
private:
    Ui::MainWindow *ui;/**< private pointer */
    u_int8_t count;/**< save number of objects */
};

#endif // MAINWINDOW_H
