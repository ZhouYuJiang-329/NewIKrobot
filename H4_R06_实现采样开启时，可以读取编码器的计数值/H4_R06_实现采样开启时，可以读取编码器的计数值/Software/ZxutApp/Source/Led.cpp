#include "stdafx.h"
#include "Led.h"

CLed::CLed(void)
{
	m_crBK = GetSysColor(COLOR_3DFACE);	// 获取对话框背景颜色

	m_crOnFG = RGB(255, 0, 0);
	m_crOffFG = RGB(0, 255, 0);
	m_crDisFG = RGB(192, 192, 192);

	m_nType = LED_SQUARE;
	m_etState = LED_ON;

	m_brOnFG = new CBrush(m_crOnFG);
	m_brOffFG = new CBrush(m_crOffFG);
	m_brDisFG = new CBrush(m_crDisFG);

	m_penOn = CreatePen(PS_SOLID, 1, m_crOnFG);
	m_penOff = CreatePen(PS_SOLID, 1, m_crOffFG);
	m_penDis = CreatePen(PS_SOLID, 1, m_crDisFG);

	m_bTextOn = FALSE;
	m_sOnString = "on";
	m_sOffString = "off";
}

CLed::~CLed(void)
{
	delete m_brOnFG;
	delete m_brOffFG;
	delete m_brDisFG;

	if (m_penOn)
	{
		DeleteObject(m_penOn);
	}

	if (m_penOff)
	{
		DeleteObject(m_penOff);
	}

	if (m_penDis)
	{
		DeleteObject(m_penDis);
	}
}

BEGIN_MESSAGE_MAP(CLed, CStatic)

	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()

END_MESSAGE_MAP()

int CLed::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CLed::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	OnPaint();
}

void CLed::OnDestroy(void)
{
	CStatic::OnDestroy();
}

void CLed::OnPaint(void)
{
	CPaintDC dc(this);
	DrawFigure();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 绘图

void CLed::DrawFigure(void)
{
	CClientDC pdc(this);

	CRect r;
	GetClientRect(r);

	CBrush b;
	b.CreateSolidBrush(m_crBK);
	pdc.SelectObject(&b);
	pdc.FillRect(r, &b);
	pdc.SetBkMode(TRANSPARENT);

	if (m_etState == LED_ON)
	{
		SelectObject(pdc, m_penOn);
		pdc.SelectObject(m_brOnFG);
	}
	else if (m_etState == LED_OFF)
	{
		SelectObject(pdc, m_penOff);
		pdc.SelectObject(m_brOffFG);
	}
	else
	{
		SelectObject(pdc, m_penDis);
		pdc.SelectObject(m_brDisFG);
	}

	if (m_nType == LED_CIRCLE)
	{
		CRect r1;
		if (r.Width() > r.Height())
		{
			r1.left = r.left + (r.Width() - r.Height()) / 2;
			r1.right = r.right - (r.Width() - r.Height()) / 2;
			r1.top = r.top;
			r1.bottom = r.bottom;
		}
		else
		{
			r1.left = r.left;
			r1.right = r.right;
			r1.top = r.top + (r.Height() - r.Width()) / 2;
			r1.bottom = r.bottom - (r.Height() - r.Width()) / 2;
		}

		pdc.Ellipse(r1);
	}
	else
	{
		pdc.Rectangle(r);
	}

	if (m_bTextOn)
	{
		if (m_etState)
		{
			pdc.TextOut(
				r.CenterPoint().x - (int)(m_sOnString.GetLength() * 3.5),
				r.CenterPoint().y - 10,
				m_sOnString, m_sOnString.GetLength());
		}
		else
		{
			pdc.TextOut(
				r.CenterPoint().x - (int)(m_sOffString.GetLength() * 3.5),
				r.CenterPoint().y - 10,
				m_sOffString, m_sOffString.GetLength());
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 前景颜色

void CLed::SetOnFgColor(COLORREF C)
{
	m_brOnFG->DeleteObject();
	m_crOnFG = C;
	m_brOnFG->CreateSolidBrush(m_crOnFG);
	OnPaint();
}

COLORREF CLed::GetOnFgColor(void)
{
	return m_crOnFG;
}

void CLed::SetOffFgColor(COLORREF C)
{
	m_brOffFG->DeleteObject();
	m_crOffFG = C;
	m_brOffFG->CreateSolidBrush(m_crOffFG);
	OnPaint();
}

COLORREF CLed::GetOffFgColor(void)
{
	return m_crOffFG;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 类型

void CLed::SetType(ET_LED_TYPE type)
{
	m_nType = type;
	OnPaint();
}

ET_LED_TYPE CLed::GetType(void)
{
	return m_nType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 背景颜色

void CLed::SetBKColor(COLORREF C)
{
	m_crBK = C;
	OnPaint();
}

COLORREF CLed::GetBKColor(void)
{
	return m_crBK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ON/OFF文本

void CLed::SetOnText(CString str)
{
	m_sOnString = str;
	OnPaint();
}

CString CLed::GetOnText(void)
{
	return m_sOnString;
}

void CLed::SetOffText(CString str)
{
	m_sOffString=str;
	OnPaint();
}

CString CLed::GetOffText(void)
{
	return m_sOffString;
}

void CLed::SetTextOnOff(bool val)
{
	m_bTextOn=val;
	OnPaint();
}

bool CLed::GetTextOnOff()
{
	return m_bTextOn;
}

void CLed::SetState(ET_LED_STATE etState)
{
	m_etState = etState;
//	OnPaint();
	DrawFigure();
}

ET_LED_STATE CLed::GetState(void)
{
	return m_etState;
}
