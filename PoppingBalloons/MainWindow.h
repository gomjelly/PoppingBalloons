#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QPushButton>

#include <opencv2/opencv.hpp>

using namespace cv;

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
    void update_window();

private:

    VideoCapture m_cap;
    Mat m_frame;

    QPushButton* m_openButton;
    QPushButton* m_closeButton;
    QPushButton* m_backgroundButton;
    QPushButton* m_startButton;
    QLabel* m_cameraLabel;

    QPixmap* m_cameraView;
    QTimer* timer;
    QImage qt_image;
};