#ifndef COMPLETEJOINTPLOT_H
#define COMPLETEJOINTPLOT_H

#include "ui_CompleteJointPlot.h"
#include "Enumerations.h"
#include "JointPlot.h"
#include "AddRemoveDialog.h"
#include "SelectItems.h"
#include "constantini97.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QFile>



/*!
  *     \file       CompleteJointPlot.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      This class has the double inheritance, and is derived from QWidget and Ui::CompleteJointPlot.
  *                 The namespace includes the class ui_CompleteJointPlot and consists of a custom designed widget and also other Qt- based widgets.
  *                 The custom designed widget is called WidgetPlot , which is promoted to class JointPlot. This class has the following functionalities:
  *                 1) Adding or Removing the markers with the help of a dialog which allows the user to pick-up a marker out of a list to remove and to enter the marker value to add
  *                 2) Add, Move, or remove the markers with the help of mouse.
  *                 3) Exporting curves with the help of a dialog which gives several options to the user to select from i.e marker values, samples, period, interpolation-type, angle-units ( radians or degrees), period-mode (time or percent).
  *                 4)Importing curves with the help of a file dialog which allows a file to be imported in specific format
  *                 5)Markers can be imported and exported in different formats
  *
*/

class MainWindow;

class CompleteJointPlot : public QWidget, protected Ui::CompleteJointPlot
{
    Q_OBJECT

public:


    explicit CompleteJointPlot(QWidget *parent = 0);

    /*!  Imports the markers in the form of vectors of type double with the angle units and period mode. The time
     *   and angle values of the markers are imported separately as vectors
     *  \param[in]  vTimeImport vector of time values of markers to be imported
     *  \param[in]  vAngleImport    vector of angle values of markers to be imported
     *  \param[in]  auAngleUnits    angle units of type enum AngleUnits_T
     *  \param[in]  pmPeriodMode    period mode of type enum PeriodMode_T
     *  \retval true if the the sizes of the time and angle values vectors are same, the angle units and period mode are valid,
     *          the angle and time units are modified correctly, false otherwise
     */
    bool ImportMarkers ( std::vector <double> vTimeImport , std::vector <double> vAngleImport, AngleUnits_T auAngleUnits , PeriodMode_T pmPeriodMode );

    /*!  Imports the markers in the form of vectors of type double. The time and angle values of the markers are imported separately as vectors
     *  \param[in]  vTimeImport vector of time values of markers to be imported
     *  \param[in]  vAngleImport    vector of angle values of markers to be imported
     *  \retval true if the the sizes of the time and angle values vectors are same, and the interpolation is ok. otherwise return false
     */
    bool ImportMarkers ( std::vector <double> vTimeImport , std::vector <double> vAngleImport);

    /*!  Exports the markers in the form of vectors of type double. The time and angle values of the markers are exported separately as vectors
     *  \param[out]  vTimeExport vector of time values of markers to be exported
     *  \param[out]  vAngleExport    vector of angle values of markers to be exported
     *  \retval true if the the sizes of the time and angle values of markers as vectors are same, false otherwise
     */
    bool ExportMarkers ( std::vector <double> &vTimeExport, std::vector <double> &vAngleExport);

   /*!  Adds the marker of type double to the plot.
    *  \param[out]  dXMarker Marker's time value of type double to be added
    *  \param[out]  dYMarker Marker's angle value of type double to be added
    *  \retval returns true if the marker is added succesfuly to the plot. That means that after adding the marker rearrangement,
               interpolation, and plotting was successful
    */
    bool AddMarker(double dXMarker, double dYMarker);

    /*!  Adds the markers of default color red in vectors of type double to the plot.
     *  \param[in]   vXMarkers vector of type double consisting of marker time values
     *  \param[in]   vYMarkers vector of type double consisting of marker angle values
     *  \param[in]   qtgcGlobalColor color of type Qt::GlobalColor, used to assign the color to the markers
     *  \retval returns true if the vectors of markers are added succesfuly to the plot and false otherwise
     */
    bool AddMarkers(std::vector <double> vXMarkers, std::vector<double> vYMarkers, Qt::GlobalColor qtgcGlobalColor = Qt::red);

