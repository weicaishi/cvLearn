// CvDTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../comm/cvHead.h"

int main()
{
	//10��ѵ������
	float trainingDat[10][4] = { { 1,0,0,0 },{ 1,1,0,1 },{ 0,0,1,0 },
	{ 0,1,1,1 },{ 1,0,0,0 },{ 1,0,1,1 },{ 1,1,1,1 },{ 0,1,1,0 },{ 1,1,0,1 },{ 0,0,0,1 } };
	Mat trainingDataMat(10, 4, CV_32FC1, trainingDat);

	//�����ķ���������Ϊ��ǩ��ѵ��������������
	float responses[10] = { 1,1,0,0,0,0,1,1,1,0 }; // 1����ȡ��0������
	Mat responsesMat(10, 1, CV_32FC1, responses);

	float priors[4] = { 1,1,1,1 };  //������ʣ�����ÿ�������ĸ��ʶ���һ����

									//�������������
	CvDTreeParams params(15,  //��������������
		1,   //������Ҷ�ӽڵ����С������
		0,   //�ع龫�ȣ������к���
		false,  //��ʹ������ֲ�����
		25,  //����������
		0,   //����Ҫ������֤
		false,  //����Ҫʹ��1SE����
		false,   //���Է�֧�����޼�
		priors   //�������
	);
	//����
	Mat varTypeMat(5, 1, CV_8U, Scalar::all(1));

	CvDTree tree;
	tree.train(trainingDataMat,  //ѵ������
		CV_ROW_SAMPLE,  //����������б�ʾ�������б�ʾ����
		responsesMat,   //��������Ӧֵ����
		Mat(),
		Mat(),
		varTypeMat,   //����ʽ������
		Mat(),   //û������ȷʵ
		params   //����������
	);
	tree.save("CvDTree.xml");
	CvMat varImportance;
	varImportance = tree.getVarImportance();
	cout << "������ռ��Ȩ�طֱ�Ϊ��\n\n";
	string item;
	for (int i = 0; i<varImportance.cols*varImportance.rows; i++)
	{
		switch (i)
		{
		case 0:
			item = "��������ҵ��";
			break;
		case 1:
			item = "������Ӷࣺ";
			break;
		case 2:
			item = "����̨��ࣺ";
			break;
		case 3:
			item = "���ڷ��۸ߣ�";
			break;
		default:
			break;
		}
		float value = varImportance.data.db[i];
		cout << item << value << endl << endl;
	}
	float myData[4] = { 0,1,1,0 };  //��������
	Mat myDataMat(4, 1, CV_32FC1, myData);
	double r = tree.predict(myDataMat, Mat(), false)->value; //���Ԥ����

	if (r == (double)1.0)
	{
		cout << endl << "Ԥ�����ǣ� ��ȡ���ڴ�ѧ" << endl << endl;
	}
	else
	{
		cout << endl << "Ԥ�����ǣ� ����ȡ���ڴ�ѧ" << endl << endl;

	}
	system("pause");
    return 0;
}

