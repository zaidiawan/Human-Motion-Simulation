#include "CompleteJointPlot.h"
#include "Enumerations.h"
#include "TypeDefs.h"
#include <string>
#include <iostream>
#include <cmath>

CompleteJointPlot::CompleteJointPlot(QWidget *parent) :
    QWidget(parent)
{
    m_pConstantini = new Constantini97();
    m_pListModel = new  QStringListModel(this);
    m_pAddRemovDialog = new AddRemoveDialog(this);
    m_pSelectItemsDialog = new SelectItems(this);
    m_pqfdExport = new QFileDialog(this);
    m_pqfdImport = new QFileDialog(this);

    setupUi(this);

    connect(WidgetPlot, SIGNAL(Interpol()), this , SLOT(CatchInterpolSign()));

    connect(AddOrRemoveMarker, SIGNAL(clicked()), this, SLOT(OpenAddRemovDialog()));

    connect(m_pAddRemovDialog, SIGNAL(AddPressed()), SLOT(AddMarkerFromDialog()));

    connect(m_pAddRemovDialog, SIGNAL(RemovePressed()), SLOT(RemoveMarkerFromDialog()));

    connect(m_pAddRemovDialog, SIGNAL(CancelPressed()), SLOT(CloseAddRemovDialog()));

    connect(ButtonAddRemove, SIGNAL(clicked()), this, SLOT(AddRemoveModeSelected()));

    connect(m_pAddRemovDialog->ListMarkers, SIGNAL(clicked(QModelIndex)), this, SLOT(ListItemSelected(QModelIndex)));

    connect(ButtonMove, SIGNAL(clicked()), this, SLOT(MoveModeSelected()));

    connect(ButtonNoChange, SIGNAL(clicked()), this, SLOT(NoChangedModeSelected()));

    connect(m_pAddRemovDialog->checkBoxMarkers, SIGNAL(stateChanged(int)), this, SLOT(ControlListView()));

    connect(ButtonExportMarkers, SIGNAL(clicked()), this, SLOT(ExportMarkerstoFile()));

    connect(ButtonExportCurve, SIGNAL(clicked()), this, SLOT(OpenSelectListDialog()));

    connect(m_pSelectItemsDialog->ButtonOK, SIGNAL(clicked()), this, SLOT(ExportCurveToFile()));

    connect(m_pSelectItemsDialog, SIGNAL(rejected()), this, SLOT(ChangeStyleSheet()));

    connect(ButtonImportMarkers, SIGNAL(clicked()), this, SLOT(ImportMarkersFromFile()));

    connect(ButtonImportCurve, SIGNAL(clicked()), this, SLOT(ImportCurveFromFile()));

    connect(CheckBoxDelay, SIGNAL(clicked()), this, SLOT(ChangeCurveForDelay()));

    connect(m_pAddRemovDialog, SIGNAL(rejected()), this, SLOT(ChangeStyleSheet()));

    m_qsButtonPressedStr = QString("QPushButton {border-radius: 2px;padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(100, 100, 100);background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #34f32d, stop: 1 #000000); color: white;}");
    m_qsButtonNormalStr =  QString("QPushButton {border-radius: 2px;padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(100, 100, 100);background : lightgray;}");

    SetMarkersStatus(MarkersUnchanged);
    ButtonNoChange->setStyleSheet(m_qsButtonPressedStr);
}

bool CompleteJointPlot::SetPeriod ( double dPeriod )
{
    bool bSetPeriod = false;

    if (dPeriod > 0) {

        for(unsigned int uiMarker = 0; uiMarker < WidgetPlot->m_vTimeValues.size(); uiMarker++ ) {
            WidgetPlot->m_vTimeValues.at(uiMarker) = WidgetPlot->m_vTimeValues.at(uiMarker) * (dPeriod / WidgetPlot->m_dPeriodPlot);
        }

        WidgetPlot->m_dPeriodPlot = dPeriod;
        WidgetPlot->m_dInterpolPeriod = dPeriod;
        WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues);
        bSetPeriod = true;
    }
    return bSetPeriod;
}

