// CvDTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../comm/cvHead.h"

int main()
{
	//10个训练样本
	float trainingDat[10][4] = { { 1,0,0,0 },{ 1,1,0,1 },{ 0,0,1,0 },
	{ 0,1,1,1 },{ 1,0,0,0 },{ 1,0,1,1 },{ 1,1,1,1 },{ 0,1,1,0 },{ 1,1,0,1 },{ 0,0,0,1 } };
	Mat trainingDataMat(10, 4, CV_32FC1, trainingDat);

	//样本的分类结果，作为标签供训练决策树分类器
	float responses[10] = { 1,1,0,0,0,0,1,1,1,0 }; // 1代表考取，0代表不考
	Mat responsesMat(10, 1, CV_32FC1, responses);

	float priors[4] = { 1,1,1,1 };  //先验概率，这里每个特征的概率都是一样的

									//定义决策树参数
	CvDTreeParams params(15,  //决策树的最大深度
		1,   //决策树叶子节点的最小样本数
		0,   //回归精度，本例中忽略
		false,  //不使用替代分叉属性
		25,  //最大的类数量
		0,   //不需要交叉验证
		false,  //不需要使用1SE规则
		false,   //不对分支进行修剪
		priors   //先验概率
	);
	//掩码
	Mat varTypeMat(5, 1, CV_8U, Scalar::all(1));

	CvDTree tree;
	tree.train(trainingDataMat,  //训练样本
		CV_ROW_SAMPLE,  //样本矩阵的行表示样本，列表示特征
		responsesMat,   //样本的响应值矩阵
		Mat(),
		Mat(),
		varTypeMat,   //类形式的掩码
		Mat(),   //没有属性确实
		params   //决策树参数
	);
	tree.save("CvDTree.xml");
	CvMat varImportance;
	varImportance = tree.getVarImportance();
	cout << "各项所占的权重分别为：\n\n";
	string item;
	for (int i = 0; i<varImportance.cols*varImportance.rows; i++)
	{
		switch (i)
		{
		case 0:
			item = "马化腾深大毕业：";
			break;
		case 1:
			item = "深大妹子多：";
			break;
		case 2:
			item = "深圳台风多：";
			break;
		case 3:
			item = "深圳房价高：";
			break;
		default:
			break;
		}
		float value = varImportance.data.db[i];
		cout << item << value << endl << endl;
	}
	float myData[4] = { 0,1,1,0 };  //测试样本
	Mat myDataMat(4, 1, CV_32FC1, myData);
	double r = tree.predict(myDataMat, Mat(), false)->value; //获得预测结果

	if (r == (double)1.0)
	{
		cout << endl << "预测结果是： 考取深圳大学" << endl << endl;
	}
	else
	{
		cout << endl << "预测结果是： 不考取深圳大学" << endl << endl;

	}
	system("pause");
    return 0;
}

