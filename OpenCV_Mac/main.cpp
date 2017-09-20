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
    while(1){
        Mat frame;
        // 取当前帧
        capture>>frame;
        imshow("camera", frame);
        waitKey(20);
    }
    return 0;
}


