#include "CustomPlotPicker.h"
#include <QDebug>

CustomPlotPicker::CustomPlotPicker(QwtPlotCanvas *Canvas) :
    QwtPlotPicker(Canvas)
{
}
void CustomPlotPicker::CustomTransform(QPoint x)
{
    //move(x);        `
}