   /*!  Adds the markers to the plot in specific color
    *  \param[in]   qtgcGlobalColor color of type Qt::GlobalColor assigned to the markers
    *  \retval returns true if the vectors of markers (time and angle) in the plot to be shown are of equal number and false otherwise
    */
    bool ShowMarkers(Qt::GlobalColor qtgcGlobalColor);

   /*!  Removes the marker with specific time of type double
    *  \param[in]   dTimeValue time value of type double of the marker to be removed
    *  \retval returns true if after marker's removal, rearrangement of markers, interpolation and replotting is successful, false otherwise
    */
    bool RemoveMarker(double dTimeValue);

    //! Remove all the markers in the plot
    void RemoveAllMarkers();


   /*!  Gets the interpolated angle value for specific time
    *  \param[in]  vTimeGet The vector of type double consisting of time values for which the interpolated angle value is needed
    *  \param[out] vAngleGet The vector of type double which are the interpolated values for the time values provided in the form of vector
    *  \retval returns true if for non-zero vector of original markers, all the values obtained after interpolation
    *          for the given time vector, are zero
    */
    bool GetValues ( const std::vector <double> vTimeGet , std::vector<double> &vAngleGet);

    //! Get the time samples depending upon the period, the mode of time selected and the number of samples
    void GetSamples(std::vector <double> &vTimeValues);

    //! Get the the number of samples in the plot of type unsigned int
    unsigned int GetNumSamples () { return WidgetPlot->m_uiSamplesPlot;}

    //! Get the period of type double being used in the plot
    double GetPeriod () { return WidgetPlot->m_dPeriodPlot; }

    //! Get the period of interpolation of type double from the plot
    void GetInterpolPeriod(double &dInterpolCycle) { WidgetPlot->GetInterpolPeriod(dInterpolCycle); }

    //! Get the delay from the plot
    double GetDelay() { return WidgetPlot->m_dDelay; }

   /*!  Gets the parameters Markers number, period, interpolation type, period mode, angle units from the plot
    *  \param[out]  uiMarkersNumber  Number of markers used in the plot of type unsigned int
    *  \param[out]  dPeriod  Period in the plot of type double
    *  \param[out]  itInterpolType Inteprolation type from the plot of type enum IntepolType_T
    *  \param[out]  pmPeriodMode  Period mode selected of type enum PeriodMode_T
    *  \param[out]  auAngleUnits  Angle units selected of type enum AngleUnits_T
    *  \retval returns true if all the parameters in the plot are valid, false otherwise
    */
    bool GetParameters(unsigned int &uiMarkersNumber, double &dPeriod, InterpolType_T &itInterpolType, PeriodMode_T &pmPeriodMode, AngleUnits_T &auAngleUnits);

   /*!  Gets the index of the parameters interpolation type, period mode, angle units from the plot
    *  \param[out]  itInterpolType index of Inteprolation type from the plot of type enum IntepolType_T
    *  \param[out]  pmPeriodMode  index of Period mode selected of type enum PeriodMode_T
    *  \param[out]  auAngleUnits  index of Angle units selected of type enum AngleUnits_T
    *  \retval returns true if all the indices of parameters in the plot are valid, false otherwise
    *
    */
    bool GetParamImpCurve(ImportCurveParameters &iInterpolType, ImportCurveParameters &iPeriodMode, ImportCurveParameters &iAngleUnits, double &dPeriod);

    //! Get the title of the plot of type QString
    QString GetTitle() { return WidgetPlot->m_qsTitle; }

    //! Get the interpolation type from the plot
    InterpolType_T GetInterpolType () { return WidgetPlot->m_itInterpolType; }

