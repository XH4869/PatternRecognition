
// K_means.h : K_means Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CK_meansApp:
// �йش����ʵ�֣������ K_means.cpp
//

class CK_meansApp : public CWinApp
{
public:
	CK_meansApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK_meansApp theApp;