bool CompleteJointPlot::SetInterpolPeriod(double dInterpolPeriod)
{
   WidgetPlot->SetInterpolPeriod(dInterpolPeriod);

   if (WidgetPlot->SetInterpolPeriod(dInterpolPeriod) == true)
       return true;
   else
       return false;
}
bool CompleteJointPlot::SetParameters(unsigned int uiMarkersNumber, double dPeriod, InterpolType_T itInterpolType, PeriodMode_T pmPeriodMode, AngleUnits_T auAngleUnits)
{
    WidgetPlot->m_uiMarkersNumber = uiMarkersNumber;
    WidgetPlot->m_dPeriodPlot = dPeriod;
    WidgetPlot->m_itInterpolType = itInterpolType;
    WidgetPlot->m_auAngleUnits = auAngleUnits;
    WidgetPlot->m_pmPeriodMode = pmPeriodMode;

    if (WidgetPlot->CheckMarkersNumber(uiMarkersNumber) == true &&
        WidgetPlot->CheckPeriod(dPeriod) == true &&
        WidgetPlot->CheckInterpolType(itInterpolType) == true &&
        WidgetPlot->CheckPeriodMode(pmPeriodMode) == true &&
        WidgetPlot->CheckAngleUnits(auAngleUnits) == true) {
        return true;
    }
    else
        return false;

}

bool CompleteJointPlot::SetParamImpCurve(double dPeriod, ImportCurveParameters iInterpolType, ImportCurveParameters iPeriodMode, ImportCurveParameters iAngleUnits)
{
    bool bSetParamStatus = false;
    if ((iInterpolType == 0 || iInterpolType == 1 || iInterpolType == 2 || iInterpolType == 3)  &&
        (iPeriodMode == 0 || iPeriodMode == 1) &&
        (iAngleUnits == 0 || iAngleUnits == 1) &&
            dPeriod > 0) {
        bSetParamStatus = true;
    }
    m_dPeriod = dPeriod;
    m_iInterpolType = iInterpolType;
    m_iPeriodMode = iPeriodMode;
    m_iAngleUnits = iAngleUnits;


    return bSetParamStatus;
}

bool CompleteJointPlot::SetPeriodMode(PeriodMode_T pmPeriodMode )
{
    double dScalingFactPeriod;
    bool bStatus = false;
    if ( WidgetPlot->CheckPeriodMode(pmPeriodMode) == true &&
         CheckPeriodMode(pmPeriodMode, dScalingFactPeriod) == true &&
         ModifyTimeUnits(dScalingFactPeriod) == true) {
         bStatus = true;
    }
    return bStatus;
}

bool CompleteJointPlot::SetSamples ( unsigned int uiNumSamples )
{
    bool bStatus = false;
    if (uiNumSamples > 0) {
        WidgetPlot->m_uiSamplesPlot = uiNumSamples;
        if (WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues) == true) {
            bStatus = true;
        }
    }
        return bStatus;
}

bool CompleteJointPlot::SetInterpolType ( InterpolType_T itInterpolType )
{
    bool bStatus = false;
    if (WidgetPlot->CheckInterpolType(itInterpolType) == true) {
        WidgetPlot->m_itInterpolType = itInterpolType;
        WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues);
        bStatus = true;
    }
    return bStatus;
}

bool CompleteJointPlot::SetAngleUnits ( AngleUnits_T auAngleUnits )
{
    double dScalingFactAngUnits;
    bool bStatus = false;
    if (WidgetPlot->CheckAngleUnits(auAngleUnits) == true &&
        CheckAngleUnits(auAngleUnits, dScalingFactAngUnits) == true &&
        ModifyAngUnits(dScalingFactAngUnits) == true ) {
        bStatus = true;
    }
    return bStatus;
}

bool CompleteJointPlot::SetMarkersStatus(MarkersStatus_T msMarkersStatus)
{
    if (msMarkersStatus == MarkersInserted || msMarkersStatus == MarkersUnchanged || msMarkersStatus == MarkersMoved) {
        WidgetPlot->m_msMarkersStatus = msMarkersStatus;
        return true;
    }
   else

        return false;

}
void CompleteJointPlot::SetDelay(double dDelay)
{

    WidgetPlot->m_dDelay = dDelay;
}

bool CompleteJointPlot::ImportMarkers ( vector <double> vTimeImport , vector <double> vAngleImport )
{
    bool Ok = false;
    if(vTimeImport.size() == vAngleImport.size()) {
        WidgetPlot->m_vTimeValues = vTimeImport;
        WidgetPlot->m_vAngleValues = vAngleImport;
        WidgetPlot->m_uiMarkersNumber = vTimeImport.size();
        if (WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues) == true) {
             WidgetPlot->RescaleAxis();
             Ok = true;
        }
    }
    return Ok;
}

bool CompleteJointPlot::ExportMarkers ( vector <double> &vTimeExport, vector <double> &vAngleExport)
{
    bool Ok = false;

    if (vTimeExport.size() == vAngleExport.size()) {
        vTimeExport = WidgetPlot->m_vTimeValues;
        vAngleExport = WidgetPlot->m_vAngleValues;
        Ok = true;
    }
    return Ok;
}