    //! Get the angle units from the plot
    AngleUnits_T GetAngleUnits () { return WidgetPlot->m_auAngleUnits; }

    //! Get the period mode from the plot
    PeriodMode_T GetPeriodMode () { return WidgetPlot->m_pmPeriodMode;}

    //! Set the period of plot of type double, return true if period is positive, false otherwise
    bool SetPeriod ( double dPeriod );

    //! Set the period of interpolation. returns true if interpolation period is valid, false otherwise
    bool SetInterpolPeriod (double dInterpolPeriod);

   /*!  Sets the parameters Markers number, period, interpolation type, period mode, angle units from the plot
    *  \param[out]  uiMarkersNumber  Number of markers to be set in the plot of type unsigned int
    *  \param[out]  dPeriod  Period to be set in the plot of type double
    *  \param[out]  itInterpolType Inteprolation type to be set in the plot of type enum IntepolType_T
    *  \param[out]  pmPeriodMode  Period mode to be set of type enum PeriodMode_T
    *  \param[out]  auAngleUnits  Angle units to be set of type enum AngleUnits_T
    *  \retval returns true if all the parameters to be set in the plot are valid, false otherwise
    *
    */
    bool SetParameters (unsigned int uiMarkersNumber, double dPeriod, InterpolType_T itInterpolType, PeriodMode_T pmPeriodMode, AngleUnits_T auAngleUnits);

    /*!  Sets the indices of the parameters interpolation type, period mode, angle units from the plot
    *  \param[out]  itInterpolType index of Inteprolation type in the plot to be set of type enum IntepolType_T
    *  \param[out]  pmPeriodMode  index of Period mode in the plot to be set of type enum PeriodMode_T
    *  \param[out]  auAngleUnits  index of Angle units in the plot to be set of type enum AngleUnits_T
    *  \retval returns true if all the indices of parameters to be set are valid, false otherwise
    */
    bool SetParamImpCurve (double dPeriod, ImportCurveParameters iInterpolType, ImportCurveParameters iPeriodMode, ImportCurveParameters iAngleUnits);

    //! Sets the interpoltype in the plot of type enum InterpolType_T, returns true if the type being set is valid
    bool SetInterpolType(InterpolType_T itInterpolType);

    //! Set the period mode of the plots of type enum PeriodMode_T , returns true if period mode is valid and time units are modified correctly, else otherwise
    bool SetPeriodMode(PeriodMode_T pmPeriodMode);

    //! Set the samples, returns true if number of samples is greater than zero and interpolation is successful
    bool SetSamples ( unsigned int uiNumSamples );

    //! Set the angle units of type enum AngleUnits_T, returns true if the units are vaild and  angle units are modified correctly, else otherwise
    bool SetAngleUnits ( AngleUnits_T qsAngleUnits );

    //! Set the markers status of type enum MarkersStatus_T, returns true if markers status is valid , false otherwise
    bool SetMarkersStatus (MarkersStatus_T msMarkersStatus);

    //! Set the delay in the plot
    void SetDelay (double dDelay);

    //! Set the title of the plot
    void SetTitle (QString qsTitle);

   /*!  Determine the scaling factor for changing the period mode and takes into account every possibility from one mode to other
    *  \param[in]  pmPeriodMode Period mode of type enum PeriodMode_T
    *  \param[out] dScalingFactPeriod The scaling factor for changing the time units
    *  \retval returns true if the scaling factor is positive, and false otherwise
    */
    bool CheckPeriodMode(PeriodMode_T pmPeriodMode, double &dScalingFactPeriod);

    /*!  Determine the scaling factor for changing the angle units and takes into account every possibility from one mode to other
    *  \param[in]  auAngleUnits Angle units of type enum AngleUnits_T
    *  \param[out] dScalingFactAngUnits The scaling factor for changing the Angle units
    *  \retval returns true if the scaling factor is positive, and false otherwise
    */
    bool CheckAngleUnits(AngleUnits_T auAngleUnits, double &dScalingFactAngUnits);

