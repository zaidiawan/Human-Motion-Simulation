#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "CompleteJointPlot.h"
#include "CompleteRobotLinks.h"
#include "CompleteEndEffectPlot.h"
#include "qtimer.h"

/*!
  *     \file       MainWindow.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      This class provides the main interface to the user to control the motion simulation and the trajectoris and also contains many other widgets which are created within it.
  *
  *                 The class is inherited from QMainWindow and Ui::MainWindow.
  *                 The class contains two tab widgets. one for the robot motion simulation and the other related to creating
  *                 and managing the joint trajectories. Objects for the trajectories and simulation of motion are instantiated from the
  *                 classes CompletedJointPlot, CompleteEndEffectorPlot, and CompleteRobotLinks.
  *                 To control the trajectories, an interface has been created which provides the possibility for the user to change the trajectories and see
  *                 the relevant effect on the motion simulation at the same time.
  *
*/


class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

private:

    CompleteJointPlot *pHipLeft, *pHipRight, *pKneeLeft, *pKneeRight;
    CompleteEndEffectPlot *pEndEffectLeft, *pEndEffectRight;
    CompleteJointPlot **ppRobotObjects;
    CompleteRobotLinks *pRobotMain;
    QTimer *m_pTimerMainWindow;
    QSignalMapper *m_pSignalMapper;
    QMessageBox *m_pMessagebox;

   /*! \fn   void GetTimeValues(std::vector <double> &vTimeValues, double dDelay);
    *  \brief Getting the time values selected in the range from T- 2T in  the correct format depending upon the time mode and the delay
    *  \param[in]  dDelay   The delay of type double of the manipulator
    *  \param[out] vTimeValues The time values in the form of vectors of type double
    */
    void GetTimeValues(std::vector <double> &vTimeValues, double dDelay);

    /*! \fn   void GetTimeValues(std::vector <double> &vTimeValues);
     *  \brief Getting the time values selected in the range from 0- T depending upon the sample values
     *  \param[out] vTimeValues The time values in the form of vectors of type doubles
     */
    void GetTimeValues(std::vector <double> &vTimeValues);

    /*! \fn   void ChangeSimulation();
     *  \brief Changes the motion simulation depending upon the joint trajectories
     *  \pre   The joint trajectories have been changed
     */
    void ChangeSimulation();

    /*! \fn   GetRobotObjectSampledValues(CompleteJointPlot *pObject, std::vector <double> &vAngleSampleVals);
     *  \brief Getting the time values selected in the range from 0- T depending upon the sample values
     *  \param[out] vTimeValues The time values in the form of vectors of type doubles
     */
    void GetRobotObjectSampledValues(CompleteJointPlot *pObject, std::vector <double> &vAngleSampleVals);
    /*!  Gets the complete robot angle sample values for both the two legs
     *  \param[out]  vHipLeftValues The vector of left hip values
     *  \param[out]  vHipRightValues The vector of right hip values
     *  \param[out]  vKneeLeftValues The vector of left knee values
     *  \param[out]  vKneeRightValues The vector of right knee values
     */
    void GetCompleteRobotSamplesValues(std::vector <double> &vHipLeftValues, std::vector <double> &vHipRightValues, std::vector <double> &vKneeLeftValues, std::vector <double> &vKneeRightValues);
    //!  Replot the joint trajectories of all the four objects
    void ModifyAllObjectPlots();
    /*!  Updates all the joint trajectories and the corresponding simulation, and this is achieved after identification of the object
     *  \param[out]  pObjectChanged Object being changed i.e the plot trajectory of left or right hip or knee joint
     */
    void UpdateSimulationAndEndEffectPlot(CompleteJointPlot * &pObjectChanged);
    /*!  Plots the end-effector positions after recognizing the object changed
     *  \param[in] pEndEffector  end-effector object (left or right end-effector)
     *  \param[in] pActualObject the actual object which is changed from the class CompleteJointPlot, i.e any left or right hip or knee joint trajectory
     *  \param[in]  pRelativeObject the corresponding object which is changed from the class CompleteJointPlot, i.e any left or right hip or knee joint trajectory
     *               e.g if the object changed is left hip, then the corresponding object will be left knee.
     */
    void EndEffectorPlot(CompleteEndEffectPlot* pEndEffector, CompleteJointPlot* pActualObject, CompleteJointPlot* pRelativeObject);
    /*!  Gets the end-effector marker angles from the object changed, the corresponsing object of the object changed
     *  \param[in] pObjChanged  The object of class CompleteJointPlot changed e.g by changing any joint trajectory
     *  \param[in]  pRelativeObject the corresponding object which is changed from the class CompleteJointPlot, i.e any left or right hip or knee joint trajectory
     *               e.g if the object changed is left hip, then the corresponding object will be left knee.
     *  \param[out] vObjChangedValues The vector of angle values of the markers  for the object changed
     *  \param[out] RelativObjValues The vector of angle values of the markers  for the corresponding object of the object changed
     *               e.g if the object changed is left hip, then the corresponding object will be left knee.
*/
    void GetEndEffectMarkersAngles (CompleteJointPlot *pObjChanged, CompleteJointPlot *pRelativObj, std::vector <double> &vObjChangedValues, std::vector <double> &vRelativObjValues);

private slots:

    /*! Imports the parameters for the curve, it is worth noted that this is only one slot for all the four joint trajectories
     *  In this slot, the joint trajectory whose values are required to be imported is also identified
     */
    void ImportValsCurve();
    //! Changes the samples of all the plots, runs the motion simulation from the start
    void SamplesTextChanged();
    //! Changes the delay of all the joint plots and the motion simulation and also changes the simulation
    void DelayTextChanged();
    //! Changes the length of the lower leg, and also changes the end-effector plots
    void LegLenTextChanged();
    //! Changes the length of theigh, and also changes the end-effector plots
    void ThighLenTextChanged();
    //! Changes the period of all the joint trajectories, changes the motion simulation, restart the motion simulation
    void PeriodTextChanged();
    /*! Changes the period mode of all the plots and the motion simulation, if the period mode is percent, then disables the period text
     *  Motion simulation is not changes practically, but the values of time are changed which are provided to class RobotPlot
     */
    void PeriodModeChanged();
    /*! Changes the angle units of all the plots and the motion simulation
     *  Motion simulation is not changes practically, but the values of angles are changed which are provided to class RobotPlot
     */
    void AngleUnitsChanged();
    //! Get the interpolation values of all the joints. this slot is executed every time interpolation occurs
    void GetValuesInterpol();
    //! Changes the Interpolation of all the plots and the motion simulation
    void InterpolMethodChanged();
    /*! All the time and angle values of the joints, the number of cycles of simuation, and other parameters e.g period and delay are packed in suitable format for matlab, matlab engine is started and matlab file
     *  which controls the reference points for the controller in Simulink is executed.
     */
    void RunAdamsSim();

signals:

};

#endif // MAINWINDOW_H
