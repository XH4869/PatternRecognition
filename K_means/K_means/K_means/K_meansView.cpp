
// K_meansView.cpp : CK_meansView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "K_means.h"
#endif

#include "K_meansDoc.h"
#include "K_meansView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CK_meansView

IMPLEMENT_DYNCREATE(CK_meansView, CView)

BEGIN_MESSAGE_MAP(CK_meansView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Input, &CK_meansView::OnInput)
	ON_COMMAND(ID_Output, &CK_meansView::OnOutput)
END_MESSAGE_MAP()

// CK_meansView ����/����

CK_meansView::CK_meansView()
{
	// TODO: �ڴ˴���ӹ������

}

CK_meansView::~CK_meansView()
{
}

BOOL CK_meansView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CK_meansView ����

void CK_meansView::OnDraw(CDC* /*pDC*/)
{
	CK_meansDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CK_meansView ��ӡ

BOOL CK_meansView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CK_meansView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CK_meansView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CK_meansView ���

#ifdef _DEBUG
void CK_meansView::AssertValid() const
{
	CView::AssertValid();
}

void CK_meansView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK_meansDoc* CK_meansView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK_meansDoc)));
	return (CK_meansDoc*)m_pDocument;
}
#endif //_DEBUG


// CK_meansView ��Ϣ�������

#include "MyDlg.h"
void CK_meansView::OnInput()
{
	// TODO: �ڴ���������������
	CK_meansDoc *pDoc = GetDocument();
	CMyDlg dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		pDoc->m_Pt[pDoc->m_PtCount].x = dlg.m_x;
		pDoc->m_Pt[pDoc->m_PtCount].y = dlg.m_y;
		pDoc->m_PtCount++;
	}
}


void CK_meansView::OnOutput()
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

	CK_meansDoc *pDoc = GetDocument();
	pDoc->K_Means();

	CPoint point;
	CBrush *pOldBrush, NewBrush;
	NewBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);

	for (int i = 0; i < pDoc->m_N1; i++)
	{
		int x, y;
		point = pDoc->m_K1[i];
		x = 50 * point.x;
		y = 50 * point.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	NewBrush.DeleteObject();
	NewBrush.CreateSolidBrush(RGB(0, 255, 0));
	pDC->SelectObject(&NewBrush);
	for (int i = 0; i < pDoc->m_N2; i++)
	{
		int x, y;
		point = pDoc->m_K2[i];
		x = 50 * point.x;
		y = 50 * point.y;
		pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
	}

	pDC->SelectObject(pOldBrush);
}