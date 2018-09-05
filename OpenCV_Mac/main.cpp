#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/flann.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/ml.hpp"

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
using namespace cv::ml;

Point2f getTransformPoint(const Point2f originalPoint,const Mat &transformMaxtri)
{
    Mat originelP,targetP;
    originelP=(Mat_<double>(3,1)<<originalPoint.x,originalPoint.y,1.0);
    targetP=transformMaxtri*originelP;
    float x=targetP.at<double>(0,0)/targetP.at<double>(2,0);
    float y=targetP.at<double>(1,0)/targetP.at<double>(2,0);
    return Point2f(x,y);
}
int main(int argc,char *argv[])
{
    Mat image1 = imread(argv[4], IMREAD_COLOR);    //读取灰度图像
    Mat image2 = imread(argv[5], IMREAD_COLOR);
    
    //创建方式和2中的不一样
    Ptr<SIFT> sift = SIFT::create(800);
    vector<KeyPoint> keyPoint1,keyPoint2;
    sift->detect(image1, keyPoint1);
    sift->detect(image2, keyPoint2);
    Mat imageDesc1,imageDesc2;
    sift->compute(image1,keyPoint1,imageDesc1);
    sift->compute(image2,keyPoint2,imageDesc2);
    
    BFMatcher matcher;
    vector<DMatch> matchePoints;
    matcher.match(imageDesc1, imageDesc2, matchePoints,Mat());
    sort(matchePoints.begin(), matchePoints.end());
    
    vector<Point2f> imagePoints1,imagePoints2;
    for (int i = 0; i<10; i++) {
        imagePoints1.push_back(keyPoint1[matchePoints[i].queryIdx].pt);
        imagePoints2.push_back(keyPoint2[matchePoints[i].trainIdx].pt);
    }
    
    Mat homo = findHomography(imagePoints1, imagePoints2,CV_RANSAC);
    Mat adjustMat = (Mat_<double>(3,3)<<1.0,0,image1.cols,0,1.0,0,0,0,1.0);
    Mat adjustHomo = adjustMat * homo;
    
    Point2f originalLinkPoint,targetLinkPoint,basedImagePoint;
    originalLinkPoint = keyPoint1[matchePoints[0].queryIdx].pt;
    targetLinkPoint = getTransformPoint(originalLinkPoint, adjustHomo);
    basedImagePoint = keyPoint2[matchePoints[0].trainIdx].pt;
    
    Mat imageTransform1;
    warpPerspective(image1,imageTransform1,adjustMat*homo,Size(image2.cols+image1.cols+110,image2.rows));
    
    //在最强匹配点左侧的重叠区域进行累加，是衔接稳定过渡，消除突变
    Mat image1Overlap,image2Overlap; //图1和图2的重叠部
    
    image1Overlap=imageTransform1(Rect(Point(targetLinkPoint.x-basedImagePoint.x,0),Point(targetLinkPoint.x,image2.rows)));
    image2Overlap=image2(Rect(0,0,image1Overlap.cols,image1Overlap.rows));
    Mat image1ROICopy=image1Overlap.clone();  //复制一份图1的重叠部分
    for(int i=0;i<image1Overlap.rows;i++)
    {
        for(int j=0;j<image1Overlap.cols;j++)
        {
            double weight;
            weight=(double)j/image1Overlap.cols;  //随距离改变而改变的叠加系数
            image1Overlap.at<Vec3b>(i,j)[0]=(1-weight)*image1ROICopy.at<Vec3b>(i,j)[0]+weight*image2Overlap.at<Vec3b>(i,j)[0];
            image1Overlap.at<Vec3b>(i,j)[1]=(1-weight)*image1ROICopy.at<Vec3b>(i,j)[1]+weight*image2Overlap.at<Vec3b>(i,j)[1];
            image1Overlap.at<Vec3b>(i,j)[2]=(1-weight)*image1ROICopy.at<Vec3b>(i,j)[2]+weight*image2Overlap.at<Vec3b>(i,j)[2];
        }
    }
    
    Mat ROIMat = image2(Rect(Point(basedImagePoint.x,0),Point(image2.cols,image2.rows)));
    ROIMat.copyTo(Mat(imageTransform1,Rect(targetLinkPoint.x,0,image2.cols-basedImagePoint.x+1,image2.rows)));
    
    imshow("result", imageTransform1);

    waitKey(0);
    return 0;
}


