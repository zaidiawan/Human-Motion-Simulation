#ifndef ROBOTLINKS_H
#define ROBOTLINKS_H

#include <qwt_plot.h>
#include <JointPlot.h>
#include <QTimer>

/*!
  *     \file       RobotLinks.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      This class has the following functionalities:
  *                 1) Get the interpolated values for the hip and knee joints from JointPlot class in the form of vectors
  *                 2) Creates the motion simulation for every sample time for the hip and knee joints of both the legs
  *                 3) Run the simulation in continuous cycles
  *
*/

class RobotLinks : public QwtPlot
{
    Q_OBJECT
public:
    explicit RobotLinks(QWidget *parent = 0);
    //! Declaring Class 'CompleteJointPlot' as friend
    friend class CompleteRobotLinks;
    QTimer *m_pTimerRobotLinks;
signals:

public slots:

private:

    /*! Get the interpolated values of hip and knee angles from both the legs
     *  \param[in] vLeftHipValues vector of left hip interpolated values of angles
     *  \param[in] vRightHipValues vector of right hip interpolated values of angles
     *  \param[in] vLeftKneeValues vector of left knee interpolated values of angles
     *  \param[in] vRightKneeValues vector of right knee interpolated values of angles
    */
    void GetPlotInterpolValues(vector <double> vLeftHipValues, vector <double> vRightHipValues, vector <double> vLeftKneeValues, vector <double> vRightKneeValues );
    //! Get the interpolated values for the left hip in the form of vector of type double
    void GetPlotLeftHipValues(vector <double> vLeftHipValues);
    //! Get the interpolated values for the right hip in the form of vector of type double
    void GetPlotRightHipValues(vector <double> vRightHipValues);
    //! Get the interpolated values for the left knee in the form of vector of type double
    void GetPlotLeftKneeValues(vector <double> vLeftKneeValues);
    //! Get the interpolated values for the right knee in the form of vector of type double
    void GetPlotRightKneeValues(vector <double> vRightKneeValues);

    double m_dLengthThigh, m_dLengthLeg, m_dPeriod, m_dDelay;
    unsigned int m_uiSamplesCounter, m_uiSamples;
    double m_dTempStepValue, m_dScalingFactorAngle;

    vector <double> m_vHipRLeg, m_vKneeRLeg, m_vHipLLeg, m_vKneeLLeg;

    QwtPlotCurve * m_pRThighCurve, *m_pRLegCurve, *m_pLThighCurve, *m_pLLegCurve;

private slots:
    //! Slot which is executed every sample time and creates the motion simulation from the interpolated values
    void MoveLinks();

};

#endif // ROBOTLINKS_H
