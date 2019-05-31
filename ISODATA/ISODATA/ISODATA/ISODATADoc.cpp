
// ISODATADoc.cpp : CISODATADoc 类的实现
//

#include "stdafx.h"
#include "DoublePt.h"
#include <vector>
using namespace std;
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ISODATA.h"
#endif

#include "ISODATADoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CISODATADoc

IMPLEMENT_DYNCREATE(CISODATADoc, CDocument)

BEGIN_MESSAGE_MAP(CISODATADoc, CDocument)
END_MESSAGE_MAP()


// CISODATADoc 构造/析构

CISODATADoc::CISODATADoc()
	: m_K(0)
	, m_SigmaN(0)
	, m_SigmaS(0)
	, m_SigmaC(0)
	, m_L(0)
	, m_I(0)
	, m_PtCount(0)
	, m_C(0)
	, m_CenterNum(NULL)
	, p_Pt(NULL)
	, m_DistArr(NULL)
	, m_TotalDist(0)
{
	// TODO: 在此添加一次性构造代码

}

CISODATADoc::~CISODATADoc()
{
}

BOOL CISODATADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CISODATADoc 序列化

void CISODATADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CISODATADoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CISODATADoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CISODATADoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CISODATADoc 诊断

#ifdef _DEBUG
void CISODATADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CISODATADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CISODATADoc 命令
#include <math.h>

void CISODATADoc::IsoData()
{
	//变量初始化
	m_CenterNum = new int[m_C];//各类点的个数
	p_Pt = new CPoint*[m_C];//用以将点分类存储在各个聚类中
	for (int i = 0; i < m_C; i++)
		p_Pt[i] = new CPoint[m_PtCount];
	m_DistArr = new double[m_C];//每个类别样本到中心距离的平均值
	int iteration = 0;//迭代次数
	//确定C个初始聚类中心，取前C个样本作为初始聚类中心
	for (int i = 0; i < m_C; i++)
	{
		CDoublePt tmp;
		tmp.m_x = (double)m_Pt[i].x;
		tmp.m_y = (double)m_Pt[i].y;
		m_CenterPt.push_back(tmp);
		m_CenterNum[i] = 0;
	}
step3:
	while (m_I != iteration)
	{
		//根据最小距离准则分类
		for (int i = 0; i < m_PtCount; i++)
		{
			double *dist = new double[m_C], min = 10000;
			int index;
			for (int j = 0; j < m_C; j++)
				dist[j] = GetDist(m_Pt[i], m_CenterPt[j]);//计算每个样本到每个聚类中心的距离
			for (int k = 0; k < m_C; k++)//找到最小距离
				if (dist[k] < min)
				{
					min = dist[k];
					index = k;
				}
			p_Pt[index][m_CenterNum[index]++] = m_Pt[i];
			if (dist) delete[] dist;
		}
		//计算新的聚类中心
		for (int i = 0; i < m_C; i++)
		{
			double sum_x = 0, sum_y = 0;
			for (int j = 0; j < m_CenterNum[i]; j++)
			{
				sum_x += p_Pt[i][j].x;
				sum_y += p_Pt[i][j].y;
			}
			m_CenterPt[i].m_x = sum_x / (double)m_CenterNum[i];
			m_CenterPt[i].m_y = sum_y / (double)m_CenterNum[i];
		}
		//计算每一聚类样本到聚类中心距离的平均值
		for (int i = 0; i < m_C; i++)
		{
			double d = 0;
			for (int j = 0; j < m_CenterNum[i]; j++)
				d += GetDist(p_Pt[i][j], m_CenterPt[i]);
			m_DistArr[i] = d / (double)m_CenterNum[i];
		}
		//计算总距离的平均值
		for (int i = 0; i < m_C; i++)
			m_TotalDist += m_DistArr[i] * m_CenterNum[i];
		m_TotalDist /= (double)m_PtCount;

		iteration++;
		break;
	}
	//判断
	if (iteration == m_I) goto end;
	if (m_C <= m_K / 2 || (m_C > m_K / 2 && m_C < m_K * 2 && iteration % 2))
	{
		Split();
		for (int i = 0; i < m_C; i++)
			m_CenterNum[i] = 0;
		goto step3;
	}
	//合并操作
	int d1 = -1, d2 = -1;
	double min = 10000;
	for (int i = 0; i < m_C - 1; i++)//设置L为1，每次只合并中心距离最小的两类
		for (int j = i + 1; j < m_C; j++)
		{
			double dist = GetCenterDist(m_CenterPt[i], m_CenterPt[j]);
			if (dist < m_SigmaC)
				if (dist < min)
				{
					min = dist;
					d1 = i, d2 = j;
				}
		}
	
	if (d1 != -1 && d2 != -1)
	{
		m_C--;

		CDoublePt tmp;
		tmp.m_x = (m_CenterNum[d1] * m_CenterPt[d1].m_x + m_CenterNum[d2] * m_CenterPt[d2].m_x) / (m_CenterNum[d1] + m_CenterNum[d2]);
		tmp.m_y = (m_CenterNum[d1] * m_CenterPt[d1].m_y + m_CenterNum[d2] * m_CenterPt[d2].m_y) / (m_CenterNum[d1] + m_CenterNum[d2]);
		m_CenterPt[d1] = tmp;
		m_CenterPt.erase(m_CenterPt.begin() + d2);

		m_CenterNum = new int[m_C];
		p_Pt = new CPoint*[m_C];
		for (int i = 0; i < m_C; i++)
			p_Pt[i] = new CPoint[m_PtCount];
		m_DistArr = new double[m_C];
	}

	for (int i = 0; i < m_C; i++)
		m_CenterNum[i] = 0;
	goto step3;

end:
	if (m_DistArr) delete[] m_DistArr;
}


