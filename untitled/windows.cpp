#include "windows.h"
#include "ui_windows.h"

Windows::Windows(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Windows)
{
    ui->setupUi(this);
}

Windows::~Windows()
{
    delete ui;
}
