QT       += core gui opengl
QT += 3dcore 3drender 3dextras 3dinput 3dlogic
INCLUDEPATH += C:\Qt\6.6.2\mingw_64\include\QtOpenGLWidgets
INCLUDEPATH += C:\Qt\6.6.2\mingw_64\bin
LIBS += "C:\Qt\6.6.2\mingw_64\bin\Qt6OpenGLWidgets.dll"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OpenGLWidget.cpp \
    about.cpp \
    dialog.cpp \
    gridwindow.cpp \
    layer.cpp \
    layerdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    selectionwidget.cpp \
    setting.cpp \
    windows.cpp

HEADERS += \
    OpenGLWidget.h \
    about.h \
    dialog.h \
    gridwindow.h \
    layer.h \
    layerdelegate.h \
    mainwindow.h \
    selectionwidget.h \
    setting.h \
    windows.h

FORMS += \
    about.ui \
    dialog.ui \
    layer.ui \
    mainwindow.ui \
    setting.ui \
    windows.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

DISTFILES += \
    Translations/qt_zh_CN.qm \
    qt_zh_CN.ts
TRANSLATIONS += qt_zh_CN.ts

LIBS += -lopengl32 -luser32



win32: LIBS += -L$$PWD/lib/lib-mingw-w64/ -lglfw3dll

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include
