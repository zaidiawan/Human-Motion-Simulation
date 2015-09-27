/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Wed Aug 6 22:21:20 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *WindowMain;
    QWidget *General;
    QLabel *LabelAngUnits;
    QComboBox *ComboAngUnits;
    QComboBox *ComboPeriodMode;
    QLabel *LabelPeriodMode;
    QLabel *LabelPeriod;
    QLineEdit *lineEditPeriod;
    QLabel *LabelInterpolation;
    QComboBox *ComboInterpolMode;
    QLabel *LabelSamples;
    QLineEdit *lineEditSamples;
    QLabel *LabelThighLength;
    QLineEdit *lineEditThighLength;
    QLabel *LabelLowerLegLength;
    QLineEdit *lineEditLowerLegLength;
    QLabel *LabelDelay;
    QLineEdit *lineEditDelay;
    QPushButton *ButtonAdamsSim;
    QLabel *LabelCycles;
    QLineEdit *lineEditCycles;
    QCommandLinkButton *CommandDelay;
    QCommandLinkButton *CommandSamples;
    QCommandLinkButton *CommandCycles;
    QCommandLinkButton *CommandThighLeng;
    QCommandLinkButton *CommandLowerLegLeng;
    QCommandLinkButton *CommandPeriod;
    QLabel *label;
    QWidget *Rleg;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *MainHLayoutLHip;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *MainHLayoutLKnee;
    QWidget *Lleg;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *MainHLayoutRHip;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *MainHLayoutRKnee;
    QWidget *REndEffect;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *MWinHLayoutLEndEffect;
    QWidget *LEndEffect;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *MWinHLayoutREndEffect;
    QTabWidget *RobotSim;
    QWidget *Simulation1;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *MainHLayoutSimulation;
    QWidget *Simulation2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1344, 733);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        WindowMain = new QTabWidget(centralWidget);
        WindowMain->setObjectName(QString::fromUtf8("WindowMain"));
        WindowMain->setGeometry(QRect(10, 0, 681, 681));
        QFont font;
        font.setFamily(QString::fromUtf8("MS PMincho"));
        font.setPointSize(11);
        WindowMain->setFont(font);
        WindowMain->setStyleSheet(QString::fromUtf8(""));
        WindowMain->setTabShape(QTabWidget::Triangular);
        General = new QWidget();
        General->setObjectName(QString::fromUtf8("General"));
        LabelAngUnits = new QLabel(General);
        LabelAngUnits->setObjectName(QString::fromUtf8("LabelAngUnits"));
        LabelAngUnits->setGeometry(QRect(70, 120, 101, 20));
        ComboAngUnits = new QComboBox(General);
        ComboAngUnits->setObjectName(QString::fromUtf8("ComboAngUnits"));
        ComboAngUnits->setGeometry(QRect(340, 120, 121, 22));
        ComboAngUnits->setLayoutDirection(Qt::LeftToRight);
        ComboAngUnits->setEditable(false);
        ComboAngUnits->setModelColumn(0);
        ComboPeriodMode = new QComboBox(General);
        ComboPeriodMode->setObjectName(QString::fromUtf8("ComboPeriodMode"));
        ComboPeriodMode->setGeometry(QRect(340, 150, 121, 22));
        ComboPeriodMode->setLayoutDirection(Qt::LeftToRight);
        LabelPeriodMode = new QLabel(General);
        LabelPeriodMode->setObjectName(QString::fromUtf8("LabelPeriodMode"));
        LabelPeriodMode->setGeometry(QRect(70, 150, 101, 20));
        LabelPeriod = new QLabel(General);
        LabelPeriod->setObjectName(QString::fromUtf8("LabelPeriod"));
        LabelPeriod->setGeometry(QRect(70, 180, 101, 20));
        lineEditPeriod = new QLineEdit(General);
        lineEditPeriod->setObjectName(QString::fromUtf8("lineEditPeriod"));
        lineEditPeriod->setGeometry(QRect(340, 180, 121, 21));
        LabelInterpolation = new QLabel(General);
        LabelInterpolation->setObjectName(QString::fromUtf8("LabelInterpolation"));
        LabelInterpolation->setGeometry(QRect(70, 210, 101, 20));
        ComboInterpolMode = new QComboBox(General);
        ComboInterpolMode->setObjectName(QString::fromUtf8("ComboInterpolMode"));
        ComboInterpolMode->setGeometry(QRect(340, 210, 121, 22));
        ComboInterpolMode->setLayoutDirection(Qt::LeftToRight);
        LabelSamples = new QLabel(General);
        LabelSamples->setObjectName(QString::fromUtf8("LabelSamples"));
        LabelSamples->setGeometry(QRect(70, 250, 151, 20));
        lineEditSamples = new QLineEdit(General);
        lineEditSamples->setObjectName(QString::fromUtf8("lineEditSamples"));
        lineEditSamples->setGeometry(QRect(340, 250, 121, 21));
        LabelThighLength = new QLabel(General);
        LabelThighLength->setObjectName(QString::fromUtf8("LabelThighLength"));
        LabelThighLength->setGeometry(QRect(70, 290, 141, 20));
        lineEditThighLength = new QLineEdit(General);
        lineEditThighLength->setObjectName(QString::fromUtf8("lineEditThighLength"));
        lineEditThighLength->setGeometry(QRect(340, 290, 121, 21));
        LabelLowerLegLength = new QLabel(General);
        LabelLowerLegLength->setObjectName(QString::fromUtf8("LabelLowerLegLength"));
        LabelLowerLegLength->setGeometry(QRect(70, 330, 181, 21));
        lineEditLowerLegLength = new QLineEdit(General);
        lineEditLowerLegLength->setObjectName(QString::fromUtf8("lineEditLowerLegLength"));
        lineEditLowerLegLength->setGeometry(QRect(340, 330, 121, 21));
        LabelDelay = new QLabel(General);
        LabelDelay->setObjectName(QString::fromUtf8("LabelDelay"));
        LabelDelay->setGeometry(QRect(70, 370, 151, 21));
        lineEditDelay = new QLineEdit(General);
        lineEditDelay->setObjectName(QString::fromUtf8("lineEditDelay"));
        lineEditDelay->setGeometry(QRect(340, 370, 121, 21));
        ButtonAdamsSim = new QPushButton(General);
        ButtonAdamsSim->setObjectName(QString::fromUtf8("ButtonAdamsSim"));
        ButtonAdamsSim->setGeometry(QRect(240, 500, 191, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Leelawadee"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        ButtonAdamsSim->setFont(font1);
        ButtonAdamsSim->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 2px;\n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"    background: QLinearGradient( x1: 0, y1: 0.02, x2: 0, y2: 1.2, stop: 0 #220, stop: 1 #ffffff);\n"
"    color: white;\n"
"}"));
        LabelCycles = new QLabel(General);
        LabelCycles->setObjectName(QString::fromUtf8("LabelCycles"));
        LabelCycles->setGeometry(QRect(70, 410, 201, 21));
        lineEditCycles = new QLineEdit(General);
        lineEditCycles->setObjectName(QString::fromUtf8("lineEditCycles"));
        lineEditCycles->setGeometry(QRect(340, 410, 121, 21));
        CommandDelay = new QCommandLinkButton(General);
        CommandDelay->setObjectName(QString::fromUtf8("CommandDelay"));
        CommandDelay->setGeometry(QRect(550, 360, 61, 41));
        CommandSamples = new QCommandLinkButton(General);
        CommandSamples->setObjectName(QString::fromUtf8("CommandSamples"));
        CommandSamples->setGeometry(QRect(550, 240, 61, 41));
        CommandCycles = new QCommandLinkButton(General);
        CommandCycles->setObjectName(QString::fromUtf8("CommandCycles"));
        CommandCycles->setGeometry(QRect(550, 400, 61, 41));
        CommandThighLeng = new QCommandLinkButton(General);
        CommandThighLeng->setObjectName(QString::fromUtf8("CommandThighLeng"));
        CommandThighLeng->setGeometry(QRect(550, 280, 61, 41));
        CommandLowerLegLeng = new QCommandLinkButton(General);
        CommandLowerLegLeng->setObjectName(QString::fromUtf8("CommandLowerLegLeng"));
        CommandLowerLegLeng->setGeometry(QRect(550, 320, 61, 41));
        CommandPeriod = new QCommandLinkButton(General);
        CommandPeriod->setObjectName(QString::fromUtf8("CommandPeriod"));
        CommandPeriod->setGeometry(QRect(550, 170, 61, 41));
        label = new QLabel(General);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 40, 211, 41));
        WindowMain->addTab(General, QString());
        Rleg = new QWidget();
        Rleg->setObjectName(QString::fromUtf8("Rleg"));
        horizontalLayoutWidget = new QWidget(Rleg);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 641, 311));
        MainHLayoutLHip = new QHBoxLayout(horizontalLayoutWidget);
        MainHLayoutLHip->setSpacing(6);
        MainHLayoutLHip->setContentsMargins(11, 11, 11, 11);
        MainHLayoutLHip->setObjectName(QString::fromUtf8("MainHLayoutLHip"));
        MainHLayoutLHip->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_2 = new QWidget(Rleg);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 330, 641, 321));
        MainHLayoutLKnee = new QHBoxLayout(horizontalLayoutWidget_2);
        MainHLayoutLKnee->setSpacing(6);
        MainHLayoutLKnee->setContentsMargins(11, 11, 11, 11);
        MainHLayoutLKnee->setObjectName(QString::fromUtf8("MainHLayoutLKnee"));
        MainHLayoutLKnee->setContentsMargins(0, 0, 0, 0);
        WindowMain->addTab(Rleg, QString());
        Lleg = new QWidget();
        Lleg->setObjectName(QString::fromUtf8("Lleg"));
        horizontalLayoutWidget_3 = new QWidget(Lleg);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 10, 641, 311));
        MainHLayoutRHip = new QHBoxLayout(horizontalLayoutWidget_3);
        MainHLayoutRHip->setSpacing(6);
        MainHLayoutRHip->setContentsMargins(11, 11, 11, 11);
        MainHLayoutRHip->setObjectName(QString::fromUtf8("MainHLayoutRHip"));
        MainHLayoutRHip->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_6 = new QWidget(Lleg);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(20, 330, 641, 321));
        MainHLayoutRKnee = new QHBoxLayout(horizontalLayoutWidget_6);
        MainHLayoutRKnee->setSpacing(6);
        MainHLayoutRKnee->setContentsMargins(11, 11, 11, 11);
        MainHLayoutRKnee->setObjectName(QString::fromUtf8("MainHLayoutRKnee"));
        MainHLayoutRKnee->setContentsMargins(0, 0, 0, 0);
        WindowMain->addTab(Lleg, QString());
        REndEffect = new QWidget();
        REndEffect->setObjectName(QString::fromUtf8("REndEffect"));
        horizontalLayoutWidget_4 = new QWidget(REndEffect);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(40, 59, 521, 561));
        MWinHLayoutLEndEffect = new QHBoxLayout(horizontalLayoutWidget_4);
        MWinHLayoutLEndEffect->setSpacing(6);
        MWinHLayoutLEndEffect->setContentsMargins(11, 11, 11, 11);
        MWinHLayoutLEndEffect->setObjectName(QString::fromUtf8("MWinHLayoutLEndEffect"));
        MWinHLayoutLEndEffect->setContentsMargins(0, 0, 0, 0);
        WindowMain->addTab(REndEffect, QString());
        LEndEffect = new QWidget();
        LEndEffect->setObjectName(QString::fromUtf8("LEndEffect"));
        horizontalLayoutWidget_7 = new QWidget(LEndEffect);
        horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(40, 30, 571, 581));
        MWinHLayoutREndEffect = new QHBoxLayout(horizontalLayoutWidget_7);
        MWinHLayoutREndEffect->setSpacing(6);
        MWinHLayoutREndEffect->setContentsMargins(11, 11, 11, 11);
        MWinHLayoutREndEffect->setObjectName(QString::fromUtf8("MWinHLayoutREndEffect"));
        MWinHLayoutREndEffect->setContentsMargins(0, 0, 0, 0);
        WindowMain->addTab(LEndEffect, QString());
        RobotSim = new QTabWidget(centralWidget);
        RobotSim->setObjectName(QString::fromUtf8("RobotSim"));
        RobotSim->setGeometry(QRect(720, 0, 611, 681));
        RobotSim->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("MS PMincho"));
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        RobotSim->setFont(font2);
        RobotSim->setStyleSheet(QString::fromUtf8(""));
        RobotSim->setTabShape(QTabWidget::Triangular);
        Simulation1 = new QWidget();
        Simulation1->setObjectName(QString::fromUtf8("Simulation1"));
        horizontalLayoutWidget_5 = new QWidget(Simulation1);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(50, 30, 521, 571));
        MainHLayoutSimulation = new QHBoxLayout(horizontalLayoutWidget_5);
        MainHLayoutSimulation->setSpacing(6);
        MainHLayoutSimulation->setContentsMargins(11, 11, 11, 11);
        MainHLayoutSimulation->setObjectName(QString::fromUtf8("MainHLayoutSimulation"));
        MainHLayoutSimulation->setContentsMargins(0, 0, 0, 0);
        RobotSim->addTab(Simulation1, QString());
        Simulation2 = new QWidget();
        Simulation2->setObjectName(QString::fromUtf8("Simulation2"));
        RobotSim->addTab(Simulation2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1344, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        WindowMain->setCurrentIndex(0);
        ComboAngUnits->setCurrentIndex(0);
        RobotSim->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        LabelAngUnits->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Angle Units</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        ComboAngUnits->clear();
        ComboAngUnits->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Radians", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Degrees", 0, QApplication::UnicodeUTF8)
        );
        ComboPeriodMode->clear();
        ComboPeriodMode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Percent", 0, QApplication::UnicodeUTF8)
        );
        LabelPeriodMode->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Period Mode</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        LabelPeriod->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Period (Sec)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEditPeriod->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        LabelInterpolation->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Interpolation</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        ComboInterpolMode->clear();
        ComboInterpolMode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Cubic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Akima", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Constantini", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "CFourier", 0, QApplication::UnicodeUTF8)
        );
        LabelSamples->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Number of Samples</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEditSamples->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        LabelThighLength->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Thigh Length(cm)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEditThighLength->setText(QApplication::translate("MainWindow", "45", 0, QApplication::UnicodeUTF8));
        LabelLowerLegLength->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Lower Leg Length(cm)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEditLowerLegLength->setText(QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8));
        LabelDelay->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Delay </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEditDelay->setText(QApplication::translate("MainWindow", "1.5", 0, QApplication::UnicodeUTF8));
        ButtonAdamsSim->setText(QApplication::translate("MainWindow", "Run Simulation in Adams", 0, QApplication::UnicodeUTF8));
        LabelCycles->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS PMincho'; font-size:12pt; color:#0000ff;\">Simulation Cycles (Adams)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEditCycles->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        CommandDelay->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        CommandSamples->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        CommandCycles->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        CommandThighLeng->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        CommandLowerLegLeng->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        CommandPeriod->setText(QApplication::translate("MainWindow", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS PMincho'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#005500;\">General Features</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        WindowMain->setTabText(WindowMain->indexOf(General), QApplication::translate("MainWindow", "General", 0, QApplication::UnicodeUTF8));
        WindowMain->setTabText(WindowMain->indexOf(Rleg), QApplication::translate("MainWindow", "Left Leg", 0, QApplication::UnicodeUTF8));
        WindowMain->setTabText(WindowMain->indexOf(Lleg), QApplication::translate("MainWindow", "Right Leg", 0, QApplication::UnicodeUTF8));
        WindowMain->setTabText(WindowMain->indexOf(REndEffect), QApplication::translate("MainWindow", "Left End Effector", 0, QApplication::UnicodeUTF8));
        WindowMain->setTabText(WindowMain->indexOf(LEndEffect), QApplication::translate("MainWindow", "Right End Effector", 0, QApplication::UnicodeUTF8));
        RobotSim->setTabText(RobotSim->indexOf(Simulation1), QApplication::translate("MainWindow", "Simulation 1", 0, QApplication::UnicodeUTF8));
        RobotSim->setTabText(RobotSim->indexOf(Simulation2), QApplication::translate("MainWindow", "Simulation 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
