#ifndef LAYER_H
#define LAYER_H

#include <QMainWindow>
#include <Windows.h>
#include <windef.h>
#include <minwindef.h>
namespace Ui {
class Layer;
}

class Layer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Layer(QWidget *parent = nullptr);
    ~Layer();

protected:
    void createWindow(); // 添加这行
    void showCustomContextMenu(const QPoint &pos);

private:
    Ui::Layer *ui;
    HWND hWnd; // 添加这行
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // 添加这行



};

#endif // LAYER_H
