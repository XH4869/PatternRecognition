
// LineryClassificationView.cpp : CLineryClassificationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LineryClassification.h"
#endif

#include "LineryClassificationDoc.h"
#include "LineryClassificationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLineryClassificationView

IMPLEMENT_DYNCREATE(CLineryClassificationView, CView)

BEGIN_MESSAGE_MAP(CLineryClassificationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CLineryClassificationView::OnType1)
	ON_COMMAND(ID_32772, &CLineryClassificationView::OnType2)
	ON_COMMAND(ID_32773, &CLineryClassificationView::OnType3)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CLineryClassificationView 构造/析构

CLineryClassificationView::CLineryClassificationView()
	: m_x1(0)
	, m_x2(0)
{
	// TODO: 在此处添加构造代码

}

CLineryClassificationView::~CLineryClassificationView()
{
}

BOOL CLineryClassificationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLineryClassificationView 绘制

void CLineryClassificationView::OnDraw(CDC* pDC)
{
	CLineryClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->TextOutW(0, 0, _T("红色代表w1，绿色代表w2，蓝色代表w3"));
	pDC->TextOutW(0, 20, _T("单击右键可刷新画布"));
}


// CLineryClassificationView 打印

BOOL CLineryClassificationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLineryClassificationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLineryClassificationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CLineryClassificationView 诊断

#ifdef _DEBUG
void CLineryClassificationView::AssertValid() const
{
	CView::AssertValid();
}

void CLineryClassificationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLineryClassificationDoc* CLineryClassificationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLineryClassificationDoc)));
	return (CLineryClassificationDoc*)m_pDocument;
}
#endif //_DEBUG


// CLineryClassificationView 消息处理程序


void CLineryClassificationView::OnType1()
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

	double g1, g2, g3;
	CPen *pOldPen, NewPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&NewPen);

	pDC->MoveTo(0, -500); pDC->LineTo(0, 500);
	pDC->MoveTo(-450, 500); pDC->LineTo(500, -450);
	pDC->MoveTo(-450, -500); pDC->LineTo(500, 450);

	for (int i = -400; i <= 500; i++)
	{
		for (int j = -450; j <= 450; j++)
		{
			m_x1 = (double)i / 50;
			m_x2 = (double)j / 50;
			g1 = -m_x1; g2 = m_x1 + m_x2 - 1; g3 = m_x1 - m_x2 - 1;
			if (g1 > 0 && g2 < 0 && g3 < 0)
				pDC->SetPixel(i, j, RGB(255, 0, 0));
			if (g1 < 0 && g2 > 0 && g3 < 0)
				pDC->SetPixel(i, j, RGB(0, 255, 0));
			if (g1 < 0 && g2 < 0 && g3 > 0)
				pDC->SetPixel(i, j, RGB(0, 0, 255));
		}
	}
	pDC->SelectObject(pOldPen);
}


void CLineryClassificationView::OnType2()
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

	double g12, g23, g13;
	CPen *pOldPen, NewPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&NewPen);

	pDC->MoveTo(0, -500); pDC->LineTo(0, 500);
	pDC->MoveTo(-450, 500); pDC->LineTo(500, -450);
	pDC->MoveTo(-450, -500); pDC->LineTo(500, 450);

	for (int i = -400; i <= 500; i++)
	{
		for (int j = -450; j <= 450; j++)
		{
			m_x1 = (double)i / 50;
			m_x2 = (double)j / 50;
			g12 = -m_x1; g23 = m_x1 + m_x2 - 1; g13 = -m_x1 + m_x2 + 1;
			if (g12 > 0 && g13 > 0)
				pDC->SetPixel(i, j, RGB(255, 0, 0));
			if (g12 < 0 && g23 > 0)
				pDC->SetPixel(i, j, RGB(0, 255, 0));
			if (g13 < 0 && g23 < 0)
				pDC->SetPixel(i, j, RGB(0, 0, 255));
		}
	}
	pDC->SelectObject(pOldPen);
}


void CLineryClassificationView::OnType3()
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

	double g1, g2, g3;
	CPen *pOldPen, NewPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&NewPen);

	pDC->MoveTo(0, -500); pDC->LineTo(0, 500);
	pDC->MoveTo(-450, 500); pDC->LineTo(500, -450);
	pDC->MoveTo(-450, -500); pDC->LineTo(500, 450);

	for (int i = -400; i <= 500; i++)
	{
		for (int j = -450; j <= 450; j++)
		{
			m_x1 = (double)i / 50;
			m_x2 = (double)j / 50;
			g1 = -m_x1; g2 = m_x1 + m_x2 - 1; g3 = m_x1 - m_x2 - 1;
			if (g1 > g2 && g1 > g3)
				pDC->SetPixel(i, j, RGB(255, 0, 0));
			if (g2 > g1 && g2 > g3)
				pDC->SetPixel(i, j, RGB(0, 255, 0));
			if (g3 > g1 && g3 > g2)
				pDC->SetPixel(i, j, RGB(0, 0, 255));
		}
	}
	pDC->SelectObject(pOldPen);
}


void CLineryClassificationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}
