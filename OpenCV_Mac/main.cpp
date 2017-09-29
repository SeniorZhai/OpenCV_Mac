#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, const char** argv ){
    Mat image = imread(argv[1]);
    Mat logo = imread(argv[3]);
    
    // ROI region of interest
    // 起点0，0 logo大小的区域
    // Mat roi = image(Rect(100,100,logo.cols,logo.rows));
    Mat roi = image(Range(100,100+logo.cols),Range(100,100+logo.rows));
    
    // 遮板 必须是灰度图
    Mat mask = imread(argv[3],0);
    
    logo.copyTo(roi,mask);
    
    imshow("roi", image);
    waitKey(0);
    
    return 0;
}

