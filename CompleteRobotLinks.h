#ifndef COMPLETEROBOTLINKS_H
#define COMPLETEROBOTLINKS_H

#include "ui_CompleteRobotLinks.h"
#include "Enumerations.h"

/*!
  *     \file       CompleteRobotLinks.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      This class is inherited from QWidget and Ui::CompleteRobotPlot.
  *
  *                 This class provides an interface to the class "RobotLinks". The interpolated values from the class JointPlot are obtained
  *                 Morever, the lengths of the thigh and lower leg is changed, the sample time is set, delay between the legs and
  *                 the period is set. The units of angle are also set.
  *
*/


class CompleteRobotLinks : public QWidget, protected Ui::CompleteRobotLinks
{
    Q_OBJECT

public:
    explicit CompleteRobotLinks(QWidget *parent = 0);

    //! Set the thigh length
    void SetThighLength (double dThighLength);
    //! Set the lower leg length
    void SetLegLength (double dLegLength);
    //! Set the lower leg length
    void SetStepValue ( double dTempStepValue);
    //! Set the period of simuation
    void SetPeriod(double dPeriod);
    //! Set the delay between the legs
    void SetDelay(double dDelay);
    //! Set the scaling factor for angle depending upon the angle units selected
    void SetScalingFactorAngle(double dScalingFactorAngle);
    //! Set the samples counter in the robot simulation
    void SetSamplesCounter(unsigned int uiSamplesCounter);
    //! Set the samples in the robot plot
    void SetSamples(unsigned int uiSamples);
    //! Set the angle units
    void SetAnglesScale(AngleUnits_T auAngleUnits);
    //! Set the time interval for one sample to be simulated
    void SetTimerInterval();

    //void SetInterpolPeriod(double dInterpolPeriod);

    /*! Get the interpolated values of hip and knee angles from both the legs
     *  \param[in] vLHipValues vector of left hip interpolated values of angles
     *  \param[in] vRHipValues vector of right hip interpolated values of angles
     *  \param[in] vLKneeValues vector of left knee interpolated values of angles
     *  \param[in] vRKneeValues vector of right knee interpolated values of angles
    */
    void GetPlotInterpolValues(vector <double> vLHipValues, vector <double> vRHipValues, vector <double> vLKneeValues, vector <double> vRKneeValues);
    //! Get the interpolated values for the left knee in the form of vector of type double
    void GetPlotLeftKneeValues(vector <double> vLeftKneeValues);
    //! Get the interpolated values for the right knee in the form of vector of type double
    void GetPlotRightKneeValues(vector <double> vRightKneeValues);
    //! Get the interpolated values for the left hip in the form of vector of type double
    void GetPlotLeftHipValues(vector <double> vLeftHipValues);
    //! Get the interpolated values for the right hip in the form of vector of type double
    void GetPlotRightHipValues(vector <double> vRightHipValues);

private slots:
    //! Slot which is executed for every sample and changes the progress bar to show the percentage of simulation completed
    void ChangeProgressBar();
    //! Stops the motion simulation
    void StopSimulation();
    //! Runs the motion simulation
    void RunSimulation();
private:
    QString m_qsButtonPressedStr, m_qsButtonNormalStr;
};

#endif // COMPLETEROBOTLINKS_H



