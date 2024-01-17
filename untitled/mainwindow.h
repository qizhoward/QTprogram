#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>
#include <QAction>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void openFile(); // 声明槽函数
    void saveFile();
    void saveFileAs();
    void importData();
    void exportData();
    void openDialog();
    void openAbout();
    void toggleLayer();
    void importObjFile(const QString &fileName);
    void exportObjFile(const QString &fileName);
private:
    Ui::MainWindow *ui;
    Qt3DExtras::Qt3DWindow *view;

    void createCoordinateAxes(Qt3DCore::QEntity *rootEntity);
    void createGrid(Qt3DCore::QEntity *rootEntity);

    void showContextMenu(const QPoint &pos);

    // 用于显示场景的模型和场景
    QStandardItemModel *treeViewModel;
    QGraphicsScene *scene;
    QStackedWidget *stackedWidget;
    // Qt3D相关成员
    Qt3DExtras::Qt3DWindow *qt3DView;
    Qt3DCore::QEntity* rootEntity;
    Qt3DCore::QEntity* objEntity;
    Qt3DCore::QEntity* importedObjEntity;

    // OBJ文件格式相关成员
    struct ObjVertex {
        QVector3D position;
        QVector3D normal;
        QVector2D textureCoord;
    };

    struct ObjFile {
        QVector<ObjVertex> vertices;
        QVector<QVector<int>> faces;
    };

    ObjFile objFile;

};




#endif // MAINWINDOW_H
