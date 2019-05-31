
// K_meansDoc.h : CK_meansDoc 类的接口
//

#include "DoublePt.h"
#pragma once


class CK_meansDoc : public CDocument
{
protected: // 仅从序列化创建
	CK_meansDoc();
	DECLARE_DYNCREATE(CK_meansDoc)

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
	virtual ~CK_meansDoc();
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
	int m_PtCount;//统计样本点的个数
	CPoint m_Pt[25];//存储样本点
	CPoint m_K1[25];//样本1类点
	CPoint m_K2[25];//样本2类点
	int m_N1;//样本1类点的个数
	int m_N2;//样本2类点的个数
			 // 使用K均值聚类，K=2
	void K_Means();
	double GetDist(CDoublePt Center, CPoint Point);
};
