#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QPushButton>

#include <opencv2/opencv.hpp>

//using namespace cv;

class GraphicsScene;

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void open();
    void close();
    void capture();
    void start();
    void update_window();

private:

    cv::VideoCapture m_cap;
    cv::Mat m_frame;

    QPushButton* m_openButton;
    QPushButton* m_closeButton;
    QPushButton* m_backgroundButton;
    QPushButton* m_startButton;
    QLabel* m_gameView;
    
    // test
    QLabel* m_captureImage;
    QLabel* m_diffImage;

    bool m_startGame = false;
    cv::Ptr<cv::BackgroundSubtractorKNN> bs;

    QPixmap* m_cameraView;
    QTimer* timer;
    QImage qt_image;
};