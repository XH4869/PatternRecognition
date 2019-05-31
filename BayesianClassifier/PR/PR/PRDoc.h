
// PRDoc.h : CPRDoc 类的接口
//


#pragma once
#include "atltypes.h"


class CPRDoc : public CDocument
{
protected: // 仅从序列化创建
	CPRDoc();
	DECLARE_DYNCREATE(CPRDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CPRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
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
