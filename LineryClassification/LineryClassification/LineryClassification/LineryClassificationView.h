
// LineryClassificationView.h : CLineryClassificationView ��Ľӿ�
//

#pragma once


class CLineryClassificationView : public CView
{
protected: // �������л�����
	CLineryClassificationView();
	DECLARE_DYNCREATE(CLineryClassificationView)

// ����
public:
	CLineryClassificationDoc* GetDocument() const;

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
	virtual ~CLineryClassificationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // LineryClassificationView.cpp �еĵ��԰汾
inline CLineryClassificationDoc* CLineryClassificationView::GetDocument() const
   { return reinterpret_cast<CLineryClassificationDoc*>(m_pDocument); }
#endif