bool CompleteJointPlot::GetValues ( const vector <double> vTimeGet , vector<double> &vAngleGet)
{
    bool bGetValsStatus = true;
    vAngleGet.clear();

    QPolygonF qpfpolygonMarkers;
    qpfpolygonMarkers = WidgetPlot->MakeValsPeriodic(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues);
    vector <float> v_fAngleValuesd, v_fAngleValuesdd, v_fAnglesGet;
    vector <float> v_fTimeValues(WidgetPlot->m_vTimeValues.begin(), WidgetPlot->m_vTimeValues.end());
    vector <float> v_fAngleValues(WidgetPlot->m_vAngleValues.begin(), WidgetPlot->m_vAngleValues.end());
    vector <float> v_fTimeGet(vTimeGet.begin(), vTimeGet.end());
    vector <float> v_fTimeMarkersPeriodic;
    vector <float> v_fAngleMarkersPeriodic;

    /* Problem for The Constantini Spline
     * If the input sample time values at which it is required to get the values are not
     * in order then interpolation fails. If we use the technique of MOD operator to pack
     * the values always with time period then the time values are definitely not in order
     * and interpolation fails. So the only solution which is left is to use the same procedure
     * used for Akima and Cubic Spline interpolation techniques
     */

    for (int iPoly = 0; iPoly < qpfpolygonMarkers.size(); iPoly++) {
        v_fTimeMarkersPeriodic.push_back(qpfpolygonMarkers.at(iPoly).x());
        v_fAngleMarkersPeriodic.push_back(qpfpolygonMarkers.at(iPoly).y());
        //qDebug()<<vAnglePeriodic.at(iPoly);
    }

    for(unsigned int iSamples = 0 ; iSamples < vTimeGet.size() ; iSamples++) {
        if (WidgetPlot->m_itInterpolType == cubic) {
            vAngleGet.push_back(WidgetPlot->m_pqwtSpline->value(vTimeGet.at(iSamples) + WidgetPlot->m_dInterpolPeriod) );
        }
        else if (WidgetPlot->m_itInterpolType == akima) {
            vAngleGet.push_back(WidgetPlot->m_asSpline(vTimeGet.at(iSamples) + WidgetPlot->m_dInterpolPeriod));
        }
    }
    if (WidgetPlot->m_itInterpolType == Constantini || WidgetPlot->m_itInterpolType == CFourier) {
        if (WidgetPlot->m_itInterpolType == Constantini) {
            // The period is multiplied with 4 because of the technique of periodicity mentioned above
            m_pConstantini->calc(v_fTimeMarkersPeriodic, v_fAngleMarkersPeriodic, v_fTimeGet, v_fAnglesGet, v_fAngleValuesd, v_fAngleValuesdd, float(WidgetPlot->m_dInterpolPeriod)* 4, 6);

        }
        else if (WidgetPlot->m_itInterpolType == CFourier) {
             m_pConstantini->calc_fourier(v_fTimeValues, v_fAngleValues, v_fTimeGet, v_fAnglesGet, v_fAngleValuesd, v_fAngleValuesdd, float(WidgetPlot->m_dInterpolPeriod), 6, 100);
        }

        vector <double> vAnglesOut(v_fAnglesGet.begin(), v_fAnglesGet.end());
        vAngleGet = vAnglesOut;

        if (CheckVectorOfZeroes(WidgetPlot->m_vAngleValues) == false && CheckVectorOfZeroes(vAnglesOut) == true) {
            bGetValsStatus = false;
        }
    }
    return bGetValsStatus;
}

void CompleteJointPlot::GetSamples(vector <double> &vTimeValues)

{
    vTimeValues.clear();
    double dTimeValue = 0;

    for(unsigned int uiMarker = 0; uiMarker < WidgetPlot->m_uiSamplesPlot; uiMarker++) {

        //vTimeValues.push_back(dTimeValue + WidgetPlot->m_dInterpolPeriod + fmod(WidgetPlot->m_dDelay, WidgetPlot->m_dInterpolPeriod) );
        //vTimeValues.push_back(fmod(dTimeValue + WidgetPlot->m_dDelay, WidgetPlot->m_dInterpolPeriod) );
        vTimeValues.push_back(dTimeValue + WidgetPlot->m_dDelay + WidgetPlot->m_dInterpolPeriod);
        dTimeValue += (WidgetPlot->m_dInterpolPeriod / (double)WidgetPlot->m_uiSamplesPlot );
    }
}

