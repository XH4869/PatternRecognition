// PtDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ISODATA.h"
#include "PtDlg.h"
#include "afxdialogex.h"


// CPtDlg �Ի���

IMPLEMENT_DYNAMIC(CPtDlg, CDialogEx)

CPtDlg::CPtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, x(0)
	, y(0)
{

}

CPtDlg::~CPtDlg()
{
}

void CPtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, x);
	DDX_Text(pDX, IDC_Y, y);
}


BEGIN_MESSAGE_MAP(CPtDlg, CDialogEx)
END_MESSAGE_MAP()


// CPtDlg ��Ϣ�������
