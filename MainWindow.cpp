#include "MainWindow.h"
#include "Enumerations.h"
#include <iterator>
#include <string>
#include <QString>
#include "MatlabSimulation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    m_pTimerMainWindow = new QTimer(this);
    m_pTimerMainWindow->setInterval(100);
    m_pTimerMainWindow->start();

    connect(ComboAngUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(AngleUnitsChanged())) ;

    connect(ComboPeriodMode, SIGNAL(currentIndexChanged(int)), this, SLOT(PeriodModeChanged())) ;

    connect(ComboInterpolMode, SIGNAL(currentIndexChanged(int)), this, SLOT(InterpolMethodChanged())) ;

    connect(CommandPeriod, SIGNAL(pressed()), this, SLOT(PeriodTextChanged())) ;

    connect(CommandSamples, SIGNAL(pressed()), this, SLOT(SamplesTextChanged())) ;

    connect(CommandThighLeng, SIGNAL(pressed()), this, SLOT(ThighLenTextChanged())) ;

    connect(CommandLowerLegLeng, SIGNAL(pressed()) ,this, SLOT(LegLenTextChanged())) ;

    connect(CommandDelay, SIGNAL(pressed()), this, SLOT(DelayTextChanged())) ;

    connect(ButtonAdamsSim, SIGNAL(clicked()), this, SLOT(RunAdamsSim()));


    /*-----------------------------------------------------------------------------------------------
                                Hip Objects Creation and Initialization
      -----------------------------------------------------------------------------------------------*/

    vector <double> vHipTimeVals, vHipAngVals;

    pHipLeft = new CompleteJointPlot;
    MainHLayoutLHip->addWidget(pHipLeft);

    pHipRight = new CompleteJointPlot;
    MainHLayoutRHip->addWidget(pHipRight);

    vHipTimeVals.push_back(0.12);    // Getting Time values into vector
    vHipTimeVals.push_back(0.75);
    vHipTimeVals.push_back(1.47);
    vHipTimeVals.push_back(1.98);
    vHipTimeVals.push_back(2.55);
    vHipTimeVals.push_back(2.91);

    vHipAngVals.push_back(0.371755131000000);  // Getting Angle Values into Vector
    vHipAngVals.push_back(0.0279252680000000);
    vHipAngVals.push_back(-0.336848546000000);
    vHipAngVals.push_back(0.0191986220000000);
    vHipAngVals.push_back(0.425860337000000);
    vHipAngVals.push_back(0.359537826000000);

    pHipLeft->SetDelay(1.5);
    pHipLeft->SetTitle("Left Hip");
    pHipLeft->SetMarkersStatus(MarkersUnchanged);
    pHipLeft->ImportMarkers (vHipTimeVals,vHipAngVals);
    pHipLeft->ShowMarkers(Qt::red);
    pHipLeft->PlotCurve();

    pHipRight->SetDelay(0);
    pHipRight->SetTitle("Right Hip");
    pHipRight->SetMarkersStatus(MarkersUnchanged);
    pHipRight->ImportMarkers (  vHipTimeVals , vHipAngVals );
    pHipRight->ShowMarkers(Qt::red);
    pHipRight->PlotCurve();

    /*-----------------------------------------------------------------------------------------------
                               Knee Objects Creation and Initialization
      -----------------------------------------------------------------------------------------------*/

    vector <double> vKneeTimeVals, vKneeAngVals;

    pKneeLeft = new CompleteJointPlot;
    MainHLayoutLKnee->addWidget(pKneeLeft);

    pKneeRight = new CompleteJointPlot;
    MainHLayoutRKnee->addWidget(pKneeRight);

    vKneeTimeVals.push_back(0.15);    // Getting Time values into vector
    vKneeTimeVals.push_back(0.39);
    vKneeTimeVals.push_back(0.78);
    vKneeTimeVals.push_back(1.17);
    vKneeTimeVals.push_back(1.65);
    vKneeTimeVals.push_back(2.16);

    vKneeAngVals.push_back(-0.169296937);  // Getting Angle Values into Vector
    vKneeAngVals.push_back(-0.307177948000000);
    vKneeAngVals.push_back(-0.151843645000000);
    vKneeAngVals.push_back(-0.0331612560000000);
    vKneeAngVals.push_back(-0.3036872900000);
    vKneeAngVals.push_back(-0.996583003000000);


    pKneeLeft->SetDelay(1.5);
    pKneeLeft->SetTitle("Left Knee");
    pKneeLeft->SetMarkersStatus(MarkersUnchanged);
    pKneeLeft->ImportMarkers ( vKneeTimeVals , vKneeAngVals );
    pKneeLeft->ShowMarkers(Qt::red);
    pKneeLeft->PlotCurve();

    pKneeRight->SetDelay(0);
    pKneeRight->SetTitle("Right Knee");
    pKneeRight->SetMarkersStatus(MarkersUnchanged);
    pKneeRight->ImportMarkers ( vKneeTimeVals , vKneeAngVals);
    pKneeRight->ShowMarkers(Qt::red);
    pKneeRight->PlotCurve();

    connect(pHipLeft, SIGNAL(InterpolationCompleted()), this, SLOT(GetValuesInterpol())) ;
    connect(pHipRight, SIGNAL(InterpolationCompleted()), this, SLOT(GetValuesInterpol())) ;
    connect(pKneeLeft, SIGNAL(InterpolationCompleted()), this, SLOT(GetValuesInterpol())) ;
    connect(pKneeRight, SIGNAL(InterpolationCompleted()), this, SLOT(GetValuesInterpol())) ;

    connect(pHipLeft, SIGNAL(ImportCurve()), this, SLOT(ImportValsCurve())) ;
    connect(pHipRight, SIGNAL(ImportCurve()), this, SLOT(ImportValsCurve())) ;
    connect(pKneeLeft, SIGNAL(ImportCurve()), this, SLOT(ImportValsCurve())) ;
    connect(pKneeRight, SIGNAL(ImportCurve()), this, SLOT(ImportValsCurve())) ;

    /*-----------------------------------------------------------------------------------------------
                                    Creating End Effector Objects and initialization
     -----------------------------------------------------------------------------------------------*/

    pEndEffectRight = new CompleteEndEffectPlot;
    MWinHLayoutREndEffect->addWidget(pEndEffectRight);

    pEndEffectLeft = new CompleteEndEffectPlot;
    MWinHLayoutLEndEffect->addWidget(pEndEffectLeft);

    pEndEffectLeft->SetMarkersNumber(vHipTimeVals.size(), vKneeTimeVals.size());
    pEndEffectRight->SetMarkersNumber(vHipTimeVals.size(), vKneeTimeVals.size());
    EndEffectorPlot(pEndEffectRight, pHipRight, pKneeRight);
    EndEffectorPlot(pEndEffectLeft, pHipLeft, pKneeLeft);

    /*-----------------------------------------------------------------------------------------------
                                    Creating RobotLinks Object
     -----------------------------------------------------------------------------------------------*/
    pRobotMain = new CompleteRobotLinks;
    MainHLayoutSimulation->addWidget(pRobotMain);

    pRobotMain->SetThighLength(50);
    pRobotMain->SetLegLength(60);
    pRobotMain->SetStepValue(0.0);
    pRobotMain->SetPeriod(lineEditPeriod->text().toDouble());
    pRobotMain->SetDelay(lineEditDelay->text().toDouble());
    pRobotMain->SetScalingFactorAngle(1);
    pRobotMain->SetSamples(lineEditSamples->text().toInt());
    pRobotMain->SetSamplesCounter(0);
    pRobotMain->SetTimerInterval();
    ChangeSimulation();

    /*-----------------------------------------------------------------------------------------------
                                   Pointer to Robot Objects Creation
     -----------------------------------------------------------------------------------------------*/

    ppRobotObjects = new CompleteJointPlot*[4];

    ppRobotObjects[1] = pHipLeft;
    ppRobotObjects[3] = pKneeLeft;
    ppRobotObjects[0] = pHipRight;
    ppRobotObjects[2] = pKneeRight;
}

void MainWindow::SamplesTextChanged()
{
    pHipLeft->SetSamples(lineEditSamples->text().toInt());
    pHipLeft->PlotCurve();

    pHipRight->SetSamples(lineEditSamples->text().toInt());
    pHipRight->PlotCurve();

    pKneeLeft->SetSamples(lineEditSamples->text().toInt());
    pKneeLeft->PlotCurve();

    pKneeRight->SetSamples(lineEditSamples->text().toInt());
    pKneeRight->PlotCurve();

    pRobotMain->SetSamples(lineEditSamples->text().toInt());
    pRobotMain->SetSamplesCounter(0);

    ChangeSimulation();



}
void MainWindow::DelayTextChanged()
{
    pRobotMain->SetDelay(lineEditDelay->text().toDouble());
    pHipLeft->SetDelay(lineEditDelay->text().toDouble());
    pKneeLeft->SetDelay(lineEditDelay->text().toDouble());
    ChangeSimulation();
    pRobotMain->SetStepValue(0.0);
    pRobotMain->SetSamplesCounter(0);
}
void MainWindow::LegLenTextChanged()
{
    double dThighLength = lineEditThighLength->text().toDouble();
    double dLegLength   = lineEditLowerLegLength->text().toDouble();
    double dFactor      = 110 / (dThighLength + dLegLength);

    pRobotMain->SetLegLength(dLegLength*dFactor);
    pRobotMain->SetThighLength(dThighLength*dFactor);

    EndEffectorPlot(pEndEffectRight, pHipRight, pKneeRight);
    EndEffectorPlot(pEndEffectLeft, pHipLeft, pKneeLeft);

}
void MainWindow::ThighLenTextChanged()
{
    double dThighLength = lineEditThighLength->text().toDouble();
    double dLegLength   = lineEditLowerLegLength->text().toDouble();
    double dFactor      = 110 / (dThighLength + dLegLength);

    pRobotMain->SetLegLength(dLegLength*dFactor);
    pRobotMain->SetThighLength(dThighLength*dFactor);

    EndEffectorPlot(pEndEffectRight, pHipRight, pKneeRight);
    EndEffectorPlot(pEndEffectLeft, pHipLeft, pKneeLeft);
}
void MainWindow::PeriodTextChanged()
{
   if(ComboPeriodMode->currentText() == "Time") {
        pHipLeft->SetPeriod(lineEditPeriod->text().toDouble());

        pHipRight->SetPeriod(lineEditPeriod->text().toDouble());

        pKneeLeft->SetPeriod(lineEditPeriod->text().toDouble());

        pKneeRight->SetPeriod(lineEditPeriod->text().toDouble());

        pRobotMain->SetPeriod(lineEditPeriod->text().toDouble());

        pRobotMain->SetStepValue(0.0);

        pRobotMain->SetSamplesCounter(0);

        ModifyAllObjectPlots();

        ChangeSimulation();
    }
    else
    {

        m_pMessagebox = new QMessageBox();
        m_pMessagebox->setInformativeText("Period change is possible in only Time mode!!!!");
        m_pMessagebox->setWindowTitle("Information");
        m_pMessagebox->show();
    }

}


void MainWindow::PeriodModeChanged()
{
    QString qsDelayTime, qsDelayPercent;
    PeriodMode_T pmPeriodMode;

    qsDelayTime = QString::number((lineEditDelay->text().toDouble() * lineEditPeriod->text().toDouble() ) / 100 );
    qsDelayPercent = QString::number((lineEditDelay->text().toDouble() / lineEditPeriod->text().toDouble() ) * 100);

    if(ComboPeriodMode->currentText() == "Time") {

        lineEditDelay->setText(qsDelayTime);
        pmPeriodMode =  time;
        lineEditPeriod->setDisabled(false);

    }
    else if(ComboPeriodMode->currentText() == "Percent") {

        lineEditPeriod->setDisabled(true);
        lineEditDelay->setText(qsDelayPercent);
        pmPeriodMode = percent;
    }

    pHipLeft->SetDelay(lineEditDelay->text().toDouble());
    pKneeLeft->SetDelay(lineEditDelay->text().toDouble());

    pHipLeft->SetPeriodMode(pmPeriodMode);

    pHipRight->SetPeriodMode(pmPeriodMode);

    pKneeLeft->SetPeriodMode(pmPeriodMode);

    pKneeRight->SetPeriodMode(pmPeriodMode);

    ModifyAllObjectPlots();

    ChangeSimulation();
}

