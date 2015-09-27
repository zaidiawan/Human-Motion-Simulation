#include "AddRemoveDialog.h"

AddRemoveDialog::AddRemoveDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(ButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ButtonAdd, SIGNAL(clicked()), this, SLOT(EmitAdd()));
    connect(ButtonRemove, SIGNAL(clicked()), this, SLOT(EmitRemove()));
    connect(ButtonCancel, SIGNAL(clicked()), this, SLOT(EmitCancel()));
}
void AddRemoveDialog::GetMarkerValues(double &dTimeVal, double &dAngleVal)
{
    dTimeVal = TextTime->text().toDouble();
    dAngleVal = TextAngle->text().toDouble();
}

void AddRemoveDialog::EmitAdd()
{
    emit AddPressed();
}
void AddRemoveDialog::EmitRemove()
{
    emit RemovePressed();
}
void AddRemoveDialog::EmitCancel()
{
    emit CancelPressed();
}
