/********************************************************************************
** Form generated from reading UI file 'widgetbox.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETBOX_H
#define UI_WIDGETBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetbox
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *widget1;
    QPushButton *widget2;
    QPushButton *widget3;
    QPushButton *widget4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *widgetbox)
    {
        if (widgetbox->objectName().isEmpty())
            widgetbox->setObjectName(QStringLiteral("widgetbox"));
        widgetbox->resize(1366, 768);
        centralWidget = new QWidget(widgetbox);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 260, 1321, 421));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(horizontalLayoutWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 100, 701, 61));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget1 = new QPushButton(widget);
        widget1->setObjectName(QStringLiteral("widget1"));

        horizontalLayout_2->addWidget(widget1);

        widget2 = new QPushButton(widget);
        widget2->setObjectName(QStringLiteral("widget2"));

        horizontalLayout_2->addWidget(widget2);

        widget3 = new QPushButton(widget);
        widget3->setObjectName(QStringLiteral("widget3"));

        horizontalLayout_2->addWidget(widget3);

        widget4 = new QPushButton(widget);
        widget4->setObjectName(QStringLiteral("widget4"));

        horizontalLayout_2->addWidget(widget4);

        widgetbox->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(widgetbox);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 20));
        widgetbox->setMenuBar(menuBar);
        mainToolBar = new QToolBar(widgetbox);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        widgetbox->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(widgetbox);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        widgetbox->setStatusBar(statusBar);

        retranslateUi(widgetbox);

        QMetaObject::connectSlotsByName(widgetbox);
    } // setupUi

    void retranslateUi(QMainWindow *widgetbox)
    {
        widgetbox->setWindowTitle(QApplication::translate("widgetbox", "widgetbox", 0));
        widget1->setText(QApplication::translate("widgetbox", "widget1", 0));
        widget2->setText(QApplication::translate("widgetbox", "widget2", 0));
        widget3->setText(QApplication::translate("widgetbox", "widget3", 0));
        widget4->setText(QApplication::translate("widgetbox", "widget4", 0));
    } // retranslateUi

};

namespace Ui {
    class widgetbox: public Ui_widgetbox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETBOX_H
