#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgAbout.h"

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)

CDlgAbout::CDlgAbout(CWnd* pParent) : CDialog(CDlgAbout::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
}

CDlgAbout::~CDlgAbout(void)
{
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgAbout::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CString str;

	char date_str[20];
	char month_str[10];
	char year_str[10];
	int month, day;

	sprintf(date_str, "%s", __DATE__);
	sscanf(date_str, "%s %d %s", month_str, &day, year_str);

	char MONTH_STR[12][10] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	for (month = 0; month < 12; month ++)
	{
		if (strcmp(month_str, MONTH_STR[month]) == 0)
		{
			break;	// 一定会有返回值
		}
	}

	char type[20];
	sprintf(type, "%s", (m_pApp->m_bPci) ? "PCI" : "NET");

	str.Format("%s, %s-%02d-%02d %s", m_pApp->m_strAppVer, year_str, month + 1, day, __TIME__);
	((CStatic*)GetDlgItem(IDC_TXT_APP_VER))->SetWindowText(str);

	str.Format("ZXUT-%s%s, %s", type, m_pApp->m_strAppName, m_pApp->m_strSoftPlat);
	((CStatic*)GetDlgItem(IDC_TXT_APP_NAME))->SetWindowText(str);

	ST_EXP_INFO& exp_info = *(m_pApp->m_pstExpInfo);
	U8 pcb_ver = exp_info.m_nPcbVer;
	str.Format("v%d.0", pcb_ver);
	((CStatic*)GetDlgItem(IDC_TXT_PCB_VER))->SetWindowText(str);

	U16 fpga_ver = exp_info.m_nFpgaVer;
	str.Format("v%d.%d", fpga_ver / 256, fpga_ver % 256);
	((CStatic*)GetDlgItem(IDC_TXT_FPGA_VER))->SetWindowText(str);

	U16 dev_ver = exp_info.m_nDevVer;
	str.Format("v%d.%d", dev_ver / 256, dev_ver % 256);
	((CStatic*)GetDlgItem(IDC_TXT_DEV_VER))->SetWindowText(str);

	U16 mid_ver = exp_info.m_nMidVer;
	str.Format("v%d.%d", mid_ver / 256, mid_ver % 256);
	((CStatic*)GetDlgItem(IDC_TXT_MID_VER))->SetWindowText(str);

	char inner_sync = (exp_info.m_nInnerSync == BRD_SYNC_PARA) ? 'P' : 'S';
	str.Format("%s-%c%d.%d", type, inner_sync, exp_info.m_nTotHard, exp_info.m_nTotSoft);
	((CStatic*)GetDlgItem(IDC_TXT_BRD_TYPE))->SetWindowText(str);

	return TRUE;
}
