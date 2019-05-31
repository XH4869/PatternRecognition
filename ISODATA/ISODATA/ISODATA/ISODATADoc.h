
// ISODATADoc.h : CISODATADoc 类的接口
//


#pragma once
#include "DoublePt.h"
#include <vector>
using namespace std;
class CISODATADoc : public CDocument
{
protected: // 仅从序列化创建
	CISODATADoc();
	DECLARE_DYNCREATE(CISODATADoc)

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
	virtual ~CISODATADoc();
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
	int m_K;
	int m_SigmaN;
	double m_SigmaS;
	double m_SigmaC;
	int m_L;
	int m_I;
	// 样本总数
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