bool CompleteJointPlot::GetParameters(unsigned int &uiMarkersNumber, double &dPeriod, InterpolType_T &itInterpolType, PeriodMode_T &pmPeriodMode, AngleUnits_T &auAngleUnits)
{
    bool bGetParametersStatus = false;
    uiMarkersNumber = WidgetPlot->m_uiMarkersNumber;
    dPeriod = WidgetPlot->m_dPeriodPlot;
    itInterpolType = WidgetPlot->m_itInterpolType;
    pmPeriodMode = WidgetPlot->m_pmPeriodMode;
    auAngleUnits = WidgetPlot->m_auAngleUnits;
    if (WidgetPlot->CheckMarkersNumber(uiMarkersNumber) == true &&
        WidgetPlot->CheckPeriod(pmPeriodMode) == true &&
        WidgetPlot->CheckAngleUnits(auAngleUnits) == true &&
        WidgetPlot->CheckInterpolType(itInterpolType) == true &&
        WidgetPlot->CheckPeriodMode(pmPeriodMode) == true) {
        bGetParametersStatus = true;
    }
    return bGetParametersStatus;

}
bool CompleteJointPlot::GetParamImpCurve(ImportCurveParameters &iInterpolType, ImportCurveParameters &iPeriodMode, ImportCurveParameters &iAngleUnits, double &dPeriod)
{
    bool bGetImpCurveStatus = false;
    iInterpolType = m_iInterpolType;
    iPeriodMode = m_iPeriodMode;
    iAngleUnits = m_iAngleUnits;
    dPeriod = m_dPeriod;
    if ((iInterpolType == 0 || iInterpolType == 1 || iInterpolType == 2 || iInterpolType == 3)  &&
        (iPeriodMode == 0 || iPeriodMode == 1) &&
        (iAngleUnits == 0 || iAngleUnits == 1) &&
            dPeriod > 0) {
        bGetImpCurveStatus = true;
    }
    return bGetImpCurveStatus;

}

void CompleteJointPlot::CatchInterpolSign()
{
    emit InterpolationCompleted();
}

void CompleteJointPlot::RemoveAllMarkers()
{
    for(unsigned int iMarker =0; iMarker < WidgetPlot->m_uiMarkersCount; iMarker++) {
        WidgetPlot->m_pMarkerArray[iMarker].detach();
    }
    WidgetPlot->m_uiMarkersCount =0;
}

void CompleteJointPlot::SetTitle(QString qsTitle)
{
    WidgetPlot->m_qsTitle = qsTitle;
    WidgetPlot->setTitle(qsTitle);
}

bool CompleteJointPlot::ImportMarkers ( vector <double> vTimeImport , vector<double> vAngleImport, AngleUnits_T auAngleUnits, PeriodMode_T pmPeriodMode)
{
    bool bImportMarkersStatus = false;
    if (vTimeImport.size() == vAngleImport.size() && ( auAngleUnits == radians || auAngleUnits == degrees) && (pmPeriodMode == time || pmPeriodMode == percent ) ) {

        double dScalingFactPeriod, dScalingFactAngUnits;
        WidgetPlot->m_vTimeValues = vTimeImport;
        WidgetPlot->m_vAngleValues = vAngleImport;
        WidgetPlot->m_uiMarkersNumber = vTimeImport.size();

        if (CheckAngleUnits(auAngleUnits, dScalingFactAngUnits) == true &&
            CheckPeriodMode(pmPeriodMode, dScalingFactPeriod)   == true &&
            ModifyTimeUnits(dScalingFactPeriod) == true &&
            ModifyAngUnits(dScalingFactAngUnits) == true) {
            WidgetPlot->RescaleAxis();
            bImportMarkersStatus = true;
        }

    }
     return bImportMarkersStatus;

}


bool CompleteJointPlot::AddMarker(double dXMarker, double dYMarker)
{
    QStringList qsList;

    for(unsigned int i = 0; i< WidgetPlot->m_uiMarkersNumber; i++) {
        qsList.append(QString::number(i));
    }
    m_pListModel->setStringList(qsList);
    if (WidgetPlot->AddMarker(dXMarker, dYMarker) == true) {
       //WidgetPlot->AddMarkers(WidgetPlot->m_vTimeValues , WidgetPlot->m_vAngleValues);
        return true;
    }
    else
        return false;
}

