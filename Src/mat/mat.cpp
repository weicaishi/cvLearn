// mat.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../comm/cvHead.h"


int main()
{
	Mat  img=imread(MAT_IMG_FILENAME, IMREAD_COLOR);
	imshow("mat", img);

	Mat block = img(Rect(120, 120, 160, 160));
	imshow("block", block);
	cv::waitKey(0);
	cv::destroyAllWindows();
    return 0;
}

