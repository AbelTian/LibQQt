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

        QStyleOptionButton item;
        item.init ( option.widget );

        //QRect checkbox_rect = QApplication::style()->subElementRect ( QStyle::SE_CheckBoxIndicator, &item );

        //center
        item.rect = option.rect;
        //item.rect.setLeft ( option.rect.x() +
        //                    option.rect.width() / 2 - checkbox_rect.width() / 2 );

        editor->setGeometry ( item.rect );
    }

    void paint ( QPainter* painter, const QStyleOptionViewItem& option,
                 const QModelIndex& index ) const override {

        //retrieve data
        bool data = index.model()->data ( index, Qt::DisplayRole ).toBool();

        //create CheckBox style
        QStyleOptionViewItemV3 item;
        item.init ( option.widget );

        //QRect checkbox_rect = QApplication::style()->subElementRect ( QStyle::SE_CheckBoxIndicator, &item );
        //QRect checkbox_rect ( option.rect );
        //center
        item.rect = option.rect;
        //item.rect.setLeft ( option.rect.left() +
        //                    option.rect.width() / 2 - checkbox_rect.width() / 2 );

        //checked or not checked
        //if ( data )
        //    item.state = QStyle::State_On | QStyle::State_Enabled;
        //else
        //    item.state = QStyle::State_Off | QStyle::State_Enabled;
        item.state = option.state;

        //done! we can draw!
        QApplication::style()->drawControl ( QStyle::CE_CheckBox, &item, painter );

    }
protected:

private:

};

#endif // QQTCHECKBOXDELEGATE_H

