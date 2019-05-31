
// ISODATAView.cpp : CISODATAView 类的实现
//

#include "stdafx.h"
#include "DoublePt.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ISODATA_Parameter, &CISODATAView::OnIsodataParameter)
	ON_COMMAND(ID_ISODATA_Input, &CISODATAView::OnIsodataInput)
	ON_COMMAND(ID_ISODATA_Output, &CISODATAView::OnIsodataOutput)
END_MESSAGE_MAP()

// CISODATAView 构造/析构

CISODATAView::CISODATAView()
{
	// TODO: 在此处添加构造代码

}

CISODATAView::~CISODATAView()
{
}

BOOL CISODATAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CISODATAView 绘制

void CISODATAView::OnDraw(CDC* /*pDC*/)
{
	CISODATADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CISODATAView 打印

BOOL CISODATAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CISODATAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CISODATAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CISODATAView 诊断

#ifdef _DEBUG
void CISODATAView::AssertValid() const
{
	CView::AssertValid();
}

void CISODATAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CISODATADoc* CISODATAView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CISODATADoc)));
	return (CISODATADoc*)m_pDocument;
}
#endif //_DEBUG


// CISODATAView 消息处理程序

#include "ParaDlg.h"
void CISODATAView::OnIsodataParameter()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
