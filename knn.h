#ifndef KNN_H
#define KNN_H
#include"Eigen/Dense"
#include<iostream>
using namespace std;
using namespace Eigen;
#define classnum 6  //classnum是数据分成了几个类别
int knn(MatrixXf model, MatrixXf sample, int n, int div_num);
//model是已经训练好的特征数据集，大小是height*width，height是训练时的样本图片数量，width是前width个最大特征值
//sample是输入要检测的图片的主成分，是个1*width的行向量
//n表示在model中取前n个与sample距离最小的行向量
//dic_num表示每个划分的样本数量，且每段都相等，比如男 眼镜  有10个图片，则dic_num=10；
//函数返回值是1-6的值，表示图片在哪个分类中；
//男 眼镜             1
//男 口罩             2
//男 无口罩眼镜   3
//女 眼镜             4
//女 口罩             5
//女 无口罩眼镜   6
#endif
