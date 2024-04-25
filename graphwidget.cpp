#include "graphwidget.h"

#include "Set.h"
#include "Vertex.h"
#include "Edge.h"

#include <QPainter>
#include <QDebug>
#include <iostream>

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
    , m_graph(nullptr)
    , m_paintPaths(false)
{}

void GraphWidget::setGraph(Graph*& graph)
{
    m_graph = graph;
    update(); // Trigger widget repaint
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (!m_graph)
        return;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    // Clear the canvas
    painter.fillRect(rect(), Qt::white);
    // Draw vertices
    for (const auto& set : m_graph->getSets()) {
        for (const auto& vertex : set->getVertices()) {
            //paint vertices
            painter.setBrush(Qt::blue);
            painter.drawEllipse(vertex->getPosition(), 20, 20);
            QString vertexName = vertex->getName();
            QPointF textPosition(vertex->getPosition().x() - 20, vertex->getPosition().y() - 24);
            painter.drawText(textPosition, vertexName);
            //paint edges
            painter.setPen(QPen(Qt::blue, 2));
            for(const auto& edge : vertex->getRightEdges()) {
                painter.drawLine(edge->getLeftSide()->getPosition(), edge->getRightSide()->getPosition());
            }
        }
    }
    if(m_paintPaths) {
        for(auto path : m_graph->getDisjPaths()) {
            QVector<QPointF> points;
            for(auto point : path) {
                points.append(point->getPosition());
            }
            painter.setPen(QPen(Qt::red, 3));
            painter.drawPolyline(points.data(), points.size());
        }
    }
}
