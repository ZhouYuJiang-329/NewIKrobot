#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgFlawParam.h"
#include "DlgChanEnb.h"
#include "DlgEncModu.h"

IMPLEMENT_DYNAMIC(CDlgFlawParam, CDialog)

CDlgFlawParam::CDlgFlawParam(CWnd* pParent) : CDialog(CDlgFlawParam::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgFlawParam = this;
}

CDlgFlawParam::~CDlgFlawParam(void)
{
}

void CDlgFlawParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TXT_NET_RATE, m_txtNetRate);
	DDX_Control(pDX, IDC_BTN_NET_RATE, m_btnNetRate);
	DDX_Control(pDX, IDC_TXT_DAQ_RATE, m_txtDaqRate);
	DDX_Control(pDX, IDC_TXT_SMPL_TIMES, m_txtSmplTimes);
	DDX_Control(pDX, IDC_TXT_ACC_TIMES, m_txtAccTimes);
	DDX_Control(pDX, IDC_BTN_SYNC_PARAM, m_btnSyncParam);
	DDX_Control(pDX, IDC_BTN_AUTO_GAIN, m_btnAutoGain);
	DDX_Control(pDX, IDC_BTN_TST_VERT_LINEAR, m_btnTstVertLinear);
	DDX_Control(pDX, IDC_EDT_TST_SPAN, m_edtTstSpan);
	DDX_Control(pDX, IDC_CHK_DAC_CALIB, m_chkDacCalib);
	DDX_Control(pDX, IDC_BTN_DB_PLUS, m_btnDbPlus);
	DDX_Control(pDX, IDC_BTN_DB_MINUS, m_btnDbMinus);
	DDX_Control(pDX, IDC_BTN_TST_USR_REG, m_btnTstUsrReg);
	DDX_Control(pDX, IDC_TXT_SP_DIFF, m_txtSpDiff);
	DDX_Control(pDX, IDC_EDT_MAX_DAQ_RATE, m_edtMaxDaqRate);
}

BEGIN_MESSAGE_MAP(CDlgFlawParam, CDialog)
	ON_BN_CLICKED(IDC_BTN_SYNC_PARAM, OnBnClickedBtnSyncParam)
	ON_BN_CLICKED(IDC_BTN_DB_PLUS, OnBnClickedBtnDbPlus)
	ON_BN_CLICKED(IDC_BTN_DB_MINUS, OnBnClickedBtnDbMinus)
	ON_BN_CLICKED(IDC_BTN_AUTO_GAIN, &CDlgFlawParam::OnBnClickedBtnAutoGain)
	ON_BN_CLICKED(IDC_BTN_TST_VERT_LINEAR, &CDlgFlawParam::OnBnClickedBtnTstVertLinear)
	ON_BN_CLICKED(IDC_CHK_DAC_CALIB, &CDlgFlawParam::OnBnClickedChkDacCalib)
	ON_BN_CLICKED(IDC_BTN_TST_USR_REG, &CDlgFlawParam::OnBnClickedBtnTstUsrReg)
	ON_BN_CLICKED(IDC_BTN_CHAN_ENB, &CDlgFlawParam::OnBnClickedBtnChanEnb)
	ON_BN_CLICKED(IDC_BTN_NET_RATE, &CDlgFlawParam::OnBnClickedBtnNetRate)
	ON_BN_CLICKED(IDC_BTN_MAX_RPT_FREQ, &CDlgFlawParam::OnBnClickedBtnMaxRptFreq)
END_MESSAGE_MAP()

