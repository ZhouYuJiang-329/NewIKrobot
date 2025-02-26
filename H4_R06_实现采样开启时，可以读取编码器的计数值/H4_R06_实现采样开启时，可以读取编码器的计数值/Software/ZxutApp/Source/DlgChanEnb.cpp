#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgChanEnb.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CDlgChanEnb, CDialog)
CDlgChanEnb::CDlgChanEnb(CWnd* pParent) : CDialog(CDlgChanEnb::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
	x_nTotHard = m_pApp->m_pstExpInfo->m_nTotHard;
	x_nTotSoft = m_pApp->m_pstExpInfo->m_nTotSoft;
}

CDlgChanEnb::~CDlgChanEnb(void)
{
}

void CDlgChanEnb::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GRP_BRD0, m_grpBrd[0]);
	DDX_Control(pDX, IDC_GRP_BRD1, m_grpBrd[1]);
	DDX_Control(pDX, IDC_GRP_BRD2, m_grpBrd[2]);
	DDX_Control(pDX, IDC_GRP_BRD3, m_grpBrd[3]);
	DDX_Control(pDX, IDC_GRP_BRD4, m_grpBrd[4]);
	DDX_Control(pDX, IDC_GRP_BRD5, m_grpBrd[5]);
	DDX_Control(pDX, IDC_GRP_BRD6, m_grpBrd[6]);
	DDX_Control(pDX, IDC_GRP_BRD7, m_grpBrd[7]);
	DDX_Control(pDX, IDC_GRP_BRD8, m_grpBrd[8]);
	DDX_Control(pDX, IDC_GRP_BRD9, m_grpBrd[9]);

	DDX_Control(pDX, IDC_TXT_HARD0, m_txtHard[0]);
	DDX_Control(pDX, IDC_TXT_HARD1, m_txtHard[1]);
	DDX_Control(pDX, IDC_TXT_HARD2, m_txtHard[2]);
	DDX_Control(pDX, IDC_TXT_HARD3, m_txtHard[3]);
	DDX_Control(pDX, IDC_TXT_HARD4, m_txtHard[4]);
	DDX_Control(pDX, IDC_TXT_HARD5, m_txtHard[5]);
	DDX_Control(pDX, IDC_TXT_HARD6, m_txtHard[6]);
	DDX_Control(pDX, IDC_TXT_HARD7, m_txtHard[7]);
	DDX_Control(pDX, IDC_TXT_HARD8, m_txtHard[8]);
	DDX_Control(pDX, IDC_TXT_HARD9, m_txtHard[9]);
	DDX_Control(pDX, IDC_TXT_HARD10, m_txtHard[10]);
	DDX_Control(pDX, IDC_TXT_HARD11, m_txtHard[11]);
	DDX_Control(pDX, IDC_TXT_HARD12, m_txtHard[12]);
	DDX_Control(pDX, IDC_TXT_HARD13, m_txtHard[13]);
	DDX_Control(pDX, IDC_TXT_HARD14, m_txtHard[14]);
	DDX_Control(pDX, IDC_TXT_HARD15, m_txtHard[15]);
	DDX_Control(pDX, IDC_TXT_HARD16, m_txtHard[16]);
	DDX_Control(pDX, IDC_TXT_HARD17, m_txtHard[17]);
	DDX_Control(pDX, IDC_TXT_HARD18, m_txtHard[18]);
	DDX_Control(pDX, IDC_TXT_HARD19, m_txtHard[19]);
	DDX_Control(pDX, IDC_TXT_HARD20, m_txtHard[20]);
	DDX_Control(pDX, IDC_TXT_HARD21, m_txtHard[21]);
	DDX_Control(pDX, IDC_TXT_HARD22, m_txtHard[22]);
	DDX_Control(pDX, IDC_TXT_HARD23, m_txtHard[23]);
	DDX_Control(pDX, IDC_TXT_HARD24, m_txtHard[24]);
	DDX_Control(pDX, IDC_TXT_HARD25, m_txtHard[25]);
	DDX_Control(pDX, IDC_TXT_HARD26, m_txtHard[26]);
	DDX_Control(pDX, IDC_TXT_HARD27, m_txtHard[27]);
	DDX_Control(pDX, IDC_TXT_HARD28, m_txtHard[28]);
	DDX_Control(pDX, IDC_TXT_HARD29, m_txtHard[29]);
	DDX_Control(pDX, IDC_TXT_HARD30, m_txtHard[30]);
	DDX_Control(pDX, IDC_TXT_HARD31, m_txtHard[31]);
	DDX_Control(pDX, IDC_TXT_HARD32, m_txtHard[32]);
	DDX_Control(pDX, IDC_TXT_HARD33, m_txtHard[33]);
	DDX_Control(pDX, IDC_TXT_HARD34, m_txtHard[34]);
	DDX_Control(pDX, IDC_TXT_HARD35, m_txtHard[35]);
	DDX_Control(pDX, IDC_TXT_HARD36, m_txtHard[36]);
	DDX_Control(pDX, IDC_TXT_HARD37, m_txtHard[37]);
	DDX_Control(pDX, IDC_TXT_HARD38, m_txtHard[38]);
	DDX_Control(pDX, IDC_TXT_HARD39, m_txtHard[39]);

	DDX_Control(pDX, IDC_BTN_SET_BRD0, m_btnSet[0]);
	DDX_Control(pDX, IDC_BTN_SET_BRD1, m_btnSet[1]);
	DDX_Control(pDX, IDC_BTN_SET_BRD2, m_btnSet[2]);
	DDX_Control(pDX, IDC_BTN_SET_BRD3, m_btnSet[3]);
	DDX_Control(pDX, IDC_BTN_SET_BRD4, m_btnSet[4]);
	DDX_Control(pDX, IDC_BTN_SET_BRD5, m_btnSet[5]);
	DDX_Control(pDX, IDC_BTN_SET_BRD6, m_btnSet[6]);
	DDX_Control(pDX, IDC_BTN_SET_BRD7, m_btnSet[7]);
	DDX_Control(pDX, IDC_BTN_SET_BRD8, m_btnSet[8]);
	DDX_Control(pDX, IDC_BTN_SET_BRD9, m_btnSet[9]);

	DDX_Control(pDX, IDC_BTN_CLR_BRD0, m_btnClr[0]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD1, m_btnClr[1]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD2, m_btnClr[2]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD3, m_btnClr[3]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD4, m_btnClr[4]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD5, m_btnClr[5]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD6, m_btnClr[6]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD7, m_btnClr[7]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD8, m_btnClr[8]);
	DDX_Control(pDX, IDC_BTN_CLR_BRD9, m_btnClr[9]);

	DDX_Control(pDX, IDC_EDT_SYN_DLY0, m_edtSynDly[0]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY1, m_edtSynDly[1]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY2, m_edtSynDly[2]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY3, m_edtSynDly[3]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY4, m_edtSynDly[4]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY5, m_edtSynDly[5]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY6, m_edtSynDly[6]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY7, m_edtSynDly[7]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY8, m_edtSynDly[8]);
	DDX_Control(pDX, IDC_EDT_SYN_DLY9, m_edtSynDly[9]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE0, m_edtChanShare[0]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE1, m_edtChanShare[1]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE2, m_edtChanShare[2]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE3, m_edtChanShare[3]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE4, m_edtChanShare[4]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE5, m_edtChanShare[5]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE6, m_edtChanShare[6]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE7, m_edtChanShare[7]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE8, m_edtChanShare[8]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE9, m_edtChanShare[9]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE10, m_edtChanShare[10]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE11, m_edtChanShare[11]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE12, m_edtChanShare[12]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE13, m_edtChanShare[13]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE14, m_edtChanShare[14]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE15, m_edtChanShare[15]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE16, m_edtChanShare[16]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE17, m_edtChanShare[17]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE18, m_edtChanShare[18]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE19, m_edtChanShare[19]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE20, m_edtChanShare[20]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE21, m_edtChanShare[21]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE22, m_edtChanShare[22]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE23, m_edtChanShare[23]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE24, m_edtChanShare[24]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE25, m_edtChanShare[25]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE26, m_edtChanShare[26]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE27, m_edtChanShare[27]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE28, m_edtChanShare[28]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE29, m_edtChanShare[29]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE30, m_edtChanShare[30]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE31, m_edtChanShare[31]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE32, m_edtChanShare[32]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE33, m_edtChanShare[33]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE34, m_edtChanShare[34]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE35, m_edtChanShare[35]);

	DDX_Control(pDX, IDC_EDT_CHAN_SHARE36, m_edtChanShare[36]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE37, m_edtChanShare[37]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE38, m_edtChanShare[38]);
	DDX_Control(pDX, IDC_EDT_CHAN_SHARE39, m_edtChanShare[39]);

	DDX_Control(pDX, IDC_BTN_SET_ALL, m_btnAllSet);
	DDX_Control(pDX, IDC_BTN_CLR_ALL, m_btnAllClr);
	DDX_Control(pDX, IDC_BTN_UPD_CHAN_ENB, m_btnUpdChanEnb);

	// 0#
	DDX_Control(pDX, IDC_CHK_H0_S0, m_chkChanEnb[0][0]);
	DDX_Control(pDX, IDC_CHK_H0_S1, m_chkChanEnb[0][1]);
	DDX_Control(pDX, IDC_CHK_H0_S2, m_chkChanEnb[0][2]);
	DDX_Control(pDX, IDC_CHK_H0_S3, m_chkChanEnb[0][3]);

	// 1#
	DDX_Control(pDX, IDC_CHK_H1_S0, m_chkChanEnb[1][0]);
	DDX_Control(pDX, IDC_CHK_H1_S1, m_chkChanEnb[1][1]);
	DDX_Control(pDX, IDC_CHK_H1_S2, m_chkChanEnb[1][2]);
	DDX_Control(pDX, IDC_CHK_H1_S3, m_chkChanEnb[1][3]);

	// 2#
	DDX_Control(pDX, IDC_CHK_H2_S0, m_chkChanEnb[2][0]);
	DDX_Control(pDX, IDC_CHK_H2_S1, m_chkChanEnb[2][1]);
	DDX_Control(pDX, IDC_CHK_H2_S2, m_chkChanEnb[2][2]);
	DDX_Control(pDX, IDC_CHK_H2_S3, m_chkChanEnb[2][3]);

	// 3#
	DDX_Control(pDX, IDC_CHK_H3_S0, m_chkChanEnb[3][0]);
	DDX_Control(pDX, IDC_CHK_H3_S1, m_chkChanEnb[3][1]);
	DDX_Control(pDX, IDC_CHK_H3_S2, m_chkChanEnb[3][2]);
	DDX_Control(pDX, IDC_CHK_H3_S3, m_chkChanEnb[3][3]);

	// 4#
	DDX_Control(pDX, IDC_CHK_H4_S0, m_chkChanEnb[4][0]);
	DDX_Control(pDX, IDC_CHK_H4_S1, m_chkChanEnb[4][1]);
	DDX_Control(pDX, IDC_CHK_H4_S2, m_chkChanEnb[4][2]);
	DDX_Control(pDX, IDC_CHK_H4_S3, m_chkChanEnb[4][3]);

	// 5#
	DDX_Control(pDX, IDC_CHK_H5_S0, m_chkChanEnb[5][0]);
	DDX_Control(pDX, IDC_CHK_H5_S1, m_chkChanEnb[5][1]);
	DDX_Control(pDX, IDC_CHK_H5_S2, m_chkChanEnb[5][2]);
	DDX_Control(pDX, IDC_CHK_H5_S3, m_chkChanEnb[5][3]);

	// 6#
	DDX_Control(pDX, IDC_CHK_H6_S0, m_chkChanEnb[6][0]);
	DDX_Control(pDX, IDC_CHK_H6_S1, m_chkChanEnb[6][1]);
	DDX_Control(pDX, IDC_CHK_H6_S2, m_chkChanEnb[6][2]);
	DDX_Control(pDX, IDC_CHK_H6_S3, m_chkChanEnb[6][3]);

	// 7#
	DDX_Control(pDX, IDC_CHK_H7_S0, m_chkChanEnb[7][0]);
	DDX_Control(pDX, IDC_CHK_H7_S1, m_chkChanEnb[7][1]);
	DDX_Control(pDX, IDC_CHK_H7_S2, m_chkChanEnb[7][2]);
	DDX_Control(pDX, IDC_CHK_H7_S3, m_chkChanEnb[7][3]);

	// 8#
	DDX_Control(pDX, IDC_CHK_H8_S0, m_chkChanEnb[8][0]);
	DDX_Control(pDX, IDC_CHK_H8_S1, m_chkChanEnb[8][1]);
	DDX_Control(pDX, IDC_CHK_H8_S2, m_chkChanEnb[8][2]);
	DDX_Control(pDX, IDC_CHK_H8_S3, m_chkChanEnb[8][3]);

	// 9#
	DDX_Control(pDX, IDC_CHK_H9_S0, m_chkChanEnb[9][0]);
	DDX_Control(pDX, IDC_CHK_H9_S1, m_chkChanEnb[9][1]);
	DDX_Control(pDX, IDC_CHK_H9_S2, m_chkChanEnb[9][2]);
	DDX_Control(pDX, IDC_CHK_H9_S3, m_chkChanEnb[9][3]);

	// 10#
	DDX_Control(pDX, IDC_CHK_H10_S0, m_chkChanEnb[10][0]);
	DDX_Control(pDX, IDC_CHK_H10_S1, m_chkChanEnb[10][1]);
	DDX_Control(pDX, IDC_CHK_H10_S2, m_chkChanEnb[10][2]);
	DDX_Control(pDX, IDC_CHK_H10_S3, m_chkChanEnb[10][3]);

	// 11#
	DDX_Control(pDX, IDC_CHK_H11_S0, m_chkChanEnb[11][0]);
	DDX_Control(pDX, IDC_CHK_H11_S1, m_chkChanEnb[11][1]);
	DDX_Control(pDX, IDC_CHK_H11_S2, m_chkChanEnb[11][2]);
	DDX_Control(pDX, IDC_CHK_H11_S3, m_chkChanEnb[11][3]);

	// 12#
	DDX_Control(pDX, IDC_CHK_H12_S0, m_chkChanEnb[12][0]);
	DDX_Control(pDX, IDC_CHK_H12_S1, m_chkChanEnb[12][1]);
	DDX_Control(pDX, IDC_CHK_H12_S2, m_chkChanEnb[12][2]);
	DDX_Control(pDX, IDC_CHK_H12_S3, m_chkChanEnb[12][3]);

	// 13#
	DDX_Control(pDX, IDC_CHK_H13_S0, m_chkChanEnb[13][0]);
	DDX_Control(pDX, IDC_CHK_H13_S1, m_chkChanEnb[13][1]);
	DDX_Control(pDX, IDC_CHK_H13_S2, m_chkChanEnb[13][2]);
	DDX_Control(pDX, IDC_CHK_H13_S3, m_chkChanEnb[13][3]);

	// 14#
	DDX_Control(pDX, IDC_CHK_H14_S0, m_chkChanEnb[14][0]);
	DDX_Control(pDX, IDC_CHK_H14_S1, m_chkChanEnb[14][1]);
	DDX_Control(pDX, IDC_CHK_H14_S2, m_chkChanEnb[14][2]);
	DDX_Control(pDX, IDC_CHK_H14_S3, m_chkChanEnb[14][3]);

	// 15#
	DDX_Control(pDX, IDC_CHK_H15_S0, m_chkChanEnb[15][0]);
	DDX_Control(pDX, IDC_CHK_H15_S1, m_chkChanEnb[15][1]);
	DDX_Control(pDX, IDC_CHK_H15_S2, m_chkChanEnb[15][2]);
	DDX_Control(pDX, IDC_CHK_H15_S3, m_chkChanEnb[15][3]);

	// 16#
	DDX_Control(pDX, IDC_CHK_H16_S0, m_chkChanEnb[16][0]);
	DDX_Control(pDX, IDC_CHK_H16_S1, m_chkChanEnb[16][1]);
	DDX_Control(pDX, IDC_CHK_H16_S2, m_chkChanEnb[16][2]);
	DDX_Control(pDX, IDC_CHK_H16_S3, m_chkChanEnb[16][3]);

	// 17#
	DDX_Control(pDX, IDC_CHK_H17_S0, m_chkChanEnb[17][0]);
	DDX_Control(pDX, IDC_CHK_H17_S1, m_chkChanEnb[17][1]);
	DDX_Control(pDX, IDC_CHK_H17_S2, m_chkChanEnb[17][2]);
	DDX_Control(pDX, IDC_CHK_H17_S3, m_chkChanEnb[17][3]);

	// 18#
	DDX_Control(pDX, IDC_CHK_H18_S0, m_chkChanEnb[18][0]);
	DDX_Control(pDX, IDC_CHK_H18_S1, m_chkChanEnb[18][1]);
	DDX_Control(pDX, IDC_CHK_H18_S2, m_chkChanEnb[18][2]);
	DDX_Control(pDX, IDC_CHK_H18_S3, m_chkChanEnb[18][3]);

	// 19#
	DDX_Control(pDX, IDC_CHK_H19_S0, m_chkChanEnb[19][0]);
	DDX_Control(pDX, IDC_CHK_H19_S1, m_chkChanEnb[19][1]);
	DDX_Control(pDX, IDC_CHK_H19_S2, m_chkChanEnb[19][2]);
	DDX_Control(pDX, IDC_CHK_H19_S3, m_chkChanEnb[19][3]);

	// 20#
	DDX_Control(pDX, IDC_CHK_H20_S0, m_chkChanEnb[20][0]);
	DDX_Control(pDX, IDC_CHK_H20_S1, m_chkChanEnb[20][1]);
	DDX_Control(pDX, IDC_CHK_H20_S2, m_chkChanEnb[20][2]);
	DDX_Control(pDX, IDC_CHK_H20_S3, m_chkChanEnb[20][3]);

	// 21#
	DDX_Control(pDX, IDC_CHK_H21_S0, m_chkChanEnb[21][0]);
	DDX_Control(pDX, IDC_CHK_H21_S1, m_chkChanEnb[21][1]);
	DDX_Control(pDX, IDC_CHK_H21_S2, m_chkChanEnb[21][2]);
	DDX_Control(pDX, IDC_CHK_H21_S3, m_chkChanEnb[21][3]);

	// 22#
	DDX_Control(pDX, IDC_CHK_H22_S0, m_chkChanEnb[22][0]);
	DDX_Control(pDX, IDC_CHK_H22_S1, m_chkChanEnb[22][1]);
	DDX_Control(pDX, IDC_CHK_H22_S2, m_chkChanEnb[22][2]);
	DDX_Control(pDX, IDC_CHK_H22_S3, m_chkChanEnb[22][3]);

	// 23#
	DDX_Control(pDX, IDC_CHK_H23_S0, m_chkChanEnb[23][0]);
	DDX_Control(pDX, IDC_CHK_H23_S1, m_chkChanEnb[23][1]);
	DDX_Control(pDX, IDC_CHK_H23_S2, m_chkChanEnb[23][2]);
	DDX_Control(pDX, IDC_CHK_H23_S3, m_chkChanEnb[23][3]);

	// 24#
	DDX_Control(pDX, IDC_CHK_H24_S0, m_chkChanEnb[24][0]);
	DDX_Control(pDX, IDC_CHK_H24_S1, m_chkChanEnb[24][1]);
	DDX_Control(pDX, IDC_CHK_H24_S2, m_chkChanEnb[24][2]);
	DDX_Control(pDX, IDC_CHK_H24_S3, m_chkChanEnb[24][3]);

	// 25#
	DDX_Control(pDX, IDC_CHK_H25_S0, m_chkChanEnb[25][0]);
	DDX_Control(pDX, IDC_CHK_H25_S1, m_chkChanEnb[25][1]);
	DDX_Control(pDX, IDC_CHK_H25_S2, m_chkChanEnb[25][2]);
	DDX_Control(pDX, IDC_CHK_H25_S3, m_chkChanEnb[25][3]);

	// 26#
	DDX_Control(pDX, IDC_CHK_H26_S0, m_chkChanEnb[26][0]);
	DDX_Control(pDX, IDC_CHK_H26_S1, m_chkChanEnb[26][1]);
	DDX_Control(pDX, IDC_CHK_H26_S2, m_chkChanEnb[26][2]);
	DDX_Control(pDX, IDC_CHK_H26_S3, m_chkChanEnb[26][3]);

	// 27#
	DDX_Control(pDX, IDC_CHK_H27_S0, m_chkChanEnb[27][0]);
	DDX_Control(pDX, IDC_CHK_H27_S1, m_chkChanEnb[27][1]);
	DDX_Control(pDX, IDC_CHK_H27_S2, m_chkChanEnb[27][2]);
	DDX_Control(pDX, IDC_CHK_H27_S3, m_chkChanEnb[27][3]);

	// 28#
	DDX_Control(pDX, IDC_CHK_H28_S0, m_chkChanEnb[28][0]);
	DDX_Control(pDX, IDC_CHK_H28_S1, m_chkChanEnb[28][1]);
	DDX_Control(pDX, IDC_CHK_H28_S2, m_chkChanEnb[28][2]);
	DDX_Control(pDX, IDC_CHK_H28_S3, m_chkChanEnb[28][3]);

	// 29#
	DDX_Control(pDX, IDC_CHK_H29_S0, m_chkChanEnb[29][0]);
	DDX_Control(pDX, IDC_CHK_H29_S1, m_chkChanEnb[29][1]);
	DDX_Control(pDX, IDC_CHK_H29_S2, m_chkChanEnb[29][2]);
	DDX_Control(pDX, IDC_CHK_H29_S3, m_chkChanEnb[29][3]);

	// 30#
	DDX_Control(pDX, IDC_CHK_H30_S0, m_chkChanEnb[30][0]);
	DDX_Control(pDX, IDC_CHK_H30_S1, m_chkChanEnb[30][1]);
	DDX_Control(pDX, IDC_CHK_H30_S2, m_chkChanEnb[30][2]);
	DDX_Control(pDX, IDC_CHK_H30_S3, m_chkChanEnb[30][3]);

	// 31#
	DDX_Control(pDX, IDC_CHK_H31_S0, m_chkChanEnb[31][0]);
	DDX_Control(pDX, IDC_CHK_H31_S1, m_chkChanEnb[31][1]);
	DDX_Control(pDX, IDC_CHK_H31_S2, m_chkChanEnb[31][2]);
	DDX_Control(pDX, IDC_CHK_H31_S3, m_chkChanEnb[31][3]);

	// 32#
	DDX_Control(pDX, IDC_CHK_H32_S0, m_chkChanEnb[32][0]);
	DDX_Control(pDX, IDC_CHK_H32_S1, m_chkChanEnb[32][1]);
	DDX_Control(pDX, IDC_CHK_H32_S2, m_chkChanEnb[32][2]);
	DDX_Control(pDX, IDC_CHK_H32_S3, m_chkChanEnb[32][3]);

	// 33#
	DDX_Control(pDX, IDC_CHK_H33_S0, m_chkChanEnb[33][0]);
	DDX_Control(pDX, IDC_CHK_H33_S1, m_chkChanEnb[33][1]);
	DDX_Control(pDX, IDC_CHK_H33_S2, m_chkChanEnb[33][2]);
	DDX_Control(pDX, IDC_CHK_H33_S3, m_chkChanEnb[33][3]);

	// 34#
	DDX_Control(pDX, IDC_CHK_H34_S0, m_chkChanEnb[34][0]);
	DDX_Control(pDX, IDC_CHK_H34_S1, m_chkChanEnb[34][1]);
	DDX_Control(pDX, IDC_CHK_H34_S2, m_chkChanEnb[34][2]);
	DDX_Control(pDX, IDC_CHK_H34_S3, m_chkChanEnb[34][3]);

	// 35#
	DDX_Control(pDX, IDC_CHK_H35_S0, m_chkChanEnb[35][0]);
	DDX_Control(pDX, IDC_CHK_H35_S1, m_chkChanEnb[35][1]);
	DDX_Control(pDX, IDC_CHK_H35_S2, m_chkChanEnb[35][2]);
	DDX_Control(pDX, IDC_CHK_H35_S3, m_chkChanEnb[35][3]);

	// 36#
	DDX_Control(pDX, IDC_CHK_H36_S0, m_chkChanEnb[36][0]);
	DDX_Control(pDX, IDC_CHK_H36_S1, m_chkChanEnb[36][1]);
	DDX_Control(pDX, IDC_CHK_H36_S2, m_chkChanEnb[36][2]);
	DDX_Control(pDX, IDC_CHK_H36_S3, m_chkChanEnb[36][3]);

	// 37#
	DDX_Control(pDX, IDC_CHK_H37_S0, m_chkChanEnb[37][0]);
	DDX_Control(pDX, IDC_CHK_H37_S1, m_chkChanEnb[37][1]);
	DDX_Control(pDX, IDC_CHK_H37_S2, m_chkChanEnb[37][2]);
	DDX_Control(pDX, IDC_CHK_H37_S3, m_chkChanEnb[37][3]);

	// 38#
	DDX_Control(pDX, IDC_CHK_H38_S0, m_chkChanEnb[38][0]);
	DDX_Control(pDX, IDC_CHK_H38_S1, m_chkChanEnb[38][1]);
	DDX_Control(pDX, IDC_CHK_H38_S2, m_chkChanEnb[38][2]);
	DDX_Control(pDX, IDC_CHK_H38_S3, m_chkChanEnb[38][3]);

	// 39#
	DDX_Control(pDX, IDC_CHK_H39_S0, m_chkChanEnb[39][0]);
	DDX_Control(pDX, IDC_CHK_H39_S1, m_chkChanEnb[39][1]);
	DDX_Control(pDX, IDC_CHK_H39_S2, m_chkChanEnb[39][2]);
	DDX_Control(pDX, IDC_CHK_H39_S3, m_chkChanEnb[39][3]);
}

