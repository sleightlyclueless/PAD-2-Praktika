/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mainwindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_0;
    QPushButton *pushButton_0;
    QLineEdit *input_0;
    QLabel *L_input_0;
    QWidget *page_2;
    QLineEdit *input_2;
    QLabel *L_input_2;
    QPushButton *pushButton_2;
    QWidget *page_3;
    QLineEdit *input_3;
    QLabel *L_input_3;
    QPushButton *pushButton_3;
    QWidget *page_7;
    QLineEdit *input_7;
    QLabel *L_input_7;
    QPushButton *pushButton_7;
    QWidget *page_8;
    QLineEdit *input_8;
    QLabel *L_input_8;
    QPushButton *pushButton_8;
    QWidget *page_9;
    QLineEdit *input_9;
    QLabel *L_input_9;
    QPushButton *pushButton_9;
    QLabel *L_out;
    QPlainTextEdit *instr;
    QLabel *L_instr;
    QPlainTextEdit *output;

    void setupUi(QDialog *Mainwindow)
    {
        if (Mainwindow->objectName().isEmpty())
            Mainwindow->setObjectName(QString::fromUtf8("Mainwindow"));
        Mainwindow->resize(727, 589);
        stackedWidget = new QStackedWidget(Mainwindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 470, 711, 111));
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setMaximumSize(QSize(731, 16777215));
        page_0 = new QWidget();
        page_0->setObjectName(QString::fromUtf8("page_0"));
        pushButton_0 = new QPushButton(page_0);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setGeometry(QRect(580, 40, 80, 21));
        input_0 = new QLineEdit(page_0);
        input_0->setObjectName(QString::fromUtf8("input_0"));
        input_0->setGeometry(QRect(120, 40, 113, 21));
        L_input_0 = new QLabel(page_0);
        L_input_0->setObjectName(QString::fromUtf8("L_input_0"));
        L_input_0->setGeometry(QRect(30, 40, 91, 16));
        stackedWidget->addWidget(page_0);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        input_2 = new QLineEdit(page_2);
        input_2->setObjectName(QString::fromUtf8("input_2"));
        input_2->setGeometry(QRect(120, 40, 113, 21));
        L_input_2 = new QLabel(page_2);
        L_input_2->setObjectName(QString::fromUtf8("L_input_2"));
        L_input_2->setGeometry(QRect(30, 40, 91, 16));
        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(580, 40, 80, 21));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        input_3 = new QLineEdit(page_3);
        input_3->setObjectName(QString::fromUtf8("input_3"));
        input_3->setGeometry(QRect(120, 40, 113, 21));
        L_input_3 = new QLabel(page_3);
        L_input_3->setObjectName(QString::fromUtf8("L_input_3"));
        L_input_3->setGeometry(QRect(30, 30, 91, 41));
        pushButton_3 = new QPushButton(page_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(580, 40, 80, 21));
        stackedWidget->addWidget(page_3);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        input_7 = new QLineEdit(page_7);
        input_7->setObjectName(QString::fromUtf8("input_7"));
        input_7->setGeometry(QRect(120, 40, 113, 21));
        L_input_7 = new QLabel(page_7);
        L_input_7->setObjectName(QString::fromUtf8("L_input_7"));
        L_input_7->setGeometry(QRect(30, 30, 91, 41));
        pushButton_7 = new QPushButton(page_7);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(580, 40, 80, 21));
        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        input_8 = new QLineEdit(page_8);
        input_8->setObjectName(QString::fromUtf8("input_8"));
        input_8->setGeometry(QRect(120, 40, 113, 21));
        L_input_8 = new QLabel(page_8);
        L_input_8->setObjectName(QString::fromUtf8("L_input_8"));
        L_input_8->setGeometry(QRect(30, 40, 91, 16));
        pushButton_8 = new QPushButton(page_8);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(580, 40, 80, 21));
        stackedWidget->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        input_9 = new QLineEdit(page_9);
        input_9->setObjectName(QString::fromUtf8("input_9"));
        input_9->setGeometry(QRect(120, 40, 113, 21));
        L_input_9 = new QLabel(page_9);
        L_input_9->setObjectName(QString::fromUtf8("L_input_9"));
        L_input_9->setGeometry(QRect(30, 40, 91, 16));
        pushButton_9 = new QPushButton(page_9);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(580, 40, 80, 21));
        stackedWidget->addWidget(page_9);
        L_out = new QLabel(Mainwindow);
        L_out->setObjectName(QString::fromUtf8("L_out"));
        L_out->setGeometry(QRect(40, 270, 441, 21));
        instr = new QPlainTextEdit(Mainwindow);
        instr->setObjectName(QString::fromUtf8("instr"));
        instr->setGeometry(QRect(40, 30, 631, 211));
        L_instr = new QLabel(Mainwindow);
        L_instr->setObjectName(QString::fromUtf8("L_instr"));
        L_instr->setGeometry(QRect(40, 10, 261, 21));
        output = new QPlainTextEdit(Mainwindow);
        output->setObjectName(QString::fromUtf8("output"));
        output->setGeometry(QRect(40, 290, 631, 161));
        output->raise();
        instr->raise();
        L_instr->raise();
        stackedWidget->raise();
        L_out->raise();

        retranslateUi(Mainwindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Mainwindow);
    } // setupUi

    void retranslateUi(QDialog *Mainwindow)
    {
        Mainwindow->setWindowTitle(QCoreApplication::translate("Mainwindow", "Mainwindow", nullptr));
        pushButton_0->setText(QCoreApplication::translate("Mainwindow", "Submit", nullptr));
        L_input_0->setText(QCoreApplication::translate("Mainwindow", "Choose Option", nullptr));
        L_input_2->setText(QCoreApplication::translate("Mainwindow", "Add a movie:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Mainwindow", "Submit", nullptr));
        L_input_3->setText(QCoreApplication::translate("Mainwindow", "Enter Number of \n"
"movie to remove:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Mainwindow", "Submit", nullptr));
        L_input_7->setText(QCoreApplication::translate("Mainwindow", "Play movie at \n"
"position:", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Mainwindow", "Submit", nullptr));
        L_input_8->setText(QCoreApplication::translate("Mainwindow", "Option 8:", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Mainwindow", "Submit", nullptr));
        L_input_9->setText(QCoreApplication::translate("Mainwindow", "Save to file:", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Mainwindow", "Submit", nullptr));
        L_out->setText(QCoreApplication::translate("Mainwindow", "Output", nullptr));
        L_instr->setText(QCoreApplication::translate("Mainwindow", "Instructions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mainwindow: public Ui_Mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
