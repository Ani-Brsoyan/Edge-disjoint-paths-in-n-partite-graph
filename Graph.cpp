#include "Graph.h"

#include <iostream>

#include "Set.h"
#include "Vertex.h"
#include "GraphUtils.h"

Graph::Graph()
{}

void Graph::addPath (QVector<Vertex*> path)
{
    path.erase(path.begin());
    m_disjointPaths.push_back(path);
}

void Graph::addSet(Set*& set, const int position)
{
    increaseGraphSize(1);
    if(position > -1) {
        m_sets.insert(m_sets.begin() + position, set);
        return;
    }
    m_sets.push_back(set);
}

void Graph::deleteSet(int position)
{
    if(position > -1 && position < getGraphSize()) {
        m_sets.erase(m_sets.begin() + position);
        decreaseGraphSize(1);
    }
}

void Graph::printSets() const
{
    std::cout << std::endl;
    std::cout << "*********Set Report*********" << std::endl << std::endl;
    const QVector<Set*> sets = getSets();
    for(unsigned i = 1; auto set : sets) {
        std::cout << "set[" << i << "] ";
        set->printVertices();
        ++i;
    }
}

void Graph::findEdgeDisjPaths()
{
    graphHelper::modifyGraph(this);
    graphHelper::runFordFulkerson(this);
    graphHelper::getInitialGraph(this);
    graphHelper::visualizePaths(this);
}

Vertex* Graph::containsVertex(int setNumber, QString vertexName)
{
    Set* currentSet = getSet(setNumber);
    Vertex* tmp = nullptr;
    auto fn = [&vertexName, &tmp](const Vertex* ver){
        if(ver->getName() == vertexName) {
            tmp = const_cast<Vertex*>(ver);
            return;
        }
    };
    currentSet->forEachVertex(fn);
    return tmp;
}

Graph::~Graph()
{}

Set* Graph::getSet(int setNumber)
{
    if(setNumber < 0 || setNumber >= graphSize) {
        std::cout << "ERROR: Attempting to get invalid set." << std::endl;
        return nullptr;
    }
    return m_sets[setNumber];
}
