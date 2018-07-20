#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
 * 放射变换
 * getAffineTransform 获取放射矩阵
 * getRotationMatrix2D 根据中心点旋转、放大获取放射矩阵
 */
void warpAffineT(Mat image) {
    Mat dst1 = Mat::zeros(image.rows, image.cols, image.type());
    Mat dst2 = Mat::zeros(image.rows, image.cols, image.type());

    Point2f srcTri[3];
    srcTri[0] = Point2f(0,0);
    srcTri[1] = Point2f(image.cols,0);
    srcTri[2] = Point2f(0,image.rows);
    Point2f dstTri[3];
    dstTri[0] = Point2f(0,image.rows*0.3);
    dstTri[1] = Point2f(image.cols*0.8,0);
    dstTri[2] = Point2f(image.cols*0.1,image.rows);
    
    Mat warp_mat = getAffineTransform(srcTri,dstTri);
    warpAffine(image,dst1,warp_mat,dst1.size());
    
    Mat rot_mat = getRotationMatrix2D(Point(dst2.cols/2, dst2.rows/2), 30.0, 0.8);
    warpAffine(image, dst2, rot_mat, dst2.size());

    imshow("Affine1", dst1);
    imshow("Affine_2", dst2);
}

/*
 * 透视转换与仿射转换相似，只是多传入一个点，得到一个更完整的矩形
 */
void perspective(Mat src) {
    Mat dst1 = Mat::zeros(src.rows, src.cols, src.type());
    Point2f srcTri[4];
    srcTri[0] = Point2f(0,0);
    srcTri[1] = Point2f(src.cols,0);
    srcTri[2] = Point2f(0,src.rows);
    srcTri[3] = Point2f(src.cols,src.rows);
    Point2f dstTri[4];
    dstTri[0] = Point2f(0,src.rows*0.3);
    dstTri[1] = Point2f(src.cols*0.8,0);
    dstTri[2] = Point2f(src.cols*0.1,src.rows);
    dstTri[3] = Point2f(src.cols,src.rows*0.8);
    Mat warp_mat = getPerspectiveTransform(srcTri, dstTri);
    warpPerspective(src,dst1,warp_mat,dst1.size());
    imshow("p", dst1);
}

/*
 * threshold 固定阈值 所谓二值化是将影像进行区分，
 * 分成我们感兴趣的部分(前景)和不感兴趣的部分(背景)
 * 通常将某个强度当值分割的标准，这个强度就是threshold，
 * 强度超过这个阈值的像素当做前景，反之就是背景
 * 阈值一般分为固定阈值、自适应阈值
 */

/*
 * double threshold(InputArray src,OutArray dst,double threshold,
    double maxval,int type)
 * thresh是阈值 maxval是二值化的最大值
 * type 二值化操作形态
 *  THRESH_BINARY 超过阈值设为最大 小于设为0
 *  THRESH_BINARY_INV 超过阈值设为0 小于设为最大值
 *  THRESH_TRUNC 超过阈值设为阈值 小于设为0
 *  THRESH_TOZERO 超过阈值不变，小于设为0
 *  THRESH_TOZERO_INV 超过阈值设为0，小于不变
 */
void gray(Mat src) {
    Mat dst;
    threshold(src, dst, 75, 255, THRESH_BINARY);
    imshow("Binary", dst);
}

/*
 * 自适应阈值算法
 * Otsu流程
 *  先计算影像直方图
 *  把直方图大于阈值的像素分成一组，小于的分成另一组
 *  分别计算这两组的内变异数，并把两组内变异数相加
 *  将0~255依序当做阈值来计算组内异数和，总和值最小的就是结果阈值
 * 实际使用只需要只要threshold最后的Type或THRESH_OTSU即可
 */
void thresholdOtsu(Mat src) {
    Mat dst;
    threshold(src, dst, 150, 255, THRESH_TOZERO|THRESH_OTSU);
    imshow("thre", dst);
}

/*
 * 图像边缘是图像的重要特征，边缘通常是强度明显变化的像素点，
 * 也可以是梯度较大或极大的地方
 * 边缘检测通常有以下步骤
 * 1、平滑滤波 减少噪点
 * 2、锐化滤波 加强强度变化
 * 3、边缘判定 梯度不为零的地方
 * 4、边缘连结 将间断的边缘连结，同事去除假边缘
 * 锐化时大致相同，划分一阶微分或二阶微分，
 * 一阶微分较知名的有Prewitt算子、Sobel算子
 * 二阶微分有Laplace算子，还有Canny边缘算法，
 * 能找细致边缘的方法
 */
void edgeSobel(Mat src) {
    Mat dst;
    GaussianBlur(src, src, Size(3,3), 0, 0);
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    // ddepth 输入图的深度 x方向的微分阶数 y方向的微分阶数
    // ksize 核心 必须为 1、3、5、7
    // scale 缩放值 delta 偏移量
    Sobel(src, grad_x,  CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    // 计算输入图的各像素转成8位原图
    convertScaleAbs(grad_x, abs_grad_x);
    Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    Mat dst1,dst2;
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst1);
    threshold(dst1, dst2, 80, 255, THRESH_BINARY|THRESH_OTSU);
    
    imshow("sobel1", dst1);
    imshow("sobel2", dst2);
}

void edgeScharr(Mat src) {
    GaussianBlur(src, src, Size(3,3), 0, 0);
    Mat grad_x, grad_y;
    Mat abs_grad_x,abs_grad_y;
    Scharr(src, grad_x, CV_16S, 1, 0, 1, 0,BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    Scharr(src, grad_y, CV_16S, 0, 1, 1, 0,BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    
    Mat dst1,dst2;
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst1);
    threshold(dst1, dst2, 80, 255, THRESH_OTSU|THRESH_BINARY);
    imshow("Scharr1", dst1);
    imshow("Scharr2", dst2);
}

void edgeLaplace(Mat src) {
    GaussianBlur(src, src, Size(3,3), 0, 0);
    Mat dst1,dst2,dst3;
    Laplacian(src, dst1, CV_16S, 3, 1, 0,BORDER_DEFAULT);
    convertScaleAbs(dst1, dst2);
    
    threshold(dst2, dst3, 80, 255, THRESH_OTSU|THRESH_BINARY);
    imshow("Laplacian_2", dst2);
    imshow("Laplacian_3", dst3);
}

void edgeCanny(Mat src) {
    GaussianBlur(src, src, Size(3,3), 0, 0);
    Mat dst1, dst2;
    Canny(src, dst1, 50, 150, 3);
    threshold(dst1, dst2, 128, 255, THRESH_BINARY_INV);
    imshow("Canny_1", dst1);
    imshow("Canny_2", dst2);
}

int main( int argc, const char** argv ){
    Mat image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    
//    edgeSobel(image);
//    edgeScharr(image);
//    edgeLaplace(image);
    edgeCanny(image);
    
    waitKey();
    return 0;
}


