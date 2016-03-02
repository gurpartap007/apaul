#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

namespace Ui {
class camera;
}

class camera : public QWidget
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = 0);
    ~camera();

private:
    Ui::camera *ui;
};

#endif // CAMERA_H
