#include "MainWindow.h"

#include "GraphicsScene.h"

//Qt
#include <QGraphicsView>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QMenu* file = menuBar()->addMenu(tr("&File"));

    QAction* newAction = file->addAction(tr("New Game"));
    newAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    QAction* quitAction = file->addAction(tr("Quit"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    if (QApplication::arguments().contains("-fullscreen")) {
        scene = new GraphicsScene(0, 0, 750, 400,  GraphicsScene::Small, this);
        setWindowState(Qt::WindowFullScreen);
    }
    else {
        scene = new GraphicsScene(0, 0, 880, 630, GraphicsScene::Big, this);
        layout()->setSizeConstraint(QLayout::SetFixedSize);
    }

    view = new QGraphicsView(scene, this);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // scene->setupScene(newAction, quitAction);

    setCentralWidget(view);
}