void MainWindow::GetTimeValues(vector <double> &vTimeValues, double dDelay )
{
    vTimeValues.clear();
    double dTimeValue = 0;

    for(unsigned int uiMarker = 0; uiMarker < lineEditSamples->text().toUInt(); uiMarker++) {
    // Providing time values from T-2T
        if(ComboPeriodMode->currentText() == "Percent") {
            vTimeValues.push_back(dTimeValue + 100 + dDelay);
            dTimeValue += (100 / (double)lineEditSamples->text().toInt() );
        }

        else if(ComboPeriodMode->currentText() == "Time") {

            vTimeValues.push_back(dTimeValue + lineEditPeriod->text().toDouble() + dDelay);
            dTimeValue += (lineEditPeriod->text().toDouble() /(double)lineEditSamples->text().toInt() );
        }
    }
}

void MainWindow::GetTimeValues(vector <double> &vTimeValues)
{
    double dTimeVal = 0;
    for (unsigned int uiMarker = 0; uiMarker < lineEditSamples->text().toDouble(); uiMarker++) {
        vTimeValues.push_back(dTimeVal);
        dTimeVal +=  lineEditPeriod->text().toDouble() / (double)lineEditSamples->text().toInt();
    }
}

void MainWindow::ChangeSimulation()
{
    std::vector <double> vHipLeftVals, vHipRightVals, vKneeLeftVals, vKneeRightVals;

    GetCompleteRobotSamplesValues(vHipLeftVals, vHipRightVals, vKneeLeftVals, vKneeRightVals);

    pRobotMain->GetPlotInterpolValues(vHipLeftVals, vHipRightVals, vKneeLeftVals, vKneeRightVals);
}

void MainWindow::AngleUnitsChanged()
{

    AngleUnits_T auAngleUnits;

    if(ComboAngUnits->currentText() == "Degrees") {
         auAngleUnits = degrees;
    }
    else if(ComboAngUnits->currentText() == "Radians") {
        auAngleUnits = radians;
    }

    pRobotMain->SetAnglesScale(auAngleUnits);
    pEndEffectLeft->SetScalingAngUnits(auAngleUnits);
    pEndEffectRight->SetScalingAngUnits(auAngleUnits);

    pHipLeft->SetAngleUnits(auAngleUnits);

    pHipRight->SetAngleUnits(auAngleUnits);

    pKneeLeft->SetAngleUnits(auAngleUnits);

    pKneeRight->SetAngleUnits(auAngleUnits);

    ModifyAllObjectPlots();
    ChangeSimulation();
}

void MainWindow::InterpolMethodChanged()
{
    InterpolType_T itInterpolType;
    if (ComboInterpolMode->currentText() == "Akima") {
        itInterpolType = akima;
    }
    else if (ComboInterpolMode->currentText() == "Cubic") {
        itInterpolType = cubic;
    }

    else if (ComboInterpolMode->currentText() == "Constantini") {
        itInterpolType = Constantini;
    }
    else if (ComboInterpolMode->currentText() == "CFourier") {
        itInterpolType = CFourier;
    }

    pHipLeft->SetInterpolType(itInterpolType);

    pHipRight->SetInterpolType(itInterpolType);

    pKneeLeft->SetInterpolType(itInterpolType);

    pKneeRight->SetInterpolType(itInterpolType);

    ModifyAllObjectPlots();
    ChangeSimulation();

}

void MainWindow::GetRobotObjectSampledValues(CompleteJointPlot *pObject, std::vector <double> &vAngleSampleVals)
{
    std::vector <double> vTimeSamples, vAngSamples;
    pObject->GetSamples(vTimeSamples);
    pObject->GetValues(vTimeSamples, vAngSamples);

    vAngleSampleVals = vAngSamples;


}

