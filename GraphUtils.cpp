#include "GraphUtils.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>

#include "Graph.h"
#include "Set.h"
#include "Vertex.h"
#include "Edge.h"
#include "graphwidget.h"

namespace parser
{

Graph* parseFileAndCreateGraph(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Failed to open file " << fileName;
        return nullptr;
    }

    if (file.size() == 0) {
        qDebug() << "Error: File is empty.";
        return nullptr;
    }
    QTextStream in(&file);
    QString line;

    Graph* myGraph = new Graph();
    int setCount = 0;

    while (!(line = in.readLine()).isNull()) {
        if (line == "//Edges") { // Start reading edges
            break;
        }
        if (line.isEmpty() || line.startsWith('/')) { // Skip comments
            continue;
        }
        ++setCount;

        QStringList vertexNames = line.split(' ', Qt::SkipEmptyParts);

        Set* currSet = new Set();
        float xRay = (setCount * 100) + 10;
        float yRay = 50;
        for (const QString& vertexName : vertexNames) {
            Vertex* v = new Vertex(vertexName, QPoint(xRay, yRay));
            currSet->addVertex(v);
            yRay += 80;
        }
        myGraph->addSet(currSet);
    }
    myGraph->setGraphSize(setCount);
    //myGraph->printSets();
    unsigned setNumber = 0;
    while (!(line = in.readLine()).isNull()) {
        line = line.trimmed();
        if (line.isEmpty() || line.startsWith("//")) { // Skip empty lines and comments
            continue;
        }
        if (line.startsWith("{")) {
            line = line.mid(1, line.size() - 2).trimmed(); // Remove curly braces
            QStringList edges = line.split(',', Qt::SkipEmptyParts);
            for (const QString& edge : edges) {
                QStringList vertices = edge.split('-', Qt::SkipEmptyParts); // Split the edge into left and right vertices

                if (vertices.size() != 2) {
                    qDebug() << "ERROR: Invalid edge input for set" << setNumber + 1;
                    return nullptr;
                }

                QString vertexLeft = vertices[0].trimmed();
                QString vertexRight = vertices[1].trimmed();

                Vertex* leftVer = myGraph->containsVertex(setNumber, vertexLeft);
                Vertex* rightVer = myGraph->containsVertex(setNumber + 1, vertexRight);
                if (!leftVer || !rightVer) {
                    qDebug() << "ERROR: Invalid edge input for set" << setNumber + 1;
                    return nullptr;
                }

                Edge* newEdge = new Edge(leftVer, rightVer);
                leftVer->addRightEdge(newEdge);
                rightVer->addLeftEdge(newEdge);
            }
        }
        ++setNumber;
    }

    return myGraph;
}

} // end of parser namespace

namespace graphHelper
{

void modifyGraph(Graph* g)
{
    //preparing graph for Ford-Fulkerson implementation
    addTmpSets(g);
    addTmpEdges(g);
}

void runFordFulkerson(Graph* g)
{
    int sourceNum = 0;
    Set* soucreSet = g->getSet(sourceNum);
    Vertex* source = nullptr;
    for(auto s : soucreSet->getVertices()) {
        source = s;
    }
    int sinkNum = g->getGraphSize() - 1;
    Set* sinkSet = g->getSet(sinkNum);
    Vertex* sink = nullptr;
    for(auto s : sinkSet->getVertices()) {
        sink = s;
    }
    unsigned int pathCount = 0;
    QVector <Vertex*> path{};
    while(pathExists(source, sink, path)) {
        printPath(g, path);
        ++pathCount;
        g->addPath(path);
    }
    std::cout << "Path count: " << pathCount << std::endl;
}

void getInitialGraph(Graph* g)
{
    deleteTmSets(g);
    deleteTmpEdges(g);
}

void visualizePaths(Graph* g)
{
    GraphWidget* gw = g->getGW();
    gw->setPaintPaths(true);
    gw->update();
}

} //end of graphHelper namespace

namespace
{

void addTmpSets(Graph* g)
{
    QString source = "s";
    QString sink = "t";
    int sourcePos = 0;
    //add 0th and n+1th tmp sets
    addTmpSet(g, source, sourcePos);
    addTmpSet(g, sink);
}

void addTmpSet(Graph* g, QString vertexName, int setPos)
{
    Set* tmpSet = new Set();
    Vertex* tmpVer = new Vertex(vertexName);
    tmpSet->addVertex(tmpVer);
    g->addSet(tmpSet, setPos);
}

void addTmpEdges(Graph* g)
{
    int sourceSetNum = 0;
    Set* source = g->getSet(sourceSetNum);
    Set* firstOrigSet = g->getSet(sourceSetNum + 1);
    auto fnSource = [&source](Vertex* rightVer) {
        for(auto leftVer : source->getVertices()) {
            Edge* e = new Edge(leftVer, rightVer);
            e->setCapacity(rightVer->getRightSidePower());
            leftVer->addRightEdge(e);
            rightVer->addLeftEdge(e);
        }
    };
    firstOrigSet->forEachVertex(fnSource);

    int sinkSetNum = g->getGraphSize() - 1;
    Set* sink = g->getSet(sinkSetNum);
    Set* lastOrigSet = g->getSet(sinkSetNum - 1);
    auto fnSink = [&sink](Vertex* leftVer) {
        for(auto rightVer : sink->getVertices()) {
            Edge* e = new Edge(leftVer, rightVer);
            e->setCapacity(leftVer->getLeftSidePower());
            leftVer->addRightEdge(e);
            rightVer->addLeftEdge(e);
        }
    };
    lastOrigSet->forEachVertex(fnSink);
}

bool pathExists(Vertex* s, Vertex* t, QVector<Vertex*>& path)
{
    path.clear();
    return findPathRec(s, t, path);
}

bool findPathRec(Vertex* s, Vertex* t, QVector<Vertex*>& path)
{
    if(s == t) {
        return true;
    }

    for(auto edge : s->getRightEdges()) {
        if((edge->getCapacity() - edge->getCurrFlow() > 0) && findPathRec(edge->getRightSide(), t, path)) {
            edge->getRightSide()->setPrevInfo(s);
            edge->addCurrFlow();
            path.push_back(s);
            return true;
        }
    }
    return false;
}

void printPath(Graph* g, QVector<Vertex*>& path)
{
    std::reverse(path.begin(), path.end());
    for(auto it = path.begin() + 1; it != path.end(); ++it) {
            std::cout << ((*it)->getName()).toStdString() << " ";
    }
    std::cout << std::endl;
}

void deleteTmSets(Graph* g)
{
    int sourceNum = 0;
    g->deleteSet(sourceNum);
    int sinkNum = g->getGraphSize() - 1;
    g->deleteSet(sinkNum);
}

void deleteTmpEdges(Graph* g)
{
    int firstSetNum = 0;
    Set* firstOrigSet = g->getSet(firstSetNum);
    auto fnFirst = [](Vertex* v) {
        v->clearLeftConnection();
    };
    firstOrigSet->forEachVertex(fnFirst);

    int lastSetNum = g->getGraphSize() - 1;
    Set* lastOrigSet = g->getSet(lastSetNum);
    auto fnLast = [](Vertex* v) {
        v->clearRightConnection();
    };
    lastOrigSet->forEachVertex(fnLast);
}

} //end of anonymous namespace

