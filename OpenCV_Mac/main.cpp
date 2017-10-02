#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
using namespace cv;


int main( int argc, const char** argv ){
    Mat image = imread(argv[1]);
    
    Mat element =  getStructuringElement(MORPH_RECT, Size(15,15));
    
    /*
     利用基本的膨胀和腐蚀技术，执行高级形态变化
     第三个参数是形态学运算的类型
     MORPH_OPEN 开运算
     MORPH_CLOSE 闭运算
     MORPH_GRADIENT 形态学梯度
     MORPH_TOPHAT 顶帽
     MORPH_BLACKHAT 黑帽
     MORPH_ERODE 腐蚀
     MORPH_DILATE 膨胀
     第三个参数是形态学运算内核
     为NULL是个3*3诶和，一般使用getStructuringElement获取
     常用MORPH_RECT MORPH_CROSS MORPH_ELLIPSE
     第五个参数是锚点
     第六个参数是迭代次数
     第七个参数边界模式
     第八个参数是边界为常数的边界值
     */
    
    morphologyEx(image, image, MORPH_GRADIENT, element);
    
    imshow("image", image);
    
    waitKey();
    
    return 0;
}

/*
     膨胀 求局部最大值
     腐蚀 求局部最小值
 */

