#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <wchar.h>
#include <vector>
#include <string>
#include <iostream>

#include "osg/Texture2D"
#include "osg/Geometry"
#include "osg/CullStack"
#include "osg/AutoTransform"
#include "osg/MatrixTransform"
#include "osg/PositionAttitudeTransform"
#include "osgDB/ReadFile"
#include "osgGA/TrackballManipulator"
#include "osgViewer/ViewerEventHandlers"
#include "osgViewer/Viewer"
#include "osgQt/QWidgetImage"

#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QQtApplication>
#include <qqtframe.h>
#include <QObject>

QWidget* createWidget ( const QString& movieFile, const QString& title )
{
    QLabel* label = new QLabel;
    QPushButton* playBtn = new QPushButton ( "Play " + title );
    QPushButton* stopBtn = new QPushButton ( "Stop " + title );
    QWidget* demo = new QWidget;
    demo->setLayout ( new QVBoxLayout );
    demo->layout()->addWidget ( label );
    demo->layout()->addWidget ( playBtn );
    demo->layout()->addWidget ( stopBtn );
    demo->setStyleSheet ( "background-color:lightblue;" );
    QMovie* movie = new QMovie ( movieFile );
    label->setMovie ( movie );
    label->setFixedHeight ( 400 );
    QObject::connect ( playBtn, SIGNAL ( clicked() ), movie, SLOT ( start() ) );
    QObject::connect ( stopBtn, SIGNAL ( clicked() ), movie, SLOT ( stop() ) );
    return demo;
}

osg::Node* createNode ( osg::Vec3& position, const QString& title, const QString& backgroundImage )
{
    osg::ref_ptr<osgQt::QWidgetImage> widgetImage =
        new osgQt::QWidgetImage ( createWidget ( backgroundImage, title ) );

    osg::ref_ptr<osgViewer::InteractiveImageHandler> handler =
        new osgViewer::InteractiveImageHandler ( widgetImage.get() );
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage ( widgetImage.get() );

    osg::ref_ptr<osg::Geometry> quad =
        osg::createTexturedQuadGeometry ( osg::Vec3(),
                                          osg::Vec3 ( widgetImage->getQWidget()->width(), 0, 0 ),
                                          osg::Vec3 ( 0, widgetImage->getQWidget()->height(), 0 ) );

    quad->setEventCallback ( handler.get() );
    quad->setCullCallback ( handler.get() );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable ( quad.get() );
    geode->getOrCreateStateSet()->setTextureAttributeAndModes ( 0, texture.get() );
    geode->getOrCreateStateSet()->setMode ( GL_LIGHTING, osg::StateAttribute::OFF );
    geode->getOrCreateStateSet()->setMode ( GL_DEPTH_TEST, osg::StateAttribute::OFF );
    geode->getOrCreateStateSet()->setRenderingHint ( osg::StateSet::TRANSPARENT_BIN );

    osg::ref_ptr<osg::AutoTransform> autoNode = new osg::AutoTransform;
    autoNode->setAutoRotateMode ( osg::AutoTransform::ROTATE_TO_SCREEN );
    autoNode->setAutoScaleToScreen ( true );
    autoNode->addChild ( geode.get() );

    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
    pat->setPosition ( position );
    pat->addChild ( geode.get() );

    return pat.release();
}

int main ( int argc, char* argv[] )
{
    QQtApplication a ( argc, argv );

    //MainWindow w;
    //w.show();

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild ( createNode ( osg::Vec3 ( 1.0, 0.0, 0.0 ), "Widget 2", qrc ( "aa.gif" ) ) );
    osgViewer::Viewer viewer;
    viewer.setSceneData ( root.get() );
    viewer.setCameraManipulator ( new osgGA::TrackballManipulator );
    viewer.addEventHandler ( new osgViewer::StatsHandler );

    while ( !viewer.done() )
    {
        QCoreApplication::processEvents ( QEventLoop::AllEvents, 100 );
        viewer.frame();
    }
    return 0;
}
