//
//  main.cpp
//  OpenCV_Mac
//
//  Created by zhai on 2017/9/7.
//  Copyright © 2017年 zhai. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>

using namespace cv;

int main(int argc, const char * argv[]) {

    Mat srcImage = imread("/Users/zhai/Downloads/avater.png");
    imshow("Source",srcImage);
    Mat dstImage;
    dstImage.create(srcImage.size(), srcImage.type());
    Mat grayImage;
    cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
    Mat edge;
    blur(grayImage, edge, Size(3,3));
    Canny(edge, edge, 3, 9, 3);
    imshow("Canny",edge);
    waitKey(0);
    return 0;
}


