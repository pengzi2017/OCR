#ifndef PCA_H
#define PCA_H
#include"Eigen/Dense"
#include<iostream>
#include<math.h>
using namespace Eigen;
using namespace std;
class Pca
{
public:
	Pca(int heighs, int widths, MatrixXf inputDatas);
	~Pca() {};
	void pca();//topNefeat是表示取前topNefeat个特征值的特征向量,将值传给eigenVector；
	MatrixXf pcaValue();
	int top;
private:
	MatrixXf inputData;//输入数据的矩阵
	MatrixXf eigenValue;//特征值；
	MatrixXf eigenVector;//特征向量；
	MatrixXf valueFace;//特征脸向量（主成分）；
	int width;
	int heigh;
};

#endif // !PCA_H
