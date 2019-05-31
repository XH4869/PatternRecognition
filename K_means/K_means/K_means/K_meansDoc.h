
// K_meansDoc.h : CK_meansDoc ��Ľӿ�
//

#include "DoublePt.h"
#pragma once


class CK_meansDoc : public CDocument
{
protected: // �������л�����
	CK_meansDoc();
	DECLARE_DYNCREATE(CK_meansDoc)

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
	virtual ~CK_meansDoc();
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
	int m_PtCount;//ͳ��������ĸ���
	CPoint m_Pt[25];//�洢������
	CPoint m_K1[25];//����1���
	CPoint m_K2[25];//����2���
	int m_N1;//����1���ĸ���
	int m_N2;//����2���ĸ���
			 // ʹ��K��ֵ���࣬K=2
	void K_Means();
	double GetDist(CDoublePt Center, CPoint Point);
};
