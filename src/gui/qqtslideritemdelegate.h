#ifndef QQTSLIDERITEMDELEGATE_H
#define QQTSLIDERITEMDELEGATE_H

#include <QApplication>
#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QSlider>
#include <QPainter>

#include <qqt-local.h>
/**
 * @brief The QQtSliderItemDelegate class
 * Qt表格 Slider Item代理
 *
 * 不用代理也可以。
 * QTableWidget::setCellWidget(int row, int column, QWidget *widget)
 * QAbstractItemView::setIndexWidget(const QModelIndex &index, QWidget *widget)
 *
 */
class QQTSHARED_EXPORT QQtSliderItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit QQtSliderItemDelegate ( QObject* parent = 0 )
        : QItemDelegate ( parent ) {}
    virtual ~QQtSliderItemDelegate() {}

    QWidget* createEditor ( QWidget* parent, const QStyleOptionViewItem& option,
                            const QModelIndex& index ) const override {
        QSlider* editor = new QSlider ( Qt::Horizontal, parent );
        editor->setRange ( 0, 100 );
        editor->setAutoFillBackground ( true );
        return editor;
    }

    virtual void destroyEditor ( QWidget* editor, const QModelIndex& index ) const override {
        editor->deleteLater();
    }

    void setEditorData ( QWidget* editor, const QModelIndex& index ) const override {
        QSlider* slider = qobject_cast<QSlider*> ( editor );
        if ( slider ) {
            const int value = index.model()->data ( index ).toInt();
            slider->setValue ( value );
        }
    }

    void setModelData ( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const override {
        QSlider* slider = qobject_cast<QSlider*> ( editor );
        if ( editor ) {
            model->setData ( index, slider->value() );
        }
    }

    void updateEditorGeometry ( QWidget* editor, const QStyleOptionViewItem& option,
                                const QModelIndex& index ) const override {
        Q_UNUSED ( index )
        editor->setGeometry ( option.rect );
    }

    void paint ( QPainter* painter, const QStyleOptionViewItem& option,
                 const QModelIndex& index ) const override {
        bool ok = false;
        int value = index.data().toInt ( &ok );
        if ( ok ) {
            painter->save();

            QRect rect ( option.rect );
            int width = ( value * rect.width() ) / 100;
            rect.setWidth ( width );
            QColor c;
            if ( value <= 20 ) {
                c = Qt::red;
            }
            else if ( value <= 50 ) {
                c = QColor ( 240, 96, 0 );
            }
            else {
                c = Qt::green;
            }

            painter->fillRect ( rect, c );

            QTextOption o;
            o.setAlignment ( Qt::AlignLeft | Qt::AlignVCenter );
            painter->drawText ( option.rect, QString ( "%1%" ).arg ( value ), o );

            painter->restore();
        }
        else {
            QItemDelegate::paint ( painter, option, index );
        }
    }

protected:

private:

};

#endif // QQTSLIDERITEMDELEGATE_H

