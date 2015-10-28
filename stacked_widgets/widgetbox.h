#ifndef WIDGETBOX_H
#define WIDGETBOX_H

#include <QMainWindow>
#include <QStackedWidget>
#include "widget1.h"
#include "widget2.h"
#include "widget3.h"
#include "widget4.h"


namespace Ui {
class widgetbox;
}

class widgetbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit widgetbox(QWidget *parent = 0);
    ~widgetbox();
  widget1 *scene1;
  widget2 *scene2;
  widget3 *scene3;
  widget4 *scene4;


private slots:
    void on_widget1_clicked();

    void on_widget2_clicked();

    void on_widget3_clicked();

    void on_widget4_clicked();

private:
    Ui::widgetbox *ui;
};

#endif // WIDGETBOX_H
