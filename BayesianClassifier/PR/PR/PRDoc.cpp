
// PRDoc.cpp : CPRDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PR.h"
#endif

#include "PRDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPRDoc

IMPLEMENT_DYNCREATE(CPRDoc, CDocument)

BEGIN_MESSAGE_MAP(CPRDoc, CDocument)
END_MESSAGE_MAP()


// CPRDoc ����/����

CPRDoc::CPRDoc()
	: m_Count1(0)
	, m_Count2(0)
	, m_Count3(0)
	, w21(0)
	, w22(0)
	, w11(0)
	, w12(0)
	, w0(0)
	, w23(0)
	, m_IsCovEqual(-1)
	, m_CountTestPt(0)
{
	// TODO: �ڴ����һ���Թ������
	memset(m_var1, 0, sizeof(m_var1));
	memset(m_var2, 0, sizeof(m_var2));
	memset(m_var3, 0, sizeof(m_var3));
}

CPRDoc::~CPRDoc()
{
}

BOOL CPRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPRDoc ���л�

void CPRDoc::Serialize(CArchive& ar)
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
void CPRDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CPRDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CPRDoc::SetSearchContent(const CString& value)
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

// CPRDoc ���

#ifdef _DEBUG
void CPRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPRDoc ����


void CPRDoc::Calculate()
{
	double sum_x = 0, sum_y = 0, sum_xy = 0;
	//������1�ľ�ֵ��Э������
	if (m_Count1)
	{
		for (int i = 0; i < m_Count1; i++)
		{
			sum_x += Pt1[i].x;
			sum_y += Pt1[i].y;
		}
		m_mean1[0] = sum_x / (double)(m_Count1);
		m_mean1[1] = sum_y / (double)(m_Count1);

		sum_x = sum_y = 0;
		for (int i = 0; i < m_Count1; i++)
		{
			sum_x += pow(Pt1[i].x - m_mean1[0], 2);
			sum_y += pow(Pt1[i].y - m_mean1[1], 2);
			sum_xy += ((Pt1[i].x - m_mean1[0])*(Pt1[i].y - m_mean1[1]));
		}
		m_var1[0] = sum_x / (double)(m_Count1 - 1);
		m_var1[1] = m_var1[2] = sum_xy / (double)(m_Count1 - 1);
		m_var1[3] = sum_y / (double)(m_Count1 - 1);
	}
	//������2�ľ�ֵ��Э������
	if (m_Count2)
	{
		sum_x = sum_y = 0;
		for (int i = 0; i < m_Count2; i++)
		{
			sum_x += Pt2[i].x;
			sum_y += Pt2[i].y;
		}
		m_mean2[0] = sum_x / (double)(m_Count2);
		m_mean2[1] = sum_y / (double)(m_Count2);

		sum_x = sum_y = sum_xy = 0;
		for (int i = 0; i < m_Count2; i++)
		{
			sum_x += pow(Pt2[i].x - m_mean2[0], 2);
			sum_y += pow(Pt2[i].y - m_mean2[1], 2);
			sum_xy += ((Pt2[i].x - m_mean2[0])*(Pt2[i].y - m_mean2[1]));
		}
		m_var2[0] = sum_x / (double)(m_Count2 - 1);
		m_var2[1] = m_var2[2] = sum_xy / (double)(m_Count2 - 1);
		m_var2[3] = sum_y / (double)(m_Count2 - 1);
	}
	//������3�ľ�ֵ��Э������
	if (m_Count3)
	{
		sum_x = sum_y = 0;
		for (int i = 0; i < m_Count3; i++)
		{
			sum_x += Pt3[i].x;
			sum_y += Pt3[i].y;
		}
		m_mean3[0] = sum_x / (double)(m_Count3);
		m_mean3[1] = sum_y / (double)(m_Count3);

		sum_x = sum_y = sum_xy = 0;
		for (int i = 0; i < m_Count3; i++)
		{
			sum_x += pow(Pt3[i].x - m_mean3[0], 2);
			sum_y += pow(Pt3[i].y - m_mean3[1], 2);
			sum_xy += ((Pt3[i].x - m_mean3[0])*(Pt3[i].y - m_mean3[1]));
		}
		m_var3[0] = sum_x / (double)(m_Count3 - 1);
		m_var3[1] = m_var3[2] = sum_xy / (double)(m_Count3 - 1);
		m_var3[3] = sum_y / (double)(m_Count3 - 1);
	}
	//�������Э��������ͬ���ϲ�ԭЭ������m_IsCovEqualΪ0��ʾѡ��Э��������ͬ��
	if (!m_IsCovEqual)
	{
		m_var1[0] = m_var2[0] = m_var3[0] = m_var1[0] + m_var2[0] + m_var3[0];
		m_var1[1] = m_var2[1] = m_var3[1] = m_var1[1] + m_var2[1] + m_var3[1];
		m_var1[2] = m_var2[2] = m_var3[2] = m_var1[2] + m_var2[2] + m_var3[2];
		m_var1[3] = m_var2[3] = m_var3[3] = m_var1[3] + m_var2[3] + m_var3[3];
	}
}

