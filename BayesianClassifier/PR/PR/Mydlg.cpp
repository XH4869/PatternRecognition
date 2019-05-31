// Mydlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PR.h"
#include "Mydlg.h"
#include "afxdialogex.h"


// CMydlg 对话框

IMPLEMENT_DYNAMIC(CMydlg, CDialogEx)

CMydlg::CMydlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_x(0)
	, m_y(0)
	, m_IsChosen(-1)
	, m_IsCovEqual(-1)
{

}

CMydlg::~CMydlg()
{
}

void CMydlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
	DDX_Radio(pDX, IDC_RADIO3, m_IsChosen);
	DDX_Radio(pDX, IDC_RADIO1, m_IsCovEqual);
}


BEGIN_MESSAGE_MAP(CMydlg, CDialogEx)

	ON_BN_CLICKED(IDC_RADIO3, &CMydlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMydlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO5, &CMydlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO1, &CMydlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMydlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CMydlg 消息处理程序


BOOL CMydlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CMydlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}


void CMydlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}
