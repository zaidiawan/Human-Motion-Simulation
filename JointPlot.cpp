#include "JointPlot.h"
#include "CustomSplineInterpolation.h"
#include <QMouseEvent>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

JointPlot::JointPlot(QWidget *parent) : QwtPlot(parent), m_csCurveStatus(ShowWithoutDelay)
{
    m_pqwtSpline = new QwtSpline;   // Creating Spline
    m_pConstSpline = new Constantini97();

    m_pMarkerArray = new QwtPlotMarker[100]; // Creating MarkerArray

    m_pSignalMapper = new QSignalMapper (this);

    this->setCanvasBackground(QColor(200,200,230)); // Setting canvas Background

    m_uiSamplesPlot = 100;
    m_uiMarkersCount = 0;
    m_dPeriodPlot = 3.0;
    m_dInterpolPeriod = 3.0;
    m_itInterpolType = cubic;
    m_pmPeriodMode = time;
    m_auAngleUnits = radians;

    m_pTimerMoveMarker = new QTimer;
    m_pTimerMoveMarker->setInterval(80);                    // Interval 80 ms

    connect(m_pTimerMoveMarker, SIGNAL(timeout()), m_pSignalMapper , SLOT( map() ) ) ;
    m_pGrid = new QwtPlotGrid;  //  Creating Grid
    m_pGrid->setMajPen( QPen( Qt::white, 0, Qt::DotLine ) );
    m_pGrid->attach(this);

    m_pSymbolRect = new QwtSymbol;  // Creating Symbol
    m_pSymbolRect->setStyle(QwtSymbol::Rect);
    m_pSymbolRect->setSize(10.0, 10.0);
    m_pSymbolRect->setBrush(Qt::red);

    m_pSymbolRect2 = new QwtSymbol;  // Creating Symbol
    m_pSymbolRect2->setStyle(QwtSymbol::Rect);
    m_pSymbolRect2->setSize(10.0, 10.0);
    m_pSymbolRect2->setBrush(Qt::green);

    m_pCurveJoint = new QwtPlotCurve(); // Creating Curve
    m_pCurveJoint->setStyle(QwtPlotCurve::Lines);
    m_pCurveJoint->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_pCurveJoint->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_pCurveJoint->setPen(QPen(Qt::black, 2.5));

    QwtPlotPicker* qppPlotPicker = new QwtPlotPicker(this->xBottom, this->yLeft, QwtPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas()); // Creating PlotPicker for displaying coordinates on Canvas
    qppPlotPicker->setStateMachine(new QwtPickerClickPointMachine);
    qppPlotPicker->setTrackerPen(QColor(Qt::blue));
    qppPlotPicker->setTrackerFont(QFont("Helvetica"));
}

void JointPlot:: mousePressEvent(QMouseEvent *PressEvent)
{
    QPointF qpfPressPos, qpfPressTransformedPos;
    m_pTimerMoveMarker->start();
    vector <bool> bPresHistory;

    qpfPressPos = (PressEvent->pos())-(this->canvas()->pos());  // Getting accurate position by subtracting the canvas position from event position
    qpfPressTransformedPos =  InvTransform(qpfPressPos);
    bPresHistory = GetPressHistory(qpfPressTransformedPos , m_vTimeValues , m_vAngleValues);

    if((PressEvent->buttons()&Qt::LeftButton)==Qt::LeftButton) {

        if(m_msMarkersStatus == MarkersMoved) {

            for(unsigned int iMarker = 0; iMarker  < m_uiMarkersNumber ; iMarker++) {

                if (bPresHistory[iMarker] == true) {

                    m_pSignalMapper->setMapping(m_pTimerMoveMarker, iMarker);
                    connect(m_pSignalMapper, SIGNAL(mapped(int)), this, SLOT(MoveMarker(int)) );
                    m_pTimerMoveMarker->start();
                }
            }
        }
        else if (m_msMarkersStatus == MarkersInserted) {           // If new marker is placed
            AddMarker(qpfPressTransformedPos.x(), qpfPressTransformedPos.y());

        }
    }

    if((PressEvent->buttons()&Qt::RightButton) == Qt::RightButton && m_msMarkersStatus !=   MarkersUnchanged ) {
        for(unsigned int iMarker = 0; iMarker  < m_uiMarkersNumber ; iMarker++) {
            if ((bPresHistory[iMarker] == true) &&
               (!((m_itInterpolType == Constantini || m_itInterpolType == CFourier) && (m_uiMarkersNumber <= 4)) &&
               (m_uiMarkersNumber > 4))) {

                    RemoveMarker(iMarker);


            }
        }
    }
}
void JointPlot::mouseReleaseEvent(QMouseEvent *ReleaseEvent)
{

    m_pTimerMoveMarker->stop();
    m_pSignalMapper->removeMappings(m_pTimerMoveMarker);

    ArrangeMarkers(m_vTimeValues, m_vAngleValues);

    RescaleAxis();

    replot();

}

