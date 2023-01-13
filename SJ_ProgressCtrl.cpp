// SJ_ProgressCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "MyProgressBar.h"
#include "SJ_ProgressCtrl.h"


// SJ_ProgressCtrl

IMPLEMENT_DYNAMIC(SJ_ProgressCtrl, CWnd)

SJ_ProgressCtrl::SJ_ProgressCtrl()
{
	m_pos = 0;
	m_min = 0;
	m_max = 100;

	m_bk_color = RGB(0, 80, 160);
	m_fore_color = RGB(0, 160, 255);
}

SJ_ProgressCtrl::~SJ_ProgressCtrl()
{
}

void SJ_ProgressCtrl::CreateProgress(CWnd* ap_parent, CRect a_rect, int a_ctrl_id)
{
	Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, a_rect, ap_parent, a_ctrl_id);
}

void SJ_ProgressCtrl::CreateProgress(CWnd* ap_parent, int a_guide_ctrl_id, int a_ctrl_id)
{
	CRect r;
	ap_parent->GetDlgItem(a_guide_ctrl_id)->GetWindowRect(r);
	ap_parent->ScreenToClient(r);
	CreateProgress(ap_parent, r, a_ctrl_id);
}

void SJ_ProgressCtrl::SetRange(int a_min, int a_max)
{
	if (a_max == a_min) return;

	if (a_max < a_min)
	{
		m_max = a_min;
		m_min = a_max;
	}
	else
	{
		m_max = a_max;
		m_min = a_min;
	}

	m_min = a_min;
	m_max = a_max;
}

void SJ_ProgressCtrl::SetPos(int a_pos)
{
	m_pos = a_pos;
	if (m_pos < m_min) m_pos = m_min;
	else if (m_pos > m_max) m_pos = m_max;
}


int SJ_ProgressCtrl::GetPos() { return m_pos; }

void SJ_ProgressCtrl::SetColor(COLORREF a_bk_color, COLORREF a_fore_color)
{
	m_bk_color = a_bk_color;
	m_fore_color = a_fore_color;
}

BEGIN_MESSAGE_MAP(SJ_ProgressCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// SJ_ProgressCtrl 메시지 처리기
void SJ_ProgressCtrl::OnPaint()
{
	CPaintDC dc(this); 
	
	CDC *p_dc = m_mem_image.GetDC();
	int pos = m_pos * m_width / (m_max - m_min);

	p_dc->FillSolidRect(0, 0, m_width - pos, m_height, m_bk_color);
	p_dc->FillSolidRect(0, 0, pos, m_height, m_fore_color);

	m_mem_image.Draw(&dc, 0, 0);
	
}


int SJ_ProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	CRect r;
	GetClientRect(r);

	m_width = r.Width();
	m_height = r.Height();

	m_mem_image.Create(this, m_width, m_height);

	return 0;
}
