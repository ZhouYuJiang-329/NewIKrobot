#include "stdafx.h"
#include "DlgWaitCnnct.h"
#include "ZxutApp.h"

IMPLEMENT_DYNAMIC(CDlgWaitCnnct, CDialog)
CDlgWaitCnnct::CDlgWaitCnnct(CWnd* pParent)
	: CDialog(IDD_WAIT_CNNCT, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pdlgWaitCnnct = this;
	m_pPrgBar = NULL;
	m_nTimeCntr = 0;
}

BEGIN_MESSAGE_MAP(CDlgWaitCnnct, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CDlgWaitCnnct::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CString str;

	for (U8 i = 0; i < MAX_BRD_NUM; i ++)
	{
		str.Format(" %d#°å¿¨", i + 1);
		SetDlgItemText(IDC_CLIENT_IP[i], str);
		SetDlgItemText(IDC_CONNECT_STS[i], " µÈ´ýÁ¬½Ó...");
	}

	str.Format("%d", m_pApp->m_stFlawParam.m_nNetPort);
	((CStatic*)GetDlgItem(IDC_TXT_NET_PORT))->SetWindowText(str);

	U32 ip_addr = m_pApp->m_nClientIpAddr;
	str.Format("%d.%d.%d.%d",
		(ip_addr >> 3 * 8) & 0xFF,
		(ip_addr >> 2 * 8) & 0xFF,
		(ip_addr >> 1 * 8) & 0xFF,
		(ip_addr >> 0 * 8) & 0xFF);
	((CStatic*)GetDlgItem(IDC_TXT_IP_ADDR))->SetWindowText(str);

	m_pPrgBar = (CProgressCtrl*)GetDlgItem(IDC_PRG_BAR);
	m_pPrgBar->SetRange(0, 100);

	m_iTimerID = SetTimer(103, 100, NULL);

	m_pApp->m_bDlgWaitOk = TRUE;

	return TRUE;
}

void CDlgWaitCnnct::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	m_pPrgBar->SetPos(m_nTimeCntr % 100);

	CString str;
	str.Format("%02d:%02d:%02d",
		(((m_nTimeCntr / 10) / 60) / 60),	// h
		(((m_nTimeCntr / 10) / 60) % 60),	// m
		((m_nTimeCntr / 10) % 60));			// s
	SetDlgItemText(IDC_PRG_TEXT, str);

	if (m_pApp->m_bIsClientCnncted == TRUE)
	{
		KillTimer(m_iTimerID);
		CDialog::OnOK();
		return;
	}
	m_nTimeCntr++;
}
