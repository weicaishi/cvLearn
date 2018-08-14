// entropy.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../comm/cvHead.h"

/*
from url: https://blog.csdn.net/wzz110011/article/details/78194726
��ͼ���ѹ�������о����ᵽ��Դ�صĸ��������matlabʵ��

close all;

clc;
clear all;
f = [119 123 168 119;123 119 168 168;
119 119 107 119;107 107 119 119];%��f����һ��ͼ��
p = hist(f(:),8);%��ֱ��ͼ������8�У�����ǻҶ�ͼ����ʹ��hist(f(:),256)����Ϊ�Ҷ�ͼ��256���Ҷȼ�
p = p/sum(p);
i = find(p);
h = -sum(p(i).*log2(p(i)))%������Դ��
* */

//����������
//	ע��:����ֻ��Ӧ���ܶȣ��������ֳ��ֲ�
double entropy(Mat mat){
	//����ֱ��ͼ
	cv::Mat histogram(256, 1, CV_32FC1);
	//256������Χ��0��255.
	const int histSize = 256;
	float range[] = { 0, 255 };
	const float *ranges[] = { range };
	const int channels = 0;
	cv::calcHist(&mat, 1, &channels, cv::Mat(), histogram, 1, &histSize, &ranges[0], true, false);

	//������
	float sum = 0.0;
	float *pData = reinterpret_cast<float*>(histogram.data);
	//ͳ�Ƶ����е�����
	cv::Scalar fSum = cv::sum(histogram);
	//����ÿ���Ҷ�ֵ���ֵĸ���
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
	cout << mat << endl << "�þ�����أ�" <<setw(5)<< entropy(mat) << endl;

	unsigned char data2[] = {
		119, 119, 119, 119,
		119, 107, 121, 119,
		119, 119, 119, 88,
		107, 107, 119, 119 };

	mat.data = data2;
	cout << mat << endl << "�þ�����أ�" << setw(5) << entropy(mat) << endl;

	system("pause");
    return 0;
}

