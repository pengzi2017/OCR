#ifndef READBMP_H
#define READBMP_H
#include<iostream>
#include<stdio.h>
#include<Windows.h>
#include<fstream>
using namespace std;

class ReadBMP
{
public:
	ReadBMP(char *name);
	~ReadBMP() { delete[] pBmpBuf; delete pColorTable; };
	unsigned char *getRGBdata() { return pBmpBuf; };
	BITMAPINFOHEADER getHead() { return head; };
	long getlineByte() { return (head.biWidth*head.biBitCount / 8 + 3) / 4 * 4; }
	long getHeigth() { return getHead().biHeight; }
	RGBQUAD *getColorTable() { return pColorTable; };
private:
	unsigned char *pBmpBuf;//读入图像数据的指针  
	BITMAPINFOHEADER head;
	RGBQUAD *pColorTable;//颜色表指针
	bool readBmp(char *bmpName);

};
#endif // !READBMP_H
