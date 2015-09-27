#include "EndEffectorPlot.h"
#include <qwt_plot_picker.h>

EndEffectorPlot::EndEffectorPlot(QWidget *parent) :
    QwtPlot(parent)
{

    m_uiMarkersNumber = 0;
    m_pMarkerArray = new QwtPlotMarker[100]; // Creating MarkerArray

    this->setCanvasBackground(QColor(200,200,230)); // Setting canvas Background

    m_pGrid = new QwtPlotGrid;  //  Creating Grid
    m_pGrid->setMajPen( QPen( Qt::white, 0, Qt::DotLine ) );
    m_pGrid->attach(this);

    m_pSymbolRect = new QwtSymbol;  // Creating Symbol
    m_pSymbolRect->setStyle(QwtSymbol::Rect);
    m_pSymbolRect->setSize(10.0, 10.0);
    m_pSymbolRect->setBrush(Qt::red);

    m_pSymbolRect2 = new QwtSymbol;  // Creating Symbol
    m_pSymbolRect2->setStyle(QwtSymbol::Rect);
    m_pSymbolRect2->setSize(10.0, 10.0);
    m_pSymbolRect2->setBrush(Qt::green);

    m_pCurveJoint = new QwtPlotCurve(); // Creating Curve
    m_pCurveJoint->setStyle(QwtPlotCurve::Lines);
    m_pCurveJoint->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_pCurveJoint->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_pCurveJoint->setPen(QPen(Qt::black, 2.5));

    QwtPlotPicker* qppPlotPicker = new QwtPlotPicker(this->xBottom, this->yLeft, QwtPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas()); // Creating PlotPicker for displaying coordinates on Canvas
}

bool EndEffectorPlot::ImportSamples ( std::vector <double> vHipSamples , std::vector <double> vKneeSamples)
{
    m_vHipSamples = vHipSamples;
    m_vKneeSamples = vKneeSamples;

    return true;
}

bool EndEffectorPlot::ExportPositions(double dThighLeng, double dLegLeng, std::vector <double> &vOutXPositions , std::vector <double> &vOutYPositions, std::vector <double> &vInHipAngles , std::vector <double> &vInKneeAngles)
{

double dThighX, dThighY, dLegX, dLegY;
vOutXPositions.clear();
vOutYPositions.clear();

// x position of end effector = thigh_length*sin(hipangle)+lower_leg_length*sin(hipangle+kneeangle)
// y position of end effector  = thigh_length*cos(hipangle )+ lower_leg_length*cos(hipange+kneeangle)


for(unsigned int uiSample = 0; uiSample < vInHipAngles.size(); uiSample++) {

    dThighX = dThighLeng * sin(vInHipAngles.at(uiSample));
    dThighY = dThighLeng * cos(vInHipAngles.at(uiSample));

    dLegX = dLegLeng*sin( vInHipAngles.at(uiSample) + vInKneeAngles.at(uiSample) );
    dLegY = dLegLeng*cos( vInHipAngles.at(uiSample) + vInKneeAngles.at(uiSample) );

    vOutXPositions.push_back(dThighX + dLegX);
    vOutYPositions.push_back((dThighLeng + dLegLeng) - (dThighY + dLegY));
    //qDebug()<<vXPositions.at(uiSample);
    return true;

    }
}

bool EndEffectorPlot::ImportMarkers(std::vector <double> vXMarkers, std::vector <double> vYMarkers)
{
    m_vHipMarkers = vXMarkers;
    m_vKneeMarkers = vYMarkers;

    QwtText qwttMarkersNumber;

    for (unsigned int uiMarker = 0; uiMarker < vXMarkers.size(); uiMarker++) {

        m_pMarkerArray[uiMarker].setSymbol(m_pSymbolRect);
        //m_pSymbolRect->setBrush(qtgcMarkersColor);
        m_pMarkerArray[uiMarker].detach();
        m_pMarkerArray[uiMarker].setValue(vXMarkers.at(uiMarker), vYMarkers.at(uiMarker)) ;
        //qwttMarkersNumber.setText(QString::number(uiMarker));
        m_pMarkerArray[uiMarker].setLabel(qwttMarkersNumber);
        m_pMarkerArray[uiMarker].attach(this);
        m_uiMarkersNumber += vXMarkers.size();
     }

}

bool EndEffectorPlot::PlotCurve(std::vector <double> vXPositions, std::vector <double> vYPositions)
{
    m_pCurveJoint->setSamples(&vXPositions[0],&vYPositions[0], vXPositions.size() );
    m_pCurveJoint->attach(this);
    replot();
    return true;
}






