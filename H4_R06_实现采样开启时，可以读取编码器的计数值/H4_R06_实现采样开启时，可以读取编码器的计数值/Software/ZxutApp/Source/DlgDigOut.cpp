#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgDigOut.h"
#include "ZxutDlg.h"
#include "XSleep.h"

IMPLEMENT_DYNAMIC(CDlgDigOut, CDialog)

CDlgDigOut::CDlgDigOut(CWnd* pParent) : CDialog(CDlgDigOut::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgDigOut = this;
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
}

CDlgDigOut::~CDlgDigOut(void)
{
}

void CDlgDigOut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_DO_CMD0, m_chkDoCmd[0]);
	DDX_Control(pDX, IDC_CHK_DO_CMD1, m_chkDoCmd[1]);
	DDX_Control(pDX, IDC_CHK_DO_CMD2, m_chkDoCmd[2]);
	DDX_Control(pDX, IDC_CHK_DO_CMD3, m_chkDoCmd[3]);
	DDX_Control(pDX, IDC_CHK_DO_CMD4, m_chkDoCmd[4]);
	DDX_Control(pDX, IDC_CHK_DO_CMD5, m_chkDoCmd[5]);
	DDX_Control(pDX, IDC_CHK_DO_CMD6, m_chkDoCmd[6]);
	DDX_Control(pDX, IDC_CHK_DO_CMD7, m_chkDoCmd[7]);

	DDX_Control(pDX, IDC_CHK_DO_ENB0, m_chkDoEnb[0]);
	DDX_Control(pDX, IDC_CHK_DO_ENB1, m_chkDoEnb[1]);
	DDX_Control(pDX, IDC_CHK_DO_ENB2, m_chkDoEnb[2]);
	DDX_Control(pDX, IDC_CHK_DO_ENB3, m_chkDoEnb[3]);
	DDX_Control(pDX, IDC_CHK_DO_ENB4, m_chkDoEnb[4]);
	DDX_Control(pDX, IDC_CHK_DO_ENB5, m_chkDoEnb[5]);
	DDX_Control(pDX, IDC_CHK_DO_ENB6, m_chkDoEnb[6]);
	DDX_Control(pDX, IDC_CHK_DO_ENB7, m_chkDoEnb[7]);

	DDX_Control(pDX, IDC_COMBO_DO_MODE0, m_combDoMode[0]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE1, m_combDoMode[1]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE2, m_combDoMode[2]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE3, m_combDoMode[3]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE4, m_combDoMode[4]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE5, m_combDoMode[5]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE6, m_combDoMode[6]);
	DDX_Control(pDX, IDC_COMBO_DO_MODE7, m_combDoMode[7]);

	DDX_Control(pDX, IDC_COMBO_DO_POL0, m_combDoPol[0]);
	DDX_Control(pDX, IDC_COMBO_DO_POL1, m_combDoPol[1]);
	DDX_Control(pDX, IDC_COMBO_DO_POL2, m_combDoPol[2]);
	DDX_Control(pDX, IDC_COMBO_DO_POL3, m_combDoPol[3]);
	DDX_Control(pDX, IDC_COMBO_DO_POL4, m_combDoPol[4]);
	DDX_Control(pDX, IDC_COMBO_DO_POL5, m_combDoPol[5]);
	DDX_Control(pDX, IDC_COMBO_DO_POL6, m_combDoPol[6]);
	DDX_Control(pDX, IDC_COMBO_DO_POL7, m_combDoPol[7]);

	DDX_Control(pDX, IDC_SPIN_DO_WIDTH0, m_spinDoWidth[0]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH1, m_spinDoWidth[1]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH2, m_spinDoWidth[2]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH3, m_spinDoWidth[3]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH4, m_spinDoWidth[4]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH5, m_spinDoWidth[5]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH6, m_spinDoWidth[6]);
	DDX_Control(pDX, IDC_SPIN_DO_WIDTH7, m_spinDoWidth[7]);

	DDX_Control(pDX, IDC_TXT_DO_WIDTH0, m_txtDoWidth[0]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH1, m_txtDoWidth[1]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH2, m_txtDoWidth[2]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH3, m_txtDoWidth[3]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH4, m_txtDoWidth[4]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH5, m_txtDoWidth[5]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH6, m_txtDoWidth[6]);
	DDX_Control(pDX, IDC_TXT_DO_WIDTH7, m_txtDoWidth[7]);

	DDX_Control(pDX, IDC_SPIN_DO_DLY0, m_spinDoDly[0]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY1, m_spinDoDly[1]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY2, m_spinDoDly[2]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY3, m_spinDoDly[3]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY4, m_spinDoDly[4]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY5, m_spinDoDly[5]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY6, m_spinDoDly[6]);
	DDX_Control(pDX, IDC_SPIN_DO_DLY7, m_spinDoDly[7]);

	DDX_Control(pDX, IDC_TXT_DO_DLY0, m_txtDoDly[0]);
	DDX_Control(pDX, IDC_TXT_DO_DLY1, m_txtDoDly[1]);
	DDX_Control(pDX, IDC_TXT_DO_DLY2, m_txtDoDly[2]);
	DDX_Control(pDX, IDC_TXT_DO_DLY3, m_txtDoDly[3]);
	DDX_Control(pDX, IDC_TXT_DO_DLY4, m_txtDoDly[4]);
	DDX_Control(pDX, IDC_TXT_DO_DLY5, m_txtDoDly[5]);
	DDX_Control(pDX, IDC_TXT_DO_DLY6, m_txtDoDly[6]);
	DDX_Control(pDX, IDC_TXT_DO_DLY7, m_txtDoDly[7]);

	DDX_Control(pDX, IDC_BTN_DO_TRIG0, m_btnDoTrig[0]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG1, m_btnDoTrig[1]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG2, m_btnDoTrig[2]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG3, m_btnDoTrig[3]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG4, m_btnDoTrig[4]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG5, m_btnDoTrig[5]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG6, m_btnDoTrig[6]);
	DDX_Control(pDX, IDC_BTN_DO_TRIG7, m_btnDoTrig[7]);

	DDX_Control(pDX, IDC_COMBO_DO_BASE, m_combDoBase);
}

