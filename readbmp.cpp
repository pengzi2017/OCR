#include"ReadBmp.h"

ReadBMP::ReadBMP(char *name)
{
	pBmpBuf = NULL;
	pColorTable = NULL;
	bool tab;
	tab = readBmp(name);
}
bool ReadBMP::readBmp(char *bmpName)
{
	FILE *fp;
	fopen_s(&fp, bmpName, "rb");
	if (fp == 0) {
		cout << "文件打开失败" << endl;
		return 0;
	}
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	int lineByte = (head.biWidth*head.biBitCount / 8 + 3) / 4 * 4;
	if (head.biBitCount == 8)
	{
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}
	pBmpBuf = new unsigned char[lineByte*head.biHeight];
	fread(pBmpBuf, 1, lineByte*head.biHeight, fp);
	fclose(fp);
	return 1;
}
