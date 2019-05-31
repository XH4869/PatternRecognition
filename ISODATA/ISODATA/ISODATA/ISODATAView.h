
// ISODATAView.h : CISODATAView ��Ľӿ�
//

#pragma once
#include "DoublePt.h"

class CISODATAView : public CView
{
protected: // �������л�����
	CISODATAView();
	DECLARE_DYNCREATE(CISODATAView)

// ����
public:
	CISODATADoc* GetDocument() const;

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
	virtual ~CISODATAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIsodataParameter();
	afx_msg void OnIsodataInput();
	afx_msg void OnIsodataOutput();
};

#ifndef _DEBUG  // ISODATAView.cpp �еĵ��԰汾
inline CISODATADoc* CISODATAView::GetDocument() const
   { return reinterpret_cast<CISODATADoc*>(m_pDocument); }
#endif

