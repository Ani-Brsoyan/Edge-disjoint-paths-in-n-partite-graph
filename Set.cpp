#include "Set.h"
#include "Vertex.h"

#include <QDebug>
#include <QTextStream>

void Set::addVertex(Vertex*& ver)
{
    m_vertices.insert(ver);
}

void Set::printVertices() const
{
    QTextStream out(stdout);
    for (auto vertex : m_vertices)
    {
        out << vertex->getName() << ", ";
    }
    out << Qt::endl;
}

void Set::forEachVertex(std::function<void(Vertex*)> fn)
{
    for (auto vertex : m_vertices)
    {
        fn(vertex);
    }
}

void Set::forEachVertex(std::function<void(const Vertex*)> fn) const
{
    for (const auto vertex : m_vertices)
    {
        fn(vertex);
    }
}
