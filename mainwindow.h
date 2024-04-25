#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Graph* , QWidget *parent = nullptr);
    ~MainWindow();

    GraphWidget* getGraphWidget() const;

private:
    Ui::MainWindow *ui;
    GraphWidget *graphWidget;
};
#endif // MAINWINDOW_H
