#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QMainWindow>
#include <QTimer>
#include <QPalette>
#include <QConicalGradient>
#include <QSplashScreen>
#include <QPainter>
#include <QLabel>

class mySplashScreen:public QSplashScreen
{
      Q_OBJECT
      public:
        mySplashScreen():
        QSplashScreen(), m_pDrawAngle(0)
        {
              timer = new QTimer();
              m_pPalette = new QPalette();
              m_pConicalGradient = new QConicalGradient();

             font1 = new QFont("Courier New");
             font1->setItalic(true);
             font1->setPixelSize(70);

             font2 = new QFont("Courier New");
             font2->setPixelSize(29);

              timer->start(10);
              connect(timer,SIGNAL(timeout()),this,SLOT(animateBackground()));
        };
        ~mySplashScreen(){};

private:
      void paintEvent(QPaintEvent* event)
      {
             QPainter painter(this);

             painter.setPen(Qt::black);
             painter.setFont(*font1);
             painter.drawText(190,70,"BUS");
             painter.drawText(60,140,"PASSENGER");
             painter.drawText(10,210,"INFORMATION");
             painter.drawText(120,280,"SYSTEM");

             painter.setFont(*font2);
             painter.drawText(10,490,"Mfd. By : A Paul Instruments");
      };

private slots:
      void animateBackground()
      {
            m_pConicalGradient->setColorAt(0.5, Qt::gray);
            m_pConicalGradient->setColorAt(1, Qt::white);
            m_pConicalGradient->setAngle(m_pDrawAngle);
            m_pConicalGradient->setCenter(width()/2,height()/2);

            m_pBrush = new  QBrush(*m_pConicalGradient);
            m_pPalette->setBrush(QPalette::Window,*m_pBrush);
            setPalette(*m_pPalette);

            m_pDrawAngle+=2;
            if(m_pDrawAngle>360)
            {
              m_pDrawAngle = 0;
        }
      };

private:
      QTimer* timer;
      QPalette* m_pPalette;
      QConicalGradient* m_pConicalGradient;
      QBrush* m_pBrush;
      QLabel* m_pLabel;
      QFont* font1;
      QFont* font2;
      int m_pDrawAngle;
};

#endif // SPLASHSCREEN_H
