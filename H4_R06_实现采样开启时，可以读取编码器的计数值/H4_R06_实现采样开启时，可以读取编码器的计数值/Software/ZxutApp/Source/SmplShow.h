#pragma once

class CZxutApp;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 颜色定义

const COLORREF SMPL_WAVE_COLOR	= RGB(0, 0, 0);			// 采样波形的颜色
const COLORREF ENVLP_WAVE_COLOR	= RGB(191, 102, 30);	// 包络波形的颜色

////////////////////////////////////////////////////////////////////////////////////////////////////
// 波形类型

const U8 WAVE_TYPE_SMPL = 0;	// 采样波形
const U8 WAVE_TYPE_ENVLP = 1;	// 包络波形

class CSmplShow
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// 公有成员

public:
	CSmplShow(void);
	~CSmplShow(void);

	void InitWndHandle(HWND pWndHandle);

	void ShowSmplView(ST_RQ_DATA& stRqData);
//	void ShowSmplView(U16* pSmplBuf, U8& nDigIn, F32& fCpuTempValue, F32& fPcbTempValue, U32* nEncCntr, U32 tot, U32 nSmplDepth, BOOL smpl_wave_enb, U16 db_num, ST_GATE_RES* pGateRes);
	void ClearSmplView(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 私有成员

private:
	CZxutApp* m_pApp;

	U16 InvertShowData(U16 nShowData);
	void SetShowStatus(BOOL bStatus, U32 nSmplDepth);
	void ShowGrid(void);

	U16 cm_nSmplWaveHeight;	// 采样波形高度(2^12=4096)
	U16 cm_nGateHeightSpan;
	U16 cm_nSmplWaveYRatio;

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

	HPEN	m_hEnvlpWavePen;			// 用于绘制包络波形的笔
	HPEN	m_hSmplWavePen;				// 用于绘制采样波形的笔
	HPEN	m_hGatePen[4];				// 用于绘制伤波闸门的笔

	HFONT	m_hFont;					// 文本显示字体
	int		m_nOrigMapMode;				// 原来的图形映射模式

	void	ShowSmplWave(U8 nWaveType, U16* pSmplBuf, U32 nSmplDepth);
	void	ShowGate(U8 gate_sel, ST_GATE_PARAM* pGateParam, ST_GATE_RES* pGateRes, U32 nSmplDepth);
//	void	ShowAuxInfo(U8& nDigIn, F32& fCpuTempValue, F32& fPcbTempValue, U32* nEncCntr, U32 tot, U32 nSmplDepth, U16 db_num);
	void	ShowAuxInfo(ST_RQ_DATA& stRqData);
};
