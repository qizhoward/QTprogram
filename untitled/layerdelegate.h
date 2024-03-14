#ifndef LAYERDELEGATE_H
#define LAYERDELEGATE_H

#include <QStyledItemDelegate>
class LayerDelegate : public QStyledItemDelegate {
public:
    explicit LayerDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // LAYERDELEGATE_H
