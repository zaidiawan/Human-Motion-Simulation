#include "RobotLinks.h"
#include "qwt_plot_curve.h"
#include "qwt_legend.h"
#include <qpainter.h>
#include <qpoint.h>
#include <qwt_plot_picker.h>
#include <TypeDefs.h>

RobotLinks::RobotLinks(QWidget *parent) :
    QwtPlot(parent)
{
    QwtPlotPicker* plotPicker = new QwtPlotPicker(this->xBottom, this->yLeft, QwtPicker::CrossRubberBand, QwtPicker::AlwaysOn, this->canvas());
    insertLegend( new QwtLegend() );
    setCanvasBackground(Qt::lightGray);
    setAxisScale(QwtPlot::xBottom, -70, 150);
    setAxisScale(QwtPlot::yLeft,-70,180);
    enableAxis(QwtPlot::yLeft, false);
    enableAxis(QwtPlot::xBottom, false);

    QwtPlotCurve *pHeadCurve = new QwtPlotCurve();
    pHeadCurve->setPen( QPen( Qt::red, 8 ) );
    pHeadCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *pTorsoCurve = new QwtPlotCurve();
    pTorsoCurve->setTitle( "Torso" );
    pTorsoCurve->setPen( QPen( Qt::red, 9 ) );
    pTorsoCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    m_pRThighCurve = new QwtPlotCurve();
    m_pRThighCurve->setTitle("Right-Thigh");
    m_pRThighCurve->setPen( QPen( Qt::darkCyan, 9 ) );
    m_pRThighCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    m_pRLegCurve = new QwtPlotCurve();
    m_pRLegCurve->setTitle("Right-Leg");
    m_pRLegCurve->setPen( QPen( Qt::green, 9 ) );
    m_pRLegCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    m_pLThighCurve = new QwtPlotCurve();
    m_pLThighCurve->setTitle("Left-Thigh");
    m_pLThighCurve->setPen( QPen( Qt::cyan, 9 ) );
    m_pLThighCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    m_pLLegCurve = new QwtPlotCurve();
    m_pLLegCurve->setTitle("Left-Leg");
    m_pLLegCurve->setPen( QPen( Qt::black, 9 ) );
    m_pLLegCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *pLHandCurve = new QwtPlotCurve();
    pLHandCurve->setTitle("Left-Hand");
    pLHandCurve->setPen( QPen( Qt::magenta, 9 ) );
    pLHandCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *pRHandCurve = new QwtPlotCurve();
    pRHandCurve->setTitle("Right-Hand");
    pRHandCurve->setPen( QPen( Qt::yellow, 9 ) );
    pRHandCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtSymbol *pEllipRedSymbolRed = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::red ), QPen( Qt::red, 5 ), QSize( 18, 18 ) );

    QwtSymbol *pEllipSymbolGreen = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::green ), QPen( Qt::red, 2 ), QSize( 18, 18 ) );

    QwtSymbol *pRectSymbolMagenta = new QwtSymbol( QwtSymbol::Rect,
    QBrush( Qt::magenta ), QPen( Qt::magenta, 11 ), QSize( 18, 18 ) );

    QwtSymbol *pEllipSymbolWhite = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::white), QPen( Qt::darkMagenta, 8 ), QSize( 66, 58 ) );

    pTorsoCurve->setSymbol( pEllipRedSymbolRed );
    m_pRThighCurve->setSymbol(pEllipSymbolGreen);
    m_pRLegCurve->setSymbol(pRectSymbolMagenta);
    m_pLThighCurve->setSymbol(pEllipSymbolGreen);
    m_pLLegCurve->setSymbol(pRectSymbolMagenta);


    QPolygonF qpfTorso, qpfNeck, qpfLHand, qpfRHand;

    qpfLHand << QPointF(30,126)  << QPointF(74,98) << QPointF(84,106);
    pLHandCurve->setSamples(qpfLHand);
    pLHandCurve->attach(this);
    pLHandCurve->show();

    qpfRHand <<QPointF(30,126)   << QPointF(-5.71,91.5) << QPointF(6.4,76.3);
    pRHandCurve->setSamples(qpfRHand);
    pRHandCurve->attach(this);
    pRHandCurve->show();

    qpfTorso << QPointF(30, 45 ) << QPointF(30, 146);
    pTorsoCurve->setSamples( qpfTorso );
    pTorsoCurve->attach(this);
    pTorsoCurve->show();

    qpfNeck << QPointF(30,155);
    pHeadCurve->setSymbol(pEllipSymbolWhite);
    pHeadCurve->setSamples(qpfNeck);
    pHeadCurve->attach(this);

    m_pTimerRobotLinks = new QTimer(this);
    connect(m_pTimerRobotLinks, SIGNAL(timeout()),this,SLOT(MoveLinks())) ;

    m_pTimerRobotLinks->start();
}
void RobotLinks::MoveLinks()
{

    QPolygonF PolyLHip;
    double dLHipAngleValue;

    dLHipAngleValue = m_vHipLLeg[m_uiSamplesCounter];
    PolyLHip.clear();

    PolyLHip << QPointF(30, 45 ) << QPointF(30+(m_dLengthThigh*sin((dLHipAngleValue*m_dScalingFactorAngle))), 45-(m_dLengthThigh*cos((dLHipAngleValue*m_dScalingFactorAngle))));

    m_pLThighCurve->setSamples( PolyLHip );
    m_pLThighCurve->attach(this);
    replot();

    //-------------------------------------------------
    QPolygonF PolyLKnee;
    double dLKneeAngleValue;

    dLKneeAngleValue = m_vKneeLLeg[m_uiSamplesCounter];

    /* (x1, y1) = ( Length of Hip * sin(Hip Angle) , Length of Hip * cos(Hip Angle) )
       (x2, y2) = ( Lnegth of Knee * sin(Knee Angle + Hip Angle) + Length of Hip * sin(Hip Angle) ,
                    Length of Hip * cos(Angle of Hip) - Length of Knee * cos(Angle of Hip + Angle of Knee) ) */

    PolyLKnee << QPointF(30+(m_dLengthThigh*sin(dLHipAngleValue*m_dScalingFactorAngle)), 45-(m_dLengthThigh*cos(dLHipAngleValue*m_dScalingFactorAngle)))
              << QPointF(30+(m_dLengthLeg*sin((dLKneeAngleValue+dLHipAngleValue)*m_dScalingFactorAngle))+(m_dLengthThigh*sin(dLHipAngleValue*m_dScalingFactorAngle)),
                         45-(m_dLengthThigh*cos(dLHipAngleValue*m_dScalingFactorAngle))-(m_dLengthLeg*cos((dLHipAngleValue+dLKneeAngleValue)*m_dScalingFactorAngle)));


    m_pLLegCurve->setSamples( PolyLKnee );
    m_pLLegCurve->attach(this);
    replot();
    PolyLKnee.clear();
    //-------------------------------------------------
    QPolygonF PolyRHip;
    double dRHipAngleValue;

    dRHipAngleValue = m_vHipRLeg[m_uiSamplesCounter];

    PolyRHip << QPointF(30, 45 ) << QPointF(30+(m_dLengthThigh*sin((dRHipAngleValue*m_dScalingFactorAngle))), 45-(m_dLengthThigh*cos((dRHipAngleValue*m_dScalingFactorAngle))));

    m_pRThighCurve->setSamples( PolyRHip );
    m_pRThighCurve->attach(this);
    replot();
    PolyRHip.clear();

    //---------------------------------------------------------------

    QPolygonF PolyRKnee;
    double dRKneeAngleValue;

    dRKneeAngleValue = m_vKneeRLeg[m_uiSamplesCounter];

    /* (x1, y1) = ( Length of Hip * sin(Hip Angle) , Length of Hip * cos(Hip Angle) )
       (x2, y2) = ( Lnegth of Knee * sin(Knee Angle + Hip Angle) + Length of Hip * sin(Hip Angle) ,
                    Length of Hip * cos(Angle of Hip) - Length of Knee * cos(Angle of Hip + Angle of Knee) ) */

    PolyRKnee << QPointF(30+(m_dLengthThigh*sin(dRHipAngleValue*m_dScalingFactorAngle)), 45-(m_dLengthThigh*cos(dRHipAngleValue*m_dScalingFactorAngle)))
              << QPointF(30+(m_dLengthLeg*sin((dRKneeAngleValue+dRHipAngleValue)*m_dScalingFactorAngle))+(m_dLengthThigh*sin(dRHipAngleValue*m_dScalingFactorAngle)),
                         45-(m_dLengthThigh*cos(dRHipAngleValue*m_dScalingFactorAngle))-(m_dLengthLeg*cos((dRHipAngleValue+dRKneeAngleValue)*m_dScalingFactorAngle)));
    m_pRLegCurve->setSamples( PolyRKnee );
    m_pRLegCurve->attach(this);
    replot();
    PolyRKnee.clear();
    // -------------------------------------------------------------
    m_uiSamplesCounter   = m_uiSamplesCounter+1;
       if(m_uiSamplesCounter == m_uiSamples) {
        m_uiSamplesCounter = 0;
        m_dTempStepValue   = 0;
    }

}

void RobotLinks::GetPlotInterpolValues(vector <double> vLeftHipValues, vector <double> vRightHipValues, vector <double> vLeftKneeValues, vector <double> vRightKneeValues )
{
    m_vHipLLeg  = vLeftHipValues;
    m_vHipRLeg  = vRightHipValues;
    m_vKneeLLeg = vLeftKneeValues;
    m_vKneeRLeg = vRightKneeValues;
}
void RobotLinks::GetPlotLeftHipValues(vector <double> vLeftHipValues)
{
    m_vHipLLeg = vLeftHipValues;
}
void RobotLinks::GetPlotRightHipValues(vector <double> vRightHipValues)
{
    m_vHipRLeg = vRightHipValues;
}
void RobotLinks::GetPlotLeftKneeValues(vector <double> vLeftKneeValues)
{
    m_vKneeLLeg = vLeftKneeValues;
}
void RobotLinks::GetPlotRightKneeValues(vector <double> vRightKneeValues)
{
    m_vKneeRLeg = vRightKneeValues;
}


