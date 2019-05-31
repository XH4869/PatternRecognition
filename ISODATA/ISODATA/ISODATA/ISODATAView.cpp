
// ISODATAView.cpp : CISODATAView ���ʵ��
//

#include "stdafx.h"
#include "DoublePt.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ISODATA.h"
#endif

#include "ISODATADoc.h"
#include "ISODATAView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CISODATAView

IMPLEMENT_DYNCREATE(CISODATAView, CView)

BEGIN_MESSAGE_MAP(CISODATAView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ISODATA_Parameter, &CISODATAView::OnIsodataParameter)
	ON_COMMAND(ID_ISODATA_Input, &CISODATAView::OnIsodataInput)
	ON_COMMAND(ID_ISODATA_Output, &CISODATAView::OnIsodataOutput)
END_MESSAGE_MAP()

// CISODATAView ����/����

CISODATAView::CISODATAView()
{
	// TODO: �ڴ˴���ӹ������

}

CISODATAView::~CISODATAView()
{
}

BOOL CISODATAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CISODATAView ����

void CISODATAView::OnDraw(CDC* /*pDC*/)
{
	CISODATADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CISODATAView ��ӡ

BOOL CISODATAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CISODATAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CISODATAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CISODATAView ���

#ifdef _DEBUG
void CISODATAView::AssertValid() const
{
	CView::AssertValid();
}

void CISODATAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CISODATADoc* CISODATAView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CISODATADoc)));
	return (CISODATADoc*)m_pDocument;
}
#endif //_DEBUG


// CISODATAView ��Ϣ�������

#include "ParaDlg.h"
void CISODATAView::OnIsodataParameter()
{
	// TODO: �ڴ���������������
	CParaDlg dlg;
	CISODATADoc *pDoc = GetDocument();

	if (dlg.DoModal() == IDOK)
	{
		UpdateData(true);
		pDoc->m_K = dlg.K;
		pDoc->m_SigmaN = dlg.Sigma_N;
		pDoc->m_SigmaS = dlg.Sigma_S;
		pDoc->m_SigmaC = dlg.Sigma_C;
		pDoc->m_L = dlg.L;
		pDoc->m_I = dlg.I;
		pDoc->m_C = dlg.m_C;
	}
}

#include "PtDlg.h"
void CISODATAView::OnIsodataInput()
{
	// TODO: �ڴ���������������
	CPtDlg dlg;
	CISODATADoc *pDoc = GetDocument();

	if (dlg.DoModal() == IDOK)
	{
		UpdateData(true);
		pDoc->m_Pt[pDoc->m_PtCount].x = dlg.x;
		pDoc->m_Pt[pDoc->m_PtCount++].y = dlg.y;
	}
}


void CISODATAView::OnIsodataOutput()
{
	// TODO: �ڴ���������������
	CISODATADoc *pDoc = GetDocument();
	pDoc->IsoData();
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	COLORREF color[5] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255),RGB(255,255,0),RGB(255,0,255) };

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(1000, -1000);

	pDC->MoveTo(-500, 0);
	pDC->LineTo(500, 0);
	pDC->MoveTo(0, -500);
	pDC->LineTo(0, 500);

	CPoint point;
	CBrush NewBrush, *pOldBrush;
	NewBrush.CreateSolidBrush(color[0]);
	pOldBrush = pDC->SelectObject(&NewBrush);
	for (int i = 0; i < pDoc->m_C; i++)
	{
		for (int j = 0; j < pDoc->m_CenterNum[i]; j++)
		{
			point = pDoc->p_Pt[i][j];
			int x = point.x * 50, y = point.y * 50;
			pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
		}
		NewBrush.DeleteObject();
		NewBrush.CreateSolidBrush(color[i + 1]);
		pDC->SelectObject(NewBrush);
	}
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();

	if (pDoc->m_CenterNum) delete[] pDoc->m_CenterNum;
	for (int i = 0; i < pDoc->m_C; i++)
		if (pDoc->p_Pt[i]) delete[] pDoc->p_Pt[i];
	if (pDoc->p_Pt) delete[] pDoc->p_Pt;
}
