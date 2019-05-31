
// PRView.h : CPRView 类的接口
//

#pragma once


class CPRView : public CView
{
protected: // 仅从序列化创建
	CPRView();
	DECLARE_DYNCREATE(CPRView)

// 特性
public:
	CPRDoc* GetDocument() const;

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
	virtual ~CPRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void On32773();
	afx_msg void On32776();
	afx_msg void OnTest();
};

#ifndef _DEBUG  // PRView.cpp 中的调试版本
inline CPRDoc* CPRView::GetDocument() const
   { return reinterpret_cast<CPRDoc*>(m_pDocument); }
#endif

