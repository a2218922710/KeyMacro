#include <QApplication>
#include <QTranslator>

#include <Windows.h>
#include "services/comfunc.h"
#include "widgets/mainwindow.h"
#include "widgets/inputlistview.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString qss;
    QFile qssFile(":/qss.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = qssFile.readAll();

        a.setStyleSheet(qss);
        qssFile.close();
    }

    QString appDir = QApplication::applicationDirPath();

    QTranslator default_ranslator;
    default_ranslator.load(appDir + "/languages/qt_zh_CN.qm");
    a.installTranslator(&default_ranslator);

    QTranslator translator;
    translator.load(appDir + "/languages/tr-zh_CN.qm");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
