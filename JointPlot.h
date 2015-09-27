#ifndef JOINTPLOT_H
#define JOINTPLOT_H

#include <vector>
#include <qwt_plot.h>
#include "Enumerations.h"
#include "TypeDefs.h"
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_spline.h>
#include <qwt_plot_curve.h>
#include <Qtimer>
#include <QSignalMapper>
#include <qwt_plot.h>
#include "InterpolationSpline.h"
#include "constantini97.h"
#include <QMessageBox>
#include <Splines.h>

/*!
  *     \file       JointPlot.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      JointPlot class is used to plot the joint trajectories with the markers
  *
  *                 The class is inherited from QwtPlot and adds further functionalities
  *                 The class used four interpolation types to interpolate the markers. Markers are arranged, joint curves are plotted
  *                 with the specific interpolations. This class allows the user to add, remove or move the markers with the help of mouse.
  *                 Additionally the class has some functions to transform the coordinate systems and adding features to plots
  *
*/

using namespace Splines ;

using std::vector;

class CompleteJointPlot;

class JointPlot: public QwtPlot
{
    Q_OBJECT

public:
    explicit JointPlot(QWidget *parent = 0);

    QwtSpline *m_pqwtSpline;
    AkimaSpline m_asSpline;
    Constantini97 *m_pConstSpline;

    friend class CompleteJointPlot;

    //! Plots the trajectories based upon the selected interpolation type and returns true if the time and angle values are same for samples being plotted
    bool PlotCurve();

    /*! \fn PlotCurve(vector <double> vTimeSamples, vector <double> vAngleSamples);
     *  \brief Plots the trajectories based upon the provided input vectors
     *  \param[in]  vTimeSamples    Input time samples
     *  \param[in]  vAngleSamples   Input angle samples
     *  \retval true if the the sizes of the time and angle values are same, false otherwise
     */
    bool PlotCurve(vector <double> vTimeSamples, vector <double> vAngleSamples);

protected:
    /*! \fn   void mousePressEvent(QMouseEvent *PressEvent);
    *  \brief The function is invoked every time the mouse button is pressed
    *         further filters have been used within the function to detect if the right or left button is clicked
    *  \param[in]  The pointer to QMouseEvent
    *  \pre Mouse button is clicked
    *   \retval Nothing
    *  \post The markers are placed, removed or moved
    */
    void mousePressEvent(QMouseEvent *PressEvent);

    //! The function is invoked every time the mouse button is released
    void mouseReleaseEvent(QMouseEvent *ReleaseEvent);

private:

    AngleUnits_T m_auAngleUnits;
    PeriodMode_T m_pmPeriodMode;
    InterpolType_T m_itInterpolType;
    MarkersStatus_T m_msMarkersStatus;
    CurveStatus_T m_csCurveStatus;

    QwtSymbol *m_pSymbolRect, *m_pSymbolRect2;
    QwtPlotMarker *m_pMarkerArray;
    QwtPlotGrid *m_pGrid;
    QwtPlotCurve *m_pCurveJoint;
    QTimer *m_pTimerMoveMarker;
    QSignalMapper *m_pSignalMapper;
    QMessageBox *m_pMessageBox;

    dPlot m_dPeriodPlot, m_dDelay, m_dInterpolPeriod;
    uiPlot m_uiSamplesPlot , m_uiMarkersNumber, m_uiMarkersCount;
    QString m_qsTitle;

    vector <double> m_vTimeValues;
    vector <double> m_vAngleValues;
    vector <float> m_v_fCSplineSampledAngles;

    /*! \fn returns the time samples depending upon the step size, the number of samples and status of curve
    * \param[in] csCurveStatus the curve status either shown delayed or without delay
    * \retval   returns the equally time spanned samples
    */
    vector <double> TimeSamples(CurveStatus_T csCurveStatus);

   /*! \fn  bool Interpolation(const vector <double> vTimeInterpol, const vector <double> vAngleInterpol);
    *  \brief Takes the markers as inputs and do the interpolation depending upon the interpolation type selected
    *
    *  \param[in]  vTimeIntepol The vector of time values of the markers
    *  \param[in]   vAngleInterpol The vector of angle values of the markers
    *  \retval return true if the interpolation was successful, false otherwise
    */
    bool Interpolation(const vector <double>  vTimeInterpol , const vector <double> vAngleInterpol);

    //! The function adjust the axis scales so that the plot always remains in middle of canvas
    void RescaleAxis();

    /*! \fn  QPointF InvTransform( const QPointF &pos ) const;
    *  \brief The function returns the transformed position from pixel to plot coordinates
    *  \param[in]  pos  The actual position
    *  \retval The position with reference to the canvas
    */
    QPointF InvTransform( const QPointF &pos ) const;

    //! The function takes the vectors of markers as input parameters and adjust them in the ascending time values and returns true if both are of same size
    bool ArrangeMarkers(vector <double> &vXMarkers,vector <double> &vYMarkers);

    //! The function takes the vectors of markers  as input parameters and add them on the plot with the default red colour and returns true if both of same size
    bool AddMarkers(const vector <double> vXMarkers, const vector <double> vYMarkers, Qt::GlobalColor qtgcMarkersColor = Qt::red);

