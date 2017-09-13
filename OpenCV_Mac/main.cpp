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
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

Mat src;
Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int,void*);

int main(int argc, const char * argv[]) {
    src = imread("/Users/zhai/Downloads/avater.png",1);
    // 灰度
    cvtColor(src, src_gray, CV_BGR2GRAY );
    // 模糊
    blur(src_gray, src_gray, Size(3,3));
    
    namedWindow("Source",CV_WINDOW_AUTOSIZE);
    imshow("Source", src);
    
    // 创建滑竿
    createTrackbar("Canny", "Source", &thresh, max_thresh,thresh_callback);
    thresh_callback(0,0);
    
    waitKey(0);
    return 0;
}

void thresh_callback(int,void*){
    Mat canny_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Canny(src_gray, canny_output, thresh, thresh*2,3);
    /**
        void findContours(InputOutputArray image,OutputArrayOfArrays contours,int mode, int method,Point offset = Point());
        void findContours(InputOutputArray image,OutputArrayOfArrays contours,OutputArray hierarchy,int mode,int method,Point offset = Point());
        contours是找到的轮廓
        mode CV_RETR_EXTERNAL 找到的轮廓里面没有小轮廓 CV_RETR_LIST找到的轮廓可以包括小轮廓
        hierarchy 层次结构，存放轮廓统一登记的前后轮廓的索引
        method CV_CHAIN_APPROX_NONE获取轮廓所有像素点
      */
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    Mat drawing = Mat::zeros(canny_output.size(), CV_8SC3);
    for(int i = 0;i<contours.size();i++){
        Scalar color = Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
        drawContours(drawing, contours, i, color,2,8,hierarchy,0,Point());
    }
    namedWindow("Contours",CV_WINDOW_AUTOSIZE);
    imshow("Contours", drawing);
}


