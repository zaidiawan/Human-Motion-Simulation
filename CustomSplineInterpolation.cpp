#include "CustomSplineInterpolation.h"
#include <MainWindow.h>
#include <QDebug>
#include <Splines.h>

CustomSplineInterpolation::CustomSplineInterpolation(const QwtSpline &Other):QwtSpline(Other)
{


}
void CustomSplineInterpolation::CustomBuildSpline()
{
    //buildNaturalSpline(this->points());
    setSplineType(this->Natural);
    buildNaturalSpline(this->points());
    //AkimaSpline spline ;
    /*double x[] = {0.12,0.75,1.47,1.98, 2.55, 2.91} ;
    double y[] = {0.371755131000000,0.0279252680000000,-0.336848546000000,0.0191986220000000,0.425860337000000,0.359537826000000} ;
    spline.build(this->points().x,this->points().,6) ; // build a cubic spline with 4 points
    spline.build()
    qDebug() << spline(0.7) << '\n';     // spline at x = 1.1
    qDebug() << spline(1.2) << '\n';     // spline at x = 1.1
    qDebug() << spline(2.3) << '\n';     // spline at x = 1.1
    qDebug() << spline.D(1.2) << '\n';   // spline first derivative at x = 1.1
    qDebug()<< spline.DD(2.3) << '\n';  // spline second derivative at x = 1.1*/

    qDebug()<<"*******************************";
}
