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
#include "Enumerations.h"

/*!
  *     \file       EndEffectorPlot.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       11/08/2014
  *     \brief      This class is derived from QwtPlot and plots the end-effector positions
  *                 The class calculates the end-effector positions for every respective sample of hip and knee joints.
  *                 The positions corresponding to hip and knee markers are shown as markers
  *                 Every time the user changes the plot trajectories, the new positions are calculated and plotted
*/
class EndEffectorPlot : public QwtPlot
{
    Q_OBJECT

public:
    explicit EndEffectorPlot(QWidget *parent = 0);

signals:

public slots:

public:

    friend class CompleteEndEffectPlot;
    /*! Imports the hip and knee angle samples into the class
     *  \param[in] vHipSamples the vector of type double containing the hip angle samples
     *  \param[in] vKneeSamples The vector of type double containing knee angle samples
     *  \retval returns true if both the hip and knee vectors are of equal size
     */
    bool ImportSamples ( std::vector <double> vHipSamples , std::vector <double> vKneeSamples);
   /*! Imports the hip markers
    *  \param[in] vHipMarkerAngles vector of hip angle markers from the joint trajectories
    *  \param[in] vKneeMarkerAngles vector of knee angle markers at the time of hip  markers from the joint trajectories
    *  \param[in] qtgcHipMarkersColor color of the hip markers to be assigned
    *  \retval returns true if both the hip and knee vectors of markers are of equal size
    */
    bool ImportHipMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles, Qt::GlobalColor qtgcHipMarkersColor);
    /*! Imports the knee markers
     *  \param[in] vKneeMarkerAngles vector of knee angle markers from the joint trajectories
     *  \param[in] vHipMarkerAngles vector of hip angle markers at the time of knee  markers from the joint trajectories
     *  \param[in] qtgcKneeMarkersColor color of the knee markers to be assigned
     *  \retval returns true if both the hip and knee vectors of markers are of equal size
     */
    bool ImportKneeMarkers (std::vector <double> vHipMarkerAngles, std::vector <double> vKneeMarkerAngles, Qt::GlobalColor qtgcKneeMarkersColor);
    /*! Exports the end-effector positions for the given hip and knee lengths, and the hip and knee angle positions
     *  \param[in] dThighLen The length of the thigh
     *  \param[in] dThighLen The length of the lower leg
     *  \param[out] voutXPos vector of X positions of the end effector
     *  \param[out] voutYPos vector of Y positions of the end effector
     *  \param[in] vInHipAng The vector of type double containing the hip angle values
     *  \param[in] vInKneeAng The vector of type double containing the knee angle values
     *  \retval returns true if the lengths of the thighs and lower length are of equal size, and also the
     *          the hip and knee vectors are of equal size
     */
    bool ExportPositions(double dThighLen, double dLegLen, std::vector <double> &vOutXPos , std::vector <double> &vOutYPos, std::vector <double> vInHipAng, std::vector <double> vInKneeAng);
    /*! Plots the end-effector positions from the x and y positions
     *  \param[in] vXPositions vector of X-positions of the end-effector
     *  \param[in] vYPositions vector of Y-positions of the end-effector
     *  \retval returns true if both the vectors containing the hip and knee angle positions of the end-effectors are of equal size
     */
    bool PlotCurve(std::vector <double> vXPositions, std::vector <double> vYPositions);

private:

    QwtSymbol *m_pSymbolRect, *m_pSymbolRect2;
    QwtPlotMarker *m_pMarkerHipArray, *m_pMarkerKneeArray;
    QwtPlotGrid *m_pGrid;
    QwtPlotCurve *m_pCurveJoint;

    uiPlot m_uiSamplesPlot , m_uiMarkersNumber, m_uiHipMarkersNumber, m_uiKneeMarkersNumber;
    dPlot m_dAnglesScale, m_dThighLength, m_dLowerLegLength;
    QString m_qsTitle;

    std::vector <double> m_vHipSamples, m_vKneeSamples;
    //! Remove all the hip markers from the end-effector plot
    void RemoveAllHipMarkers();
    //! Remove all the knee markers from the end-effector plot
    void RemoveAllKneeMarkers();

};

#endif // ENDEFFECTORPLOT_H
