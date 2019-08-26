#ifndef QQTWINDOWATTRIBUTE_H
#define QQTWINDOWATTRIBUTE_H

#include <QWidget>

//#include <qqt-local.h>
#define QQTSHARED_EXPORT

//frameless
void QQTSHARED_EXPORT setFrameless ( QWidget* widget, bool open = true );

//主、子窗口
void QQTSHARED_EXPORT setMainWindow ( QWidget* widget, bool open = true );

//full screen (normal screen, +size)
void QQTSHARED_EXPORT setFullScreen ( QWidget* widget, bool open = true, QRect normalGeometry = QRect ( 0, 0, 800, 600 ) );

//子窗体填充主窗体



#endif // QQTWINDOWATTRIBUTE_H
