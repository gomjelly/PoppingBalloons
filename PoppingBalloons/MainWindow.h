#pragma once
#include <QMainWindow>

class GraphicsScene;

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:

    GraphicsScene* scene;
    QGraphicsView* view;
};