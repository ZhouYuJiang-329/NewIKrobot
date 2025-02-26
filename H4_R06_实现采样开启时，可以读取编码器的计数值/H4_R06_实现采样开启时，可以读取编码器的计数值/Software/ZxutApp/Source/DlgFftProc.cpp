#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgFftProc.h"
#include "FftShow.h"
#include "FlawParamAdj.h"

IMPLEMENT_DYNAMIC(CDlgFftProc, CDialog)
CDlgFftProc::CDlgFftProc(CWnd* pParent) : CDialog(CDlgFftProc::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgFftProc = this;
}

CDlgFftProc::~CDlgFftProc(void)
{
}

void CDlgFftProc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TXT_MAX_FREQ, m_txtMaxFreq);

	DDX_Control(pDX, IDC_TXT_CENT_FREQ, m_txtCentFreq);
	DDX_Control(pDX, IDC_TXT_LEFT_FREQ, m_txtLeftFreq);
	DDX_Control(pDX, IDC_TXT_RIGHT_FREQ, m_txtRightFreq);

	DDX_Control(pDX, IDC_COMBO_FFT_GATE, m_combFftGate);
	DDX_Control(pDX, IDC_COMBO_ANG_FLTR, m_combAngFltr);
	DDX_Control(pDX, IDC_BTN_REC_BW, m_btnRecBw);
	DDX_Control(pDX, IDC_BTN_GET_BW, m_btnAnalysizeBw);
	DDX_Control(pDX, IDC_CHK_SCAN_FREQ, m_chkScanFreq);
	DDX_Control(pDX, IDC_CHK_LOCK_BW, m_chkLockBw);
	DDX_Control(pDX, IDC_CHK_FFT_WAVE, m_chkFftWave);
	DDX_Control(pDX, IDC_CHK_CENT_FREQ, m_chkCentFreq);
	DDX_Control(pDX, IDC_COMBO_FREQ_REF_LINE, m_combFreqRefLine);
	DDX_Control(pDX, IDC_TXT_INST_GAIN, m_txtInstGain);
	DDX_Control(pDX, IDC_RAD_N3DB, m_radN3dB);
	DDX_Control(pDX, IDC_RAD_N6DB, m_radN6dB);
	DDX_Control(pDX, IDC_TXT_BW, m_txtBw);
	DDX_Control(pDX, IDC_TXT_RBW, m_txtRBw);
}

BEGIN_MESSAGE_MAP(CDlgFftProc, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_FFT_GATE, &CDlgFftProc::OnCbnSelchangeComboFftGate)
	ON_BN_CLICKED(IDC_CHK_SCAN_FREQ, &CDlgFftProc::OnBnClickedChkScanFreq)
	ON_BN_CLICKED(IDC_BTN_REC_BW, &CDlgFftProc::OnBnClickedBtnRecBw)
	ON_BN_CLICKED(IDC_CHK_LOCK_BW, &CDlgFftProc::OnBnClickedChkLockBw)
	ON_CBN_SELCHANGE(IDC_COMBO_FREQ_REF_LINE, &CDlgFftProc::OnCbnSelchangeComboFreqRefLine)
	ON_BN_CLICKED(IDC_RAD_N3DB, &CDlgFftProc::OnBnClickedRadN3db)
	ON_BN_CLICKED(IDC_RAD_N6DB, &CDlgFftProc::OnBnClickedRadN6db)
	ON_BN_CLICKED(IDC_CHK_FFT_WAVE, &CDlgFftProc::OnBnClickedChkFftWave)
	ON_BN_CLICKED(IDC_CHK_CENT_FREQ, &CDlgFftProc::OnBnClickedChkCentFreq)
	ON_BN_CLICKED(IDC_BTN_GET_BW, &CDlgFftProc::OnBnClickedBtnGetBw)
	ON_CBN_SELCHANGE(IDC_COMBO_ANG_FLTR, &CDlgFftProc::OnCbnSelchangeComboAngFltr)
END_MESSAGE_MAP()

