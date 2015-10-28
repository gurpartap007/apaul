#ifndef RECIEVER_H
#define RECIEVER_H

#include <QWidget>

namespace Ui {
class reciever;
}

class reciever : public QWidget
{
    Q_OBJECT

public:
    explicit reciever(QWidget *parent = 0);
    ~reciever();
signals:
    void play();
      void pause();
        void stop();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::reciever *ui;

    };

#endif // RECIEVER_H
