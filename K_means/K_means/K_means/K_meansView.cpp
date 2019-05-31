
// K_meansView.cpp : CK_meansView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Input, &CK_meansView::OnInput)
	ON_COMMAND(ID_Output, &CK_meansView::OnOutput)
END_MESSAGE_MAP()

// CK_meansView 构造/析构

CK_meansView::CK_meansView()
{
	// TODO: 在此处添加构造代码

}

CK_meansView::~CK_meansView()
{
}

BOOL CK_meansView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CK_meansView 绘制

void CK_meansView::OnDraw(CDC* /*pDC*/)
{
	CK_meansDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CK_meansView 打印

BOOL CK_meansView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CK_meansView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CK_meansView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CK_meansView 诊断

#ifdef _DEBUG
void CK_meansView::AssertValid() const
{
	CView::AssertValid();
}

void CK_meansView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK_meansDoc* CK_meansView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK_meansDoc)));
	return (CK_meansDoc*)m_pDocument;
}
#endif //_DEBUG


// CK_meansView 消息处理程序

#include "MyDlg.h"
void CK_meansView::OnInput()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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