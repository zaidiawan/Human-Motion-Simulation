#ifndef COMPLETEENDEFFECTPLOT_H
#define COMPLETEENDEFFECTPLOT_H

#include "ui_CompleteEndEffectPlot.h"
#include "Enumerations.h"

/*!
  *     \file       CompleteEndEffectPlot.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      This class is inherited from QWidget and Ui::CompleteEndEffectorPlot.
  *
  *                 This class provides an interface to the class "EndEffectorPlot". All the end-effector positions , and the relative
  *                 hip and knee markers are accessed from this class and are plotted.
  *
*/
class CompleteEndEffectPlot : public QWidget, protected Ui::CompleteEndEffectPlot
{
    Q_OBJECT

public:
    explicit CompleteEndEffectPlot(QWidget *parent = 0);
public:
    /*! Import the sample values into the EndEffectorPlot class
     *  \param[in]  vHipSamples vector of hip marker angles
     *  \param[in] vKneeSamples vector of knee marker angles
     *  \retval returns true if the size of the hip and knee samples to be imported is samee
     */
    bool ImportSamples ( std::vector <double> vHipSamples , std::vector <double> vKneeSamples);
    /*! Imports the hip markers into the Endeffector plot
     *  \param[in] vHipMarkerAngles vector of hip marker angles
     *  \param[in] vKneeMarkerAngles vector of knee marker angles
     *  \param[in] qtgcHipMarkersColor color of Hip markers to be imported
     *  \retval returns true if the size of the hip and knee vectors consisting of marker angles is same
    */
    bool ImportHipMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles,  Qt::GlobalColor qtgcHipMarkersColor);
    /*! Imports the knee markers into the Endeffector plot
     *  \param[in] vHipMarkerAngles vector of hip marker angles
     *  \param[in] vKneeMarkerAngles vector of knee marker angles
     *  \param[in] qtgcKneeMarkersColor color of Knee markers to be imported
     *  \retval returns true if the size of the hip and knee vectors consisting of marker angles is same
    */
    bool ImportKneeMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles,  Qt::GlobalColor qtgcKneeMarkersColor);
    /*! Export the position of the ankles
     *  \param[in] dThighLeng length of thigh of type double
     *  \param[in] dLegLeng length of lower leg of type double
     *  \param[out] vOutXPositions X position of the ankle
     *  \param[out] vOutYPositions Y position of the ankle
     *  \param[in] vInHipAngles vector of hip angles
     *  \param[in] vInKneeAngles vector of knee angles

     *  \retval returns true if the lengths of the thigh and lower leg is positive, and also if the vector lengths of the hip and knee angles is same
    */
    bool ExportPositions(double dThighLeng, double dLegLeng, std::vector <double> &vOutXPositions , std::vector <double> &vOutYPositions, std::vector <double> vInHipAngles , std::vector <double> vInKneeAngles);
    /*! Plots the curve using the x and y ankle positions
     *  \param[in] vXPositions vector of X positions of the ankle
     *  \retval returns true if the vector of x and y positions is  of same length
    */
    bool PlotCurve(std::vector <double> vXPositions, std::vector <double> vYPositions);
    //! Set the scaling factors for angle units in the class EndEffectorPlot depending on the angle units used
    bool SetScalingAngUnits(AngleUnits_T auAngleUnits);
    //! Set the markers number in the end effector plot class so that the history of markers can be used to remove the previous markers
    void SetMarkersNumber(uiPlot HipMarkersNr, uiPlot KneeMarkersNr);

private:


};

#endif // COMPLETEENDEFFECTPLOT_H
