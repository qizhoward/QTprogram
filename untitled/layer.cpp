#include "layer.h"
#include "ui_layer.h"
#include <Windows.h>
#include <QMenu>
#include <QContextMenuEvent>

Layer::Layer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Layer)
{
    ui->setupUi(this);


}

Layer::~Layer()
{
    delete ui;
}

