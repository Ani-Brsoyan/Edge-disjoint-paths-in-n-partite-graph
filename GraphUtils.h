#pragma once

#include <QString>
#include <QVector>

class Graph;
class Vertex;

namespace parser
{
    Graph* parseFileAndCreateGraph(const QString& fileName);
}

namespace graphHelper
{
    void modifyGraph(Graph*);
    void runFordFulkerson(Graph*);
    void getInitialGraph(Graph*);
    void visualizePaths(Graph*);
}

namespace
{
    void addTmpSets(Graph*);
    void addTmpSet(Graph*, QString, int = -1);
    void addTmpEdges(Graph*);

    bool pathExists(Vertex*, Vertex*, QVector<Vertex*>&);
    bool findPathRec(Vertex*, Vertex*, QVector<Vertex*>&);
    void printPath(Graph*, QVector<Vertex*>&);

    void deleteTmSets(Graph*);
    void deleteTmpEdges(Graph*);
}
