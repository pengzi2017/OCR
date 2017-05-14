#include "pretreatment.h"
Pretre::Pretre(long height, long width, unsigned char *fileData)
{
	long widths = width;
	if (width % 3 != 0)widths = width - width % 3;
	w = widths / 3;
	h = height;
	int *files = new int[widths*height];
	int ptr = 0;
	for (int i = 0; i<height; i++)
		for (int j = 0; j <widths; j++)
		{
			if ((i*widths + j + 1) % w == 0 && (i != 0 || j != 0))ptr = i*w + j + (width % 3) + 1;
			else ptr = i*widths + j;
			files[i*widths + j] = fileData[ptr];
		}
	file = new int[h*w];
	gray(files);
	delete files;
}

Pretre::~Pretre()
{
	delete file;
}

void Pretre::gray(int *pic)
{
	for (int i = 0; i < h*w; i++)
	{
		file[i] = (pic[i * 3] + pic[i * 3 + 1] + pic[i * 3 + 2]) / 3;
	}
}

void Pretre::reversion(int L)
{
	for (int i = 0; i < h*w; i++)
	{
		file[i] = L - 1 - file[i];
	}
}

void Pretre::power(int L, float a, float b)
{
	for (int i = 0; i < h*w; i++)
	{
		file[i] = int(a*pow(file[i] / (L - 1), b));
	}
}

void Pretre::segmentation_liner(float a, float b, float c, float d, int mf, int mg)
{
	for (int i = 0; i < h*w; i++)
	{
		if (file[i] >= 0 && file[i] <= a - 1)file[i] = int(c*file[i] / a);
		else if (file[i] >= a&&file[i] <= b - 1)file[i] = int((d - c) / (b - a)*(file[i] - a) + c);
		else
			file[i] = int((mg - d) / (mf - b)*(file[i] - b) + d);
	}
}

void Pretre::image_balance(int grade)
{
	float p, q[256];
	int hd[256] = { 256 * 0 };
	for (int i = 0; i < h*w; i++)hd[file[i]]++;
	q[0] = (float)hd[0] / (h*w);
	for (int i = 1; i <256; i++)
	{
		p = (float)hd[i] / (h*w);
		q[i] = q[i - 1] + p;
	}
	for (int i = 0; i < h*w; i++)
		file[i] = int(q[file[i]] * (grade - 1));
}

void Pretre::filter_average(float op[7][7], int n)
{
	for (int y = n / 2; y<h - n / 2; y++)
		for (int x = n / 2; x < w - n / 2; x++)
		{
			float sum = 0;
			for (int t = -n / 2; t <= n / 2; t++)
				for (int s = -n / 2; s <= n / 2; s++)
					sum = sum + op[t + n / 2][s + n / 2] * file[(y + t)*w + x + s];
			if (sum < 0)file[x*w + y] = 0;
			else if (sum > 255)file[x*w + y] = 255;
			else file[x*w + y] = int(sum);
		}
}

void Pretre::filter_middle(int n)
{
	int m = n / 2, t, s = n*n;
	int a[100];
	for (int y = n; y<h - m; y++)
		for (int x = m; x < w - m; x++)
		{
			int k = 0;
			for (int k1 = -m; k1 <= m; k1++)
				for (int k2 = -m; k2 <= m; k2++)
					a[k++] = file[(y + k1)*w + x + k2];
			for (int i = 0; i<s; i++)
				for (int j = 0; j < s - i - 1; j++)
					if (a[j] > a[j + 1])
					{
						t = a[j];
						a[j] = a[j + 1];
						a[j + 1] = t;
					}
			file[y*w + x] = a[s / 2];
		}
}

//void Pretre::filter_k(int * pic, int n, int k)