QPointF JointPlot::InvTransform( const QPointF &pos ) const
{

    QwtScaleMap xMap = this->canvasMap( this->xBottom );
    QwtScaleMap yMap = this->canvasMap( this->yLeft );
    return QPointF(
                xMap.invTransform( pos.x() ),
                yMap.invTransform( pos.y() )
                );
}

bool JointPlot::Interpolation(const vector<double> vTimeInterpol, const vector<double> vAngleInterpol)
{

    bool bInterpolStatus = true;
    QPolygonF qpfPolyPoints;                             // Defining Polygon of points

    if (m_itInterpolType == cubic) {
        qpfPolyPoints = MakeValsPeriodic(vTimeInterpol, vAngleInterpol);
        bInterpolStatus = SetCubicSpline(qpfPolyPoints);
    }

    else if (m_itInterpolType == akima) {
        qpfPolyPoints = MakeValsPeriodic(vTimeInterpol, vAngleInterpol);
        SetAkimaSpline(qpfPolyPoints);
    }


    emit Interpol();
    return bInterpolStatus;
}

bool JointPlot::PlotCurve()
{
    vector <double> vTimePlot, vAnglePlot;

    GetPlotSamples(vTimePlot, vAnglePlot);

    if (vTimePlot.size() == vAnglePlot.size()) {

        m_pCurveJoint->setSamples(&vTimePlot[0], &vAnglePlot[0], m_uiSamplesPlot);
        m_pCurveJoint->attach(this);
        replot();
        return true;
    }
    else
        return false;
}

bool JointPlot::PlotCurve(vector <double> vTimeSamples, vector <double> vAngleSamples)
{
    if (vTimeSamples.size() == vAngleSamples.size()) {
        m_pCurveJoint->setSamples(&vTimeSamples[0], &vAngleSamples[0], m_uiSamplesPlot);
        m_pCurveJoint->attach(this);
        replot();
        return true;

    }
    else
        return false;
}

bool JointPlot::AddMarkers(const vector <double> vXMarkers, const vector<double> vYMarkers, Qt::GlobalColor qtgcGlobalColor)
{

    QwtText qwttMarkersNumber;
    double dMarkersDelay;

    if (m_csCurveStatus == ShowDelayed) { dMarkersDelay = m_dDelay; }
    else if (m_csCurveStatus == ShowWithoutDelay) { dMarkersDelay = 0; }

    if (vXMarkers.size() == vYMarkers.size()) {

        for (unsigned int uiMarker = 0; uiMarker < vXMarkers.size(); uiMarker++) {

            m_pMarkerArray[uiMarker].setSymbol(m_pSymbolRect);
            m_pSymbolRect->setBrush(qtgcGlobalColor);
            m_pMarkerArray[uiMarker].detach();
            m_pMarkerArray[uiMarker].setValue(fmod(vXMarkers.at(uiMarker) + dMarkersDelay, m_dInterpolPeriod) , vYMarkers.at(uiMarker)) ;
            //qDebug()<<"  "<< m_pMarkerArray[uiMarker].xValue()<<" "<<m_pMarkerArray[uiMarker].yValue();
            qwttMarkersNumber.setText(QString::number(uiMarker));
            m_pMarkerArray[uiMarker].setLabel(qwttMarkersNumber);
            m_pMarkerArray[uiMarker].attach(this);

        }
        m_uiMarkersCount = vXMarkers.size();
        return true;
    }
    else
        return false;
}

vector <double> JointPlot::TimeSamples(CurveStatus_T csCurveStatus)
{
    double dStep= 0, dTimeValue = 0;         // Angle Step
    vector <double> vTimeSampled ;

    for(unsigned int c = 0; c < m_uiSamplesPlot; c++) {  // Values of vTimeSamples = No. of samples
        if (csCurveStatus == ShowDelayed) {
          vTimeSampled.push_back(fmod(dTimeValue + m_dDelay, m_dInterpolPeriod));
        }

        else if (csCurveStatus == ShowWithoutDelay) {
            vTimeSampled.push_back(dTimeValue);
        }

        GetStepValue(dStep);
        dTimeValue += dStep;

    }
    return vTimeSampled;
}


