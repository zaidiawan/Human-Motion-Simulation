#include <QtGui/QApplication>
#include "MainWindow.h"
#include <engine.h>
#include "constantini97.h"

int main(int argc, char *argv[])
{

    Constantini97 test;
    vector <float> x1, x2,y1,y2, xd,xdd;
    x1.push_back(0.12);
    x1.push_back(0.2);
    x1.push_back(0.8);
    x1.push_back(1.2);
    x1.push_back(1.6);
    x1.push_back(2.1);

    y1.push_back(0.12);
    y1.push_back(-0.2);
    y1.push_back(0.8);
    y1.push_back(1.9);
    y1.push_back(-0.8);
    y1.push_back(2.0);

    x2.push_back(6.2);
    x2.push_back(6.12);
    x2.push_back(6.8);
    x2.push_back(7.2);
    x2.push_back(7.6);
    x2.push_back(9.1);

    //test.calc(x1, y1, x2, y2, 3, 6);
    test.calc_fourier(x1, y1, x2, y2, xd ,xdd, 3, 6,20);
    //qDebug()<<y2.at(0);
    //qDebug()<<y2.at(1);
    //qDebug()<<y2.at(2);
    //qDebug()<<y2.at(3);
    //qDebug()<<y2.at(4);
    //qDebug()<<y2.at(5);


    Engine * m_matlabEngine;
    m_matlabEngine=engOpen("\0");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
