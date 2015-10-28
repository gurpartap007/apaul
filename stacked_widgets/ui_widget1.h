/********************************************************************************
** Form generated from reading UI file 'widget1.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET1_H
#define UI_WIDGET1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget1
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *widget1)
    {
        if (widget1->objectName().isEmpty())
            widget1->setObjectName(QStringLiteral("widget1"));
        widget1->resize(1319, 419);
        horizontalLayoutWidget = new QWidget(widget1);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1321, 514));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../apaul/Downloads/alarm.png")));

        horizontalLayout->addWidget(label);


        retranslateUi(widget1);

        QMetaObject::connectSlotsByName(widget1);
    } // setupUi

    void retranslateUi(QWidget *widget1)
    {
        widget1->setWindowTitle(QApplication::translate("widget1", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class widget1: public Ui_widget1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET1_H
