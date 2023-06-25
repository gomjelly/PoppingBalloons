#include "MainWindow.h"

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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //QImage img = QImage("images/qt-logo.png").convertToFormat(QImage::Format_ARGB32);
    //QVideoSurfaceFormat format(img.size(), QVideoFrame::Format_ARGB32);
    //videoWidget = new QVideoWidget;
    //videoWidget->videoSurface()->start(format);
    //videoWidget->videoSurface()->present(img);
    //videoWidget->show();

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