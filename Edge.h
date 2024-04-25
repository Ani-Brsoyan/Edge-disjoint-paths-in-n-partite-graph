#pragma once

class Vertex;

class Edge {
    public:
        Edge() = delete;
        Edge(Vertex* left, Vertex* right)
            :m_leftSide(left)
            ,m_rightSide(right)
            ,m_capacity(1)
            ,m_currFlow(0)
            {}
        Vertex* getLeftSide() const { return m_leftSide; }
        Vertex* getRightSide() const { return m_rightSide; }
        int getCapacity() const { return m_capacity; }
        void setCapacity(int cap) { m_capacity = cap; }
        int getCurrFlow() const { return m_currFlow; }
        void addCurrFlow() { m_currFlow++; }
        ~Edge();
    private:
        Vertex* m_rightSide;
        Vertex* m_leftSide;
        int m_capacity;
        int m_currFlow;
};
