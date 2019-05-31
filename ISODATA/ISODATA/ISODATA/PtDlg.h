#pragma once


// CPtDlg 对话框

class CPtDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPtDlg)

public:
	CPtDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPtDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int x;
	int y;
};
