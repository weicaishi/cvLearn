// boost.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../comm/cvHead.h"


int main()
{
	//训练样本

	float trainingData[42][2] = { { 40, 55 },{ 35, 35 },{ 55, 15 },{ 45, 25 },{ 10, 10 },{ 15, 15 },{ 40, 10 },
		{ 30, 15 },{ 30, 50 },{ 100, 20 },{ 45, 65 },{ 20, 35 },{ 80, 20 },{ 90, 5 },
		{ 95, 35 },{ 80, 65 },{ 15, 55 },{ 25, 65 },{ 85, 35 },{ 85, 55 },{ 95, 70 },
		{ 105, 50 },{ 115, 65 },{ 110, 25 },{ 120, 45 },{ 15, 45 },
		{ 55, 30 },{ 60, 65 },{ 95, 60 },{ 25, 40 },{ 75, 45 },{ 105, 35 },{ 65, 10 },
		{ 50, 50 },{ 40, 35 },{ 70, 55 },{ 80, 30 },{ 95, 45 },{ 60, 20 },{ 70, 30 },
		{ 65, 45 },{ 85, 40 } };
	Mat trainingDataMat(42, 2, CV_32FC1, trainingData);

	//训练样本的响应值

	float responses[42] = { 'R','R','R','R','R','R','R','R','R','R','R','R','R','R','R','R',
		'R','R','R','R','R','R','R','R','R','R',
		'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B' };
	Mat responsesMat(42, 1, CV_32FC1, responses);
	float priors[2] = { 1, 1 };    //先验概率

	CvBoostParams params(CvBoost::REAL, // boost_type  
		10, // weak_count  
		0.95, // weight_trim_rate  
		15, // max_depth  
		false, // use_surrogates  
		priors // priors 
	);

	CvBoost boost;
	boost.train(trainingDataMat,
		CV_ROW_SAMPLE,
		responsesMat,
		Mat(),
		Mat(),
		Mat(),
		Mat(),
		params
	);
	//预测样本
	float myData[2] = { 55, 25 };
	Mat myDataMat(2, 1, CV_32FC1, myData);
	double r = boost.predict(myDataMat);
	cout << endl << "result:  " << (char)r << endl;




	system("pause");
    return 0;
}