    //! Checks if the vector consists of only zeros and returns true, false otherwise
    bool CheckVectorOfZeroes(vector <double> vInput);

    /*!  Modify the time units based upon the scaling factor determined
    *  \param[in]  dScalingFactPeriod   Suitable scaling factor for changing the time units
    *  \retval returns true if the time units are modified correctly and interpolation with new units is successful
    */
    bool ModifyTimeUnits(double dScalingFactPeriod);

    /*!  Modify the angle units based upon the scaling factor determined
    *  \param[in]  dScalingFactAngUnits   Suitable scaling factor for changing the angle units
    *  \retval returns true if the angle units are modified correctly and interpolation with new units is successful
    */
    bool ModifyAngUnits(double dScalingFactAngUnits);

    //! Concatenate the two vectors of type double, returns the concatenated vector of type double
    std::vector <double> ConcatenateVectors (const std::vector <double> vInputA, std::vector <double> &vInputB);

    //bool DeleteMarker ( unsigned int uiMarkerNumber );
    //bool MoveMarker ( unsigned int uiMarkerNumber, double dDeltaTime, float dDeltaAngle );
    //! create the plot from samples depending upon interpolation type
    void PlotCurve (){
        WidgetPlot->PlotCurve();
    }


private:


    JointPlot m_plot;
    Constantini97 *m_pConstantini;
    AddRemoveDialog *m_pAddRemovDialog;
    SelectItems *m_pSelectItemsDialog, *m_pSelectItemsDialogImport;
    QStringListModel *m_pListModel;
    QString m_qsButtonPressedStr, m_qsButtonNormalStr;
    QFileDialog *m_pqfdExport, *m_pqfdImport;
    QMessageBox *m_pMessagebox;
    ImportCurveParameters m_iInterpolType, m_iAngleUnits, m_iPeriodMode;
    double m_dPeriod;


private slots:


    //! Catches the interpolation signal and emit another one which is used as interface with mainwindow class
    void CatchInterpolSign();

    //! Show add remove dialog
    void OpenAddRemovDialog();

    //! Show select items dialog
    void OpenSelectListDialog();

    //void CloseSelectListDialog();
    //void ImportCurvetoFile();

    //! Close add remove dialog
    void CloseAddRemovDialog();

    //! Add the marker from AddRemovDialog
    void AddMarkerFromDialog();

    //! Remove marker from add remove dialog
    void RemoveMarkerFromDialog();

    //! Export the markers to file
    void ExportMarkerstoFile();

    //! Export the curve to file depending upon the parameters selected with the help of chech boxes
    void ExportCurveToFile();

    //! Reads the file  and import the markers into the plot
    void ImportMarkersFromFile();

    //! Read the file  and imports the curve into the plot including all the parameters
    void ImportCurveFromFile();

    //! Shows the list of markers if the relative check box is checked, otherwise clear the list
    void ControlListView();

    //! Shows the markers values in the AddRemovDialog depending upon the index of the marker selected from the list
    void ListItemSelected(QModelIndex iMarkerIndex);

    //! Change the stylesheets and the mode of the plot to add and remove
    void AddRemoveModeSelected();

    //! Change the stylesheets and the mode of the plot to Move
    void MoveModeSelected();

    //! Change the stylesheets and the mode of the plot to no change
    void NoChangedModeSelected();

    //! Depending on if the curve is shown delayed or not, change the status of the relevant plots
    void ChangeCurveForDelay();

    //! Change the stylesheets if the relevant dialogs are cancelled
    void ChangeStyleSheet();

signals:
     //! Emitted when the interpolation is done
     void InterpolationCompleted();

     //! Emitted when the curve is imported
     void ImportCurve();

};

#endif // COMPLETEJOINTPLOT_H
