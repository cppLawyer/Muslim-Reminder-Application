/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *rootWD;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *imagePr;
    QLabel *CurrentPrayer;
    QLabel *label_6;
    QLabel *nextPrayer;
    QLabel *timeTogo;
    QLabel *label_3;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(786, 638);
        gui->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 57, 89);\n"
"border-color: rgb(42, 57, 89);"));
        verticalLayout_3 = new QVBoxLayout(gui);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget = new QWidget(gui);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rootWD = new QWidget(widget);
        rootWD->setObjectName(QString::fromUtf8("rootWD"));
        rootWD->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(rootWD);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(rootWD);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_5);

        imagePr = new QLabel(rootWD);
        imagePr->setObjectName(QString::fromUtf8("imagePr"));
        imagePr->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(imagePr);

        CurrentPrayer = new QLabel(rootWD);
        CurrentPrayer->setObjectName(QString::fromUtf8("CurrentPrayer"));
        CurrentPrayer->setStyleSheet(QString::fromUtf8("font: 70pt \"OCR A Extended\";\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(CurrentPrayer, 0, Qt::AlignHCenter|Qt::AlignTop);

        label_6 = new QLabel(rootWD);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        nextPrayer = new QLabel(rootWD);
        nextPrayer->setObjectName(QString::fromUtf8("nextPrayer"));
        nextPrayer->setStyleSheet(QString::fromUtf8("font: 50pt \"OCR A Extended\";\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(nextPrayer, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        timeTogo = new QLabel(rootWD);
        timeTogo->setObjectName(QString::fromUtf8("timeTogo"));
        timeTogo->setStyleSheet(QString::fromUtf8("font: 19pt \"OCR A Extended\";\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(timeTogo, 0, Qt::AlignHCenter|Qt::AlignBottom);

        label_3 = new QLabel(rootWD);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_3);


        verticalLayout_2->addWidget(rootWD, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout_3->addWidget(widget);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "Muslim Reminder", nullptr));
        label_5->setText(QString());
        imagePr->setText(QString());
        CurrentPrayer->setText(QString());
        label_6->setText(QString());
        nextPrayer->setText(QString());
        timeTogo->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
