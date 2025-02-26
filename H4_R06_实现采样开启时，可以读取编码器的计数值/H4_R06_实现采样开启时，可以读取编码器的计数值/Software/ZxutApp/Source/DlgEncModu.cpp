#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgEncModu.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CDlgEncModu, CDialog)

CDlgEncModu::CDlgEncModu(CWnd* pParent) : CDialog(CDlgEncModu::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgEncModu = this;
	m_nEncChan = 0;
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
	x_nTotHard = m_pApp->m_pstExpInfo->m_nTotHard;
}

CDlgEncModu::~CDlgEncModu(void)
{
}

void CDlgEncModu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_ENC_ENB0, m_chkEncEnb[0]);
	DDX_Control(pDX, IDC_CHK_ENC_ENB1, m_chkEncEnb[1]);
	DDX_Control(pDX, IDC_CHK_ENC_ENB2, m_chkEncEnb[2]);
	DDX_Control(pDX, IDC_CHK_ENC_ENB3, m_chkEncEnb[3]);
	DDX_Control(pDX, IDC_CHK_ENC_ENB, m_chkEncEnb[4]);

	DDX_Control(pDX, IDC_TXT_EAB_CNTR0, m_txtEabCntr[0]);
	DDX_Control(pDX, IDC_TXT_EAB_CNTR1, m_txtEabCntr[1]);
	DDX_Control(pDX, IDC_TXT_EAB_CNTR2, m_txtEabCntr[2]);
	DDX_Control(pDX, IDC_TXT_EAB_CNTR3, m_txtEabCntr[3]);

	DDX_Control(pDX, IDC_TXT_EZ_CNTR0, m_txtEzCntr[0]);
	DDX_Control(pDX, IDC_TXT_EZ_CNTR1, m_txtEzCntr[1]);
	DDX_Control(pDX, IDC_TXT_EZ_CNTR2, m_txtEzCntr[2]);
	DDX_Control(pDX, IDC_TXT_EZ_CNTR3, m_txtEzCntr[3]);

	DDX_Control(pDX, IDC_CHK_ENC_ZE0, m_chkEncZe[0]);
	DDX_Control(pDX, IDC_CHK_ENC_ZE1, m_chkEncZe[1]);
	DDX_Control(pDX, IDC_CHK_ENC_ZE2, m_chkEncZe[2]);
	DDX_Control(pDX, IDC_CHK_ENC_ZE3, m_chkEncZe[3]);
	DDX_Control(pDX, IDC_CHK_ENC_ZE, m_chkEncZe[4]);

	DDX_Control(pDX, IDC_BTN_RST_ENC_CNTR0, m_btnRstEncCntr[0]);
	DDX_Control(pDX, IDC_BTN_RST_ENC_CNTR1, m_btnRstEncCntr[1]);
	DDX_Control(pDX, IDC_BTN_RST_ENC_CNTR2, m_btnRstEncCntr[2]);
	DDX_Control(pDX, IDC_BTN_RST_ENC_CNTR3, m_btnRstEncCntr[3]);
	DDX_Control(pDX, IDC_BTN_RST_ENC_CNTR, m_btnRstEncCntr[4]);

	DDX_Control(pDX, IDC_CHK_ENC_POL0, m_chkEncPol[0]);
	DDX_Control(pDX, IDC_CHK_ENC_POL1, m_chkEncPol[1]);
	DDX_Control(pDX, IDC_CHK_ENC_POL2, m_chkEncPol[2]);
	DDX_Control(pDX, IDC_CHK_ENC_POL3, m_chkEncPol[3]);
	DDX_Control(pDX, IDC_CHK_ENC_POL, m_chkEncPol[4]);

	DDX_Control(pDX, IDC_RAD_SCAN_ENC0, m_radScanEnc[0]);
	DDX_Control(pDX, IDC_RAD_SCAN_ENC1, m_radScanEnc[1]);
	DDX_Control(pDX, IDC_RAD_SCAN_ENC2, m_radScanEnc[2]);
	DDX_Control(pDX, IDC_RAD_SCAN_ENC3, m_radScanEnc[3]);

	DDX_Control(pDX, IDC_COMBO_ENC_TYPE0, m_combEncType[0]);
	DDX_Control(pDX, IDC_COMBO_ENC_TYPE1, m_combEncType[1]);
	DDX_Control(pDX, IDC_COMBO_ENC_TYPE2, m_combEncType[2]);
	DDX_Control(pDX, IDC_COMBO_ENC_TYPE3, m_combEncType[3]);
	DDX_Control(pDX, IDC_COMBO_ENC_TYPE, m_combEncType[4]);

	DDX_Control(pDX, IDC_COMBO_ENC_FLTR0, m_combEncFltr[0]);
	DDX_Control(pDX, IDC_COMBO_ENC_FLTR1, m_combEncFltr[1]);
	DDX_Control(pDX, IDC_COMBO_ENC_FLTR2, m_combEncFltr[2]);
	DDX_Control(pDX, IDC_COMBO_ENC_FLTR3, m_combEncFltr[3]);
	DDX_Control(pDX, IDC_COMBO_ENC_FLTR, m_combEncFltr[4]);

	DDX_Control(pDX, IDC_EDT_SCAN_SPAN, m_edtScanSpan);

	////////////////////////////////////////////////////////////////////////////////////////////////

	DDX_Control(pDX, IDC_CHK_ENC_TST_ENB, m_chkEncTstEnb);
	DDX_Control(pDX, IDC_BTN_ENC_TST_TRIG, m_btnEncTstTrig);
	DDX_Control(pDX, IDC_EDT_ENC_TST_PUL_NUM, m_edtEncTstPulNum);
	DDX_Control(pDX, IDC_EDT_ENC_TST_LINE_NUM, m_edtEncTstLineNum);
	DDX_Control(pDX, IDC_CHK_ENC_TST_CONT, m_chkEncTstCont);
	DDX_Control(pDX, IDC_EDT_ENC_TST_FREQ, m_edtEncTstFreq);
	DDX_Control(pDX, IDC_TXT_ENC_TST_FREQ, m_txtEncTstFreq);
	DDX_Control(pDX, IDC_TXT_ENC_SCAN_FREQ, m_txtEncScanFreq);

	DDX_Control(pDX, IDC_COMB_ENC_CHAN, m_combEncIdx);
	DDX_Control(pDX, IDC_TXT_ENC_MEAS_RES, m_txtEncMeasFreq);
}

