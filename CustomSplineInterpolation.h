#ifndef CUSTOMSPLINEINTERPOLATION_H
#define CUSTOMSPLINEINTERPOLATION_H
#include <qwt_spline.h>


class CustomSplineInterpolation : public QwtSpline
{
public:
    CustomSplineInterpolation(const QwtSpline &Other);
    void CustomBuildSpline();
};

#endif // CUSTOMSPLINEINTERPOLATION_H
