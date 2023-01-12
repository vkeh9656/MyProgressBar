
// MyProgressBar.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MyProgressBar.h"
#include "MyProgressBarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyProgressBarApp

BEGIN_MESSAGE_MAP(CMyProgressBarApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyProgressBarApp 생성

CMyProgressBarApp::CMyProgressBarApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMyProgressBarApp 개체입니다.

CMyProgressBarApp theApp;


// CMyProgressBarApp 초기화

BOOL CMyProgressBarApp::InitInstance()
{
	CWinApp::InitInstance();

	CMyProgressBarDlg dlg;
	dlg.DoModal();
	return FALSE;
}

