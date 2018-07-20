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

int main( int argc, const char** argv ){
    Mat image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    
    thresholdOtsu(image);
    
    waitKey();
    return 0;
}


