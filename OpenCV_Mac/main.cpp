#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void colorReduce(Mat& inputImage,Mat& outputImage,int div){
    double time = static_cast<double>(getTickCount());
    outputImage = inputImage.clone();
    
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();
    
    for (int i = 0; i < rowNumber; i++) {
        uchar* data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++) {
            data[j] = data[j] / div * div + div / 2;
        }
    }
    
    time = ((double)getTickCount() - time) / getTickFrequency();
    cout << time << endl;
}


void colorReduceNew(Mat& inputImage,Mat& outputImage,int div){
    double time = static_cast<double>(getTickCount());
    outputImage = inputImage.clone();
    
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();
    
    uchar table[256];
    for(int i = 0 ;i < 256;i++){
        table[i] = i / div * div  + div/2;
    }
    
    for (int i = 0; i < rowNumber; i++) {
        uchar* data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++) {
            data[j] = table[data[j]];
        }
    }
    
    time = ((double)getTickCount() - time) / getTickFrequency();
    cout << time << endl;
}

void colorReduceLUT(Mat& inputImage,Mat& outputImage,int div){
    double time = static_cast<double>(getTickCount());
    Mat lookUpTable(1,256,CV_8U);
    uchar* p = lookUpTable.data;
    for(int i = 0 ;i < 256;i++){
        p[i] = i / div * div + div /2;
    }
    // 官方推介方法
    LUT(inputImage, lookUpTable, outputImage);
    time = ((double)getTickCount() - time) / getTickFrequency();
    cout << time << endl;
}

void colorReduceIterator(Mat& inputImage,Mat& outputImage,int div){
    double time = static_cast<double>(getTickCount());
    outputImage = inputImage.clone();
    Mat_<Vec3b>:: iterator it = outputImage.begin<Vec3b>();
    Mat_<Vec3b>:: iterator itend = outputImage.end<Vec3b>();
    for (; it != itend; ++it) {
        (*it)[0] = (*it)[0] / div * div + div /2;
        (*it)[1] = (*it)[1] / div * div + div /2;
        (*it)[2] = (*it)[2] / div * div + div /2;
    }
    time = ((double)getTickCount() - time) / getTickFrequency();
    cout << time << endl;
}

void colorReduceP(Mat& inputImage,Mat& outputImage,int div){
    double time = static_cast<double>(getTickCount());
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols;
    for (int i = 0; i < rowNumber; i++) {
        for (int j = 0; j < colNumber; j++) {
            outputImage.at<Vec3b>(i,j)[0] = outputImage.at<Vec3b>(i,j)[0] / div * div + div / 2;
             outputImage.at<Vec3b>(i,j)[1] = outputImage.at<Vec3b>(i,j)[1] / div * div + div / 2;
             outputImage.at<Vec3b>(i,j)[2] = outputImage.at<Vec3b>(i,j)[2] / div * div + div / 2;
        }
    }
    time = ((double)getTickCount() - time) / getTickFrequency();
    cout << time << endl;
}

int main( int argc, const char** argv ){
    Mat input = imread(argv[1]);
    imshow("source", input);
    
    /*
         矩阵元素存储的是单通道像素，使用char类型，3通道就有一千六百万种颜色
         进行处理时会造成严重影响
         这时候需要颜色缩减 color space reduction
         将现有颜色空间除以某个输入值，获得较少的颜色数
         比如0到9取0 10到19取10
         newColor = oldColor / div * div;
         int divWith = 10;
         uchar table[256];
         for(int i = 0;i < 256;i++)
             table[i] = divWidth * (i/divWith);
         对每个元素进行乘除法比较浪费时间，可以先将256色计算后储存，之后对元素取值
     */
    Mat out;
    colorReduce(input, out, 10);
    imshow("out", input);
    
    Mat out1;
    colorReduceNew(input, out1, 10);
    imshow("out new", input);
 
    Mat out2;
    colorReduceLUT(input, out2, 10);
    imshow("out lut", input);
    
    Mat out3;
    colorReduceIterator(input, out2, 10);
    imshow("out iterator", input);
    
    Mat out4;
    colorReduceP(input, out2, 10);
    imshow("out p", input);
    
    waitKey(0);
    return 0;
}

