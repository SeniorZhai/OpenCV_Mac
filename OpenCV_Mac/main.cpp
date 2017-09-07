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
    
    // Mat是用于保存图像以及其矩阵数据的数据结构
    
    Mat image;
    image = imread("/Users/zhai/Downloads/avater.png",1);
    /*
     imread函数 Mat imread(const string& filename, int flags =1);
     第一个参数是文件路径
     第二个参数是图像的颜色类型
     CV_LOAD_IMAGE_UNCHANGED = -1 // 废弃
     CV_LOAD_IMAGE_GRATSCALE = 0 // 灰度
     CV_LOAD_IMAGE_COLOR = 1 // default
     CV_LOAD_IMAGE_ANYDEPTH = 2 若载入的图像深度为16或32位，返回对应图像，否则转换成8位返回
     CV_LOAD_IMAGE_ANYCOLOR = 4
     flags > 0返回3通道彩色图像
     flags = 0返回灰度图像
     flags < 0返回包含Alpha通道的图像
     */
    namedWindow("Display Image",WINDOW_AUTOSIZE);
    /*
     void nameWindow(const string& winname,int flags=WINDOW_AUTOSIZE);
     flags   WINDOW_NORMAL可改变大小
     WINDOW_AUTOSIZE适应图像大小
     WINDOW_OPENGL支持OpenGL
     destroyWindow()或者destroyAllWindows()函数可以关闭窗口
     */
    imshow("Display Image", image);
    /*
     void imshow(const string& winname,InputArray mat);
     显示图像
     */
    /*
     bool imwrite(const string& filename,InputArray img,const vector<int>& params = vector<int>());
     输出图像到文件
     第三个参数是采参数编码
     对于JPEG格式，参数是0到100的图片质量(CV_IMWRITE_JPEG_QUALITY)，默认值是95
     对于PNG，参数是压缩等级0到9(CV_IMWRITE_PNG_COMPRESSION)，默认是3
     对于PPM、PGM、PBM表示0或1的二进制标志(CV_IMWRITE_PXM_BINARY)
     */
    // 注意作为logo需要alpha通道
    Mat logo = imread("/Users/zhai/Downloads/logo.jpg",3);
    namedWindow("Logo Image",WINDOW_AUTOSIZE);
    

    Mat imgROI = image(Rect(10,10,logo.cols,logo.rows));

    // 叠加 掩膜 必须是灰度图
    Mat mask = imread("/Users/zhai/Downloads/logo.jpg",0);
    logo.copyTo(imgROI,mask);
    
    imshow("Log Image", image);
    waitKey(0);
    return 0;
}
