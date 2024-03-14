#include "layerdelegate.h"
#include <QPainter>
#include <QApplication>
#include <QIcon>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

LayerDelegate::LayerDelegate(QObject *parent): QStyledItemDelegate(parent) {}

void LayerDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    QStyledItemDelegate::paint(painter, opt, index);

    // 绘制图标
    if (index.data(Qt::DecorationRole).canConvert<QIcon>()) {
        QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
        icon.paint(painter, option.rect, Qt::AlignLeft | Qt::AlignVCenter);
    }
}

bool LayerDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton && index.data(Qt::DecorationRole).canConvert<QIcon>()) {
            QRect iconRect = option.rect;
            iconRect.setWidth(option.rect.height());
            if (iconRect.contains(mouseEvent->pos())) {
                qDebug() << "Icon clicked at row:" << index.row();
                // 在此处执行您想要的操作
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
