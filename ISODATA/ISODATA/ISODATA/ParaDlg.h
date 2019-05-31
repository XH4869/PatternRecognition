#pragma once


// CParaDlg 对话框

class CParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParaDlg)

public:
	CParaDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParaDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 聚类中心数
	int K;
	// 一个类别至少应具有的样本数目
	int Sigma_N;
	// 一个类别样本标准差阈值
	double Sigma_S;
	// 聚类中心之间距离的阈值
	double Sigma_C;
	// 在一次迭代中可以归并的类别的最多对数
	int L;
	// 允许迭代的最多次数
	int I;
	int m_C;
};
