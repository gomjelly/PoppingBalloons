#include "PoppingBalloons.h"
#include <QtWidgets/QApplication>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
    Mat img = imread("resource/Lenna.png");

    imshow("img", img);
    waitKey(0);

    QApplication a(argc, argv);
    PoppingBalloons w;
    w.show();
    return a.exec();
}
