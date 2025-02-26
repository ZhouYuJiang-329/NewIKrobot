#pragma once

class CZxutApp;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 颜色定义

const COLORREF FFT_CURVE_COLOR = RGB(0, 0, 255);			// 蓝色，FFT曲线
const COLORREF BW_CURVE_COLOR = RGB(255, 0, 0);				// 红色，带宽曲线
const COLORREF BW_LOCK_COLOR = RGB(0, 255, 0);				// 绿色，带宽锁定
const COLORREF CLR_CURVE_COLOR = RGB(255, 255, 255);		// 白色，清除曲线
const COLORREF BASE_LINE_COLOR = RGB(0, 255, 0);			// 绿色，基准横线
const COLORREF FREQ_REF_LINE_COLOR = RGB(255, 0, 255);		// 洋红，频率参考线

////////////////////////////////////////////////////////////////////////////////////////////////////
// 曲线类型

const U8 CURVE_TYPE_FFT = 0;	// FFT曲线
const U8 CURVE_TYPE_BW = 1;		// BW曲线

class CFftShow
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// 公有成员

public:
	CFftShow(void);
	~CFftShow(void);

	void InitWndHandle(HWND pWndHandle);
	void ShowFftView(U8* pFftCurve, U8* pBwCurve, U16 x1, U16 x2, U16 x3, U8 y, U32 ref_line);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 私有成员

private:
	CZxutApp* m_pApp;

	U8 InvertFftShowData(U8 nShowData);
	void SetShowStatus(BOOL bStatus);
	void ShowGrid(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 前景与背景DC

	HBITMAP m_hBackBitmap;
	HBITMAP m_hShadowBitmap;

	HANDLE	m_hBackMemDCInit;
	HANDLE	m_hShadowMemDCInit;

	HWND	m_hWaveWnd;
	HDC		m_hWndDC;
	HDC		m_hShadowMemDC;
	HDC		m_hBackMemDC;

	HPEN	m_hFftCurvePen;		// 用于绘制FFT曲线的笔
	HPEN	m_hBwCurvePen;		// 用于绘制BW曲线的笔
	HPEN	m_hBwLockPen;		// 用于绘制BW锁定的笔
	HPEN	m_hClrCurvePen;		// 用于绘制清除曲线的笔
	HPEN	m_hBaseLinePen;		// 用于绘制基准横线的笔
	HPEN	m_hFreqRefLinePen;	// 用于绘制频率参考线的笔

	int		m_nOrigMapMode;		// 原来的图形映射模式

	void	ShowFftWave(U8 nCurveType, U8* pFftCurve, HPEN pen);
};