BEGIN_MESSAGE_MAP(CDlgEncModu, CDialog)
	ON_BN_CLICKED(IDC_CHK_ENC_ENB0, &CDlgEncModu::OnBnClickedChkEncEnb)
	ON_BN_CLICKED(IDC_CHK_ENC_ENB1, &CDlgEncModu::OnBnClickedChkEncEnb)
	ON_BN_CLICKED(IDC_CHK_ENC_ENB2, &CDlgEncModu::OnBnClickedChkEncEnb)
	ON_BN_CLICKED(IDC_CHK_ENC_ENB3, &CDlgEncModu::OnBnClickedChkEncEnb)
	ON_BN_CLICKED(IDC_CHK_ENC_ENB, &CDlgEncModu::OnBnClickedChkEncEnb)

	ON_BN_CLICKED(IDC_CHK_ENC_ZE0, &CDlgEncModu::OnBnClickedChkEncZe)
	ON_BN_CLICKED(IDC_CHK_ENC_ZE1, &CDlgEncModu::OnBnClickedChkEncZe)
	ON_BN_CLICKED(IDC_CHK_ENC_ZE2, &CDlgEncModu::OnBnClickedChkEncZe)
	ON_BN_CLICKED(IDC_CHK_ENC_ZE3, &CDlgEncModu::OnBnClickedChkEncZe)
	ON_BN_CLICKED(IDC_CHK_ENC_ZE, &CDlgEncModu::OnBnClickedChkEncZe)

	ON_BN_CLICKED(IDC_BTN_RST_ENC_CNTR0, OnBnClickedBtnRstEncCntr)
	ON_BN_CLICKED(IDC_BTN_RST_ENC_CNTR1, OnBnClickedBtnRstEncCntr)
	ON_BN_CLICKED(IDC_BTN_RST_ENC_CNTR2, OnBnClickedBtnRstEncCntr)
	ON_BN_CLICKED(IDC_BTN_RST_ENC_CNTR3, OnBnClickedBtnRstEncCntr)
	ON_BN_CLICKED(IDC_BTN_RST_ENC_CNTR, OnBnClickedBtnRstEncCntr)

	ON_BN_CLICKED(IDC_CHK_ENC_POL0, &CDlgEncModu::OnBnClickedChkEncPol)
	ON_BN_CLICKED(IDC_CHK_ENC_POL1, &CDlgEncModu::OnBnClickedChkEncPol)
	ON_BN_CLICKED(IDC_CHK_ENC_POL2, &CDlgEncModu::OnBnClickedChkEncPol)
	ON_BN_CLICKED(IDC_CHK_ENC_POL3, &CDlgEncModu::OnBnClickedChkEncPol)
	ON_BN_CLICKED(IDC_CHK_ENC_POL, &CDlgEncModu::OnBnClickedChkEncPol)

	ON_BN_CLICKED(IDC_RAD_SCAN_ENC0, &CDlgEncModu::OnBnClickedRadScanEnc)
	ON_BN_CLICKED(IDC_RAD_SCAN_ENC1, &CDlgEncModu::OnBnClickedRadScanEnc)
	ON_BN_CLICKED(IDC_RAD_SCAN_ENC2, &CDlgEncModu::OnBnClickedRadScanEnc)
	ON_BN_CLICKED(IDC_RAD_SCAN_ENC3, &CDlgEncModu::OnBnClickedRadScanEnc)

	ON_CBN_SELCHANGE(IDC_COMBO_ENC_TYPE0, &CDlgEncModu::OnCbnSelchangeComboEncType)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_TYPE1, &CDlgEncModu::OnCbnSelchangeComboEncType)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_TYPE2, &CDlgEncModu::OnCbnSelchangeComboEncType)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_TYPE3, &CDlgEncModu::OnCbnSelchangeComboEncType)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_TYPE, &CDlgEncModu::OnCbnSelchangeComboEncType)

	ON_CBN_SELCHANGE(IDC_COMBO_ENC_FLTR0, &CDlgEncModu::OnCbnSelchangeComboEncFltr)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_FLTR1, &CDlgEncModu::OnCbnSelchangeComboEncFltr)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_FLTR2, &CDlgEncModu::OnCbnSelchangeComboEncFltr)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_FLTR3, &CDlgEncModu::OnCbnSelchangeComboEncFltr)
	ON_CBN_SELCHANGE(IDC_COMBO_ENC_FLTR, &CDlgEncModu::OnCbnSelchangeComboEncFltr)

	ON_BN_CLICKED(IDC_CHK_ENC_TST_ENB, &CDlgEncModu::OnBnClickedChkEncTstEnb)
	ON_BN_CLICKED(IDC_BTN_ENC_TST_TRIG, &CDlgEncModu::OnBnClickedBtnEncTstTrig)
	ON_BN_CLICKED(IDC_CHK_ENC_TST_CONT, &CDlgEncModu::OnBnClickedChkEncTstCont)
	ON_BN_CLICKED(IDC_BTN_RST_ENC_MEAS, &CDlgEncModu::OnBnClickedBtnRstEncMeas)
	ON_CBN_SELCHANGE(IDC_COMB_ENC_CHAN, &CDlgEncModu::OnCbnSelchangeCombEncChan)
	ON_BN_CLICKED(IDC_BTN_RD_ENC_CNTR, &CDlgEncModu::OnBnClickedBtnRdEncCntr)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgEncModu::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	CString str;

	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 编码器使能

	BOOL all = FALSE;
	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		BOOL enb = enc_modu.m_bEnb[i];
		m_chkEncEnb[i].SetCheck(enb);
		EnbEncCtrl(i, enb);
		if (enb == TRUE)
		{
			all = TRUE;
		}
	}

	if (all == FALSE)
	{
		EnbEncCtrl(TOT_ENC_NUM, FALSE);	// 全部禁止
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 回零使能

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		m_chkEncZe[i].SetCheck(enc_modu.m_bZe[i]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 编码器极性

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		m_chkEncPol[i].SetCheck(enc_modu.m_nPol[i]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 扫查编码器

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		m_radScanEnc[i].SetCheck(enc_modu.m_bScan[i]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 编码器类型

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		m_combEncType[i].ResetContent();
		for (U8 j = 0; j < ENC_TYPE_MAX; j++)
		{
			m_combEncType[i].AddString(ENC_TYPE_STR[j]);
		}
		m_combEncType[i].SetCurSel(enc_modu.m_nType[i]);
	}

		m_combEncType[TOT_ENC_NUM].ResetContent();
		for (U8 j = 0; j < ENC_TYPE_MAX; j++)
		{
			m_combEncType[TOT_ENC_NUM].AddString(ENC_TYPE_STR[j]);
		}
		m_combEncType[TOT_ENC_NUM].SetCurSel(ENC_TYPE_QUAD);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 编码器滤波

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		U8 enc_fltr = m_pApp->m_stFlawParam.m_stEncModu[0].m_nFltr[0];
		m_combEncFltr[i].ResetContent();
		for (U8 j = ENC_FLTR_MIN; j <= ENC_FLTR_MAX; j++)
		{
			m_combEncFltr[i].AddString(ENC_FLTR_STR[j]);
		}
		m_combEncFltr[i].SetCurSel(enc_modu.m_nFltr[i]);
	}

		m_combEncFltr[TOT_ENC_NUM].ResetContent();
		for (U8 j = ENC_FLTR_MIN; j <= ENC_FLTR_MAX; j++)
		{
			m_combEncFltr[TOT_ENC_NUM].AddString(ENC_FLTR_STR[j]);
		}
		m_combEncFltr[TOT_ENC_NUM].SetCurSel(ENC_FLTR_10KHZ);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 扫查间隔

	str.Format("%d", m_pApp->m_stFlawParam.m_nScanSpan);
	m_edtScanSpan.SetWindowText(str);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 编码器测试

	m_chkEncTstEnb.SetCheck(enc_modu.m_nTstEnb);	// 测试使能

	// 测试脉冲数
	str.Format("%d", enc_modu.m_nTstPulNum);
	m_edtEncTstPulNum.SetWindowText(str);

	// 测试线数
	str.Format("%d", enc_modu.m_nTstLineNum);
	m_edtEncTstLineNum.SetWindowText(str);

	m_chkEncTstCont.SetCheck(enc_modu.m_bTstCont);	// 持续测试

	// 测试频率
	str.Format("%d", enc_modu.m_nTstFreq);
	m_edtEncTstFreq.SetWindowText(str);

	GetEncTstFreq(str);
	m_txtEncTstFreq.SetWindowText(str);

	GetEncScanFreq(str);
	m_txtEncScanFreq.SetWindowText(str);

	FreshEncTstCtrl();

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 编码器测量

	m_combEncIdx.ResetContent();
	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		str.Format("%d", i);
		m_combEncIdx.AddString(str);
	}
	m_combEncIdx.SetCurSel(m_nEncChan);
	ZXUT_SetEncMeasChan(brd_num, m_nEncChan);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 刷新编码器测试控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::FreshEncTstCtrl(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	BOOL all_dis = TRUE;
	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		if (enc_modu.m_bEnb[i] == TRUE)
		{
			all_dis = FALSE;	// 至少有一个编码器使能
		}
	}

	if (all_dis == TRUE)
	{
		// 全部编码器禁止，测试当然也要禁止
		m_chkEncTstEnb.EnableWindow(FALSE);
		m_edtEncTstPulNum.EnableWindow(FALSE);
		m_edtEncTstLineNum.EnableWindow(FALSE);
		m_txtEncTstFreq.EnableWindow(FALSE);
		m_txtEncScanFreq.EnableWindow(FALSE);
		m_edtEncTstFreq.EnableWindow(FALSE);
		m_chkEncTstCont.EnableWindow(FALSE);
		m_btnEncTstTrig.EnableWindow(FALSE);
		return;
	}

		m_chkEncTstEnb.EnableWindow(TRUE);

	BOOL act = enc_modu.m_nTstEnb;
	{
		m_edtEncTstPulNum.EnableWindow(act);
		m_edtEncTstLineNum.EnableWindow(act);
		m_txtEncTstFreq.EnableWindow(act);
		m_txtEncScanFreq.EnableWindow(act);
		m_edtEncTstFreq.EnableWindow(act);
		m_chkEncTstCont.EnableWindow(act);
		m_btnEncTstTrig.EnableWindow(act);

		if (act == TRUE)
		{
			m_edtEncTstPulNum.EnableWindow(enc_modu.m_bTstCont == FALSE);
			m_btnEncTstTrig.EnableWindow(enc_modu.m_bTstCont == FALSE);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::EnbEncCtrl(U8 enc_chan, BOOL enb)
{
	if (enc_chan == TOT_ENC_NUM)
	{
		m_edtScanSpan		.EnableWindow(enb);
	}
	else
	{
		m_txtEabCntr	[enc_chan].EnableWindow(enb);
		m_txtEzCntr		[enc_chan].EnableWindow(enb);
		m_radScanEnc	[enc_chan].EnableWindow(enb);
	}

		m_chkEncZe		[enc_chan].EnableWindow(enb);
		m_btnRstEncCntr	[enc_chan].EnableWindow(enb);
		m_chkEncPol		[enc_chan].EnableWindow(enb);
		m_combEncType	[enc_chan].EnableWindow(enb);
		m_combEncFltr	[enc_chan].EnableWindow(enb);
}

void CDlgEncModu::OnBnClickedChkEncEnb(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U8 enc_chan;
	if (GetFocus() == &m_chkEncEnb[0])
	{
		enc_chan = 0;
	}
	else if (GetFocus() == &m_chkEncEnb[1])
	{
		enc_chan = 1;
	}
	else if (GetFocus() == &m_chkEncEnb[2])
	{
		enc_chan = 2;
	}
	else if (GetFocus() == &m_chkEncEnb[3])
	{
		enc_chan = 3;
	}
	else
	{
		enc_chan = 4;
		int chk = m_chkEncEnb[enc_chan].GetCheck();

		// 全部
		for (U8 i = 0; i < TOT_ENC_NUM; i++)
		{
			m_chkEncEnb[i].SetCheck(chk);
			ZXUT_SetEncEnb(brd_num, i, chk);
			enc_modu.m_bEnb[i] = chk;
			EnbEncCtrl(i, chk);
		}

		EnbEncCtrl(enc_chan, chk);
		FreshEncTstCtrl();
		return;
	}

	// 单个
	int chk = m_chkEncEnb[enc_chan].GetCheck();
	ZXUT_SetEncEnb(brd_num, enc_chan, chk);
	enc_modu.m_bEnb[enc_chan] = chk;
	EnbEncCtrl(enc_chan, chk);
	FreshEncTstCtrl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新编码器计数值
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::UpdEncCntr(U32* encab_cntr, U32* encz_cntr)
{
	CString str;

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		str.Format("%d", encab_cntr[i]);
		m_txtEabCntr[i].SetWindowText(str);

		str.Format("%d", encz_cntr[i]);
		m_txtEzCntr[i].SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器回零使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedChkEncZe(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U8 enc_chan;
	if (GetFocus() == &m_chkEncZe[0])
	{
		enc_chan = 0;
	}
	else if (GetFocus() == &m_chkEncZe[1])
	{
		enc_chan = 1;
	}
	else if (GetFocus() == &m_chkEncZe[2])
	{
		enc_chan = 2;
	}
	else if (GetFocus() == &m_chkEncZe[3])
	{
		enc_chan = 3;
	}
	else
	{
		enc_chan = 4;
		int chk = m_chkEncZe[enc_chan].GetCheck();

		// 全部
		for (U8 i = 0; i < TOT_ENC_NUM; i++)
		{
			m_chkEncZe[i].SetCheck(chk);
			ZXUT_SetEncZe(brd_num, i, chk);
			enc_modu.m_bZe[i] = chk;
		}
		return;
	}

	// 单个
	int chk = m_chkEncZe[enc_chan].GetCheck();
	ZXUT_SetEncZe(brd_num, enc_chan, chk);
	enc_modu.m_bZe[enc_chan] = chk;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器复位
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::RstEncCntr(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		ZXUT_SetEabCntr(brd_num, i, 0);
		ZXUT_SetEzCntr(brd_num, i, 0);
	}
}

void CDlgEncModu::OnBnClickedBtnRstEncCntr(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U8 enc_chan;
	if (GetFocus() == &m_btnRstEncCntr[0])
	{
		enc_chan = 0;
	}
	else if (GetFocus() == &m_btnRstEncCntr[1])
	{
		enc_chan = 1;
	}
	else if (GetFocus() == &m_btnRstEncCntr[2])
	{
		enc_chan = 2;
	}
	else if (GetFocus() == &m_btnRstEncCntr[3])
	{
		enc_chan = 3;
	}
	else
	{
		enc_chan = 4;
		RstEncCntr();	// 全部
		return;
	}

	// 单个
	ZXUT_SetEabCntr(brd_num, enc_chan, 0);
	ZXUT_SetEzCntr(brd_num, enc_chan, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器极性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedChkEncPol(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U8 enc_chan;
	if (GetFocus() == &m_chkEncPol[0])
	{
		enc_chan = 0;
	}
	else if (GetFocus() == &m_chkEncPol[1])
	{
		enc_chan = 1;
	}
	else if (GetFocus() == &m_chkEncPol[2])
	{
		enc_chan = 2;
	}
	else if (GetFocus() == &m_chkEncPol[3])
	{
		enc_chan = 3;
	}
	else
	{
		enc_chan = 4;
		int chk = m_chkEncPol[enc_chan].GetCheck();

		// 全部
		for (U8 i = 0; i < TOT_ENC_NUM; i++)
		{
			enc_modu.m_nPol[i] = chk;
			ZXUT_SetEncPol(brd_num, i, chk);
			m_chkEncPol[i].SetCheck(chk);
		}

		return;
	}

	// 单个
	int chk = m_chkEncPol[enc_chan].GetCheck();
	enc_modu.m_nPol[enc_chan] = chk;
	ZXUT_SetEncPol(brd_num, enc_chan, chk);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 扫查编码器
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedRadScanEnc(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	for (U8 i = 0; i < TOT_ENC_NUM; i++)
	{
		enc_modu.m_bScan[i] = m_radScanEnc[i].GetCheck();
		if (enc_modu.m_bScan[i])
		{
			ZXUT_SetScanEnc(brd_num, i);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器类型
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnCbnSelchangeComboEncType(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U8 enc_chan;
	if (GetFocus() == &m_combEncType[0])
	{
		enc_chan = 0;
	}
	else if (GetFocus() == &m_combEncType[1])
	{
		enc_chan = 1;
	}
	else if (GetFocus() == &m_combEncType[2])
	{
		enc_chan = 2;
	}
	else if (GetFocus() == &m_combEncType[3])
	{
		enc_chan = 3;
	}
	else
	{
		enc_chan = 4;
		int idx = m_combEncType[enc_chan].GetCurSel();

		// 全部
		for (U8 i = 0; i < TOT_ENC_NUM; i++)
		{
			enc_modu.m_nType[i] = idx;
			ZXUT_SetEncType(brd_num, i, idx);
			m_combEncType[i].SetCurSel(idx);
		}

		return;
	}

	// 单个
	int idx = m_combEncType[enc_chan].GetCurSel();
	enc_modu.m_nType[enc_chan] = idx;
	ZXUT_SetEncType(brd_num, enc_chan, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器滤波
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnCbnSelchangeComboEncFltr(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U8 enc_chan;
	if (GetFocus() == &m_combEncFltr[0])
	{
		enc_chan = 0;
	}
	else if (GetFocus() == &m_combEncFltr[1])
	{
		enc_chan = 1;
	}
	else if (GetFocus() == &m_combEncFltr[2])
	{
		enc_chan = 2;
	}
	else if (GetFocus() == &m_combEncFltr[3])
	{
		enc_chan = 3;
	}
	else
	{
		enc_chan = 4;
		int idx = m_combEncFltr[enc_chan].GetCurSel();

		// 全部
		for (U8 i = 0; i < TOT_ENC_NUM; i++)
		{
			enc_modu.m_nFltr[i] = idx;
			ZXUT_SetEncFltr(brd_num, i, idx);
			m_combEncFltr[i].SetCurSel(idx);
		}

		return;
	}

	// 单个
	int idx = m_combEncFltr[enc_chan].GetCurSel();
	enc_modu.m_nFltr[enc_chan] = idx;
	ZXUT_SetEncFltr(brd_num, enc_chan, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 测试使能，针对所有4个编码器有效
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedChkEncTstEnb(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	int chk = m_chkEncTstEnb.GetCheck();
	enc_modu.m_nTstEnb = chk;
	ZXUT_SetEncTstEnb(brd_num, enc_modu.m_nTstEnb);

	RstEncCntr();
	FreshEncTstCtrl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 预翻译信息

BOOL CDlgEncModu::PreTranslateMessage(MSG* pMsg)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];
	CString str;

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:	// 屏蔽回车键
			{
				////////////////////////////////////////////////////////////////////////////////////
				// 扫查间隔

				if (GetFocus() == &m_edtScanSpan)
				{
					m_edtScanSpan.GetWindowText(str);
					U16 bak = m_pApp->m_stFlawParam.m_nScanSpan;
					U16 tmp = atoi(str);
					if ((tmp < 1) || (tmp > 1000))
					{
						m_pApp->DispMsg(ZXUT_MSG_ERR, "需要输入1到1000之间的整数");
						str.Format("%d", bak);
						m_edtScanSpan.SetWindowText(str);
					}
					else
					{
						m_pApp->m_stFlawParam.m_nScanSpan = tmp;
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetScanSpan(brd_num, tmp);
						}

						GetEncScanFreq(str);
						m_txtEncScanFreq.SetWindowText(str);
					}
				}

				////////////////////////////////////////////////////////////////////////////////////
				// 编码器测试频率

				else if (GetFocus() == &m_edtEncTstFreq)
				{
					m_edtEncTstFreq.GetWindowText(str);
					U32 bak = enc_modu.m_nTstFreq;
					U32 tmp = atoi(str);
					if ((tmp < 50) || (tmp > 500000))
					{
						m_pApp->DispMsg(ZXUT_MSG_ERR, "需要输入100到500000之间的整数");
						str.Format("%d", bak);
						m_edtEncTstFreq.SetWindowText(str);
					}
					else
					{
						enc_modu.m_nTstFreq = tmp;
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetEncTstFreq(brd_num, tmp);
						}

						GetEncTstFreq(str);
						m_txtEncTstFreq.SetWindowText(str);

						GetEncScanFreq(str);
						m_txtEncScanFreq.SetWindowText(str);

						ZXUT_SetEncMeasChan(brd_num, m_nEncChan);
					}
				}

				////////////////////////////////////////////////////////////////////////////////////
				// 编码器测试脉冲数

				else if (GetFocus() == &m_edtEncTstPulNum)
				{
					m_edtEncTstPulNum.GetWindowText(str);
					U16 bak = enc_modu.m_nTstPulNum;
					U16 tmp = atoi(str);
					if (tmp > 60000)
					{
						m_pApp->DispMsg(ZXUT_MSG_ERR, "需要输入小于60000的整数");
						str.Format("%d", bak);
						m_edtEncTstPulNum.SetWindowText(str);
					}
					else
					{
						enc_modu.m_nTstPulNum = tmp;
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetEncTstPulNum(brd_num, tmp);
						}
					}
				}

				////////////////////////////////////////////////////////////////////////////////////
				// 编码器测试线数

				else if (GetFocus() == &m_edtEncTstLineNum)
				{
					m_edtEncTstLineNum.GetWindowText(str);
					U16 bak = enc_modu.m_nTstLineNum;
					U16 tmp = atoi(str);
					if ((tmp < 50) || (tmp > 10000))
					{
						m_pApp->DispMsg(ZXUT_MSG_ERR, "需要输入50到10000之间的整数");
						str.Format("%d", bak);
						m_edtEncTstLineNum.SetWindowText(str);
					}
					else
					{
						enc_modu.m_nTstLineNum = tmp;
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetEncTstLineNum(brd_num, tmp);
						}
					}
				}

				return TRUE;
			}

		case VK_ESCAPE:	// 屏蔽ESC键
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器测试触发
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedBtnEncTstTrig(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ZXUT_SetEncTstTrig(brd_num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器测试频率，转换为KHz字符串
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::GetEncTstFreq(CString& str)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	U32 enc_tst_freq = enc_modu.m_nTstFreq;
	if (enc_tst_freq >= 1000)
	{
		str.Format("%d.%dKHz", enc_tst_freq / 1000, enc_tst_freq % 1000);
	}
	else
	{
		str.Format("%dHz", enc_tst_freq);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器扫查频率，转换为KHz字符串
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::GetEncScanFreq(CString& str)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	U32 enc_tst_freq = m_pApp->m_stFlawParam.m_stEncModu[brd_num].m_nTstFreq;
	U32 enc_scan_span = m_pApp->m_stFlawParam.m_nScanSpan;
	U32 enc_scan_freq = enc_tst_freq / enc_scan_span;
	if (enc_scan_freq >= 1000)
	{
		str.Format("%d.%dKHz", enc_scan_freq / 1000, enc_scan_freq % 1000);
	}
	else
	{
		str.Format("%dHz", enc_scan_freq);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 是否持续测试
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedChkEncTstCont(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ST_ENC_MODU& enc_modu = m_pApp->m_stFlawParam.m_stEncModu[brd_num];

	enc_modu.m_bTstCont = m_chkEncTstCont.GetCheck();
	m_btnEncTstTrig.EnableWindow(enc_modu.m_bTstCont == FALSE);
	FreshEncTstCtrl();

	if (enc_modu.m_bTstCont)
	{
		ZXUT_SetEncTstMode(brd_num, ENC_TST_MODE_CONT);	// 持续
	}
	else
	{
		ZXUT_SetEncTstMode(brd_num, ENC_TST_MODE_BURST);	// 猝发(按指定脉冲数)
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 编码器测量复位
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnBnClickedBtnRstEncMeas(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ZXUT_SetEncMeasChan(brd_num, m_nEncChan);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新编码器测量结果
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::UpdEncMeasRes(ST_RQ_DATA& daq_buf)
{
/*	CString str;
	U32 res = daq_buf.m_nEncMeasRes;
	if (res >= 1000)
	{
		str.Format("%d.%03dKHz", res / 1000, res % 1000);
	}
	else
	{
		str.Format("%dHz", res);
	}
	m_txtEncMeasFreq.SetWindowText(str);*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 选择编码器测量索引
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgEncModu::OnCbnSelchangeCombEncChan()
{
	m_nEncChan = m_combEncIdx.GetCurSel();

	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	ZXUT_SetEncMeasChan(brd_num, m_nEncChan);
}


void CDlgEncModu::OnBnClickedBtnRdEncCntr(void)
{
	U8 brd_num = m_pApp->m_nHardNum / x_nTotHard;
	U32 enc_cntr = ZXUT_GetEncCntr(brd_num, 1);	// 读取第二个编码器，序号为1
	TRACE("enc_cntr[1] = %d\n", enc_cntr);

	CString str;
	str.Format("%d\n", enc_cntr);
	((CStatic*)GetDlgItem(IDC_TXT_ENC_CNTR))->SetWindowText(str);
}
