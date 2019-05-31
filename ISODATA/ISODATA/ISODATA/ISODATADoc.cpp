
// ISODATADoc.cpp : CISODATADoc ���ʵ��
//

#include "stdafx.h"
#include "DoublePt.h"
#include <vector>
using namespace std;
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CISODATADoc ����/����

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
	// TODO: �ڴ����һ���Թ������

}

CISODATADoc::~CISODATADoc()
{
}

BOOL CISODATADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CISODATADoc ���л�

void CISODATADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CISODATADoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CISODATADoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CISODATADoc ���

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


// CISODATADoc ����
#include <math.h>

void CISODATADoc::IsoData()
{
	//������ʼ��
	m_CenterNum = new int[m_C];//�����ĸ���
	p_Pt = new CPoint*[m_C];//���Խ������洢�ڸ���������
	for (int i = 0; i < m_C; i++)
		p_Pt[i] = new CPoint[m_PtCount];
	m_DistArr = new double[m_C];//ÿ��������������ľ����ƽ��ֵ
	int iteration = 0;//��������
	//ȷ��C����ʼ�������ģ�ȡǰC��������Ϊ��ʼ��������
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
		//������С����׼�����
		for (int i = 0; i < m_PtCount; i++)
		{
			double *dist = new double[m_C], min = 10000;
			int index;
			for (int j = 0; j < m_C; j++)
				dist[j] = GetDist(m_Pt[i], m_CenterPt[j]);//����ÿ��������ÿ���������ĵľ���
			for (int k = 0; k < m_C; k++)//�ҵ���С����
				if (dist[k] < min)
				{
					min = dist[k];
					index = k;
				}
			p_Pt[index][m_CenterNum[index]++] = m_Pt[i];
			if (dist) delete[] dist;
		}
		//�����µľ�������
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
		//����ÿһ�����������������ľ����ƽ��ֵ
		for (int i = 0; i < m_C; i++)
		{
			double d = 0;
			for (int j = 0; j < m_CenterNum[i]; j++)
				d += GetDist(p_Pt[i][j], m_CenterPt[i]);
			m_DistArr[i] = d / (double)m_CenterNum[i];
		}
		//�����ܾ����ƽ��ֵ
		for (int i = 0; i < m_C; i++)
			m_TotalDist += m_DistArr[i] * m_CenterNum[i];
		m_TotalDist /= (double)m_PtCount;

		iteration++;
		break;
	}
	//�ж�
	if (iteration == m_I) goto end;
	if (m_C <= m_K / 2 || (m_C > m_K / 2 && m_C < m_K * 2 && iteration % 2))
	{
		Split();
		for (int i = 0; i < m_C; i++)
			m_CenterNum[i] = 0;
		goto step3;
	}
	//�ϲ�����
	int d1 = -1, d2 = -1;
	double min = 10000;
	for (int i = 0; i < m_C - 1; i++)//����LΪ1��ÿ��ֻ�ϲ����ľ�����С������
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
	//����ÿһ�������
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
