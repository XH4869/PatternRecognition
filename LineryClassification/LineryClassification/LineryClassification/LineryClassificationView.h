
// LineryClassificationView.h : CLineryClassificationView 类的接口
//

#pragma once


class CLineryClassificationView : public CView
{
protected: // 仅从序列化创建
	CLineryClassificationView();
	DECLARE_DYNCREATE(CLineryClassificationView)

// 特性
public:
	CLineryClassificationDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLineryClassificationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	double m_x1;
	double m_x2;
	afx_msg void OnType1();
	afx_msg void OnType2();
	afx_msg void OnType3();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // LineryClassificationView.cpp 中的调试版本
inline CLineryClassificationDoc* CLineryClassificationView::GetDocument() const
   { return reinterpret_cast<CLineryClassificationDoc*>(m_pDocument); }
#endif

