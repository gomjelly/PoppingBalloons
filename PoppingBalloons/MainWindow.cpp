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
//#include <QQuickView>

using namespace std;

#define IMAGE_WIDTH 1920 / 4 
#define IMAGE_HEIGHT 1080 / 4
#define TIMAGE_WIDTH 1920 / 8 
#define TIMAGE_HEIGHT 1080 / 8 
#define RESIZE_RATIO 4

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //QImage img = QImage("images/qt-logo.png").convertToFormat(QImage::Format_ARGB32);
    //QVideoSurfaceFormat format(img.size(), QVideoFrame::Format_ARGB32);
    //videoWidget = new QVideoWidget;
    //videoWidget->videoSurface()->start(format);
    //videoWidget->videoSurface()->present(img);
    //videoWidget->show();

    m_openButton = new QPushButton("Connect camera");
    m_closeButton = new QPushButton("Disconnect camera");
    m_backgroundButton = new QPushButton("Capture background");
    m_startButton = new QPushButton("Start game");

    m_gameView = new QLabel;    
    m_gameView->setMinimumSize(IMAGE_WIDTH, IMAGE_HEIGHT);

    m_captureImage = new QLabel;
    m_captureImage->setMinimumSize(TIMAGE_WIDTH, TIMAGE_HEIGHT);

    m_diffImage = new QLabel;
    m_diffImage->setMinimumSize(TIMAGE_WIDTH, TIMAGE_HEIGHT);

    m_gameView->setScaledContents(true);
    m_captureImage->setScaledContents(true);
    m_diffImage->setScaledContents(true);

    //QQuickView* qmlView = new QQuickView();
    //qmlView->setSource(QUrl("qrc:/resource/QuickMain.qml"));
    //QWidget* container = QWidget::createWindowContainer(qmlView, this);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(m_gameView, 0, 0, 10, 2);
    layout->addWidget(m_openButton, 0, 2);
    layout->addWidget(m_closeButton, 1, 2);
    layout->addWidget(m_backgroundButton, 2, 2);
    layout->addWidget(m_startButton, 3, 2);
    layout->addWidget(m_captureImage, 10, 0);
    layout->addWidget(m_diffImage, 10, 1);
    layout->setColumnStretch(0, 2);
    layout->setRowStretch(9, 2);
    //layout->addWidget(container, 10, 0, 10, 1);

    m_backgroundButton->setEnabled(false);
    m_startButton->setEnabled(false);

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(m_openButton, SIGNAL(clicked()), this, SLOT(open()));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_backgroundButton, SIGNAL(clicked()), this, SLOT(capture()));
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(start()));

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

        m_backgroundButton->setEnabled(true);
        m_startButton->setEnabled(true);
    }
}

void MainWindow::close()
{
    disconnect(timer, &QTimer::timeout, this, &MainWindow::update_window);
    m_cap.release();

    cv::Mat image = cv::Mat::zeros(m_frame.size(), CV_8UC3);

    qt_image = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

    m_gameView->setPixmap(QPixmap::fromImage(qt_image));
    
    //m_cameraView->fromImage(qt_image);
    //view->setBackgroundBrush(qt_image);

    //m_cameraLabel->resize(m_cameraLabel->pixmap()->size());

    m_backgroundButton->setEnabled(false);
    m_startButton->setEnabled(false);

    cout << "camera is closed" << endl;
}

void MainWindow::update_window()
{
    m_cap >> m_frame;

    cv::flip(m_frame, m_frame, 1);
    
    cvtColor(m_frame, m_frame, cv::COLOR_BGR2RGB);    

    if (!m_startGame)
    {
        qt_image = QImage((const unsigned char*)(m_frame.data), m_frame.cols, m_frame.rows, QImage::Format_RGB888);
        m_gameView->setPixmap(QPixmap::fromImage(qt_image));
    }
    else
    {
        //////
        cv::Mat frame;
        cv::resize(m_frame, frame, cv::Size(m_frame.cols / RESIZE_RATIO, m_frame.rows / RESIZE_RATIO));
        cv::Mat gray, back, fgmask;

        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        
        m_backgroundSubtractor->apply(gray, fgmask);
        //m_backgroundSubtractor->getBackgroundImage(back);

        //cv::Mat image_labels, stats, centroids;
        //int numOfLables = connectedComponentsWithStats(fgmask, image_labels, stats, centroids, 8);

        //// 라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
        //for (int i = 1; i < numOfLables; i++) {
        //    int area = stats.at<int>(i, cv::CC_STAT_AREA);
        //    int left = stats.at<int>(i, cv::CC_STAT_LEFT);
        //    int top = stats.at<int>(i, cv::CC_STAT_TOP);
        //    int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        //    int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);

        //    if (area < 10) continue;
        //    cv::rectangle(frame, cv::Point(left, top), cv::Point(left + width, top + height), cv::Scalar(0, 0, 255), 2);
        //}

        //cv::imshow("camera back", back);
        //cv::imshow("camera fgmask", fgmask);
        //cv::imshow("camera frame", frame);
        auto kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
        cv::morphologyEx(fgmask, fgmask, cv::MORPH_DILATE, kernel);        
        cv::morphologyEx(fgmask, fgmask, cv::MORPH_ERODE, kernel);
        cv::morphologyEx(fgmask, fgmask, cv::MORPH_ERODE, kernel);

        m_diffImage->setPixmap(QPixmap::fromImage(QImage((const unsigned char*)(fgmask.data), fgmask.cols, fgmask.rows, QImage::Format_Grayscale8)));

        cv::resize(fgmask, fgmask, cv::Size(m_frame.cols, m_frame.rows));

        cvtColor(fgmask, fgmask, cv::COLOR_GRAY2RGB);

        m_frame = fgmask + m_frame;

        qt_image = QImage((const unsigned char*)(m_frame.data), m_frame.cols, m_frame.rows, QImage::Format_RGB888);        
        m_gameView->setPixmap(QPixmap::fromImage(qt_image));                
    }   
}

void MainWindow::capture()
{
    m_cap.set(cv::CAP_PROP_AUTOFOCUS, 1);
    m_cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 1);

    m_cap >> m_frame;

    cv::flip(m_frame, m_frame, 1);

    cv::Mat captureFrame;

    cv::resize(m_frame, captureFrame, cv::Size(m_frame.cols / RESIZE_RATIO, m_frame.rows / RESIZE_RATIO));

    cv::cvtColor(captureFrame, captureFrame, cv::COLOR_BGR2RGB);

    qt_image = QImage((const unsigned char*)(captureFrame.data), captureFrame.cols, captureFrame.rows, QImage::Format_RGB888);

    m_captureImage->setPixmap(QPixmap::fromImage(qt_image));    
}

void MainWindow::start()
{
    m_startGame = true;

    //if (m_backgroundSubtractor) m_backgroundSubtractor->clear();

    m_backgroundSubtractor = cv::createBackgroundSubtractorKNN();
    m_backgroundSubtractor->setDetectShadows(false);
}