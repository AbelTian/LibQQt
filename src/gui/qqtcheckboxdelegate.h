#ifndef QQTCHECKBOXDELEGATE_H
#define QQTCHECKBOXDELEGATE_H

#include <QApplication>
#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QCheckBox>
#include <QPainter>

#include <qqt-local.h>
/**
 * @brief The QQtCheckBoxDelegate class
 * Qt表格 CheckBox代理
 *
 * 不用代理也可以。
 * QTableWidget::setCellWidget(int row, int column, QWidget *widget)
 * QAbstractItemView::setIndexWidget(const QModelIndex &index, QWidget *widget)
 *
 */
class QQTSHARED_EXPORT QQtCheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit QQtCheckBoxDelegate ( QObject* parent = 0 )
        : QItemDelegate ( parent ) {}
    virtual ~QQtCheckBoxDelegate() {}

    QWidget* createEditor ( QWidget* parent, const QStyleOptionViewItem& option,
                            const QModelIndex& index ) const override {
        //create the checkbox editor
        QCheckBox* editor = new QCheckBox ( parent );
        return editor;
    }

    virtual void destroyEditor ( QWidget* editor, const QModelIndex& index ) const override {
        editor->deleteLater();
    }

    void setEditorData ( QWidget* editor, const QModelIndex& index ) const override {
        //set if checked or not
        QCheckBox* cb = qobject_cast<QCheckBox*> ( editor );
        cb->setChecked ( index.data().toBool() );
    }

    void setModelData ( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const override {
        QCheckBox* cb = static_cast<QCheckBox*> ( editor );
        int value = ( cb->checkState() == Qt::Checked ) ? 1 : 0;
        model->setData ( index, value, Qt::EditRole );
    }

    void updateEditorGeometry ( QWidget* editor, const QStyleOptionViewItem& option,
                                const QModelIndex& index ) const override {
        Q_UNUSED ( index );
        editor->setGeometry ( option.rect );
    }

protected:

private:


    // QAbstractItemDelegate interface
public:
    virtual void paint ( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override {
        bool ok = false;
        int value = index.data().toInt ( &ok );
        if ( ok ) {
            painter->save();

            QColor c;
            if ( value <= 0 ) {
                c = Qt::red;
            }
            else {
                c = Qt::green;
            }

            QRect localRect ( option.rect );
            localRect.setWidth ( localRect.height() );
            painter->fillRect ( localRect, c );

            QTextOption o;
            o.setAlignment ( Qt::AlignLeft | Qt::AlignVCenter );
            QRect localRect2 ( option.rect );
            localRect2.setLeft ( localRect2.left() + localRect.height() );
            painter->drawText ( localRect2, QString ( "%1" ).arg ( value ), o );

            painter->restore();
        }
        else {
            QItemDelegate::paint ( painter, option, index );
        }
    }
};

#endif // QQTCHECKBOXDELEGATE_H

