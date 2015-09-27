#ifndef ENDEFFECTORPLOT_H
#define ENDEFFECTORPLOT_H
#include <qwt_plot.h>
#include "TypeDefs.h"
#include <vector>
#include "TypeDefs.h"
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>




class EndEffectorPlot : public QwtPlot
{

public:
    explicit EndEffectorPlot(QWidget *parent = 0);
    
signals:


public slots:

public:

    friend class CompleteEndEffectPlot;

    QwtSymbol *m_pSymbolRect, *m_pSymbolRect2;
    QwtPlotMarker *m_pMarkerArray;
    QwtPlotGrid *m_pGrid;
    QwtPlotCurve *m_pCurveJoint;

    uiPlot m_uiSamplesPlot , m_uiMarkersNumber;
    QString m_qsTitle;

    bool ImportSamples ( std::vector <double> vHipSamples , std::vector <double> vKneeSamples);
    bool ImportMarkers (std::vector <double> vXMarkers , std::vector <double> vYMarkers);
    bool ExportPositions(double dThighLeng, double dLegLeng, std::vector <double> &vOutXPositions , std::vector <double> &vOutYPositions, std::vector <double> &vInHipAngles , std::vector <double> &vInKneeAngles);
    bool PlotCurve(std::vector <double> vXPositions, std::vector <double> vYPositions);

private:



    std::vector <double> m_vHipSamples, m_vKneeSamples, m_vHipMarkers, m_vKneeMarkers;



};

#endif // ENDEFFECTORPLOT_H