bool JointPlot::ArrangeMarkers(vector <double> &vXMarkers,vector <double> &vYMarkers)
{
    if (vXMarkers.size() == vYMarkers.size()) {
        bool bDone = false; // this flag will be used to check whether we have to continue the algorithm
        while (!bDone) {
            bDone = true; // assume that the array is currently sorted
            for (unsigned int iMarker = 0; iMarker < vXMarkers.size()-1; iMarker++ )  { // for every element in the array     ( notice: this can be a bit optimized, see http://en.wikipedia.org/wiki/Bubblesort#Optimizing_bubble_sort )
                if ( vXMarkers[iMarker]> vXMarkers[iMarker+1]) { // compare the current element with the following one

                    double dtmpXMarker = vXMarkers[iMarker];
                    double dtmpYMarker = vYMarkers[iMarker];
                    vXMarkers[iMarker] = vXMarkers[iMarker+1];
                    vYMarkers[iMarker] = vYMarkers[iMarker+1];
                    vXMarkers[iMarker+1] = dtmpXMarker;
                    vYMarkers[iMarker+1] = dtmpYMarker;
                    bDone = false;
                }
            }
        }

        return true;
    }
    else
        return false;
}

vector <bool> JointPlot::GetPressHistory(const QPointF qpfPresPos  , const vector <double> vTimeValues, const vector <double> vAngleValues)
{

    bool qpfMarkerPos[m_uiMarkersNumber];
    double dSymbolWidth, dSymbolHeight;
    vector <bool> vPressHistory;

    GetSymbolSize(dSymbolWidth, dSymbolHeight);

    //    qDebug()<<"DSymbolHeight: "<<dSymbolHeight;
    //    qDebug()<<"DSymbolWidth: "<<dSymbolWidth;

    for(unsigned int cMarker = 0; cMarker < m_uiMarkersNumber; cMarker++) {

        qpfMarkerPos[cMarker] =   qpfPresPos.x() >=  (vTimeValues.at(cMarker)  - dSymbolWidth)
                && qpfPresPos.x() <=  (vTimeValues.at(cMarker)  + dSymbolWidth)
                && qpfPresPos.y() >=  (vAngleValues.at(cMarker) - (dSymbolHeight))
                && qpfPresPos.y() <=  (vAngleValues.at(cMarker) + (dSymbolHeight));

        //        qDebug()<<"Marker: "<<cMarker<<"Value: "<<qpfMarkerPos[cMarker];

        vPressHistory.push_back(qpfMarkerPos[cMarker]);
    }
    return  vPressHistory;
}

void JointPlot:: MoveMarker(int iMarker)
{

    vector <double> vTimeValues, vAngleValues;

    QCursor* pCursor = new QCursor;
    QPoint qpPosGlobal= pCursor->pos();
    QPointF qpfPosLocal = this->mapFromGlobal(qpPosGlobal) - this->canvas()->pos();
    QPointF qpfPosTransformed = this->InvTransform(qpfPosLocal);

    m_vTimeValues.at(iMarker) = qpfPosTransformed.x();
    m_vAngleValues.at(iMarker) = qpfPosTransformed.y();
    //qDebug()<<pCursor->pos();
    vTimeValues =  m_vTimeValues;    //temporary vector, is the copy
    vAngleValues = m_vAngleValues;

    if(CheckMarkerCorrectMov(iMarker)) {
        ArrangeMarkers(vTimeValues, vAngleValues);
        AddMarkers(vTimeValues, vAngleValues, Qt::red);
        Interpolation (vTimeValues, vAngleValues);
        PlotCurve();
   }
}

bool JointPlot::GetStepValue(double &dStepValue)
{
    if (m_pmPeriodMode == time)
        dStepValue =  m_dPeriodPlot /(double)m_uiSamplesPlot;
    else if (m_pmPeriodMode == percent)
        dStepValue = 100 / (double)m_uiSamplesPlot;

    if (dStepValue > 0)
        return true;
    else
        return false;
}
void JointPlot::GetInterpolPeriod(double &dInterpolCycle)
{
    dInterpolCycle = m_dInterpolPeriod;

}

