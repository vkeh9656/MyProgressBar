﻿
// MyProgressBarDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MyProgressBar.h"
#include "MyProgressBarDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyProgressBarDlg 대화 상자



CMyProgressBarDlg::CMyProgressBarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYPROGRESSBAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyProgressBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MY_PROGRESS, m_my_progress);
}

BEGIN_MESSAGE_MAP(CMyProgressBarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyProgressBarDlg 메시지 처리기

BOOL CMyProgressBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	GetDlgItem(IDC_USER_RECT)->GetWindowRect(m_user_rect); // Picture Control의 좌표
	ScreenToClient(m_user_rect);	// 캡션 크기만큼 보정

	SetTimer(1, 50, NULL); // WM_TIMER Message 발생

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyProgressBarDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		int pos = m_my_progress.GetPos() * (200 / 100);

		dc.FillSolidRect(pos, 0, 200, 30, RGB(0, 80, 160));
		dc.FillSolidRect(0, 0, pos, 30, RGB(0, 160, 255));

		pos = m_my_progress.GetPos() * m_user_rect.Width() / 100;

		dc.FillSolidRect(m_user_rect.left + pos, m_user_rect.top, 
			m_user_rect.Width(), m_user_rect.Height(), RGB(0, 80, 160));
		dc.FillSolidRect(m_user_rect.left, m_user_rect.top,
			pos, m_user_rect.Height(), RGB(0, 160, 255));
		
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyProgressBarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyProgressBarDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		int pos = m_my_progress.GetPos();
		// pos = (pos + 1) % 101;
		m_my_progress.SetPos((pos + 1) % 101);

		InvalidateRect(CRect(0, 0, 200, 30), FALSE);
		InvalidateRect(m_user_rect, 1);
	}
	else
	{
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMyProgressBarDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}