BEGIN_MESSAGE_MAP(CDlgDigOut, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_BASE, &CDlgDigOut::OnCbnSelchangeComboDoBase)

	ON_BN_CLICKED(IDC_CHK_DO_ENB0, OnBnClickedChkDoEnb0)
	ON_BN_CLICKED(IDC_CHK_DO_ENB1, OnBnClickedChkDoEnb1)
	ON_BN_CLICKED(IDC_CHK_DO_ENB2, OnBnClickedChkDoEnb2)
	ON_BN_CLICKED(IDC_CHK_DO_ENB3, OnBnClickedChkDoEnb3)
	ON_BN_CLICKED(IDC_CHK_DO_ENB4, OnBnClickedChkDoEnb4)
	ON_BN_CLICKED(IDC_CHK_DO_ENB5, OnBnClickedChkDoEnb5)
	ON_BN_CLICKED(IDC_CHK_DO_ENB6, OnBnClickedChkDoEnb6)
	ON_BN_CLICKED(IDC_CHK_DO_ENB7, OnBnClickedChkDoEnb7)

	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE0, &CDlgDigOut::OnCbnSelchangeComboDoMode0)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE1, &CDlgDigOut::OnCbnSelchangeComboDoMode1)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE2, &CDlgDigOut::OnCbnSelchangeComboDoMode2)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE3, &CDlgDigOut::OnCbnSelchangeComboDoMode3)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE4, &CDlgDigOut::OnCbnSelchangeComboDoMode4)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE5, &CDlgDigOut::OnCbnSelchangeComboDoMode5)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE6, &CDlgDigOut::OnCbnSelchangeComboDoMode6)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_MODE7, &CDlgDigOut::OnCbnSelchangeComboDoMode7)

	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL0, OnCbnSelchangeComboDoPol0)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL1, OnCbnSelchangeComboDoPol1)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL2, OnCbnSelchangeComboDoPol2)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL3, OnCbnSelchangeComboDoPol3)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL4, OnCbnSelchangeComboDoPol4)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL5, OnCbnSelchangeComboDoPol5)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL6, OnCbnSelchangeComboDoPol6)
	ON_CBN_SELCHANGE(IDC_COMBO_DO_POL7, OnCbnSelchangeComboDoPol7)

	ON_BN_CLICKED(IDC_BTN_DO_TRIG0, &CDlgDigOut::OnBnClickedBtnDoTrig0)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG1, &CDlgDigOut::OnBnClickedBtnDoTrig1)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG2, &CDlgDigOut::OnBnClickedBtnDoTrig2)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG3, &CDlgDigOut::OnBnClickedBtnDoTrig3)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG4, &CDlgDigOut::OnBnClickedBtnDoTrig4)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG5, &CDlgDigOut::OnBnClickedBtnDoTrig5)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG6, &CDlgDigOut::OnBnClickedBtnDoTrig6)
	ON_BN_CLICKED(IDC_BTN_DO_TRIG7, &CDlgDigOut::OnBnClickedBtnDoTrig7)

	ON_BN_CLICKED(IDC_CHK_DO_CMD0, &CDlgDigOut::OnBnClickedChkDoCmd0)
	ON_BN_CLICKED(IDC_CHK_DO_CMD1, &CDlgDigOut::OnBnClickedChkDoCmd1)
	ON_BN_CLICKED(IDC_CHK_DO_CMD2, &CDlgDigOut::OnBnClickedChkDoCmd2)
	ON_BN_CLICKED(IDC_CHK_DO_CMD3, &CDlgDigOut::OnBnClickedChkDoCmd3)
	ON_BN_CLICKED(IDC_CHK_DO_CMD4, &CDlgDigOut::OnBnClickedChkDoCmd4)
	ON_BN_CLICKED(IDC_CHK_DO_CMD5, &CDlgDigOut::OnBnClickedChkDoCmd5)
	ON_BN_CLICKED(IDC_CHK_DO_CMD6, &CDlgDigOut::OnBnClickedChkDoCmd6)
	ON_BN_CLICKED(IDC_CHK_DO_CMD7, &CDlgDigOut::OnBnClickedChkDoCmd7)
	ON_BN_CLICKED(IDC_BTN_AUO_TST_DO, &CDlgDigOut::OnBnClickedBtnAuoTstDo)
	ON_BN_CLICKED(IDC_BTN_ALL_DO_SET, &CDlgDigOut::OnBnClickedBtnAllDoSet)
	ON_BN_CLICKED(IDC_BTN_ALL_DO_CLR, &CDlgDigOut::OnBnClickedBtnAllDoClr)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

