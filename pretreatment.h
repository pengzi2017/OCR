#ifndef PRETREATMENT_H
#define PRETREATMENT_H
#include<stdio.h>
#include<iostream>
#include"ReadBmp.h"
using namespace std;
class Pretre            //预处理类
{
public:
	Pretre(long height, long width, unsigned char *fileData);
	~Pretre();
	void reversion(int L);//灰度变换-->灰度反转
	void power(int L, float a, float b);//灰度变换-->幂律变换
	void segmentation_liner(float a, float b, float c, float d, int mf, int mg);//灰度变换-->分段线性变换
	void image_balance(int grade);//直方图处理
	void filter_average(float op[7][7], int n);//滤波处理-->均值滤波
	void filter_middle(int n);//滤波处理-->中值滤波
	int *getData() { return file; };
	long getH() { return h; };
	long getW() { return w; };
	//void filter_k(int *pic, int n, int k);//滤波处理-->k值滤波
private:
	void gray(int *pic);
	int *file;
	long h;
	long w;
};

#endif 
