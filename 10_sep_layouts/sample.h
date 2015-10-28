#ifndef SAMPLE_H
#define SAMPLE_H

#include <QMainWindow>
namespace Ui {
class sample;
}

class sample : public QMainWindow
{
    Q_OBJECT

public:
    explicit sample(QWidget *parent = 0);
    ~sample();

private:
    Ui::sample *ui;
};

#endif // SAMPLE_H
