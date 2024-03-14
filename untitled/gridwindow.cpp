#include "gridwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>

GridWindow::GridWindow(QWidget *parent) : QWidget(parent),mousePressed(false),gridSize(20) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 添加网格线
    int rows = 20;
    int cols = 20;
    int cellWidth = gridSize;
    int cellHeight = gridSize;
    for (int x = 0; x <= cols; ++x) {
        scene->addLine(x * cellWidth, 0, x * cellWidth, rows * cellHeight);
    }
    for (int y = 0; y <= rows; ++y) {
        scene->addLine(0, y * cellHeight, cols * cellWidth, y * cellHeight);
    }


    // 将 QGraphicsView 添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);
    /*view->setDragMode(QGraphicsView::ScrollHandDrag);*/
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

}


void GridWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        lastPos = event->pos();
        mousePressed = true;
    }
}
void GridWindow::mouseMoveEvent(QMouseEvent *event) {
    if (mousePressed) {
        QPoint delta = event->pos() - lastPos;
        view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() - delta.x());
        view->verticalScrollBar()->setValue(view->verticalScrollBar()->value() - delta.y());
        lastPos = event->pos();
    }
}
void GridWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        mousePressed = false;
    }
}
void GridWindow::wheelEvent(QWheelEvent *event) {
    // 根据滚轮滚动的距离调整网格大小
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;
    int newGridSize = gridSize + numSteps;

    // 确保网格大小不小于10
    gridSize = std::max(10, newGridSize);

    // 清空现有的网格线
    scene->clear();

    // 添加新的网格线
    int rows = 20;
    int cols = 20;
    int cellWidth = gridSize;
    int cellHeight = gridSize;
    for (int x = 0; x <= cols; ++x) {
        scene->addLine(x * cellWidth, 0, x * cellWidth, rows * cellHeight);
    }
    for (int y = 0; y <= rows; ++y) {
        scene->addLine(0, y * cellHeight, cols * cellWidth, y * cellHeight);
    }

    QPoint delta = event->angleDelta();
    view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() - delta.x());
    view->verticalScrollBar()->setValue(view->verticalScrollBar()->value() - delta.y());
}


/* // 设置网格线的间距和颜色
    int gridSize = 20; // 网格尺寸
    int width = this->width();
    int height = this->height();
    QColor gridColor(200, 200, 200); // 网格颜色

    // 绘制垂直线
    for (int x = 0; x < width; x += gridSize) {
        painter.setPen(gridColor);
        painter.drawLine(x, 0, x, height);
    }

    // 绘制水平线
    for (int y = 0; y < height; y += gridSize) {
        painter.setPen(gridColor);
        painter.drawLine(0, y, width, y);
    }
}
*/
