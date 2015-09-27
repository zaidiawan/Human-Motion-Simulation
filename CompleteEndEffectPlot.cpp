#include "CompleteEndEffectPlot.h"

CompleteEndEffectPlot::CompleteEndEffectPlot(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

bool CompleteEndEffectPlot::ImportSamples ( std::vector <double> vHipSamples , std::vector <double> vKneeSamples)
{
    if (EndEffectPlot->ImportSamples(vHipSamples, vKneeSamples ) == true)
        return true;
    else
        return false;
}

bool CompleteEndEffectPlot::ExportPositions(double dThighLeng, double dLegLeng, std::vector <double> &vOutXPositions , std::vector <double> &vOutYPositions, std::vector <double> vInHipAngles , std::vector <double> vInKneeAngles)
{
    EndEffectPlot->ExportPositions(dThighLeng, dLegLeng, vOutXPositions , vOutYPositions, vInHipAngles , vInKneeAngles);

    if (EndEffectPlot->ExportPositions(dThighLeng, dLegLeng, vOutXPositions , vOutYPositions, vInHipAngles , vInKneeAngles) == true)
        return true;
    else
        return false;
}

bool CompleteEndEffectPlot::ImportHipMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles,  Qt::GlobalColor qtgcHipMarkersColor)
{
     EndEffectPlot->ImportHipMarkers (vHipMarkerAngles , vKneeMarkerAngles, qtgcHipMarkersColor);

     if (  EndEffectPlot->ImportHipMarkers (vHipMarkerAngles , vKneeMarkerAngles, qtgcHipMarkersColor) == true)
         return true;
     else
         return false;
}

bool CompleteEndEffectPlot::ImportKneeMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles,  Qt::GlobalColor qtgcKneeMarkersColor)
{
     EndEffectPlot->ImportKneeMarkers (vHipMarkerAngles , vKneeMarkerAngles, qtgcKneeMarkersColor);
     if (EndEffectPlot->ImportKneeMarkers (vHipMarkerAngles , vKneeMarkerAngles, qtgcKneeMarkersColor) == true)
         return true;
     else
         return false;
}

bool CompleteEndEffectPlot::PlotCurve(std::vector <double> vXPositions, std::vector <double> vYPositions)
{
    EndEffectPlot->PlotCurve(vXPositions, vYPositions);

    if (EndEffectPlot->PlotCurve(vXPositions, vYPositions) == true)
        return true;
    else
        return false;
}
bool CompleteEndEffectPlot::SetScalingAngUnits(AngleUnits_T auAngleUnits)
{
    if (auAngleUnits == radians || auAngleUnits == degrees) {

        if(auAngleUnits == radians) {
            EndEffectPlot->m_dAnglesScale = 1;
        }
        else if(auAngleUnits == degrees) {
            EndEffectPlot->m_dAnglesScale = (M_PI / 180);
        }
        return true;
    }
    else
        return false;
}
void CompleteEndEffectPlot::SetMarkersNumber(uiPlot HipMarkersNr, uiPlot KneeMarkersNr)
{
    EndEffectPlot->m_uiHipMarkersNumber = HipMarkersNr;
    EndEffectPlot->m_uiKneeMarkersNumber = KneeMarkersNr;
}
