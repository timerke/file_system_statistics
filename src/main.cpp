#include <QApplication>
#include <QMetaType>
#include "filedirinfo.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    qRegisterMetaType<StatisticsDataT>("StatisticsDataT");
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