bool JointPlot::SetInterpolPeriod(double dInterpolPeriod)
{
    if (m_dInterpolPeriod == m_dPeriodPlot || m_dInterpolPeriod == 100) {
        m_dInterpolPeriod = dInterpolPeriod;
        return true;
    }
    else
        return false;
}

void JointPlot::RescaleAxis()
{
    vector <double>::const_iterator itAngMin , itAngMax;

    itAngMax = max_element(m_vAngleValues.begin() , m_vAngleValues.end());
    itAngMin = min_element(m_vAngleValues.begin() , m_vAngleValues.end());
    //qDebug()<<"AngleMax"<<*itAngMax<<"AngleMin"<<*itAngMin;
    //setAxisScale(xBottom, floor(m_vTimeValues.front()), ceil(m_vTimeValues.back()));    // Set Time Axis Scale, min = min. time value rounded , max = max. time value rounded
    setAxisScale(yLeft, (*itAngMin -(fabs(*itAngMax - *itAngMin) / 2 ) ), (*itAngMax + ( fabs(*itAngMax - *itAngMin) / 2) ) );    // Set Angle Axis Axis Scale
    // min. = min. - (max. - min.)/2, max. = max.+ (max. - min.)/2
}
void JointPlot::GetSymbolSize(double &dSymbWidth, double &dSymbHeight)
{
    QwtScaleMap qsmSymbRectSMap;

    const QRectF qrfSymbRect(QPoint(0,0), QPoint(m_pSymbolRect->size().width(), -m_pSymbolRect->size().height()));
    const QwtScaleMap qsmXMap = this->canvasMap(this->xBottom);
    const QwtScaleMap qsmYMap = this->canvasMap(this->yLeft);
    QRectF qrfSymbRectTransformed = qsmSymbRectSMap.invTransform(qsmXMap,qsmYMap, qrfSymbRect );
    dSymbWidth = qrfSymbRectTransformed.width();
    dSymbHeight = qrfSymbRectTransformed.height();

}

bool JointPlot::CheckMarkerCorrectPlacement(double XValue)
{
    m_pMessageBox = new QMessageBox(this);
    double dTruncDialogXVal, dTruncActXVal;
    bool bCheckMarkerPlacement = true;
    unsigned int iMarker = 0;

    while(iMarker < m_uiMarkersNumber && bCheckMarkerPlacement == true) {
        // Truncating decimal places to 2
        dTruncDialogXVal = TruncateDecimalPlaces(XValue);
        dTruncActXVal = TruncateDecimalPlaces(m_vTimeValues.at(iMarker));

       if(dTruncDialogXVal == dTruncActXVal)  {
         bCheckMarkerPlacement = false;
         m_pMessageBox->setInformativeText("Already a marker!!");
         m_pMessageBox->setWindowTitle("Information");
         m_pMessageBox->show();
       }
       iMarker++;

    }
    return  bCheckMarkerPlacement;
}

bool JointPlot::CheckMarkerCorrectMov(unsigned int iMarker)
{
    bool bCheckAxis = true;
    double dSymbWidth, dSymbHeight;
    GetSymbolSize(dSymbWidth, dSymbHeight);
    vector <double>::const_iterator itMaxXValue, itMinXValue;
    itMaxXValue = std::max_element(m_vTimeValues.begin(), m_vTimeValues.end());
    itMinXValue = std::min_element(m_vTimeValues.begin(), m_vTimeValues.end());
    for(unsigned int i = 0; i < m_uiMarkersNumber; i++) {
        if(i != iMarker) {
            if( (*itMaxXValue > m_dInterpolPeriod || *itMinXValue < 0 ) || ((m_vTimeValues.at(i) > m_vTimeValues.at(iMarker) - (dSymbWidth/2)) && (m_vTimeValues.at(i) < m_vTimeValues.at(iMarker) + (dSymbWidth/2) ))) {
            bCheckAxis = false;
            }
        }
    }
    return bCheckAxis;
}

