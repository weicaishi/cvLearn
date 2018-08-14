// entropy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../comm/cvHead.h"

/*
from url: https://blog.csdn.net/wzz110011/article/details/78194726
在图像的压缩编码中经常提到信源熵的概念，下面用matlab实现

close all;

clc;
clear all;
f = [119 123 168 119;123 119 168 168;
119 119 107 119;107 107 119 119];%将f看做一幅图像
p = hist(f(:),8);%该直方图将会有8列，如果是灰度图像，则使用hist(f(:),256)，因为灰度图有256个灰度级
p = p/sum(p);
i = find(p);
h = -sum(p(i).*log2(p(i)))%计算信源熵
* */

//计算矩阵的熵
//	注意:该熵只反应了密度，不能体现出分布
double entropy(Mat mat){
	//计算直方图
	cv::Mat histogram(256, 1, CV_32FC1);
	//256个，范围是0，255.
	const int histSize = 256;
	float range[] = { 0, 255 };
	const float *ranges[] = { range };
	const int channels = 0;
	cv::calcHist(&mat, 1, &channels, cv::Mat(), histogram, 1, &histSize, &ranges[0], true, false);

	//计算熵
	float sum = 0.0;
	float *pData = reinterpret_cast<float*>(histogram.data);
	//统计点所有点总数
	cv::Scalar fSum = cv::sum(histogram);
	//计算每个灰度值出现的概率
	histogram = histogram / fSum[0];
	for (int i = 0; i < histogram.rows; i++) {
		if (0 == pData[i])
			continue;
		sum = sum + pData[i] * log10f(pData[i]) / log10f(2.0);
	}
	return sum;
}

int main()
{
	unsigned char data1[] = {
		119, 119, 119, 119,
		119, 107, 119, 119,
		119, 119, 119, 119,
		107, 107, 119, 119 };

	Mat mat(4, 4, CV_8UC1, data1);
	cout << mat << endl << "该矩阵的熵：" <<setw(5)<< entropy(mat) << endl;

	unsigned char data2[] = {
		119, 119, 119, 119,
		119, 107, 121, 119,
		119, 119, 119, 88,
		107, 107, 119, 119 };

	mat.data = data2;
	cout << mat << endl << "该矩阵的熵：" << setw(5) << entropy(mat) << endl;

	system("pause");
    return 0;
}

