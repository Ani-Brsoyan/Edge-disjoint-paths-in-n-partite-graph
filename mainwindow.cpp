#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Graph.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(Graph* graph, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget());
    graphWidget = new GraphWidget(centralWidget());
    // Creating a button for finding edge disjoint paths
    QPushButton *button = new QPushButton("Find Paths", this);
    button->setStyleSheet("background-color: #50C878;");

    mainLayout->addWidget(graphWidget);
    mainLayout->addWidget(button, 0, Qt::AlignLeft);
    centralWidget()->setLayout(mainLayout);

    connect(button, &QPushButton::clicked, this, [graph]() {
        graph->findEdgeDisjPaths();
    });
    graph->setGW(graphWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

GraphWidget* MainWindow::getGraphWidget() const
{
    return graphWidget;
}
