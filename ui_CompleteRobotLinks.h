/********************************************************************************
** Form generated from reading UI file 'CompleteRobotLinks.ui'
**
** Created: Tue Aug 12 00:25:55 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPLETEROBOTLINKS_H
#define UI_COMPLETEROBOTLINKS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <robotlinks.h>

QT_BEGIN_NAMESPACE

class Ui_CompleteRobotLinks
{
public:
    RobotLinks *RobotPlot;
    QPushButton *ButtonStop;
    QPushButton *ButtonRun;
    QProgressBar *progressBar;

    void setupUi(QWidget *CompleteRobotLinks)
    {
        if (CompleteRobotLinks->objectName().isEmpty())
            CompleteRobotLinks->setObjectName(QString::fromUtf8("CompleteRobotLinks"));
        CompleteRobotLinks->resize(550, 600);
        RobotPlot = new RobotLinks(CompleteRobotLinks);
        RobotPlot->setObjectName(QString::fromUtf8("RobotPlot"));
        RobotPlot->setGeometry(QRect(30, 30, 451, 461));
        ButtonStop = new QPushButton(CompleteRobotLinks);
        ButtonStop->setObjectName(QString::fromUtf8("ButtonStop"));
        ButtonStop->setGeometry(QRect(220, 510, 111, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Leelawadee"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        ButtonStop->setFont(font);
        ButtonStop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: QLinearGradient( x1: 0, y1: 0.02, x2: 0, y2: 1.2, stop: 0 #220, stop: 1 #ffffff);\n"
"    color: white;\n"
"}"));
        ButtonRun = new QPushButton(CompleteRobotLinks);
        ButtonRun->setObjectName(QString::fromUtf8("ButtonRun"));
        ButtonRun->setGeometry(QRect(70, 510, 111, 31));
        ButtonRun->setFont(font);
        ButtonRun->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #34f32d, stop: 1 #000000);\n"
"    color: white;\n"
"}"));
        progressBar = new QProgressBar(CompleteRobotLinks);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(90, 550, 261, 31));
        progressBar->setValue(24);

        retranslateUi(CompleteRobotLinks);

        QMetaObject::connectSlotsByName(CompleteRobotLinks);
    } // setupUi

    void retranslateUi(QWidget *CompleteRobotLinks)
    {
        CompleteRobotLinks->setWindowTitle(QApplication::translate("CompleteRobotLinks", "Form", 0, QApplication::UnicodeUTF8));
        ButtonStop->setText(QApplication::translate("CompleteRobotLinks", "Stop", 0, QApplication::UnicodeUTF8));
        ButtonRun->setText(QApplication::translate("CompleteRobotLinks", "Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CompleteRobotLinks: public Ui_CompleteRobotLinks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPLETEROBOTLINKS_H