BOOL CDlgFftProc::OnInitDialog(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	CDialog::OnInitDialog();

	m_pApp->m_hFftShowWnd = GetDlgItem(IDC_BASE_MAP_FFT)->GetSafeHwnd();
	m_pApp->m_pFftShow->InitWndHandle(m_pApp->m_hFftShowWnd);

	m_combFftGate.ResetContent();
	for (U8 i = GATE_SEL_MIN; i <= GATE_SEL_MAX; i++)
	{
		m_combFftGate.AddString(GATE_SEL_STR[i]);
	}
	m_combFftGate.SetCurSel(param.m_anFftGate[hard_num][soft_num]);

	m_btnAnalysizeBw.EnableWindow(FALSE);
	m_btnRecBw.EnableWindow(FALSE);
	m_chkLockBw.EnableWindow(m_pApp->m_bScanFreq);

	m_combFreqRefLine.EnableWindow(FALSE);

	m_combFreqRefLine.ResetContent();
	for (U32 i = 0; i < FFT_CURVE_LEN; i++)
	{
		CString str;
		U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
		str.Format("%.2f", ZXUT_GetFftFreq(i, freq_ratio));
		m_combFreqRefLine.AddString(str);
	}
	m_combFreqRefLine.SetCurSel(m_pApp->m_stFlawParam.m_nFreqRefLine);

	if (m_pApp->m_stFlawParam.m_bBwN3dB == TRUE)
	{
		m_radN3dB.SetCheck(TRUE);
		m_radN6dB.SetCheck(FALSE);
	}
	else
	{
		m_radN3dB.SetCheck(FALSE);
		m_radN6dB.SetCheck(TRUE);
	}

	m_pApp->FreshFftEnbCtrl();	// 刷新FFT使能控件

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 模拟滤波

	m_combAngFltr.EnableWindow(m_pApp->m_bAngFltrEnb);
	if (m_pApp->m_bAngFltrEnb)
	{
		m_combAngFltr.ResetContent();
		if (m_pApp->m_bPci)
		{
			for (U8 i = 0; i < ANG_FLTR_NUM_PCI; i++)
			{
				m_combAngFltr.AddString(ANG_FLTR_STR_PCI[i]);
			}
		}
		else if (m_pApp->m_bNet)
		{
			for (U8 i = 0; i < ANG_FLTR_NUM_NET; i++)
			{
				m_combAngFltr.AddString(ANG_FLTR_STR_NET[i]);
			}
		}

		U8 ang_fltr = param.m_anAngFltr[hard_num][soft_num];
		m_combAngFltr.SetCurSel(ang_fltr);
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 选择FFT闸门

void CDlgFftProc::OnCbnSelchangeComboFftGate(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	U8& fft_gate = m_pApp->m_stFlawParam.m_anFftGate[hard_num][soft_num];
	U8 bak = fft_gate;
	fft_gate = m_combFftGate.GetCurSel();
	if (m_pApp->m_stFlawParam.m_astGateParam[hard_num][soft_num].m_bEnb[fft_gate])
	{
		ZXUT_SetFftGate(hard_num, soft_num, fft_gate);
	}
	else
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "%s没有使能，不能选做FFT闸门", GATE_SEL_STR[fft_gate]);
		fft_gate = bak;
		m_combFftGate.SetCurSel(fft_gate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 扫频开启
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFftProc::OnBnClickedChkScanFreq(void)
{
	m_pApp->m_bScanFreq = m_chkScanFreq.GetCheck();
	m_pApp->ClrFftRes();

	m_chkLockBw.EnableWindow(m_pApp->m_bScanFreq);

	if (m_pApp->m_bScanFreq == FALSE)
	{
		m_pApp->m_bLockBw = FALSE;
	}

	m_chkLockBw.SetCheck(m_pApp->m_bLockBw);
	m_btnAnalysizeBw.EnableWindow(m_pApp->m_bScanFreq);
	m_btnRecBw.EnableWindow(m_pApp->m_bScanFreq);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 频带记录
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFftProc::OnBnClickedBtnRecBw(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 db_code = param.m_anDbNum[hard_num][soft_num];

#if 0

	fprintf(m_pApp->m_fpFreqBand, "%8.2f %8.2f %8.2f %8.2f %d.%d\n",
		m_pApp->m_fFreqLeft, m_pApp->m_fFreqCent, m_pApp->m_fFreqRight, m_pApp->m_fFreqMax,
		db_code / 10, db_code % 10);

#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 频带锁定
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFftProc::OnBnClickedChkLockBw(void)
{
	if (m_pApp->m_bScanFreq)
	{
		BOOL sts = m_chkLockBw.GetCheck();
		if (sts == TRUE)
		{
			m_pApp->LockBwCurve();
		}
		else
		{
			m_pApp->m_bLockBw = FALSE;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 频带分析
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgFftProc::OnBnClickedBtnGetBw(void)
{
	m_pApp->AnalyzeBwCure();
}

void CDlgFftProc::OnCbnSelchangeComboFreqRefLine(void)
{
	m_pApp->m_stFlawParam.m_nFreqRefLine = m_combFreqRefLine.GetCurSel();
	m_pApp->FreezeUpdFreqRefLine();
}

void CDlgFftProc::OnBnClickedRadN3db(void)
{
	m_pApp->m_stFlawParam.m_bBwN3dB = TRUE;		// -3dB
}

void CDlgFftProc::OnBnClickedRadN6db(void)
{
	m_pApp->m_stFlawParam.m_bBwN3dB = FALSE;	// -6dB
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// FFT波形开关

void CDlgFftProc::OnBnClickedChkFftWave(void)
{
	m_pApp->UpdFftWave(NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 中心频率开关

void CDlgFftProc::OnBnClickedChkCentFreq(void)
{
	m_pApp->UpdCentFreq(NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 模拟滤波器

void CDlgFftProc::OnCbnSelchangeComboAngFltr(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	U8& ang_fltr = param.m_anAngFltr[hard_num][soft_num];
	ang_fltr = m_combAngFltr.GetCurSel();
	m_pApp->m_pFlawParamAdj->FreshAngFltr();

	ZXUT_SetAngFltr(hard_num, soft_num, ang_fltr);
}
