#include "mainwindow.h"
#include "About.h"
#include "ui_dialog.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QTreeView>
#include <QGraphicsItem>
#include <QStandardItem>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QMessageBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , importedObjEntity(nullptr)
{
    ui->setupUi(this);

    // Create Qt3D window for the 3D scene
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view);
    setCentralWidget(container);

    // Set background color to black
    view->defaultFrameGraph()->setClearColor(QColor(Qt::black));

    // Root entity for the scene
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    scene = new QGraphicsScene();
    createCoordinateAxes(rootEntity);
    createGrid(rootEntity);


    // Set up camera
    Qt3DRender::QCamera *camera = view->camera();
    Qt3DRender::QCameraLens *lens = camera->lens();
    lens->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 10));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Add orbit camera controller
    Qt3DExtras::QOrbitCameraController *orbitController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    orbitController->setLinearSpeed(50.0f);
    orbitController->setLookSpeed(180.0f);
    orbitController->setCamera(camera);

    // Set root entity
    view->setRootEntity(rootEntity);

    container->installEventFilter(this);





    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionImport,&QAction::triggered,this,&MainWindow::importData);
    connect(ui->actionExport,&QAction::triggered,this,&MainWindow::exportData);
    connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);
    connect(ui->actionPreferences, &QAction::triggered, this, &MainWindow::openDialog);
    connect(ui->actionPreferences_2,&QAction::triggered, this, &MainWindow::openDialog);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::openAbout);
    connect(ui->actionLayer,&QAction::triggered,this,&MainWindow::toggleLayer);


}

void MainWindow::createCoordinateAxes(Qt3DCore::QEntity *rootEntity)
{
    // Create an entity for the coordinate axes
    Qt3DCore::QEntity *axesEntity = new Qt3DCore::QEntity(rootEntity);

    // Create the material for the axes
    Qt3DExtras::QPhongMaterial *axisMaterial = new Qt3DExtras::QPhongMaterial();

    // X-axis (Red)
    Qt3DExtras::QCylinderMesh *xAxisMesh = new Qt3DExtras::QCylinderMesh();
    xAxisMesh->setRadius(0.05f);
    xAxisMesh->setLength(3.0f);

    Qt3DCore::QTransform *xAxisTransform = new Qt3DCore::QTransform();
    xAxisTransform->setTranslation(QVector3D(1.5f, 0.0f, 0.0f)); // Position the X-axis
    xAxisTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f)); // Rotate X-axis to point along X

    Qt3DCore::QEntity *xAxisEntity = new Qt3DCore::QEntity(axesEntity);
    xAxisEntity->addComponent(xAxisMesh);
    axisMaterial->setDiffuse(QColor(255, 0, 0)); // Red color for X-axis
    xAxisEntity->addComponent(axisMaterial);
    xAxisEntity->addComponent(xAxisTransform);

    // Y-axis (Green)
    Qt3DExtras::QCylinderMesh *yAxisMesh = new Qt3DExtras::QCylinderMesh();
    yAxisMesh->setRadius(0.05f);
    yAxisMesh->setLength(3.0f);

    Qt3DCore::QTransform *yAxisTransform = new Qt3DCore::QTransform();
    yAxisTransform->setTranslation(QVector3D(0.0f, 1.5f, 0.0f)); // Position the Y-axis
    yAxisTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), -90.0f)); // Rotate Y-axis to point along Y

    Qt3DCore::QEntity *yAxisEntity = new Qt3DCore::QEntity(axesEntity);
    yAxisEntity->addComponent(yAxisMesh);
    axisMaterial->setDiffuse(QColor(0, 255, 0)); // Green color for Y-axis
    yAxisEntity->addComponent(axisMaterial);
    yAxisEntity->addComponent(yAxisTransform);

    // Z-axis (Blue)
    Qt3DExtras::QCylinderMesh *zAxisMesh = new Qt3DExtras::QCylinderMesh();
    zAxisMesh->setRadius(0.05f);
    zAxisMesh->setLength(3.0f);

    Qt3DCore::QTransform *zAxisTransform = new Qt3DCore::QTransform();
    zAxisTransform->setTranslation(QVector3D(0.0f, 0.0f, 1.5f)); // Position the Z-axis
    zAxisTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90.0f)); // Rotate Z-axis to point along Z

    Qt3DCore::QEntity *zAxisEntity = new Qt3DCore::QEntity(axesEntity);
    zAxisEntity->addComponent(zAxisMesh);
    axisMaterial->setDiffuse(QColor(0, 0, 255)); // Blue color for Z-axis
    zAxisEntity->addComponent(axisMaterial);
    zAxisEntity->addComponent(zAxisTransform);
}

void MainWindow::createGrid(Qt3DCore::QEntity *rootEntity)
{

    // 加载并显示 OBJ 模型
    Qt3DRender::QMesh* objMesh = new Qt3DRender::QMesh();
    QString filePath = "Users\\Administrator\\Desktop\\11803_Airplane_v1_l1.obj";
    objMesh->setMeshName(QFileInfo(filePath).absoluteFilePath());  // 设置你的 OBJ 文件的路径

    Qt3DExtras::QPhongMaterial* objMaterial = new Qt3DExtras::QPhongMaterial();
    objMaterial->setDiffuse(QColor(255, 255, 255)); // 根据需要设置材质属性

    objEntity = new Qt3DCore::QEntity(rootEntity);
    objEntity->addComponent(objMesh);
    objEntity->addComponent(objMaterial);

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == centralWidget() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            showContextMenu(mouseEvent->globalPos());
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu menu(this);

    QMenu subMenu1("Submenu 1");
    QAction action1_1("Menu Item 1_1", this);
    QAction action1_2("Menu Item 1_2", this);
    subMenu1.addAction(&action1_1);
    subMenu1.addAction(&action1_2);

    QMenu subMenu2("Submenu 2");
    QAction action2_1("Menu Item 2_1", this);
    QAction action2_2("Menu Item 2_2", this);
    subMenu2.addAction(&action2_1);
    subMenu2.addAction(&action2_2);

    QAction action3("Menu Item 3", this);
    menu.addMenu(&subMenu1);
    menu.addMenu(&subMenu2);
    menu.addAction(&action3);
    menu.exec(pos);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFile() {

    // 在这里编写处理打开文件操作的代码
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择文件"), "", tr("2024 File(*.3D);;TXT File(*.txt);;所有文件 (*.*)"));
    if (!fileName.isEmpty()) {
        // 处理打开文件后的逻辑，例如读取文件内容等
        qDebug() << "Selected File: " << fileName;
        statusBar()->showMessage("Selected File: "+fileName);
    }
}
void MainWindow::saveFile()
{
    // 在这里实现保存文件逻辑
    // 例如，保存当前打开的文件内容
    qDebug() << "Saving file...";
    statusBar()->showMessage("Saving file...");
}
void MainWindow::saveFileAs()
{
    // 在这里弹出另存为对话框，允许用户选择文件路径
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), "", tr("2024 File(*.3D);;所有文件 (*.*)"));
    if (!fileName.isEmpty()) {
        // 在这里执行另存为文件的逻辑
        // 例如，将当前内容另存为指定路径的文件
        qDebug() << "Saving file as: " << fileName;
        statusBar()->showMessage("Saving file as: "+fileName);
    }
}
void MainWindow::importData(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择OBJ文件"), "", tr("OBJ文件 (*.obj);;所有文件 (*.*)"));
    if (!fileName.isEmpty()) {
        importObjFile(fileName);
        statusBar()->showMessage("Imported OBJ File: " + fileName);
    }
}
void MainWindow::exportData(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出OBJ文件"), "", tr("OBJ文件 (*.obj);;所有文件 (*.*)"));
    if (!fileName.isEmpty()) {
        exportObjFile(fileName);
        statusBar()->showMessage("Exported OBJ File: " + fileName);
    }
}
void MainWindow::openDialog(){
    QDialog *dialog = new QDialog(this);
    Ui::Dialog ui;
    ui.setupUi(dialog);

    dialog->exec();
}
void MainWindow::openAbout(){
    About *aboutWindow = new About(this);
    aboutWindow->exec();
}
void MainWindow::toggleLayer(){
    int layerIndex = 0;  // Replace with your actual layer index

   QWidget *layerWidget = stackedWidget->widget(layerIndex);

    if (layerWidget) {
        bool isVisible = !layerWidget->isVisible();
        layerWidget->setVisible(isVisible);

        if (isVisible) {
           stackedWidget->setCurrentIndex(layerIndex);
        }
    }
}
void MainWindow::importObjFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << fileName;
        QMessageBox::critical(this, tr("Error"), tr("Failed to open OBJ file."));
        return;
    }

    objFile.vertices.clear();
    objFile.faces.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(' ');

        if (parts.isEmpty())
            continue;

        if (parts[0] == "v") {
            ObjVertex vertex;
            vertex.position.setX(parts[1].toFloat());
            vertex.position.setY(parts[2].toFloat());
            vertex.position.setZ(parts[3].toFloat());
            objFile.vertices.append(vertex);
        } else if (parts[0] == "f") {
            QVector<int> faceIndices;
            for (int i = 1; i < parts.size(); ++i) {
                QStringList vertexParts = parts[i].split('/');
                faceIndices.append(vertexParts[0].toInt() - 1);
            }
            objFile.faces.append(faceIndices);
        }
    }

    file.close();

    // 清除之前的 objEntity
    if (objEntity) {
        // 移除 objEntity 的所有组件
        QList<Qt3DCore::QComponent *> components = objEntity->components();
        for (Qt3DCore::QComponent *component : components) {
            objEntity->removeComponent(component);
            delete component;
        }

        // 释放 objEntity 内存
        delete objEntity;
        objEntity = nullptr;  // 重要：确保在删除后将指针置为空，以免出现悬挂指针
    }


    // 创建新的 objEntity
    objEntity = new Qt3DCore::QEntity(rootEntity);

    // 创建材质
    Qt3DExtras::QPhongMaterial *objMaterial = new Qt3DExtras::QPhongMaterial();
    objMaterial->setDiffuse(QColor(255, 255, 255));

    // 创建顶点坐标数组
    QVector<float> vertices;
    for (const ObjVertex &vertex : objFile.vertices) {
        vertices << vertex.position.x() << vertex.position.y() << vertex.position.z();
    }

    // 创建面索引数组
    QVector<int> indices;
    for (const QVector<int> &faceIndices : objFile.faces) {
        for (int vertexIndex : faceIndices) {
            indices << vertexIndex;
        }
    }

    // 创建顶点和索引缓冲区
    Qt3DCore::QBuffer *vertexBuffer = new Qt3DCore::QBuffer();
    vertexBuffer->setData(QByteArray::fromRawData(reinterpret_cast<const char*>(vertices.constData()), vertices.size() * sizeof(float)));

    Qt3DCore::QBuffer *indexBuffer = new Qt3DCore::QBuffer();
    indexBuffer->setData(QByteArray::fromRawData(reinterpret_cast<const char*>(indices.constData()), indices.size() * sizeof(int)));

    // 创建几何体
    Qt3DCore::QGeometry *objGeometry = new Qt3DCore::QGeometry(objEntity);

    Qt3DCore::QAttribute *positionAttribute = new Qt3DCore::QAttribute(objGeometry);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setByteOffset(0);
    positionAttribute->setCount(vertices.size() / 3);

    Qt3DCore::QAttribute *indexAttribute = new Qt3DCore::QAttribute(objGeometry);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
    indexAttribute->setVertexSize(1);
    indexAttribute->setByteOffset(0);
    indexAttribute->setCount(indices.size());

    // 添加属性到几何体
    objGeometry->addAttribute(positionAttribute);
    objGeometry->addAttribute(indexAttribute);

    // 创建网格
    Qt3DRender::QGeometryRenderer *objRenderer = new Qt3DRender::QGeometryRenderer();
    objRenderer->setGeometry(objGeometry);

    // 添加材质和网格到实体
    objEntity->addComponent(objMaterial);
    objEntity->addComponent(objRenderer);
}
void MainWindow::exportObjFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << fileName;
        QMessageBox::critical(this, tr("Error"), tr("Failed to create OBJ file."));
        return;
    }

    QTextStream out(&file);

    for (const ObjVertex &vertex : objFile.vertices) {
        out << "v " << vertex.position.x() << " " << vertex.position.y() << " " << vertex.position.z() << "\n";
    }

    for (const QVector<int> &faceIndices : objFile.faces) {
        out << "f";
        for (int vertexIndex : faceIndices) {
            out << " " << vertexIndex + 1;  // +1 because OBJ indices start from 1
        }
        out << "\n";
    }

    file.close();

}
