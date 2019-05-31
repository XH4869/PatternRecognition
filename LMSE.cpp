// LMSE.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Eigen\Dense>
using namespace Eigen;
using namespace std;
void InitializeMat(MatrixXd &X, VectorXd &b, int num, int dim, int &c);
void LMSE(MatrixXd X, VectorXd &w, VectorXd b, VectorXd e, int c);
bool IsPositive(VectorXd e);
int main()
{
	int num, dim, c;
	cout << "请输入向量的维度和每类的数量:";
	cin >> dim >> num;

	MatrixXd X(2 * num, dim + 1);
	VectorXd w(dim + 1), b(2 * num), e(2 * num);

	InitializeMat(X, b, num, dim, c);

	LMSE(X, w, b, e, c);

	cout << "解向量如下：w=" << w << endl;
    return 0;
}

void InitializeMat(MatrixXd &X, VectorXd &b, int num, int dim, int &c)
{
	cout << "请输入第一类特征向量：" << endl;
	for (int i = 0; i < num; i++)
	{
		printf("x%d:", i + 1);
		cin >> X(i, 0) >> X(i, 1) >> X(i, 2);
		X(i, 3) = 1;
	}
	
	cout << "请输入第二类特征向量：" << endl;
	for (int i = 0; i < num; i++)
	{
		printf("x%d:", i + 1);
		cin >> X(i + num, 0) >> X(i + num, 1) >> X(i + num, 2);
		for (int j = 0; j < dim; j++)
			X(i + num, j) *= -1;
		X(i + num, 3) = -1;
	}

	cout << "请输入b的初始向量值b(0)：";
	for (int i = 0; i < 2 * num; i++)
		cin >> b[i];

	cout << "请输入矫正系数c：";
	cin >> c;
}

bool IsPositive(VectorXd e)
{
	int row = e.rows();
	for (int i = 0; i < row; i++)
		if (e[i] < 0)
			return false;
	return true;
}

void LMSE(MatrixXd X, VectorXd &w, VectorXd b, VectorXd e, int c)
{
	MatrixXd X_T = X.transpose();
	MatrixXd X_tmp = X_T*X;
	const MatrixXd X_Inv = X_tmp.inverse();
	MatrixXd X_MSE = X_Inv*X_T;

	w = X_MSE*b;
	e = X*w - b;
	while (X*w != b)
	{
		if (!IsPositive(e))
		{
			cout << "系统线性不可分！" << endl;
			return;
		}
		else
		{
			b += 2 * c*e;
			w = X_MSE*b;
		}
	}
	cout << "系统线性可分！" << endl;
}