#include "stdafx.h"
#include "ZxutApp.h"
#include "ZxutDlg.h"
#include "SmplShow.h"
#include "DlgKeyHlp.h"
#include "DlgAbout.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

CZxutDlg::CZxutDlg(CWnd* pParent)
	: CDialog(CZxutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgZxut = this;
}

void CZxutDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_BTN_SMPL_ENB, m_btnSmplEnb);
	DDX_Control(pDX, IDC_TAB_ZXUT, m_tabZxut);
	DDX_Control(pDX, IDC_TXT_PEAK_DIST, m_txtPeakDist);
	DDX_Control(pDX, IDC_TXT_PEAK_HEIGHT, m_txtPeakHeight);
	DDX_Control(pDX, IDC_CHK_AUTO_GAIN, m_chkAutoGain);
	DDX_Control(pDX, IDC_TXT_RUN_TIME, m_txtRunTime);
	DDX_Control(pDX, IDC_LED_OVER_HEIGHT, m_ledOverHeight);

	DDX_Control(pDX, IDC_BTN_CLIENT_EXIT, m_btnClientExit);
	DDX_Control(pDX, IDC_BTN_CLIENT_REBOOT, m_btnClientReboot);
	DDX_Control(pDX, IDC_BTN_CLIENT_HALT, m_btnClientHalt);

	DDX_Control(pDX, IDC_CHK_RT_MEM, m_chkRtMem);
	DDX_Control(pDX, IDC_EDT_RT_MEM, m_edtRtMem);

	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZxutDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BTN_SMPL_ENB, OnBnClickedBtnSmplEnb)
	ON_BN_CLICKED(IDC_BTN_CLIENT_EXIT, OnBnClickedBtnClientExit)
	ON_BN_CLICKED(IDC_BTN_CLIENT_REBOOT, &CZxutDlg::OnBnClickedBtnClientReboot)
	ON_BN_CLICKED(IDC_BTN_CLIENT_HALT, &CZxutDlg::OnBnClickedBtnClientHalt)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ZXUT, &CZxutDlg::OnTcnSelchangeTabZxut)
	ON_BN_CLICKED(IDC_BTN_KEY_HLP, &CZxutDlg::OnBnClickedBtnKeyHlp)
	ON_BN_CLICKED(IDC_BTN_WAVE_EXPORT, &CZxutDlg::OnBnClickedBtnWaveExport)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CZxutDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_CHK_RT_MEM, &CZxutDlg::OnBnClickedChkRtMem)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

