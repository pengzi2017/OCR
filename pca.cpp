#include"pca.h"

Pca::Pca(int heighs, int widths, MatrixXf inputDatas) :width(widths), heigh(heighs)
{
	inputData = inputDatas;
}

void Pca::pca()
{
	//求协方差矩阵的特征值和特征向量；
	MatrixXf meanVals(heigh, width);
	for (int i = 0; i <width; i++)
	{
		float average = 0;
		for (int j = 0; j < heigh; j++)average = average + inputData(j, i);
		average = average / heigh;
		for (int k = 0; k < heigh; k++)meanVals(k, i) = average;
	}
	meanVals = inputData - meanVals;
	cout << "1wnach" << endl;
	meanVals = (meanVals*meanVals.transpose()) / float(inputData.rows() - 1);
	cout << "2wnach" << endl;
	EigenSolver<MatrixXf> eig(meanVals);
	eigenValue = eig.pseudoEigenvalueMatrix();
	eigenVector = eig.pseudoEigenvectors();
	cout << eigenValue.rows() << endl;
	cout << eigenValue.cols() << endl;
	cout << eigenVector.rows() << endl;
	cout << eigenVector.cols() << endl;
	cout << "3wnach" << endl;
	//还要排序，取前topNfeat个最大的特征值；
	////////////////////////////////////////////////////////
	float sum = 0, rate = 0, sum_rate = 0;
	//int top;//表示共有最大的特征值有top个；
	for (int i = 0; i < eigenValue.rows(); i++)sum = sum + eigenValue(i, i);
	for (int i = 0; i < eigenValue.rows(); i++)
	{
		sum_rate = sum_rate + eigenValue(i, i);
		if (sum_rate / sum > 0.98) { top = i + 1; break; }
	}
	MatrixXf topVector(eigenValue.rows(), top);//取特征向量的前top列；下面是赋值
	for (int i = 0; i < eigenValue.rows(); i++)
		for (int j = 0; j < top; j++)
			topVector(i, j) = eigenVector(i, j);
	valueFace = topVector.transpose()* inputData;//得到特征脸
}

MatrixXf Pca::pcaValue()
{
	return valueFace;
}
