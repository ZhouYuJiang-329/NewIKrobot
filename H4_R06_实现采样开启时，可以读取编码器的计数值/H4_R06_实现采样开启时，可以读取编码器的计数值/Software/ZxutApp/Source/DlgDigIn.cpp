#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgDigIn.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CDlgDigIn, CDialog)

CDlgDigIn::CDlgDigIn(CWnd* pParent) : CDialog(CDlgDigIn::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgDigIn = this;
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
}

CDlgDigIn::~CDlgDigIn(void)
{
}

void CDlgDigIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LED_DI_RES0, m_ledDiRes[0]);
	DDX_Control(pDX, IDC_LED_DI_RES1, m_ledDiRes[1]);
	DDX_Control(pDX, IDC_LED_DI_RES2, m_ledDiRes[2]);
	DDX_Control(pDX, IDC_LED_DI_RES3, m_ledDiRes[3]);
	DDX_Control(pDX, IDC_LED_DI_RES4, m_ledDiRes[4]);
	DDX_Control(pDX, IDC_LED_DI_RES5, m_ledDiRes[5]);
	DDX_Control(pDX, IDC_LED_DI_RES6, m_ledDiRes[6]);
	DDX_Control(pDX, IDC_LED_DI_RES7, m_ledDiRes[7]);

	DDX_Control(pDX, IDC_CHK_DI_ENB0, m_chkDiEnb[0]);
	DDX_Control(pDX, IDC_CHK_DI_ENB1, m_chkDiEnb[1]);
	DDX_Control(pDX, IDC_CHK_DI_ENB2, m_chkDiEnb[2]);
	DDX_Control(pDX, IDC_CHK_DI_ENB3, m_chkDiEnb[3]);
	DDX_Control(pDX, IDC_CHK_DI_ENB4, m_chkDiEnb[4]);
	DDX_Control(pDX, IDC_CHK_DI_ENB5, m_chkDiEnb[5]);
	DDX_Control(pDX, IDC_CHK_DI_ENB6, m_chkDiEnb[6]);
	DDX_Control(pDX, IDC_CHK_DI_ENB7, m_chkDiEnb[7]);

	DDX_Control(pDX, IDC_COMBO_DI_MODE0, m_combDiMode[0]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE1, m_combDiMode[1]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE2, m_combDiMode[2]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE3, m_combDiMode[3]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE4, m_combDiMode[4]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE5, m_combDiMode[5]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE6, m_combDiMode[6]);
	DDX_Control(pDX, IDC_COMBO_DI_MODE7, m_combDiMode[7]);

	DDX_Control(pDX, IDC_COMBO_DI_POL0, m_combDiPol[0]);
	DDX_Control(pDX, IDC_COMBO_DI_POL1, m_combDiPol[1]);
	DDX_Control(pDX, IDC_COMBO_DI_POL2, m_combDiPol[2]);
	DDX_Control(pDX, IDC_COMBO_DI_POL3, m_combDiPol[3]);
	DDX_Control(pDX, IDC_COMBO_DI_POL4, m_combDiPol[4]);
	DDX_Control(pDX, IDC_COMBO_DI_POL5, m_combDiPol[5]);
	DDX_Control(pDX, IDC_COMBO_DI_POL6, m_combDiPol[6]);
	DDX_Control(pDX, IDC_COMBO_DI_POL7, m_combDiPol[7]);

	DDX_Control(pDX, IDC_SPIN_DI_WIDTH0, m_spinDiWidth[0]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH1, m_spinDiWidth[1]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH2, m_spinDiWidth[2]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH3, m_spinDiWidth[3]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH4, m_spinDiWidth[4]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH5, m_spinDiWidth[5]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH6, m_spinDiWidth[6]);
	DDX_Control(pDX, IDC_SPIN_DI_WIDTH7, m_spinDiWidth[7]);

	DDX_Control(pDX, IDC_TXT_DI_WIDTH0, m_txtDiWidth[0]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH1, m_txtDiWidth[1]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH2, m_txtDiWidth[2]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH3, m_txtDiWidth[3]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH4, m_txtDiWidth[4]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH5, m_txtDiWidth[5]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH6, m_txtDiWidth[6]);
	DDX_Control(pDX, IDC_TXT_DI_WIDTH7, m_txtDiWidth[7]);

	DDX_Control(pDX, IDC_SPIN_DI_DLY0, m_spinDiDly[0]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY1, m_spinDiDly[1]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY2, m_spinDiDly[2]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY3, m_spinDiDly[3]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY4, m_spinDiDly[4]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY5, m_spinDiDly[5]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY6, m_spinDiDly[6]);
	DDX_Control(pDX, IDC_SPIN_DI_DLY7, m_spinDiDly[7]);

	DDX_Control(pDX, IDC_TXT_DI_DLY0, m_txtDiDly[0]);
	DDX_Control(pDX, IDC_TXT_DI_DLY1, m_txtDiDly[1]);
	DDX_Control(pDX, IDC_TXT_DI_DLY2, m_txtDiDly[2]);
	DDX_Control(pDX, IDC_TXT_DI_DLY3, m_txtDiDly[3]);
	DDX_Control(pDX, IDC_TXT_DI_DLY4, m_txtDiDly[4]);
	DDX_Control(pDX, IDC_TXT_DI_DLY5, m_txtDiDly[5]);
	DDX_Control(pDX, IDC_TXT_DI_DLY6, m_txtDiDly[6]);
	DDX_Control(pDX, IDC_TXT_DI_DLY7, m_txtDiDly[7]);

	DDX_Control(pDX, IDC_BTN_DI_CLR0, m_btnDiClr[0]);
	DDX_Control(pDX, IDC_BTN_DI_CLR1, m_btnDiClr[1]);
	DDX_Control(pDX, IDC_BTN_DI_CLR2, m_btnDiClr[2]);
	DDX_Control(pDX, IDC_BTN_DI_CLR3, m_btnDiClr[3]);
	DDX_Control(pDX, IDC_BTN_DI_CLR4, m_btnDiClr[4]);
	DDX_Control(pDX, IDC_BTN_DI_CLR5, m_btnDiClr[5]);
	DDX_Control(pDX, IDC_BTN_DI_CLR6, m_btnDiClr[6]);
	DDX_Control(pDX, IDC_BTN_DI_CLR7, m_btnDiClr[7]);

	DDX_Control(pDX, IDC_COMBO_DI_BASE, m_combDiBase);

	DDX_Control(pDX, IDC_EDT_DI_TST_FREQ, m_edtDiTstFreq);
	DDX_Control(pDX, IDC_EDT_DI_TST_WIDTH, m_edtDiTstWidth);
	DDX_Control(pDX, IDC_CHK_DI_TST_ENB, m_chkDiTstEnb);
	DDX_Control(pDX, IDC_COMBO_DI_TST_CHAN, m_combDiTstIdx);
	DDX_Control(pDX, IDC_TXT_DI_TST_NOTE, m_txtDiTstNote);
}

