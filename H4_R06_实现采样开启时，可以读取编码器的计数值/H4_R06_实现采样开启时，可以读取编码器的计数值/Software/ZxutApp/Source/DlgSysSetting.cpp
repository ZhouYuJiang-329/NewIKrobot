#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgSysSetting.h"
#include "DlgBrdInfo.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CDlgSysSetting, CDialog)
CDlgSysSetting::CDlgSysSetting(CWnd* pParent) : CDialog(CDlgSysSetting::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgSysSetting = this;
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
}

CDlgSysSetting::~CDlgSysSetting(void)
{
}

void CDlgSysSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDT_IP_ADDR0, m_edtIpAddr[0]);
	DDX_Control(pDX, IDC_EDT_IP_ADDR1, m_edtIpAddr[1]);
	DDX_Control(pDX, IDC_EDT_IP_ADDR2, m_edtIpAddr[2]);
	DDX_Control(pDX, IDC_EDT_IP_ADDR3, m_edtIpAddr[3]);
	DDX_Control(pDX, IDC_EDT_IP_ADDR4, m_edtIpAddr[4]);

	DDX_Control(pDX, IDC_EDT_NET_PORT, m_edtNetPort);

	DDX_Control(pDX, IDC_TXT_CPU_TEMP0, m_txtCpuTemp[0]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP1, m_txtCpuTemp[1]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP2, m_txtCpuTemp[2]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP3, m_txtCpuTemp[3]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP4, m_txtCpuTemp[4]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP5, m_txtCpuTemp[5]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP6, m_txtCpuTemp[6]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP7, m_txtCpuTemp[7]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP8, m_txtCpuTemp[8]);
	DDX_Control(pDX, IDC_TXT_CPU_TEMP9, m_txtCpuTemp[9]);

	DDX_Control(pDX, IDC_TXT_PCB_TEMP0, m_txtPcbTemp[0]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP1, m_txtPcbTemp[1]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP2, m_txtPcbTemp[2]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP3, m_txtPcbTemp[3]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP4, m_txtPcbTemp[4]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP5, m_txtPcbTemp[5]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP6, m_txtPcbTemp[6]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP7, m_txtPcbTemp[7]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP8, m_txtPcbTemp[8]);
	DDX_Control(pDX, IDC_TXT_PCB_TEMP9, m_txtPcbTemp[9]);

	DDX_Control(pDX, IDC_TXT_DIF_TEMP0, m_txtDifTemp[0]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP1, m_txtDifTemp[1]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP2, m_txtDifTemp[2]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP3, m_txtDifTemp[3]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP4, m_txtDifTemp[4]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP5, m_txtDifTemp[5]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP6, m_txtDifTemp[6]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP7, m_txtDifTemp[7]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP8, m_txtDifTemp[8]);
	DDX_Control(pDX, IDC_TXT_DIF_TEMP9, m_txtDifTemp[9]);

	DDX_Control(pDX, IDC_EDT_SN_CORE,		m_edtBrdSn[BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_EDT_SN_CHAN,		m_edtBrdSn[BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_EDT_SN_HV,			m_edtBrdSn[BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_EDT_SN_PWR,		m_edtBrdSn[BRD_SN_TYPE_PWR]);

	DDX_Text(pDX, IDC_EDT_SN_CORE,			m_strBrdSn[BRD_SN_TYPE_CORE]);
	DDX_Text(pDX, IDC_EDT_SN_CHAN,			m_strBrdSn[BRD_SN_TYPE_CHAN]);
	DDX_Text(pDX, IDC_EDT_SN_HV,			m_strBrdSn[BRD_SN_TYPE_HV]);
	DDX_Text(pDX, IDC_EDT_SN_PWR,			m_strBrdSn[BRD_SN_TYPE_PWR]);

	DDX_Control(pDX, IDC_BTN_SN_RD_CORE,	m_btnBrdSnRd[BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_BTN_SN_RD_CHAN,	m_btnBrdSnRd[BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_BTN_SN_RD_HV,		m_btnBrdSnRd[BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_BTN_SN_RD_PWR,		m_btnBrdSnRd[BRD_SN_TYPE_PWR]);

	DDX_Control(pDX, IDC_BTN_SN_WR_CORE,	m_btnBrdSnWr[BRD_SN_TYPE_CORE]);
	DDX_Control(pDX, IDC_BTN_SN_WR_CHAN,	m_btnBrdSnWr[BRD_SN_TYPE_CHAN]);
	DDX_Control(pDX, IDC_BTN_SN_WR_HV,		m_btnBrdSnWr[BRD_SN_TYPE_HV]);
	DDX_Control(pDX, IDC_BTN_SN_WR_PWR,		m_btnBrdSnWr[BRD_SN_TYPE_PWR]);

	DDX_Control(pDX, IDC_BTN_UPD_SET_NET_CFG,	m_btnUpdSetNetCfg);
	DDX_Control(pDX, IDC_BTN_UPD_DEF_NET_CFG,	m_btnUpdDefNetCfg);

	DDX_Control(pDX, IDC_EDT_NEDD_BRD_NUM,	m_edtNeedBrdNum);
	DDX_Control(pDX, IDC_CHK_SMPL_ACT,		m_chkSmplAct);
}

BEGIN_MESSAGE_MAP(CDlgSysSetting, CDialog)
	ON_BN_CLICKED(IDC_BTN_UPD_SET_NET_CFG, OnBnClickedBtnUpdSetNetCfg)
	ON_BN_CLICKED(IDC_BTN_UPD_DEF_NET_CFG, OnBnClickedBtnUpdDefNetCfg)
	ON_BN_CLICKED(IDC_BTN_SN_RD_CORE, &CDlgSysSetting::OnBnClickedBtnSnRdCore)
	ON_BN_CLICKED(IDC_BTN_SN_WR_CORE, &CDlgSysSetting::OnBnClickedBtnSnWrCore)
	ON_BN_CLICKED(IDC_BTN_SN_RD_CHAN, &CDlgSysSetting::OnBnClickedBtnSnRdChan)
	ON_BN_CLICKED(IDC_BTN_SN_WR_CHAN, &CDlgSysSetting::OnBnClickedBtnSnWrChan)
	ON_BN_CLICKED(IDC_BTN_SN_RD_HV, &CDlgSysSetting::OnBnClickedBtnSnRdHv)
	ON_BN_CLICKED(IDC_BTN_SN_WR_HV, &CDlgSysSetting::OnBnClickedBtnSnWrHv)
	ON_BN_CLICKED(IDC_BTN_SN_RD_PWR, &CDlgSysSetting::OnBnClickedBtnSnRdPwr)
	ON_BN_CLICKED(IDC_BTN_SN_WR_PWR, &CDlgSysSetting::OnBnClickedBtnSnWrPwr)
	ON_BN_CLICKED(IDC_BTN_BRD_INFO, &CDlgSysSetting::OnBnClickedBtnBrdInfo)
	ON_BN_CLICKED(IDC_CHK_SMPL_ACT, &CDlgSysSetting::OnBnClickedChkSmplAct)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgSysSetting::OnInitDialog(VOID)
{
	CDialog::OnInitDialog();

	char str[10];
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	for (U8 i = 0; i < BRD_SN_TYPE_NUM; i++)
	{
		if (i != BRD_SN_TYPE_CHAN)
		{
			m_edtBrdSn[i].EnableWindow(m_pApp->m_bNet);
			m_btnBrdSnRd[i].EnableWindow(m_pApp->m_bNet);
			m_btnBrdSnWr[i].EnableWindow(m_pApp->m_bNet);
		}
	}

	UpdBrdSn();	// 显示板号

	// 客户机首地址
	for (U8 i = 0; i < 4; i++)
	{
		sprintf(str, "%d", param.m_anIpAddr[i]);
		m_edtIpAddr[i].SetWindowText(str);
		m_edtIpAddr[i].EnableWindow(m_pApp->m_bNet);
	}

	// 服务器地址
	sprintf(str, "%d", param.m_anIpAddr[4]);
	m_edtIpAddr[4].SetWindowText(str);
	m_edtIpAddr[4].EnableWindow(m_pApp->m_bNet);

	// 网络端口
	sprintf(str, "%d", param.m_nNetPort);
	m_edtNetPort.SetWindowText(str);
	m_edtNetPort.EnableWindow(m_pApp->m_bNet);

	m_btnUpdSetNetCfg.EnableWindow(m_pApp->m_bNet);
	m_btnUpdDefNetCfg.EnableWindow(m_pApp->m_bNet);

	sprintf(str, "%d", param.m_nNeedBrdNum);
	m_edtNeedBrdNum.SetWindowText(str);
	m_edtNeedBrdNum.EnableWindow(m_pApp->m_bNet);

	m_chkSmplAct.SetCheck(m_pApp->m_stFlawParam.m_bSmplAct);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新设定的网络配置
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::OnBnClickedBtnUpdSetNetCfg(void)
{
	CString str;
	U8 net_ip[5];
	U32 net_port;

	m_edtIpAddr[0].GetWindowText(str);
	net_ip[0] = atoi(str);
	if (net_ip[0] == 0)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "客户机首地址，第1字段不能为0");
		m_edtIpAddr[0].SetFocus();
		m_edtIpAddr[0].SetSel(0, -1);
		return;
	}

	m_edtIpAddr[1].GetWindowText(str);
	net_ip[1] = atoi(str);

	m_edtIpAddr[2].GetWindowText(str);
	net_ip[2] = atoi(str);

	m_edtIpAddr[3].GetWindowText(str);
	net_ip[3] = atoi(str);
	if (net_ip[3] == 0)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "客户机首地址，第4字段不能为0");
		m_edtIpAddr[3].SetFocus();
		m_edtIpAddr[3].SetSel(0, -1);
		return;
	}
	else if (net_ip[3] == 1)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "客户机首地址，第4字段不能为1");
		m_edtIpAddr[3].SetFocus();
		m_edtIpAddr[3].SetSel(0, -1);
		return;
	}
	else if (net_ip[3] > 251)
	{
		// 最后有效地址：251, 252, 253, 254
		m_pApp->DispMsg(ZXUT_MSG_ERR, "客户机首地址，第4字段不能大于251");
		m_edtIpAddr[3].SetFocus();
		m_edtIpAddr[3].SetSel(0, -1);
		return;
	}

	m_edtIpAddr[4].GetWindowText(str);
	net_ip[4] = atoi(str);
	if (net_ip[4] == 0)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "服务器地址，第4字段不能为0");
		m_edtIpAddr[4].SetFocus();
		m_edtIpAddr[4].SetSel(0, -1);
		return;
	}
	else if (net_ip[4] == 1)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "服务器地址，第4字段不能为1");
		m_edtIpAddr[4].SetFocus();
		m_edtIpAddr[4].SetSel(0, -1);
		return;
	}
	else if (net_ip[4] > 251)
	{
		// 最后有效地址：251, 252, 253, 254
		m_pApp->DispMsg(ZXUT_MSG_ERR, "服务器地址，第4字段不能大于251");
		m_edtIpAddr[4].SetFocus();
		m_edtIpAddr[4].SetSel(0, -1);
		return;
	}

	if ((net_ip[4] >= net_ip[3]) && (net_ip[4] <= net_ip[3] + 3))
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "服务器和客户机地址，第4字段不能重复");
		m_edtIpAddr[4].SetFocus();
		m_edtIpAddr[4].SetSel(0, -1);
		return;
	}

	m_edtNetPort.GetWindowText(str);
	net_port = atoi(str);

	////////////////////////////////////////////////////////////////////////////////////////////////

	S32 ret = m_pApp->DispMsg(ZXUT_MSG_ASK,
		"客户机首地址为：%d.%d.%d.%d\n"
		"服务器地址为：%d.%d.%d.%d\n"
		"网路端口为：%d\n"
		"确认修改吗？",
		net_ip[0], net_ip[1], net_ip[2], net_ip[3],
		net_ip[0], net_ip[1], net_ip[2], net_ip[4],
		net_port);
	if (ret == IDYES)
	{
		ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
		memcpy(param.m_anIpAddr, net_ip, sizeof(net_ip));
		param.m_nNetPort = net_port;

		for (U8 i = 0; i < x_nTotBrd; i++)
		{
			ZXUT_SetNetCfg(i, net_ip, net_port);
		}

		m_pApp->DispMsg(ZXUT_MSG_INFO,
			"即将关闭软件，设备已经重启\n"
			"稍后请重新开启软件");

		OnOK();

		m_pApp->m_nAppExitCmd = APP_EXIT_CMD_REBOOT;
		m_pApp->m_pDlgZxut->OnCancel();
	}
	else
	{
		m_edtIpAddr[3].SetFocus();
		m_edtIpAddr[3].SetSel(0, -1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新缺省的网络配置
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::OnBnClickedBtnUpdDefNetCfg(void)
{
	CString str;
	U8 net_ip[5] = {CS_DEFAULT_IP0, CS_DEFAULT_IP1, CS_DEFAULT_IP2, CS_DEFAULT_IP3, CS_DEFAULT_IP4};
	U32 net_port = CS_DEFAULT_PORT;

	S32 ret = m_pApp->DispMsg(ZXUT_MSG_ASK,
		"客户机首地址为：%d.%d.%d.%d\n"
		"服务器地址为：%d.%d.%d.%d\n"
		"网路端口为：%d\n"
		"确认修改吗？",
		net_ip[0], net_ip[1], net_ip[2], net_ip[3],
		net_ip[0], net_ip[1], net_ip[2], net_ip[4],
		net_port);
	if (ret == IDYES)
	{
		for (U8 i = 0; i < 5; i++)
		{
			str.Format("%d", net_ip[i]);
			m_edtIpAddr[i].SetWindowText(str);
		}

		str.Format("%d", CS_DEFAULT_PORT);
		m_edtNetPort.SetWindowText(str);

		////////////////////////////////////////////////////////////////////////////////////////////

		ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
		memcpy(param.m_anIpAddr, net_ip, sizeof(net_ip));
		param.m_nNetPort = net_port;

		for (U8 i = 0; i < x_nTotBrd; i++)
		{
			ZXUT_SetNetCfg(i, net_ip, net_port);
		}

		m_pApp->DispMsg(ZXUT_MSG_INFO,
			"即将关闭软件，设备已经重启\n"
			"稍后请重新开启软件");

		OnOK();

		m_pApp->m_nAppExitCmd = APP_EXIT_CMD_REBOOT;
		m_pApp->m_pDlgZxut->OnCancel();
	}
	else
	{
		m_edtIpAddr[3].SetFocus();
		m_edtIpAddr[3].SetSel(0, -1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 读取板卡的温度值
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::UpdTempValue(U8 nBrdNum)
{
	static F32 tot_cpu_temp[MAX_BRD_NUM];
	static F32 tot_pcb_temp[MAX_BRD_NUM];
	CString msg;

	U32& proc_cntr = m_pApp->m_nUpdProcCntr[GATE_SEL_A];

	for (int i = 0; i < x_nTotBrd; i++)
	{
		if (m_pApp->m_stFlawParam.m_nDispUpd == DISP_UPD_REAL)
		{
			if (i == nBrdNum)
			{
				// 实时显示温度值
				F32 cpu_temp = m_pApp->m_fAvgCpuTemp = m_pApp->m_fCpuTempValue[i];
				F32 pcb_temp = m_pApp->m_fAvgPcbTemp = m_pApp->m_fPcbTempValue[i];

				if (m_pApp->m_bNet)
				{
					msg.Format("%.1f", cpu_temp);
					m_txtCpuTemp[i].SetWindowText(msg);
				}

				msg.Format("%.1f", pcb_temp);
				m_txtPcbTemp[i].SetWindowText(msg);

				if (m_pApp->m_bNet)
				{
					msg.Format("%.1f", cpu_temp - pcb_temp);
					m_txtDifTemp[i].SetWindowText(msg);
				}
			}
		}
		else
		{
			if (proc_cntr == 0)
			{
				tot_cpu_temp[i] = 0.0;
				tot_pcb_temp[i] = 0.0;
			}

			tot_cpu_temp[i] += m_pApp->m_fCpuTempValue[i];
			tot_pcb_temp[i] += m_pApp->m_fPcbTempValue[i];

			if (proc_cntr == m_pApp->m_nUpdProcEnd - 1)
			{
				// 显示平均之后的温度值

				F32 avg_cpu_temp = tot_cpu_temp[i] / m_pApp->m_nUpdProcEnd;
				if (m_pApp->m_bNet)
				{
					msg.Format("%.1f", avg_cpu_temp);
					m_txtCpuTemp[i].SetWindowText(msg);
				}

				F32 avg_pcb_temp = tot_pcb_temp[i] / m_pApp->m_nUpdProcEnd;
				msg.Format("%.1f", avg_pcb_temp);
				m_txtPcbTemp[i].SetWindowText(msg);

				F32 avg_dif_temp = avg_cpu_temp - avg_pcb_temp;
				if (m_pApp->m_bNet)
				{
					msg.Format("%.1f", avg_dif_temp);
					m_txtDifTemp[i].SetWindowText(msg);
				}

				if (i == nBrdNum)
				{
					m_pApp->m_fAvgCpuTemp = avg_cpu_temp;
					m_pApp->m_fAvgPcbTemp = avg_pcb_temp;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 访问板号
//
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 读指定板号

void CDlgSysSetting::OnBnClickedBtnSnRdCore(void)
{
	m_pApp->RdBrdSn(BRD_SN_TYPE_CORE);
}

void CDlgSysSetting::OnBnClickedBtnSnRdChan(void)
{
	m_pApp->RdBrdSn(BRD_SN_TYPE_CHAN);
}

void CDlgSysSetting::OnBnClickedBtnSnRdHv(void)
{
	m_pApp->RdBrdSn(BRD_SN_TYPE_HV);
}

void CDlgSysSetting::OnBnClickedBtnSnRdPwr(void)
{
	m_pApp->RdBrdSn(BRD_SN_TYPE_PWR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 写指定板号

void CDlgSysSetting::OnBnClickedBtnSnWrCore(void)
{
	m_pApp->WrBrdSn(BRD_SN_TYPE_CORE);
}

void CDlgSysSetting::OnBnClickedBtnSnWrChan(void)
{
	m_pApp->WrBrdSn(BRD_SN_TYPE_CHAN);
}

void CDlgSysSetting::OnBnClickedBtnSnWrHv(void)
{
	m_pApp->WrBrdSn(BRD_SN_TYPE_HV);
}

void CDlgSysSetting::OnBnClickedBtnSnWrPwr(void)
{
	m_pApp->WrBrdSn(BRD_SN_TYPE_PWR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 当前更新板号
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::UpdBrdSn(void)
{
	U8 brd_num = m_pApp->m_nHardNum / m_pApp->m_pstExpInfo->m_nTotHard;

	if (m_pApp->m_bPci)
	{
		m_strBrdSn[BRD_SN_TYPE_CHAN].Format("%s", m_pApp->m_pstExpInfo->m_aastrBrdSn[brd_num][0]);	// 只有1个板号，即通道板
	}
	else
	{
		m_strBrdSn[BRD_SN_TYPE_CORE].Format("%s", m_pApp->m_pstExpInfo->m_aastrBrdSn[brd_num][BRD_SN_TYPE_CORE]);
		m_strBrdSn[BRD_SN_TYPE_CHAN].Format("%s", m_pApp->m_pstExpInfo->m_aastrBrdSn[brd_num][BRD_SN_TYPE_CHAN]);
		m_strBrdSn[BRD_SN_TYPE_HV].Format("%s", m_pApp->m_pstExpInfo->m_aastrBrdSn[brd_num][BRD_SN_TYPE_HV]);
		m_strBrdSn[BRD_SN_TYPE_PWR].Format("%s", m_pApp->m_pstExpInfo->m_aastrBrdSn[brd_num][BRD_SN_TYPE_PWR]);
	}
	UpdateData(FALSE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 读取通道板信息
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::OnBnClickedBtnBrdInfo(void)
{
	CDlgBrdInfo dlg;
	dlg.DoModal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 避免回车后响应OnOK()
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::OnOK(void)
{
	if (GetFocus() == &m_edtNeedBrdNum)
	{
		CString str;
		m_edtNeedBrdNum.GetWindowText(str);
		U32 tmp = _ttoi(str);
		if (tmp > MAX_BRD_NUM)
		{
			m_pApp->DispMsg(ZXUT_MSG_ERR, "输入的板卡数%d，超出板卡总数为%d的限制", tmp, MAX_BRD_NUM);
			return;
		}
		m_pApp->m_stFlawParam.m_nNeedBrdNum = tmp;	// 读取需要连接板卡数
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 一打开软件就开启采样
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgSysSetting::OnBnClickedChkSmplAct(void)
{
	m_pApp->m_stFlawParam.m_bSmplAct = m_chkSmplAct.GetCheck();
}