BEGIN_MESSAGE_MAP(CDlgChanEnb, CDialog)
	ON_BN_CLICKED(IDC_BTN_SET_BRD0, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD1, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD2, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD3, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD4, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD5, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD6, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD7, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD8, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_BRD9, OnBnClickedBtnSetBrd)
	ON_BN_CLICKED(IDC_BTN_SET_ALL, OnBnClickedBtnSetAll)

	ON_BN_CLICKED(IDC_BTN_CLR_BRD0, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD1, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD2, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD3, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD4, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD5, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD6, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD7, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD8, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_BRD9, OnBnClickedBtnClrBrd)
	ON_BN_CLICKED(IDC_BTN_CLR_ALL, OnBnClickedBtnClrAll)

	ON_BN_CLICKED(IDC_BTN_UPD_CHAN_ENB, OnBnClickedBtnUpdChanEnb)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgChanEnb::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	UpdChanEnbCtrl();	// 更新通道使能控件

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新通道使能控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgChanEnb::UpdChanEnbCtrl(void)
{
	CString str;
	ST_CORE_PARAM& core_param = m_pApp->m_stFlawParam.m_stCoreParam;

	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
		if (i < x_nTotBrd)
		{
			////////////////////////////////////////////////////////////////////////////////////////
			// 全部显示

			str.Format("%d", core_param.m_anSynDly[i]);
			m_edtSynDly[i].SetWindowText(str);

			for (U8 j = 0; j < MAX_HARD_NUM; j++)
			{
				U8 hard_num = i * x_nTotHard + j;

				if (j < x_nTotHard)
				{
					str.Format("%d", m_pApp->m_stFlawParam.m_anChanShare[hard_num]);
					m_edtChanShare[hard_num].SetWindowText(str);

					for (U8 k = 0; k < MAX_SOFT_NUM; k++)
					{
						if (k < x_nTotSoft)
						{
							U8 chan_enb = core_param.m_abChanEnb[hard_num][k];
							m_chkChanEnb[hard_num][k].SetCheck(chan_enb);
							if (m_pApp->m_bPci)
							{
								str.Format("%d", hard_num + 1);
								m_chkChanEnb[hard_num][k].SetWindowText(str);
							}
						}
						else
						{
							m_chkChanEnb[hard_num][k].ShowWindow(FALSE);
						}
					}
				}
				else
				{
					m_edtChanShare[hard_num].ShowWindow(FALSE);
					for (U8 k = 0; k < MAX_SOFT_NUM; k++)
					{
						m_chkChanEnb[hard_num][k].ShowWindow(FALSE);
					}
				}
			}
		}
		else
		{
			////////////////////////////////////////////////////////////////////////////////////////
			// 全部隐藏

			m_grpBrd[i].ShowWindow(FALSE);
			m_btnSet[i].ShowWindow(FALSE);
			m_btnClr[i].ShowWindow(FALSE);
			m_edtSynDly[i].ShowWindow(FALSE);

			for (U8 j = 0; j < MAX_HARD_NUM; j++)
			{
				U8 hard_num = i * x_nTotHard + j;
				m_txtHard[hard_num].ShowWindow(FALSE);
				m_edtChanShare[hard_num].ShowWindow(FALSE);

				for (U8 k = 0; k < MAX_SOFT_NUM; k++)
				{
					m_chkChanEnb[hard_num][k].ShowWindow(FALSE);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新通道使能设置
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgChanEnb::OnBnClickedBtnUpdChanEnb(void)
{
	if (m_pApp->UpdChanEnb(this) == TRUE)
	{
		CDialog::OnOK();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 全选

void CDlgChanEnb::ExecChanEnb(U8 brd, BOOL enb)
{
	for (U8 j = 0; j < x_nTotHard; j++)
	{
		U8 hard_num = brd * x_nTotHard + j;
		for (U8 k = 0; k < x_nTotSoft; k++)
		{
			m_chkChanEnb[hard_num][k].SetCheck(enb);
		}
	}
}

void CDlgChanEnb::OnBnClickedBtnBrd(BOOL enb)
{
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		if (enb == TRUE)
		{
			if (((CButton*)GetFocus()) == &m_btnSet[i])
			{
				ExecChanEnb(i, enb);
				return;
			}
		}
		else
		{
			if (((CButton*)GetFocus()) == &m_btnClr[i])
			{
				ExecChanEnb(i, enb);
				return;
			}
		}
	}
}

void CDlgChanEnb::OnBnClickedBtnSetBrd(void)
{
	OnBnClickedBtnBrd(TRUE);
}

void CDlgChanEnb::OnBnClickedBtnSetAll(void)
{
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		ExecChanEnb(i, TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 全清

void CDlgChanEnb::OnBnClickedBtnClrBrd(void)
{
	OnBnClickedBtnBrd(FALSE);
}

void CDlgChanEnb::OnBnClickedBtnClrAll(void)
{
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		ExecChanEnb(i, FALSE);
	}
}
