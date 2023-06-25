#include "MainWindow.h"

#include "GraphicsScene.h"
#include "PixmapItem.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QLayout>

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>

using namespace std;


// https://webnautes.tistory.com/1517
//
//MainWindow::MainWindow(QWidget* parent)
//    : QMainWindow(parent)
//{
//    QMenu* file = menuBar()->addMenu(tr("&File"));
//
//    QAction* newAction = file->addAction(tr("New Game"));
//    newAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
//    QAction* quitAction = file->addAction(tr("Quit"));
//    quitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
//
//    if (QApplication::arguments().contains("-fullscreen")) {
//        scene = new GraphicsScene(0, 0, 750, 400,  GraphicsScene::Small, this);
//        setWindowState(Qt::WindowFullScreen);
//    }
//    else {
//        scene = new GraphicsScene(0, 0, 880, 630, GraphicsScene::Big, this);
//        layout()->setSizeConstraint(QLayout::SetFixedSize);
//    }
//
//    view = new QGraphicsView(scene, this);
//    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
//    // scene->setupScene(newAction, quitAction);
//
//    setCentralWidget(view);
//}

//class MainWindow : public QMainWindow
//{
//public:
//    MainWindow(QWidget* parent = 0);
//
//private slots:
//
//    void Open();
//    void Close();
//    void update_window();
//
//private:
//
//    QTimer* timer;
//    VideoCapture cap;
//
//    Mat frame;
//    QImage qt_image;
//    QLabel* label;
//    QPushButton* openBtn;
//    QPushButton* closeBtn;
//};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QWidget* qwidget = new QWidget(this);

    auto* vbox = new QVBoxLayout(this);
    auto* hbox = new QHBoxLayout();

    openBtn = new QPushButton("Open", this);
    closeBtn = new QPushButton("Close", this);

    hbox->addWidget(openBtn, 1, Qt::AlignRight);
    hbox->addWidget(closeBtn, 0);

    label = new QLabel(this);

    //

    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 600, 600);
    //! [1] //! [2]
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    //! [2]

    for (int i = 0; i < 3; ++i) {
        QGraphicsPixmapItem* mouse = new QGraphicsPixmapItem(QPixmap(":/resource/gfx/shooter.png"));

        mouse->setPos(::sin((i * 6.28) / 3) * 200,
            ::cos((i * 6.28) / 3) * 200);
        mouse->setZValue(3);
        scene.addItem(mouse);
    }
    
    //! [4]
    //! 
    //m_cameraView = new QPixmap();
    view = new QGraphicsView(&scene, label);
    //view->setRenderHint(QPainter::Antialiasing);
    //view->setBackgroundBrush(*m_cameraView);
    //! [4] //! [5]
    //view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);
    //! [5] //! [6]
    //view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    //view->resize(600, 600);
    //view->show();

    //

    vbox->addWidget(view);
    //vbox->addWidget(label);
    vbox->addStretch(1);

    vbox->addLayout(hbox);
    qwidget->setLayout(vbox);
    setCentralWidget(qwidget);

    connect(openBtn, &QPushButton::clicked, this, &MainWindow::Open);
    connect(closeBtn, &QPushButton::clicked, this, &MainWindow::Close);

    timer = new QTimer(this);
}


void MainWindow::Open()
{
    cap.open(0);

    if (!cap.isOpened())
    {
        cout << "camera is not open" << endl;
    }
    else
    {
        cout << "camera is open" << endl;

        connect(timer, &QTimer::timeout, this, &MainWindow::update_window);
        timer->start(30);
    }
}

void MainWindow::Close()
{
    disconnect(timer, &QTimer::timeout, this, &MainWindow::update_window);
    cap.release();

    Mat image = Mat::zeros(frame.size(), CV_8UC3);

    qt_image = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

    label->setPixmap(QPixmap::fromImage(qt_image));
    
    //m_cameraView->fromImage(qt_image);
    //view->setBackgroundBrush(qt_image);

    label->resize(label->pixmap()->size());

    cout << "camera is closed" << endl;
}

void MainWindow::update_window()
{
    cap >> frame;

    cvtColor(frame, frame, COLOR_BGR2RGB);

    qt_image = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

    label->setPixmap(QPixmap::fromImage(qt_image));
    //m_cameraView->fromImage(qt_image);
    //view->setBackgroundBrush(qt_image);

    label->resize(label->pixmap()->size());
}