    /*! \fn bool AddMarker(double XMarker, double YMarker);
    *  \brief Adds one single marker with the time and angles values as parameters
    *
    *  \param[in]  The time marker of type double
    *  \param[in]  The angle marker of type double
    *  \retval returns true if markers arrangement, interpolation, markers placement and curve plotting is in right way
    */
    bool AddMarker(double XMarker, double YMarker);

    //! Removes the marker with the index of the marker is provided as input parameter and returns true if arrangement, interpolation, placement and plotting is correct
    bool RemoveMarker(unsigned int uiMarkerIndex);

    //! Takes the time value of the marker as input parameter and ensures there is not any marker with same time values and returns true if this condition is met
    bool CheckMarkerCorrectPlacement(double XValue);

    //! ensures that plot doesn't change if the marker is moved beyond the limits of canvas and returns false otherwise. It takes the marker index as input parameter.
    bool CheckMarkerCorrectMov(unsigned int iMarker);

    //! Takes the period mode as input and informs if the correct mode has been selected and return true. otherwise returns false
    bool CheckPeriodMode(PeriodMode_T pmPeriodMode);

    //! Takes angle units as input and ensures that appropriate angle units are selected and returns true. otherwise returns false
    bool CheckAngleUnits(AngleUnits_T auAngleUnits);

    //! Ensures the correct interpol type to be selected and takes interpol-type as input and returns true. otherwise returns false
    bool CheckInterpolType(InterpolType_T itInterpolType);

    //! The function ensures proper period to be provided and takes period of type double as input and returns true. otherwise returns false
    bool CheckPeriod(double dPeriod);

    //! Checks if the markers number is valid or not and takes it of type unsigned int as input. Returns true if it is valid and false otherwise
    bool CheckMarkersNumber(unsigned int uiMarkersNumber);

    /*! \fn   vector <bool> GetPressHistory(const QPointF qpfPressPos , const vector <double> vTimeValues, const vector <double> vAngleValues);
    *  \brief The function return the vector of type bool which contains information about if the the position where mouse clicks is marker or not
    *  \param[in]  qpfPressPos The press position of type QPointF
    *  \param[in]   vTimeValues  The vector of values of type double which contains the markers time
    *  \param[in]   vAngleValues The vector of values of type double which contains the markers angles
    *  \retval the vector of type bool which contains "1" at the index of marker which was clicked
    */
    vector <bool> GetPressHistory(const QPointF qpfPressPos , const vector <double> vTimeValues, const vector <double> vAngleValues);

    //! Calculates the step value based upon the number of samples and the period
    bool GetStepValue(double &dStepValue);

    //! Provides the period of interpolation and takes it as input by reference
    void GetInterpolPeriod(double &dInterpolCycle);

    /*! \fn   void GetSymbolSize(double &dSymbWidth, double &dSymbHeight);
    *  \brief The function calculates the size of the marker symbol
    *
    *  \param[out]  the width of the symbol calcuated and passed as reference
    *  \param[out]   The height of the symbol calculated and passed as reference
    */
    void GetSymbolSize(double &dSymbWidth, double &dSymbHeight);

    //! Truncate the decimal places to 2 of the number of type double passed as input and returns the truncated value of type double
    double TruncateDecimalPlaces(double dNumber);

    //! Sets the period of interpolation which is passed as input parameter of type double. True is returned if interpol. period is valid. False otherwise
    bool SetInterpolPeriod(double dInterpolPeriod);

    /*!  Copies the angle values of joints on both sides of interval T-2T, to make the spline interpolation periodic
     *  \param[in]  vTimeInterpol vector of time values for interpolation
     *  \param[in]  vAngleInterpol    vector of angle values for interpolation
     *  \retval returns the polygon of type QPolygonF , consisting of all the time and angle values for the 3 cycles
     */
    QPolygonF  MakeValsPeriodic(const vector<double> vTimeInterpol, const vector<double> vAngleInterpol);

    //! Sets the cubic spline interpolation by using the polygon of points and returns true if spline interpolation is successful
    bool SetCubicSpline(QPolygonF qpfPolyPoints );

    //! Sets the akima spline interpolation by using the polygon of points
    void SetAkimaSpline(QPolygonF qpfPolyPoints);

    /*! Sets the Constantini Spline interpolation and considering the curve status
     *  \param[in]  vTimeInterpol vector of time values for interpolation
     *  \param[in]  vAngleInterpol    vector of angle values for interpolation
     *  \param[in]  m_itInterpolType Interpolation type (Constantini or Constantini-Fourier)
     *  \param[in]  csCurveStatus Status of the curve (Curve is shown delayed or without delay)
     *  \param[out]  v_dAngleSamples vector of angle samples calculated using the interpolation
     *  \retval returns true if the interpolation was successful and false otherwise
     */
    bool SetConstantiniSpline(vector <double> vTimeInterpol, vector <double> vAngleInterpol, InterpolType_T m_itInterpolType, CurveStatus_T csCurveStatus, vector <double> &v_dAngleSamples);

    //! Finds the time samples depending on period and no. of samples,and then calculates the relevant interpolated values depending upon the interpolation type used
    void GetPlotSamples (vector <double> &vTimeSamples, vector <double> &vAngleSamples);
signals:
     //! Signal is emitted every time interpolation is done
    void Interpol();

private slots:
    //! Every time the marker is moved, this slot is executed and the index number of the marker which is moved is mapped as input parameter
    void MoveMarker(int iMarker);
};

#endif // JOINTPLOT_H
