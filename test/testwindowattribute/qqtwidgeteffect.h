#ifndef QQTWIDGETEFFECT_H
#define QQTWIDGETEFFECT_H

#include <QWidget>

//#include <qqt-local.h>
#define QQTSHARED_EXPORT

//shadow effect （子控件）
void QQTSHARED_EXPORT setShadowEffect ( QWidget* widget );

//fade effect
void QQTSHARED_EXPORT setFadeEffect ( QWidget* widget, quint32 millseconds = 2000, qreal startOpacity = 0, qreal endOpacity = 1 );

#endif // QQTWIDGETEFFECT_H
