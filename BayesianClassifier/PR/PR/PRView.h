
// PRView.h : CPRView ��Ľӿ�
//

#pragma once


class CPRView : public CView
{
protected: // �������л�����
	CPRView();
	DECLARE_DYNCREATE(CPRView)

// ����
public:
	CPRDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void On32773();
	afx_msg void On32776();
	afx_msg void OnTest();
};

#ifndef _DEBUG  // PRView.cpp �еĵ��԰汾
inline CPRDoc* CPRView::GetDocument() const
   { return reinterpret_cast<CPRDoc*>(m_pDocument); }
#endif

