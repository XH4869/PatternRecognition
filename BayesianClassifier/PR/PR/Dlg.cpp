// Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PR.h"
#include "Dlg.h"
#include "afxdialogex.h"


// CDlg �Ի���

IMPLEMENT_DYNAMIC(CDlg, CDialogEx)

CDlg::CDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_x(0)
	, m_y(0)
{

}

CDlg::~CDlg()
{
}

void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
}


BEGIN_MESSAGE_MAP(CDlg, CDialogEx)
END_MESSAGE_MAP()


// CDlg ��Ϣ�������
