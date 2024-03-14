#include "mainwindow.h"
#include "About.h"
#include "ui_dialog.h"
#include "ui_mainwindow.h"
#include "ui_setting.h"
#include "ui_layer.h"
#include "dialog.h"
#include "setting.h"
#include "gridwindow.h"
#include "LayerDelegate.h"
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
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
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DRender/QBlendEquation>
#include <Qt3DRender/QPointLight>
#include <QTextEdit>
#include <QScreen>
#include <QStringListModel>
#include <QDialog>
#include <QStringListModel>
#include <QListView>
#include <QStackedWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QScrollArea>
#include <QTreeWidget>
#include <QDockWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QSurfaceFormat>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , importedObjEntity(nullptr)
{
    ui->setupUi(this);

    GridWindow *gridWindow = new GridWindow(this);

    // 设置GridWindow对象为主窗口的中心部件
    setCentralWidget(gridWindow);
    /* QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    QSurfaceFormat format;
    format.setVersion(3, 3);  // 设置 OpenGL 版本为 3.3
    format.setProfile(QSurfaceFormat::CoreProfile);  // 使用核心配置文件
    QSurfaceFormat::setDefaultFormat(format);

    QOpenGLWidget *widget = new QOpenGLWidget(ui->centralwidget);
    layout->addWidget(widget);

    widget->setAutoFillBackground(true);
    QPalette palette = widget->palette();
    palette.setColor(QPalette::Window, Qt::darkGray);
    widget->setPalette(palette);
    setPalette(palette);
*/
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onNewDocumentClicked);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionImport,&QAction::triggered,this,&MainWindow::importData);
    connect(ui->actionExport,&QAction::triggered,this,&MainWindow::exportData);
    connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);
    connect(ui->actionPreferences, &QAction::triggered, this, &MainWindow::openDialog);
    connect(ui->actionPreferences_2,&QAction::triggered, this, &MainWindow::openDialog);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::openAbout);
    connect(ui->actionWhat_s_New,&QAction::triggered, this,[=](){QDesktopServices::openUrl(QUrl("https://github.com/qizhoward/QTprogram"));});
    connect(ui->actionWindows,&QAction::triggered,this,&MainWindow::openWindows);
    connect(ui->actionswitch,&QAction::triggered,this,&MainWindow::openSetting);
    connect(ui->actionLayer,&QAction::triggered,this,&MainWindow::toggleLayer);
    connect(ui->actionScene,&QAction::triggered,this,&MainWindow::toggleScene);
    connect(ui->actionLayer_Explorer,&QAction::triggered,this,&MainWindow::Layer_Explorer);
    connect(ui->actionScene_Explorer,&QAction::triggered,this,&MainWindow::Scene_Explorer);
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
void MainWindow::createGridLines(Qt3DCore::QEntity *rootEntity)
{
    // 创建网格线实体
    Qt3DCore::QEntity *gridLineEntity = new Qt3DCore::QEntity(rootEntity);

    // 创建网格线材料
    Qt3DExtras::QPhongMaterial *gridLineMaterial = new Qt3DExtras::QPhongMaterial();
    gridLineMaterial->setDiffuse(QColor(192, 192, 192)); // 灰色网格线


    // 添加组件到网格线实体

    gridLineEntity->addComponent(gridLineMaterial);
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

    QMenu subMenu3("Attribute");

    QAction action3("Menu Item 3", this);
    menu.addMenu(&subMenu1);
    menu.addMenu(&subMenu2);
    menu.addMenu(&subMenu3);
    menu.addAction(&action3);
    menu.exec(pos);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewDocumentClicked(){
    QTextEdit *newDocument = new QTextEdit(this);
    newDocument->setWindowTitle("New Document");


    // 添加最小化、最大化和关闭按钮
    newDocument->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);


    newDocument->show();
}
void MainWindow::openSetting(){
    QDialog *setting = new QDialog(this); // 创建对话框对象
    // 在新的 Dialog 对象上设置 UI
    Ui::setting uiDialog;
    uiDialog.setupUi(setting);
    qDebug() << "Setting dialog UI loaded: " << setting;

    // 访问设置界面的 listView
    QListView *listView = setting->findChild<QListView*>("listView");
    QStackedWidget *stackedWidget = setting->findChild<QStackedWidget*>("stackedWidget");
    qDebug() << "Setting dialog children: " << setting->children();
    // 设置 listView 的大小策略
    if (listView && stackedWidget) {
        listView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        // 将数据模型设置到 listView 中
        listView->setSpacing(5);

        QStringList data;
        data << "Commonly used" << "exterior" << "select" << "unit" << "browse" << "senior" << "file option"<< "support files";
        QStringListModel *model = new QStringListModel(data, setting); // 创建字符串列表模型
        listView->setModel(model);

        // 添加页面到 stackedWidget
        for (int i = 0; i < data.size(); ++i) {

            SubPage *page = new SubPage(data.at(i), setting); // 创建带有标题的页面

            // 根据页面标题调用相应函数设置内容
            if (data.at(i) == "Commonly used") {
                page->setCommonlyUsedContent();
            } else if (data.at(i) == "exterior") {
                page->setExteriorContent();
            } else if (data.at(i) == "select") {
                page->setSelectContent();
            }else if (data.at(i) == "unit") {
                page->setUnitContent();
            }else if (data.at(i) == "browse") {
                page->setBrowseContent();
            }else if (data.at(i) == "senior") {
                page->setSeniorContent();
            }else if (data.at(i) == "file option") {
                page->setFileoptionContent();
               // 创建 "file option" 页面
                SubPage *fileOptionPage = new SubPage("file option", setting);

                // 将 "file option" 页面添加到 stackedWidget 中
                stackedWidget->addWidget(fileOptionPage);

                // 创建子页面并添加到 stackedWidget
                SubPage *generalPage = new SubPage("General", setting);
                generalPage->setGeneralContent();
                stackedWidget->addWidget(generalPage);

                SubPage *igesPage = new SubPage("IGES", setting);
                igesPage->setIgesContent();
                stackedWidget->addWidget(igesPage);

                SubPage *objPage = new SubPage("OBJ", setting);
                objPage->setObjContent();
                stackedWidget->addWidget(objPage);

                SubPage *stlPage = new SubPage("STL", setting);
                stlPage->setStlContent();
                stackedWidget->addWidget(stlPage);

            }else if (data.at(i) == "support files") {
                page->setSupportfilesContent();
            }
            else {
                // 如果是其他页面，设置空内容或其他内容
            }

            stackedWidget->addWidget(page);


        }

        // 设置初始显示的页面
        stackedWidget->setCurrentIndex(0);
        // 切换页面时更新当前项
        connect(listView, &QListView::clicked, [=](const QModelIndex &index){
            stackedWidget->setCurrentIndex(index.row());
        });

        setting->exec();

    } else {
        qDebug() << "listView or stackedWidget not found";
    }

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
void MainWindow::openWindows(){
    Windows*windows = new Windows(this);
    windows->exec();
}

void MainWindow::Scene_Explorer(){
    QDockWidget *dockWidget1 = new QDockWidget("Scene View", this);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget1);

    // Left side: TreeView
    SceneView = new QTreeView(dockWidget1); // Declare and initialize treeView
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *rootItem = model->invisibleRootItem();
    QStandardItem *item1 = new QStandardItem("Layer 0");
    rootItem->appendRow(item1);
    SceneView->setModel(model);
    SceneView->setHeaderHidden(true);
    dockWidget1->setWidget(SceneView);


}
void MainWindow::Layer_Explorer(){
    QDockWidget *dockWidget = new QDockWidget("Layer View", this);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    QIcon icon(":/Resource/Layer/Layers_24.png"); // 替换为你自己的图标路径
    // Left side: TreeView
    treeView = new QTreeView(dockWidget); // Declare and initialize treeView
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *rootItem = model->invisibleRootItem();
    QStandardItem *item1 = new QStandardItem("Layer 0(default)");
    item1->setIcon(icon);
    rootItem->appendRow(item1);
    treeView->setModel(model);
    treeView->setHeaderHidden(true);
    dockWidget->setWidget(treeView);

}
void MainWindow::toggleLayer(){


    QDockWidget *dockWidget = new QDockWidget("Layer View", this);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);


    QWidget* dockWidgetContents = new QWidget(this);
    dockWidget->setWidget(dockWidgetContents);
    QVBoxLayout* layout = new QVBoxLayout(dockWidgetContents);

    QMenuBar *menuBar = new QMenuBar(dockWidgetContents);
    QMenu *fileMenu = menuBar->addMenu("Select");
    QMenu *showMenu = menuBar->addMenu("Show");
    QMenu *editMenu = menuBar->addMenu("Edit");
    QMenu *customMenu = menuBar->addMenu("Custom");
    QAction *SelectAction = fileMenu->addAction("Select All");
    QAction *exitAction = fileMenu->addAction("&Exit");
    QAction *showAction = showMenu->addAction("Show impact");
    QAction *copyAction = editMenu->addAction("Copy");
    QAction *layoutAction = customMenu->addAction("Layout");
    connect(SelectAction, &QAction::triggered, this, &MainWindow::selectAllItems);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(showAction, &QAction::triggered, this, &MainWindow::showItems);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyItems);
    connect(layoutAction, &QAction::triggered, this, &MainWindow::layoutItems);
    layout->setMenuBar(menuBar);


    QTreeWidget* treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(4); // 设置树形视图的列数
    LayerDelegate delegate;
    treeWidget->setItemDelegate(&delegate);

    treeWidget->setHeaderLabels(QStringList() << "名称"<< "冻结"<<"显示为外框"<<"可渲染"); // 设置列头标签
    layout->addWidget(treeWidget);
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, "0(default)");
    rootItem->setIcon(0, QIcon(":/Resource/Layer/Layers_24.png"));
    rootItem->setData(0, Qt::DecorationRole,  QVariant(QIcon(":/Resource/Layer/ble_on_24.png")));
    rootItem->setData(0, Qt::UserRole, QVariant(QIcon(":/Resource/Layer/ble_off_24.png")));

    for (int i = 1; i < 4; ++i) {
        rootItem->setText(i, "Data");
    }

    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(rootItem);
    childItem1->setText(0, "Child 1");
    treeWidget->expandAll();
    update();
}
void MainWindow::toggleScene(){
    if (SceneView->isVisible())
    {
        SceneView->setVisible(false); // Hide treeView
    }
    else
    {
        SceneView->setVisible(true); // Show treeView
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


void MainWindow::selectAllItems() {
    // 实现selectallItems槽函数
}
void MainWindow::showItems(){}
void MainWindow::copyItems(){}
void MainWindow::layoutItems(){}

