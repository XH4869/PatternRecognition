// Hierarchical_Cluster.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;
typedef struct Sample
{
	int tag;//所属类别
	int id;//样本编号
	int x1, x2, x3, x4, x5, x6;//六个维度的特征值
}Sample;
typedef struct Center
{
	double x1, x2, x3, x4, x5, x6;//样本中心的六维坐标
	int count;//包含样本的数量
	int *id;//记录包含样本的编号的数组
}Center;
int GetDistanceArray(vector<Center>&center, Sample *sample, int type, int &classes, int number, int T);
double GetDistance_G(vector<Center>&center, int i, int j);
double GetDistance_M(vector < Center>&center, Sample *sample, int i, int j);
double MaxDist(vector<Center>&center, Sample *sample, int i, int j);
double MinDist(vector<Center>&center, Sample *sample, int i, int j);
double GetDist(Sample s1, Sample s2);
bool GetCenter(vector<Center>&center, Sample *sample, int number);
double FindMinDist(double *DistArray, int classes, int &i, int &j);
Sample* Join(vector<Center>&center, Sample *sample, int c1, int c2, int &classes);
int main()
{
	Sample *sample;
	vector<Center> center;
	int number, classes, T, type;
	
	printf("请输入样本数量:");
	scanf("%d", &number);
	classes = number;

	sample = new Sample[number];

	printf("请输入样本数据:\n");
	for (int i = 0; i < number; i++)
	{
		sample[i].id = i;
		sample[i].tag = i;
		scanf("%d %d %d %d %d %d", &sample[i].x1, &sample[i].x2, &sample[i].x3, &sample[i].x4, &sample[i].x5, &sample[i].x6);
	}
	//printf("\n");

	printf("请选择距离准则(0-中间距离法 1-重心距离法):");
	scanf("%d", &type);

	printf("请输入阈值:");
	scanf("%d", &T);

	while (true)
	{
		int result = GetDistanceArray(center, sample, type, classes, number, T);
		if (result == 0)
		{
			printf("类间最小距离超过阈值，分类完成！\n");
			break;
		}
		if (result == -1)
		{
			printf("当前类别数已达目标数，分类完成！\n");
			break;
		}
	}

	printf("分类结果如下:\n");
	for (int i = 0; i < classes; i++)
	{
		printf("第%d类:", i + 1);
		for (int j = 0; j < center[i].count; j++)
		{
			int id = center[i].id[j];
			printf("x%d(%d,%d,%d,%d,%d,%d) ", id + 1, sample[id].x1, sample[id].x2, sample[id].x3, sample[id].x4, sample[id].x5, sample[id].x6);
		}
		printf("\n");
	}

	if (sample) delete[] sample;
	system("pause");
	return 0;
}

bool GetCenter(vector<Center>&center, Sample *sample, int number)
{
	Center tmp;
	double s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	for (int i = 0; i < number; i++)
	{
		tmp.id = new int[number];
		tmp.count = 0;
		for (int j = 0; j < number; j++)
			if (sample[j].tag == i)
			{
				s1 += sample[j].x1; s2 += sample[j].x2; s3 += sample[j].x3;
				s4 += sample[j].x4; s5 += sample[j].x5; s6 += sample[j].x6;
				tmp.id[tmp.count] = sample[j].id;
				tmp.count++;
			}
		tmp.x1 = s1 / tmp.count; tmp.x2 = s2 / tmp.count; tmp.x3 = s3 / tmp.count;
		tmp.x4 = s4 / tmp.count; tmp.x5 = s5 / tmp.count; tmp.x6 = s6 / tmp.count;
		s1 = s2 = s3 = s4 = s5 = s6 = 0;
		if (tmp.count != 0)
			center.push_back(tmp);
	}
	return true;
}

double GetDistance_G(vector<Center>&center, int i, int j)
{
	double d1, d2, d3, d4, d5, d6;
	d1 = center[i].x1 - center[j].x1; d2 = center[i].x2 - center[j].x2; d3 = center[i].x3 - center[j].x3;
	d4 = center[i].x4 - center[j].x4; d5 = center[i].x5 - center[j].x5; d6 = center[i].x6 - center[j].x6;
	double sum = 0;
	sum = pow(d1, 2) + pow(d2, 2) + pow(d3, 2) + pow(d4, 2) + pow(d5, 2) + pow(d6, 2);
	return sum;
}

