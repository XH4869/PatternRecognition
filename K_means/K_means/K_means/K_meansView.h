
// K_meansView.h : CK_meansView ��Ľӿ�
//

#pragma once


class CK_meansView : public CView
{
protected: // �������л�����
	CK_meansView();
	DECLARE_DYNCREATE(CK_meansView)

// ����
public:
	CK_meansDoc* GetDocument() const;

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
	virtual ~CK_meansView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInput();
	afx_msg void OnOutput();
};

#ifndef _DEBUG  // K_meansView.cpp �еĵ��԰汾
inline CK_meansDoc* CK_meansView::GetDocument() const
   { return reinterpret_cast<CK_meansDoc*>(m_pDocument); }
#endif

