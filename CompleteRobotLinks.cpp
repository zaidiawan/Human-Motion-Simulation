#include "CompleteRobotLinks.h"

CompleteRobotLinks::CompleteRobotLinks(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(RobotPlot->m_pTimerRobotLinks, SIGNAL(timeout()), this, SLOT(ChangeProgressBar()));
    connect(ButtonStop, SIGNAL(clicked()), this, SLOT(StopSimulation()));
    connect(ButtonRun, SIGNAL(clicked()), this, SLOT(RunSimulation()));

    m_qsButtonPressedStr = QString("QPushButton {border-radius: 2px;padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(100, 100, 100);background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #34f32d, stop: 1 #000000); color: white;}");
    m_qsButtonNormalStr =  QString("QPushButton {border-radius: 2px;padding: 0.2em 0.2em 0.3em 0.2em;border: 1px solid rgb(100, 100,100);background: QLinearGradient( x1: 0, y1: 0.02, x2: 0, y2: 1.2, stop: 0 #220, stop: 1 #ffffff);color: white;}");
}

void CompleteRobotLinks::SetThighLength (double dThighLength) {

    RobotPlot->m_dLengthThigh = dThighLength;
}

void CompleteRobotLinks::SetLegLength (double dLegLength) {
    RobotPlot->m_dLengthLeg = dLegLength;
}

void CompleteRobotLinks::SetStepValue (double dTempStepValue) {
    RobotPlot->m_dTempStepValue = dTempStepValue;
}

void CompleteRobotLinks::SetPeriod(double dPeriod) {
    RobotPlot->m_dPeriod = dPeriod;
    RobotPlot->m_pTimerRobotLinks->setInterval(((RobotPlot->m_dPeriod*1000) / (RobotPlot->m_uiSamples)));
}
void CompleteRobotLinks::SetDelay(double dDelay) {
    RobotPlot->m_dDelay = dDelay;
}

void CompleteRobotLinks::SetScalingFactorAngle(double dScalingFactorAngle) {
    RobotPlot->m_dScalingFactorAngle = dScalingFactorAngle;
}

void CompleteRobotLinks::SetSamplesCounter(unsigned int uiSamplesCounter) {
   RobotPlot->m_uiSamplesCounter = uiSamplesCounter;
}

void CompleteRobotLinks::SetSamples(unsigned int uiSamples) {
    RobotPlot->m_uiSamples = uiSamples;
    SetTimerInterval();
}

void CompleteRobotLinks::GetPlotInterpolValues(vector<double> vLHipValues, vector<double> vRHipValues, vector<double> vLKneeValues, vector<double> vRKneeValues) {
    RobotPlot->GetPlotInterpolValues(vLHipValues, vRHipValues, vLKneeValues, vRKneeValues);
}

void CompleteRobotLinks::GetPlotLeftHipValues(vector <double> vLeftHipValues)
{

    RobotPlot->GetPlotLeftHipValues(vLeftHipValues);

}

void CompleteRobotLinks::GetPlotRightHipValues(vector <double> vRightHipValues)

{

    RobotPlot->GetPlotRightHipValues(vRightHipValues);
}

void CompleteRobotLinks::GetPlotLeftKneeValues(vector <double> vLeftKneeValues)

{
    RobotPlot->GetPlotLeftKneeValues(vLeftKneeValues);
}

void CompleteRobotLinks::GetPlotRightKneeValues(vector <double> vRightKneeValues)
{
    RobotPlot->GetPlotRightKneeValues(vRightKneeValues);
}

void CompleteRobotLinks::SetAnglesScale(AngleUnits_T auAngleUnits)
{
    if(auAngleUnits == radians) {
        RobotPlot->m_dScalingFactorAngle = 1;
    }
    else if(auAngleUnits == degrees) {
        RobotPlot->m_dScalingFactorAngle = (M_PI / 180);
    }
}

void CompleteRobotLinks::SetTimerInterval()
{
    RobotPlot->m_pTimerRobotLinks->setInterval(((RobotPlot->m_dPeriod*(1000)) / (RobotPlot->m_uiSamples)));
    qDebug()<<"Test:"<<(RobotPlot->m_dPeriod) / (RobotPlot->m_uiSamples);
}
void CompleteRobotLinks::ChangeProgressBar()
{

  int iValProgressBar =  (((RobotPlot->m_dPeriod) / (RobotPlot->m_uiSamples)*RobotPlot->m_uiSamplesCounter) / RobotPlot->m_dPeriod)*100;
  progressBar->setValue(iValProgressBar);


}

void CompleteRobotLinks::StopSimulation()
{
    RobotPlot->m_pTimerRobotLinks->stop();
    ButtonStop->setStyleSheet(m_qsButtonPressedStr);
    ButtonRun->setStyleSheet(m_qsButtonNormalStr);
}

void CompleteRobotLinks::RunSimulation()
{
    RobotPlot->m_pTimerRobotLinks->start();
    ButtonStop->setStyleSheet(m_qsButtonNormalStr);
    ButtonRun->setStyleSheet(m_qsButtonPressedStr);
}

/*void CompleteRobotLinks::SetInterpolPeriod(double dInterpolPeriod)
{
    RobotPlot->m_dInterpolPeriod = dInterpolPeriod;
}*/