double GetDistance_M(vector<Center>&center, Sample *sample, int i, int j)
{
	if (i == j)
		return 0;
	double d_min, d_max, d_center;
	d_center = GetDistance_G(center, i, j);
	d_max = MaxDist(center, sample, i, j);
	d_min = MinDist(center, sample, i, j);
	return (pow(d_max, 2) / 2 + pow(d_min, 2) / 2 - pow(d_center, 2) / 4);
}

double MaxDist(vector<Center>&center, Sample *sample, int i, int j)
{
	double max = 0, dist = 0;
	for (int m = 0; m < center[i].count; m++)
	{
		int id1 = center[i].id[m];
		for (int n = 0; n < center[j].count; n++)
		{
			int id2 = center[j].id[n];
			dist = GetDist(sample[id1], sample[id2]);
			if (dist > max)
				max = dist;
		}
	}
	return max;
}

double MinDist(vector<Center>&center, Sample *sample, int i, int j)
{
	double min = 10000, dist = 0;
	for (int m = 0; m < center[i].count; m++)
	{
		int id1 = center[i].id[m];
		for (int n = 0; n < center[j].count; n++)
		{
			int id2 = center[j].id[n];
			dist = GetDist(sample[id1], sample[id2]);
			if (dist < min)
				min = dist;
		}
	}
	return min;
}

double GetDist(Sample s1, Sample s2) 
{
	double d1, d2, d3, d4, d5, d6;
	d1 = s1.x1 - s2.x1; d2 = s1.x2 - s2.x2; d3 = s1.x3 - s2.x3;
	d4 = s1.x4 - s2.x4; d5 = s1.x5 - s2.x5; d6 = s1.x6 - s2.x6;
	return (d1*d1 + d2*d2 + d3*d3 + d4*d4 + d5*d5 + d6*d6);
}

double FindMinDist(double *DistArray, int classes, int &i, int &j)
{
	double min = 10000;
	for (int m = 0; m < classes; m++)
		for (int n = m; n < classes; n++)
			if (DistArray[m*classes + n] < min&&DistArray[m*classes + n] != 0)
			{
				min = DistArray[m*classes + n];
				i = m;
				j = n;
			}
	return min;
}

int GetDistanceArray(vector<Center>&center, Sample *sample, int type, int &classes, int number, int T)
{
	double *DistArray = new double[classes*classes];
	GetCenter(center, sample, number);

	for (int i = 0; i < classes; i++)
		for (int j = i; j < classes; j++)
			switch (type)
			{
			case 0:
				DistArray[i*classes + j] = GetDistance_M(center, sample, i, j);
				DistArray[j*classes + i] = DistArray[i*classes + j];
				break;
			case 1:
				DistArray[i*classes + j] = GetDistance_G(center, i, j);
				DistArray[j*classes + i] = DistArray[i*classes + j];
				break;
			}

	int c1, c2;
	double MinDist;
	MinDist = FindMinDist(DistArray, classes, c1, c2);

	if (MinDist > T)
	{
		if (DistArray) delete[] DistArray;
		return 0;
	}

	sample = Join(center, sample, c1, c2, classes);

	if (classes == 2)
	{
		if (DistArray) delete[] DistArray;
		center.clear();
		GetCenter(center, sample, number);
		return -1;
	}

	if (DistArray) delete[] DistArray;
	center.clear();
	return 1;
}

Sample* Join(vector<Center>&center, Sample *sample, int c1, int c2, int &classes)
{
	for (int i = center[c1].count; i < center[c1].count + center[c2].count; i++)
		center[c1].id[i] = center[c2].id[i - center[c1].count];
	for (int i = 0; i < center[c2].count; i++)
	{
		int id = center[c2].id[i];
		sample[id].tag = sample[center[c1].id[0]].tag;
	}
	center[c1].x1 = (center[c1].x1*center[c1].count + center[c2].x1*center[c2].count) / (center[c1].count + center[c2].count);
	center[c1].x2 = (center[c1].x2*center[c1].count + center[c2].x2*center[c2].count) / (center[c1].count + center[c2].count);
	center[c1].x3 = (center[c1].x3*center[c1].count + center[c2].x3*center[c2].count) / (center[c1].count + center[c2].count);
	center[c1].x4 = (center[c1].x4*center[c1].count + center[c2].x4*center[c2].count) / (center[c1].count + center[c2].count);
	center[c1].x5 = (center[c1].x5*center[c1].count + center[c2].x5*center[c2].count) / (center[c1].count + center[c2].count);
	center[c1].x6 = (center[c1].x6*center[c1].count + center[c2].x6*center[c2].count) / (center[c1].count + center[c2].count);
	center[c1].count += center[c2].count;
	center.erase(center.begin() + c2);
	classes--;

	return sample;
}
