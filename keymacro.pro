QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -luser32

INCLUDEPATH += $$PWD
HEADERS += $$files($$PWD/*.h, false)
SOURCES += $$files($$PWD/*.cpp, false)
FORMS += $$files($$PWD/*.ui, false)

# 定义全局变量
SW_PROJECT_DIR=$$PWD/
CONAN_FILE_DIR = $$SW_PROJECT_DIR/conanfile

# 导入全局公共模块
include($$SW_PROJECT_DIR/qmakefunc.pri)

# 定义全局的输出变量
SW_PROJECT_OUT = $$SW_PROJECT_DIR/build/$$SPEC/$$SWQ_BUILD_TYPE()
CONAN_OUT_DIR = $$CONAN_FILE_DIR/dependents/$$SPEC/$$SWQ_BUILD_TYPE()/

# 安裝和清理依赖库
$$SWQ_INSTALL_QTLIB($$(QTDIR), $$SW_PROJECT_OUT)

#模块
include($$PWD/GlobalMouseKey/GlobalMouseKey.pri)
include($$PWD/services/services.pri)
include($$PWD/widgets/widgets.pri)
include($$PWD/languages/languages.pri)

DESTDIR = $$SW_PROJECT_OUT

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc
