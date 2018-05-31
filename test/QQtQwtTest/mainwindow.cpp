#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqttcpclient.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    QQtTcpClient t;
    setupRealtimeDataDemo ( ui->qwtPlot );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupRealtimeDataDemo ( QwtPlot* qwtplot )
{


    //初始化xdata,x对应长度为5的坐标，y初始全为0
    for ( int i = 1; i < 5001; i++ )
    {
        xdata.append ( double ( i ) / 1000 - 5 );
        ydata.append ( 0 );
    }

    demoName = "Real Time Data Demo";
    qwtplot->setTitle ( demoName );
    qwtplot->setCanvasBackground ( Qt::gray ); //背景
    qwtplot->insertLegend ( new QwtLegend(), QwtPlot::RightLegend ); //标签

    curve = new QwtPlotCurve();
    curve->setTitle ( "肌电信号" ); //曲线名字
    curve->setPen ( Qt::yellow, 1 ); //曲线的颜色 宽度;

    QTime curtime;
    curtime = curtime.currentTime();
    qwtplot->setAxisTitle ( QwtPlot::xBottom, " System Uptime" );
    qwtplot->setAxisTitle ( QwtPlot::yLeft, "EMG" );
    qwtplot->setAxisScale ( QwtPlot::yLeft, -2, 2, 1 );
    qwtplot->setAxisScale ( QwtPlot::xBottom, -5, 0, 1 );



    QwtPlotZoomer* zoomer = new QwtPlotZoomer ( qwtplot->canvas() );
    zoomer->setRubberBandPen ( QColor ( Qt::blue ) );
    zoomer->setTrackerPen ( QColor ( Qt::black ) );
    zoomer->setMousePattern ( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern ( QwtEventPattern::MouseSelect3, Qt::RightButton );
    QwtPlotMagnifier* magnifier = new QwtPlotMagnifier (
        qwtplot->canvas() );                //默认的滑轮及右键缩放功能  图形的整体缩放

    //    magnifier->setMouseButton(Qt::LeftButton);     //设置哪个按钮与滑轮为缩放画布  如果不设置(注册掉当前行)按钮默认为滑轮以及右键为缩放

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->enableX ( true ); //设置网格线
    grid->enableY ( true );
    grid->setMajorPen ( Qt::black, 0, Qt::DotLine );
    grid->attach ( qwtplot );

    connect ( &updateTimer, SIGNAL ( timeout() ), this, SLOT ( updatedataSlot() ) );
    updateTimer.start ( 0 );


}


/**
 * @brief getData
 * @param inteval
 * @return
 * 获取一个值  模拟串口接收到的值
 */
double MainWindow::getData ( double time )
{

    double s = qCos ( time * M_PI * 2 ) ;
    return s;
}


//用于更新ydata,实际情况就是read数据
void MainWindow::updatedataSlot()
{
    static QTime dataTime ( QTime::currentTime() );
    long int eltime = dataTime.elapsed();
    static int lastpointtime = 0;

    int size = ( eltime - lastpointtime );


    if ( size > 0 ) //有数据传入
    {
        ydata.erase ( ydata.begin(), ydata.begin() + size ); //擦除多余的数据
        for ( int i = 1; i < size + 1; i++ )
        {
            ydata.append ( getData ( ( ( ( double ) lastpointtime + i ) / 1000 ) ) );
        }
        lastpointtime = eltime;
    }

    curve->setSamples ( xdata, ydata );
    curve->attach ( ui->qwtPlot );
    ui->qwtPlot->replot();

    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    double fpstime = ( double ) eltime / 1000.0 - lastFpsKey;
    if ( fpstime > 2 ) // average fps over 2 seconds
    {
        ui->statusBar->showMessage (
            QString ( "%1 FPS" )
            .arg ( frameCount / fpstime, 0, 'f', 0 )
            , 0 );
        lastFpsKey = ( double ) eltime / 1000.0;
        frameCount = 0;
    }
}