HCURSOR CZxutDlg::OnQueryDragIcon(void)
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CZxutDlg::OnPaint(void)
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	m_nTimeCntr = 0;
	m_iTimerID = SetTimer(104, 1000, NULL);

	m_pApp->m_hSmplShowWnd = GetDlgItem(IDC_BASE_MAP_WAVE)->GetSafeHwnd();
	m_pApp->m_pSmplShow->InitWndHandle(m_pApp->m_hSmplShowWnd);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_ledOverHeight.SetState(LED_DIS);

	////////////////////////////////////////////////////////////////////////////////////////////////

	m_fntTxt.CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "Verdana");

	m_txtPeakDist.SetFont(&m_fntTxt);
	m_txtPeakDist.SetTextColor(RGB(255, 0, 0));

	m_txtPeakHeight.SetFont(&m_fntTxt);
	m_txtPeakHeight.SetTextColor(RGB(0, 0, 255));

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取产品名称和版本

	char date_str[20];
	char month_str[10];
	char day_str[10];
	char year_str[10];

	sprintf(date_str, "%s", __DATE__);
	sscanf(date_str, "%s %s %s", month_str, day_str, year_str);

	char type[20];
	sprintf(type, "%s", (m_pApp->m_bPci) ? "PCI" : "NET");

	CString str;
	str.Format("ZXUT-%s%s %s (C) 2007-%s 武汉泽旭科技有限公司 %s",
		type,
		m_pApp->m_strAppName,
		m_pApp->m_strAppVer,
		year_str,
		m_pApp->m_strSoftPlat);
	SetWindowText(str);

	////////////////////////////////////////////////////////////////////////////////////////////////

	m_pApp->m_bSmplEnb = FALSE;
	m_btnSmplEnb.SetWindowText("开启采样");

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Tab控件

	// 初始化
	m_tabZxut.InsertItem(TAB_FLAW_PARAM,	"探伤参数");
	m_tabZxut.InsertItem(TAB_FLAW_GATE,		"探伤闸门");
	m_tabZxut.InsertItem(TAB_DIG_IN,		"数字输入");
	m_tabZxut.InsertItem(TAB_DIG_OUT,		"数字输出");
	m_tabZxut.InsertItem(TAB_ENC_MODU,		"编码器");
	m_tabZxut.InsertItem(TAB_TCG_PROC,		"TCG处理");
	m_tabZxut.InsertItem(TAB_SYS_SETTING,	"系统设置");
	m_tabZxut.InsertItem(TAB_FFT_PROC,		"FFT处理");

	// 建立属性页各页
	m_dlgFlawParam.Create(IDD_FLAW_PARAM,	GetDlgItem(IDC_TAB_ZXUT));
	m_dlgFlawGate.Create(IDD_FLAW_GATE,		GetDlgItem(IDC_TAB_ZXUT));
	m_dlgDigIn.Create(IDD_DIG_IN,			GetDlgItem(IDC_TAB_ZXUT));
	m_dlgDigOut.Create(IDD_DIG_OUT,			GetDlgItem(IDC_TAB_ZXUT));
	m_dlgEncModu.Create(IDD_ENC_MODU,		GetDlgItem(IDC_TAB_ZXUT));
	m_dlgTcgProc.Create(IDD_TCG_PROC,		GetDlgItem(IDC_TAB_ZXUT));
	m_dlgSysSetting.Create(IDD_SYS_SETTING,	GetDlgItem(IDC_TAB_ZXUT));
	m_dlgFftProc.Create(IDD_FFT_PROC,		GetDlgItem(IDC_TAB_ZXUT));

	// 设置页面的位置在m_tab控件范围内
	CRect rect;
	m_tabZxut.GetClientRect(&rect);
	rect.top += 25;
	rect.bottom -= 4;
	rect.left += 4;
	rect.right -= 4;

	m_dlgFlawParam.MoveWindow(&rect);
	m_dlgFlawGate.MoveWindow(&rect);
	m_dlgDigIn.MoveWindow(&rect);
	m_dlgDigOut.MoveWindow(&rect);
	m_dlgEncModu.MoveWindow(&rect);
	m_dlgTcgProc.MoveWindow(&rect);
	m_dlgSysSetting.MoveWindow(&rect);
	m_dlgFftProc.MoveWindow(&rect);

	// 只有网络探伤设备才可进行设备更新
	if (m_pApp->m_bDevUpdEnb)
	{
		m_tabZxut.InsertItem(TAB_DEV_UPD, "设备更新");
		m_dlgDevUpd.Create(IDD_DEV_UPD,	GetDlgItem(IDC_TAB_ZXUT));
		m_dlgDevUpd.MoveWindow(&rect);
	}

	m_dlgFlawParam.ShowWindow(TRUE);
	m_tabZxut.SetCurSel(0);

	m_btnClientExit.EnableWindow(m_pApp->m_bNet);
	m_btnClientReboot.EnableWindow(m_pApp->m_bNet);
	m_btnClientHalt.EnableWindow(m_pApp->m_bNet);

	// 设置实时存储
	str.Format("%d", m_pApp->m_stFlawParam.m_nRtMemTime);
	m_edtRtMem.SetWindowText(str);

	if (m_pApp->m_stFlawParam.m_bSmplAct)
	{
		OnBnClickedBtnSmplEnb();	// 一旦连接上客户机，立即开启采样
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 开启/关闭采样
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnBnClickedBtnSmplEnb(void)
{
	m_pApp->SetSmplEnb();
	m_pApp->m_pDlgFftProc->m_btnRecBw.EnableWindow(FALSE);

	m_pApp->m_pDlgFlawParam->m_btnTstVertLinear.EnableWindow(m_pApp->m_bSmplEnb);
	m_pApp->m_pDlgFlawParam->m_edtMaxDaqRate.EnableWindow(!m_pApp->m_bSmplEnb);
	m_chkRtMem.EnableWindow(!m_pApp->m_bSmplEnb);
	m_edtRtMem.EnableWindow(!m_pApp->m_bSmplEnb);

	if (m_pApp->m_bSmplEnb == TRUE)
	{
		// 采样开启
		m_btnSmplEnb.SetWindowText("关闭采样");
	}
	else
	{
		// 采样关闭
		m_btnSmplEnb.SetWindowText("开启采样");
	}

	if (m_pApp->m_bSmplEnb == TRUE)
	{
		BOOL sn_ctrl_enb = FALSE;	// 一旦开启采样，禁止如下操作

		m_pApp->m_pDlgFlawParam->m_btnTstUsrReg.EnableWindow(sn_ctrl_enb);

		for (U8 i = 0; i < BRD_SN_TYPE_NUM; i++)
		{
			CDlgSysSetting* pdlg = m_pApp->m_pDlgSysSetting;
			pdlg->m_edtBrdSn[i]	 .EnableWindow(sn_ctrl_enb);
			pdlg->m_btnBrdSnRd[i].EnableWindow(sn_ctrl_enb);
			pdlg->m_btnBrdSnWr[i].EnableWindow(sn_ctrl_enb);
		}

		if (m_pApp->m_bDevUpdEnb)
		{
			m_pApp->m_pDlgDevUpd->FreshDuCtrl(TRUE);
		}
	}

	m_pApp->m_pDlgTcgProc->FreshTcgBtnSts();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 客户机退出

void CZxutDlg::OnBnClickedBtnClientExit(void)
{
	m_pApp->m_nAppExitCmd = APP_EXIT_CMD_EXIT;
	OnCancel();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 客户机重启

void CZxutDlg::OnBnClickedBtnClientReboot(void)
{
	m_pApp->m_nAppExitCmd = APP_EXIT_CMD_REBOOT;
	OnCancel();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 客户机关机

void CZxutDlg::OnBnClickedBtnClientHalt(void)
{
	m_pApp->m_nAppExitCmd = APP_EXIT_CMD_HALT;
	OnCancel();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 切换属性页

void CZxutDlg::OnTcnSelchangeTabZxut(NMHDR *pNMHDR, LRESULT *pResult)
{
	int CurSel = m_tabZxut.GetCurSel();
	switch(CurSel)
	{
		case TAB_FLAW_PARAM:	// 探伤参数
			m_dlgFlawParam.ShowWindow(TRUE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_FLAW_GATE:		// 探伤闸门
			m_dlgFlawGate.m_dlgFlawGateAdj.FreshFlawGate();	// 仅在此处更新闸门参数(高效)

			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(TRUE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_DIG_IN:		// 数字输入
			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(TRUE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_DIG_OUT:		// 数字输出
			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(TRUE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_ENC_MODU:		// 编码器
			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(TRUE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}

			break;

		case TAB_TCG_PROC:		// TCG处理
			m_dlgTcgProc.FreshTcgBtnSts();	// 更新TCG按钮状态
			m_dlgTcgProc.FreshTcgTp();	// 仅在此处更新TCG参数(高效)

			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(TRUE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_SYS_SETTING:	// 系统设置
			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(TRUE);
			m_dlgFftProc.ShowWindow(FALSE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_FFT_PROC:		// FFT处理
			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(TRUE);
			if (m_pApp->m_bDevUpdEnb)
			{
				m_dlgDevUpd.ShowWindow(FALSE);
			}
			break;

		case TAB_DEV_UPD:		// 设备更新
			m_dlgFlawParam.ShowWindow(FALSE);
			m_dlgFlawGate.ShowWindow(FALSE);
			m_dlgDigIn.ShowWindow(FALSE);
			m_dlgDigOut.ShowWindow(FALSE);
			m_dlgEncModu.ShowWindow(FALSE);
			m_dlgTcgProc.ShowWindow(FALSE);
			m_dlgSysSetting.ShowWindow(FALSE);
			m_dlgFftProc.ShowWindow(FALSE);
			m_dlgDevUpd.ShowWindow(TRUE);
			break;

		default: ;
	}

	*pResult = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 快捷键帮助
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnBnClickedBtnKeyHlp(void)
{
	CDlgKeyHlp dlg;
	dlg.DoModal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 波形导出
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnBnClickedBtnWaveExport(void)
{
	m_pApp->ExportWaveData();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 定时器显示软件运行时间
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (m_pApp->m_bSmplEnb)
	{
		CString str;
		str.Format("%02d:%02d:%02d",
			((m_nTimeCntr / 60) / 60),	// h
			((m_nTimeCntr / 60) % 60),	// m
			(m_nTimeCntr % 60));		// s
		m_txtRunTime.SetWindowText(str);
		m_nTimeCntr++;
	}
	else
	{
		m_nTimeCntr = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 关闭对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnCancel(void)
{
/*	if (m_pApp->m_bSmplEnb)
	{
		m_pApp->SetSmplEnb();
	}

	m_pApp->KillDataProcThrd();	// 在退出对话框之前关闭所有派生线程*/

	CDialog::OnCancel();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 关于本软件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnBnClickedBtnAbout(void)
{
	CDlgAbout dlg;
	dlg.DoModal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 避免回车后响应OnOK()
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnOK(void)
{
	CString str;
	U32& rt_mem_time = m_pApp->m_stFlawParam.m_nRtMemTime;
	if (GetFocus() == &m_edtRtMem)
	{
		m_edtRtMem.GetWindowText(str);
		U32 tmp = _ttoi(str);
		if (tmp == 0)
		{
			m_pApp->DispMsg(ZXUT_MSG_ERR, "实时存储时间非零");
			str.Format("%d", rt_mem_time);
			m_edtRtMem.SetWindowText(str);
		}
		else if (tmp > MAX_RT_MEM_TIME)
		{
			m_pApp->DispMsg(ZXUT_MSG_ERR, "实时存储时间%d秒超出%d秒限制", tmp, MAX_RT_MEM_TIME);
			str.Format("%d", rt_mem_time);
			m_edtRtMem.SetWindowText(str);
		}
		else
		{
			rt_mem_time = tmp;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 实时存储使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutDlg::OnBnClickedChkRtMem(void)
{
	BOOL rt_mem_enb = m_chkRtMem.GetCheck();	// 使能
	U32 rt_mem_time = m_pApp->m_stFlawParam.m_nRtMemTime;	// 时间
	U32 rt_mem_times;
	U64 rt_mem_file_size;	// 文件大小
	ET_ZRC ret_code = ZXUT_InitRtMem(m_pApp->m_nHardNum, m_pApp->m_nSoftNum, rt_mem_enb, rt_mem_time, "RtMem.mm", &rt_mem_times, &rt_mem_file_size);
	if (rt_mem_enb == FALSE)
	{
		return;	// 关闭实时存储
	}

	#define KILO_BYTE	1024
	#define MEGA_BYTE	(KILO_BYTE * KILO_BYTE)

	CString str1, str2, tmp_str;

	if (rt_mem_file_size >= MEGA_BYTE)
	{
		if ((rt_mem_file_size % MEGA_BYTE) == 0)
		{
			str1.Format("%lldMB\n(%lld)", rt_mem_file_size / MEGA_BYTE, rt_mem_file_size);
		}
		else
		{
			str1.Format("%lld.%lldMB\n(%lld)", rt_mem_file_size / MEGA_BYTE, (rt_mem_file_size % MEGA_BYTE) / 1000, rt_mem_file_size);
		}
	}
	else if (rt_mem_file_size >= KILO_BYTE)
	{
		if ((rt_mem_file_size % KILO_BYTE) == 0)
		{
			str1.Format("%lldKB(%lld)", rt_mem_file_size / KILO_BYTE, rt_mem_file_size);
		}
		else
		{
			str1.Format("%lld.%lldKB\n(%lld)", rt_mem_file_size / KILO_BYTE, rt_mem_file_size % KILO_BYTE, rt_mem_file_size);
		}
	}
	else
	{
		str1.Format("%lld字节", rt_mem_file_size);
	}

	BOOL ret_ok = FALSE;
	switch (ret_code)
	{
		case ZRC_API_RET_SUCCESS:
			ret_ok = TRUE;
			str2.Format("正常");
			break;

		case ZRC_RT_CREATE_FILE_FAIL:
			str2.Format("创建实时存储文件失败");
			break;

		case ZRC_RT_CREATE_FILE_MAP_FAIL:
			str2.Format("创建实时存储文件映射失败");
			break;

		case ZRC_RT_NO_ENOUGH_MEM:
			str2.Format("实时存储内存不足");
			break;

		case ZRC_RT_MAP_FILE_VIEW_FAIL:
			str2.Format("映射实时存储文件视图失败");
			break;

		default:
			str2.Format("初始化实时存储出现未知错误%d\n", ret_code);
			break;
	}

	if (ret_ok)
	{
		m_pApp->m_bRtMemEnb = rt_mem_enb;
	}
	else
	{
		m_chkRtMem.SetCheck(FALSE);
	}

	m_pApp->DispMsg(ZXUT_MSG_INFO,
		"开启实时存储通道: %d-%d\n\n"
		"时长: %d秒\n"
		"次数: %d\n"
		"文件名称: RtMem.mm\n"
		"文件长度: %s\n\n"
		"状态: %s",
		m_pApp->m_nHardNum + 1, m_pApp->m_nSoftNum + 1,
		rt_mem_time, rt_mem_times, str1, str2
	);
}


void CZxutDlg::OnClose()
{
	TRACE("CDialog::OnClose()\n");

//	m_dlgSysSetting.GetNeedBrdNum();	// 避免用户输入后没有回车

	if (m_pApp->m_bSmplEnb)
	{
		TRACE("确保退出ZxutDlg时，关闭采样\n");
		OnBnClickedBtnSmplEnb();
	}

	m_pApp->KillDataShowThrd();	// 在退出对话框之前杀死数据显示线程

	CDialog::OnClose();
}
