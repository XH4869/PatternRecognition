// LMSE.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "������������ά�Ⱥ�ÿ�������:";
	cin >> dim >> num;

	MatrixXd X(2 * num, dim + 1);
	VectorXd w(dim + 1), b(2 * num), e(2 * num);

	InitializeMat(X, b, num, dim, c);

	LMSE(X, w, b, e, c);

	cout << "���������£�w=" << w << endl;
    return 0;
}

void InitializeMat(MatrixXd &X, VectorXd &b, int num, int dim, int &c)
{
	cout << "�������һ������������" << endl;
	for (int i = 0; i < num; i++)
	{
		printf("x%d:", i + 1);
		cin >> X(i, 0) >> X(i, 1) >> X(i, 2);
		X(i, 3) = 1;
	}
	
	cout << "������ڶ�������������" << endl;
	for (int i = 0; i < num; i++)
	{
		printf("x%d:", i + 1);
		cin >> X(i + num, 0) >> X(i + num, 1) >> X(i + num, 2);
		for (int j = 0; j < dim; j++)
			X(i + num, j) *= -1;
		X(i + num, 3) = -1;
	}

	cout << "������b�ĳ�ʼ����ֵb(0)��";
	for (int i = 0; i < 2 * num; i++)
		cin >> b[i];

	cout << "���������ϵ��c��";
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
			cout << "ϵͳ���Բ��ɷ֣�" << endl;
			return;
		}
		else
		{
			b += 2 * c*e;
			w = X_MSE*b;
		}
	}
	cout << "ϵͳ���Կɷ֣�" << endl;
}