BOOL CDlgFlawParam::OnInitDialog(void)
{
	CString str;
	CDialog::OnInitDialog();

	m_dlgFlawParamAdj.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER,
		CRect(0, 0, 800, 118), this, 1);

	m_pApp->UpdSysTiming();	// 更新系统时序

	m_btnTstVertLinear.EnableWindow(m_pApp->m_bSmplEnb);

	str.Format("%d", m_pApp->m_stFlawParam.m_nVltSpan);
	m_edtTstSpan.SetWindowText(str);

	str.Format("%d", m_pApp->m_stFlawParam.m_nMaxDaqRate);
	m_edtMaxDaqRate.SetWindowText(str);

	m_txtNetRate.EnableWindow(m_pApp->m_bNet);
	m_btnNetRate.EnableWindow(m_pApp->m_bNet);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新采样次数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::UpdSmplTimes(void)
{
	CString str;
	str.Format("%d", m_pApp->m_pstExpInfo->m_nSmplTimes);
	m_txtSmplTimes.SetWindowText(str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新累积次数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::UpdAccTimes(void)
{
	CString str;
	str.Format("%d", m_pApp->m_pstExpInfo->m_nAccTimes);
	m_txtAccTimes.SetWindowText(str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新采集率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::UpdDaqRate(void)
{
	CString str;
	str.Format("%dHz", m_pApp->m_pstExpInfo->m_nDaqRate);
	m_txtDaqRate.SetWindowText(str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新网络传输率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::UpdNetRate(void)
{
	if (m_pApp->m_bNet)
	{
		CString str;
		str.Format("%.1fMB/s", m_pApp->m_pstExpInfo->m_fSysNetRate);
		m_txtNetRate.SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// +2dB
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnDbPlus(void)
{
	if (m_pApp->m_bDacCalib) return;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16& db_code = param.m_anDbNum[hard_num][soft_num];

	U16 max_db = m_pApp->m_pstExpInfo->m_nMaxGain;
	if ((db_code + 20) <= max_db)
	{
		db_code += 20;
		ZXUT_SetDbNum(hard_num, soft_num, db_code);
		m_pApp->m_pFlawParamAdj->FreshDbNum();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// -2dB
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnDbMinus(void)
{
	if (m_pApp->m_bDacCalib) return;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16& db_code = param.m_anDbNum[hard_num][soft_num];

	if (((S16)db_code - 20) >= 0)
	{
		db_code -= 20;
		ZXUT_SetDbNum(hard_num, soft_num, db_code);
		m_pApp->m_pFlawParamAdj->FreshDbNum();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 参数同步
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnSyncParam(void)
{
	m_pApp->SyncFlawParam();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 自动增益
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnAutoGain(void)
{
	if (m_pApp->m_bDacCalib) return;
	m_pApp->GenAuotoGain();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 测量垂直线性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnTstVertLinear(void)
{
	CString str;
	m_edtTstSpan.GetWindowText(str);
	m_pApp->m_stFlawParam.m_nVltSpan = _ttoi(str);	// 读取延迟时间
	m_pApp->TstVertLinear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DAC校准
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedChkDacCalib(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 db_code = param.m_anDbNum[hard_num][soft_num];

	m_pApp->m_bDacCalib = m_chkDacCalib.GetCheck();
	if (m_pApp->m_bDacCalib)
	{
		ZXUT_SetDacCalib(hard_num, soft_num);
	}
	else
	{
		ZXUT_SetDbNum(hard_num, soft_num, db_code);
	}

	m_btnAutoGain.EnableWindow(!m_pApp->m_bDacCalib);
	m_btnDbPlus.EnableWindow(!m_pApp->m_bDacCalib);
	m_btnDbMinus.EnableWindow(!m_pApp->m_bDacCalib);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 避免回车后响应OnOK()
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnOK(void)
{
	CString str;

	if (GetFocus() == &m_edtTstSpan)
	{
		m_edtTstSpan.GetWindowText(str);
		m_pApp->m_stFlawParam.m_nVltSpan = _ttoi(str);	// 读取垂直线性测量的时间间隔
	}
	else if (GetFocus() == &m_edtMaxDaqRate)
	{
		m_edtMaxDaqRate.GetWindowText(str);
		U32 tmp = _ttoi(str);
		if (tmp == 0)
		{
			m_pApp->DispMsg(ZXUT_MSG_ERR, "最大采集率非零");
		}
		else if (tmp > MAX_DAQ_RATE)
		{
			m_pApp->DispMsg(ZXUT_MSG_ERR, "最大采集率%dHz超出%dKHz限制", tmp, MAX_DAQ_RATE / 1000);
		}
		else
		{
			m_pApp->m_stFlawParam.m_nMaxDaqRate = tmp;
			ZXUT_SetMaxDaqRate(tmp);
			m_pApp->UpdSysTiming();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 测试用户寄存器
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnTstUsrReg(void)
{
	m_pApp->TstUsrReg();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示两个闸门AB之间的声程差
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::UpdSpDiff(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_GATE_PARAM& gate_param = param.m_astGateParam[m_pApp->m_nHardNum][m_pApp->m_nSoftNum];
	if ((param.m_nHoriDisp != HORI_DISP_DOTS) &&
		(gate_param.m_bEnb[GATE_SEL_A] == TRUE) &&
		(gate_param.m_bEnb[GATE_SEL_B] == TRUE))
	{
		CString str;
		F32 sp_diff = (F32)fabs(m_pApp->m_fGateDfctXInfo - m_pApp->m_fGateBttmXInfo);
		switch (param.m_nHoriDisp)
		{
			case HORI_DISP_MM:
				str.Format("%.2fmm", sp_diff);
				break;

			case HORI_DISP_US:
				str.Format("%.2fus", sp_diff);
				break;
		}
		m_txtSpDiff.SetWindowText(str);
	}
	else
	{
		m_txtSpDiff.SetWindowText("");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 通道使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnChanEnb(void)
{
	CDlgChanEnb dlg;
	dlg.DoModal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 网络传输率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnNetRate(void)
{
	ST_EXP_INFO& exp_info = *(m_pApp->m_pstExpInfo);
	CString str, msg;
	msg.Format("系统网络传输率 = %.1fMB/s\n\n", exp_info.m_fSysNetRate);

	for (U8 i = 0; i < exp_info.m_nTotBrd; i++)
	{
		str.Format("%d#板卡网络传输率 = %.1fMB/s\n", i + 1, exp_info.m_afBrdNetRate[i]);
		msg += str;
	}

	m_pApp->DispMsg(ZXUT_MSG_INFO, "%s", msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 获取最大重复频率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFlawParam::OnBnClickedBtnMaxRptFreq(void)
{
	m_pApp->GetMaxRptFreq();
}
