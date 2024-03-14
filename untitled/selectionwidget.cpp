#include "selectionwidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include <QAction>
SelectionWidget::SelectionWidget(QWidget *parent)
    : QWidget(parent), isDrawing(false)
{
    setMouseTracking(true); // 这里添加了鼠标跟踪的设置
}

void SelectionWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        endPoint = event->pos();
        isDrawing = true;
    }
}

void SelectionWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        endPoint = event->pos();
        update();
    }
}

void SelectionWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        isDrawing = false;
        update();
    }
}

void SelectionWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::blue); // 设置画笔颜色
    painter.setBrush(Qt::NoBrush); // 设置不填充颜色
    if (isDrawing) {
        painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter.drawRect(QRect(startPoint, endPoint));
    } else {
        // 绘制实线框
        painter.setPen(QPen(Qt::red, 1));
        painter.drawRect(QRect(endPoint, startPoint));
    }
}

void SelectionWidget::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction("Action 1");
    menu.addAction("Action 2");
    menu.addAction("Action 3");

    menu.exec(event->globalPos());
}
