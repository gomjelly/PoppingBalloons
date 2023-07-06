#include "MainWindow.h"

#include <iostream>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QLayout>

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QQuickView>

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //QImage img = QImage("images/qt-logo.png").convertToFormat(QImage::Format_ARGB32);
    //QVideoSurfaceFormat format(img.size(), QVideoFrame::Format_ARGB32);
    //videoWidget = new QVideoWidget;
    //videoWidget->videoSurface()->start(format);
    //videoWidget->videoSurface()->present(img);
    //videoWidget->show();

    m_openButton = new QPushButton("open");
    m_closeButton = new QPushButton("close");
    m_backgroundButton = new QPushButton("background");
    m_startButton = new QPushButton("start");

    m_cameraLabel = new QLabel;

    QQuickView* qmlView = new QQuickView();
    qmlView->setSource(QUrl("qrc:/resource/QuickMain.qml"));
    QWidget* container = QWidget::createWindowContainer(qmlView, this);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(m_cameraLabel, 0, 0, 10, 1);
    layout->addWidget(container, 10, 0, 10, 1);
    layout->addWidget(m_openButton, 0, 1);
    layout->addWidget(m_closeButton, 1, 1);
    layout->addWidget(m_backgroundButton, 2, 1);
    layout->addWidget(m_startButton, 3, 1);
    layout->setColumnStretch(0, 1);
    layout->setRowStretch(9, 1);

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(m_openButton, SIGNAL(clicked()), this, SLOT(open()));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));

    timer = new QTimer(this);
}

void MainWindow::open()
{
    m_cap.open(0);

    if (!m_cap.isOpened())
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

void MainWindow::close()
{
    disconnect(timer, &QTimer::timeout, this, &MainWindow::update_window);
    m_cap.release();

    cv::Mat image = cv::Mat::zeros(m_frame.size(), CV_8UC3);

    qt_image = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

    m_cameraLabel->setPixmap(QPixmap::fromImage(qt_image));
    
    //m_cameraView->fromImage(qt_image);
    //view->setBackgroundBrush(qt_image);

    //m_cameraLabel->resize(m_cameraLabel->pixmap()->size());

    cout << "camera is closed" << endl;
}

void MainWindow::update_window()
{
    m_cap >> m_frame;

    cvtColor(m_frame, m_frame, cv::COLOR_BGR2RGB);

    qt_image = QImage((const unsigned char*)(m_frame.data), m_frame.cols, m_frame.rows, QImage::Format_RGB888);

    m_cameraLabel->setPixmap(QPixmap::fromImage(qt_image));
    //m_cameraView->fromImage(qt_image);
    //view->setBackgroundBrush(qt_image);

    //m_cameraLabel->resize(label->pixmap()->size());
}