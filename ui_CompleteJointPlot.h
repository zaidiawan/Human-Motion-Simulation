/********************************************************************************
** Form generated from reading UI file 'CompleteJointPlot.ui'
**
** Created: Tue Aug 12 00:25:55 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPLETEJOINTPLOT_H
#define UI_COMPLETEJOINTPLOT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "jointplot.h"

QT_BEGIN_NAMESPACE

class Ui_CompleteJointPlot
{
public:
    JointPlot *WidgetPlot;
    QPushButton *AddOrRemoveMarker;
    QPushButton *ButtonImportCurve;
    QPushButton *ButtonImportMarkers;
    QPushButton *ButtonExportMarkers;
    QPushButton *ButtonExportCurve;
    QPushButton *ButtonAddRemove;
    QPushButton *ButtonMove;
    QPushButton *ButtonNoChange;
    QCheckBox *CheckBoxDelay;

    void setupUi(QWidget *CompleteJointPlot)
    {
        if (CompleteJointPlot->objectName().isEmpty())
            CompleteJointPlot->setObjectName(QString::fromUtf8("CompleteJointPlot"));
        CompleteJointPlot->resize(635, 314);
        CompleteJointPlot->setStyleSheet(QString::fromUtf8(""));
        WidgetPlot = new JointPlot(CompleteJointPlot);
        WidgetPlot->setObjectName(QString::fromUtf8("WidgetPlot"));
        WidgetPlot->setGeometry(QRect(30, 30, 451, 221));
        AddOrRemoveMarker = new QPushButton(CompleteJointPlot);
        AddOrRemoveMarker->setObjectName(QString::fromUtf8("AddOrRemoveMarker"));
        AddOrRemoveMarker->setGeometry(QRect(510, 30, 111, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Leelawadee"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        AddOrRemoveMarker->setFont(font);
        AddOrRemoveMarker->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}"));
        ButtonImportCurve = new QPushButton(CompleteJointPlot);
        ButtonImportCurve->setObjectName(QString::fromUtf8("ButtonImportCurve"));
        ButtonImportCurve->setGeometry(QRect(510, 70, 111, 31));
        ButtonImportCurve->setFont(font);
        ButtonImportCurve->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}\n"
"QPushButton {\n"
"background-image:url(:/new/prefix1/Import.png)\n"
"}"));
        ButtonImportMarkers = new QPushButton(CompleteJointPlot);
        ButtonImportMarkers->setObjectName(QString::fromUtf8("ButtonImportMarkers"));
        ButtonImportMarkers->setGeometry(QRect(510, 150, 111, 31));
        ButtonImportMarkers->setFont(font);
        ButtonImportMarkers->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}"));
        ButtonExportMarkers = new QPushButton(CompleteJointPlot);
        ButtonExportMarkers->setObjectName(QString::fromUtf8("ButtonExportMarkers"));
        ButtonExportMarkers->setGeometry(QRect(510, 190, 111, 31));
        ButtonExportMarkers->setFont(font);
        ButtonExportMarkers->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}"));
        ButtonExportCurve = new QPushButton(CompleteJointPlot);
        ButtonExportCurve->setObjectName(QString::fromUtf8("ButtonExportCurve"));
        ButtonExportCurve->setGeometry(QRect(510, 110, 111, 31));
        ButtonExportCurve->setFont(font);
        ButtonExportCurve->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}\n"
""));
        ButtonAddRemove = new QPushButton(CompleteJointPlot);
        ButtonAddRemove->setObjectName(QString::fromUtf8("ButtonAddRemove"));
        ButtonAddRemove->setGeometry(QRect(70, 260, 111, 31));
        ButtonAddRemove->setFont(font);
        ButtonAddRemove->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}"));
        ButtonMove = new QPushButton(CompleteJointPlot);
        ButtonMove->setObjectName(QString::fromUtf8("ButtonMove"));
        ButtonMove->setGeometry(QRect(200, 260, 111, 31));
        ButtonMove->setFont(font);
        ButtonMove->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}"));
        ButtonNoChange = new QPushButton(CompleteJointPlot);
        ButtonNoChange->setObjectName(QString::fromUtf8("ButtonNoChange"));
        ButtonNoChange->setGeometry(QRect(330, 260, 111, 31));
        ButtonNoChange->setFont(font);
        ButtonNoChange->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightgray;\n"
"    color: black;\n"
"}"));
        CheckBoxDelay = new QCheckBox(CompleteJointPlot);
        CheckBoxDelay->setObjectName(QString::fromUtf8("CheckBoxDelay"));
        CheckBoxDelay->setGeometry(QRect(510, 230, 111, 31));
        CheckBoxDelay->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: lightblue;\n"
"    color: black;\n"
"}"));

        retranslateUi(CompleteJointPlot);

        QMetaObject::connectSlotsByName(CompleteJointPlot);
    } // setupUi

    void retranslateUi(QWidget *CompleteJointPlot)
    {
        CompleteJointPlot->setWindowTitle(QApplication::translate("CompleteJointPlot", "Form", 0, QApplication::UnicodeUTF8));
        AddOrRemoveMarker->setText(QApplication::translate("CompleteJointPlot", "+ / -  Marker", 0, QApplication::UnicodeUTF8));
        ButtonImportCurve->setText(QApplication::translate("CompleteJointPlot", "Import Curve", 0, QApplication::UnicodeUTF8));
        ButtonImportMarkers->setText(QApplication::translate("CompleteJointPlot", "Import Markers", 0, QApplication::UnicodeUTF8));
        ButtonExportMarkers->setText(QApplication::translate("CompleteJointPlot", "Export Markers", 0, QApplication::UnicodeUTF8));
        ButtonExportCurve->setText(QApplication::translate("CompleteJointPlot", "Export Curve", 0, QApplication::UnicodeUTF8));
        ButtonAddRemove->setText(QApplication::translate("CompleteJointPlot", "Add / Remove", 0, QApplication::UnicodeUTF8));
        ButtonMove->setText(QApplication::translate("CompleteJointPlot", "Move", 0, QApplication::UnicodeUTF8));
        ButtonNoChange->setText(QApplication::translate("CompleteJointPlot", "No Change", 0, QApplication::UnicodeUTF8));
        CheckBoxDelay->setText(QApplication::translate("CompleteJointPlot", "Show with Delay", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CompleteJointPlot: public Ui_CompleteJointPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPLETEJOINTPLOT_H