bool JointPlot::AddMarker(double XMarker, double YMarker)
{
    if(CheckMarkerCorrectPlacement(XMarker)) {
        m_vTimeValues.push_back(XMarker);  // Add the new point  for curve to the  vector
        m_vAngleValues.push_back(YMarker);
        m_uiMarkersNumber++ ;

    }

    //ArrangeMarkers(m_vTimeValues , m_vAngleValues);
    //AddMarkers(m_vTimeValues, m_vAngleValues, Qt::red );
    //Interpolation( m_vTimeValues , m_vAngleValues);
    //PlotCurve();

    if (ArrangeMarkers(m_vTimeValues , m_vAngleValues) == true &&
        AddMarkers(m_vTimeValues, m_vAngleValues, Qt::red) == true &&
        Interpolation( m_vTimeValues , m_vAngleValues) == true &&
        PlotCurve() == true) {
        return true;
    }
    else
        return false;

}
bool JointPlot::RemoveMarker(unsigned int uiMarkerIndex)
{
    for(unsigned int iMarker = uiMarkerIndex; iMarker < m_uiMarkersNumber; iMarker++) {
        while(iMarker < m_uiMarkersNumber - 1) {
            m_pMarkerArray[iMarker].setValue(m_pMarkerArray[iMarker+1].value());     // Remove the point or marker and all the next points or markers with be shifted backward one position in vector
            m_vTimeValues.at(iMarker) = m_vTimeValues.at(iMarker+1);
            m_vAngleValues.at(iMarker)= m_vAngleValues.at(iMarker+1);
            iMarker++;
        }
    }
    m_uiMarkersNumber--;
    m_pMarkerArray[m_uiMarkersNumber].detach();
    m_vTimeValues.pop_back();
    m_vAngleValues.pop_back();

    if (ArrangeMarkers(m_vTimeValues , m_vAngleValues) == true &&
        AddMarkers(m_vTimeValues, m_vAngleValues, Qt::red) == true &&
        Interpolation( m_vTimeValues , m_vAngleValues) == true &&
        PlotCurve() == true) {
        return true;
    }
    else
        return false;
}

double JointPlot::TruncateDecimalPlaces(double dNumber)
{
    double dTruncatedVal;
    double Scale = 0.01;
    dTruncatedVal = (int)(dNumber / Scale) ;
    dTruncatedVal = dTruncatedVal * Scale;
    return dTruncatedVal;
}
bool JointPlot::CheckMarkersNumber(unsigned int uiMarkersNumber)
{
    if (uiMarkersNumber >= 0 && uiMarkersNumber < m_uiMarkersNumber) {
        return true;
    }
    else
        return false;
}
bool JointPlot::CheckPeriod(double dPeriod)
{
    if (dPeriod > 0) {
        return true;
    }
    else
        return false;
}
bool JointPlot::CheckInterpolType(InterpolType_T itInterpolType)
{
    if (itInterpolType == cubic || itInterpolType == akima || itInterpolType == CFourier || itInterpolType == Constantini) {
        return true;
    }
    else
        return false;
}
bool JointPlot::CheckAngleUnits(AngleUnits_T auAngleUnits)
{
    if (auAngleUnits == degrees || auAngleUnits == radians) {
        return true;
    }
    else
        return false;
}
bool JointPlot::CheckPeriodMode(PeriodMode_T pmPeriodMode)
{
    if (pmPeriodMode == time || pmPeriodMode == percent) {
        return true;
    }
    else
        return false;
}
QPolygonF  JointPlot::MakeValsPeriodic(const vector<double> vTimeInterpol, const vector<double> vAngleInterpol)
{
    double dPeriod;
    QPolygonF qpfPolyPoints;

    GetInterpolPeriod(dPeriod);

    qpfPolyPoints.clear();

    // Time 0 - T
    for(unsigned int iInputVector = 0 ; iInputVector < vTimeInterpol.size() ;iInputVector++) {
        qpfPolyPoints << QPointF(vTimeInterpol.at(iInputVector) , vAngleInterpol.at(iInputVector) );
    }
   //Time T - 2T
    for(unsigned int iInputVector = 0 ; iInputVector < vTimeInterpol.size() ;iInputVector++) {
        qpfPolyPoints << QPointF(vTimeInterpol.at(iInputVector) + dPeriod , vAngleInterpol.at(iInputVector) );
    }
    //Time 2T - 3T
    for(unsigned int iInputVector = 0 ; iInputVector < vTimeInterpol.size() ;iInputVector++) {
        qpfPolyPoints << QPointF(vTimeInterpol.at(iInputVector) + (dPeriod*2) , vAngleInterpol.at(iInputVector) );
    }
    //Time 3T - 4T
    for(unsigned int iInputVector = 0 ; iInputVector < vTimeInterpol.size() ;iInputVector++) {
        qpfPolyPoints << QPointF(vTimeInterpol.at(iInputVector) + (dPeriod*3) , vAngleInterpol.at(iInputVector) );
    }

    return qpfPolyPoints;

}

