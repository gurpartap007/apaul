#ifndef PHONE_H
#define PHONE_H

#include <QWidget>
#include <QString>

namespace Ui {
class phone;
}

class phone : public QWidget
{
    Q_OBJECT

public:
    explicit phone(QWidget *parent = 0);
    ~phone();\
private slots:
    void call_to_board();
    void stop_call_to_board();

private:
    Ui::phone *ui;

};

#endif // PHONE_H
