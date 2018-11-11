#ifndef QQTGUIQT_H
#define QQTGUIQT_H

#include <qglobal.h>

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtCore>
#include <QtGui>
#else
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtGlobal>
#endif

//来自qqt_qkit.pri
#if defined __EMBEDDED_LINUX__
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QWSInputMethod>
#include <QWSServer>
#include <QMouseDriverFactory>
#endif
#endif

#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include <QSslError>
#include <QSslKey>
#include <QSslSocket>

#include <QPixmap>
#include <QImage>
#include <QMovie>
#include <QTime>
#include <QThread>
#include <QTimer>
#include <QSettings>
#include <QQueue>
#include <QMutex>
#include <QList>
#include <QSemaphore>
#include <QStylePainter>
#include <QMouseEvent>
#include <QUuid>

#include <QTextFormat>
#include <QTextTable>
#include <QTextEdit>
#include <QTextBrowser>
#include <QTextCodec>
#include <QFont>

#include <QFileInfo>
#include <QFile>
#include <QDir>

#include <QMessageBox>
#include <QSplashScreen>
#include <QWidget>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QLayout>

#include <QTableView>
#include <QItemSelectionModel>
#include <QItemDelegate>
#include <QSqlRelationalDelegate>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QAnimationGroup>
#include <QPauseAnimation>
#include <QVariantAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

#include <QState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QEventTransition>
#include <QTimeLine>

//来自qqt_header.pri
#ifdef __PRINTSUPPORT__
#include <QPrinter>
#endif

//来自qqt_header.pri
#ifdef __PROCESSSUPPORT__
#include <QProcess>
#endif

#endif // QQTGUIQT_H
