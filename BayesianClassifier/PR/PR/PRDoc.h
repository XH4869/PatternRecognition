
// PRDoc.h : CPRDoc ��Ľӿ�
//


#pragma once
#include "atltypes.h"


class CPRDoc : public CDocument
{
protected: // �������л�����
	CPRDoc();
	DECLARE_DYNCREATE(CPRDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CPRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_Count1;
	int m_Count2;
	int m_Count3;
	CPoint Pt1[10];
	CPoint Pt2[10];
	CPoint Pt3[10];
	double m_mean1[2];
	double m_mean2[2];
	double m_mean3[2];
	double m_var1[4];
	double m_var2[4];
	double m_var3[4];
	void Calculate();
	double w21;
	double w22;
	double w11;
	double w12;
	double w0;
	void CountCoefficient2(CDC *pDC);
	double w23;
	int m_IsCovEqual;
	void CountCoefficient3(CDC *pDC);
	CPoint m_TestPt[10];
	int m_CountTestPt;
};
