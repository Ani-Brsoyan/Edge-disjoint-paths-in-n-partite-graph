#include "mainwindow.h"

#include <QApplication>
#include <QSharedPointer>
#include <QString>

#include "Graph.h"
#include "GraphUtils.h"

int main(int argc, char *argv[])
{
    QString inputFile = "/home/ani/Qt/DiplomaWork/example.txt";
    Graph* g = parser::parseFileAndCreateGraph(inputFile);
    QApplication a(argc, argv);
    MainWindow w(g);
    GraphWidget* gw = w.getGraphWidget();
    if(!gw) {
        qWarning() << "Failed to get the GraphWidget instance from MainWindow.";
        return 1;
    }
    gw->setGraph(g);
    w.show();
    return a.exec();
}
