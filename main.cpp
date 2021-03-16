#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardItemModel>
#include <QDateTime>
#include "oscilloscopemodel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

//    QStandardItemModel lineModel(100, 4);// 100 rows and 4 columns

//    for (int row = 0; row < lineModel.rowCount(); row++) {
//        QStandardItem *item1 = new QStandardItem(QString::number(row));
//        QDateTime time = QDateTime::currentDateTime().addSecs(row);
//        QStandardItem *item2 = new QStandardItem(QString::number(time.toMSecsSinceEpoch()));
//        QStandardItem *item3 = new QStandardItem(QString::number(row*row));
//        QStandardItem *item4 = new QStandardItem(QString::number(row*100));
//        lineModel.setItem(row, 0, item1);
//        lineModel.setItem(row, 1, item2);
//        lineModel.setItem(row, 2, item3);
//        lineModel.setItem(row, 3, item4);
//    }

    OscilloscopeModel lineModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("lineModel", &lineModel);
    lineModel.startGenerated();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
