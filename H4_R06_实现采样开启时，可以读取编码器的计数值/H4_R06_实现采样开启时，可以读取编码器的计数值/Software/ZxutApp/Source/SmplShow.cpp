#include "stdafx.h"
#include "ZxutApp.h"
#include "SmplShow.h"

#define SHOW_WAVE_GRID 0

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 构造函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CSmplShow::CSmplShow(void)
{
	m_pApp = (CZxutApp*)AfxGetApp();

	m_hWaveWnd		= NULL;

	m_hWndDC		= NULL;
	m_hBackMemDC	= NULL;
	m_hShadowMemDC	= NULL;

	m_hBackBitmap	= NULL;
	m_hShadowBitmap	= NULL;

	m_hEnvlpWavePen	= CreatePen(PS_SOLID, 1, ENVLP_WAVE_COLOR);
	m_hSmplWavePen	= CreatePen(PS_SOLID, 1, SMPL_WAVE_COLOR);

	m_hGatePen[0]	= CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_hGatePen[1]	= CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_hGatePen[2]	= CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_hGatePen[3]	= CreatePen(PS_SOLID, 1, RGB(0, 255, 255));

	m_hFont			= CreateFont(
		20, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, GB2312_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "Tahoma"
		);

	cm_nSmplWaveHeight = m_pApp->m_nSmplWaveHeight;
	cm_nSmplWaveYRatio = m_pApp->m_nSmplWaveYRatio;
	cm_nGateHeightSpan = 3 * cm_nSmplWaveYRatio;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 析构函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CSmplShow::~CSmplShow(void)
{
	if (m_hFont)
	{
		DeleteObject(m_hFont);
	}

	if (m_hEnvlpWavePen)
	{
		DeleteObject(m_hEnvlpWavePen);
	}

	if (m_hSmplWavePen)
	{
		DeleteObject(m_hSmplWavePen);
	}

	for (U8 p = 0; p < TOT_GATE_NUM; p++)
	{
		if (m_hGatePen[p])
		{
			DeleteObject(m_hGatePen[p]);
		}
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

void CSmplShow::InitWndHandle(HWND pWndHandle)
{
	m_hWaveWnd = pWndHandle;

	m_hWndDC = GetWindowDC(m_hWaveWnd);
	if (m_hWndDC != NULL)
	{
		m_hBackBitmap = LoadBitmap(m_pApp->m_hInstance, MAKEINTRESOURCE(IDB_BASE_MAP_SMPL));
		m_hBackMemDC = CreateCompatibleDC(m_hWndDC);
		m_hBackMemDCInit = SelectObject(m_hBackMemDC, m_hBackBitmap);

		m_hShadowBitmap = CreateCompatibleBitmap(m_hBackMemDC, SHOW_SMPL_WIDTH, SHOW_SMPL_HEIGHT);
		m_hShadowMemDC = CreateCompatibleDC(m_hWndDC);
		m_hShadowMemDCInit = SelectObject(m_hShadowMemDC, m_hShadowBitmap);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 波形显示的准备和善后
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::SetShowStatus(BOOL bStatus, U32 nSmplDepth)
{
	if (bStatus == FALSE)
	{
		BitBlt(m_hShadowMemDC, 0, 0, SHOW_SMPL_WIDTH, SHOW_SMPL_HEIGHT, m_hBackMemDC, 0, 0, SRCCOPY);
		m_nOrigMapMode = SetMapMode(m_hShadowMemDC, MM_ANISOTROPIC);

	#if (SHOW_WAVE_GRID == 1)
		SetWindowExtEx(m_hShadowMemDC, nSmplDepth, SHOW_SMPL_HEIGHT, NULL);
	#else
		SetWindowExtEx(m_hShadowMemDC, nSmplDepth, cm_nSmplWaveHeight, NULL);
	#endif
		SetViewportExtEx(m_hShadowMemDC, SHOW_SMPL_WIDTH, SHOW_SMPL_HEIGHT, NULL);
		SetViewportOrgEx(m_hShadowMemDC, 0, 0, NULL);
	}
	else
	{
		SetMapMode(m_hShadowMemDC, m_nOrigMapMode);
		BitBlt(m_hWndDC, 0, 0, SHOW_SMPL_WIDTH, SHOW_SMPL_HEIGHT, m_hShadowMemDC, 0, 0, SRCCOPY);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 清除采样视图
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::ClearSmplView(void)
{
	BitBlt(m_hWndDC, 0, 0, SHOW_SMPL_WIDTH, SHOW_SMPL_HEIGHT, m_hBackMemDC, 0, 0, SRCCOPY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示采样视图
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::ShowSmplView(ST_RQ_DATA& stRqData)
//void CSmplShow::ShowSmplView(U16* pSmplBuf, U8& nDigIn, F32& fCpuTempValue, F32& fPcbTempValue,
//							 U32* nEncCntr, U32 tot, U32 nSmplDepth, BOOL smpl_wave_enb, U16 db_num, ST_GATE_RES stGateRes[TOT_GATE_NUM])
{
	ST_DAQ_DATA& daq_data = stRqData.rd_pstDaqData[0/*m*/][m_pApp->m_nHardNum][m_pApp->m_nSoftNum];

	U32 nSmplDepth = daq_data.dd_nSmplDepth;
	SetShowStatus(FALSE, nSmplDepth);

#if (SHOW_WAVE_GRID == 1)
	ShowGrid();	// 显示背景栅格
#else
	if (daq_data.dd_bSmplWavEnb)
	{
		ShowSmplWave(0, daq_data.dd_pnSmplWave, nSmplDepth);	// 显示动态回波
		if (m_pApp->m_bEnvlpEnb)
		{
			ShowSmplWave(1, m_pApp->m_anEnvlpBuf, nSmplDepth);	// 显示动态回波
		}
	}

//	ShowAuxInfo(nDigIn, fCpuTempValue, fPcbTempValue, nEncCntr, tot, nSmplDepth, db_num);	// 显示辅助信息
	ShowAuxInfo(stRqData);

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	// 显示所有闸门
	for (U8 p = 0; p < TOT_GATE_NUM; p++)
	{
		BOOL& gate_enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[p];
		if (gate_enb)
		{
			ShowGate(p, &(param.m_astGateParam[hard_num][soft_num]), &daq_data.dd_astGateRes[p], nSmplDepth);
		}
	}
#endif
	SetShowStatus(TRUE, nSmplDepth);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示背景栅格
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::ShowGrid(void)
{
	const COLORREF DARK_COLOR		= RGB(0, 0, 0);
	const COLORREF LIGHT_COLOR		= RGB(192, 192, 192);
	const COLORREF MID_COLOR		= RGB(255, 0, 255);

	U8 x, y;
	U16 dx, dy;

	::SetPixel(m_hShadowMemDC, 0, 0, DARK_COLOR);
	::SetPixel(m_hShadowMemDC, SHOW_SMPL_WIDTH - 1, SHOW_SMPL_HEIGHT - 1, DARK_COLOR);

	// 水平方向
	for (x = 1; x <= 49; x++)
	{
		dx = (U16)((SHOW_SMPL_WIDTH - 1) * 1.0 / (49 + 1) * x);

		for (y = 1; y <= 4; y++)
		{
			dy = (U16)((SHOW_SMPL_HEIGHT - 1) * 1.0 / (4 + 1) * y);
			::SetPixel(m_hShadowMemDC, dx - 1, InvertShowData(dy), LIGHT_COLOR);
			::SetPixel(m_hShadowMemDC, dx, InvertShowData(dy), DARK_COLOR);
			::SetPixel(m_hShadowMemDC, dx + 1, InvertShowData(dy), LIGHT_COLOR);
		}

		U16 mid = SHOW_SMPL_HEIGHT / 2 - 1;
		::SetPixel(m_hShadowMemDC, dx - 1, InvertShowData(mid), MID_COLOR);
		::SetPixel(m_hShadowMemDC, dx, InvertShowData(mid), MID_COLOR);
		::SetPixel(m_hShadowMemDC, dx + 1, InvertShowData(mid), MID_COLOR);
	}

	// 垂直方向
	for (x = 1; x <= 9; x++)
	{
		dx = (U16)((SHOW_SMPL_WIDTH - 1) * 1.0 / (9 + 1) * x);

		for (y = 1; y <= 24; y++)
		{
			dy = (U16)((SHOW_SMPL_HEIGHT - 1) * 1.0 / (24 + 1) * y);
			::SetPixel(m_hShadowMemDC, dx, InvertShowData(dy - 1), LIGHT_COLOR);
			::SetPixel(m_hShadowMemDC, dx, InvertShowData(dy), DARK_COLOR);
			::SetPixel(m_hShadowMemDC, dx, InvertShowData(dy + 1), LIGHT_COLOR);

			if (x == 5)
			{
				::SetPixel(m_hShadowMemDC, dx - 1, InvertShowData(dy - 1), LIGHT_COLOR);
				::SetPixel(m_hShadowMemDC, dx - 1, InvertShowData(dy), DARK_COLOR);
				::SetPixel(m_hShadowMemDC, dx - 1, InvertShowData(dy + 1), LIGHT_COLOR);

				::SetPixel(m_hShadowMemDC, dx + 1, InvertShowData(dy - 1), LIGHT_COLOR);
				::SetPixel(m_hShadowMemDC, dx + 1, InvertShowData(dy), DARK_COLOR);
				::SetPixel(m_hShadowMemDC, dx + 1, InvertShowData(dy + 1), LIGHT_COLOR);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示采样波形
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::ShowSmplWave(U8 nWaveType, U16* pSmplBuf, U32 nSmplDepth)
{
	COLORREF color;
	HANDLE hOldPen;
	if (nWaveType == WAVE_TYPE_SMPL)
	{
		color = SMPL_WAVE_COLOR;
		hOldPen = SelectObject(m_hShadowMemDC, m_hSmplWavePen);
	}
	else
	{
		color = ENVLP_WAVE_COLOR;
		hOldPen = SelectObject(m_hShadowMemDC, m_hEnvlpWavePen);
	}

	U16 p1, p2;
	for (U32 i = 0; i < nSmplDepth - 1; i++)
	{
		p1 = InvertShowData(pSmplBuf[i]);
		::MoveToEx(m_hShadowMemDC, i, p1, NULL);

		p2 = InvertShowData(pSmplBuf[i + 1]);
		::LineTo(m_hShadowMemDC, i + 1, p2);
	}

	SelectObject(m_hShadowMemDC, hOldPen);
}

U16 CSmplShow::InvertShowData(U16 nShowData)
{
#if (SHOW_WAVE_GRID == 1)

	return SHOW_SMPL_HEIGHT - 1 - nShowData;

#else

	nShowData = cm_nSmplWaveHeight - 1 - nShowData;

	U8 y_bw = m_pApp->m_pstExpInfo->m_nYBw;
	U32 wave_show_lmt = 499 * (1 << y_bw) / 500;
	if (nShowData > wave_show_lmt)
	{
		nShowData = wave_show_lmt;
	}

	return nShowData;

#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示伤波闸门
//
//  x
//	mm mm			mmmmmmm
//	mmmmm			 mmmmm
//	mmmmm y			  mmm
//	mmmmm			   m y
//	mm mm		       x
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::ShowGate(U8 gate_sel, ST_GATE_PARAM* pGateParam, ST_GATE_RES* pGateRes, U32 nSmplDepth)
{
	HANDLE hOldPen = SelectObject(m_hShadowMemDC, m_hGatePen[gate_sel]);

	U16 dx = nSmplDepth / SHOW_SMPL_WIDTH;
	U16 start = pGateParam->m_nStart[gate_sel] * dx;
	U16 width = pGateParam->m_nWidth[gate_sel] * dx;

	U16 dy = cm_nSmplWaveYRatio;
	U16 y = cm_nSmplWaveHeight - 1 - pGateParam->m_nHeight[gate_sel] * dy;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 绘制缺陷参考点

	if (m_pApp->m_stFlawParam.m_bFlawRef)
	{
		U16 nx, ny;
		BOOL disp_rp_enb;
		switch (pGateParam->m_nType[gate_sel])
		{
			case FLAW_TYPE_PEAK:	// 峰值
				nx = pGateRes->gr_xPeak;
				ny = pGateRes->gr_yPeak / dy;
				disp_rp_enb = TRUE;
				break;

			case FLAW_TYPE_PEDGE:	// 前沿
				nx = pGateRes->gr_xpEdge;
				ny = pGateParam->m_nHeight[gate_sel];
				disp_rp_enb = (nx != 0);
				break;

			case FLAW_TYPE_NEDGE:	// 后沿
				nx = pGateRes->gr_xnEdge;
				ny = pGateParam->m_nHeight[gate_sel];
				disp_rp_enb = (nx != 0);
				break;
		}

		int sign;
		if (ny <= SHOW_SMPL_HEIGHT - 1 - 6)
		{
			ny += 3;
			sign = 1;
		}
		else
		{
			ny = SHOW_SMPL_HEIGHT - 1;
			sign = -1;
		}

		if (disp_rp_enb)
		{
			for (int i = 0; i <= 4; i++)
			{
				U16 z = (ny + sign * i);
				z = cm_nSmplWaveHeight - 1 - z * dy;

				MoveToEx(m_hShadowMemDC, nx - i * dx,		z, NULL);
				LineTo  (m_hShadowMemDC, nx + i * dx + dx,	z);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 绘制左端点

	for (U8 i = 0; i <= 1; i++)
	{
		MoveToEx(m_hShadowMemDC, start + i * dx, y - cm_nGateHeightSpan, NULL);
		LineTo(m_hShadowMemDC, start + i * dx, y + cm_nGateHeightSpan + dy);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 绘制水平线

	for (int i = -1; i <= 1; i++)
	{
		MoveToEx(m_hShadowMemDC, start + 2 * dx, y + i * dy, NULL);
		LineTo(m_hShadowMemDC, start + width, y + i * dy);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 绘制右端点

	for (U8 i = 0; i <= 1; i++)
	{
		MoveToEx(m_hShadowMemDC, start + width - (2 - i) * dx, y - cm_nGateHeightSpan, NULL);
		LineTo(m_hShadowMemDC, start + width - (2 - i) * dx, y + cm_nGateHeightSpan + dy);
	}

	SelectObject(m_hShadowMemDC, hOldPen);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示附加信息
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CSmplShow::ShowAuxInfo(ST_RQ_DATA& stRqData)
//void CSmplShow::ShowAuxInfo(U8& nDigIn, F32& fCpuTempValue, F32& fPcbTempValue, U32* nEncCntr, U32 tot, U32 nSmplDepth, U16 db_num)
{
	::SetTextColor(m_hShadowMemDC, RGB(0, 0, 255));
	::SetBkColor(m_hShadowMemDC, RGB(255, 255, 255));

	ST_DAQ_DATA& daq_data = stRqData.rd_pstDaqData[0/*m*/][m_pApp->m_nHardNum][m_pApp->m_nSoftNum];

	const U32 AUX_INFO_START = 930 * daq_data.dd_nSmplDepth / SHOW_SMPL_WIDTH;
	const U32 AUX_INFO_RATIO = 16;

	CString str;
	U8 idx = 0;
	for (U8 i = 0; i < TOT_ENC_NUM - 2; i++)
	{
		str.Format("%d", daq_data.dd_anEabCntr[i]);
		::TextOut(m_hShadowMemDC, AUX_INFO_START, idx * 8 * AUX_INFO_RATIO, str, str.GetLength());
		idx++;
	}

//	str.Format("%d-%d %d",
	str.Format("%d-%d",
		m_pApp->m_nHardNum + 1,	// 硬编号
		m_pApp->m_nSoftNum + 1);// ,	// 软编号
//		tot);
	::TextOut(m_hShadowMemDC, AUX_INFO_START, idx * 8 * AUX_INFO_RATIO, str, str.GetLength());
	idx++;

	S16 db_num = m_pApp->m_stFlawParam.m_anDbNum[m_pApp->m_nHardNum][m_pApp->m_nSoftNum];
	str.Format("%d.%ddB 0x%02X", db_num / 10, db_num % 10, stRqData.rd_nDigIn);
	::TextOut(m_hShadowMemDC, AUX_INFO_START, idx * 8 * AUX_INFO_RATIO, str, str.GetLength());
	idx++;

	U8 brd_num = m_pApp->m_nHardNum / m_pApp->m_pstExpInfo->m_nTotHard;
//	int cpu_temp = static_cast<int>(fCpuTempValue);
//	int pcb_temp = static_cast<int>(fPcbTempValue);
	int cpu_temp = static_cast<int>(m_pApp->m_fCpuTempValue[brd_num]);
	int pcb_temp = static_cast<int>(m_pApp->m_fPcbTempValue[brd_num]);
	if (m_pApp->m_bPci)
	{
		str.Format("%d'C", pcb_temp);
	}
	else
	{
		str.Format("%d - %d = %d'C", cpu_temp, pcb_temp, cpu_temp - pcb_temp);
	}
	::TextOut(m_hShadowMemDC, AUX_INFO_START, idx * 8 * AUX_INFO_RATIO, str, str.GetLength());
	idx++;

	ST_EXP_INFO& exp_info = *(m_pApp->m_pstExpInfo);
//	U8 brd_num = m_pApp->m_nHardNum / exp_info.m_nTotHard;
//	str.Format("%d", exp_info.m_apstDaqBuf[brd_num]->m_nSmplOrder);
	str.Format("%d", stRqData.rd_nSmplOrder);
	::TextOut(m_hShadowMemDC, AUX_INFO_START, idx * 8 * AUX_INFO_RATIO, str, str.GetLength());
	idx++;
}
