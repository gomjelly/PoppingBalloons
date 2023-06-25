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
    void Open();
    void Close();
    void update_window();

private:

    //GraphicsScene* scene;
    //QGraphicsView* view;
    VideoCapture cap;
    Mat frame;

    QGraphicsView* view;

    QPushButton* openBtn;
    QPushButton* closeBtn;
    QLabel* label;
    QPixmap* m_cameraView;
    QTimer* timer;
    QImage qt_image;
};