// Mydlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PR.h"
#include "Mydlg.h"
#include "afxdialogex.h"


// CMydlg �Ի���

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


// CMydlg ��Ϣ�������


BOOL CMydlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CMydlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
}


void CMydlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
}
