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
#include <QLabel>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QScrollArea>
#include <QComboBox>
#include <QTextEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QTreeView>
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
    void onNewDocumentClicked();
    void openSetting();
    void saveFile();
    void saveFileAs();
    void importData();
    void exportData();
    void openDialog();
    void openAbout();
    void toggleLayer();
    void toggleScene();
    void Layer_Explorer();
    void Scene_Explorer();
    void openWindows();
    void importObjFile(const QString &fileName);
    void exportObjFile(const QString &fileName);

    void showContextMenu(const QPoint &pos);

    void selectAllItems();
    void showItems();
    void copyItems();
    void layoutItems();
private:

    QTreeView *treeView;
    QDockWidget *dockWidget;
    QTreeView *SceneView;

    Ui::MainWindow *ui;
    Qt3DExtras::Qt3DWindow *view;

    void createCoordinateAxes(Qt3DCore::QEntity *rootEntity);
    void createGridLines(Qt3DCore::QEntity *rootEntity);
    Qt3DRender::QGeometryRenderer *createGridLines(float size, int resolution);


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

class SubPage : public QWidget {
    Q_OBJECT
public:
    SubPage(const QString& title, QWidget *parent = nullptr)
        : QWidget(parent){

    }

    void setCommonlyUsedContent() {
        // 声明副标题标签
        QLabel *subtitleLabel3 = new QLabel("Graphics performance");
        QLabel *subtitleLabel1 = new QLabel("Interface options");
        QLabel *subtitleLabel2 = new QLabel("Control options");

        // 设置副标题样式
        subtitleLabel1->setStyleSheet("font-weight: bold;");
        subtitleLabel2->setStyleSheet("font-weight: bold;");
        subtitleLabel3->setStyleSheet("font-weight: bold;");
        // 创建分割线
        QFrame *line1 = new QFrame();
        QFrame *line2 = new QFrame();
        QFrame *line3 = new QFrame();

        // 设置分割线样式
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);
        line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        // 创建复选框和标签
        QCheckBox *checkBox = new QCheckBox("Show Tooltips");
        QCheckBox *checkBox2 = new QCheckBox("Display status messages in the window");
        QCheckBox *checkBox3 = new QCheckBox("Display pop-up messages in the status bar");
        QCheckBox *checkBox4 = new QCheckBox("Display pop-up progress messages");
        QCheckBox *checkBox5 = new QCheckBox("Display tool highlights");
        QCheckBox *checkBox6 = new QCheckBox("Show scrollbars");
        checkBox->setChecked(true);
        checkBox2->setChecked(true);
        checkBox3->setChecked(true);
        checkBox4->setChecked(true);
        QCheckBox *checkBox7 = new QCheckBox("Display view direction in the design window");
        QCheckBox *checkBox8 = new QCheckBox("Display mini toolbar on selected content");
        checkBox7->setChecked(true);
        checkBox8->setChecked(true);

        QHBoxLayout *renderQualityLayout = new QHBoxLayout;
        QLabel *renderQualityLabel = new QLabel("Render Quality：");
        QComboBox *ComboBox = new QComboBox;

        // 添加选项到下拉框
        ComboBox->addItem("Low");
        ComboBox->addItem("Middle");
        ComboBox->addItem("High");
        renderQualityLayout->addWidget(renderQualityLabel);
        renderQualityLayout->addWidget(ComboBox);

        QVBoxLayout *layout = new QVBoxLayout(this);
        // 添加副标题和分割线到布局中

