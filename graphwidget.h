#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>

#include "Graph.h"

class Vertex;

class GraphWidget : public QWidget
{
    Q_OBJECT
    public:
        GraphWidget(QWidget *parent = nullptr);

        // Method to set the graph data
        void setGraph(Graph*& graph);
        void setPaintPaths(bool value) { m_paintPaths = value; }

    protected:
        // Override paintEvent to perform custom painting
        void paintEvent(QPaintEvent *event) override;

    private:
        Graph* m_graph;
        bool m_paintPaths;
};

#endif // GRAPHWIDGET_H
