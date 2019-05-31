
// PRView.cpp : CPRView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PR.h"
#endif

#include "PRDoc.h"
#include "PRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPRView

IMPLEMENT_DYNCREATE(CPRView, CView)

BEGIN_MESSAGE_MAP(CPRView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CPRView::On32771)
	ON_COMMAND(ID_32773, &CPRView::On32773)
	ON_COMMAND(ID_32776, &CPRView::On32776)
	ON_COMMAND(ID_Test, &CPRView::OnTest)
END_MESSAGE_MAP()

// CPRView ����/����

CPRView::CPRView()
{
	// TODO: �ڴ˴���ӹ������

}

CPRView::~CPRView()
{
}

BOOL CPRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPRView ����

void CPRView::OnDraw(CDC* pDC)
{
	CPRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	
}


// CPRView ��ӡ

BOOL CPRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPRView ���

#ifdef _DEBUG
void CPRView::AssertValid() const
{
	CView::AssertValid();
}

void CPRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPRDoc* CPRView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPRDoc)));
	return (CPRDoc*)m_pDocument;
}
#endif //_DEBUG


// CPRView ��Ϣ�������
#include "Mydlg.h"

void CPRView::On32771()
{
	// TODO: �ڴ���������������
	CMydlg dlg1;
	CPRDoc *pDoc = GetDocument();
	if (dlg1.DoModal() == IDOK)
	{
		UpdateData(true);
		if (dlg1.m_IsChosen == 0)
		{
			pDoc->Pt1[pDoc->m_Count1].x = dlg1.m_x;
			pDoc->Pt1[pDoc->m_Count1].y = dlg1.m_y;
			pDoc->m_Count1++;
		}
		if (dlg1.m_IsChosen == 1)
		{
			pDoc->Pt2[pDoc->m_Count2].x = dlg1.m_x;
			pDoc->Pt2[pDoc->m_Count2].y = dlg1.m_y;
			pDoc->m_Count2++;
		}
		if (dlg1.m_IsChosen == 2)
		{
			pDoc->Pt3[pDoc->m_Count3].x = dlg1.m_x;
			pDoc->Pt3[pDoc->m_Count3].y = dlg1.m_y;
			pDoc->m_Count3++;
		}
		pDoc->m_IsCovEqual = dlg1.m_IsCovEqual;
	}
}

#include <math.h>
void CPRView::On32773()
{
	// TODO: �ڴ���������������
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(1000, -1000);

	pDC->MoveTo(-500, 0);
	pDC->LineTo(500, 0);
	pDC->MoveTo(0, -500);
	pDC->LineTo(0, 500);
	
	CPoint m_TrainPt;
	CPRDoc *pDoc = GetDocument();
	CBrush *pOldBrush, NewBrush;
	NewBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);

	for (int i = 0; i < pDoc->m_Count1; i++)
	{
		int x, y;
		m_TrainPt = pDoc->Pt1[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	NewBrush.DeleteObject();
	NewBrush.CreateSolidBrush(RGB(0, 255, 0));
	pDC->SelectObject(NewBrush);
	for (int i = 0; i < pDoc->m_Count2; i++)
	{
		int x, y;
		m_TrainPt = pDoc->Pt2[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	NewBrush.DeleteObject();
	NewBrush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->SelectObject(NewBrush);
	for (int i = 0; i < pDoc->m_CountTestPt; i++)
	{
		int x, y;
		m_TrainPt = pDoc->m_TestPt[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}
	pDC->SelectObject(pOldBrush);

	pDoc->Calculate();
	pDoc->CountCoefficient2(pDC);
}


void CPRView::On32776()
{
	// TODO: �ڴ���������������
	CPRDoc *pDoc = GetDocument();
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(1000, -1000);

	pDC->MoveTo(-500, 0);
	pDC->LineTo(500, 0);
	pDC->MoveTo(0, -500);
	pDC->LineTo(0, 500);

	CPoint m_TrainPt;
	CBrush *pOldBrush, NewBrush;
	NewBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);

	for (int i = 0; i < pDoc->m_Count1; i++)
	{
		int x, y;
		m_TrainPt = pDoc->Pt1[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	NewBrush.DeleteObject();
	NewBrush.CreateSolidBrush(RGB(0, 255, 0));
	pDC->SelectObject(&NewBrush);
	for (int i = 0; i < pDoc->m_Count2; i++)
	{
		int x, y;
		m_TrainPt = pDoc->Pt2[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	NewBrush.DeleteObject();
	NewBrush.CreateSolidBrush(RGB(0, 0, 255));
	pDC->SelectObject(&NewBrush);
	for (int i = 0; i < pDoc->m_Count3; i++)
	{
		int x, y;
		m_TrainPt = pDoc->Pt3[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	NewBrush.DeleteObject();
	NewBrush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->SelectObject(NewBrush);
	for (int i = 0; i < pDoc->m_CountTestPt; i++)
	{
		int x, y;
		m_TrainPt = pDoc->m_TestPt[i];
		x = 100 * m_TrainPt.x;
		y = 100 * m_TrainPt.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}
	pDC->SelectObject(pOldBrush);
	
	pDoc->Calculate();
	pDoc->CountCoefficient3(pDC);
}

#include "Dlg.h"
void CPRView::OnTest()
{
	// TODO: �ڴ���������������
	CDlg dlg;
	CPRDoc *pDoc = GetDocument();

	if (dlg.DoModal() == IDOK)
	{
		UpdateData(true);
		pDoc->m_TestPt[pDoc->m_CountTestPt].x = dlg.m_x;
		pDoc->m_TestPt[pDoc->m_CountTestPt].y = dlg.m_y;
		pDoc->m_CountTestPt++;
	}
}
