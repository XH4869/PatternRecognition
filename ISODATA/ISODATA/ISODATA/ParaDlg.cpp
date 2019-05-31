// ParaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ISODATA.h"
#include "ParaDlg.h"
#include "afxdialogex.h"


// CParaDlg 对话框

IMPLEMENT_DYNAMIC(CParaDlg, CDialogEx)

CParaDlg::CParaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, K(0)
	, Sigma_N(0)
	, Sigma_S(0)
	, Sigma_C(0)
	, L(0)
	, I(0)
	, m_C(0)
{

}

CParaDlg::~CParaDlg()
{
}

void CParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_K, K);
	DDX_Text(pDX, IDC_Sigma_N, Sigma_N);
	DDX_Text(pDX, IDC_Sigma_S, Sigma_S);
	DDX_Text(pDX, IDC_Sigma_C, Sigma_C);
	DDX_Text(pDX, IDC_L, L);
	DDX_Text(pDX, IDC_I, I);
	DDX_Text(pDX, IDC_C, m_C);
}


BEGIN_MESSAGE_MAP(CParaDlg, CDialogEx)
END_MESSAGE_MAP()


// CParaDlg 消息处理程序
