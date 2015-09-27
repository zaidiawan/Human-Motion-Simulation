#include "EndEffectorPlot.h"
#include <qwt_plot_picker.h>


EndEffectorPlot::EndEffectorPlot(QWidget *parent) :
    QwtPlot(parent)
{

    m_uiMarkersNumber = 0;
    m_dAnglesScale = 1;
    m_pMarkerHipArray = new QwtPlotMarker[100]; // Creating MarkerArray
    m_pMarkerKneeArray = new QwtPlotMarker[100]; // Creating MarkerArray

    this->setCanvasBackground(QColor(200,200,230)); // Setting canvas Background

    m_pGrid = new QwtPlotGrid;  //  Creating Grid
    m_pGrid->setMajPen( QPen( Qt::white, 0, Qt::DotLine ) );
    m_pGrid->attach(this);

    m_pSymbolRect = new QwtSymbol;  // Creating Symbol
    m_pSymbolRect->setStyle(QwtSymbol::Rect);
    m_pSymbolRect->setSize(10.0, 10.0);

    m_pSymbolRect2 = new QwtSymbol;  // Creating Symbol
    m_pSymbolRect2->setStyle(QwtSymbol::Rect);
    m_pSymbolRect2->setSize(10.0, 10.0);

    m_pCurveJoint = new QwtPlotCurve(); // Creating Curve
    m_pCurveJoint->setStyle(QwtPlotCurve::Lines);
    m_pCurveJoint->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_pCurveJoint->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_pCurveJoint->setPen(QPen(Qt::black, 2.5));

    QwtPlotPicker* qppPlotPicker = new QwtPlotPicker(this->xBottom, this->yLeft, QwtPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas()); // Creating PlotPicker for displaying coordinates on Canvas
}

bool EndEffectorPlot::ImportSamples ( std::vector <double> vHipSamples , std::vector <double> vKneeSamples)
{
    if (vHipSamples.size() == vKneeSamples.size()) {

        m_vHipSamples = vHipSamples;
        m_vKneeSamples = vKneeSamples;
        return true;
    }
    else
        return false;
}

bool EndEffectorPlot::ExportPositions(double dThighLen, double dLegLen, std::vector <double> &vOutXPos, std::vector <double> &vOutYPos, std::vector <double> vInHipAng , std::vector <double> vInKneeAng)
{

    if (dThighLen > 0 && dLegLen > 0 && vInHipAng.size() == vInKneeAng.size()) {

        double dThighX, dThighY, dLegX, dLegY;
        vOutXPos.clear();
        vOutYPos.clear();

        m_dThighLength = dThighLen;
        m_dLowerLegLength = dLegLen;

        // x position of end effector = thigh_length*sin(hipangle)+lower_leg_length*sin(hipangle+kneeangle)
        // y position of end effector  = thigh_length*cos(hipangle )+ lower_leg_length*cos(hipange+kneeangle)

        for(unsigned int uiSample = 0; uiSample < vInHipAng.size(); uiSample++) {

            dThighX = dThighLen * sin((vInHipAng.at(uiSample)) * m_dAnglesScale);
            dThighY = dThighLen * cos((vInHipAng.at(uiSample)) * m_dAnglesScale);

            dLegX = dLegLen*sin( ( vInHipAng.at(uiSample) + vInKneeAng.at(uiSample)) * m_dAnglesScale );
            dLegY = dLegLen*cos( (vInHipAng.at(uiSample) + vInKneeAng.at(uiSample)) * m_dAnglesScale );

            vOutXPos.push_back(dThighX + dLegX);
            vOutYPos.push_back((dThighLen + dLegLen) - (dThighY + dLegY));
        }

        return true;
    }
    else
        return false;
}

bool EndEffectorPlot::ImportHipMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles, Qt::GlobalColor qtgcHipMarkersColor)
{
    qDebug()<<"Hip"<<vHipMarkerAngles.size();
    qDebug()<<"Knee"<<vKneeMarkerAngles.size();
    if (vHipMarkerAngles.size() == vKneeMarkerAngles.size()) {

        std::vector <double> vHipMarkersX, vHipMarkersY;

        ExportPositions(m_dThighLength, m_dLowerLegLength, vHipMarkersX , vHipMarkersY,  vHipMarkerAngles, vKneeMarkerAngles);

        QwtText qwttMarkersNumber;

        RemoveAllHipMarkers();
        m_uiHipMarkersNumber = vHipMarkerAngles.size();
        for (unsigned int uiMarker = 0; uiMarker < vHipMarkersX.size(); uiMarker++) {

            m_pMarkerHipArray[uiMarker].setSymbol(m_pSymbolRect);
            m_pSymbolRect->setBrush(qtgcHipMarkersColor);
            m_pMarkerHipArray[uiMarker].detach();
            m_pMarkerHipArray[uiMarker].setValue(vHipMarkersX.at(uiMarker), vHipMarkersY.at(uiMarker)) ;
            qwttMarkersNumber.setText(QString::number(uiMarker));
            m_pMarkerHipArray[uiMarker].setLabel(qwttMarkersNumber);
            m_pMarkerHipArray[uiMarker].attach(this);
        }

        return true;
    }

    else
        return false;
}

bool EndEffectorPlot::ImportKneeMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles, Qt::GlobalColor qtgcKneeMarkersColor)
{

    if(vHipMarkerAngles.size() == vKneeMarkerAngles.size()) {

        std::vector <double> vKneeMarkersX, vKneeMarkersY;

        ExportPositions(m_dThighLength, m_dLowerLegLength, vKneeMarkersX , vKneeMarkersY,  vHipMarkerAngles, vKneeMarkerAngles);

        QwtText qwttMarkersNumber;

        RemoveAllKneeMarkers();

        m_uiKneeMarkersNumber = vKneeMarkerAngles.size();

        for (unsigned int uiMarker = 0; uiMarker < vKneeMarkersX.size(); uiMarker++) {

            m_pMarkerKneeArray[uiMarker].setSymbol(m_pSymbolRect2);
            m_pSymbolRect2->setBrush(qtgcKneeMarkersColor);

            m_pMarkerKneeArray[uiMarker].setValue(vKneeMarkersX.at(uiMarker), vKneeMarkersY.at(uiMarker)) ;
            qwttMarkersNumber.setText(QString::number(uiMarker));
            m_pMarkerKneeArray[uiMarker].setLabel(qwttMarkersNumber);
            m_pMarkerKneeArray[uiMarker].attach(this);
        }


        return true;
    }

    else
        return false;
}

bool EndEffectorPlot::PlotCurve(std::vector <double> vXPositions, std::vector <double> vYPositions)
{
    if(vXPositions.size() == vYPositions.size()) {

        m_uiMarkersNumber = 0;
        m_pCurveJoint->setSamples(&vXPositions[0],&vYPositions[0], vXPositions.size() );
        m_pCurveJoint->attach(this);
        replot();

        return true;
    }

    else
        return false;
}
void EndEffectorPlot::RemoveAllHipMarkers()
{
    for(unsigned int iMarker =0; iMarker < m_uiHipMarkersNumber; iMarker++) {
        //qDebug()<<"HipNumber"<<m_uiHipMarkersNumber;
        m_pMarkerHipArray[iMarker].detach();
    }
    m_uiHipMarkersNumber = 0;
}
void EndEffectorPlot::RemoveAllKneeMarkers()
{
    for(unsigned int iMarker =0; iMarker < m_uiKneeMarkersNumber; iMarker++) {
        m_pMarkerKneeArray[iMarker].detach();
    }
    m_uiKneeMarkersNumber = 0;
}