double CISODATADoc::GetDist(CPoint point, CDoublePt center)
{
	double dx, dy;
	dx = center.m_x - (double)point.x;
	dy = center.m_y - (double)point.y;
	return sqrt(dx*dx + dy*dy);
}


void CISODATADoc::Split()
{
	//计算每一类的向量
	double **var = new double*[m_C];
	for (int i = 0; i < m_C; i++)
		var[i] = new double[2];
	double *var_max = new double[m_C];
	int *var_id = new int[m_C];

	for (int i = 0; i < m_C; i++)
	{
		double sum_x = 0, sum_y = 0;
		for (int j = 0; j < m_CenterNum[i]; j++)
		{
			sum_x += pow((p_Pt[i][j].x - m_CenterPt[i].m_x), 2);
			sum_y += pow((p_Pt[i][j].y - m_CenterPt[i].m_y), 2);
		}
		var[i][0] = sum_x / (double)m_CenterNum[i];
		var[i][1] = sum_y / (double)m_CenterNum[i];
		var_max[i] = (var[i][0] > var[i][1] ? var[i][0] : var[i][1]);
		var_id[i] = (var[i][0] > var[i][1] ? 0 : 1);
	}

	bool change = false;
	for (int i = 0; i < m_C; i++)
		if (var_max[i]>m_SigmaS)
			if ((m_DistArr[i] >= m_TotalDist&&m_CenterNum[i] > 2 * (m_SigmaN + 1)) || m_C < m_K / 2)
			{
				m_C++;
				change = true;
				double r = var_max[i] / 2;
				CDoublePt tmp, z1, z2;
				tmp = m_CenterPt[i];
				switch (var_id[i])
				{
				case 0:
					z1.m_y = z2.m_y = tmp.m_y;
					z1.m_x = tmp.m_x - r;
					z2.m_x = tmp.m_x + r;
					break;
				case 1:
					z1.m_x = z2.m_x = tmp.m_x;
					z1.m_y = tmp.m_y - r;
					z2.m_y = tmp.m_y + r;
					break;
				}
				m_CenterPt[i] = z1;
				m_CenterPt.push_back(z2);

				if (m_CenterNum) delete[] m_CenterNum;
				for (int i = 0; i < m_C - 1; i++)
					if (p_Pt[i]) delete[] p_Pt[i];
				if (p_Pt) delete[] p_Pt;
				if (m_DistArr) delete[] m_DistArr;

				m_CenterNum = new int[m_C];
				p_Pt = new CPoint*[m_C];
				for (int i = 0; i < m_C; i++)
					p_Pt[i] = new CPoint[m_PtCount];
				m_DistArr = new double[m_C];

				break;
			}

	if (change == false)
	{
		for (int i = 0; i < m_C; i++)
			if (var[i]) delete[] var[i];
	}
	else
	{
		for (int i = 0; i < m_C - 1; i++)
			if (var[i]) delete[] var[i];
	}
	if (var) delete[] var;
	if (var_max) delete[] var_max;
	if (var_id) delete[] var_id;
}


double CISODATADoc::GetCenterDist(CDoublePt z1, CDoublePt z2)
{
	double dx, dy;
	dx = z1.m_x - z2.m_x;
	dy = z1.m_y - z2.m_y;
	return sqrt(dx*dx + dy*dy);
}
