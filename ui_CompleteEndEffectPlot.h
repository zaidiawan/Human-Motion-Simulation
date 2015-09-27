/********************************************************************************
** Form generated from reading UI file 'CompleteEndEffectPlot.ui'
**
** Created: Tue Aug 12 00:25:55 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPLETEENDEFFECTPLOT_H
#define UI_COMPLETEENDEFFECTPLOT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include <endeffectorplot.h>

QT_BEGIN_NAMESPACE

class Ui_CompleteEndEffectPlot
{
public:
    EndEffectorPlot *EndEffectPlot;

    void setupUi(QWidget *CompleteEndEffectPlot)
    {
        if (CompleteEndEffectPlot->objectName().isEmpty())
            CompleteEndEffectPlot->setObjectName(QString::fromUtf8("CompleteEndEffectPlot"));
        CompleteEndEffectPlot->resize(538, 451);
        EndEffectPlot = new EndEffectorPlot(CompleteEndEffectPlot);
        EndEffectPlot->setObjectName(QString::fromUtf8("EndEffectPlot"));
        EndEffectPlot->setGeometry(QRect(20, 60, 491, 321));

        retranslateUi(CompleteEndEffectPlot);

        QMetaObject::connectSlotsByName(CompleteEndEffectPlot);
    } // setupUi

    void retranslateUi(QWidget *CompleteEndEffectPlot)
    {
        CompleteEndEffectPlot->setWindowTitle(QApplication::translate("CompleteEndEffectPlot", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CompleteEndEffectPlot: public Ui_CompleteEndEffectPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPLETEENDEFFECTPLOT_H
