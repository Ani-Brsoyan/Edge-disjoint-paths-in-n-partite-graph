#pragma once

#include <functional>
#include <QSet>

class Vertex;

class Set {
public:
    Set() {}
    void addVertex(Vertex*& ver);
    void printVertices() const;
    QSet<Vertex*>& getVertices() { return m_vertices; };
    void forEachVertex(std::function<void(Vertex*)> fn);
    void forEachVertex(std::function<void(const Vertex*)> fn) const;

private:
    QSet<Vertex*> m_vertices;
};
