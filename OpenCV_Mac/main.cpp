//
//  main.cpp
//  OpenCV_Mac
//
//  Created by zhai on 2017/9/7.
//  Copyright © 2017年 zhai. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[]) {
    // 调用摄像头
    VideoCapture capture(0);
    /*
     VideoCapture capture;
     capture.open(0);
     **/
    Mat edges;
    while(1){
        Mat frame;
        // 取当前帧
        capture>>frame;
        cvtColor(frame, edges, CV_BGR2GRAY);
        blur(edges, edges, Size(7,7));
        Canny(edges, edges, 0, 30,3);
        imshow("camera", edges);
        if(waitKey(20)>=0)break;
    }
    return 0;
}


