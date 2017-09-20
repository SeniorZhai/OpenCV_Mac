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

    VideoCapture capture("/Users/zhai/Desktop/25.mp4");
    /*
     VideoCapture capture;
     capture.open("");
     **/
    while(1){
        Mat frame;
        // 取当前帧
        capture>>frame;
        imshow("video", frame);
        waitKey(20);
    }
    return 0;
}


