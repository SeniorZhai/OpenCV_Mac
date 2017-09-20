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
    // 模糊
    blur(srcImage, dstImage, Size(7,7));
    imshow("dst", dstImage);
    waitKey(0);
    return 0;
}