bool CompleteJointPlot::RemoveMarker(double dTimeValue)
{
    bool bRemoveMarkerStatus = false;
    double dTruncDialogTimeVal, dTruncActTimeVal;
    dTruncDialogTimeVal = WidgetPlot->TruncateDecimalPlaces(dTimeValue);

    for(unsigned int uiMarker = 0; uiMarker  < WidgetPlot->m_uiMarkersNumber ; uiMarker++) {
    dTruncActTimeVal = WidgetPlot->TruncateDecimalPlaces(WidgetPlot->m_vTimeValues.at(uiMarker));
        if ((dTruncActTimeVal == dTruncDialogTimeVal) && (WidgetPlot->m_uiMarkersNumber > 2)) {

             if (WidgetPlot->RemoveMarker(uiMarker) == true) {
                 bRemoveMarkerStatus = true;
             }

        }
    }
    return bRemoveMarkerStatus;
}

bool CompleteJointPlot::AddMarkers(vector <double> vXMarkers, vector<double> vYMarkers, Qt::GlobalColor qtgcGlobalColor)
{
    if  (WidgetPlot->AddMarkers(vXMarkers, vYMarkers, qtgcGlobalColor ) == true )
        return true;
    else
        return false;
}

bool CompleteJointPlot::ShowMarkers(Qt::GlobalColor qtgcGlobalColor)
{
    if (WidgetPlot->AddMarkers(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues, qtgcGlobalColor) == true)
        return true;
    else
        return false;
}

vector <double> CompleteJointPlot::ConcatenateVectors (const vector <double> vInputA, vector <double> &vInputB)
{
    std::vector <double> AB;
    AB.reserve(vInputA.size() + vInputB.size());
    AB.insert(AB.end(), vInputA.begin(), vInputA.end());
    AB.insert(AB.end(), vInputB.begin(), vInputB.end());
    return AB;
}

bool CompleteJointPlot::CheckPeriodMode(PeriodMode_T pmPeriodMode, double &dScalingFactPeriod)
{
    switch (pmPeriodMode)
    {
    case percent:
                           if (WidgetPlot->m_pmPeriodMode == percent) {
                               dScalingFactPeriod = 1;
                               break;
                           }

                           else if (WidgetPlot->m_pmPeriodMode == time) {
                               WidgetPlot->m_pmPeriodMode = percent;
                               SetInterpolPeriod(100.0);
                               dScalingFactPeriod =  (100.0 / WidgetPlot->m_dPeriodPlot);
                               break;
                           }
    case time:
                           if (WidgetPlot->m_pmPeriodMode == time) {
                               dScalingFactPeriod = 1;
                               break;
                           }

                           else if (WidgetPlot->m_pmPeriodMode == percent) {
                               WidgetPlot->m_pmPeriodMode = time;
                               SetInterpolPeriod(WidgetPlot->m_dPeriodPlot);
                               dScalingFactPeriod = (WidgetPlot->m_dPeriodPlot / 100.0);
                               break;
                           }
    }

    if (dScalingFactPeriod > 0)
        return true;
    else
        return false;


}

bool CompleteJointPlot::CheckAngleUnits(AngleUnits_T auAngleUnits, double &dScalingFactAngUnits)
{
    switch (auAngleUnits)
    {
    case radians:           if (WidgetPlot->m_auAngleUnits == radians) {
                                dScalingFactAngUnits = 1;
                                break;
                            }


                            else if (WidgetPlot->m_auAngleUnits == degrees) {

                                WidgetPlot->m_auAngleUnits = radians;
                                dScalingFactAngUnits =  M_PI / 180;
                                break;
                            }
   case degrees:
                            if (WidgetPlot->m_auAngleUnits == degrees) {
                                dScalingFactAngUnits = 1;
                                break;
                            }

                            else if (WidgetPlot->m_auAngleUnits == radians) {

                                WidgetPlot->m_auAngleUnits = degrees;
                                dScalingFactAngUnits = 180 / M_PI;
                                break;
                            }
    }

    if (dScalingFactAngUnits > 0)
        return true;
    else
        return false;

}

bool CompleteJointPlot::ModifyTimeUnits(double dScalingFactPeriod)
{
    for(unsigned int uiMarker = 0; uiMarker < WidgetPlot->m_vTimeValues.size(); uiMarker++ ) {

        WidgetPlot->m_vTimeValues.at(uiMarker) = WidgetPlot->m_vTimeValues.at(uiMarker) * dScalingFactPeriod;
    }

    if (WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues) == true && dScalingFactPeriod > 0 ) {
        return true;
    }
    else
        return false;

}

