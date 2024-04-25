#pragma once

#include <QVector>
#include <QString>

class Set;
class Vertex;
class GraphWidget;

class Graph {
    public:
        Graph();
        void setGW(GraphWidget* gw) { m_gw = gw; }
        GraphWidget* getGW() const { return m_gw; }
        QVector<QVector<Vertex*>> getDisjPaths() const { return m_disjointPaths; }
        void addPath (QVector<Vertex*> path);
        void addSet(Set*& set, int position = -1);
        void deleteSet(int position);
        Set* getSet(int setNumber);
        const QVector<Set*>& getSets() const { return m_sets; };
        int getGraphSize() const { return graphSize; };
        void setGraphSize(int size) { graphSize = size; };
        void printSets() const;
        void findEdgeDisjPaths();
        Vertex* containsVertex(int setNumber, QString vertexName);
        ~Graph();

    private:
        void increaseGraphSize(int addition) { graphSize += addition; };
        void decreaseGraphSize(int subtraction) { graphSize -= subtraction; }
    private:
        GraphWidget* m_gw;
        QVector<QVector<Vertex*>> m_disjointPaths;

        QVector<Set*> m_sets;
        int graphSize;
};