void MainWindow::GetCompleteRobotSamplesValues(std::vector <double> &vHipLeftValues, std::vector <double> &vHipRightValues, std::vector <double> &vKneeLeftValues, std::vector <double> &vKneeRightValues)
{
    vector <double> vHipLeftVals, vHipRightVals, vKneeLeftVals, vKneeRightVals;

    GetRobotObjectSampledValues(pHipLeft, vHipLeftVals);
    GetRobotObjectSampledValues(pKneeLeft, vKneeLeftVals);
    GetRobotObjectSampledValues(pHipRight, vHipRightVals);
    GetRobotObjectSampledValues(pKneeRight, vKneeRightVals);

    vHipLeftValues = vHipLeftVals;
    vHipRightValues = vHipRightVals;
    vKneeLeftValues = vKneeLeftVals;
    vKneeRightValues = vKneeRightVals;
}


void MainWindow::GetEndEffectMarkersAngles(CompleteJointPlot *pActObj, CompleteJointPlot *pRelativObj, vector <double> &vActObjValues, vector <double> &vRelativObjValues)
{
    vector <double> vActObjTimeVals, vActObjAngVals, vRelativObjAngVals;

    pActObj->ExportMarkers(vActObjTimeVals, vActObjAngVals);
    pRelativObj->GetValues(vActObjTimeVals, vRelativObjAngVals);

    vActObjValues = vActObjAngVals;
    vRelativObjValues = vRelativObjAngVals;

}

void MainWindow::ModifyAllObjectPlots()
{
    pHipLeft->ShowMarkers(Qt::red);
    pHipLeft->PlotCurve();

    pHipRight->ShowMarkers(Qt::red);
    pHipRight->PlotCurve();

    pKneeLeft->ShowMarkers(Qt::red);
    pKneeLeft->PlotCurve();

    pKneeRight->ShowMarkers(Qt::red);
    pKneeRight->PlotCurve();
}

void MainWindow::GetValuesInterpol()
{
    CompleteJointPlot *pObjectChanged = (CompleteJointPlot*)sender();
    UpdateSimulationAndEndEffectPlot(pObjectChanged);
}

void  MainWindow::UpdateSimulationAndEndEffectPlot(CompleteJointPlot * &pObjectChanged)
{
    vector <double> vAngSamples;
    CompleteJointPlot *pRelativeObject;

    GetRobotObjectSampledValues(pObjectChanged, vAngSamples);

    for(unsigned int ippRobot = 0; ippRobot < 4; ippRobot++) {
        if(ppRobotObjects[ippRobot] == pObjectChanged) {
            if(ippRobot%2 == 0)
            {

                if(ppRobotObjects[ippRobot]->GetTitle() == "Right Hip") {
                    pObjectChanged = pHipRight;
                    pRelativeObject = pKneeRight;

                    pRobotMain->GetPlotRightHipValues(vAngSamples);
                }
                else if(ppRobotObjects[ippRobot]->GetTitle() == "Right Knee") {
                    pObjectChanged = pKneeRight;
                    pRelativeObject = pHipRight;
                    pRobotMain->GetPlotRightKneeValues(vAngSamples);
                }

              EndEffectorPlot(pEndEffectRight, pObjectChanged, pRelativeObject);
            }
            else
            {
                if(ppRobotObjects[ippRobot]->GetTitle() == "Left Hip") {
                    pObjectChanged = pHipLeft;
                    pRelativeObject = pKneeLeft;
                    pRobotMain->GetPlotLeftHipValues(vAngSamples);
                }
                else if(ppRobotObjects[ippRobot]->GetTitle() == "Left Knee") {
                    pObjectChanged = pKneeLeft;
                    pRelativeObject = pHipLeft;
                    pRobotMain->GetPlotLeftKneeValues(vAngSamples);
                }

                EndEffectorPlot(pEndEffectLeft, pObjectChanged, pRelativeObject);
            }
        }
    }

}

void MainWindow::EndEffectorPlot(CompleteEndEffectPlot* pEndEffector, CompleteJointPlot* pActualObject, CompleteJointPlot* pRelativeObject)