bool CompleteJointPlot::ModifyAngUnits(double dScalingFactAngUnits)
{
    for(unsigned int uiMarker = 0; uiMarker < WidgetPlot->m_vTimeValues.size(); uiMarker++ ) {
        WidgetPlot->m_vAngleValues.at(uiMarker) = WidgetPlot->m_vAngleValues.at(uiMarker) * dScalingFactAngUnits;
    }

    if (WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues) == true && dScalingFactAngUnits >0) {
        WidgetPlot->RescaleAxis();
        return true;
    }
    else
        return false;
}

void CompleteJointPlot::OpenAddRemovDialog()
{
    m_pAddRemovDialog->show();
    AddOrRemoveMarker->setStyleSheet(m_qsButtonPressedStr);

}

void CompleteJointPlot::ExportCurveToFile()
{
    vector <double> vTimeSamples, vAngleSamples, vTimeValues, vAngleValues;
    bool bExportMarkersStatus, bGetSamplesStatus;
    ButtonExportCurve->setStyleSheet(m_qsButtonPressedStr);
    ButtonImportCurve->setStyleSheet(m_qsButtonNormalStr);
    QString qsSavedFileName = m_pqfdExport->getSaveFileName(this, tr("Save As"), "C:/Users/Zahid/GUI/RobotSim2" , tr("Text files (*.txt);;CSV files (*.csv);;DAT files (*.DAT)"));
    QFile FileExport(qsSavedFileName);
    QTextStream out(&FileExport);
    FileExport.open(QIODevice::WriteOnly|QIODevice::Text);

    bExportMarkersStatus = ExportMarkers(vTimeValues, vAngleValues);
    WidgetPlot->GetPlotSamples(vTimeSamples, vAngleSamples);
    if (m_pSelectItemsDialog->checkBoxPeriod->isChecked() && m_pSelectItemsDialog->radioButtonNormal->isChecked()) {
        out <<"T\t"<<WidgetPlot->m_dPeriodPlot<<"\n\n";
    }
    if (m_pSelectItemsDialog->checkBoxItType->isChecked() && m_pSelectItemsDialog->radioButtonNormal->isChecked()) {
        out <<"Interpol\t"<<WidgetPlot->m_itInterpolType<<"\n\n";
    }
    if (m_pSelectItemsDialog->checkBoxAngUnits->isChecked() && m_pSelectItemsDialog->radioButtonNormal->isChecked()) {
        out <<"AngUnits\t"<<WidgetPlot->m_auAngleUnits<<"\n\n";
    }
    if (m_pSelectItemsDialog->checkBoxPeriodMode->isChecked() && m_pSelectItemsDialog->radioButtonNormal->isChecked()) {
        out <<"PeriodMode\t"<<WidgetPlot->m_pmPeriodMode<<"\n\n";
    }

    if (m_pSelectItemsDialog->checkBoxVals->isChecked() && m_pSelectItemsDialog->radioButtonNormal->isChecked()) {
        if (bExportMarkersStatus == true) {
            for (unsigned int i = 0; i < vTimeValues.size(); i++) {
                out << fmod(vTimeValues.at(i), WidgetPlot->m_dInterpolPeriod)  <<"\t"<<vAngleValues.at(i)<<"\n";
            }
        }
        out <<"**\t**\t**\n";
    }

    if (m_pSelectItemsDialog->checkBoxSamples->isChecked()) {
        if (bGetSamplesStatus == true) {
            for (unsigned int i = 0; i < vTimeSamples.size(); i++) {
            out << fmod(vTimeSamples.at(i), WidgetPlot->m_dInterpolPeriod) <<"\t"<<vAngleSamples.at(i)<<"\n";
            }
        }

    }

    FileExport.close();
    ButtonExportCurve->setStyleSheet(m_qsButtonNormalStr);
}


void CompleteJointPlot::OpenSelectListDialog()
{
    m_pSelectItemsDialog->show();
    m_pSelectItemsDialog->radioButtonNormal->setChecked(true);
    ButtonExportCurve->setStyleSheet(m_qsButtonPressedStr);

}

void CompleteJointPlot::AddMarkerFromDialog()
{
    double dTimeValue, dAngleValue;

    m_pAddRemovDialog->GetMarkerValues(dTimeValue, dAngleValue);
    AddMarker(dTimeValue, dAngleValue);
    ControlListView();

}

void CompleteJointPlot::RemoveMarkerFromDialog()
{
    QStringList qsList;
    double dTimeValue, dAngleValue;
    m_pAddRemovDialog->GetMarkerValues(dTimeValue, dAngleValue);
    if (WidgetPlot->m_uiMarkersNumber > 4) {
        RemoveMarker(dTimeValue);
    }

    for(unsigned int i = 0; i< WidgetPlot->m_uiMarkersNumber; i++) {

        qsList.append(QString::number(i));
    }
    m_pListModel->setStringList(qsList);
    m_pAddRemovDialog->ListMarkers->setModel(m_pListModel);
}

