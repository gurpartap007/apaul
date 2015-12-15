#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDesktopWidget>

//VARIABLES
char display[20], *ptr;
int check;
char qwerty_letter[4][26] = {{'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'},
                             {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M'},
                             {'1','2','3','4','5','6','7','8','9','0','@',':',';','_','$','#','(',')','/',92,'?','!','"','+','-','='},
                             {'%','*','[',']','{','}','<','>','^','&','@',':',';','_','$','#','(',')','/',92,'?','!','"','+','-','='}};

keyboard::keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keyboard)
{
    ui->setupUi(this);
    QDesktopWidget screen_keyboard;
    this->setMaximumSize(800,200);
    if(screen_keyboard.width() == 800)
        this->setStyleSheet("QPushButton {font: 19pt \"Arial\";font-weight: bold;}QPushButton{ background-color: rgb(180, 207, 207); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    else if(screen_keyboard.width() == 1024)
        this->setStyleSheet("QPushButton {font: 24pt \"Arial\"; font-weight: bold;}QPushButton{ background-color: rgb(180, 207, 207); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    else if(screen_keyboard.width() == 1360)
        this->setStyleSheet("QPushButton {font: 28pt \"Arial\"; font-weight: bold;}QPushButton{ background-color: rgb(180, 207, 207); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
    else if(screen_keyboard.width() == 1366)
        this->setStyleSheet("QPushButton {font: 30pt \"Arial\"; font-weight: bold;}QPushButton{ background-color: rgb(180, 207, 207); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");

    memset(display,0,sizeof(display));
    ptr = &display[0];
    check = 0;
}

keyboard::~keyboard()
{
    delete ui;
}

//=============================================================================
//	characterset
//
//	Description: Set the character in text box
//
//	Parameters:	number - to select the charcter from array
//=============================================================================
void keyboard::characterset(int number,int mode)
{
    *ptr = qwerty_letter[mode][number];
    emit value_changed(*ptr);
    ptr++;
}

void keyboard::on_pushButton_3_clicked()
{
    characterset(LETTER_Qq,check);
}

void keyboard::on_pushButton_4_clicked()
{
    characterset(LETTER_Ww,check);
}

void keyboard::on_pushButton_5_clicked()
{
    characterset(LETTER_Ee,check);
}

void keyboard::on_pushButton_6_clicked()
{
    characterset(LETTER_Rr,check);
}

void keyboard::on_pushButton_7_clicked()
{
    characterset(LETTER_Tt,check);
}

void keyboard::on_pushButton_8_clicked()
{
    characterset(LETTER_Yy,check);
}

void keyboard::on_pushButton_9_clicked()
{
    characterset(LETTER_Uu,check);
}

void keyboard::on_pushButton_10_clicked()
{
    characterset(LETTER_Ii,check);
}

void keyboard::on_pushButton_11_clicked()
{
    characterset(LETTER_Oo,check);
}

void keyboard::on_pushButton_12_clicked()
{
    characterset(LETTER_Pp,check);
}

void keyboard::on_pushButton_13_clicked()
{
    characterset(LETTER_Aa,check);
}

void keyboard::on_pushButton_21_clicked()
{
    characterset(LETTER_Ss,check);
}

void keyboard::on_pushButton_17_clicked()
{
    characterset(LETTER_Dd,check);
}

void keyboard::on_pushButton_18_clicked()
{
    characterset(LETTER_Ff,check);
}

void keyboard::on_pushButton_16_clicked()
{
    characterset(LETTER_Gg,check);
}

void keyboard::on_pushButton_14_clicked()
{
    characterset(LETTER_Hh,check);
}

void keyboard::on_pushButton_19_clicked()
{
    characterset(LETTER_Jj,check);
}

void keyboard::on_pushButton_15_clicked()
{
    characterset(LETTER_Kk,check);
}

void keyboard::on_pushButton_20_clicked()
{
    characterset(LETTER_Ll,check);
}

void keyboard::on_pushButton_28_clicked()
{
    characterset(LETTER_Zz,check);
}

void keyboard::on_pushButton_25_clicked()
{
    characterset(LETTER_Xx,check);
}

void keyboard::on_pushButton_26_clicked()
{
    characterset(LETTER_Cc,check);
}

void keyboard::on_pushButton_24_clicked()
{
    characterset(LETTER_Vv,check);
}

void keyboard::on_pushButton_23_clicked()
{
    characterset(LETTER_Bb,check);
}

void keyboard::on_pushButton_27_clicked()
{
    characterset(LETTER_Nn,check);
}

void keyboard::on_pushButton_22_clicked()
{
    characterset(LETTER_Mm,check);
}

//Caps
void keyboard::on_pushButton_30_clicked()
{
    char change[2],*pter;
    pter = &change[0];
    change[1] = '\0';
    if(check == 0)
    {
        check = 1;
        //change to uppercase alphabets///////////////////////////////////////////////////////////////////////////////////////////////////////////
        *pter = 'Q';ui->pushButton_3->setText(change);*pter = 'W';ui->pushButton_4->setText(change);*pter = 'E';ui->pushButton_5->setText(change);
        *pter = 'R';ui->pushButton_6->setText(change);*pter = 'T';ui->pushButton_7->setText(change);*pter = 'Y';ui->pushButton_8->setText(change);
        *pter = 'U';ui->pushButton_9->setText(change);*pter = 'I';ui->pushButton_10->setText(change);*pter = 'O';ui->pushButton_11->setText(change);
        *pter = 'P';ui->pushButton_12->setText(change);*pter = 'A';ui->pushButton_13->setText(change);*pter = 'S';ui->pushButton_21->setText(change);
        *pter = 'D';ui->pushButton_17->setText(change);*pter = 'F';ui->pushButton_18->setText(change);*pter = 'G';ui->pushButton_16->setText(change);
        *pter = 'H';ui->pushButton_14->setText(change);*pter = 'J';ui->pushButton_19->setText(change);*pter = 'K';ui->pushButton_15->setText(change);
        *pter = 'L';ui->pushButton_20->setText(change);*pter = 'Z';ui->pushButton_28->setText(change);*pter = 'X';ui->pushButton_25->setText(change);
        *pter = 'C';ui->pushButton_26->setText(change);*pter = 'V';ui->pushButton_24->setText(change);*pter = 'B';ui->pushButton_23->setText(change);
        *pter = 'N';ui->pushButton_27->setText(change);*pter = 'M';ui->pushButton_22->setText(change);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    else if(check == 1)
    {
        check = 0;
        //change to lowercase alphabets///////////////////////////////////////////////////////////////////////////////////////////////////////////
        *pter = 'q';ui->pushButton_3->setText(change);*pter = 'w';ui->pushButton_4->setText(change);*pter = 'e';ui->pushButton_5->setText(change);
        *pter = 'r';ui->pushButton_6->setText(change);*pter = 't';ui->pushButton_7->setText(change);*pter = 'y';ui->pushButton_8->setText(change);
        *pter = 'u';ui->pushButton_9->setText(change);*pter = 'i';ui->pushButton_10->setText(change);*pter = 'o';ui->pushButton_11->setText(change);
        *pter = 'p';ui->pushButton_12->setText(change);*pter = 'a';ui->pushButton_13->setText(change);*pter = 's';ui->pushButton_21->setText(change);
        *pter = 'd';ui->pushButton_17->setText(change);*pter = 'f';ui->pushButton_18->setText(change);*pter = 'g';ui->pushButton_16->setText(change);
        *pter = 'h';ui->pushButton_14->setText(change);*pter = 'j';ui->pushButton_19->setText(change);*pter = 'k';ui->pushButton_15->setText(change);
        *pter = 'l';ui->pushButton_20->setText(change);*pter = 'z';ui->pushButton_28->setText(change);*pter = 'x';ui->pushButton_25->setText(change);
        *pter = 'c';ui->pushButton_26->setText(change);*pter = 'v';ui->pushButton_24->setText(change);*pter = 'b';ui->pushButton_23->setText(change);
        *pter = 'n';ui->pushButton_27->setText(change);*pter = 'm';ui->pushButton_22->setText(change);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

void keyboard::on_pushButton_29_clicked()
{
    if(ptr != &display[0])
        ptr--;	//decrementing write pointer
    *ptr = '\0';
    emit value_changed(*ptr);
    //SET TEXT
    //ui->plainTextEdit->setPlainText(display);
}

void keyboard::on_pushButton_31_clicked()
{
    char change[4],*pter;
    pter = &change[0];
    change[1] = '\0';change[2] = '\0';change[3] = '\0';
    if(check == 0 || check == 1)
    {
        check = 2;
        //change to extra characters//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        *pter = '1';ui->pushButton_3->setText(change);*pter = '2';ui->pushButton_4->setText(change);*pter = '3';ui->pushButton_5->setText(change);
        *pter = '4';ui->pushButton_6->setText(change);*pter = '5';ui->pushButton_7->setText(change);*pter = '6';ui->pushButton_8->setText(change);
        *pter = '7';ui->pushButton_9->setText(change);*pter = '8';ui->pushButton_10->setText(change);*pter = '9';ui->pushButton_11->setText(change);
        *pter = '0';ui->pushButton_12->setText(change);*pter = '@';ui->pushButton_13->setText(change);*pter = ':';ui->pushButton_21->setText(change);
        *pter = ';';ui->pushButton_17->setText(change);*pter = '_';ui->pushButton_18->setText(change);*pter = '$';ui->pushButton_16->setText(change);
        *pter = '#';ui->pushButton_14->setText(change);*pter = '(';ui->pushButton_19->setText(change);*pter = ')';ui->pushButton_15->setText(change);
        *pter = '/';ui->pushButton_20->setText(change);*pter =  92;ui->pushButton_28->setText(change);*pter = '?';ui->pushButton_25->setText(change);
        *pter = '!';ui->pushButton_26->setText(change);*pter = '"';ui->pushButton_24->setText(change);*pter = '+';ui->pushButton_23->setText(change);
        *pter = '-';ui->pushButton_27->setText(change);*pter = '=';ui->pushButton_22->setText(change);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        change[0] = '*';change[1] = '[';change[2] = '{';ui->pushButton_31->setText(change);
        change[0] = '\0';change[1] = '\0';change[2] = '\0';
    }
    else if(check == 2)
    {
        check = 3;
        //change to extra characters///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        *pter = '%';ui->pushButton_3->setText(change);*pter = '*';ui->pushButton_4->setText(change);*pter = '[';ui->pushButton_5->setText(change);
        *pter = ']';ui->pushButton_6->setText(change);*pter = '{';ui->pushButton_7->setText(change);*pter = '}';ui->pushButton_8->setText(change);
        *pter = '<';ui->pushButton_9->setText(change);*pter = '>';ui->pushButton_10->setText(change);*pter = '^';ui->pushButton_11->setText(change);
        *pter = '&';ui->pushButton_12->setText(change);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        change[0] = 'A';change[1] = 'b';change[2] = 'c';ui->pushButton_31->setText(change);
        change[0] = '\0';change[1] = '\0';change[2] = '\0';
    }
    else if(check == 3)
    {
        check = 0;
        //change to lowercase alphabets///////////////////////////////////////////////////////////////////////////////////////////////////////////
        *pter = 'q';ui->pushButton_3->setText(change);*pter = 'w';ui->pushButton_4->setText(change);*pter = 'e';ui->pushButton_5->setText(change);
        *pter = 'r';ui->pushButton_6->setText(change);*pter = 't';ui->pushButton_7->setText(change);*pter = 'y';ui->pushButton_8->setText(change);
        *pter = 'u';ui->pushButton_9->setText(change);*pter = 'i';ui->pushButton_10->setText(change);*pter = 'o';ui->pushButton_11->setText(change);
        *pter = 'p';ui->pushButton_12->setText(change);*pter = 'a';ui->pushButton_13->setText(change);*pter = 's';ui->pushButton_21->setText(change);
        *pter = 'd';ui->pushButton_17->setText(change);*pter = 'f';ui->pushButton_18->setText(change);*pter = 'g';ui->pushButton_16->setText(change);
        *pter = 'h';ui->pushButton_14->setText(change);*pter = 'j';ui->pushButton_19->setText(change);*pter = 'k';ui->pushButton_15->setText(change);
        *pter = 'l';ui->pushButton_20->setText(change);*pter = 'z';ui->pushButton_28->setText(change);*pter = 'x';ui->pushButton_25->setText(change);
        *pter = 'c';ui->pushButton_26->setText(change);*pter = 'v';ui->pushButton_24->setText(change);*pter = 'b';ui->pushButton_23->setText(change);
        *pter = 'n';ui->pushButton_27->setText(change);*pter = 'm';ui->pushButton_22->setText(change);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        change[0] = '1';change[1] = '2';change[2] = '!';ui->pushButton_31->setText(change);
        change[0] = '\0';change[1] = '\0';change[2] = '\0';
    }
}

void keyboard::on_pushButton_32_clicked()
{
    *ptr = 39;
    emit value_changed(*ptr);
    ptr++;
}

void keyboard::on_pushButton_39_clicked()
{
    *ptr = ',';
    emit value_changed(*ptr);
    ptr++;
}

void keyboard::on_pushButton_38_clicked()
{
    *ptr = ' ';
    emit value_changed(*ptr);
    ptr++;
}

void keyboard::on_pushButton_35_clicked()
{
    *ptr = '.';
    emit value_changed(*ptr);
    ptr++;
}

void keyboard::on_pushButton_37_clicked()
{
    *ptr = '\0';
    emit value_changed(ENTER_CLICK);
}
