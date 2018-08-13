#ifndef OPENCV_HEAD_20180813_H_
#define OPENCV_HEAD_20180813_H_

#include <iostream>
using namespace std;


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
using namespace cv;

#ifdef _DEBUG
#pragma comment(lib, "opencv_core2412d.lib")
#pragma comment(lib, "opencv_imgproc2412d.lib")
#pragma comment(lib, "opencv_highgui2412d.lib")
#pragma comment(lib, "opencv_ml2412d.lib")
#else
#pragma comment(lib, "opencv_core2412.lib")
#pragma comment(lib, "opencv_imgproc2412.lib")
#pragma comment(lib, "opencv_highgui2412.lib")
#pragma comment(lib, "opencv_ml2412.lib")
#endif // DEBUG



#endif // !OPENCV_HEAD_20180813_H_