void CompleteJointPlot::CloseAddRemovDialog()
{
    AddOrRemoveMarker->setStyleSheet(m_qsButtonNormalStr);
}

void CompleteJointPlot::AddRemoveModeSelected()
{

      ButtonAddRemove->setStyleSheet(m_qsButtonPressedStr);
      ButtonMove->setStyleSheet(m_qsButtonNormalStr);
      ButtonNoChange->setStyleSheet(m_qsButtonNormalStr);
      SetMarkersStatus(MarkersInserted);
}
void CompleteJointPlot::ListItemSelected(QModelIndex iMarkerIndex)
{
    //qDebug()<<WidgetPlot->m_vTimeValues.at(iMarkerIndex.row())<<" "<<WidgetPlot->m_vAngleValues.at(iMarkerIndex.row());
    m_pAddRemovDialog->TextTime->setText(QString::number(WidgetPlot->m_vTimeValues.at(iMarkerIndex.row())));
    m_pAddRemovDialog->TextAngle->setText(QString::number(WidgetPlot->m_vAngleValues.at(iMarkerIndex.row())));
}

void CompleteJointPlot::MoveModeSelected()
{
    ButtonMove->setStyleSheet(m_qsButtonPressedStr);
    ButtonAddRemove->setStyleSheet(m_qsButtonNormalStr);
    ButtonNoChange->setStyleSheet(m_qsButtonNormalStr);
    SetMarkersStatus(MarkersMoved);

}

void CompleteJointPlot::NoChangedModeSelected()
{
    ButtonMove->setStyleSheet(m_qsButtonNormalStr);
    ButtonAddRemove->setStyleSheet(m_qsButtonNormalStr);
    ButtonNoChange->setStyleSheet(m_qsButtonPressedStr);

    SetMarkersStatus(MarkersUnchanged);
}

void CompleteJointPlot::ControlListView()
{
    QStringList qsList;
    vector <double> vTimeValues, vAngleValues;
    ExportMarkers(vTimeValues, vAngleValues);
    // If Checkbox is Checked, display the markers
    if(m_pAddRemovDialog->checkBoxMarkers->isChecked()) {
        for(unsigned int i = 0; i< WidgetPlot->m_uiMarkersNumber; i++) {

            qsList.append(QString::number(i));
        }
        m_pListModel->setStringList(qsList);
        m_pAddRemovDialog->ListMarkers->setModel(m_pListModel);
    }
    else if(!m_pAddRemovDialog->checkBoxMarkers->isChecked()) {
        qsList.clear();
        m_pListModel->setStringList(qsList);
    }
}

void CompleteJointPlot::ExportMarkerstoFile()
{
    ButtonExportMarkers->setStyleSheet(m_qsButtonPressedStr);
    ButtonImportMarkers->setStyleSheet(m_qsButtonNormalStr);
    QString qsSavedFileName = m_pqfdExport->getSaveFileName(this, tr("Save As"), "C:/Users/Zahid/GUI/RobotSim" , tr("Text files (*.txt);;CSV files (*.csv);;DAT files (*.DAT)"));
    ButtonExportMarkers->setStyleSheet(m_qsButtonNormalStr);
    vector <double> vTimeValues, vAngleValues;
    bool bExportStatus;
    bExportStatus = ExportMarkers(vTimeValues, vAngleValues);

    QFile FileExport(qsSavedFileName);
    FileExport.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&FileExport);
    //out <<"TimeValues\t\tAngleValues\n\n";
    if (bExportStatus == true) {
        for (unsigned int i = 0; i < vTimeValues.size(); i++) {
            out << vTimeValues.at(i) <<"\t"<<vAngleValues.at(i)<<"\n";
        }
    }

    FileExport.close();
}

