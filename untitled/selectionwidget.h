#ifndef SELECTIONWIDGET_H
#define SELECTIONWIDGET_H

#include <QWidget>

class SelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectionWidget(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    QPoint startPoint;
    QPoint endPoint;
    bool isDrawing;

signals:
};

#endif // SELECTIONWIDGET_H
