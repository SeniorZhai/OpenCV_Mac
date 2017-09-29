#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, const char** argv ){
    Mat image1 = imread(argv[1]);
    Mat imgae2 = imread(argv[2]);
    /*
     dst = src1 * alpha + src2 * alpha + gamma
    addWeighted(<#InputArray src1#>, <#double alpha#>, <#InputArray src2#>, double beta, <#double gamma#>, <#OutputArray dst#>)
     */
    
    Mat out;
    addWeighted(image1, 0.5, imgae2, 0.5, 1, out);
    imshow("weighted", out);
    waitKey();
    return 0;
}

