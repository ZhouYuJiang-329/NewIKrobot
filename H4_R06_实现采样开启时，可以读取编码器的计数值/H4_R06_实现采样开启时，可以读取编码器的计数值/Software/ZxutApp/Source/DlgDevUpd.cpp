#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgDevUpd.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CDlgDevUpd, CDialog)

CDlgDevUpd::CDlgDevUpd(CWnd* pParent) : CDialog(CDlgDevUpd::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgDevUpd = this;
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
}

CDlgDevUpd::~CDlgDevUpd(void)
{
}

void CDlgDevUpd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_DU_BRD0, m_chkDuBrd[0]);
	DDX_Control(pDX, IDC_CHK_DU_BRD1, m_chkDuBrd[1]);
	DDX_Control(pDX, IDC_CHK_DU_BRD2, m_chkDuBrd[2]);
	DDX_Control(pDX, IDC_CHK_DU_BRD3, m_chkDuBrd[3]);
	DDX_Control(pDX, IDC_CHK_DU_BRD4, m_chkDuBrd[4]);
	DDX_Control(pDX, IDC_CHK_DU_BRD5, m_chkDuBrd[5]);
	DDX_Control(pDX, IDC_CHK_DU_BRD6, m_chkDuBrd[6]);
	DDX_Control(pDX, IDC_CHK_DU_BRD7, m_chkDuBrd[7]);
	DDX_Control(pDX, IDC_CHK_DU_BRD8, m_chkDuBrd[8]);
	DDX_Control(pDX, IDC_CHK_DU_BRD9, m_chkDuBrd[9]);

	DDX_Control(pDX, IDC_BTN_DU_BRD_ALL, m_btnDuBrdAll);
	DDX_Control(pDX, IDC_BTN_DU_BRD_CLR, m_btnDuBrdClr);

	DDX_Control(pDX, IDC_CHK_DU_TYPE_BOOT, m_chkDuTypeBoot);
	DDX_Control(pDX, IDC_CHK_DU_TYPE_DTB, m_chkDuTypeDtb);
	DDX_Control(pDX, IDC_CHK_DU_TYPE_KERNEL, m_chkDuTypeKernel);
	DDX_Control(pDX, IDC_CHK_DU_TYPE_ROOTFS, m_chkDuTypeRootfs);
	DDX_Control(pDX, IDC_CHK_DU_TYPE_CFG, m_chkDuTypeCfg);
	DDX_Control(pDX, IDC_CHK_DU_TYPE_DRV, m_chkDuTypeDrv);
	DDX_Control(pDX, IDC_CHK_DU_TYPE_APP, m_chkDuTypeApp);

	DDX_Control(pDX, IDC_BTN_DU_TYPE_ALL, m_btnDuTypeAll);
	DDX_Control(pDX, IDC_BTN_DU_TYPE_CLR, m_btnDuTypeClr);

	DDX_Control(pDX, IDC_BTN_DU_UPD, m_btnDuUpd);
}

