#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, const char** argv ){
    Mat image1 = imread(argv[1]);
    Mat imageROI;
    vector<Mat> channels;
    // 分离3个单通道图像
    split(image1, channels);
    
    imshow("B", channels.at(0));
    imshow("G", channels.at(1));
    imshow("R", channels.at(2));
    
    Mat out;
    merge(channels, out);
    
    imshow("out", out);
    waitKey();
    return 0;
}

