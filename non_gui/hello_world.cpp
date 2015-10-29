#include<QApplication>
#include<QLabel>
 
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QLabel    label;
    label.setText("Hello World");
    label.show();
    a.exec();
}