BEGIN_MESSAGE_MAP(CDlgDigIn, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_BASE, &CDlgDigIn::OnCbnSelchangeComboDiBase)

	ON_BN_CLICKED(IDC_CHK_DI_ENB0, OnBnClickedChkDiEnb0)
	ON_BN_CLICKED(IDC_CHK_DI_ENB1, OnBnClickedChkDiEnb1)
	ON_BN_CLICKED(IDC_CHK_DI_ENB2, OnBnClickedChkDiEnb2)
	ON_BN_CLICKED(IDC_CHK_DI_ENB3, OnBnClickedChkDiEnb3)
	ON_BN_CLICKED(IDC_CHK_DI_ENB4, OnBnClickedChkDiEnb4)
	ON_BN_CLICKED(IDC_CHK_DI_ENB5, OnBnClickedChkDiEnb5)
	ON_BN_CLICKED(IDC_CHK_DI_ENB6, OnBnClickedChkDiEnb6)
	ON_BN_CLICKED(IDC_CHK_DI_ENB7, OnBnClickedChkDiEnb7)

	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE0, &CDlgDigIn::OnCbnSelchangeComboDiMode0)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE1, &CDlgDigIn::OnCbnSelchangeComboDiMode1)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE2, &CDlgDigIn::OnCbnSelchangeComboDiMode2)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE3, &CDlgDigIn::OnCbnSelchangeComboDiMode3)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE4, &CDlgDigIn::OnCbnSelchangeComboDiMode4)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE5, &CDlgDigIn::OnCbnSelchangeComboDiMode5)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE6, &CDlgDigIn::OnCbnSelchangeComboDiMode6)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_MODE7, &CDlgDigIn::OnCbnSelchangeComboDiMode7)

	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL0, OnCbnSelchangeComboDiPol0)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL1, OnCbnSelchangeComboDiPol1)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL2, OnCbnSelchangeComboDiPol2)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL3, OnCbnSelchangeComboDiPol3)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL4, OnCbnSelchangeComboDiPol4)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL5, OnCbnSelchangeComboDiPol5)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL6, OnCbnSelchangeComboDiPol6)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_POL7, OnCbnSelchangeComboDiPol7)

	ON_BN_CLICKED(IDC_BTN_DI_CLR0, &CDlgDigIn::OnBnClickedBtnDiClr0)
	ON_BN_CLICKED(IDC_BTN_DI_CLR1, &CDlgDigIn::OnBnClickedBtnDiClr1)
	ON_BN_CLICKED(IDC_BTN_DI_CLR2, &CDlgDigIn::OnBnClickedBtnDiClr2)
	ON_BN_CLICKED(IDC_BTN_DI_CLR3, &CDlgDigIn::OnBnClickedBtnDiClr3)
	ON_BN_CLICKED(IDC_BTN_DI_CLR4, &CDlgDigIn::OnBnClickedBtnDiClr4)
	ON_BN_CLICKED(IDC_BTN_DI_CLR5, &CDlgDigIn::OnBnClickedBtnDiClr5)
	ON_BN_CLICKED(IDC_BTN_DI_CLR6, &CDlgDigIn::OnBnClickedBtnDiClr6)
	ON_BN_CLICKED(IDC_BTN_DI_CLR7, &CDlgDigIn::OnBnClickedBtnDiClr7)
	ON_BN_CLICKED(IDC_CHK_DI_TST_ENB, &CDlgDigIn::OnBnClickedChkDiTstEnb)
	ON_CBN_SELCHANGE(IDC_COMBO_DI_TST_CHAN, &CDlgDigIn::OnCbnSelchangeComboDiTstChan)
	ON_BN_CLICKED(IDC_BTN_ALL_DI_SET, &CDlgDigIn::OnBnClickedBtnAllDiSet)
	ON_BN_CLICKED(IDC_BTN_ALL_DI_CLR, &CDlgDigIn::OnBnClickedBtnAllDiClr)
	ON_BN_CLICKED(IDC_BTN_AUO_TST_DO, &CDlgDigIn::OnBnClickedBtnAuoTstDo)

	ON_WM_VSCROLL()
