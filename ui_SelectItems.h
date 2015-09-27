/********************************************************************************
** Form generated from reading UI file 'SelectItems.ui'
**
** Created: Sun Aug 3 13:11:01 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTITEMS_H
#define UI_SELECTITEMS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SelectItems
{
public:
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QCheckBox *checkBoxSamples;
    QCheckBox *checkBoxPeriod;
    QCheckBox *checkBoxItType;
    QCheckBox *checkBoxAngUnits;
    QCheckBox *checkBoxPeriodMode;
    QCheckBox *checkBoxVals;
    QRadioButton *radioButtonAdams;
    QRadioButton *radioButtonNormal;

    void setupUi(QDialog *SelectItems)
    {
        if (SelectItems->objectName().isEmpty())
            SelectItems->setObjectName(QString::fromUtf8("SelectItems"));
        SelectItems->resize(520, 300);
        ButtonOK = new QPushButton(SelectItems);
        ButtonOK->setObjectName(QString::fromUtf8("ButtonOK"));
        ButtonOK->setGeometry(QRect(150, 210, 75, 23));
        ButtonCancel = new QPushButton(SelectItems);
        ButtonCancel->setObjectName(QString::fromUtf8("ButtonCancel"));
        ButtonCancel->setGeometry(QRect(270, 210, 75, 23));
        checkBoxSamples = new QCheckBox(SelectItems);
        checkBoxSamples->setObjectName(QString::fromUtf8("checkBoxSamples"));
        checkBoxSamples->setGeometry(QRect(220, 40, 70, 17));
        checkBoxPeriod = new QCheckBox(SelectItems);
        checkBoxPeriod->setObjectName(QString::fromUtf8("checkBoxPeriod"));
        checkBoxPeriod->setGeometry(QRect(220, 60, 70, 17));
        checkBoxItType = new QCheckBox(SelectItems);
        checkBoxItType->setObjectName(QString::fromUtf8("checkBoxItType"));
        checkBoxItType->setGeometry(QRect(220, 80, 101, 17));
        checkBoxAngUnits = new QCheckBox(SelectItems);
        checkBoxAngUnits->setObjectName(QString::fromUtf8("checkBoxAngUnits"));
        checkBoxAngUnits->setGeometry(QRect(220, 100, 70, 17));
        checkBoxPeriodMode = new QCheckBox(SelectItems);
        checkBoxPeriodMode->setObjectName(QString::fromUtf8("checkBoxPeriodMode"));
        checkBoxPeriodMode->setGeometry(QRect(220, 120, 81, 17));
        checkBoxVals = new QCheckBox(SelectItems);
        checkBoxVals->setObjectName(QString::fromUtf8("checkBoxVals"));
        checkBoxVals->setGeometry(QRect(220, 20, 70, 17));
        radioButtonAdams = new QRadioButton(SelectItems);
        radioButtonAdams->setObjectName(QString::fromUtf8("radioButtonAdams"));
        radioButtonAdams->setGeometry(QRect(300, 150, 121, 31));
        radioButtonNormal = new QRadioButton(SelectItems);
        radioButtonNormal->setObjectName(QString::fromUtf8("radioButtonNormal"));
        radioButtonNormal->setGeometry(QRect(110, 150, 121, 31));

        retranslateUi(SelectItems);

        QMetaObject::connectSlotsByName(SelectItems);
    } // setupUi

    void retranslateUi(QDialog *SelectItems)
    {
        SelectItems->setWindowTitle(QApplication::translate("SelectItems", "Select Export Parameters", 0, QApplication::UnicodeUTF8));
        ButtonOK->setText(QApplication::translate("SelectItems", "OK", 0, QApplication::UnicodeUTF8));
        ButtonCancel->setText(QApplication::translate("SelectItems", "Cancel", 0, QApplication::UnicodeUTF8));
        checkBoxSamples->setText(QApplication::translate("SelectItems", "Samples", 0, QApplication::UnicodeUTF8));
        checkBoxPeriod->setText(QApplication::translate("SelectItems", "Period", 0, QApplication::UnicodeUTF8));
        checkBoxItType->setText(QApplication::translate("SelectItems", "InterpolType", 0, QApplication::UnicodeUTF8));
        checkBoxAngUnits->setText(QApplication::translate("SelectItems", "AngleUnits", 0, QApplication::UnicodeUTF8));
        checkBoxPeriodMode->setText(QApplication::translate("SelectItems", "PeriodMode", 0, QApplication::UnicodeUTF8));
        checkBoxVals->setText(QApplication::translate("SelectItems", "Values", 0, QApplication::UnicodeUTF8));
        radioButtonAdams->setText(QApplication::translate("SelectItems", "Export to Adams", 0, QApplication::UnicodeUTF8));
        radioButtonNormal->setText(QApplication::translate("SelectItems", "Normal Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectItems: public Ui_SelectItems {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTITEMS_H
