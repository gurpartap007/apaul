#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

#define LETTER_Qq	0
#define	LETTER_Ww	1
#define LETTER_Ee	2
#define	LETTER_Rr	3
#define LETTER_Tt	4
#define	LETTER_Yy	5
#define LETTER_Uu	6
#define	LETTER_Ii	7
#define LETTER_Oo	8
#define	LETTER_Pp	9
#define LETTER_Aa	10
#define	LETTER_Ss	11
#define LETTER_Dd	12
#define	LETTER_Ff	13
#define LETTER_Gg	14
#define	LETTER_Hh	15
#define LETTER_Jj	16
#define	LETTER_Kk	17
#define LETTER_Ll	18
#define LETTER_Zz	19
#define	LETTER_Xx	20
#define	LETTER_Cc	21
#define LETTER_Vv	22
#define	LETTER_Bb	23
#define LETTER_Nn	24
#define	LETTER_Mm	25
#define ENTER_CLICK	100

namespace Ui {
class keyboard;
}

class keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit keyboard(QWidget *parent = 0);
    ~keyboard();

private:
    Ui::keyboard *ui;

signals:
    void value_changed(char value);

public slots:
    void characterset(int number, int mode);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_39_clicked();
};

#endif // KEYBOARD_H
