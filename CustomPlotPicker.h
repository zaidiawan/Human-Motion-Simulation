#ifndef CUSTOMPLOTPICKER_H
#define CUSTOMPLOTPICKER_H

#include <qwt_plot_picker.h>

class CustomPlotPicker : public QwtPlotPicker
{
    Q_OBJECT
public:
    explicit CustomPlotPicker(QwtPlotCanvas *Canvas = 0);
    void CustomTransform(QPoint x);
    
signals:
    
public slots:
    
};

#endif // CUSTOMPLOTPICKER_H
