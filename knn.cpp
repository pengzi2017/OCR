#include "knn.h"

int knn(MatrixXf model, MatrixXf sample, int n, int div_num)
{
	int cols = model.cols();
	int rows = model.rows();
	int returnVaue;
	VectorXf distance(rows);
	for (int i = 0; i <rows; i++)
	{
		float sum = 0;
		for (int j = 0; j <cols; j++)
			sum = sum + (model(i, j) - sample(0, j))*(model(i, j) - sample(0, j));
		distance(i) = sum;
	}
	int *tabMin = new int[n];//tabMin[i]表示distance中最小值的位置；值是位置；
							 //开始排序
	VectorXf copy_dis = distance;
	for (int i = 0; i <n; i++)
	{
		int tab = 0;
		for (int j = 0; j <rows; j++)
		{
			float min = copy_dis(i);
			if (copy_dis(j) <= min&&copy_dis(j) >= 0) { min = copy_dis(j); tab = j; }
		}
		tabMin[i] = tab;
		copy_dis(tab) = -10;
	}
	cout << copy_dis << endl;
	for (int i = 0; i < n; i++)
		cout << tabMin[i] << " ";
	//统计tabMin中位置出现的最多的地方；返回函数值
	//分类
	int stat[classnum] = { 0 };
	for (int i = 0; i < n; i++)
	{
		if (tabMin[i] <= div_num)stat[0] = stat[0] + 1;
		else if (tabMin[i] <= div_num * 2)stat[1] = stat[1] + 1;
		else if (tabMin[i] <= div_num * 3)stat[2] = stat[2] + 1;
		else if (tabMin[i] <= div_num * 4)stat[3] = stat[3] + 1;
		else if (tabMin[i] <= div_num * 5)stat[4] = stat[4] + 1;
		else stat[5] = stat[5] + 1;
	}
	int max = stat[0];
	for (int i = 0; i < n; i++)
		if (max <= stat[i]) { max = stat[i]; returnVaue = i; }
	delete[] tabMin;
	return returnVaue;
}
