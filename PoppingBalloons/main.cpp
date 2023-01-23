#include "PoppingBalloons.h"
#include <QtWidgets/QApplication>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;



int main(int argc, char *argv[])
{
    /*Mat img = imread("resource/Lenna.png");
    imshow("img", img);*/

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        printf("Can't open the camera");
        return -1;
    }

    Mat frame;
    
    // auto bs = createBackgroundSubtractorMOG2();
    auto bs = createBackgroundSubtractorKNN();
    bs->setDetectShadows(false);
    
    int currentFrame = 0;

    while (1)
    {       
        bool re = cap.read(frame);

        if (!re) break;

        flip(frame, frame, 1);        
        
        if (currentFrame < 50)
        {
            currentFrame++;
        }
        else
        {
            Mat gray, back, fgmask;

            cvtColor(frame, gray, COLOR_BGR2GRAY);

            bs->apply(gray, fgmask);
            bs->getBackgroundImage(back);

            Mat image_labels, stats, centroids;
            int numOfLables = connectedComponentsWithStats(fgmask, image_labels, stats, centroids, 8);

            // 라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
            for (int i = 1; i < numOfLables; i++) {
                int area = stats.at<int>(i, CC_STAT_AREA);
                int left = stats.at<int>(i, CC_STAT_LEFT);
                int top = stats.at<int>(i, CC_STAT_TOP);
                int width = stats.at<int>(i, CC_STAT_WIDTH);
                int height = stats.at<int>(i, CC_STAT_HEIGHT);

                if (area < 100) continue;
                rectangle(frame, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 2);
            }
            
            cv::imshow("camera img2", back);
            cv::imshow("camera img3", fgmask);
        }

        cv::imshow("camera img1", frame);

        if (waitKey(30) == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    //QApplication a(argc, argv);
    //PoppingBalloons w;
    //w.show();
    //return a.exec();
}


int runningAverage()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        printf("Can't open the camera");
        return -1;
    }

    Mat back, frame;
    Mat fback;

    cap.read(back);
    flip(back, back, 1);
    cvtColor(back, back, COLOR_BGR2GRAY);
    GaussianBlur(back, back, Size(0, 0), 1.0);

    back.convertTo(fback, CV_32FC1);

    while (1)
    {
        cap.read(frame);
        //cap >> frame;
        flip(frame, frame, 1);
        Mat gray, diff;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(0, 0), 1.0);

        if ((gray.size().width != fback.size().width) || (gray.size().height != fback.size().height))
        {
            break;
        }
        accumulateWeighted(gray, fback, 0.02);
        fback.convertTo(back, back.type());

        // 차영상 구하기 & 이진화
        absdiff(gray, back, diff);
        threshold(diff, diff, 50, 255, THRESH_BINARY);

        Mat image_labels, stats, centroids;
        int numOfLables = connectedComponentsWithStats(diff, image_labels, stats, centroids, 8);

        // 라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
        for (int i = 1; i < numOfLables; i++) {
            int area = stats.at<int>(i, CC_STAT_AREA);
            int left = stats.at<int>(i, CC_STAT_LEFT);
            int top = stats.at<int>(i, CC_STAT_TOP);
            int width = stats.at<int>(i, CC_STAT_WIDTH);
            int height = stats.at<int>(i, CC_STAT_HEIGHT);

            if (area < 100) continue;
            rectangle(frame, Point(left, top), Point(left + width, top + height),
                Scalar(0, 0, 255), 2);

            //putText(frame, to_string(j), Point(left + 20, top + 20),
            //    FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
        }

        imshow("camera img1", frame);
        imshow("camera img2", diff);
        imshow("camera img3", back);

        if (waitKey(30) == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}