bool JointPlot::SetCubicSpline(QPolygonF qpfPolyPoints )
{
    m_pqwtSpline->setSplineType(m_pqwtSpline->Natural);
    m_pqwtSpline->setPoints(qpfPolyPoints);

    return m_pqwtSpline->setPoints(qpfPolyPoints);
}
void JointPlot::SetAkimaSpline(QPolygonF qpfPolyPoints)
{
    AkimaSpline  ASpline;
    vector <double> vTimePeriodic, vAnglePeriodic;

    for (int iPoly = 0; iPoly < qpfPolyPoints.size(); iPoly++) {
        vTimePeriodic.push_back(qpfPolyPoints.at(iPoly).x());
        vAnglePeriodic.push_back(qpfPolyPoints.at(iPoly).y());
        //qDebug()<<vAnglePeriodic.at(iPoly);
    }

    ASpline.build(vTimePeriodic, vAnglePeriodic) ; // build a cubic spline with 4 points
    m_asSpline.copySpline(ASpline);
}

bool JointPlot::SetConstantiniSpline(vector <double> vTimeInterpol, vector <double> vAngleInterpol, InterpolType_T m_itInterpolType, CurveStatus_T csCurveStatus, vector <double> &v_dAngleSamples)
{
    ArrangeMarkers(vTimeInterpol, vAngleInterpol);
    bool bInterpolStatus = false;
    vector <double> vTimeSamples;
    vector <float> v_fAngleSamples, v_fAngleValuesd, v_fAngleValuesdd;
    vector <float> v_fTimeValues(vTimeInterpol.begin(), vTimeInterpol.end());
    vector <float> v_fAngleValues(vAngleInterpol.begin(), vAngleInterpol.end());

    if (csCurveStatus == ShowWithoutDelay) {
        vTimeSamples = TimeSamples(ShowWithoutDelay);
    }
    else if (csCurveStatus == ShowDelayed) {
        vTimeSamples = TimeSamples(ShowDelayed);
    }
    std::sort(vTimeSamples.begin(), vTimeSamples.end());

    vector <float> v_fTimeSamples(vTimeSamples.begin(), vTimeSamples.end());

    if (m_itInterpolType == Constantini) {
        bInterpolStatus = m_pConstSpline->calc(v_fTimeValues, v_fAngleValues, v_fTimeSamples, v_fAngleSamples, float(m_dInterpolPeriod), 6);
    }

    else if (m_itInterpolType == CFourier) {
        bInterpolStatus =  m_pConstSpline->calc_fourier(v_fTimeValues, v_fAngleValues, v_fTimeSamples, v_fAngleSamples, v_fAngleValuesd, v_fAngleValuesdd, float(m_dInterpolPeriod), 6, 60);
    }

    vector <double> vAngleSamples(v_fAngleSamples.begin(), v_fAngleSamples.end());
    v_dAngleSamples = vAngleSamples;


    return  bInterpolStatus;
}

void JointPlot::GetPlotSamples (vector <double> &vTimeSamples, vector <double> &vAngleSamples)
{
    vector <double> vTSamples, vTimePlotSamples;
    vTSamples = TimeSamples(ShowWithoutDelay);

    for(unsigned int iSamples = 0 ; iSamples < m_uiSamplesPlot ; iSamples++) {
        if (m_itInterpolType == akima) {
            vAngleSamples.push_back(m_asSpline(vTSamples.at(iSamples) + m_dInterpolPeriod));
            //qDebug()<<vAnglePlot.at(iSamples);
        }
        else if (m_itInterpolType == cubic) {
            vAngleSamples.push_back(m_pqwtSpline->value(vTSamples.at(iSamples) + m_dInterpolPeriod));

        }
    }
    if (m_itInterpolType == Constantini || m_itInterpolType == CFourier) {
        SetConstantiniSpline(m_vTimeValues, m_vAngleValues, m_itInterpolType, m_csCurveStatus, vAngleSamples );

        }
    vTimePlotSamples = TimeSamples(m_csCurveStatus);

    ArrangeMarkers(vTimePlotSamples, vAngleSamples);

    vTimeSamples = vTimePlotSamples;
}






