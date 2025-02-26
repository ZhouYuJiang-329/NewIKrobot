#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgBrdInfo.h"

IMPLEMENT_DYNAMIC(CDlgBrdInfo, CDialog)

CDlgBrdInfo::CDlgBrdInfo(CWnd* pParent) : CDialog(CDlgBrdInfo::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
}

CDlgBrdInfo::~CDlgBrdInfo(void)
{
}

void CDlgBrdInfo::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TXT_IP_ADDR0, m_txtIpAddr[0]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR1, m_txtIpAddr[1]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR2, m_txtIpAddr[2]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR3, m_txtIpAddr[3]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR4, m_txtIpAddr[4]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR5, m_txtIpAddr[5]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR6, m_txtIpAddr[6]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR7, m_txtIpAddr[7]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR8, m_txtIpAddr[8]);
	DDX_Control(pDX, IDC_TXT_IP_ADDR9, m_txtIpAddr[9]);

	DDX_Control(pDX, IDC_TXT_MAC_ADDR0, m_txtMacAddr[0]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR1, m_txtMacAddr[1]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR2, m_txtMacAddr[2]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR3, m_txtMacAddr[3]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR4, m_txtMacAddr[4]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR5, m_txtMacAddr[5]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR6, m_txtMacAddr[6]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR7, m_txtMacAddr[7]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR8, m_txtMacAddr[8]);
	DDX_Control(pDX, IDC_TXT_MAC_ADDR9, m_txtMacAddr[9]);

	DDX_Control(pDX, IDC_TXT_CORE_SN0, m_txtBrdSn[0][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN1, m_txtBrdSn[1][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN2, m_txtBrdSn[2][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN3, m_txtBrdSn[3][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN4, m_txtBrdSn[4][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN5, m_txtBrdSn[5][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN6, m_txtBrdSn[6][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN7, m_txtBrdSn[7][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN8, m_txtBrdSn[8][BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_TXT_CORE_SN9, m_txtBrdSn[9][BRD_SN_TYPE_CORE]);

	DDX_Control(pDX, IDC_TXT_CHAN_SN0, m_txtBrdSn[0][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN1, m_txtBrdSn[1][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN2, m_txtBrdSn[2][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN3, m_txtBrdSn[3][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN4, m_txtBrdSn[4][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN5, m_txtBrdSn[5][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN6, m_txtBrdSn[6][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN7, m_txtBrdSn[7][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN8, m_txtBrdSn[8][BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_TXT_CHAN_SN9, m_txtBrdSn[9][BRD_SN_TYPE_CHAN]);

	DDX_Control(pDX, IDC_TXT_HV_SN0, m_txtBrdSn[0][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN1, m_txtBrdSn[1][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN2, m_txtBrdSn[2][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN3, m_txtBrdSn[3][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN4, m_txtBrdSn[4][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN5, m_txtBrdSn[5][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN6, m_txtBrdSn[6][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN7, m_txtBrdSn[7][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN8, m_txtBrdSn[8][BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_TXT_HV_SN9, m_txtBrdSn[9][BRD_SN_TYPE_HV]);

	DDX_Control(pDX, IDC_TXT_PWR_SN0, m_txtBrdSn[0][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN1, m_txtBrdSn[1][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN2, m_txtBrdSn[2][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN3, m_txtBrdSn[3][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN4, m_txtBrdSn[4][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN5, m_txtBrdSn[5][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN6, m_txtBrdSn[6][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN7, m_txtBrdSn[7][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN8, m_txtBrdSn[8][BRD_SN_TYPE_PWR]);
	DDX_Control(pDX, IDC_TXT_PWR_SN9, m_txtBrdSn[9][BRD_SN_TYPE_PWR]);

	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgBrdInfo, CDialog)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgBrdInfo::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	for (U8 i = 1; i < BRD_SN_TYPE_NUM; i++)
	{
		m_txtBrdSn[i]->EnableWindow(m_pApp->m_bNet);
	}

	m_pApp->FreshBrdInfo(this);
	return TRUE;
}
