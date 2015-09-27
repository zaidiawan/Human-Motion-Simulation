#ifndef SELECTITEMS_H
#define SELECTITEMS_H

#include "ui_SelectItems.h"

class SelectItems : public QDialog, protected Ui::SelectItems
{
    Q_OBJECT
    
public:

    explicit SelectItems(QWidget *parent = 0);
    friend class CompleteJointPlot;
};

#endif // SELECTITEMS_H