        layout->addWidget(subtitleLabel3);
        layout->addWidget(line3);
        layout->addLayout(renderQualityLayout);
        /*layout->addSpacing(10); // 添加一些额外的空间 */
        layout->addWidget(subtitleLabel1);
        layout->addWidget(line1);
        layout->addWidget(checkBox);
        layout->addWidget(checkBox2);
        layout->addWidget(checkBox3);
        layout->addWidget(checkBox4);
        layout->addWidget(checkBox5);
        layout->addWidget(checkBox6);
        layout->addWidget(subtitleLabel2);
        layout->addWidget(line2);
        layout->addWidget(checkBox7);
        layout->addWidget(checkBox8);
        layout->addStretch();// 添加一个可伸缩的空间
        /*layout->addWidget(scrollArea); // 将滚动区域添加到对话框中*/
        layout->addLayout(layout);
    }
    void setExteriorContent(){
        // 声明副标题标签
        QLabel *subtitleLabel1 = new QLabel("Interface options");
        QLabel *subtitleLabel2 = new QLabel("Control options");
        QLabel *subtitleLabel3 = new QLabel("Graphics performance");
        // 设置副标题样式
        subtitleLabel1->setStyleSheet("font-weight: bold;");
        subtitleLabel2->setStyleSheet("font-weight: bold;");
        subtitleLabel3->setStyleSheet("font-weight: bold;");
        // 创建分割线
        QFrame *line1 = new QFrame();
        QFrame *line2 = new QFrame();
        QFrame *line3 = new QFrame();
        // 设置分割线样式
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);
        line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        // 创建复选框和标签
        QCheckBox *checkBox = new QCheckBox("复选框");
        QCheckBox *checkBox2 = new QCheckBox("复选框2");
        QCheckBox *checkBox3 = new QCheckBox("复选框3");
        QCheckBox *checkBox4 = new QCheckBox("复选框4");
        QCheckBox *checkBox5 = new QCheckBox("复选框5");
        QCheckBox *checkBox6 = new QCheckBox("复选框6");
        QCheckBox *checkBox7 = new QCheckBox("复选框7");
        QCheckBox *checkBox8 = new QCheckBox("复选框8");

        // 获取当前页面的布局
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 添加副标题和分割线到布局中
        layout->addWidget(subtitleLabel1);
        layout->addWidget(line1);
        layout->addWidget(checkBox);
        layout->addWidget(checkBox2);
        layout->addWidget(checkBox3);
        layout->addWidget(checkBox4);
        layout->addWidget(subtitleLabel2);
        layout->addWidget(line2);
        layout->addWidget(checkBox5);
        layout->addWidget(checkBox6);
        layout->addStretch();// 添加一个可伸缩的空间
        layout->addWidget(subtitleLabel3);
        layout->addWidget(line3);
        layout->addWidget(checkBox7);
        layout->addWidget(checkBox8);
    }
    void setSelectContent(){
        // 声明副标题标签
        QLabel *subtitleLabel1 = new QLabel("Routine");
        QLabel *subtitleLabel2 = new QLabel("Powerful selection");
        QLabel *subtitleLabel3 = new QLabel("Small plane");
        // 设置副标题样式
        subtitleLabel1->setStyleSheet("font-weight: bold;");
        subtitleLabel2->setStyleSheet("font-weight: bold;");
        subtitleLabel3->setStyleSheet("font-weight: bold;");
        // 创建分割线
        QFrame *line1 = new QFrame();
        QFrame *line2 = new QFrame();
        QFrame *line3 = new QFrame();
        // 设置分割线样式
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);
        line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        /*QHBoxLayout *renderQualityLayout = new QHBoxLayout;
        QHBoxLayout *renderLayout = new QHBoxLayout;*/

        QHBoxLayout *Layout = new QHBoxLayout;
        QHBoxLayout *Layout2 = new QHBoxLayout;
        QHBoxLayout *Layout3 = new QHBoxLayout;
        QHBoxLayout *Layout4 = new QHBoxLayout;
        QHBoxLayout *Layout5 = new QHBoxLayout;
        QLabel *Label = new QLabel("Click radius：");
        QLabel *Label2 = new QLabel("pixel");
        QLabel *Label3 = new QLabel("'Powerful Choice' Relative Tolerance：");
        QLabel *Label4 = new QLabel("Small plane selection granularity：");
        QLabel *Label5 = new QLabel("Small plane drawing selection radius：");
        QLabel *Label6 = new QLabel("pixel");
        QRadioButton *RadioButton = new QRadioButton("fine");
        QRadioButton *RadioButton2 = new QRadioButton("rough");
        QSpinBox *spinBox = new QSpinBox;
        QTextEdit *TextEdit = new QTextEdit;
        QTextEdit *TextEdit2 = new QTextEdit;
        // 添加选项到下拉框

        TextEdit->setText("5");
        TextEdit->setFixedSize(50, 25);
        TextEdit->setAlignment(Qt::AlignRight);
        TextEdit2->setText("1%");
        TextEdit2->setFixedSize(100, 25);
        spinBox->setRange(0, 100); // 设置范围
        spinBox->setValue(10); // 设置默认值
        RadioButton->setChecked(true);

        Layout->addWidget(Label);
        Layout->addWidget(TextEdit);
        Layout->addWidget(Label2);
        Layout2->addWidget(Label3);
        Layout2->addWidget(TextEdit2);
        Layout3->addWidget(Label4);
        Layout4->addWidget(RadioButton);
        Layout4->addWidget(RadioButton2);
        Layout5->addWidget(Label5);
        Layout5->addWidget(spinBox);
        Layout5->addWidget(Label6);
        /*Layout5->addWidget(Label6);*/
        QVBoxLayout *layout = new QVBoxLayout(this);

        QCheckBox *checkBox = new QCheckBox("Using the mouse scroll wheel to select an edge ring");
        QCheckBox *checkBox2 = new QCheckBox("Display previous selection and pre highlight prompts");
        QCheckBox *checkBox3 = new QCheckBox("Automatically calculate ‘powerful selection’ results");
        checkBox3->setChecked(true);

        layout->addWidget(subtitleLabel1);
        layout->addWidget(line1);
        layout->addLayout(Layout);
        layout->addWidget(checkBox);
        layout->addWidget(checkBox2);
        layout->addWidget(subtitleLabel2);
        layout->addWidget(line2);
        layout->addWidget(checkBox3);
        layout->addLayout(Layout2);
        layout->addWidget(subtitleLabel3);
        layout->addWidget(line3);
        layout->addLayout(Layout3);
        layout->addLayout(Layout4);
        layout->addLayout(Layout5);
        layout->addStretch();
        layout->addLayout(layout);




    }
    void setUnitContent(){
        // 声明副标题标签
        QLabel *subtitleLabel1 = new QLabel("Unit");
        QLabel *subtitleLabel2 = new QLabel("Grid");
        QLabel *subtitleLabel3 = new QLabel("Text");
        // 设置副标题样式
        subtitleLabel1->setStyleSheet("font-weight: bold;");
        subtitleLabel2->setStyleSheet("font-weight: bold;");
        subtitleLabel3->setStyleSheet("font-weight: bold;");
        // 创建分割线
        QFrame *line1 = new QFrame();
        QFrame *line2 = new QFrame();
        QFrame *line3 = new QFrame();
        // 设置分割线样式
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);
        line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QHBoxLayout *Layout = new QHBoxLayout;
        QHBoxLayout *Layout2 = new QHBoxLayout;
        QHBoxLayout *Layout3 = new QHBoxLayout;
        QHBoxLayout *Layout4 = new QHBoxLayout;
        QHBoxLayout *Layout5 = new QHBoxLayout;
        QHBoxLayout *Layout6 = new QHBoxLayout;
        QHBoxLayout *Layout7 = new QHBoxLayout;
        QHBoxLayout *Layout8 = new QHBoxLayout;
        QHBoxLayout *Layout9 = new QHBoxLayout;
        QHBoxLayout *Layout10 = new QHBoxLayout;
        QLabel *Label = new QLabel("Length gauge：");
        QLabel *Label2 = new QLabel("Type：");
        QLabel *Label3 = new QLabel("Length：");
        QLabel *Label4 = new QLabel("Decimal/Fraction：");
        QLabel *Label5 = new QLabel("Angle：");
        QLabel *Label6 = new QLabel("Quality：");
        QLabel *Label7 = new QLabel("Density：");
        QLabel *Label8 = new QLabel("Symbol：");

        QLabel *Label9 = new QLabel("Minimum grid spacing：");
        QLabel *Label10 = new QLabel("Text height unit：");
        QComboBox *ComboBox = new QComboBox;
        QComboBox *ComboBox2 = new QComboBox;
        QComboBox *ComboBox3 = new QComboBox;
        QComboBox *ComboBox4 = new QComboBox;
        QComboBox *ComboBox5 = new QComboBox;
        QComboBox *ComboBox6 = new QComboBox;
        QComboBox *ComboBox7 = new QComboBox;
        QComboBox *ComboBox8 = new QComboBox;
        ComboBox->addItem("standard");
        ComboBox->addItem("small");
        ComboBox->addItem("large");
        ComboBox2->addItem("Metric system");
        ComboBox2->addItem("Imperial system");
        ComboBox3->addItem("millimeter");
        ComboBox3->addItem("centimeter");
        ComboBox3->addItem("metre");
        ComboBox4->addItem("decimal");
        ComboBox5->addItem("degree");
        ComboBox5->addItem("Degrees/minutes/seconds");
        ComboBox5->addItem("Degrees/minutes");
        ComboBox5->addItem("Radians");
        ComboBox6->addItem("gram");
        ComboBox6->addItem("Kilogram");
        ComboBox7->addItem("derive");
        ComboBox7->addItem("independent");
        ComboBox8->addItem("mm");

        Layout->addWidget(Label);
        Layout->addWidget(ComboBox);
        Layout2->addWidget(Label2);
        Layout2->addWidget(ComboBox2);
        Layout3->addWidget(Label3);
        Layout3->addWidget(ComboBox3);
        Layout4->addWidget(Label4);
        Layout4->addWidget(ComboBox4);
        Layout5->addWidget(Label5);
        Layout5->addWidget(ComboBox5);
        Layout6->addWidget(Label6);
        Layout6->addWidget(ComboBox6);
        Layout7->addWidget(Label7);
        Layout7->addWidget(ComboBox7);
        Layout8->addWidget(Label8);
        Layout8->addWidget(ComboBox8);

        Layout9->addWidget(Label9);
        Layout10->addWidget(Label10);
        // 获取当前页面的布局
        QVBoxLayout *layout = new QVBoxLayout(this);

        layout->addWidget(subtitleLabel1);
        layout->addWidget(line1);
        layout->addLayout(Layout);
        layout->addLayout(Layout2);
        layout->addLayout(Layout3);
        layout->addLayout(Layout4);
        layout->addLayout(Layout5);
        layout->addLayout(Layout6);
        layout->addLayout(Layout7);
        layout->addLayout(Layout8);
        layout->addWidget(subtitleLabel2);
        layout->addWidget(line2);
        layout->addLayout(Layout9);
        layout->addStretch();// 添加一个可伸缩的空间
        layout->addWidget(subtitleLabel3);
        layout->addWidget(line3);
        layout->addLayout(Layout10);
    }
    void setBrowseContent(){
        // 声明副标题标签
        QLabel *subtitleLabel1 = new QLabel("Browse");
        // 设置副标题样式
        subtitleLabel1->setStyleSheet("font-weight: bold;");

        // 创建分割线
        QFrame *line1 = new QFrame();

        // 设置分割线样式
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


        QVBoxLayout *layout = new QVBoxLayout(this);


        layout->addWidget(subtitleLabel1);
        layout->addStretch();
        layout->addLayout(layout);
    }
    void setSeniorContent(){
        // 声明副标题标签
        QLabel *subtitleLabel1 = new QLabel("Routine");
        QLabel *subtitleLabel2 = new QLabel("Behavior");
        QLabel *subtitleLabel3 = new QLabel("Graph");
        // 设置副标题样式
        subtitleLabel1->setStyleSheet("font-weight: bold;");
        subtitleLabel2->setStyleSheet("font-weight: bold;");
        subtitleLabel3->setStyleSheet("font-weight: bold;");
        // 创建分割线
        QFrame *line1 = new QFrame();
        QFrame *line2 = new QFrame();
        QFrame *line3 = new QFrame();
        // 设置分割线样式
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);
        line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QHBoxLayout *renderQualityLayout = new QHBoxLayout;
        QHBoxLayout *renderLayout = new QHBoxLayout;
        QHBoxLayout *Layout = new QHBoxLayout;
        QLabel *renderQualityLabel = new QLabel("Renderer：");
        QLabel *renderLabel = new QLabel("Preview before modification：");
        QLabel *Label = new QLabel("Maximum number of undo steps：");
        QLabel *Label2 = new QLabel("(requires restart)");
        QComboBox *ComboBox = new QComboBox;
        QComboBox *ComboBox2 = new QComboBox;
        QTextEdit *TextEdit = new QTextEdit;
        // 添加选项到下拉框

        TextEdit->setText("50");
        TextEdit->setFixedSize(50, 25);
        TextEdit->setAlignment(Qt::AlignRight);
        Layout->addWidget(Label);
        Layout->addWidget(TextEdit);
        Layout->addWidget(Label2);
        ComboBox2->addItem("Auto");
        ComboBox2->addItem("Open");
        ComboBox2->addItem("Close");
        renderLayout->addWidget(renderLabel);
        renderLayout->addWidget(ComboBox2);
        ComboBox->addItem("OpenGL");
        ComboBox->addItem("Direct3D 11");
        ComboBox->addItem("Direct3D 12");
        ComboBox->addItem("Disabled");
        renderQualityLayout->addWidget(renderQualityLabel);
        renderQualityLayout->addWidget(ComboBox);

        QVBoxLayout *layout = new QVBoxLayout(this);

        QCheckBox *checkBox = new QCheckBox("Enhance shadows");
        QCheckBox *checkBox2 = new QCheckBox("Multi threaded small planarization");
        QCheckBox *checkBox3 = new QCheckBox("Open View Change Animation");
        QCheckBox *checkBox4 = new QCheckBox("Enable constraint based sketching (requires restart)");
        checkBox->setChecked(true);
        checkBox2->setChecked(true);
        checkBox3->setChecked(true);

        layout->addWidget(subtitleLabel1);
        layout->addWidget(line1);
        layout->addWidget(checkBox4);
        layout->addWidget(checkBox3);
        layout->addLayout(Layout);
        layout->addWidget(subtitleLabel2);
        layout->addWidget(line2);
        layout->addLayout(renderLayout);
        layout->addWidget(subtitleLabel3);
        layout->addWidget(line3);
        layout->addLayout(renderQualityLayout);
        layout->addWidget(checkBox);
        layout->addWidget(checkBox2);
        layout->addStretch();
        layout->addLayout(layout);
    }
    void setFileoptionContent(){}
    void setSupportfilesContent(){}
    void setGeneralContent() {

    }
    void setIgesContent(){}
    void setObjContent(){}
    void setStlContent(){}

};



#endif // MAINWINDOW_H