void CompleteJointPlot::ImportMarkersFromFile()
{
    ButtonImportMarkers->setStyleSheet(m_qsButtonPressedStr);
    ButtonExportMarkers->setStyleSheet(m_qsButtonNormalStr);
    QString qsOpenedFileName = m_pqfdImport->getOpenFileName(this, tr("Open"), "C:/Users/Zahid/GUI/RobotSim" , tr("Text files (*.txt);;CSV files (*.csv);;DAT files (*.DAT)"));
    ButtonImportMarkers->setStyleSheet(m_qsButtonNormalStr);
    vector <double> vTimeValues, vAngleValues;
    bool bImportStatus;
    QFile FileImport(qsOpenedFileName);
    if (!FileImport.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QTextStream qtsIn(&FileImport);
    qtsIn.skipWhiteSpace();
    while (!qtsIn.atEnd()) {
        QString qsLine = qtsIn.readLine();
        QStringList qslList = qsLine.split('\t');
        vTimeValues.push_back(qslList.at(0).toDouble());
        vAngleValues.push_back(qslList.at(1).toDouble());
        //process_line(line);
        }
    for(unsigned int i =0; i< vAngleValues.size();i++) {
        //qDebug()<<vAngleValues.at(i);
    }
    bImportStatus = ImportMarkers(vTimeValues, vAngleValues);
    RemoveAllMarkers();
    WidgetPlot->AddMarkers(vTimeValues, vAngleValues);
    WidgetPlot->PlotCurve();


}


void CompleteJointPlot::ImportCurveFromFile()
{
    ImportCurveParameters iInterpolType;
    ImportCurveParameters iAngleUnits;
    ImportCurveParameters iPeriodMode;
    double dPeriod;
    bool bImportStatus;

    ButtonImportCurve->setStyleSheet(m_qsButtonPressedStr);
    ButtonExportCurve->setStyleSheet(m_qsButtonNormalStr);
    QString qsOpenedFileName = m_pqfdImport->getOpenFileName(this, tr("Open"), "C:/Users/Zahid/GUI/RobotSim2" , tr("Text files (*.txt);;CSV files (*.csv);;DAT files (*.DAT)"));
    ButtonImportCurve->setStyleSheet(m_qsButtonNormalStr);
    vector <double> vTimeValues, vAngleValues;
    QString qsLine;
    QStringList qslList;
    QFile FileImport(qsOpenedFileName);
    if (!FileImport.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QTextStream qtsIn(&FileImport);
    qtsIn.skipWhiteSpace();

    while (!qtsIn.atEnd()) {
        qsLine = qtsIn.readLine();
        qslList = qsLine.split('\t');
        if (qslList.at(0) == "T") {
            dPeriod = (qslList.at(1).toDouble());
        }
        else if (qslList.at(0) == "Interpol") {
            iInterpolType = (InterpolType_T) qslList.at(1).toInt();
        }
        else if (qslList.at(0) == "AngUnits") {
            iAngleUnits = (AngleUnits_T)qslList.at(1).toInt();
        }
        else if (qslList.at(0) == "PeriodMode") {
            iPeriodMode = (PeriodMode_T)qslList.at(1).toInt();
        }
        else if (!((qslList.at(0) == "") || (qslList.at(0) == "**" ))) {
            vTimeValues.push_back(qslList.at(0).toDouble());
            vAngleValues.push_back(qslList.at(1).toDouble());
        }


    }
    //qDebug()<<"1AngleUnits"<<iAngleUnits<<"PeriodMode"<<iPeriodMode<<"InterpolType"<<iInterpolType<<"AngleUnits"<<iAngleUnits<<"Period"<<dPeriod;
    SetParamImpCurve(dPeriod, iInterpolType, iPeriodMode, iAngleUnits);
    emit ImportCurve();
    bImportStatus = ImportMarkers(vTimeValues, vAngleValues);
    RemoveAllMarkers();
    WidgetPlot->AddMarkers(vTimeValues, vAngleValues);
    WidgetPlot->PlotCurve();


}
bool CompleteJointPlot::CheckVectorOfZeroes(vector <double> vInput)
{
    bool bZeroStatus = true;
    for(vector <double>::iterator it = vInput.begin(); it != vInput.end(); it++) {
        if (*it !=0) {
            bZeroStatus = false;
        }
    }
    return bZeroStatus;

}
void CompleteJointPlot::ChangeCurveForDelay()
{
    if (CheckBoxDelay->isChecked()) {
        WidgetPlot->m_csCurveStatus = ShowDelayed;
    }
    else
        WidgetPlot->m_csCurveStatus = ShowWithoutDelay;
    WidgetPlot->Interpolation(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues);
    PlotCurve();
    AddMarkers(WidgetPlot->m_vTimeValues, WidgetPlot->m_vAngleValues);
}

void CompleteJointPlot::ChangeStyleSheet()
{
    ButtonExportCurve->setStyleSheet(m_qsButtonNormalStr);
    AddOrRemoveMarker->setStyleSheet(m_qsButtonNormalStr);
    ButtonImportCurve->setStyleSheet(m_qsButtonNormalStr);


}

