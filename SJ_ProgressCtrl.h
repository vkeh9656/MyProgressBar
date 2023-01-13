#pragma once


class SJ_SimpleProgressCtrl
{
private:
	int m_pos, m_min, m_max;
	COLORREF m_bk_color, m_fore_color;
	CRect m_rect;

public:
	SJ_SimpleProgressCtrl() : m_rect(0, 0, 100, 30)
	{
		m_pos = 0;
		m_min = 0;
		m_max = 100;
		m_bk_color = RGB(0, 80, 160);
		m_fore_color = RGB(0, 160, 255);
	}

	void Create(CWnd* ap_parent, int a_guide_ctrl_id)
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

	void Update(CWnd* ap_parent)
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

	void Draw(CDC* ap_dc)
	{
		int pos = m_pos * m_rect.Width() / (m_max - m_min);

		ap_dc->FillSolidRect(m_rect.left + pos, m_rect.top, m_rect.Width() - pos, m_rect.Height(), m_bk_color);
		ap_dc->FillSolidRect(m_rect.left, m_rect.top, pos, m_rect.Height(), m_fore_color);
	}

};

class SJ_MemDC
{
private:
	CDC m_mem_dc;
	CBitmap m_mem_bmp;
	int m_width, m_height;

public:
	SJ_MemDC()
	{
		m_width = m_height = 0;
	}

	~SJ_MemDC()
	{
		if (m_mem_dc.m_hDC != NULL)
		{
			m_mem_bmp.DeleteObject();
			m_mem_dc.DeleteDC();
		}
	}

	void Create(CWnd* ap_wnd, int a_width, int a_height)
	{
		CClientDC dc(ap_wnd);

		m_width = a_width;
		m_height = a_height;
		m_mem_dc.CreateCompatibleDC(&dc);
		m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
		m_mem_dc.SelectObject(&m_mem_bmp);
	}

	void Resize(CWnd* ap_wnd, int a_width, int a_height)
	{
		if (a_width != m_width || a_width != m_height)
		{
			if (m_width && m_height)
			{
				m_mem_bmp.DeleteObject();

				m_width = a_width;
				m_height = a_height;

				CClientDC dc(ap_wnd);
				m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
				m_mem_dc.SelectObject(&m_mem_bmp);
			}
		}
	}

	inline CDC* GetDC()
	{
		return &m_mem_dc;
	}

	inline int GetWidth()
	{
		return m_width;
	}

	inline int GetHeight()
	{
		return m_height;
	}

	void Draw(CDC* ap_dc, int a_x, int a_y)
	{
		ap_dc->BitBlt(0, 0, m_width, m_height, &m_mem_dc, 0, 0, SRCCOPY);
	}
};

// SJ_ProgressCtrl
class SJ_ProgressCtrl : public CWnd
{
	DECLARE_DYNAMIC(SJ_ProgressCtrl)

protected:
	int m_pos, m_min, m_max;
	int m_width, m_height;
	COLORREF m_bk_color, m_fore_color;
	SJ_MemDC m_mem_image;

public:
	SJ_ProgressCtrl();
	virtual ~SJ_ProgressCtrl();

	void CreateProgress(CWnd* ap_parent, CRect a_rect, int a_ctrl_id);
	void CreateProgress(CWnd* ap_parent, int a_guide_ctrl_id, int a_ctrl_id);

	void SetRange(int a_min, int a_max);

	void SetPos(int a_pos);
	inline void UpdatePos(int a_pos) 
	{
		SetPos(a_pos);
		Invalidate(FALSE);
	}
	int GetPos();

	void SetColor(COLORREF a_bk_color, COLORREF a_fore_color);


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