BOOL CDlgDigOut::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	CString str;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 时基

	m_combDoBase.ResetContent();
	for (U32 i = 0; i < 10; i++)
	{
		str.Format("%.1fms", (i + 1) * 0.1f);
		m_combDoBase.AddString(str);
	}
	m_combDoBase.SetCurSel(stDigOut.m_nBase);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 使能

	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		m_chkDoEnb[i].SetCheck(stDigOut.m_bEnb[i]);
		m_combDoMode[i].EnableWindow(stDigOut.m_bEnb[i]);
		m_combDoPol[i].EnableWindow(stDigOut.m_bEnb[i]);
		m_btnDoTrig[i].EnableWindow(stDigOut.m_bEnb[i]);
		EnbDoWidthDly(i, stDigOut.m_bEnb[i]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 模式

	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		m_combDoMode[i].ResetContent();
		m_combDoMode[i].AddString("脉冲");		// 0
		m_combDoMode[i].AddString("电平");		// 1
		m_combDoMode[i].SetCurSel(stDigOut.m_nMode[i]);

		BOOL enb = (stDigOut.m_nMode[i] == DIO_MODE_PUL) && (stDigOut.m_bEnb[i] == TRUE);
		m_btnDoTrig[i].EnableWindow(enb);
		m_chkDoCmd[i].EnableWindow(!enb);
		EnbDoWidthDly(i, enb);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 极性

	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		m_combDoPol[i].ResetContent();
		m_combDoPol[i].AddString("负极性");	// 0
		m_combDoPol[i].AddString("正极性");	// 1
		m_combDoPol[i].SetCurSel(stDigOut.m_nPol[i]);
	}

	UpdDoWidth();	// 宽度
	UpdDoDly();		// 延迟

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 时基
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::OnCbnSelchangeComboDoBase(void)
{
	CString str;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;
	stDigOut.m_nBase = m_combDoBase.GetCurSel();

	U32 do_base = (stDigOut.m_nBase + 1) * 100;	// us
	ZXUT_SetDoBase(do_base);

	UpdDoWidth();	// 更新宽度
	UpdDoDly();		// 更新延迟
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置DO使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::SetDoEnb(U8 do_chan)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;
	U8& do_enb = stDigOut.m_bEnb[do_chan];
	do_enb = m_chkDoEnb[do_chan].GetCheck();

	ZXUT_SetDoEnb(do_chan, do_enb);

	m_combDoMode[do_chan].EnableWindow(do_enb);
	m_combDoPol[do_chan].EnableWindow(do_enb);
	m_btnDoTrig[do_chan].EnableWindow(do_enb);
	EnbDoWidthDly(do_chan, do_enb);

	if (do_enb == TRUE)
	{
		BOOL enb = (stDigOut.m_nMode[do_chan] == DIO_MODE_PUL);
		m_btnDoTrig[do_chan].EnableWindow(enb);
		m_chkDoCmd[do_chan].EnableWindow(!enb);
		EnbDoWidthDly(do_chan, enb);
	}
}

