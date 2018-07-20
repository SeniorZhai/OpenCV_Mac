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

int main( int argc, const char** argv ){
    Mat image = imread(argv[1]);
    
    perspective(image);
    
    waitKey();
    return 0;
}


