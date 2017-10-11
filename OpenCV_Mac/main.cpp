#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

/*
 图像金字塔与图片尺寸缩放
 */
int main( int argc, const char** argv ){
    Mat image = imread(argv[1]);
    
    Mat tmpImage,dstImage1,dstImage2;
    tmpImage = image;
    imshow("source",image);
    
    /* 第四个参数值沿水平轴的缩放系数 第五个参数是沿垂直轴的缩放系数
       第六个参数是插值方式
         INTER_NEAREST 最近邻插值
         INTER_LINEAR 线性插值
         INTER_AREA 区域插值
         INTER_CUBIC 三次样条插值
         INTER_LANCZOS4 Lanczos插值
    */
    resize(tmpImage, dstImage1, Size(tmpImage.cols/2,tmpImage.rows/2),(0,0),(0,0),INTER_LANCZOS4);
    resize(tmpImage, dstImage2, Size(tmpImage.cols/3,tmpImage.rows/3));
    
    imshow("1", dstImage1);
    imshow("2", dstImage2);
    waitKey();
    return 0;
}

