#pragma once

#include "resource.h"
#include "ZxutCmn.h"

class CZxutApp;

const U32 IDC_CLIENT_IP[] =
{
	IDC_CLIENT_IP0,
	IDC_CLIENT_IP1,
	IDC_CLIENT_IP2,
	IDC_CLIENT_IP3,
	IDC_CLIENT_IP4,
	IDC_CLIENT_IP5,
	IDC_CLIENT_IP6,
	IDC_CLIENT_IP7,
	IDC_CLIENT_IP8,
	IDC_CLIENT_IP9
};

const U32 IDC_CONNECT_STS[] =
{
	IDC_CONNECT_STS0,
	IDC_CONNECT_STS1,
	IDC_CONNECT_STS2,
	IDC_CONNECT_STS3,
	IDC_CONNECT_STS4,
	IDC_CONNECT_STS5,
	IDC_CONNECT_STS6,
	IDC_CONNECT_STS7,
	IDC_CONNECT_STS8,
	IDC_CONNECT_STS9
};

class CDlgWaitCnnct : public CDialog
{
	DECLARE_DYNAMIC(CDlgWaitCnnct)

public:
	CDlgWaitCnnct(CWnd* pParent = NULL);

private:
	UINT_PTR m_iTimerID;
	U32 m_nTimeCntr;
	CProgressCtrl* m_pPrgBar;
	CZxutApp* m_pApp;

	virtual BOOL OnInitDialog(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
