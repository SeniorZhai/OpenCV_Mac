#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

static void on_ContrastAmdBright(int , void *);

int g_nContentValue;//对比度
int g_nBrightVavle;
Mat g_srcImgae,g_dstImage;

int main( int argc, const char** argv ){
    g_srcImgae = imread(argv[1]);
    g_dstImage = Mat::zeros(g_srcImgae.size(),g_srcImgae.type());
    
    g_nContentValue = 100;
    g_nBrightVavle = 80;
    
    namedWindow("dst",1);
    createTrackbar("db", "dst", & g_nContentValue, 300,on_ContrastAmdBright);
    createTrackbar("ld", "dst", & g_nBrightVavle, 200, on_ContrastAmdBright);
    
    on_ContrastAmdBright(g_nBrightVavle, 0);
    
    while (char(waitKey(1) != 'q')) {
    }
    
    return 0;
}

static void on_ContrastAmdBright(int ,void *){
    namedWindow("source",1);
    for (int y = 0; y < g_srcImgae.rows; y++) {
        for (int x= 0; x < g_srcImgae.cols; x++) {
            for (int c = 0; c < 3; c++) {
                g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (g_nContentValue * 0.01) * g_srcImgae.at<Vec3b>(y,x)[c] + g_nBrightVavle);
            }
        }
    }
    imshow("source", g_srcImgae);
    imshow("dst",g_dstImage);
}

