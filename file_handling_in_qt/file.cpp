#include "file.h"

file::file()
{
    QString folder_path;
    folder_path = "/home/apaul/Documents/qmkdir/example/";
    QString file_name = "test.txt";
    QFile test_file(folder_path+file_name);
      if(!test_file.exists())
         qDebug() << "file doesn't exist";
     //else
         test_file.open(QIODevice::ReadWrite);
     while(!test_file.atEnd())
         qDebug() << test_file.readLine();
     QTextStream stream(&test_file);
     stream << "create Document" << endl  ;
     qDebug() << stream.read(5);
     test_file.close();
}

file::~file()
{

}