{
    vector <double> vHipAngleMarkers, vKneeAngleMarkers;
    vector <double> vHipAngleSamples, vKneeAngleSamples;
    vector <double> vXPositions, vYPositions;

    CompleteJointPlot *pHipObject, *pKneeObject;
    QString qsActualObject  = pActualObject->GetTitle();
    if (qsActualObject.contains("Hip")) {
            pHipObject = pActualObject;
            pKneeObject = pRelativeObject;
        }
    else if (qsActualObject.contains("Knee")) {
            pHipObject = pRelativeObject;
            pKneeObject = pActualObject;
    }

    GetRobotObjectSampledValues(pHipObject, vHipAngleSamples);
    GetRobotObjectSampledValues(pKneeObject, vKneeAngleSamples);

    pEndEffector->ExportPositions(lineEditThighLength->text().toDouble(), lineEditLowerLegLength->text().toDouble(), vXPositions , vYPositions, vHipAngleSamples , vKneeAngleSamples);
    pEndEffector->PlotCurve(vXPositions, vYPositions);

    // Exporting Hip Markers

    GetEndEffectMarkersAngles(pHipObject, pKneeObject, vHipAngleMarkers, vKneeAngleMarkers);
    pEndEffector->ImportHipMarkers(vHipAngleMarkers, vKneeAngleMarkers, Qt::blue);

    // Exporting Knee Markers

    GetEndEffectMarkersAngles(pKneeObject, pHipObject, vKneeAngleMarkers, vHipAngleMarkers );
    pEndEffector->ImportKneeMarkers(vHipAngleMarkers, vKneeAngleMarkers, Qt::red);

}

