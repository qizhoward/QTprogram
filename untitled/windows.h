#ifndef WINDOWS_H
#define WINDOWS_H

#include <QDialog>

namespace Ui {
class Windows;
}

class Windows : public QDialog
{
    Q_OBJECT

public:
    explicit Windows(QWidget *parent = nullptr);
    ~Windows();

private:
    Ui::Windows *ui;
};

#endif // WINDOWS_H
