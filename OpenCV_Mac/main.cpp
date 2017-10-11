#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
 图像金字塔与图片尺寸缩放
 */
int main( int argc, const char** argv ){
    Mat image = imread(argv[1]);
    
    Mat tmpImage,dstImage1,dstImage2;
    tmpImage = image;
    imshow("source",image);
    // 向上采样并模糊
    pyrUp(tmpImage, dstImage1,Size(tmpImage.cols*2,tmpImage.rows*2));
    imshow("1", dstImage1);
    // 向下采样并模糊
    pyrDown(tmpImage, dstImage2,Size(tmpImage.cols/2,tmpImage.rows/2));
    imshow("2", dstImage2);
    
    waitKey();
    return 0;
}

