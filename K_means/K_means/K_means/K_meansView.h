
// K_meansView.h : CK_meansView 类的接口
//

#pragma once


class CK_meansView : public CView
{
protected: // 仅从序列化创建
	CK_meansView();
	DECLARE_DYNCREATE(CK_meansView)

// 特性
public:
	CK_meansDoc* GetDocument() const;

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
	virtual ~CK_meansView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInput();
	afx_msg void OnOutput();
};

#ifndef _DEBUG  // K_meansView.cpp 中的调试版本
inline CK_meansDoc* CK_meansView::GetDocument() const
   { return reinterpret_cast<CK_meansDoc*>(m_pDocument); }
#endif

