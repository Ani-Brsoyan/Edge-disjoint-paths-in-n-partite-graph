#pragma once

#include <QString>
#include <QVector>
#include <QPointF>

class Edge;

class Vertex {
    public:
        Vertex() = delete;
        Vertex(QString name, QPointF position = QPointF(0, 0))
            : m_name(name)
            , m_position(position)
            , m_prevVertexInfo(nullptr)
            {}
        QString getName() const { return m_name; }
        QPointF getPosition() const {return m_position; }
        Vertex* getPrevVertexInfo() const { return m_prevVertexInfo; }
        void setPrevInfo(Vertex* info) { m_prevVertexInfo = info; }
        QVector<Edge*>& getRightEdges() { return m_rightSide; };
        QVector<Edge*>& getLeftEdges() { return m_leftSide; };
        size_t getRightSidePower() const { return m_rightSide.size(); }
        size_t getLeftSidePower() const { return m_leftSide.size(); }
        void addRightEdge(Edge* edge) { m_rightSide.push_back(edge); }
        void addLeftEdge(Edge* edge) { m_leftSide.push_back(edge); }
        void clearRightConnection() { m_rightSide.clear(); }
        void clearLeftConnection() { m_leftSide.clear(); }
        ~Vertex();
    private:
        QString m_name;
        QPointF m_position;
        Vertex* m_prevVertexInfo;
        QVector<Edge*> m_rightSide;
        QVector<Edge*> m_leftSide;
};