BEGIN_MESSAGE_MAP(CDlgDevUpd, CDialog)
	ON_BN_CLICKED(IDC_BTN_DU_UPD, &CDlgDevUpd::OnBnClickedBtnDuUpd)
	ON_BN_CLICKED(IDC_BTN_DU_BRD_ALL, &CDlgDevUpd::OnBnClickedBtnDuBrdAll)
	ON_BN_CLICKED(IDC_BTN_DU_BRD_CLR, &CDlgDevUpd::OnBnClickedBtnDuBrdClr)
	ON_BN_CLICKED(IDC_BTN_DU_TYPE_ALL, &CDlgDevUpd::OnBnClickedBtnDuTypeAll)
	ON_BN_CLICKED(IDC_BTN_DU_TYPE_CLR, &CDlgDevUpd::OnBnClickedBtnDuTypeClr)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgDevUpd::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	FreshDuCtrl(FALSE);

	m_chkDuTypeDrv.SetCheck(TRUE);
	m_chkDuTypeApp.SetCheck(TRUE);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDevUpd::FreshDuCtrl(BOOL bSmplEnb)
{
	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
		if (i < x_nTotBrd)
		{
			m_chkDuBrd[i].EnableWindow(!bSmplEnb);
			m_chkDuBrd[i].SetCheck(TRUE);
		}
		else
		{
			m_chkDuBrd[i].EnableWindow(FALSE);
		}
	}

	m_btnDuBrdAll.EnableWindow(!bSmplEnb);
	m_btnDuBrdClr.EnableWindow(!bSmplEnb);

	m_btnDuUpd.EnableWindow(!bSmplEnb);

	////////////////////////////////////////////////////////////////////////////////////////////////

	m_chkDuTypeBoot.EnableWindow(!bSmplEnb);
	m_chkDuTypeDtb.EnableWindow(!bSmplEnb);
	m_chkDuTypeKernel.EnableWindow(!bSmplEnb);
	m_chkDuTypeRootfs.EnableWindow(!bSmplEnb);

	m_chkDuTypeCfg.EnableWindow(!bSmplEnb);
	m_chkDuTypeDrv.EnableWindow(!bSmplEnb);
	m_chkDuTypeApp.EnableWindow(!bSmplEnb);

	m_btnDuTypeAll.EnableWindow(!bSmplEnb);
	m_btnDuTypeClr.EnableWindow(!bSmplEnb);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设备软件更新
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDevUpd::OnBnClickedBtnDuUpd(void)
{
	BOOL res;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 确认板卡

	res = FALSE;
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		if (m_chkDuBrd[i].GetCheck() == TRUE)
		{
			res = TRUE;
			break;
		}
	}

	if (res == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_INFO, "请选择需要更新的板卡");
		return;
	}

	BOOL upd_brd[MAX_BRD_NUM];
	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
		if (i < x_nTotBrd)
		{
			upd_brd[i] = m_chkDuBrd[i].GetCheck();	// 已连接的板卡
		}
		else
		{
			upd_brd[i] = FALSE;	// 没有连接的板卡
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 确认更新类型

	BOOL upd_type[UPD_TYPE_NUM];

	upd_type[UPD_TYPE_BOOT]		= m_chkDuTypeBoot.GetCheck();
	upd_type[UPD_TYPE_DTB]		= m_chkDuTypeDtb.GetCheck();
	upd_type[UPD_TYPE_KERNEL]	= m_chkDuTypeKernel.GetCheck();
	upd_type[UPD_TYPE_ROOTFS]	= m_chkDuTypeRootfs.GetCheck();

	upd_type[UPD_TYPE_CFG]		= m_chkDuTypeCfg.GetCheck();
	upd_type[UPD_TYPE_DRV]		= m_chkDuTypeDrv.GetCheck();
	upd_type[UPD_TYPE_APP]		= m_chkDuTypeApp.GetCheck();

	res = FALSE;
	for (U8 i = 0; i < UPD_TYPE_NUM; i++)
	{
		if (upd_type[i] == TRUE)
		{
			res = TRUE;
			break;
		}
	}
	if (res == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_INFO, "请选择需要更新的类型");
		return;
	}

	ZXUT_UpdDevSoft(m_pApp->m_nClientIpAddr, m_pApp->m_anBrdIdx, upd_brd, upd_type);	// 开始设备更新
	m_pApp->m_pDlgZxut->OnBnClickedBtnClientReboot();	// 客户端重启
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 全选/全清板卡
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDevUpd::OnBnClickedBtnDuBrdAll(void)
{
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		m_chkDuBrd->SetCheck(TRUE);
	}
}

void CDlgDevUpd::OnBnClickedBtnDuBrdClr(void)
{
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		m_chkDuBrd->SetCheck(FALSE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 全选/全清更新类型
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgDevUpd::DuTypeEnb(BOOL enb)
{
	m_chkDuTypeBoot		.SetCheck(enb);
	m_chkDuTypeDtb		.SetCheck(enb);
	m_chkDuTypeKernel	.SetCheck(enb);
	m_chkDuTypeRootfs	.SetCheck(enb);

	m_chkDuTypeCfg		.SetCheck(enb);
	m_chkDuTypeDrv		.SetCheck(enb);
	m_chkDuTypeApp		.SetCheck(enb);
}

void CDlgDevUpd::OnBnClickedBtnDuTypeAll(void)
{
	DuTypeEnb(TRUE);
}

void CDlgDevUpd::OnBnClickedBtnDuTypeClr(void)
{
	DuTypeEnb(FALSE);
}
