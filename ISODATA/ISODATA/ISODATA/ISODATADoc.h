
// ISODATADoc.h : CISODATADoc ��Ľӿ�
//


#pragma once
#include "DoublePt.h"
#include <vector>
using namespace std;
class CISODATADoc : public CDocument
{
protected: // �������л�����
	CISODATADoc();
	DECLARE_DYNCREATE(CISODATADoc)

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
	virtual ~CISODATADoc();
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
	int m_K;
	int m_SigmaN;
	double m_SigmaS;
	double m_SigmaC;
	int m_L;
	int m_I;
	// ��������
	int m_PtCount;
	CPoint m_Pt[20];
	int m_C;
	void IsoData();
	vector<CDoublePt> m_CenterPt;
	int* m_CenterNum;
	double GetDist(CPoint point, CDoublePt center);
	CPoint** p_Pt;
	double* m_DistArr;
	double m_TotalDist;
	void Split();
	double GetCenterDist(CDoublePt z1, CDoublePt z2);
};
