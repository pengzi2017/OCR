#include<iostream>
#include"ReadBmp.h"
#include"Eigen/Dense"
#include<Windows.h>
#include"pca.h"
#include"pretreatment.h"
#include<iomanip>
#include"knn.h"
#include<fstream>
#include<io.h>
using namespace Eigen;
using namespace std;
char *join(char *a, char *b) {
	char *c = (char *)malloc(strlen(a) + strlen(b) + 1);
	if (c == NULL) exit(1);
	char *tempc = c;
	while (*a != '\0') {
		*c++ = *a++;
	}
	while ((*c++ = *b++) != '\0') {
		;
	}
	return tempc;
}
void main()
{
	//将样本集的数据输入    //输入文件夹路径  
	long lf, lfmy;
	int height = 0, width = 0;   //height是图片数量，width是图片像素长和宽的乘积；
	_finddata_t file;
	char *str = "e:\\algoMatch\\标准素材\\头像_112_92\\";
	if ((lf = _findfirst("e:\\algoMatch\\标准素材\\头像_112_92\\*.*", &file)) == -1)  //       d:\\OSG\\Data\\*.*
		cout << "Not Found!" << endl;
	else {
		_findnext(lf, &file);
		while (_findnext(lf, &file) == 0)
		{
			width++;        //cout << file.name << endl
			if (width == 1)
			{
				char *filename = join(str, file.name);
				ReadBMP readPic(filename);
				Pretre ceshi(readPic.getHeigth(), readPic.getlineByte(), readPic.getRGBdata());
				height = ceshi.getH()*ceshi.getW();
			}
		}
	}
	_findclose(lf);
	cout << "图片数量统计完成！" << endl;
	cout << height << endl;
	cout << width << endl;
	///////////////////////////////////////////////////////////
	MatrixXf inputData(height, width);
	int tab = 0;
	//_finddata_t file;
	if ((lfmy = _findfirst("e:\\algoMatch\\标准素材\\头像_112_92\\*.*", &file)) == -1)  //       d:\\OSG\\Data\\*.*
		cout << "Not Found!" << endl;
	else {
		_findnext(lfmy, &file);
		while (_findnext(lfmy, &file) == 0)
		{    //cout << file.name << endl
			char *filename = join(str, file.name);
			ReadBMP readPic(filename);
			Pretre ceshi(readPic.getHeigth(), readPic.getlineByte(), readPic.getRGBdata());
			int *data = ceshi.getData();
			for (int i = 0; i <height; i++)
			{
				inputData(i, tab) = data[i];
			}
			tab++;
		}
	}
	_findclose(lfmy);
	cout << "图片数据读人完成！" << endl;
	//	cout << tab << endl;
	//	for (int i = 0; i <height; i++)
	//	{
	//		for(int j=0;j< width;j++)
	//			cout << inputData(i,j)<< " ";
	//		cout << endl;
	//	}
	///////////////////////////////////////////////////////
	//开始计算主成分，并且将数值输入到test.txt文件中；

	Pca pca(height, width, inputData);
	pca.pca();
	cout << "主成分计算完成！" << endl;
	MatrixXf pcaValues = pca.pcaValue();
	FILE *fp;
	fopen_s(&fp, "test.txt", "w");
	if (!fp)
	{
		perror("cannot open file");
		//exit(-1);
	}
	//	把二维数组的内容写入文件

	for (int i = 0; i <pca.top; i++)
	{
		for (int j = 0; j <width; j++)
		{
			fprintf(fp, "%f ", float(pcaValues(i, j)));
		}
		fputc('\n', fp);
	}
	fclose(fp);
	cout << "数据写入完成！" << endl;

	system("pause");
}
