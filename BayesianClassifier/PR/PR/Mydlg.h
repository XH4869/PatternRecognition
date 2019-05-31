#pragma once


// CMydlg 对话框

class CMydlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMydlg)

public:
	CMydlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMydlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_x;
	int m_y;
	virtual BOOL OnInitDialog();
	int m_IsChosen;
	afx_msg void OnBnClickedRadio3();
	int m_IsCovEqual;
	afx_msg void OnBnClickedRadio1();
};
