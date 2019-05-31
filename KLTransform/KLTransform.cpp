// KLTransform.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <Eigen\Dense>
#include <Eigen\Eigenvalues>
using namespace Eigen;
using namespace std;
void GetR(MatrixXd &R, int num, int dimension, MatrixXd X);
void Sort_m(MatrixXd N, int dimension, int m, int* &sort);
void GetA(MatrixXd &A, MatrixXd V, int* sort, int m, int dimension);
int main()
{
	int num, dimension, m;//num代表数量，dimension代表原始维度，m代表降维后的维度
	printf("请输入原始特征向量的维度和数量:");
	scanf("%d %d", &dimension, &num);
	printf("请输入降维后的维度:");
	scanf("%d", &m);
	int *sort = new int[m];

	MatrixXd X(num, dimension), Y(num, m);//X为输入特征值，Y为变换后的特征值
	MatrixXd A(m, dimension), R(dimension, dimension), V(dimension, dimension);//A为所求变换矩阵，R为x的自相关矩阵，V为特征向量矩阵
	MatrixXd N(dimension, dimension); //N为特征值矩阵

	printf("请输入原始特征向量:\n");
	for (int i = 0; i < num; i++)
		scanf("%lf %lf %lf", &X(i, 0), &X(i, 1), &X(i, 2));
	
	GetR(R, num, dimension, X);
	EigenSolver<MatrixXd> es(R);
	N = es.pseudoEigenvalueMatrix();
	V = es.pseudoEigenvectors();
	Sort_m(N, dimension, m, sort);
	GetA(A, V, sort, m, dimension);
	Y = A*X.transpose();
	cout << "变换后的特征如下:" << endl;
	cout << Y.transpose() << endl;

	if (sort) delete[] sort;
	system("pause");
    return 0;
}

void GetR(MatrixXd &R, int num, int dimension, MatrixXd X)
{
	for (int j = 0; j < dimension; j++)
		for (int k = 0; k < dimension; k++)
			R(j, k) = 0;

	for (int i = 0; i < num; i++)
		for (int j = 0; j < dimension; j++)
			for (int k = 0; k < dimension; k++)
				R(j, k) += X(i, j) * X(i, k);
	
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			R(i, j) /= num;
}

void Sort_m(MatrixXd N, int dimension, int m, int* &sort)
{
	for (int i = 0; i < m; i++)
	{
		int index = -1;
		double max = -10000;
		for (int j = 0; j < dimension; j++)
		{
			if (N(j, j) > max)
			{
				max = N(j, j);
				index = j;
			}
		}
		sort[i] = index;
		N(index, index) = -10000;
	}
}

void GetA(MatrixXd &A, MatrixXd V, int* sort, int m, int dimension)
{
	for (int i = 0; i < m; i++)
	{
		int m_col = sort[i];
		MatrixXd tmp = V.col(m_col);
		MatrixXd tmp_T=tmp.transpose();
		for (int j = 0; j < dimension; j++)
		{
			A(i, j) = tmp_T(0, j);
		}
	}
}
