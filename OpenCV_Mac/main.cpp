#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

const int g_MaxAlphaValue = 100;
int g_AlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void *){
    g_dAlphaValue = (double) g_AlphaValueSlider / g_MaxAlphaValue;
    g_dBetaValue = 1 - g_dAlphaValue;
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0, g_dstImage);
    imshow("Image", g_dstImage);
}

int main( int argc, const char** argv ){
    g_srcImage1 = imread(argv[1]);
    g_srcImage2 = imread(argv[2]);
    g_AlphaValueSlider = 70;
    namedWindow("Image",WINDOW_AUTOSIZE);
    createTrackbar("", "Image", &g_AlphaValueSlider, g_MaxAlphaValue,on_Trackbar);
    on_Trackbar(g_AlphaValueSlider, 0);
    waitKey(0);
    return 0;
}
