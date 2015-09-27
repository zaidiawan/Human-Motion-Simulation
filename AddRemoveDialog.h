#ifndef ADDREMOVEDIALOG_H
#define ADDREMOVEDIALOG_H

#include "ui_AddRemoveDialog.h"
/*!
  *     \file       AddRemoveDialog.h
  *     \author     Author Zahid <zahidraza.nust@gmail.com>
  *     \date       01/06/2014
  *     \brief      This class is used to add or remove markers in the dialog
  *
  *                 AddRemoveDialog class is inherited from Ui::AddRemoveDialog and QDialog.
  *                 The Ui has been designed for this class in the Designer.
  *                 The Designer contains ListBox "ListMarkers" which belongs to the class "QListView",and contain objects of classes QLineEdit, QLabel, QPushButton, and QCheckBox.
  *                 Any change in the state of these objects emit signals, and the relevant slots are executed.
  *                 In the slots, signals are emitted again, and these signals are catched by the relevant object of the class CompleteJointPlot to perform the required action.
                    or in otherwords, the signals and slots in this class provide an interface to class CompleteJointPlot
  *
*/

class AddRemoveDialog : public QDialog, protected Ui::AddRemoveDialog
{
    Q_OBJECT

public:
    friend class CompleteJointPlot;
    explicit AddRemoveDialog(QWidget *parent = 0);

/*! Getting the marker values for the given time values
 *  \fn   void GetMarkerValues(double &dTimeVal, double &dAngleVal)
 *  \param[out]  dTimeVal   The time value of type double captured from text box in the add remove dialog
 *  \param[out] dAngleVal   The angle value of type double captured from text box in the add remove dialog
 */
 void GetMarkerValues(double &dTimeVal, double &dAngleVal);

signals:
//! These signals are emitted in the slots which are executed on clicking the buttons from dialog
    void AddPressed();
    void RemovePressed();
    void CancelPressed();

private slots:
//! These slots are executed on clicking the respective buttons and further emit signals to be captured again
    void EmitAdd();
    void EmitRemove();
    void EmitCancel();
};
#endif // ADDREMOVEDIALOG_H