void CDlgDigOut::OnBnClickedChkDoEnb0(void) { SetDoEnb(0); }
void CDlgDigOut::OnBnClickedChkDoEnb1(void) { SetDoEnb(1); }
void CDlgDigOut::OnBnClickedChkDoEnb2(void) { SetDoEnb(2); }
void CDlgDigOut::OnBnClickedChkDoEnb3(void) { SetDoEnb(3); }
void CDlgDigOut::OnBnClickedChkDoEnb4(void) { SetDoEnb(4); }
void CDlgDigOut::OnBnClickedChkDoEnb5(void) { SetDoEnb(5); }
void CDlgDigOut::OnBnClickedChkDoEnb6(void) { SetDoEnb(6); }
void CDlgDigOut::OnBnClickedChkDoEnb7(void) { SetDoEnb(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 模式
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::SetDoMode(U8 do_chan)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;
	U8& di_mode = stDigOut.m_nMode[do_chan];
	di_mode = m_combDoMode[do_chan].GetCurSel();

	ZXUT_SetDoMode(do_chan, di_mode);

	BOOL enb = (di_mode == DIO_MODE_PUL);
	m_btnDoTrig[do_chan].EnableWindow(enb);
	m_chkDoCmd[do_chan].EnableWindow(!enb);
	EnbDoWidthDly(do_chan, enb);
}

void CDlgDigOut::OnCbnSelchangeComboDoMode0(void) { SetDoMode(0); }
void CDlgDigOut::OnCbnSelchangeComboDoMode1(void) { SetDoMode(1); }
void CDlgDigOut::OnCbnSelchangeComboDoMode2(void) { SetDoMode(2); }
void CDlgDigOut::OnCbnSelchangeComboDoMode3(void) { SetDoMode(3); }
void CDlgDigOut::OnCbnSelchangeComboDoMode4(void) { SetDoMode(4); }
void CDlgDigOut::OnCbnSelchangeComboDoMode5(void) { SetDoMode(5); }
void CDlgDigOut::OnCbnSelchangeComboDoMode6(void) { SetDoMode(6); }
void CDlgDigOut::OnCbnSelchangeComboDoMode7(void) { SetDoMode(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置DI极性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::SetDoPol(U8 do_chan)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;
	stDigOut.m_nPol[do_chan] = m_combDoPol[do_chan].GetCurSel();
	ZXUT_SetDoPol(do_chan, stDigOut.m_nPol[do_chan]);
}

void CDlgDigOut::OnCbnSelchangeComboDoPol0(void) { SetDoPol(0); }
void CDlgDigOut::OnCbnSelchangeComboDoPol1(void) { SetDoPol(1); }
void CDlgDigOut::OnCbnSelchangeComboDoPol2(void) { SetDoPol(2); }
void CDlgDigOut::OnCbnSelchangeComboDoPol3(void) { SetDoPol(3); }
void CDlgDigOut::OnCbnSelchangeComboDoPol4(void) { SetDoPol(4); }
void CDlgDigOut::OnCbnSelchangeComboDoPol5(void) { SetDoPol(5); }
void CDlgDigOut::OnCbnSelchangeComboDoPol6(void) { SetDoPol(6); }
void CDlgDigOut::OnCbnSelchangeComboDoPol7(void) { SetDoPol(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 宽度
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::UpdDoWidth(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;

	CString str;
	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		U16 pos = stDigOut.m_nWidth[i] + 1;
		m_spinDoWidth[i].SetRange(1, 10);	// 0 - 9
		m_spinDoWidth[i].SetPos(pos);

		F32 do_width = pos * 10 * (stDigOut.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", do_width);
		m_txtDoWidth[i].SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 延迟
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::UpdDoDly(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;

	CString str;
	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		U16 pos = stDigOut.m_nDly[i];
		m_spinDoDly[i].SetRange(0, 10);	// 0 - 10
		m_spinDoDly[i].SetPos(pos);

		F32 do_dly = pos * 10 * (stDigOut.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", do_dly);
		m_txtDoDly[i].SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 触发
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::SetDoTrig(U8 do_chan)
{
	ZXUT_SetDoCmd(do_chan, 0);
}

void CDlgDigOut::OnBnClickedBtnDoTrig0(void) { SetDoTrig(0); }
void CDlgDigOut::OnBnClickedBtnDoTrig1(void) { SetDoTrig(1); }
void CDlgDigOut::OnBnClickedBtnDoTrig2(void) { SetDoTrig(2); }
void CDlgDigOut::OnBnClickedBtnDoTrig3(void) { SetDoTrig(3); }
void CDlgDigOut::OnBnClickedBtnDoTrig4(void) { SetDoTrig(4); }
void CDlgDigOut::OnBnClickedBtnDoTrig5(void) { SetDoTrig(5); }
void CDlgDigOut::OnBnClickedBtnDoTrig6(void) { SetDoTrig(6); }
void CDlgDigOut::OnBnClickedBtnDoTrig7(void) { SetDoTrig(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 命令
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::SetDoCmd(U8 do_chan)
{
	BOOL chk = m_chkDoCmd[do_chan].GetCheck();
	ZXUT_SetDoCmd(do_chan, chk);
}

void CDlgDigOut::OnBnClickedChkDoCmd0(void) { SetDoCmd(0); }
void CDlgDigOut::OnBnClickedChkDoCmd1(void) { SetDoCmd(1); }
void CDlgDigOut::OnBnClickedChkDoCmd2(void) { SetDoCmd(2); }
void CDlgDigOut::OnBnClickedChkDoCmd3(void) { SetDoCmd(3); }
void CDlgDigOut::OnBnClickedChkDoCmd4(void) { SetDoCmd(4); }
void CDlgDigOut::OnBnClickedChkDoCmd5(void) { SetDoCmd(5); }
void CDlgDigOut::OnBnClickedChkDoCmd6(void) { SetDoCmd(6); }
void CDlgDigOut::OnBnClickedChkDoCmd7(void) { SetDoCmd(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 自动测试(需要外部连接DI和DO)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define DO_TST_DLY	500	// ms

void CDlgDigOut::OnBnClickedBtnAuoTstDo(void)
{
	SetDoWhole(0xFF);
	XSleep(DO_TST_DLY);

	SetDoWhole(0x00);
	XSleep(DO_TST_DLY);

	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		SetDoWhole(1 << i);
		XSleep(DO_TST_DLY);
	}

	SetDoWhole(0xFF);
	XSleep(DO_TST_DLY);

	SetDoWhole(0x00);
	XSleep(DO_TST_DLY);

	SetDoWhole(0xFF);
	XSleep(DO_TST_DLY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 全部置位/复位
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::SetDoWhole(U8 byte)
{
	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		U8 data = ((byte >> i) & 1);
		ZXUT_SetDoCmd(i, data);
		m_chkDoCmd[i].SetCheck(data);
	}
}

void CDlgDigOut::OnBnClickedBtnAllDoSet(void)
{
	SetDoWhole(0xFF);	// 全部置位
}

void CDlgDigOut::OnBnClickedBtnAllDoClr(void)
{
	SetDoWhole(0x00);	// 全部清零
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 微调DO宽度/延迟
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == SB_ENDSCROLL)
	{
		return; // Reject spurious messages
	}

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_OUT& stDigOut = param.m_stDigOut;

	CString str;
	U8 do_chan;
	BOOL do_width_enb = FALSE;
	BOOL do_dly_enb = FALSE;
	switch (pScrollBar->GetDlgCtrlID())
	{
		case IDC_SPIN_DO_WIDTH0: do_chan = 0; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH1: do_chan = 1; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH2: do_chan = 2; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH3: do_chan = 3; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH4: do_chan = 4; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH5: do_chan = 5; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH6: do_chan = 6; do_width_enb = TRUE; break;
		case IDC_SPIN_DO_WIDTH7: do_chan = 7; do_width_enb = TRUE; break;

		case IDC_SPIN_DO_DLY0: do_chan = 0; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY1: do_chan = 1; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY2: do_chan = 2; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY3: do_chan = 3; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY4: do_chan = 4; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY5: do_chan = 5; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY6: do_chan = 6; do_dly_enb = TRUE; break;
		case IDC_SPIN_DO_DLY7: do_chan = 7; do_dly_enb = TRUE; break;

		default: return;
	}

	if (do_width_enb)
	{
		stDigOut.m_nWidth[do_chan] = nPos - 1;
		F32 do_width = nPos * 10 * (stDigOut.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", do_width);
		m_txtDoWidth[do_chan].SetWindowText(str);
		ZXUT_SetDoWidth(do_chan, nPos * 10);
	}

	if (do_dly_enb)
	{
		stDigOut.m_nDly[do_chan] = nPos;
		F32 do_dly = nPos * 10 * (stDigOut.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", do_dly);
		m_txtDoDly[do_chan].SetWindowText(str);
		ZXUT_SetDoDly(do_chan, nPos * 10);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 使能DO宽度和延迟控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigOut::EnbDoWidthDly(U8 nDoChan, BOOL bEnb)
{
	m_spinDoWidth[nDoChan].EnableWindow(bEnb);
	m_txtDoWidth[nDoChan].EnableWindow(bEnb);

	m_spinDoDly[nDoChan].EnableWindow(bEnb);
	m_txtDoDly[nDoChan].EnableWindow(bEnb);
}
