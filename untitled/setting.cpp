#include "setting.h"
#include "ui_setting.h"
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QSplitter>
setting::setting(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}