END_MESSAGE_MAP()

BOOL CDlgDigIn::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	CString str;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// DI测试

	m_chkDiTstEnb.SetCheck(stDigIn.m_bTstEnb);

	str.Format("%d", stDigIn.m_nTstFreq);
	m_edtDiTstFreq.SetWindowText(str);

	str.Format("%d", stDigIn.m_nTstWidth);
	m_edtDiTstWidth.SetWindowText(str);

	str.Format("Hz, 周期为%dms", 1000 / stDigIn.m_nTstFreq);
	m_txtDiTstNote.SetWindowText(str);

	m_combDiTstIdx.ResetContent();
	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		str.Format("%d\n", i);
		m_combDiTstIdx.AddString(str);
	}
	m_combDiTstIdx.SetCurSel(stDigIn.m_nTstChan);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 时基

	m_combDiBase.ResetContent();
	for (U32 i = 0; i < 10; i++)
	{
		str.Format("%.1fms", (i + 1) * 0.1f);
		m_combDiBase.AddString(str);
	}
	m_combDiBase.SetCurSel(stDigIn.m_nBase);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 使能

	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		m_ledDiRes[i].SetState(LED_DIS);

		m_ledDiRes[i].EnableWindow(stDigIn.m_bEnb[i]);
		m_chkDiEnb[i].SetCheck(stDigIn.m_bEnb[i]);
		m_combDiMode[i].EnableWindow(stDigIn.m_bEnb[i]);
		m_combDiPol[i].EnableWindow(stDigIn.m_bEnb[i]);
		m_btnDiClr[i].EnableWindow(stDigIn.m_bEnb[i]);
		EnbDiWidthDly(i, stDigIn.m_bEnb[i]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 模式

	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		m_combDiMode[i].ResetContent();
		m_combDiMode[i].AddString("脉冲");		// 0
		m_combDiMode[i].AddString("电平");		// 1
		m_combDiMode[i].SetCurSel(stDigIn.m_nMode[i]);

		BOOL enb = (stDigIn.m_nMode[i] == DIO_MODE_PUL) && (stDigIn.m_bEnb[i] == TRUE);
		m_btnDiClr[i].EnableWindow(enb);
		EnbDiWidthDly(i, enb);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 极性

	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		m_combDiPol[i].ResetContent();
		m_combDiPol[i].AddString("负极性");	// 0
		m_combDiPol[i].AddString("正极性");	// 1
		m_combDiPol[i].SetCurSel(stDigIn.m_nPol[i]);
	}

	UpdDiWidth();	// 宽度
	UpdDiDly();		// 延迟

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新数字输入
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::UpdDigIn(U8 dig_in)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;

	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		if (stDigIn.m_bEnb[i] == FALSE) continue;

		if ((dig_in & (0x01 << i)) == (0x01 << i))
		{
			m_ledDiRes[i].SetState(LED_ON);
		}
		else
		{
			m_ledDiRes[i].SetState(LED_OFF);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 时基
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::OnCbnSelchangeComboDiBase(void)
{
	CString str;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;
	stDigIn.m_nBase = m_combDiBase.GetCurSel();

	// 0 -> 0.1ms =  100us
	// 9 -> 1.0ms = 1000us
	U32 di_base = (stDigIn.m_nBase + 1) * 100;	// us
	ZXUT_SetDiBase(0, di_base);

	UpdDiWidth();	// 更新宽度
	UpdDiDly();		// 更新延迟
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置DI使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::SetDiEnb(U8 di_chan)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;
	U8& di_enb = stDigIn.m_bEnb[di_chan];
	di_enb = m_chkDiEnb[di_chan].GetCheck();

	ZXUT_SetDiEnb(0, di_chan, di_enb);

	m_ledDiRes[di_chan].EnableWindow(di_enb);

	m_combDiMode[di_chan].EnableWindow(di_enb);
	m_combDiPol[di_chan].EnableWindow(di_enb);
	m_btnDiClr[di_chan].EnableWindow(di_enb);
	EnbDiWidthDly(di_chan, di_enb);

	if (di_enb == TRUE)
	{
		BOOL enb = (stDigIn.m_nMode[di_chan] == DIO_MODE_PUL);
		m_btnDiClr[di_chan].EnableWindow(enb);
		EnbDiWidthDly(di_chan, enb);
	}
	else
	{
		m_ledDiRes[di_chan].SetState(LED_DIS);
	}
}

void CDlgDigIn::OnBnClickedChkDiEnb0(void) { SetDiEnb(0); }
void CDlgDigIn::OnBnClickedChkDiEnb1(void) { SetDiEnb(1); }
void CDlgDigIn::OnBnClickedChkDiEnb2(void) { SetDiEnb(2); }
void CDlgDigIn::OnBnClickedChkDiEnb3(void) { SetDiEnb(3); }
void CDlgDigIn::OnBnClickedChkDiEnb4(void) { SetDiEnb(4); }
void CDlgDigIn::OnBnClickedChkDiEnb5(void) { SetDiEnb(5); }
void CDlgDigIn::OnBnClickedChkDiEnb6(void) { SetDiEnb(6); }
void CDlgDigIn::OnBnClickedChkDiEnb7(void) { SetDiEnb(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 模式
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::SetDiMode(U8 di_chan)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;
	U8& di_mode = stDigIn.m_nMode[di_chan];
	di_mode = m_combDiMode[di_chan].GetCurSel();

	ZXUT_SetDiMode(0, di_chan, di_mode);

	BOOL enb = (di_mode == DIO_MODE_PUL);
	m_btnDiClr[di_chan].EnableWindow(enb);
	EnbDiWidthDly(di_chan, enb);
}

void CDlgDigIn::OnCbnSelchangeComboDiMode0(void) { SetDiMode(0); }
void CDlgDigIn::OnCbnSelchangeComboDiMode1(void) { SetDiMode(1); }
void CDlgDigIn::OnCbnSelchangeComboDiMode2(void) { SetDiMode(2); }
void CDlgDigIn::OnCbnSelchangeComboDiMode3(void) { SetDiMode(3); }
void CDlgDigIn::OnCbnSelchangeComboDiMode4(void) { SetDiMode(4); }
void CDlgDigIn::OnCbnSelchangeComboDiMode5(void) { SetDiMode(5); }
void CDlgDigIn::OnCbnSelchangeComboDiMode6(void) { SetDiMode(6); }
void CDlgDigIn::OnCbnSelchangeComboDiMode7(void) { SetDiMode(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置DI极性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::SetDiPol(U8 di_chan)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;
	stDigIn.m_nPol[di_chan] = m_combDiPol[di_chan].GetCurSel();
	ZXUT_SetDiPol(0, di_chan, stDigIn.m_nPol[di_chan]);
}

void CDlgDigIn::OnCbnSelchangeComboDiPol0(void) { SetDiPol(0); }
void CDlgDigIn::OnCbnSelchangeComboDiPol1(void) { SetDiPol(1); }
void CDlgDigIn::OnCbnSelchangeComboDiPol2(void) { SetDiPol(2); }
void CDlgDigIn::OnCbnSelchangeComboDiPol3(void) { SetDiPol(3); }
void CDlgDigIn::OnCbnSelchangeComboDiPol4(void) { SetDiPol(4); }
void CDlgDigIn::OnCbnSelchangeComboDiPol5(void) { SetDiPol(5); }
void CDlgDigIn::OnCbnSelchangeComboDiPol6(void) { SetDiPol(6); }
void CDlgDigIn::OnCbnSelchangeComboDiPol7(void) { SetDiPol(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 宽度
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::UpdDiWidth(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;

	CString str;
	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		U16 pos = stDigIn.m_nWidth[i] + 1;
		m_spinDiWidth[i].SetRange(1, 10);	// 0 - 9
		m_spinDiWidth[i].SetPos(pos);

		F32 di_width = pos * 10 * (stDigIn.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", di_width);
		m_txtDiWidth[i].SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 延迟
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::UpdDiDly(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;

	CString str;
	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		U16 pos = stDigIn.m_nDly[i];
		m_spinDiDly[i].SetRange(0, 10);	// 0 - 10
		m_spinDiDly[i].SetPos(pos);

		F32 di_dly = pos * 10 * (stDigIn.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", di_dly);
		m_txtDiDly[i].SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 清除DI结果，写即清零
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::SetDiClr(U8 di_chan)
{
	ZXUT_SetDiClr(0, di_chan);
}

void CDlgDigIn::OnBnClickedBtnDiClr0(void) { SetDiClr(0); }
void CDlgDigIn::OnBnClickedBtnDiClr1(void) { SetDiClr(1); }
void CDlgDigIn::OnBnClickedBtnDiClr2(void) { SetDiClr(2); }
void CDlgDigIn::OnBnClickedBtnDiClr3(void) { SetDiClr(3); }
void CDlgDigIn::OnBnClickedBtnDiClr4(void) { SetDiClr(4); }
void CDlgDigIn::OnBnClickedBtnDiClr5(void) { SetDiClr(5); }
void CDlgDigIn::OnBnClickedBtnDiClr6(void) { SetDiClr(6); }
void CDlgDigIn::OnBnClickedBtnDiClr7(void) { SetDiClr(7); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DI测试
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::OnBnClickedChkDiTstEnb(void)
{
	U8& tst_enb = m_pApp->m_stFlawParam.m_stDigIn.m_bTstEnb;
	tst_enb = m_chkDiTstEnb.GetCheck();
	ZXUT_SetDiTstEnb(0, tst_enb);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 预翻译信息，处理回车键
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgDigIn::PreTranslateMessage(MSG* pMsg)
{
	CString str;

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			case VK_RETURN:	// 屏蔽回车键
				{
					CWnd* pwnd = GetFocus();

					////////////////////////////////////////////////////////////////////////////////
					// DI测试频率(Hz)

					if (pwnd == &m_edtDiTstFreq)
					{
						m_edtDiTstFreq.GetWindowText(str);
						U32 di_tst_freq = atoi(str);
						if ((di_tst_freq < DI_TST_FREQ_MIN) || (di_tst_freq > DI_TST_FREQ_MAX))
						{
							m_pApp->DispMsg(ZXUT_MSG_WARNING, "DI测试频率%dHz超出范围[%dHz, %dHz]",
								di_tst_freq, DI_TST_FREQ_MIN, DI_TST_FREQ_MAX);
							str.Format("%d", m_pApp->m_stFlawParam.m_stDigIn.m_nTstFreq);
							m_edtDiTstFreq.SetWindowText(str);	// 恢复原来的合法值
							return TRUE;
						}

						// 设置新值
						m_pApp->m_stFlawParam.m_stDigIn.m_nTstFreq = di_tst_freq;
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetDiTstFreq(i, di_tst_freq);
						}

						// 设置注释
						U32 di_tst_period = 1000 / di_tst_freq;	// ms
						str.Format("Hz, 周期为%dms", di_tst_period);
						m_txtDiTstNote.SetWindowText(str);

						// 设置测试宽度
						U16& di_tst_width = m_pApp->m_stFlawParam.m_stDigIn.m_nTstWidth;
						di_tst_width = di_tst_period / 2;
						str.Format("%d", di_tst_width);
						m_edtDiTstWidth.SetWindowText(str);
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetDiTstWidth(i, di_tst_width);
						}
					}

					////////////////////////////////////////////////////////////////////////////////
					// DI测试脉宽(ms)

					else if (pwnd == &m_edtDiTstWidth)
					{
						U16 di_tst_freq = m_pApp->m_stFlawParam.m_stDigIn.m_nTstFreq;
						U32 di_tst_period = 1000 / di_tst_freq;	// ms

						m_edtDiTstWidth.GetWindowText(str);
						U32 di_tst_width = atoi(str);
						if ((di_tst_width < 1) || (di_tst_width > di_tst_period / 2))
						{
							m_pApp->DispMsg(ZXUT_MSG_WARNING, "DI测试宽度%dms超过范围[1ms, %dms]",
								di_tst_width, di_tst_period / 2);
							str.Format("%d", m_pApp->m_stFlawParam.m_stDigIn.m_nTstWidth);
							m_edtDiTstWidth.SetWindowText(str);	// 恢复原来的合法值
							return TRUE;
						}

						m_pApp->m_stFlawParam.m_stDigIn.m_nTstWidth = di_tst_width;
						for (U8 i = 0; i < x_nTotBrd; i++)
						{
							ZXUT_SetDiTstWidth(i, di_tst_width);
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
// DI测试通道
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::OnCbnSelchangeComboDiTstChan(void)
{
	U8& di_tst_chan = m_pApp->m_stFlawParam.m_stDigIn.m_nTstChan;
	di_tst_chan = m_combDiTstIdx.GetCurSel();
	ZXUT_SetDiTstChan(0, di_tst_chan);
}

void CDlgDigIn::OnBnClickedBtnAuoTstDo(void)
{
	m_pApp->m_pDlgDigOut->OnBnClickedBtnAuoTstDo();
}

void CDlgDigIn::OnBnClickedBtnAllDiSet(void)
{
	m_pApp->m_pDlgDigOut->OnBnClickedBtnAllDoSet();
}

void CDlgDigIn::OnBnClickedBtnAllDiClr(void)
{
	m_pApp->m_pDlgDigOut->OnBnClickedBtnAllDoClr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 微调DI宽度/延迟
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == SB_ENDSCROLL)
	{
		return; // Reject spurious messages
	}

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_DIG_IN& stDigIn = param.m_stDigIn;

	CString str;
	U8 di_chan;
	BOOL di_width_enb = FALSE;
	BOOL di_dly_enb = FALSE;
	switch (pScrollBar->GetDlgCtrlID())
	{
		case IDC_SPIN_DI_WIDTH0: di_chan = 0; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH1: di_chan = 1; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH2: di_chan = 2; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH3: di_chan = 3; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH4: di_chan = 4; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH5: di_chan = 5; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH6: di_chan = 6; di_width_enb = TRUE; break;
		case IDC_SPIN_DI_WIDTH7: di_chan = 7; di_width_enb = TRUE; break;

		case IDC_SPIN_DI_DLY0: di_chan = 0; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY1: di_chan = 1; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY2: di_chan = 2; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY3: di_chan = 3; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY4: di_chan = 4; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY5: di_chan = 5; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY6: di_chan = 6; di_dly_enb = TRUE; break;
		case IDC_SPIN_DI_DLY7: di_chan = 7; di_dly_enb = TRUE; break;

		default: return;
	}

	if (di_width_enb)
	{
		stDigIn.m_nWidth[di_chan] = nPos - 1;
		F32 di_width = nPos * 10 * (stDigIn.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", di_width);
		m_txtDiWidth[di_chan].SetWindowText(str);
		ZXUT_SetDiWidth(0, di_chan, nPos * 10);
	}

	if (di_dly_enb)
	{
		stDigIn.m_nDly[di_chan] = nPos;
		F32 di_dly = nPos * 10 * (stDigIn.m_nBase + 1) * 0.1f;
		str.Format("%.1fms", di_dly);
		m_txtDiDly[di_chan].SetWindowText(str);
		ZXUT_SetDiDly(0, di_chan, nPos * 10);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 使能DI宽度和延迟控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDigIn::EnbDiWidthDly(U8 nDiChan, BOOL bEnb)
{
	m_spinDiWidth[nDiChan].EnableWindow(bEnb);
	m_txtDiWidth[nDiChan].EnableWindow(bEnb);

	m_spinDiDly[nDiChan].EnableWindow(bEnb);
	m_txtDiDly[nDiChan].EnableWindow(bEnb);
}