void MainWindow::RunAdamsSim()
{
    ButtonAdamsSim->setStyleSheet("QPushButton {border-radius: 2px;padding: 0.2em 0.2em 0.3em 0.2em;border: 1px solid rgb(100, 100,100);background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #34f32d, stop: 1 #000000);color: white;}");

    std::ostringstream ossStringLHip, ossStringRHip, ossStringLKnee, ossStringRKnee, ossStringTimeLeft, ossStringTimeRight,
            ossPeriod, ossCycles, ossDelay;

    vector <double> vTimeLeftLeg, vTimeRightLeg;
    vector <double> vHipR, vHipL, vKneeR, vKneeL;

    ossPeriod <<"period="<<lineEditPeriod->text().toStdString();
    ossCycles <<"cycles="<<lineEditCycles->text().toStdString();
    ossDelay <<"delay="<<lineEditDelay->text().toStdString();

    // Getting Time Values
    //GetTimeValues(vTimeValues);


    pHipRight->GetSamples(vTimeRightLeg);
    pHipLeft->GetSamples(vTimeLeftLeg);

    GetRobotObjectSampledValues(pHipLeft, vHipL);
    GetRobotObjectSampledValues(pHipRight, vHipR);
    GetRobotObjectSampledValues(pKneeLeft, vKneeL);
    GetRobotObjectSampledValues(pKneeRight, vKneeR);
    //pHipLeft->ExportMarkers(vTimeValues, vHipL);
    pHipLeft->GetValues(vTimeLeftLeg, vHipL);
    pHipRight->GetValues(vTimeRightLeg, vHipR);
    pKneeLeft->GetValues(vTimeLeftLeg, vKneeL);
    pKneeRight->GetValues(vTimeRightLeg, vKneeR);

    // Making string for left hip

    ossStringLHip << "vHipL=[";
    std::copy(vHipL.begin(), vHipL.end()-1, std::ostream_iterator <double>(ossStringLHip, " "));
    ossStringLHip << vHipL.back();
    ossStringLHip << "];";
    std::cout<<ossStringLHip.str()<<std::endl;

    // Making string for left hip

    ossStringRHip << "vHipR=[";
    std::copy(vHipR.begin(), vHipR.end()-1, std::ostream_iterator <double>(ossStringRHip, " "));
    ossStringRHip << vHipR.back();
    ossStringRHip << "];";

    // Making string for left knee

    ossStringLKnee << "vKneeL=[";
    std::copy(vKneeL.begin(), vKneeL.end()-1, std::ostream_iterator <double>(ossStringLKnee, " "));
    ossStringLKnee << vKneeL.back();
    ossStringLKnee << "];";

    // Making string for right knee

    ossStringRKnee << "vKneeR=[";
    std::copy(vKneeR.begin(), vKneeR.end()-1, std::ostream_iterator <double>(ossStringRKnee, " "));
    ossStringRKnee << vKneeR.back();
    ossStringRKnee << "];";

    // Making string for time values for Left Leg

    ossStringTimeLeft << "vTimeL=[";
    std::copy(vTimeLeftLeg.begin(), vTimeLeftLeg.end()-1, std::ostream_iterator <double>(ossStringTimeLeft, " "));
    ossStringTimeLeft << vTimeLeftLeg.back();
    ossStringTimeLeft << "];";
    std::cout<<ossStringTimeLeft.str()<<std::endl;

    // Making string for time values for Right Leg

    ossStringTimeRight << "vTimeR=[";
    std::copy(vTimeRightLeg.begin(), vTimeRightLeg.end()-1, std::ostream_iterator <double>(ossStringTimeRight, " "));
    ossStringTimeRight << vTimeRightLeg.back();
    ossStringTimeRight << "];";
    std::cout<<ossStringTimeRight.str()<<std::endl;

    Engine* m_matlabEngine;
    // Opening Matlab Engine
    m_matlabEngine=engOpen("\0");
    // Clearing
    engEvalString(m_matlabEngine, "clear;");
    engEvalString(m_matlabEngine, ossStringLHip.str().c_str());
    engEvalString(m_matlabEngine, ossStringTimeLeft.str().c_str());
    engEvalString(m_matlabEngine, ossStringTimeRight.str().c_str());
    engEvalString(m_matlabEngine, ossStringRHip.str().c_str());
    engEvalString(m_matlabEngine, ossStringRKnee.str().c_str());
    engEvalString(m_matlabEngine, ossStringLKnee.str().c_str());
    engEvalString(m_matlabEngine, ossPeriod.str().c_str());
    engEvalString(m_matlabEngine, ossCycles.str().c_str());
    engEvalString(m_matlabEngine, ossDelay.str().c_str());
    QString runEval(QString("run('%1');").arg("C:/Users/Zahid/GUI/RobotSim2/test_final_m2.m"));
    engEvalString(m_matlabEngine, "cd('C:/Users/Zahid/GUI/RobotSim2');");
    //engEvalString(m_matlabEngine, "Controls_Plant_2705_1");
    //engEvalString(m_matlabEngine, "open('test_final_model');");
    //engEvalString(m_matlabEngine, "sim('test_final_model');");
    engEvalString(m_matlabEngine, runEval.toUtf8().constData());
    engClose(m_matlabEngine);
    ButtonAdamsSim->setStyleSheet("QPushButton {border-radius: 2px;padding: 0.2em 0.2em 0.3em 0.2em;border: 1px solid rgb(100, 100,100);background: QLinearGradient( x1: 0, y1: 0.02, x2: 0, y2: 1.2, stop: 0 #220, stop: 1 #ffffff);color: white;}");
}

void MainWindow::ImportValsCurve()
{
    ImportCurveParameters iInterpolType;
    ImportCurveParameters iAngleUnits;
    ImportCurveParameters iPeriodMode;
    double dPeriod;

    CompleteJointPlot *pObjectChanged = (CompleteJointPlot*)sender();
    pObjectChanged->GetParamImpCurve(iInterpolType, iPeriodMode, iAngleUnits, dPeriod);

    lineEditPeriod->setText(QString::number(dPeriod));
    CommandPeriod->click();
    qDebug()<<"AngleUnits"<<iAngleUnits<<"PeriodMode"<<iPeriodMode<<"InterpolType"<<iInterpolType<<"AngleUnits"<<iAngleUnits<<"Period"<<dPeriod;
    ComboAngUnits->setCurrentIndex(iAngleUnits);
    ComboPeriodMode->setCurrentIndex(iPeriodMode);
    ComboInterpolMode->setCurrentIndex(iInterpolType);
}
