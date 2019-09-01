#ifndef QQTWIDGETEFFECT_H
#define QQTWIDGETEFFECT_H

#include <QWidget>

//#include <qqt-local.h>
#define QQTSHARED_EXPORT

//shadow effect （子控件）
void QQTSHARED_EXPORT setShadowEffect ( QWidget* widget );

//highlight text font for widget
void QQTSHARED_EXPORT setHighlightTextEffect ( QWidget* widget );

//fade effect 窗口透明渐变效果
void QQTSHARED_EXPORT setFadeEffect ( QWidget* widget, quint32 millseconds = 2000, qreal startOpacity = 0, qreal endOpacity = 1 );

//fade text effect 文件颜色渐变效果
void QQTSHARED_EXPORT setFadeTextEffect ( QWidget* widget, QColor color = QColor ( 122, 193, 66 ) );

#endif // QQTWIDGETEFFECT_H
