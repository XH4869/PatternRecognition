#pragma once


// CPtDlg �Ի���

class CPtDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPtDlg)

public:
	CPtDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPtDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int x;
	int y;
};
