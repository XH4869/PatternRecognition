
// K_meansDoc.cpp : CK_meansDoc 类的实现
//

#include "stdafx.h"
#include "DoublePt.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "K_means.h"
#endif

#include "K_meansDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CK_meansDoc

IMPLEMENT_DYNCREATE(CK_meansDoc, CDocument)

BEGIN_MESSAGE_MAP(CK_meansDoc, CDocument)
END_MESSAGE_MAP()


// CK_meansDoc 构造/析构

CK_meansDoc::CK_meansDoc()
	: m_PtCount(0)
	, m_N1(0)
	, m_N2(0)
{
	// TODO: 在此添加一次性构造代码

}

CK_meansDoc::~CK_meansDoc()
{
}

BOOL CK_meansDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CK_meansDoc 序列化

void CK_meansDoc::Serialize(CArchive& ar)
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
void CK_meansDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CK_meansDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CK_meansDoc::SetSearchContent(const CString& value)
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

// CK_meansDoc 诊断

#ifdef _DEBUG
void CK_meansDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CK_meansDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CK_meansDoc 命令


// 使用K均值聚类，K=2
void CK_meansDoc::K_Means()
{
	CDoublePt Z1_old, Z1_new, Z2_old, Z2_new;
	Z1_new = m_Pt[0]; Z2_new = m_Pt[9];
	
	while (Z1_old != Z1_new || Z2_old != Z2_new)
	{
		Z1_old = Z1_new; Z2_old = Z2_new;
		m_N1 = m_N2 = 0;
		
		double d1, d2;
		for (int i = 0; i < m_PtCount; i++)
		{
			d1 = GetDist(Z1_old, m_Pt[i]);
			d2 = GetDist(Z2_old, m_Pt[i]);
			if (d1 < d2)
				m_K1[m_N1++] = m_Pt[i];
			else
				m_K2[m_N2++] = m_Pt[i];
		}
		
		double sum_x = 0, sum_y = 0;
		for (int i = 0; i < m_N1; i++)
		{
			sum_x += m_K1[i].x;
			sum_y += m_K1[i].y;
		}
		Z1_new.x = sum_x / (double)m_N1;
		Z1_new.y = sum_y / (double)m_N1;

		sum_x = sum_y = 0;
		for (int i = 0; i < m_N2; i++)
		{
			sum_x += m_K2[i].x;
			sum_y += m_K2[i].y;
		}
		Z2_new.x = sum_x / (double)m_N2;
		Z2_new.y = sum_y / (double)m_N2;
	}
}


double CK_meansDoc::GetDist(CDoublePt Center, CPoint Point)
{
	double dx, dy;
	dx = Center.x - (double)Point.x;
	dy = Center.y - (double)Point.y;
	return dx*dx + dy*dy;
}
