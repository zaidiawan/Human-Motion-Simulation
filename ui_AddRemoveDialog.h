/********************************************************************************
** Form generated from reading UI file 'AddRemoveDialog.ui'
**
** Created: Wed Jun 11 15:26:04 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDREMOVEDIALOG_H
#define UI_ADDREMOVEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddRemoveDialog
{
public:
    QLineEdit *TextTime;
    QLabel *LabelTimeValue;
    QLabel *LabelAngleValue;
    QLineEdit *TextAngle;
    QPushButton *ButtonAdd;
    QPushButton *ButtonCancel;
    QListView *ListMarkers;
    QPushButton *ButtonRemove;
    QCheckBox *checkBoxMarkers;

    void setupUi(QDialog *AddRemoveDialog)
    {
        if (AddRemoveDialog->objectName().isEmpty())
            AddRemoveDialog->setObjectName(QString::fromUtf8("AddRemoveDialog"));
        AddRemoveDialog->resize(400, 299);
        TextTime = new QLineEdit(AddRemoveDialog);
        TextTime->setObjectName(QString::fromUtf8("TextTime"));
        TextTime->setGeometry(QRect(230, 60, 61, 20));
        LabelTimeValue = new QLabel(AddRemoveDialog);
        LabelTimeValue->setObjectName(QString::fromUtf8("LabelTimeValue"));
        LabelTimeValue->setGeometry(QRect(90, 60, 81, 20));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        LabelTimeValue->setFont(font);
        LabelAngleValue = new QLabel(AddRemoveDialog);
        LabelAngleValue->setObjectName(QString::fromUtf8("LabelAngleValue"));
        LabelAngleValue->setGeometry(QRect(90, 90, 81, 20));
        LabelAngleValue->setFont(font);
        TextAngle = new QLineEdit(AddRemoveDialog);
        TextAngle->setObjectName(QString::fromUtf8("TextAngle"));
        TextAngle->setGeometry(QRect(230, 90, 61, 20));
        ButtonAdd = new QPushButton(AddRemoveDialog);
        ButtonAdd->setObjectName(QString::fromUtf8("ButtonAdd"));
        ButtonAdd->setGeometry(QRect(40, 260, 75, 23));
        ButtonCancel = new QPushButton(AddRemoveDialog);
        ButtonCancel->setObjectName(QString::fromUtf8("ButtonCancel"));
        ButtonCancel->setGeometry(QRect(300, 260, 75, 23));
        ListMarkers = new QListView(AddRemoveDialog);
        ListMarkers->setObjectName(QString::fromUtf8("ListMarkers"));
        ListMarkers->setGeometry(QRect(230, 120, 61, 121));
        ButtonRemove = new QPushButton(AddRemoveDialog);
        ButtonRemove->setObjectName(QString::fromUtf8("ButtonRemove"));
        ButtonRemove->setGeometry(QRect(160, 260, 75, 23));
        checkBoxMarkers = new QCheckBox(AddRemoveDialog);
        checkBoxMarkers->setObjectName(QString::fromUtf8("checkBoxMarkers"));
        checkBoxMarkers->setGeometry(QRect(90, 150, 81, 21));

        retranslateUi(AddRemoveDialog);

        QMetaObject::connectSlotsByName(AddRemoveDialog);
    } // setupUi

    void retranslateUi(QDialog *AddRemoveDialog)
    {
        AddRemoveDialog->setWindowTitle(QApplication::translate("AddRemoveDialog", "Add/Remove Markers", 0, QApplication::UnicodeUTF8));
        TextTime->setText(QApplication::translate("AddRemoveDialog", "2.3", 0, QApplication::UnicodeUTF8));
        LabelTimeValue->setText(QApplication::translate("AddRemoveDialog", "Time Value", 0, QApplication::UnicodeUTF8));
        LabelAngleValue->setText(QApplication::translate("AddRemoveDialog", "Angle Value", 0, QApplication::UnicodeUTF8));
        TextAngle->setText(QApplication::translate("AddRemoveDialog", "0.4", 0, QApplication::UnicodeUTF8));
        ButtonAdd->setText(QApplication::translate("AddRemoveDialog", "Add", 0, QApplication::UnicodeUTF8));
        ButtonCancel->setText(QApplication::translate("AddRemoveDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        ButtonRemove->setText(QApplication::translate("AddRemoveDialog", "Remove", 0, QApplication::UnicodeUTF8));
        checkBoxMarkers->setText(QApplication::translate("AddRemoveDialog", "Markers List", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddRemoveDialog: public Ui_AddRemoveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDREMOVEDIALOG_H