#include <math.h>
void CPRDoc::CountCoefficient2(CDC *pDC)
{
	//���б�����ʾΪw21*x^2+w11*x+w23*x*y+w12*y+w22*y^2+w0����ʽ
	double A11 = m_var1[3], A12 = m_var1[1], A22 = m_var1[0], B11 = m_var2[3], B12 = m_var2[1], B22 = m_var2[0];
	double x1 = m_mean1[0], y1 = m_mean1[1], x2 = m_mean2[0], y2 = m_mean2[1];
	w21 = (A11 - B11) / 2;
	w22 = (A22 - B22) / 2;
	w23 = B12 - A12;
	w11 = (A12*y1 - A11*x1) - (B12*y2 - B11*x2);
	w12 = (A12*x1 - A22*y1) - (B12*x2 - B22*y2);
	w0 = 1 / 2 * log((A11*A22 - A12*A12) / (B11*B22 - B12*B12)) - log(m_Count1 / m_Count2);

	CBrush *pOldBrush, NewBrush;
	CPen NewPen;
	NewBrush.CreateSolidBrush(RGB(0, 0, 255));
	NewPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	pOldBrush = pDC->SelectObject(&NewBrush);

	double A = w22, B, C;
	CPoint m_CurrentPt;
	for (int j = -400; j <= 400; j++)
	{
		double x = (double)j / 100, y;
		B = w12 + w23*x;
		C = w21*x*x + w11*x + w0;

		if ((B == 0) && (C == 0) && (A == 0))
		{
			pDC->SelectObject(NewPen);
			pDC->MoveTo((int)(x * 100), -500);
			pDC->LineTo((int)(x * 100), 500);
			pDC->SelectObject(NewBrush);
		}

		if (B)
		{
			if (fabs(A)<1e-06)
			{
				y = -C / B;
			}
			else
			{
				double d = B*B - 4 * A*C;
				if (d < 0)
					continue;
				y = (sqrt(d) - B) / (2 * A);
			}

			m_CurrentPt.x = (int)(x * 100);
			m_CurrentPt.y = (int)(y * 100);
			/*
			if (j == -400)
			{
			m_OldPt = m_CurrentPt;
			continue;
			}
			else
			{
			pDC->MoveTo(m_OldPt);
			pDC->LineTo(m_CurrentPt);
			}
			m_OldPt = m_CurrentPt;
			*/
			pDC->Ellipse(m_CurrentPt.x - 2, m_CurrentPt.y - 2, m_CurrentPt.x + 2, m_CurrentPt.y + 2);
		}
	}
	pDC->SelectObject(pOldBrush);
}


void CPRDoc::CountCoefficient3(CDC *pDC)
{
	double A11[3] = { m_var1[3],m_var2[3],m_var3[3] }, A12[3] = { m_var1[1] ,m_var2[1] ,m_var3[1] }, A22[3] = { m_var1[0] ,m_var2[0] ,m_var3[0] };
	double x_bar[3] = { m_mean1[0],m_mean2[0],m_mean3[0] }, y_bar[3] = { m_mean1[1],m_mean2[1],m_mean3[1] };
	int count[3] = { m_Count1, m_Count2, m_Count3 };
	COLORREF m_color = RGB(255, 255, 0);
	for (int i = 0; i < 3; i++)
	{
		w21 = (A11[i % 3] - A11[(i + 1) % 3]) / 2;
		w22 = (A22[i % 3] - A22[(i + 1) % 3]) / 2;
		w23 = A12[(i + 1) % 3] - A12[i % 3];
		w11 = (A12[i % 3] * y_bar[i % 3] - A11[i % 3] * x_bar[i % 3]) - (A12[(i + 1) % 3] * y_bar[(i + 1) % 3] - A11[(i + 1) % 3] * x_bar[(i + 1) % 3]);
		w12 = (A12[i % 3] * x_bar[i % 3] - A22[i % 3] * y_bar[i % 3]) - (A12[(i + 1) % 3] * x_bar[(i + 1) % 3] - A22[(i + 1) % 3] * y_bar[(i + 1) % 3]);
		w0 = 1 / 2 * log((A11[i % 3] * A22[i % 3] - pow(A12[i % 3], 2)) / (A11[(i + 1) % 3] * A22[(i + 1) % 3] - pow(A12[(i + 1) % 3], 2))) - log(count[i % 3] / count[(i + 1) % 3]);
	
		switch (i)
		{
		case 1:
			m_color = RGB(0, 255, 255);
			break;
		case 2:
			m_color = RGB(255, 0, 255);
			break;
		default:
			break;
		}

		double A = w22, B, C;
		CPoint m_OldPt, m_CurrentPt;
		for (int j = -400; j <= 400; j++)
		{
			double x = (double)j / 100, y;
			B = w12 + w23*x;
			C = w21*x*x + w11*x + w0;

			if ((B == 0) && (C == 0) && (A == 0))
			{
				pDC->MoveTo((int)(x * 100), -500);
				pDC->LineTo((int)(x * 100), 500);
			}

			if (B)
			{
				if (fabs(A)<1e-06)
				{
					y = -C / B;
				}
				else
				{
					double d = B*B - 4 * A*C;
					if (d < 0)
						continue;
					y = (sqrt(d) - B) / (2 * A);
				}

				m_CurrentPt.x = (int)(x * 100);
				m_CurrentPt.y = (int)(y * 100);
				/*
				if (j == -400)
				{
					m_OldPt = m_CurrentPt;
					continue;
				}
				else
				{
					pDC->MoveTo(m_OldPt);
					pDC->LineTo(m_CurrentPt);
				}
				m_OldPt = m_CurrentPt;
				*/
				pDC->SetPixel(m_CurrentPt, m_color);
			}
		}
	}
}
