#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
int g_value = 10;
static void on_ValueChange(int , void *);
Mat g_srcImgae,g_dstImage;

int main( int argc, const char** argv ){
    g_srcImgae = imread(argv[1]);
    
    namedWindow("window");
    createTrackbar("value","window", &g_value, 50,on_ValueChange);
    on_ValueChange(g_value,0);
  
    while (char(waitKey(1) != 'q')) {
    }

    return 0;
}

static void on_ValueChange(int , void*){
    int size = g_value*2 + 1; // 孔径尺寸，必须是大于1的奇数
    medianBlur(g_srcImgae, g_dstImage, size);
    imshow("window", g_dstImage);
}
/*
     中值滤波
     核心思想是用像素领域灰度值的中值来替代该像素点的灰度值，该方法在去除脉冲噪声、椒盐噪声的同时又能保留图像的边缘细节
     劣势是中值滤波是均值滤波的5倍以上
 */
/*
     双边滤波
     结合图像的空间临近度和像素值相似度的一种折中处理，同事考虑空域信息和灰度相似性，达到包边去噪的目的
 */
