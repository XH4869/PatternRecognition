#pragma once


// CParaDlg �Ի���

class CParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParaDlg)

public:
	CParaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParaDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����������
	int K;
	// һ���������Ӧ���е�������Ŀ
	int Sigma_N;
	// һ�����������׼����ֵ
	double Sigma_S;
	// ��������֮��������ֵ
	double Sigma_C;
	// ��һ�ε����п��Թ鲢������������
	int L;
	// ���������������
	int I;
	int m_C;
};
