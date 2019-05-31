// MultiClassifier.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <Eigen\Dense>
using namespace std;
using namespace Eigen;
void InitialVector(VectorXi &x1, VectorXi &x2, VectorXi &x3, int dim);
void GetW(VectorXi x1, VectorXi x2, VectorXi x3, VectorXi &w1, VectorXi &w2, VectorXi &w3);
int main()
{
	int dim;
	cout << "请输入维度:";
	cin >> dim;
	VectorXi w1(dim + 1), w2(dim + 1), w3(dim + 1);
	VectorXi x1(dim + 1), x2(dim + 1), x3(dim + 1);
	w1.setZero(); w2.setZero(); w3.setZero();
	
	InitialVector(x1, x2, x3, dim);

	GetW(x1, x2, x3, w1, w2, w3);

	cout << "三个权向量分别是:" << endl;
	cout << "w1:" << w1.transpose() << endl;
	cout << "w2:" << w2.transpose() << endl;
	cout << "w3:" << w3.transpose() << endl;
	
	system("pause");
    return 0;
}
void InitialVector(VectorXi &x1, VectorXi &x2, VectorXi &x3, int dim)
{
	cout << "请输入训练样本:" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			switch (i)
			{
			case 0:
				cin >> x1(j);
				break;
			case 1:
				cin >> x2(j);
				break;
			case 2:
				cin >> x3(j);
				break;
			}
		}
		switch (i)
		{
		case 0:
			x1(dim) = 1;
			break;
		case 1:
			x2(dim) = 1;
			break;
		case 2:
			x3(dim) = 1;
			break;
		}
	}
}
void GetW(VectorXi x1, VectorXi x2, VectorXi x3, VectorXi &w1, VectorXi &w2, VectorXi &w3)
{
	int d1, d2, d3;
	bool is1 = false, is2 = false, is3 = false;
	while (1)
	{
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
				d1 = w1.transpose()*x1;
				d2 = w2.transpose()*x1;
				d3 = w3.transpose()*x1;
				if (d1 <= d2)
					w2 -= x1;
				if (d1 <= d3)
					w3 -= x1;
				if (d1 > d2&&d1 > d3)
					is1 = true;
				else
					w1 += x1;
				break;
			case 1:
				d1 = w1.transpose()*x2;
				d2 = w2.transpose()*x2;
				d3 = w3.transpose()*x2;
				if (d2 <= d1)
					w1 -= x2;
				if (d2 <= d3)
					w3 -= x2;
				if (d2 > d1&&d2 > d3)
					is2 = true;
				else
					w2 += x2;
				break;
			case 2:
				d1 = w1.transpose()*x3;
				d2 = w2.transpose()*x3;
				d3 = w3.transpose()*x3;
				if (d3 <= d1)
					w1 -= x3;
				if (d3 <= d2)
					w2 -= x3;
				if (d3 > d2&&d3 > d1)
					is3 = true;
				else
					w3 += x3;
				break;
			}
		}
		if (is1&&is2&&is3)
			break;
	}
}