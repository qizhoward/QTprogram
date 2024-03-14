#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

class GridWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GridWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    bool mousePressed;
    QPoint lastPos;
    int gridSize;
    QGraphicsScene *scene;
    QGraphicsView *view;
    void updateGrid();
};

#endif // GRIDWINDOW_H
