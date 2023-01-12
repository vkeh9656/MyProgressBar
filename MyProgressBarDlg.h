
// MyProgressBarDlg.h: 헤더 파일
//

#pragma once

class SJ_ProgressCtrl
{
private:
	int m_pos, m_min, m_max;
	COLORREF m_bk_color, m_fore_color;
	CRect m_rect;

public:
	SJ_ProgressCtrl() : m_rect(0, 0, 100, 30)
	{
		m_pos = 0;
		m_min = 0;
		m_max = 100;
		m_bk_color = RGB(0, 80, 160);
		m_fore_color = RGB(0, 160, 255);
	}

	void Create(CWnd *ap_parent, int a_guide_ctrl_id)
	{
		ap_parent->GetDlgItem(a_guide_ctrl_id)->GetWindowRect(m_rect);
		ap_parent->ScreenToClient(m_rect);
	}
	void Create(CRect a_rect)
	{
		m_rect = a_rect;
	}

	CRect GetRect()
	{
		return m_rect;
	}

	void Update(CWnd *ap_parent)
	{
		ap_parent->InvalidateRect(m_rect, 0);
	}

	void Update(CWnd* ap_parent, int a_pos)
	{
		SetPos(a_pos);
		ap_parent->InvalidateRect(m_rect, 0);
	}

	void SetRange(int a_min, int a_max)
	{
		if (a_max == a_min) return;
		
		if( a_max < a_min)
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

	inline void SetPos(int a_pos) 
	{ 
		m_pos = a_pos; 
		if (m_pos < m_min) m_pos = m_min;
		else if (m_pos > m_max) m_pos = m_max;
	}

	inline int GetPos() { return m_pos; }

	void SetColor(COLORREF a_bk_color, COLORREF a_fore_color)
	{
		m_bk_color = a_bk_color;
		m_fore_color = a_fore_color;
	}

	void Draw(CDC *ap_dc)
	{
		int pos = m_pos * m_rect.Width() / (m_max - m_min);

		ap_dc->FillSolidRect(m_rect.left + pos, m_rect.top, m_rect.Width(), m_rect.Height(), m_bk_color);
		ap_dc->FillSolidRect(m_rect.left, m_rect.top, pos, m_rect.Height(), m_fore_color);
	}
	
};

// CMyProgressBarDlg 대화 상자
class CMyProgressBarDlg : public CDialogEx
{
private:
	SJ_ProgressCtrl m_user_progress;
// 생성입니다.
public:
	CMyProgressBarDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPROGRESSBAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	CProgressCtrl m_my_progress;
};
