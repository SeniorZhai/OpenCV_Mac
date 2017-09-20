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

    Mat srcImage = imread("/Users/zhai/Downloads/avater.png");
    imshow("Source",srcImage);
    Mat element = getStructuringElement(MORPH_RECT, Size(15,15));
    Mat dstImage;
    // 腐蚀
    erode(srcImage, dstImage, element);
    imshow("dst", dstImage);
    waitKey(0);
    return 0;
}


