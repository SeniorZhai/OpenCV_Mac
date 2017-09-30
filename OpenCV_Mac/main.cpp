#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
int g_value = 10;
static void on_ValueChange(int , void *);
Mat g_srcImgae,g_dstImage;

int main( int argc, const char** argv ){
    g_srcImgae = imread(argv[1]);
    
    namedWindow("window");
    createTrackbar("value","window", &g_value, 10,on_ValueChange);
    on_ValueChange(g_value,0);
  
    while (char(waitKey(1) != 'q')) {
    }

    return 0;
}

static void on_ValueChange(int , void*){
    int size = g_value * 2 +1;
    boxFilter(g_srcImgae, g_dstImage, -1, Size(size,size));
    imshow("window", g_dstImage);
}

/*
 方框滤波
 void boxFilter(IntputArray src,OutputArray dst,int ddepth,Size ksize,Point anchor = Point(-1,-1),boolnormalize = true,int borderType=BORDER_DEFAULT);
 输入 输出 深度 -1使用源图深度 内核大小 内核锚点 默认是中心点 是否归一化 边界模式一般忽略
 */

/*
 均值滤波
 主要方法是领域平均法，即用一片区域的各个像素的均值来代替原图像中的各个像素值
 缺陷是不能很好的祛除噪点
 open cv中的blur函数封装的就是均值滤波
 void blur(IntputArray src,OutputArray dst,Size ksize,Point anchor=Point(-,-1),int borderType=BORDER_DEFAULT)
 输入 输出 内核大小 内核锚点 边缘模式
 */

/*
 高斯滤波是一种线性平滑滤波，可以消除高斯噪声
 高斯滤波是堆整幅图像进行加权平均的过程，每个像素的值都是由本身和领域内其他像素加权平均后得到
 高斯滤波的具体操作就是用一个模板扫描图像中的每一个像素用模板确定的领域内像素加权平均灰度去替代模板中心像素点的值
 */

