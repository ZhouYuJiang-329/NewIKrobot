#include "stdafx.h"
#include "ZxutApp.h"
#include "FftShow.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 构造函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CFftShow::CFftShow(void)
{
	m_pApp = (CZxutApp*)AfxGetApp();

	m_hWaveWnd		= NULL;

	m_hWndDC		= NULL;
	m_hBackMemDC	= NULL;
	m_hShadowMemDC	= NULL;

	m_hBackBitmap	= NULL;
	m_hShadowBitmap	= NULL;

	m_hFftCurvePen	= CreatePen(PS_SOLID, 1, FFT_CURVE_COLOR);
	m_hBwCurvePen	= CreatePen(PS_SOLID, 1, BW_CURVE_COLOR);
	m_hBwLockPen	= CreatePen(PS_SOLID, 1, BW_LOCK_COLOR);
	m_hClrCurvePen	= CreatePen(PS_SOLID, 1, CLR_CURVE_COLOR);
	m_hBaseLinePen	= CreatePen(PS_SOLID, 1, BASE_LINE_COLOR);
	m_hFreqRefLinePen = CreatePen(PS_SOLID, 1, FREQ_REF_LINE_COLOR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 析构函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CFftShow::~CFftShow(void)
{
	if (m_hFftCurvePen)
	{
		DeleteObject(m_hFftCurvePen);
	}

	if (m_hBwCurvePen)
	{
		DeleteObject(m_hBwCurvePen);
	}

	if (m_hBwLockPen)
	{
		DeleteObject(m_hBwLockPen);
	}

	if (m_hBwLockPen)
	{
		DeleteObject(m_hBwLockPen);
	}

	if (m_hClrCurvePen)
	{
		DeleteObject(m_hClrCurvePen);
	}

	if (m_hBaseLinePen)
	{
		DeleteObject(m_hBaseLinePen);
	}

	if (m_hFreqRefLinePen)
	{
		DeleteObject(m_hFreqRefLinePen);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////

	if (m_hWndDC)
	{
		ReleaseDC(m_hWaveWnd, m_hWndDC);
	}

	if (m_hBackBitmap)
	{
		SelectObject(m_hBackMemDC, m_hBackMemDCInit);
		DeleteObject(m_hBackBitmap);
	}

	if (m_hBackMemDC)
	{
		DeleteDC(m_hBackMemDC);
	}

	if (m_hShadowBitmap)
	{
		SelectObject(m_hShadowMemDC, m_hShadowMemDCInit);
		DeleteObject(m_hShadowBitmap);
	}

	if (m_hShadowMemDC)
	{
		DeleteDC(m_hShadowMemDC);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化显示窗口句柄
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFftShow::InitWndHandle(HWND pWndHandle)
{
	m_hWaveWnd = pWndHandle;

	m_hWndDC = GetWindowDC(m_hWaveWnd);
	if (m_hWndDC != NULL)
	{
		m_hBackBitmap = LoadBitmap(m_pApp->m_hInstance, MAKEINTRESOURCE(IDB_BASE_MAP_FFT));
		m_hBackMemDC = CreateCompatibleDC(m_hWndDC);
		m_hBackMemDCInit = SelectObject(m_hBackMemDC, m_hBackBitmap);

		m_hShadowBitmap = CreateCompatibleBitmap(m_hBackMemDC, SHOW_FFT_WIDTH, SHOW_FFT_HEIGHT);
		m_hShadowMemDC = CreateCompatibleDC(m_hWndDC);
		m_hShadowMemDCInit = SelectObject(m_hShadowMemDC, m_hShadowBitmap);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 波形显示的准备和善后
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFftShow::SetShowStatus(BOOL bStatus)
{
	if (bStatus == FALSE)
	{
		BitBlt(m_hShadowMemDC, 0, 0, SHOW_FFT_WIDTH, SHOW_FFT_HEIGHT, m_hBackMemDC, 0, 0, SRCCOPY);
		m_nOrigMapMode = SetMapMode(m_hShadowMemDC, MM_ANISOTROPIC);

		SetWindowExtEx(m_hShadowMemDC, SHOW_FFT_WIDTH, SHOW_FFT_HEIGHT, NULL);
		SetViewportExtEx(m_hShadowMemDC, SHOW_FFT_WIDTH, SHOW_FFT_HEIGHT, NULL);
		SetViewportOrgEx(m_hShadowMemDC, 0, 0, NULL);
	}
	else
	{
		SetMapMode(m_hShadowMemDC, m_nOrigMapMode);
		BitBlt(m_hWndDC, 0, 0, SHOW_FFT_WIDTH, SHOW_FFT_HEIGHT, m_hShadowMemDC, 0, 0, SRCCOPY);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示采样视图
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFftShow::ShowFftView(U8* pFftCurve, U8* pBwCurve, U16 x1, U16 x2, U16 x3, U8 y, U32 ref_line)
{
	SetShowStatus(FALSE);

//	ShowGrid();				// 显示背景栅格

	ShowFftWave(CURVE_TYPE_FFT, pFftCurve, m_hFftCurvePen);		// 显示FFT曲线

	if (m_pApp->m_bScanFreq)
	{
		if (m_pApp->m_bLockBw)
		{
			ShowFftWave(CURVE_TYPE_BW, m_pApp->m_anBwLockCurve, m_hBwLockPen);		// 显示锁定的带宽曲线

			HANDLE hOldPen = SelectObject(m_hShadowMemDC, m_hFreqRefLinePen);
			::MoveToEx(m_hShadowMemDC, ref_line, 0, NULL);
			::LineTo(m_hShadowMemDC, ref_line, SHOW_FFT_HEIGHT - 1);
			SelectObject(m_hShadowMemDC, hOldPen);

			hOldPen = SelectObject(m_hShadowMemDC, m_hBaseLinePen);
			U8 p = InvertFftShowData(y);
			::MoveToEx(m_hShadowMemDC, 0, p, NULL);
			::LineTo(m_hShadowMemDC, FFT_CURVE_LEN, p);
			SelectObject(m_hShadowMemDC, hOldPen);

			hOldPen = SelectObject(m_hShadowMemDC, m_hFftCurvePen);
			U8 p1 = InvertFftShowData(0);
			U8 p2 = InvertFftShowData(179);
			::MoveToEx(m_hShadowMemDC, x1, p1, NULL);
			::LineTo(m_hShadowMemDC, x1, p2);
			::MoveToEx(m_hShadowMemDC, x2, p1, NULL);
			::LineTo(m_hShadowMemDC, x2, p2);
			::MoveToEx(m_hShadowMemDC, x3, p1, NULL);
			::LineTo(m_hShadowMemDC, x3, p2);
			SelectObject(m_hShadowMemDC, hOldPen);
		}

		ShowFftWave(CURVE_TYPE_BW, pBwCurve, m_hBwCurvePen);		// 显示当前的带宽曲线
	}

	SetShowStatus(TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示背景栅格
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFftShow::ShowGrid(void)
{
	const COLORREF DARK_COLOR		= RGB(0, 0, 0);
	const COLORREF LIGHT_COLOR		= RGB(192, 192, 192);
	const COLORREF MID_COLOR		= RGB(255, 0, 255);

	U8 x, y;
	U16 dx;
	U8 dy;

	::SetPixel(m_hShadowMemDC, 0, 0, DARK_COLOR);
	::SetPixel(m_hShadowMemDC, SHOW_FFT_WIDTH - 1, SHOW_FFT_HEIGHT - 1, DARK_COLOR);

	// 水平方向
	for (x = 1; x <= 49; x++)
	{
		dx = (U16)((SHOW_FFT_WIDTH - 1) * 1.0 / (49 + 1) * x);

		for (y = 1; y <= 4; y++)
		{
			dy = (U8)((SHOW_FFT_HEIGHT - 1) * 1.0 / (4 + 1) * y);
			::SetPixel(m_hShadowMemDC, dx - 1, InvertFftShowData(dy), LIGHT_COLOR);
			::SetPixel(m_hShadowMemDC, dx, InvertFftShowData(dy), DARK_COLOR);
			::SetPixel(m_hShadowMemDC, dx + 1, InvertFftShowData(dy), LIGHT_COLOR);
		}
	}

	// 垂直方向
	for (x = 1; x <= 9; x++)
	{
		dx = (U16)((SHOW_FFT_WIDTH - 1) * 1.0 / (9 + 1) * x);

		for (y = 1; y <= 24; y++)
		{
			dy = (U8)((SHOW_FFT_HEIGHT - 1) * 1.0 / (24 + 1) * y);
			::SetPixel(m_hShadowMemDC, dx, InvertFftShowData(dy - 1), LIGHT_COLOR);
			::SetPixel(m_hShadowMemDC, dx, InvertFftShowData(dy), DARK_COLOR);
			::SetPixel(m_hShadowMemDC, dx, InvertFftShowData(dy + 1), LIGHT_COLOR);

			if (x == 5)
			{
				::SetPixel(m_hShadowMemDC, dx - 1, InvertFftShowData(dy - 1), LIGHT_COLOR);
				::SetPixel(m_hShadowMemDC, dx - 1, InvertFftShowData(dy), DARK_COLOR);
				::SetPixel(m_hShadowMemDC, dx - 1, InvertFftShowData(dy + 1), LIGHT_COLOR);

				::SetPixel(m_hShadowMemDC, dx + 1, InvertFftShowData(dy - 1), LIGHT_COLOR);
				::SetPixel(m_hShadowMemDC, dx + 1, InvertFftShowData(dy), DARK_COLOR);
				::SetPixel(m_hShadowMemDC, dx + 1, InvertFftShowData(dy + 1), LIGHT_COLOR);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示采样波形
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFftShow::ShowFftWave(U8 nCurveType, U8* pFftCurve, HPEN pen)
{
	HANDLE hOldPen;
	U32 len;

	hOldPen = SelectObject(m_hShadowMemDC, pen);

	if (nCurveType == CURVE_TYPE_FFT)
	{
		len = FFT_OUT_DOTS - 1;
	}
	else
	{
		len = FFT_CURVE_LEN;
	}

	U16 p1, p2;
	for (U32 i = 0; i < len; i++)
	{
		p1 = InvertFftShowData(pFftCurve[i]);
		::MoveToEx(m_hShadowMemDC, i, p1, NULL);

		p2 = InvertFftShowData(pFftCurve[i + 1]);
		::LineTo(m_hShadowMemDC, i + 1, p2);
	}

	SelectObject(m_hShadowMemDC, hOldPen);
}

U8 CFftShow::InvertFftShowData(U8 nShowData)
{
	return SHOW_FFT_HEIGHT - 1 - nShowData;
}
