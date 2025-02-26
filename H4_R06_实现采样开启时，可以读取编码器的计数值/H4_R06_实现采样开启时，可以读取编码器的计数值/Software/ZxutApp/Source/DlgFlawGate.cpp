#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgFlawGate.h"
#include "ZxutDlg.h"
#include "SmplShow.h"

IMPLEMENT_DYNAMIC(CDlgFlawGate, CDialog)

CDlgFlawGate::CDlgFlawGate(CWnd* pParent) : CDialog(CDlgFlawGate::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgFlawGate = this;
}

CDlgFlawGate::~CDlgFlawGate(void)
{
}

void CDlgFlawGate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgFlawGate, CDialog)
END_MESSAGE_MAP()

BOOL CDlgFlawGate::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgFlawGateAdj.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER,
		CRect(0, 0, 650, 200), this, 1);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新伤波闸门判伤结果
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawGate::UpdGateRes(U8 gate_sel)
{
	CString str;

	ST_GATE_RES& stGateRes = m_pApp->m_stGateRes[gate_sel];

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
	U8 disp_upd = param.m_nDispUpd;
	U16 y = stGateRes.gr_yPeak;
	U32& proc_cntr = m_pApp->m_nUpdProcCntr[gate_sel];

	U16 x, t;
	switch (param.m_astGateParam[hard_num][soft_num].m_nType[gate_sel])
	{
		case FLAW_TYPE_PEAK:
			x = stGateRes.gr_xPeak;
			t = stGateRes.gr_tPeak;
			break;

		case FLAW_TYPE_PEDGE:
			x = stGateRes.gr_xpEdge;
			t = stGateRes.gr_tpEdge;
			break;

		case FLAW_TYPE_NEDGE:
			x = stGateRes.gr_xnEdge;
			t = stGateRes.gr_tnEdge;
			break;

		default:
			return;
	}

	static F32 tot_pdist[TOT_GATE_NUM];
	static F32 tot_ptime[TOT_GATE_NUM];
	static F32 tot_pperc[TOT_GATE_NUM];
	static U32 tot_pdots[TOT_GATE_NUM];

	if (proc_cntr == 0)
	{
		tot_pdist[gate_sel] = 0.0; tot_ptime[gate_sel] = 0.0;
		tot_pperc[gate_sel] = 0.0; tot_pdots[gate_sel] = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 水平信息

	U8& hori_disp = param.m_nHoriDisp;

	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
	F32 ptime = ZXUT_GetTstTime(freq_ratio, x, t) * 0.001f;	// ns -> us
	F32 pdist = ZXUT_GetTstRange(freq_ratio, x, t, sound_velo);

	if (disp_upd == DISP_UPD_REAL)
	{
		switch (hori_disp)
		{
			case HORI_DISP_MM:
				str.Format("%.2f", pdist);	// mm
				if (gate_sel == GATE_SEL_A)
				{
					m_pApp->m_fGateDfctXInfo = pdist;
				}
				else if (gate_sel == GATE_SEL_B)
				{
					m_pApp->m_fGateBttmXInfo = pdist;
				}
				break;

			case HORI_DISP_US:
				str.Format("%.2f", ptime);	// us
				if (gate_sel == GATE_SEL_A)
				{
					m_pApp->m_fGateDfctXInfo = ptime;
				}
				else if (gate_sel == GATE_SEL_B)
				{
					m_pApp->m_fGateBttmXInfo = ptime;
				}
				break;

			case HORI_DISP_DOTS:
				str.Format("%d, %d", x, t);	// 点数
				break;
		}

		m_dlgFlawGateAdj.FreshPeakHori(gate_sel, str);

		if (gate_sel == GATE_SEL_A)
		{
			m_pApp->m_pDlgZxut->m_txtPeakDist.SetWindowText(str);
		}
	}
	else
	{
		tot_pdist[gate_sel] += pdist;
		tot_ptime[gate_sel] += ptime;

		if (proc_cntr == m_pApp->m_nUpdProcEnd - 1)
		{
			switch (hori_disp)
			{
				case HORI_DISP_MM:
				{
					F32 tmp = tot_pdist[gate_sel] / m_pApp->m_nUpdProcEnd;
					str.Format("%.2f", tmp);	// mm
					if (gate_sel == GATE_SEL_A)
					{
						m_pApp->m_fGateDfctXInfo = tmp;
					}
					else if (gate_sel == GATE_SEL_B)
					{
						m_pApp->m_fGateBttmXInfo = tmp;
					}
					break;
				}

				case HORI_DISP_US:
				{
					F32 tmp = tot_ptime[gate_sel] / m_pApp->m_nUpdProcEnd;
					str.Format("%.2f", tmp);	// us
					if (gate_sel == GATE_SEL_A)
					{
						m_pApp->m_fGateDfctXInfo = tmp;
					}
					else if (gate_sel == GATE_SEL_B)
					{
						m_pApp->m_fGateBttmXInfo = tmp;
					}

					break;
				}

				case HORI_DISP_DOTS:
				{
					str.Format("%d, %d", x, t);		// 点数
					break;
				}
			}

			m_dlgFlawGateAdj.FreshPeakHori(gate_sel, str);

			if (gate_sel == GATE_SEL_A)
			{
				m_pApp->m_pDlgZxut->m_txtPeakDist.SetWindowText(str);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 垂直信息

	U8& vert_disp = param.m_nVertDisp;

	F32 pp = y * 100.0f / (m_pApp->m_nSmplWaveHeight - 1);
	if (disp_upd == DISP_UPD_REAL)
	{
		switch (vert_disp)
		{
			case VERT_DISP_PERC:
				str.Format("%.1f%%", pp);	// 百分比
				break;

			case VERT_DISP_DOTS:
				str.Format("%d", y);		// 点数
				break;
		}

		m_dlgFlawGateAdj.FreshPeakVert(gate_sel, str);

		if (gate_sel == GATE_SEL_A)
		{
			m_pApp->m_pDlgZxut->m_txtPeakHeight.SetWindowText(str);
			m_pApp->m_nAvgWaveHeight = y;
		}
	}
	else
	{
		tot_pperc[gate_sel] += pp;
		tot_pdots[gate_sel] += y;

		if (proc_cntr == m_pApp->m_nUpdProcEnd - 1)
		{
			switch (vert_disp)
			{
				case VERT_DISP_PERC:
					str.Format("%.1f%%", tot_pperc[gate_sel] / m_pApp->m_nUpdProcEnd);	// 百分比
					break;

				case VERT_DISP_DOTS:
					str.Format("%d", tot_pdots[gate_sel] / m_pApp->m_nUpdProcEnd);		// 点数
					break;
			}

			m_dlgFlawGateAdj.FreshPeakVert(gate_sel, str);

			if (gate_sel == GATE_SEL_A)
			{
				m_pApp->m_pDlgZxut->m_txtPeakHeight.SetWindowText(str);
				m_pApp->m_nAvgWaveHeight = tot_pdots[gate_sel] / m_pApp->m_nUpdProcEnd;
			}
		}
	}

	if (disp_upd != DISP_UPD_REAL)
	{
		if (proc_cntr == m_pApp->m_nUpdProcEnd - 1)
		{
			proc_cntr = 0;
		}
		else
		{
			proc_cntr++;
		}
	}
}
