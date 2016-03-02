#ifndef STREAM_H
#define STREAM_H

#include <QMainWindow>

namespace Ui {
class stream;
}

class stream : public QMainWindow
{
    Q_OBJECT

public:
    explicit stream(QWidget *parent = 0);
    ~stream();

private:
    Ui::stream *ui;
};

#endif // STREAM_H
