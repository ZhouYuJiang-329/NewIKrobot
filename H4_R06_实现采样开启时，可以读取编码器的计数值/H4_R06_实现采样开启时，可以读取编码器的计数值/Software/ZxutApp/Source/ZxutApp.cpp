#include "stdafx.h"
#include "ZxutApp.h"
#include "ZxutDlg.h"
#include "SmplShow.h"
#include "FftShow.h"
#include "DlgBrdInfo.h"
#include "DlgWaitCnnct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CZxutApp, CWinAppEx)
	ON_COMMAND(IDK_CHAN_INC, &CZxutApp::OnChanInc)
	ON_COMMAND(IDK_CHAN_DEC, &CZxutApp::OnChanDec)

	ON_COMMAND(IDK_GAIN_INC_COARSE, &CZxutApp::OnGainIncCoarse)
	ON_COMMAND(IDK_GAIN_DEC_COARSE, &CZxutApp::OnGainDecCoarse)
	ON_COMMAND(IDK_AUTO_GAIN, &CZxutApp::OnAutoGain)
	ON_COMMAND(IDK_GAIN_DEC_FINE, &CZxutApp::OnGainDecFine)
	ON_COMMAND(IDK_GAIN_INC_FINE, &CZxutApp::OnGainIncFine)

	ON_COMMAND(IDK_FREQ_REF_LINE_DEC_COARSE, &CZxutApp::OnFreqRefLineDecCoarse)
	ON_COMMAND(IDK_FREQ_REF_LINE_DEC_FINE, &CZxutApp::OnFreqRefLineDecFine)
	ON_COMMAND(IDK_FREQ_REF_LINE_INC_COARSE, &CZxutApp::OnFreqRefLineIncCoarse)
	ON_COMMAND(IDK_FREQ_REF_LINE_INC_FINE, &CZxutApp::OnFreqRefLineIncFine)

	ON_COMMAND(IDK_ORIG_DLY_INC_CORSE, &CZxutApp::OnOrigDlyIncCorse)
	ON_COMMAND(IDK_ORIG_DLY_INC_FINE, &CZxutApp::OnOrigDlyIncFine)
	ON_COMMAND(IDK_ORIG_DLY_DEC_CORSE, &CZxutApp::OnOrigDlyDecCorse)
	ON_COMMAND(IDK_ORIG_DLY_DEC_FINE, &CZxutApp::OnOrigDlyDecFine)

	////////////////////////////////////////////////////////////////////////////////////////////////

	ON_COMMAND(IDK_GA_START_DEC_FINE, &CZxutApp::OnGaStartDecFine)
	ON_COMMAND(IDK_GA_START_DEC_COARSE, &CZxutApp::OnGaStartDecCoarse)
	ON_COMMAND(IDK_GA_START_INC_FINE, &CZxutApp::OnGaStartIncFine)
	ON_COMMAND(IDK_GA_START_INC_COARSE, &CZxutApp::OnGaStartIncCoarse)

	ON_COMMAND(IDK_GB_START_DEC_FINE, &CZxutApp::OnGbStartDecFine)
	ON_COMMAND(IDK_GB_START_DEC_COARSE, &CZxutApp::OnGbStartDecCoarse)
	ON_COMMAND(IDK_GB_START_INC_FINE, &CZxutApp::OnGbStartIncFine)
	ON_COMMAND(IDK_GB_START_INC_COARSE, &CZxutApp::OnGbStartIncCoarse)

	ON_COMMAND(IDK_GC_START_DEC_FINE, &CZxutApp::OnGcStartDecFine)
	ON_COMMAND(IDK_GC_START_DEC_COARSE, &CZxutApp::OnGcStartDecCoarse)
	ON_COMMAND(IDK_GC_START_INC_FINE, &CZxutApp::OnGcStartIncFine)
	ON_COMMAND(IDK_GC_START_INC_COARSE, &CZxutApp::OnGcStartIncCoarse)

	ON_COMMAND(IDK_GI_START_DEC_FINE, &CZxutApp::OnGiStartDecFine)
	ON_COMMAND(IDK_GI_START_DEC_COARSE, &CZxutApp::OnGiStartDecCoarse)
	ON_COMMAND(IDK_GI_START_INC_FINE, &CZxutApp::OnGiStartIncFine)
	ON_COMMAND(IDK_GI_START_INC_COARSE, &CZxutApp::OnGiStartIncCoarse)

	////////////////////////////////////////////////////////////////////////////////////////////////

	ON_COMMAND(IDK_GA_WIDTH_DEC_FINE, &CZxutApp::OnGaWidthDecFine)
	ON_COMMAND(IDK_GA_WIDTH_DEC_COARSE, &CZxutApp::OnGaWidthDecCoarse)
	ON_COMMAND(IDK_GA_WIDTH_INC_FINE, &CZxutApp::OnGaWidthIncFine)
	ON_COMMAND(IDK_GA_WIDTH_INC_COARSE, &CZxutApp::OnGaWidthIncCoarse)

	ON_COMMAND(IDK_GB_WIDTH_DEC_FINE, &CZxutApp::OnGbWidthDecFine)
	ON_COMMAND(IDK_GB_WIDTH_DEC_COARSE, &CZxutApp::OnGbWidthDecCoarse)
	ON_COMMAND(IDK_GB_WIDTH_INC_FINE, &CZxutApp::OnGbWidthIncFine)
	ON_COMMAND(IDK_GB_WIDTH_INC_COARSE, &CZxutApp::OnGbWidthIncCoarse)

	ON_COMMAND(IDK_GC_WIDTH_DEC_FINE, &CZxutApp::OnGcWidthDecFine)
	ON_COMMAND(IDK_GC_WIDTH_DEC_COARSE, &CZxutApp::OnGcWidthDecCoarse)
	ON_COMMAND(IDK_GC_WIDTH_INC_FINE, &CZxutApp::OnGcWidthIncFine)
	ON_COMMAND(IDK_GC_WIDTH_INC_COARSE, &CZxutApp::OnGcWidthIncCoarse)

	ON_COMMAND(IDK_GI_WIDTH_DEC_FINE, &CZxutApp::OnGiWidthDecFine)
	ON_COMMAND(IDK_GI_WIDTH_DEC_COARSE, &CZxutApp::OnGiWidthDecCoarse)
	ON_COMMAND(IDK_GI_WIDTH_INC_FINE, &CZxutApp::OnGiWidthIncFine)
	ON_COMMAND(IDK_GI_WIDTH_INC_COARSE, &CZxutApp::OnGiWidthIncCoarse)

	////////////////////////////////////////////////////////////////////////////////////////////////

	ON_COMMAND(IDK_GA_HEIGHT_DEC_FINE, &CZxutApp::OnGaHeightDecFine)
	ON_COMMAND(IDK_GA_HEIGHT_DEC_COARSE, &CZxutApp::OnGaHeightDecCoarse)
	ON_COMMAND(IDK_GA_HEIGHT_INC_FINE, &CZxutApp::OnGaHeightIncFine)
	ON_COMMAND(IDK_GA_HEIGHT_INC_COARSE, &CZxutApp::OnGaHeightIncCoarse)

	ON_COMMAND(IDK_GB_HEIGHT_DEC_FINE, &CZxutApp::OnGbHeightDecFine)
	ON_COMMAND(IDK_GB_HEIGHT_DEC_COARSE, &CZxutApp::OnGbHeightDecCoarse)
	ON_COMMAND(IDK_GB_HEIGHT_INC_FINE, &CZxutApp::OnGbHeightIncFine)
	ON_COMMAND(IDK_GB_HEIGHT_INC_COARSE, &CZxutApp::OnGbHeightIncCoarse)

	ON_COMMAND(IDK_GC_HEIGHT_DEC_FINE, &CZxutApp::OnGcHeightDecFine)
	ON_COMMAND(IDK_GC_HEIGHT_DEC_COARSE, &CZxutApp::OnGcHeightDecCoarse)
	ON_COMMAND(IDK_GC_HEIGHT_INC_FINE, &CZxutApp::OnGcHeightIncFine)
	ON_COMMAND(IDK_GC_HEIGHT_INC_COARSE, &CZxutApp::OnGcHeightIncCoarse)

	ON_COMMAND(IDK_GI_HEIGHT_DEC_FINE, &CZxutApp::OnGiHeightDecFine)
	ON_COMMAND(IDK_GI_HEIGHT_DEC_COARSE, &CZxutApp::OnGiHeightDecCoarse)
	ON_COMMAND(IDK_GI_HEIGHT_INC_FINE, &CZxutApp::OnGiHeightIncFine)
	ON_COMMAND(IDK_GI_HEIGHT_INC_COARSE, &CZxutApp::OnGiHeightIncCoarse)
	ON_COMMAND(IDK_GB_ENB, &CZxutApp::OnGbEnb)
	ON_COMMAND(IDK_GC_ENB, &CZxutApp::OnGcEnb)
	ON_COMMAND(IDK_GI_ENB, &CZxutApp::OnGiEnb)
END_MESSAGE_MAP()

CZxutApp theApp;	// 唯一的一个CZxutApp对象

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 构造函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CZxutApp::CZxutApp(void)
{
	m_nHardNum = 0;
	m_nSoftNum = 0;

	m_pDataProcThrd = NULL;

	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
//		m_pDataProcThrd[i] = NULL;
		m_fCpuTempValue[i] = 0.0f;
		m_fPcbTempValue[i] = 0.0f;
	}

	m_bAutoGain = FALSE;

	m_pDlgZxut = NULL;
	m_pDlgFlawParam = NULL;

	m_bScanFreq = FALSE;	// 关闭扫频功能
	m_fpFreqBand = NULL;

	m_bLockBw = FALSE;	// 尚未锁定频带

	m_nAppExitCmd = APP_EXIT_CMD_RETRY;

	m_bDataProc = FALSE;

	m_fGateDfctXInfo = 0.0f;
	m_fGateBttmXInfo = 0.0f;

	ZXUT_FftInit(FFT_IN_DOTS);

	////////////////////////////////////////////////////////////////////////////////////////////////

	m_nTotBrd = 0;
	m_bIsClientCnncted = FALSE;	// 没有客户机连接
	m_bDlgWaitOk = FALSE;

	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
		m_sockZxut[i] = 0;
	}

	m_bRtMemEnb = FALSE;	// 禁止实时存储

#ifdef WIN_X64
#ifdef _DEBUG
	strcpy(m_strSoftPlat, "64位调试版");
#else
	strcpy(m_strSoftPlat, "64位发布版");
#endif
#else
#ifdef _DEBUG
	strcpy(m_strSoftPlat, "32位调试版");
#else
	strcpy(m_strSoftPlat, "32位发布版");
#endif
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 析构函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CZxutApp::~CZxutApp(void)
{
	if (m_pSmplShow != NULL)
	{
		delete m_pSmplShow;
	}

	if (m_pFftShow != NULL)
	{
		delete m_pFftShow;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 实例初始化
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutApp::InitInstance(void)
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	InitCommonControls();
	CWinAppEx::InitInstance();
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	// 套接字初始化
	if (AfxSocketInit() == FALSE)
	{
		DispMsg(ZXUT_MSG_ERR, "初始化套接字失败");
		return FALSE;
	}

	RdFlawParam();	// 读探伤参数

	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
		for (U8 j = 0; j < MAX_HARD_NUM; j++)
		{
			U8 hard_num = i * MAX_HARD_NUM + j;
			for (U8 k = 0; k < MAX_SOFT_NUM; k++)
			{
				m_stFlawParam.m_abTraceEnb[hard_num][k] = FALSE;			// 启动后，强制禁止界面波跟踪
				m_stFlawParam.m_stTcgParam[hard_num][k].tp_bTcgEnb = FALSE;	// 启动后，强制禁止TCG使能
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 避免两次打开应用软件

	m_bAppOpenMutex = FALSE;
	m_hAppOpenMutex = ::CreateMutex(NULL, TRUE, "ZXUT");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		DispMsg(ZXUT_MSG_WARNING, "应用软件已经打开!");
		m_bAppOpenMutex = TRUE;
		return FALSE;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取产品信息

	char strExeName[100];
	strcpy_s(strExeName, ((CZxutApp*)AfxGetApp())->m_pszExeName);
	strcat_s(strExeName, ".exe");
	GetFileInfo(strExeName, m_strAppName, m_strAppVer);		// 获取产品信息

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 频带分析准备工作

	m_fpFreqBand = fopen("频带分析.txt", "wt");
	if (m_fpFreqBand == NULL)
	{
		DispMsg(ZXUT_MSG_ERR, "不能打开写文件“频带分析.txt”！");
		return FALSE;
	}

	fprintf(m_fpFreqBand, "%8s %8s %8s %8s %8s %8s\n",
		"频带", "左-3dB", "中心频率", "右-3dB", "最大频率", "当前增益");

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 初始化探伤设备

	if (InitDevice() == FALSE)
	{
		return FALSE;
	}

	GenSmplDepthMenu();	// 生成采样深度菜单

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 显示对话框，进入对话框处理

	m_hSmplShowWnd = NULL;
	m_pSmplShow = new CSmplShow;

	m_hFftShowWnd = NULL;
	m_pFftShow = new CFftShow;

	m_hAcc = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));	// 加载“快捷键”资源

	CZxutDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化探伤设备
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutApp::InitDevice(void)
{
	// [1] 打开探伤设备
	if (OpenDevice() == FALSE)
	{
		return FALSE;
	}

	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	ZXUT_SetCoreParamPtr(&core_param);	// [2] 设置核心参数指针

	SetDiParam();	// [3] 设置DI参数
	SetDoParam();	// [4] 设置DO参数
	SetEncParam();	// [5] 设置ENC参数
	SetFlawParam();	// [6] 设置探伤参数

	// [7] 设置重复频率
	ZXUT_SetRptFreq(core_param.m_nRptFreq, NULL, NULL);
	UpdSysTiming();	// 更新系统时序

	CreateLogChanTab();		// [8] 创建逻辑通道表
	CreateDataProcThrd();	// [9] 创建数据处理线程
	CreateDataShowThrd();	// 创建数据显示线程

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 生成采样深度菜单(动态)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::GenSmplDepthMenu(void)
{
	if (m_bPci)
	{
		m_nSmplDepthNum = 1;	// 1K
		for (U8 i = 0; i < m_nSmplDepthNum; i++)
		{
			m_anSmplDepthValue[i] = (i + 1) * 1024;
			sprintf(m_asSmplDepthStr[i], "%dK", (i + 1));
		}
		m_nSmplDepthMax = 1536;	// 1.5K
	}
	else
	{
		m_nSmplDepthNum = 32;	// 1K, 2K, 3K, ..., 32K
		for (U8 i = 0; i < m_nSmplDepthNum; i++)
		{
			m_anSmplDepthValue[i] = (i + 1) * 1024;
			sprintf(m_asSmplDepthStr[i], "%dK", (i + 1));
		}

		m_nSmplDepthMax = SMPL_DEPTH_MAX;
		m_anSmplDepthValue[m_nSmplDepthNum - 1] = m_nSmplDepthMax;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 获取产品信息
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::GetFileInfo(const char* strFile, CString& strName, CString& strVer)
{
	char FileVerInfo[4096];
	DWORD dwVerLen = 0;
	UINT cbTranslate;
	char SubBlock[4096];
	UINT dwBytes;

	struct LANGANDCODEPAGE
	{
		WORD wLanguage;
		WORD wCodePage;
	}*lpTranslate;

	int m_len = GetFileVersionInfoSize(strFile, &dwVerLen);
	BOOL m_bFile = GetFileVersionInfo(strFile, NULL, m_len, FileVerInfo);
	if ((m_len == 0) || (m_bFile == FALSE))
	{
		strName = "";
		strVer = "";
		return;
	}

	VerQueryValue(FileVerInfo,
		TEXT("\\VarFileInfo\\Translation"),
		(LPVOID*)&lpTranslate,
		&cbTranslate);

	char* pVerValue = NULL;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取名称

	wsprintf(SubBlock,
		TEXT("\\StringFileInfo\\%04x%04x\\ProductName"),
		lpTranslate[0].wLanguage,
		lpTranslate[0].wCodePage);

	VerQueryValue(FileVerInfo,
		SubBlock,
		(LPVOID*)&pVerValue,
		&dwBytes);

	strName.Format("%s", pVerValue);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取版本

	wsprintf(SubBlock,
		TEXT("\\StringFileInfo\\%04x%04x\\ProductVersion"),
		lpTranslate[0].wLanguage,
		lpTranslate[0].wCodePage);

	VerQueryValue(FileVerInfo,
		SubBlock,
		(LPVOID*)&pVerValue,
		&dwBytes);

	U32 v1, v2, v3, v4;
	sscanf(pVerValue, "%d.%d.%d.%d", &v1, &v2, &v3, &v4);
	strVer.Format("v%d.%d", v2, v4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 创建数据处理线程
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::CreateDataProcThrd(void)
{
//	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		m_pDataProcThrd/*[i]*/ = new CDataProcThrd/*(i)*/;
		if (m_pDataProcThrd/*[i]*/)
		{
			m_pDataProcThrd/*[i]*/->Start((LPVOID)this, THREAD_PRIORITY_ABOVE_NORMAL);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 杀死数据处理线程
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::KillDataProcThrd(void)
{
//	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		if (m_pDataProcThrd/*[i]*/)
		{
			m_pDataProcThrd/*[i]*/->/*Force*/Kill();
			delete m_pDataProcThrd/*[i]*/;
			m_pDataProcThrd/*[i]*/ = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建/杀死数据显示线程
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::CreateDataShowThrd(void)
{
	m_pDataShowThrd = new CDataShowThrd;
	if (m_pDataShowThrd)
	{
		m_pDataShowThrd->Start((LPVOID)this, THREAD_PRIORITY_ABOVE_NORMAL);
	}
}

void CZxutApp::KillDataShowThrd(void)
{
	if (m_pDataShowThrd)
	{
		m_pDataShowThrd->Kill();
		delete m_pDataShowThrd;
		m_pDataShowThrd = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置当前通道
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SetCrrntChan(void)
{
	U8 log_idx = m_stLogChan.m_nLogIdx;
	m_nHardNum = m_stLogChan.m_nLogHard[log_idx];	// 逻辑通道的硬编号
	m_nSoftNum = m_stLogChan.m_nLogSoft[log_idx];	// 逻辑通道的软编号
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 退出应用程序
//
////////////////////////////////////////////////////////////////////////////////////////////////////

int CZxutApp::ExitInstance(void)
{
	if (m_fpFreqBand != NULL)
	{
		fclose(m_fpFreqBand);	// 关闭频带分析文件
	}

	WrFlawParam();	// 写探伤参数

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 关闭"应用程序开启互斥器"

	if (m_hAppOpenMutex)
	{
		CloseHandle(m_hAppOpenMutex);

		if (m_bAppOpenMutex == TRUE)
		{
			return CWinApp::ExitInstance();
		}
	}

	KillDataProcThrd();	// 杀死数据处理线程

	ZXUT_CloseDevice(m_nAppExitCmd);	// 关闭探伤设备

	if (m_bNet)
	{
		for (U8 i = 0; i < m_nTotBrd; i++)
		{
			if (m_sockZxut[i] != 0)
			{
				closesocket(m_sockZxut[i]);
				m_sockZxut[i] = 0;
			}
		}
	}
	return CWinApp::ExitInstance();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示信息 - 依据字符串
//
////////////////////////////////////////////////////////////////////////////////////////////////////

S32 CZxutApp::DispMsg(U8 nMsgType, const char *fmt, ...)
{
	char strMsg[10240];
	va_list ap;
	va_start(ap, fmt);
	vsprintf_s(strMsg, fmt, ap);
	va_end(ap);

	Beep(1000, 100);	// 喇叭响一下

	CString strCaption;
	switch (nMsgType)
	{
	case ZXUT_MSG_ASK:
		strCaption = "询问信息";
		MessageBeep(MB_ICONWARNING);
		return ::MessageBox(NULL, strMsg, strCaption,
			MB_YESNO | MB_ICONQUESTION | MB_TOPMOST | MB_TASKMODAL);

	case ZXUT_MSG_ERR:
		strCaption = "错误信息";
		return ::MessageBox(NULL, strMsg, strCaption,
			MB_OK | MB_ICONERROR | MB_TOPMOST | MB_TASKMODAL);

	case ZXUT_MSG_WARNING:
		strCaption = "警告信息";
		return ::MessageBox(NULL, strMsg, strCaption,
			MB_OK | MB_ICONWARNING | MB_TOPMOST | MB_TASKMODAL);

	case ZXUT_MSG_INFO:
		strCaption = "提示信息";
		return ::MessageBox(NULL, strMsg, strCaption,
			MB_OK | MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);

	default:
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 数据处理线程
//
////////////////////////////////////////////////////////////////////////////////////////////////////

F32 avg_cpu_temp = 0.0, avg_pcb_temp = 0.0;

void CZxutApp::ThrdDataProcHandler(void/*const U8 nBrdNum*/)
{
	U32 m, rq_len[MAX_BRD_NUM], now;
	U8 rq_full_flg;

	// 从环形队列获取数据
	for (m = 0; m < m_nTotBrd; m++)
	{
		rq_len[m] = ZXUT_GetRqNum(m, &rq_full_flg);
		if (rq_full_flg)
		{
			TRACE("*** ERROR: ring_queue is full! ***\n");
			return;
		}

		now = rq_len[m];
		if (now == 0)
		{
			continue;	// 该板卡无数据可读，进入下块板卡继续
		}

		now = (now > LMT_RQ_NUM) ? LMT_RQ_NUM : now;
		rq_len[m] = now;
		ZXUT_GetRqData(m, now, m_stRqData[m]);
		m_bRqDataUpd[m] = TRUE;

		if (m == m_nHardNum / m_pstExpInfo->m_nTotHard)
		{
//			memcpy(&m_stRqShow, &m_stRqData[m][0], sizeof ST_RQ_DATA);			// 取当前通道对应板卡的第一个环形队列数据用于显示
			memcpy(&m_stRqShow, &m_stRqData[m][now - 1], sizeof ST_RQ_DATA);	// 取当前通道对应板卡的最末个环形队列数据用于显示
		}

//		m_fPcbTempValue[m] = ZXUT_TransPcbTempValue(m_stRqData[m][now - 1].rd_nTempPcbInner);
//		m_fFpgaTempValue[m] = m_bPci ? 0.0f : ZXUT_TransFpgaTempValue(m_stRqData[m][now - 1].rd_nTempFpga);
		m_fPcbTempValue[m] = ZXUT_TransPcbTempValue(m_stRqData[m][now - 1].rd_nTempPcb);
		m_fCpuTempValue[m] = m_bPci ? 0.0f : ZXUT_TransFpgaTempValue(m_stRqData[m][now - 1].rd_nTempFpga);
	}

	Sleep(50);	// 交出CPU控制权，执行别的任务

/*	ST_RQ_DATA& daq_buf = *(m_pstExpInfo->m_apstDaqBuf[nBrdNum]);

	m_fCpuTempValue[nBrdNum] = daq_buf.m_fCpuTemp;
	m_fPcbTempValue[nBrdNum] = daq_buf.m_fPcbTemp;

	if ((nBrdNum != m_nHardNum / m_pstExpInfo->m_nTotHard)	// 若不是当前通道对应的板卡
		|| (m_bDataProc == TRUE))				// 当前通道正在被显示
	{
		return;
	}

	m_bDataProc = TRUE;	// 数据处理开始

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 更新显示数据

	CString str;

	// 仅取第0次累积的数据
	U8 hard_num = m_nHardNum - nBrdNum * m_pstExpInfo->m_nTotHard;
	//	ST_DAQ_DATA& acc_buf = daq_buf.m_stAccData[0][hard_num][m_nSoftNum];	// 取最开始的累积数据
	ST_DAQ_DATA& acc_buf = daq_buf.m_stAccData[daq_buf.m_xAccTimes - 1][hard_num][m_nSoftNum];	// 取最后的累积数据

	// 波形显示
	U32 byte_len = sizeof(U16) * acc_buf.m_nSmplDepth;
	memcpy((U8*)m_anSmplBuf, (U8*)acc_buf.m_anSmplWave, byte_len);

	memcpy((U8*)m_nEabCntr, (U8*)acc_buf.m_anEabCntr, sizeof(m_nEabCntr));
	memcpy((U8*)m_nEzCntr, (U8*)acc_buf.m_anEzCntr, sizeof(m_nEzCntr));

	if (m_pDlgEncModu->GetSafeHwnd())
		m_pDlgEncModu->UpdEncCntr(m_nEabCntr, m_nEzCntr);		// 更新编码器
	m_pDlgEncModu->UpdEncMeasRes(daq_buf);	// 更新编码器测量结果

	m_pDlgSysSetting->UpdTempValue(nBrdNum);	// 更新温度值
	m_pDlgDigIn->UpdDigIn(daq_buf.m_nDigIn);	// 更新数字输入

	U32 dword_size = (daq_buf.m_nTotSmplSize - ADD_INFO_LEN) / 4;
	m_pSmplShow->ShowSmplView(m_anSmplBuf, daq_buf.m_nDigIn,
		m_fAvgCpuTemp, m_fAvgPcbTemp,
		m_nEabCntr, dword_size,
		acc_buf.m_nSmplDepth,
		acc_buf.m_bSmplWavEnb,
		m_stFlawParam.m_anDbNum[m_nHardNum][m_nSoftNum],
		acc_buf.m_astGateRes);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 自动增益及包络

	if (acc_buf.m_bSmplWavEnb == TRUE)
	{
		ProcAutoGain();	// 处理自动增益

		// 处理包络
		if (m_bEnvlpEnb == TRUE)
		{
			for (U32 i = 0; i < acc_buf.m_nSmplDepth; i++)
			{
				if (m_anSmplBuf[i] > m_anEnvlpBuf[i])
					m_anEnvlpBuf[i] = m_anSmplBuf[i];
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门判伤结果

	memcpy(&m_stGateRes[GATE_SEL_A], &acc_buf.m_astGateRes[GATE_SEL_A], sizeof(m_stGateRes));
	for (U8 i = 0; i < TOT_GATE_NUM; i++)
	{
		if (m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_bEnb[i])
		{
			m_pDlgFlawGate->UpdGateRes(i);
		}
	}
	m_pDlgFlawParam->UpdSpDiff();

	if (m_stGateRes[GATE_SEL_A].m_fPeak == 1)
	{
		m_pDlgZxut->m_ledOverHeight.SetState(LED_ON);
	}
	else
	{
		m_pDlgZxut->m_ledOverHeight.SetState(LED_OFF);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门跟踪

	if (acc_buf.m_bGateNeedUpd)	// 若闸门需要更新
	{
		ST_GATE_PARAM& gate_param = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum];
		for (U8 i = 0; i < TOT_GATE_NUM - 1; i++)
		{
			if (gate_param.m_bEnb[i])	// 若闸门使能
			{
				gate_param.m_nStart[i] = acc_buf.m_anGateStart[i];	// 更新ABC闸门
			}
		}
	}

	ProcFftData(acc_buf);	// 处理FFT数据

	m_bDataProc = FALSE;	// 数据处理结束*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 数据显示线程

void CZxutApp::ThrdDataShowHandler(void)
{
	U8 m = m_nHardNum / m_pstExpInfo->m_nTotHard;
//	U8 chan_num = m_nChanNum % m_nTotChan;

	if (m_bRqDataUpd[m] == FALSE)
	{
		return;	// 环形队列未更新，退出
	}

	ST_RQ_DATA& rq_data = m_stRqShow;
//	ST_DAQ_DATA& daq_data = *(rq_data.rd_pstDaqData + chan_num);
	ST_DAQ_DATA& daq_data = rq_data.rd_pstDaqData[m][m_nHardNum][m_nSoftNum];

	m_pSmplShow->ShowSmplView(rq_data);	// 波形显示

	if (m_pDlgEncModu->GetSafeHwnd())
		m_pDlgEncModu->UpdEncCntr(daq_data.dd_anEabCntr, daq_data.dd_anEzCntr);		// 更新编码器

//	m_pDlgSysSetting->UpdTempValue(m);			// 更新内部温度值
//	m_pDlgZxut->UpdTempOuter(rq_data);			// 更新外部温度值

	////////////////////////////////////////////////////////////////////////////////////////
	// 自动增益及包络

/*	if (daq_data.dd_bSmplWavEnb)
	{
		ProcAutoGain(daq_data.dd_astGateRes[GATE_SEL_A]);	// 处理自动增益

		// 处理包络
		if (m_bEnvlpEnb)
		{
			for (U32 i = 0; i < daq_data.dd_nSmplDepth; i++)
			{
				if (daq_data.dd_pnSmplWave[i] > m_pnEnvlpBuf[i])
					m_pnEnvlpBuf[i] = daq_data.dd_pnSmplWave[i];
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门判伤结果

	ST_GATE_RES& gate_res = daq_data.dd_astGateRes[GATE_SEL_A];
	for (U8 i = 0; i < TOT_GATE_NUM; i++)
	{
		if (m_stFlawParam.m_astGateParam[m_nChanNum].m_bEnb[i])
		{
			m_pDlgFlawGate->UpdGateRes(i, daq_data);
		}
	}
	m_pDlgZxut->UpdSpDiff();

	if (gate_res.gr_fPeak == 1)
	{
		m_pDlgZxut->m_ledOverHeight.SetState(LED_ON);
	}
	else
	{
		m_pDlgZxut->m_ledOverHeight.SetState(LED_OFF);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门跟踪

	if (daq_data.dd_bGateNeedUpd)	// 若闸门需要更新
	{
		ST_GATE_PARAM& gate_param = m_stFlawParam.m_astGateParam[m_nChanNum];
		for (U8 i = 0; i < TOT_GATE_NUM - 1; i++)
		{
			if (gate_param.m_bEnb[i])	// 若闸门使能
			{
				gate_param.m_nStart[i] = daq_data.dd_anGateStart[i];	// 更新ABC闸门
			}
		}
	}

	if (m_bFftProc)
	{
		ProcFftData(daq_data);	// 处理FFT数据
	}*/

	m_bRqDataUpd[m] = FALSE;	// 环形队列更新的数据已显示完毕
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 处理FFT数据
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::ProcFftData(ST_DAQ_DATA& acc_buf)
{
	U32 fft_freq_index_left;	// 左-6dB点
	U32 fft_freq_index_max;		// 最大值点
	U32 fft_freq_index_right;	// 右-6dB点

	U32 mag[FFT_OUT_DOTS];
	U8 y_bw = m_pstExpInfo->m_nYBw;
	CString str;
	U32 maxValue = 0;

	U16 freq_ratio = m_stFlawParam.m_stCoreParam.m_anFreqRatio[m_nHardNum][m_nSoftNum];
	BOOL fft_wave_enb = m_stFlawParam.m_stCoreParam.m_abFftWave[m_nHardNum][m_nSoftNum];
	BOOL cent_freq_enb = m_stFlawParam.m_stCoreParam.m_abCentFreq[m_nHardNum][m_nSoftNum];
	if (m_bPci && (fft_wave_enb || cent_freq_enb))
	{
		ST_GATE_PARAM& gate_param = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum];
		U8 fft_gate = m_stFlawParam.m_anFftGate[m_nHardNum][m_nSoftNum];
		U16 gate_start = gate_param.m_nStart[fft_gate];
		U16 gate_width = gate_param.m_nWidth[fft_gate];

		for (S32 i = 0; i < FFT_IN_DOTS; i++)
		{
			if ((i < gate_start) || (i >= gate_start + gate_width))
			{
				m_astFftData[i].real = 1 << (y_bw - 1);
			}
			else
			{
				m_astFftData[i].real = acc_buf.dd_pnSmplWave[i];
			}
			m_astFftData[i].image = 0;
		}

		ZXUT_FftExec(m_astFftData);	// CPU进行快速福利叶变换

		for (S32 i = 0; i < FFT_OUT_DOTS; i++)
		{
			F64 real = m_astFftData[i].real;
			F64 image = m_astFftData[i].image;
			mag[i] = (i == 0) ? 0 : (U32)sqrt(real * real + image * image);
		}

		// CPU求最大频率
		fft_freq_index_max = 0;
		for (U32 i = 0; i < FFT_OUT_DOTS; i++)
		{
			if (mag[i] > maxValue)
			{
				fft_freq_index_max = i;
				maxValue = mag[i];
			}
		}

		// CPU获取左-6dB频点
		fft_freq_index_left = 0;
		for (int i = fft_freq_index_max - 1; i >= 1; i--)
		{
			if (mag[i] <= maxValue / 2)
			{
				fft_freq_index_left = i;
				break;
			}
		}

		// CPU获取右-6dB频点
		fft_freq_index_right = 0;
		for (int i = fft_freq_index_max + 1; i < FFT_OUT_DOTS; i++)
		{
			if (mag[i] <= maxValue / 2)
			{
				fft_freq_index_right = i;
				break;
			}
		}

		if ((fft_freq_index_max >= FFT_OUT_DOTS) ||
			(fft_freq_index_left >= FFT_OUT_DOTS) ||
			(fft_freq_index_right >= FFT_OUT_DOTS))
		{
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// FFT波形

	if (m_bPci ? fft_wave_enb : acc_buf.dd_bFftWaveEnb)
	{
		if (m_bNet && acc_buf.dd_bFftWaveEnb)
		{
			int real, imag;

			U32* fft_data = acc_buf.dd_anFftWave;
			for (int i = 0; i < FFT_OUT_DOTS; i++)
			{
				U32 x = (fft_data[i] >> (y_bw * 0)) & ((1 << y_bw) - 1);		// 12位
				U32 y = (fft_data[i] >> (y_bw * 1)) & ((1 << y_bw) - 1);		// 12位

				// FPGA已将输出转换为无符号数，现在只需转为有符号数
				real = x - (1 << (y_bw - 1));	// 2048
				imag = y - (1 << (y_bw - 1));	// 2048

				U32 square = real * real + imag * imag;
				mag[i] = (U32)sqrt(square * 1.0);	// 求模
			}

			// CPU求最大频率
			fft_freq_index_max = 0;
			for (U32 i = 0; i < FFT_OUT_DOTS; i++)
			{
				if (mag[i] > maxValue)
				{
					fft_freq_index_max = i;
					maxValue = mag[i];
				}
			}

			// FPGA求最大频率
			if (m_bNet && acc_buf.dd_bCentFreqEnb)
			{
				fft_freq_index_max = acc_buf.dd_nFftFreqIndexMax;
			}

			if (fft_freq_index_max >= FFT_OUT_DOTS)
			{
				return;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		// 构建FFT曲线

		F64 ratio = 180 * 0.8 / maxValue;
		for (int i = 0; i < FFT_OUT_DOTS; i++)
		{
			m_anFftCurve[i] = (U8)(mag[i] * ratio);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		// 更新最大频率

		F32 max_freq = ZXUT_GetFftFreq(fft_freq_index_max, freq_ratio);
		str.Format("%.2f", max_freq);
		m_pDlgFftProc->m_txtMaxFreq.SetWindowText(str);

		////////////////////////////////////////////////////////////////////////////////////////////
		// 显示FFT曲线

		m_anBwData[fft_freq_index_max] = m_stGateRes[GATE_SEL_A].gr_yPeak - (1 << (y_bw - 1));
		m_anBwCurve[fft_freq_index_max] = (U8)(m_anBwData[fft_freq_index_max] * 180 / (1 << (y_bw - 1)));
		if (m_bLockBw)
		{
			F32 a = (F32)m_anBwLockData[m_stFlawParam.m_nFreqRefLine];
			F32 b = (F32)m_nBwMaxData;
			F32 delta = (F32)(20.0 * log10(a / b));
			CString info;
			info.Format("%.1f", delta);
			m_pDlgFftProc->m_txtInstGain.SetWindowText(info);

			m_pFftShow->ShowFftView(m_anFftCurve, m_anBwCurve, m_nBwLeftIdx, m_nBwMaxIdx, m_nBwRightIdx, m_nBwMaxCurve, m_stFlawParam.m_nFreqRefLine);
		}
		else
		{
			m_pFftShow->ShowFftView(m_anFftCurve, m_anBwCurve, 0, 0, 0, 0, m_stFlawParam.m_nFreqRefLine);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 中心频率

	if (m_bPci ? cent_freq_enb : acc_buf.dd_bCentFreqEnb)
	{
		if (m_bNet && acc_buf.dd_bCentFreqEnb)
		{
			fft_freq_index_left = acc_buf.dd_nFftFreqIndexLeft;		// 获取左-6dB频点
			fft_freq_index_right = acc_buf.dd_nFftFreqIndexRight;	// 获取右-6dB频点
		}

		// 更新左-6dB频率
		F32 fft_freq_left = ZXUT_GetFftFreq(fft_freq_index_left, freq_ratio);
		str.Format("%.2f", fft_freq_left);
		m_pDlgFftProc->m_txtLeftFreq.SetWindowText(str);

		// 更新右-6dB频率
		F32 fft_freq_right = ZXUT_GetFftFreq(fft_freq_index_right, freq_ratio);
		str.Format("%.2f", fft_freq_right);
		m_pDlgFftProc->m_txtRightFreq.SetWindowText(str);

		// 更新中心频率
		F32 fft_cent_freq = (fft_freq_left + fft_freq_right) / 2;
		str.Format("%.2f", fft_cent_freq);
		m_pDlgFftProc->m_txtCentFreq.SetWindowText(str);

		// 更新BW
		F32 bw = fft_freq_right - fft_freq_left;
		str.Format("%.2f", bw);
		m_pDlgFftProc->m_txtBw.SetWindowText(str);

		// 更新相对BW
		U32 rbw = (U32)(bw / fft_cent_freq * 100);
		str.Format("%d", rbw);
		m_pDlgFftProc->m_txtRBw.SetWindowText(str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置采样使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SetSmplEnb(void)
{
	m_bSmplEnb = (m_bSmplEnb == FALSE) ? TRUE : FALSE;

	if (m_bSmplEnb == TRUE)
	{
		for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
		{
			m_bRqDataUpd[i] = FALSE;	// 环形队列未更新

			// 初始化4个编码器
			for (U8 j = 0; j < TOT_ENC_NUM; j++)
			{
				ZXUT_SetEabCntr(i, j, 0);
				ZXUT_SetEzCntr(i, j, 0);
			}
		}

		ClrFftRes();
	}

	m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
	ZXUT_SetSmplEnb(m_bSmplEnb);
	m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////

	if (m_bRtMemEnb)
	{
		FILE* fpSrc = fopen("RtMem.mm", "rb");
		FILE* fpDst = fopen("RtMem.txt", "wt");
		if ((fpSrc == NULL) || (fpDst == NULL))
		{
			return;
		}

		U16 smpl_depth = m_stFlawParam.m_stCoreParam.m_anSmplDepth[m_nHardNum][m_nSoftNum];
		fseek(fpSrc, -1 * 10 * smpl_depth * 2, SEEK_END);	// 从末尾往前回溯10次累积数据

		for (U32 i = 0; i < 10; i++)
		{
			for (U32 j = 0; j < smpl_depth; j++)
			{
				U16 tmp;
				fread(&tmp, 2, 1, fpSrc);
				fprintf(fpDst, "%d\n", tmp);
			}
		}

		fclose(fpSrc);
		fclose(fpDst);

		m_pDlgZxut->m_chkRtMem.SetCheck(FALSE);
		m_bRtMemEnb = FALSE;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::InitFlawParam(void)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;

	m_stFlawParam.m_nSigBeg = PARAM_SIG_BEG;
	m_stFlawParam.m_nSigEnd = PARAM_SIG_END;

	m_stFlawParam.m_nNeedBrdNum = MAX_BRD_NUM;

	m_stFlawParam.m_bSmplAct = FALSE;	// 一打开软件，就开启采样

	m_stFlawParam.m_anIpAddr[0] = CS_DEFAULT_IP0;
	m_stFlawParam.m_anIpAddr[1] = CS_DEFAULT_IP1;
	m_stFlawParam.m_anIpAddr[2] = CS_DEFAULT_IP2;
	m_stFlawParam.m_anIpAddr[3] = CS_DEFAULT_IP3;
	m_stFlawParam.m_anIpAddr[4] = CS_DEFAULT_IP4;

	m_stFlawParam.m_nNetPort = CS_DEFAULT_PORT;

	m_stFlawParam.m_nDispUpd = DISP_UPD_1HZ;		// 1Hz显示刷新
	m_stFlawParam.m_nHoriDisp = HORI_DISP_MM;		// 水平显示: mm
	m_stFlawParam.m_nVertDisp = VERT_DISP_PERC;		// 垂直显示: %

	m_stFlawParam.m_nVltSpan = 1000;
	m_stFlawParam.m_nFreqRefLine = 100;
	m_stFlawParam.m_bBwN3dB = TRUE;	// -3dB
	m_stFlawParam.m_bFlawRef = TRUE;

	m_stFlawParam.m_nRtMemTime = 60;	// 60秒钟(1分钟)

	m_stFlawParam.m_nTransVol = 20;					// V
	m_stFlawParam.m_nScanSpan = 50;					// 扫查间隔为50
	m_stFlawParam.m_nTrigMode = TRIG_MODE_TIME;		// 定时模式
	m_stFlawParam.m_nTrigPol = POL_DEF_POS;			// 正极性
	m_stFlawParam.m_nMaxDaqRate = 1000;				// 最大采集率1kHz
	core_param.m_nBrdSync = BRD_SYNC_PARA;			// 板间同步

	m_stFlawParam.m_nRfIdx = RF_IDX_50HZ;
	core_param.m_nRptFreq = RPT_FREQ_VALUE[m_stFlawParam.m_nRfIdx];

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 数字输入(DI)

	m_stFlawParam.m_stDigIn.m_bTstEnb = FALSE;
	m_stFlawParam.m_stDigIn.m_nTstFreq = 20;		// 20Hz, 50ms
	m_stFlawParam.m_stDigIn.m_nTstWidth = 25;		// 25ms
	m_stFlawParam.m_stDigIn.m_nTstChan = 0;

	m_stFlawParam.m_stDigIn.m_nBase = 0;	// 0.1ms
	for (U8 j = 0; j < TOT_DI_NUM; j++)
	{
		m_stFlawParam.m_stDigIn.m_bEnb[j] = TRUE;			// 使能
		m_stFlawParam.m_stDigIn.m_nMode[j] = DIO_MODE_LEV;	// 电平模式
		m_stFlawParam.m_stDigIn.m_nPol[j] = POL_DEF_POS;	// 正极性
		m_stFlawParam.m_stDigIn.m_nWidth[j] = 0;			// 0宽度
		m_stFlawParam.m_stDigIn.m_nDly[j] = 0;				// 0延迟
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 数字输出(DO)

	m_stFlawParam.m_stDigOut.m_nBase = 0;	// 0.1ms
	for (U8 j = 0; j < TOT_DI_NUM; j++)
	{
		m_stFlawParam.m_stDigOut.m_bEnb[j] = TRUE;			// 使能
		m_stFlawParam.m_stDigOut.m_nMode[j] = DIO_MODE_LEV;	// 电平模式
		m_stFlawParam.m_stDigOut.m_nPol[j] = POL_DEF_POS;	// 正极性
		m_stFlawParam.m_stDigOut.m_nWidth[j] = 0;			// 0宽度
		m_stFlawParam.m_stDigOut.m_nDly[j] = 0;				// 0延迟
	}

	for (U8 i = 0; i < MAX_BRD_NUM; i++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		// 编码器(ENC)

		m_stFlawParam.m_stEncModu[i].m_nTstEnb = 0;					// 测试禁止
		m_stFlawParam.m_stEncModu[i].m_nTstPulNum = 100;			// 测试脉冲数
		m_stFlawParam.m_stEncModu[i].m_nTstLineNum = 50;			// 测试线数
		m_stFlawParam.m_stEncModu[i].m_nTstFreq = 100000;			// 测试频率
		m_stFlawParam.m_stEncModu[i].m_bTstCont = TRUE;				// 持续测试

		for (U8 j = 0; j < TOT_ENC_NUM; j++)
		{
			m_stFlawParam.m_stEncModu[i].m_nFltr[j] = ENC_FLTR_100KHZ;	// 滤波：<= 100KHz
			m_stFlawParam.m_stEncModu[i].m_bEnb[j] = TRUE;				// 使能
			m_stFlawParam.m_stEncModu[i].m_nPol[j] = POL_DEF_POS;		// 正极性
			m_stFlawParam.m_stEncModu[i].m_nType[j] = ENC_TYPE_QUAD;	// 四脉冲模式
			m_stFlawParam.m_stEncModu[i].m_bZe[j] = FALSE;			// 禁止回零
			m_stFlawParam.m_stEncModu[i].m_bScan[j] =					// 0#编码器扫查使能
				(j == 0) ? TRUE : FALSE;
		}

		////////////////////////////////////////////////////////////////////////////////////////////
		// 通道参数

		core_param.m_anSynDly[i] = 0;	// 无同步延迟

		for (U8 j = 0; j < MAX_HARD_NUM; j++)
		{
			U8 hard_num = i * MAX_HARD_NUM + j;
			m_stFlawParam.m_anChanShare[hard_num] = 1;
			m_stFlawParam.m_anRtMode[hard_num] = RT_MODE_INIT;

			for (U8 k = 0; k < MAX_SOFT_NUM; k++)
			{
				core_param.m_abChanEnb[hard_num][k] = (k == 0) ? TRUE : FALSE;	// 仅每块板卡的每个硬通道的0#软通道使能
				core_param.m_anChanShare[hard_num][k] = 1;	// 所有通道均分重复时间
				m_stFlawParam.m_anAngFltr[hard_num][k] = 3;	// PCI = 0.5 ~ 21MHz; NETP2 = LPF10
				m_stFlawParam.m_anDbNum[hard_num][k] = DB_NUM_INIT;
				m_stFlawParam.m_anPulWidth[hard_num][k] = 70;	// ns
				m_stFlawParam.m_anPulNum[hard_num][k] = 0;
				m_stFlawParam.m_anDemMode[hard_num][k] = DEM_MODE_INIT;
				m_stFlawParam.m_anSoundVelo[hard_num][k] = SOUND_VELO_INIT;
				m_stFlawParam.m_anFftGate[hard_num][k] = GATE_SEL_A;	// 选择闸门A做FFT
				m_stFlawParam.m_anDbBoost[hard_num][k] = 0;

				m_stFlawParam.m_anAtIdx[hard_num][k] = AT_IDX_1;
				core_param.m_anAvgTimes[hard_num][k] = AVG_TIMES_VALUE[m_stFlawParam.m_anAtIdx[hard_num][k]];

				m_stFlawParam.m_anSdIdx[hard_num][k] = 0;
				core_param.m_anSmplDepth[hard_num][k] = 1024;

				core_param.m_anOrigDly[hard_num][k] = 0;	// ns
				core_param.m_anFreqRatio[hard_num][k] = 9;

				core_param.m_abSmplWave[hard_num][k] = TRUE;
				core_param.m_abFftWave[hard_num][k] = FALSE;
				core_param.m_abCentFreq[hard_num][k] = FALSE;

				m_stFlawParam.m_abTraceEnb[hard_num][k] = SW_STS_OFF;			// 禁止界面波跟踪
				m_stFlawParam.m_anTraceType[hard_num][k] = TRACE_TYPE_PEDGE;		// 前沿跟踪

				// 闸门参数
				for (U8 p = 0; p < TOT_GATE_NUM; p++)
				{
					m_stFlawParam.m_astGateParam[hard_num][k].m_nStart[p] = GATE_START_INIT + p * 50;
					m_stFlawParam.m_astGateParam[hard_num][k].m_nWidth[p] = GATE_WIDTH_INIT;
					m_stFlawParam.m_astGateParam[hard_num][k].m_nHeight[p] = GATE_HEIGHT_INIT - p * 50;
					m_stFlawParam.m_astGateParam[hard_num][k].m_nPol[p] = POL_DEF_POS;
					m_stFlawParam.m_astGateParam[hard_num][k].m_nType[p] = FLAW_TYPE_INIT;
					m_stFlawParam.m_astGateParam[hard_num][k].m_bEnb[p] = (p == 0) ? TRUE : FALSE;	// 仅使能GA
				}

				// TCG参数
				m_stFlawParam.m_stTcgParam[hard_num][k].tp_bTcgEnb = FALSE;
				m_stFlawParam.m_stTcgParam[hard_num][k].tp_nTcgTpTot = 0;
				for (U8 i = 0; i < TCG_TP_NUM_MAX; i++)
				{
					m_stFlawParam.m_stTcgParam[hard_num][k].tp_fTcgTpDist[i] = 0.0f;	// mm
					m_stFlawParam.m_stTcgParam[hard_num][k].tp_nTcgTpTime[i] = 0;	// ns
					m_stFlawParam.m_stTcgParam[hard_num][k].tp_nTcgTpGain[i] = 0;	// 0.1dB
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 写探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::WrFlawParam(void)
{
	FILE* fp = fopen(FLAW_PARAM_FILE_NAME, "wb");
	fwrite((void*)&m_stFlawParam, 1, sizeof(m_stFlawParam), fp);
	fclose(fp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 读探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::RdFlawParam(void)
{
	FILE* fp;
	fp = fopen(FLAW_PARAM_FILE_NAME, "rb");
	if (fp == NULL)
	{
		{
			DispMsg(ZXUT_MSG_INFO, "打开探伤参数文件失败，\n重新初始化探伤参数");
			InitFlawParam();
			WrFlawParam();
		}
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		U32 len = ftell(fp);
		if (len != sizeof(m_stFlawParam))
		{
			DispMsg(ZXUT_MSG_INFO, "探伤参数文件大小不匹配，\n重新初始化探伤参数");
			InitFlawParam();
			WrFlawParam();
			fclose(fp);
			return;
		}

		fseek(fp, 0, SEEK_SET);
		size_t ret = fread((void*)&m_stFlawParam, 1, sizeof(m_stFlawParam), fp);
		if ((ret != sizeof(m_stFlawParam)) ||	// 读取字节大小不匹配
			(m_stFlawParam.m_nSigBeg != PARAM_SIG_BEG) ||	// 开始标识不匹配
			(m_stFlawParam.m_nSigEnd != PARAM_SIG_END))		// 结束标识不匹配
		{
			DispMsg(ZXUT_MSG_INFO, "读取探伤参数文件失败，\n重新初始化探伤参数");
			InitFlawParam();
			WrFlawParam();
		}
		fclose(fp);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 同步探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SyncFlawParam(void)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	ST_FLAW_PARAM bak;
	memcpy((void*)&bak, (void*)&m_stFlawParam, sizeof(ST_FLAW_PARAM));	// 保存先前的探伤参数

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 同步获取探伤参数

	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		for (U8 j = 0; j < m_pstExpInfo->m_nTotHard; j++)
		{
			U8 hard_num = i * m_pstExpInfo->m_nTotHard + j;
			m_stFlawParam.m_anRtMode[hard_num] = m_stFlawParam.m_anRtMode[m_nHardNum];

			for (U8 k = 0; k < m_pstExpInfo->m_nTotSoft; k++)
			{
				// 被同步的通道必须使能
				U8 chan_enb = core_param.m_abChanEnb[hard_num][k];
				if (((hard_num != m_nHardNum) || (k != m_nSoftNum)) && chan_enb)
				{
					m_stFlawParam.m_anDbNum[hard_num][k] = m_stFlawParam.m_anDbNum[m_nHardNum][m_nSoftNum];
					m_stFlawParam.m_anPulWidth[hard_num][k] = m_stFlawParam.m_anPulWidth[m_nHardNum][m_nSoftNum];

					m_stFlawParam.m_anDemMode[hard_num][k] = m_stFlawParam.m_anDemMode[m_nHardNum][m_nSoftNum];
					m_stFlawParam.m_anSoundVelo[hard_num][k] = m_stFlawParam.m_anSoundVelo[m_nHardNum][m_nSoftNum];
					m_stFlawParam.m_anFftGate[hard_num][k] = m_stFlawParam.m_anFftGate[m_nHardNum][m_nSoftNum];

					m_stFlawParam.m_anAngFltr[hard_num][k] = m_stFlawParam.m_anAngFltr[m_nHardNum][m_nSoftNum];
					m_stFlawParam.m_anDbBoost[hard_num][k] = m_stFlawParam.m_anDbBoost[m_nHardNum][m_nSoftNum];

					////////////////////////////////////////////////////////////////////////////////////////////////////

					m_stFlawParam.m_anAtIdx[hard_num][k] = m_stFlawParam.m_anAtIdx[m_nHardNum][m_nSoftNum];
					core_param.m_anAvgTimes[hard_num][k] = AVG_TIMES_VALUE[m_stFlawParam.m_anAtIdx[hard_num][k]];

					m_stFlawParam.m_anSdIdx[hard_num][k] = m_stFlawParam.m_anSdIdx[m_nHardNum][m_nSoftNum];
					core_param.m_anSmplDepth[hard_num][k] = m_anSmplDepthValue[m_stFlawParam.m_anSdIdx[hard_num][k]];

					core_param.m_anChanShare[hard_num][k] = core_param.m_anChanShare[m_nHardNum][m_nSoftNum];

					core_param.m_anOrigDly[hard_num][k] = core_param.m_anOrigDly[m_nHardNum][m_nSoftNum];
					core_param.m_anFreqRatio[hard_num][k] = core_param.m_anFreqRatio[m_nHardNum][m_nSoftNum];

					core_param.m_abSmplWave[hard_num][k] = core_param.m_abSmplWave[m_nHardNum][m_nSoftNum];
					core_param.m_abFftWave[hard_num][k] = core_param.m_abFftWave[m_nHardNum][m_nSoftNum];
					core_param.m_abCentFreq[hard_num][k] = core_param.m_abCentFreq[m_nHardNum][m_nSoftNum];

					m_stFlawParam.m_abTraceEnb[hard_num][k] = m_stFlawParam.m_abTraceEnb[m_nHardNum][m_nSoftNum];
					m_stFlawParam.m_anTraceType[hard_num][k] = m_stFlawParam.m_anTraceType[m_nHardNum][m_nSoftNum];

					memcpy(&(m_stFlawParam.m_astGateParam[hard_num][k]),
						&(m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum]),
						sizeof(ST_GATE_PARAM));

					memcpy(&(m_stFlawParam.m_stTcgParam[hard_num][k]),
						&(m_stFlawParam.m_stTcgParam[m_nHardNum][m_nSoftNum]),
						sizeof(ST_TCG_PARAM));
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 采样深度是否超限

	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		U32 solo_brd_no_acc_dws = ZXUT_GetSoloBrdNoAccDaqDws(i);
		if (solo_brd_no_acc_dws > BRD_NOACC_MAX_DWS)
		{
			DispMsg(ZXUT_MSG_ERR, "当前单板无累积采集双字长度为%d，超出最大限制%d。", solo_brd_no_acc_dws, BRD_NOACC_MAX_DWS);
			memcpy((void*)&m_stFlawParam, (void*)&bak, sizeof(ST_FLAW_PARAM));	// 超限则恢复旧的探伤参数
			return;	// 超限返回
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////

	m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(FALSE);	// 关闭采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	FindNewRptFreq();	// (1) 找寻最接近当前的重复频率
	SetFlawParam();		// (2) 重新设置探伤参数
	DispMsg(ZXUT_MSG_INFO, "探伤参数已完成同步");

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(TRUE);	// 开启采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置DI参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SetDiParam(void)
{
	ST_DIG_IN& stDigIn = m_stFlawParam.m_stDigIn;

	U32 di_base = (stDigIn.m_nBase + 1) * 100;
	ZXUT_SetDiBase(0, di_base);

	ZXUT_SetDiTstEnb(0, stDigIn.m_bTstEnb);
	ZXUT_SetDiTstFreq(0, stDigIn.m_nTstFreq);
	ZXUT_SetDiTstWidth(0, stDigIn.m_nTstWidth);
	ZXUT_SetDiTstChan(0, stDigIn.m_nTstChan);

	for (U8 i = 0; i < TOT_DI_NUM; i++)
	{
		ZXUT_SetDiEnb(0, i, stDigIn.m_bEnb[i]);
		ZXUT_SetDiMode(0, i, stDigIn.m_nMode[i]);
		ZXUT_SetDiPol(0, i, stDigIn.m_nPol[i]);
		ZXUT_SetDiDly(0, i, stDigIn.m_nDly[i]);

		U32 di_width = (stDigIn.m_nWidth[i] + 1) * 10;
		ZXUT_SetDiWidth(0, i, di_width);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置DO参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SetDoParam(void)
{
	ST_DIG_OUT& stDigOut = m_stFlawParam.m_stDigOut;

	U32 do_base = (stDigOut.m_nBase + 1) * 100;
	ZXUT_SetDoBase(do_base);

	for (U8 i = 0; i < TOT_DO_NUM; i++)
	{
		ZXUT_SetDoEnb(i, stDigOut.m_bEnb[i]);
		ZXUT_SetDoMode(i, stDigOut.m_nMode[i]);
		ZXUT_SetDoPol(i, stDigOut.m_nPol[i]);
		ZXUT_SetDoCmd(i, 0);
		ZXUT_SetDoDly(i, stDigOut.m_nDly[i]);

		U32 do_width = (stDigOut.m_nWidth[i] + 1) * 10;
		ZXUT_SetDoWidth(i, do_width);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置ENC参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SetEncParam(void)
{
	for (U8 brd_num = 0; brd_num < m_pstExpInfo->m_nTotBrd; brd_num++)
	{
		ST_ENC_MODU& enc_modu = m_stFlawParam.m_stEncModu[brd_num];

		ZXUT_SetEncTstEnb(brd_num, enc_modu.m_nTstEnb);
		ZXUT_SetEncTstPulNum(brd_num, enc_modu.m_nTstPulNum);
		ZXUT_SetEncTstLineNum(brd_num, enc_modu.m_nTstLineNum);
		ZXUT_SetEncTstFreq(brd_num, enc_modu.m_nTstFreq);
		ZXUT_SetEncTstMode(brd_num, enc_modu.m_bTstCont);

		for (U8 j = 0; j < TOT_ENC_NUM; j++)
		{
			ZXUT_SetEabCntr(brd_num, j, 0);	// 初始化编码器AB相计数器
			ZXUT_SetEzCntr(brd_num, j, 0);	// 初始化编码器Z相计数器

			if (enc_modu.m_bScan[j])
			{
				ZXUT_SetScanEnc(brd_num, j);
			}

			ZXUT_SetEncType(brd_num, j, enc_modu.m_nType[j]);
			ZXUT_SetEncEnb(brd_num, j, enc_modu.m_bEnb[j]);
			ZXUT_SetEncPol(brd_num, j, enc_modu.m_nPol[j]);
			ZXUT_SetEncZe(brd_num, j, enc_modu.m_bZe[j]);
			ZXUT_SetEncFltr(brd_num, j, enc_modu.m_nFltr[j]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::SetFlawParam(void)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;

	ZXUT_SetMaxDaqRate(m_stFlawParam.m_nMaxDaqRate);

	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		ZXUT_SetTransVol(i, m_stFlawParam.m_nTransVol);
		ZXUT_SetScanSpan(i, m_stFlawParam.m_nScanSpan);
		ZXUT_SetTrigMode(i, m_stFlawParam.m_nTrigMode);
		ZXUT_SetTrigPol(i, m_stFlawParam.m_nTrigPol);

		if (m_bBrdSyncEnb)
		{
			ZXUT_SetBrdSync(i, core_param.m_nBrdSync);
		}

		for (U8 j = 0; j < m_pstExpInfo->m_nTotHard; j++)
		{
			U8 hard_num = i * m_pstExpInfo->m_nTotHard + j;
			ZXUT_SetRtMode(hard_num, m_stFlawParam.m_anRtMode[hard_num]);

			for (U8 k = 0; k < m_pstExpInfo->m_nTotSoft; k++)
			{
				U8 chan_enb = core_param.m_abChanEnb[hard_num][k];
				ZXUT_SetChanEnb(hard_num, k, chan_enb);

				if (chan_enb)
				{
					ZXUT_SetDbNum(hard_num, k, m_stFlawParam.m_anDbNum[hard_num][k]);
					ZXUT_SetPulWidth(hard_num, k, m_stFlawParam.m_anPulWidth[hard_num][k]);
					ZXUT_SetPulNum(hard_num, k, m_stFlawParam.m_anPulNum[hard_num][k]);
					ZXUT_SetTraceEnb(hard_num, k, m_stFlawParam.m_abTraceEnb[hard_num][k]);
					ZXUT_SetTraceType(hard_num, k, m_stFlawParam.m_anTraceType[hard_num][k]);
					ZXUT_SetFftGate(hard_num, k, m_stFlawParam.m_anFftGate[hard_num][k]);
					ZXUT_SetDemMode(hard_num, k, m_stFlawParam.m_anDemMode[hard_num][k]);

					if (m_bNetP2)
					{
						ZXUT_SetDbBoost(hard_num, k, m_stFlawParam.m_anDbBoost[hard_num][k]);
					}

					if (m_bAngFltrEnb)
					{
						ZXUT_SetAngFltr(hard_num, k, m_stFlawParam.m_anAngFltr[hard_num][k]);
					}

					ZXUT_SetSmplDepth(hard_num, k, core_param.m_anSmplDepth[hard_num][k], NULL, NULL);
					ZXUT_SetOrigDly(hard_num, k, core_param.m_anOrigDly[hard_num][k], NULL);
					ZXUT_SetFreqRatio(hard_num, k, core_param.m_anFreqRatio[hard_num][k], NULL);
					ZXUT_SetAvgTimes(hard_num, k, core_param.m_anAvgTimes[hard_num][k], NULL);

					ZXUT_SetDataSwitch(hard_num, k,
						core_param.m_abSmplWave[hard_num][k],
						core_param.m_abFftWave[hard_num][k],
						core_param.m_abCentFreq[hard_num][k]
					);

					U16 smpl_depth = core_param.m_anSmplDepth[hard_num][k];
					for (U8 p = 0; p < TOT_GATE_NUM; p++)
					{
						ST_GATE_PARAM& gate_param = m_stFlawParam.m_astGateParam[hard_num][k];
						ZXUT_SetGateStart(hard_num, k, p, gate_param.m_nStart[p] * smpl_depth / SHOW_SMPL_WIDTH);
						ZXUT_SetGateWidth(hard_num, k, p, gate_param.m_nWidth[p] * smpl_depth / SHOW_SMPL_WIDTH);
						ZXUT_SetGateHeight(hard_num, k, p, gate_param.m_nHeight[p] * m_nSmplWaveYRatio);
						ZXUT_SetGatePol(hard_num, k, p, gate_param.m_nPol[p]);
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 创建逻辑通道表: 确定每个逻辑通道的硬编号(H)和软编号(S)，以及逻辑通道总数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::CreateLogChanTab(void)
{
	m_stLogChan.m_nLogTot = 0;
	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		for (U8 j = 0; j < m_pstExpInfo->m_nTotHard; j++)
		{
			for (U8 k = 0; k < m_pstExpInfo->m_nTotSoft; k++)
			{
				U8 hard_num = i * m_pstExpInfo->m_nTotHard + j;
				if (m_stFlawParam.m_stCoreParam.m_abChanEnb[hard_num][k])
				{
					m_stLogChan.m_nLogHard[m_stLogChan.m_nLogTot] = hard_num;	// 逻辑通道的硬编号
					m_stLogChan.m_nLogSoft[m_stLogChan.m_nLogTot] = k;			// 逻辑通道的软编号
					m_stLogChan.m_nLogTot++;	// 逻辑通道总数增加
				}
			}
		}
	}
	m_stLogChan.m_nLogIdx = 0;
	SetCrrntChan();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 自动增益
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::GenAuotoGain(void)
{
	m_bAutoGain = TRUE;
	m_nAutoGainCntr = 0;
	m_pDlgFlawParam->m_btnAutoGain.EnableWindow(FALSE);
	m_pDlgZxut->m_chkAutoGain.SetCheck(TRUE);
}

void CZxutApp::ProcAutoGain(void)
{
	if (m_bAutoGain == FALSE) return;	// 若标志无效，则返回

	m_nAutoGainCntr++;
	if (m_nAutoGainCntr == m_pstExpInfo->m_nDaqRate / 2 - 1)
	{
		m_nAutoGainCntr = 0;	// 每1/2秒处理一次
	}
	if (m_nAutoGainCntr != 0) return;

	////////////////////////////////////////////////////////////////////////////////////////////////

	U8 y_bw = m_pstExpInfo->m_nYBw;
	U16 auto_height_lmt = 2 * (1 << y_bw) / (1 << 8);
	U16 height = m_stGateRes[GATE_SEL_A].gr_yPeak;
	height = (height == 0) ? 1 : height;	// log10的输入参数不能为0
	if ((height >= m_nAutoGainHeight - auto_height_lmt) &&
		(height <= m_nAutoGainHeight + auto_height_lmt))
	{
		m_bAutoGain = FALSE;	// 满足自动增益条件而退出
		m_pDlgFlawParam->m_btnAutoGain.EnableWindow(TRUE);
		m_pDlgZxut->m_chkAutoGain.SetCheck(FALSE);
		return;
	}

	BOOL need_exit;
	U16& db_code = m_stFlawParam.m_anDbNum[m_nHardNum][m_nSoftNum];

	// +，需要衰减；-，需要放大
	S16 delta = (S16)((20 * log10((F32)height) - 20 * log10((F32)m_nAutoGainHeight)) * 10);
	S16 tmp = db_code - delta;	// 调整以后的总增益

	U16 max_db = m_pstExpInfo->m_nMaxGain;
	if ((tmp >= DB_NUM_MIN) && (tmp <= max_db))
	{
		need_exit = FALSE;		// 继续自动增益
		db_code -= delta;
	}
	else if (tmp > max_db)
	{
		need_exit = TRUE;
		db_code = max_db;	// 避免放大过度, -
	}
	else
	{
		need_exit = TRUE;
		db_code = DB_NUM_MIN;	// 避免衰减过度, +
	}

	// 更新增益
	m_pFlawParamAdj->FreshDbNum();
	ZXUT_SetDbNum(m_nHardNum, m_nSoftNum, db_code);

	if (need_exit == TRUE)
	{
		m_bAutoGain = FALSE;	// 超出增益调节范围，而退出自动增益
		m_pDlgFlawParam->m_btnAutoGain.EnableWindow(TRUE);
		m_pDlgZxut->m_chkAutoGain.SetCheck(FALSE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 翻译快捷键
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutApp::PreTranslateMessage(MSG* pMsg)
{
	int iResult;

	// 针对WM_KEYDOWN消息和WM_SYSKEYDOWN消息，翻译快捷键
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		iResult = TranslateAccelerator(*AfxGetMainWnd(), m_hAcc, pMsg);
		if (iResult) return TRUE;	// 翻译快捷键成功，返回TRUE
	}

	return CWinAppEx::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 通道调节
//
////////////////////////////////////////////////////////////////////////////////////////////////////

// 减少通道
void CZxutApp::OnChanDec(void)
{
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点
	if (m_stLogChan.m_nLogIdx == 0) return;
	m_stLogChan.m_nLogIdx--;
	UpdChanNum();
}

// 增加通道
void CZxutApp::OnChanInc(void)
{
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点
	if (m_stLogChan.m_nLogIdx + 1 == m_stLogChan.m_nLogTot) return;
	m_stLogChan.m_nLogIdx++;
	UpdChanNum();
}

// 更新通道编号
void CZxutApp::UpdChanNum(void)
{
	SetCrrntChan();
	m_pDlgSysSetting->UpdBrdSn();
	m_pFlawParamAdj->FreshFlawParam();	// 更新探伤参数

	if (m_pDlgZxut->m_tabZxut.GetCurSel() == TAB_TCG_PROC)
	{
		m_pDlgTcgProc->FreshTcgBtnSts();	// 更新TCG按钮状态
		m_pDlgTcgProc->FreshTcgTp();		// 更新TCG测试点
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 增益调节
//
////////////////////////////////////////////////////////////////////////////////////////////////////

// 自动增益
void CZxutApp::OnAutoGain(void)
{
	if (m_bDacCalib) return;
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点
	m_pDlgFlawParam->OnBnClickedBtnAutoGain();
}

// -0.1dB - 细调
void CZxutApp::OnGainDecFine(void)
{
	if (m_bDacCalib) return;
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点

	ST_FLAW_PARAM& param = m_stFlawParam;
	U16& db_code = param.m_anDbNum[m_nHardNum][m_nSoftNum];
	if (db_code == 0) return;		// 已经是最小了
	db_code--;
	m_pFlawParamAdj->FreshDbNum();
	ZXUT_SetDbNum(m_nHardNum, m_nSoftNum, db_code);
}

// +0.1dB - 细调
void CZxutApp::OnGainIncFine(void)
{
	if (m_bDacCalib) return;
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点

	ST_FLAW_PARAM& param = m_stFlawParam;
	U16& db_code = param.m_anDbNum[m_nHardNum][m_nSoftNum];
	U16 max_db = m_pstExpInfo->m_nMaxGain;
	if (db_code == max_db) return;	// 已经是最大了
	db_code++;
	m_pFlawParamAdj->FreshDbNum();
	ZXUT_SetDbNum(m_nHardNum, m_nSoftNum, db_code);
}

// -2dB - 粗调
void CZxutApp::OnGainDecCoarse(void)
{
	if (m_bDacCalib) return;
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点
	m_pDlgFlawParam->OnBnClickedBtnDbMinus();
}

// +2dB - 粗调
void CZxutApp::OnGainIncCoarse(void)
{
	if (m_bDacCalib) return;
	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点
	m_pDlgFlawParam->OnBnClickedBtnDbPlus();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 限制闸门参数调节
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutApp::LmtGateParamAdj(U8 nGateIdx)
{
	if (m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_bEnb[nGateIdx])
	{
		if (m_stFlawParam.m_abTraceEnb[m_nHardNum][m_nSoftNum])
		{
			DispMsg(ZXUT_MSG_WARNING, "跟踪已使能，不能调节闸门参数");
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		DispMsg(ZXUT_MSG_WARNING, "%s已禁止，不能调节闸门参数", GATE_SEL_STR[nGateIdx]);
		return TRUE;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门BCI使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::OnGbEnb(void)
{
	AdjGateEnb(GATE_SEL_B);
}

void CZxutApp::OnGcEnb(void)
{
	AdjGateEnb(GATE_SEL_C);
}

void CZxutApp::OnGiEnb(void)
{
	AdjGateEnb(GATE_SEL_I);
}

void CZxutApp::AdjGateEnb(U8 nGateIdx)
{
	BOOL& gate_enb = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_bEnb[nGateIdx];

	gate_enb = (gate_enb == TRUE) ? FALSE : TRUE;	// 切换

	// 刷新闸门参数显示，以便背景色生效
	CString str = "";
	m_pFlawGateAdj->FreshGateStart(nGateIdx);
	m_pFlawGateAdj->FreshGateWidth(nGateIdx);
	m_pFlawGateAdj->FreshGateHeight(nGateIdx);
	m_pFlawGateAdj->FreshGatePol(nGateIdx);
	m_pFlawGateAdj->FreshFlawType(nGateIdx);
	m_pFlawGateAdj->FreshPeakHori(nGateIdx, str);
	m_pFlawGateAdj->FreshPeakVert(nGateIdx, str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门起点调节
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::AdjGateStart(U8 nGateIdx, BOOL bAdjDec, U8 nAdjGrain)
{
	if (LmtGateParamAdj(nGateIdx) == TRUE) return;

	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点

	U16& gate_start = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_nStart[nGateIdx];
	U16  gate_width = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_nWidth[nGateIdx];

	if (bAdjDec)
	{
		if (gate_start < nAdjGrain) return;	// 已经是最左边了
		gate_start -= nAdjGrain;
	}
	else
	{
		if (gate_start + nAdjGrain > SHOW_SMPL_WIDTH - gate_width - 1) return;	// 已经是最右边了
		gate_start += nAdjGrain;
	}

	U16 smpl_depth = m_stFlawParam.m_stCoreParam.m_anSmplDepth[m_nHardNum][m_nSoftNum];
	ZXUT_SetGateStart(m_nHardNum, m_nSoftNum, nGateIdx, gate_start * smpl_depth / SHOW_SMPL_WIDTH);
	m_pFlawGateAdj->FreshGateStart(nGateIdx);
}

void CZxutApp::OnGaStartDecFine(void) { AdjGateStart(GATE_SEL_A, TRUE, 1); }
void CZxutApp::OnGaStartDecCoarse(void) { AdjGateStart(GATE_SEL_A, TRUE, 10); }
void CZxutApp::OnGaStartIncFine(void) { AdjGateStart(GATE_SEL_A, FALSE, 1); }
void CZxutApp::OnGaStartIncCoarse(void) { AdjGateStart(GATE_SEL_A, FALSE, 10); }

void CZxutApp::OnGbStartDecFine(void) { AdjGateStart(GATE_SEL_B, TRUE, 1); }
void CZxutApp::OnGbStartDecCoarse(void) { AdjGateStart(GATE_SEL_B, TRUE, 10); }
void CZxutApp::OnGbStartIncFine(void) { AdjGateStart(GATE_SEL_B, FALSE, 1); }
void CZxutApp::OnGbStartIncCoarse(void) { AdjGateStart(GATE_SEL_B, FALSE, 10); }

void CZxutApp::OnGcStartDecFine(void) { AdjGateStart(GATE_SEL_C, TRUE, 1); }
void CZxutApp::OnGcStartDecCoarse(void) { AdjGateStart(GATE_SEL_C, TRUE, 10); }
void CZxutApp::OnGcStartIncFine(void) { AdjGateStart(GATE_SEL_C, FALSE, 1); }
void CZxutApp::OnGcStartIncCoarse(void) { AdjGateStart(GATE_SEL_C, FALSE, 10); }

void CZxutApp::OnGiStartDecFine(void) { AdjGateStart(GATE_SEL_I, TRUE, 1); }
void CZxutApp::OnGiStartDecCoarse(void) { AdjGateStart(GATE_SEL_I, TRUE, 10); }
void CZxutApp::OnGiStartIncFine(void) { AdjGateStart(GATE_SEL_I, FALSE, 1); }
void CZxutApp::OnGiStartIncCoarse(void) { AdjGateStart(GATE_SEL_I, FALSE, 10); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门宽度调节
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::AdjGateWidth(U8 nGateIdx, BOOL bAdjDec, U8 nAdjGrain)
{
	if (LmtGateParamAdj(nGateIdx) == TRUE) return;

	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点

	U16& gate_start = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_nStart[nGateIdx];
	U16& gate_width = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum].m_nWidth[nGateIdx];

	if (bAdjDec)
	{
		if (gate_width - nAdjGrain < GATE_WIDTH_MIN) return;	// 已经是最左边(最小)了
		gate_width -= nAdjGrain;
	}
	else
	{
		if (gate_width + nAdjGrain > SHOW_SMPL_WIDTH - gate_start - 1) return;	// 已经是最右边(最大)了
		gate_width += nAdjGrain;
	}

	U16 smpl_depth = m_stFlawParam.m_stCoreParam.m_anSmplDepth[m_nHardNum][m_nSoftNum];
	ZXUT_SetGateWidth(m_nHardNum, m_nSoftNum, nGateIdx, gate_width * smpl_depth / SHOW_SMPL_WIDTH);
	m_pFlawGateAdj->FreshGateWidth(nGateIdx);
}

void CZxutApp::OnGaWidthDecFine(void) { AdjGateWidth(GATE_SEL_A, TRUE, 1); }
void CZxutApp::OnGaWidthDecCoarse(void) { AdjGateWidth(GATE_SEL_A, TRUE, 10); }
void CZxutApp::OnGaWidthIncFine(void) { AdjGateWidth(GATE_SEL_A, FALSE, 1); }
void CZxutApp::OnGaWidthIncCoarse(void) { AdjGateWidth(GATE_SEL_A, FALSE, 10); }

void CZxutApp::OnGbWidthDecFine(void) { AdjGateWidth(GATE_SEL_B, TRUE, 1); }
void CZxutApp::OnGbWidthDecCoarse(void) { AdjGateWidth(GATE_SEL_B, TRUE, 10); }
void CZxutApp::OnGbWidthIncFine(void) { AdjGateWidth(GATE_SEL_B, FALSE, 1); }
void CZxutApp::OnGbWidthIncCoarse(void) { AdjGateWidth(GATE_SEL_B, FALSE, 10); }

void CZxutApp::OnGcWidthDecFine(void) { AdjGateWidth(GATE_SEL_C, TRUE, 1); }
void CZxutApp::OnGcWidthDecCoarse(void) { AdjGateWidth(GATE_SEL_C, TRUE, 10); }
void CZxutApp::OnGcWidthIncFine(void) { AdjGateWidth(GATE_SEL_C, FALSE, 1); }
void CZxutApp::OnGcWidthIncCoarse(void) { AdjGateWidth(GATE_SEL_C, FALSE, 10); }

void CZxutApp::OnGiWidthDecFine(void) { AdjGateWidth(GATE_SEL_I, TRUE, 1); }
void CZxutApp::OnGiWidthDecCoarse(void) { AdjGateWidth(GATE_SEL_I, TRUE, 10); }
void CZxutApp::OnGiWidthIncFine(void) { AdjGateWidth(GATE_SEL_I, FALSE, 1); }
void CZxutApp::OnGiWidthIncCoarse(void) { AdjGateWidth(GATE_SEL_I, FALSE, 10); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门高度调节
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::AdjGateHeight(U8 nGateIdx, BOOL bAdjDec, U8 nAdjGrain)
{
	if (LmtGateParamAdj(nGateIdx) == TRUE) return;

	m_pDlgZxut->m_btnSmplEnb.SetFocus();	// 转移焦点

	ST_FLAW_PARAM& param = m_stFlawParam;
	U16& gate_height = param.m_astGateParam[m_nHardNum][m_nSoftNum].m_nHeight[nGateIdx];

	if (bAdjDec)
	{
		if (gate_height - nAdjGrain < GATE_HEIGHT_MIN) return;
		gate_height -= nAdjGrain;
	}
	else
	{
		if (gate_height + nAdjGrain > SHOW_SMPL_HEIGHT - GATE_HEIGHT_MIN + 1) return;
		gate_height += nAdjGrain;
	}

	ZXUT_SetGateHeight(m_nHardNum, m_nSoftNum, nGateIdx, gate_height * m_nSmplWaveYRatio);
	m_pFlawGateAdj->FreshGateHeight(nGateIdx);
}

void CZxutApp::OnGaHeightDecFine(void) { AdjGateHeight(GATE_SEL_A, TRUE, 1); }
void CZxutApp::OnGaHeightDecCoarse(void) { AdjGateHeight(GATE_SEL_A, TRUE, 10); }
void CZxutApp::OnGaHeightIncFine(void) { AdjGateHeight(GATE_SEL_A, FALSE, 1); }
void CZxutApp::OnGaHeightIncCoarse(void) { AdjGateHeight(GATE_SEL_A, FALSE, 10); }

void CZxutApp::OnGbHeightDecFine(void) { AdjGateHeight(GATE_SEL_B, TRUE, 1); }
void CZxutApp::OnGbHeightDecCoarse(void) { AdjGateHeight(GATE_SEL_B, TRUE, 10); }
void CZxutApp::OnGbHeightIncFine(void) { AdjGateHeight(GATE_SEL_B, FALSE, 1); }
void CZxutApp::OnGbHeightIncCoarse(void) { AdjGateHeight(GATE_SEL_B, FALSE, 10); }

void CZxutApp::OnGcHeightDecFine(void) { AdjGateHeight(GATE_SEL_C, TRUE, 1); }
void CZxutApp::OnGcHeightDecCoarse(void) { AdjGateHeight(GATE_SEL_C, TRUE, 10); }
void CZxutApp::OnGcHeightIncFine(void) { AdjGateHeight(GATE_SEL_C, FALSE, 1); }
void CZxutApp::OnGcHeightIncCoarse(void) { AdjGateHeight(GATE_SEL_C, FALSE, 10); }

void CZxutApp::OnGiHeightDecFine(void) { AdjGateHeight(GATE_SEL_I, TRUE, 1); }
void CZxutApp::OnGiHeightDecCoarse(void) { AdjGateHeight(GATE_SEL_I, TRUE, 10); }
void CZxutApp::OnGiHeightIncFine(void) { AdjGateHeight(GATE_SEL_I, FALSE, 1); }
void CZxutApp::OnGiHeightIncCoarse(void) { AdjGateHeight(GATE_SEL_I, FALSE, 10); }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 根据刷新率计算得到的终值
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::GetUpdProcEnd(void)
{
	for (U8 i = 0; i < TOT_GATE_NUM; i++) m_nUpdProcCntr[i] = 0;

	switch (m_stFlawParam.m_nDispUpd)
	{
	case DISP_UPD_1HZ:	m_nUpdProcEnd = m_pstExpInfo->m_nDaqRate / 1; break;
	case DISP_UPD_2HZ:	m_nUpdProcEnd = m_pstExpInfo->m_nDaqRate / 2; break;
	case DISP_UPD_5HZ:	m_nUpdProcEnd = m_pstExpInfo->m_nDaqRate / 5; break;
	case DISP_UPD_10HZ: m_nUpdProcEnd = m_pstExpInfo->m_nDaqRate / 10; break;
	case DISP_UPD_20HZ: m_nUpdProcEnd = m_pstExpInfo->m_nDaqRate / 20; break;
	default: return;
	}

	m_nUpdProcEnd = (m_nUpdProcEnd == 0) ? 1 : m_nUpdProcEnd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 清除FFT结果
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::ClrFftRes(void)
{
	for (U32 i = 0; i < FFT_OUT_DOTS; i++)
	{
		m_anFftCurve[i] = 0;
		m_anBwData[i] = 0;
		m_anBwCurve[i] = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 测量垂直线性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::TstVertLinear(void)
{
	m_pThrdTstVertLinear = AfxBeginThread(pfnThrdTstVertLinear, (LPVOID)this,
		THREAD_PRIORITY_NORMAL, 0, 0);	// 正常优先级
}

UINT CZxutApp::pfnThrdTstVertLinear(LPVOID lpParam)
{
	CZxutApp* This = reinterpret_cast<CZxutApp*>(lpParam);
	return This->ThrdTstVertLinearHandler();
}

UINT CZxutApp::ThrdTstVertLinearHandler(void)
{
	if (m_bDacCalib) return FALSE;

	U8 db_items = 14;
	U32 time_dly;
	U16& db_code = m_stFlawParam.m_anDbNum[m_nHardNum][m_nSoftNum];
	time_dly = m_stFlawParam.m_nVltSpan;

	FILE* fp = fopen("垂直线性.txt", "wt");
	if (fp == NULL)
	{
		DispMsg(ZXUT_MSG_ERR, "不能打开写文件“垂直线性.txt”");
		return FALSE;
	}

	fprintf(fp, "%d.%ddB\n", db_code / 10, db_code % 10);	// 写入当前增益

	int wave_std[14] = { 1000, 794, 631, 501, 398, 316, 251, 200, 158, 125, 100, 79, 63, 50 };
	int wave_height[14];
	int wave_error[14];

	// 写入标准波高
	for (U8 i = 0; i < db_items; i++)
	{
		fprintf(fp, "%3d.%1d ", wave_std[i] / 10, wave_std[i] % 10);
	}
	fprintf(fp, "\n");

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取不同增益下的波高

	U8 y_bw = m_pstExpInfo->m_nYBw;
	wave_height[0] = (int)(m_nAvgWaveHeight * 100.0 / (((1 << y_bw) - 1) * 1.0) * 10.0);
	fprintf(fp, "%3d.%1d ", wave_height[0] / 10, wave_height[0] % 10);

	for (U8 i = 1; i < db_items; i++)
	{
		if (db_code < 20)
		{
			db_items = i;
			break;
		}

		db_code -= 20;
		ZXUT_SetDbNum(m_nHardNum, m_nSoftNum, db_code);
		Sleep(time_dly);
		wave_height[i] = (int)(m_nAvgWaveHeight * 100.0 / (((1 << y_bw) - 1) * 1.0) * 10.0);
		fprintf(fp, "%3d.%1d ", wave_height[i] / 10, wave_height[i] % 10);
	}
	fprintf(fp, "\n");

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 恢复之前的增益

	db_code += (db_items - 1) * 20;
	ZXUT_SetDbNum(m_nHardNum, m_nSoftNum, db_code);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 计算垂直线性误差

	char str_vert[100];
	for (U8 i = 0; i < db_items; i++)
	{
		wave_error[i] = wave_height[i] - wave_std[i];
		sprintf(str_vert, "%c%d.%d",
			wave_error[i] >= 0 ? '+' : '-',	// 最终误差
			wave_error[i] >= 0 ? wave_error[i] / 10 : (-1 * wave_error[i]) / 10,
			wave_error[i] >= 0 ? wave_error[i] % 10 : (-1 * wave_error[i]) % 10);
		fprintf(fp, "%5s ", str_vert);
	}

	int max = wave_error[0], min = wave_error[0];
	for (U8 i = 1; i < db_items; i++)
	{
		if (wave_error[i] >= max)
		{
			max = wave_error[i];	// 最大误差
		}

		if (wave_error[i] <= min)
		{
			min = wave_error[i];	// 最小误差
		}
	}

	int error;
	int min_abs = min >= 0 ? min : -1 * min;	// 最小值绝对值
	int max_abs = max >= 0 ? max : -1 * max;	// 最大值绝对值
	if (max * min < 0)
	{
		// 异号，取其和
		error = max_abs + min_abs;
	}
	else
	{
		// 同号，取最大
		error = (max_abs > min_abs) ? max_abs : min_abs;
	}

	char str_error[100];
	sprintf(str_error, "%c%d.%d",
		error >= 0 ? '+' : '-',	// 最终误差
		error >= 0 ? error / 10 : (-1 * error) / 10,
		error >= 0 ? error % 10 : (-1 * error) % 10);

	char str_min[100];
	sprintf(str_min, "%c%d.%d",	// 最小误差
		min >= 0 ? '+' : '-',
		min >= 0 ? min / 10 : (-1 * min) / 10,
		min >= 0 ? min % 10 : (-1 * min) % 10);

	char str_max[100];
	sprintf(str_max, "%c%d.%d",	// 最大误差
		max >= 0 ? '+' : '-',
		max >= 0 ? max / 10 : (-1 * max) / 10,
		max >= 0 ? max % 10 : (-1 * max) % 10);

	fprintf(fp, "%5s %5s %5s\n", str_error, str_min, str_max);
	fclose(fp);

	::WinExec("C:/WINDOWS/NOTEPAD.EXE 垂直线性.txt", SW_SHOWNORMAL);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 锁定频带
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::LockBwCurve(void)
{
	memcpy(m_anBwLockCurve, m_anBwCurve, sizeof(m_anBwLockCurve));
	memcpy(m_anBwLockData, m_anBwData, sizeof(m_anBwLockData));

	BOOL ret_res;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 求最大频率点

	m_nBwMaxData = 0;
	ret_res = FALSE;
	for (U16 i = 0; i < FFT_CURVE_LEN; i++)
	{
		if (m_anBwLockData[i] >= m_nBwMaxData)
		{
			m_nBwMaxData = m_anBwLockData[i];
			m_nBwMaxIdx = i;
			ret_res = TRUE;
		}
	}

	if (ret_res == FALSE)
	{
		DispMsg(ZXUT_MSG_ERR, "求最大频率点失败");
		m_bLockBw = FALSE;
		return;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 求左边的-3dB点

	double roll_off;
	if (m_stFlawParam.m_bBwN3dB == TRUE)
	{
		roll_off = 0.707;	// -3dB
	}
	else
	{
		roll_off = 0.5;		// -6dB
	}

	ret_res = FALSE;
	for (S16 i = m_nBwMaxIdx; i >= 0; i--)
	{
		if (m_anBwLockData[i] <= (U16)(m_nBwMaxData * roll_off))
		{
			m_nBwLeftIdx = i;
			ret_res = TRUE;
			break;
		}
	}

	if (ret_res == FALSE)
	{
		if (m_stFlawParam.m_bBwN3dB == TRUE)
		{
			DispMsg(ZXUT_MSG_ERR, "求左边的-3dB点失败");
		}
		else
		{
			DispMsg(ZXUT_MSG_ERR, "求左边的-6dB点失败");
		}
		m_bLockBw = FALSE;
		return;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 求右边的-3dB点

	ret_res = FALSE;
	for (U16 i = m_nBwMaxIdx; i < FFT_CURVE_LEN; i++)
	{
		if (m_anBwLockData[i] <= (U16)(m_nBwMaxData * roll_off))
		{
			m_nBwRightIdx = i;
			ret_res = TRUE;
			break;
		}
	}

	if (ret_res == FALSE)
	{
		if (m_stFlawParam.m_bBwN3dB == TRUE)
		{
			DispMsg(ZXUT_MSG_ERR, "求右边的-3dB点失败");
		}
		else
		{
			DispMsg(ZXUT_MSG_ERR, "求右边的-6dB点失败");
		}
		m_bLockBw = FALSE;
		return;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////

	U8 y_bw = m_pstExpInfo->m_nYBw;
	m_nBwMaxCurve = m_nBwMaxData * 180 / (1 << (y_bw - 1));	// 128 / 2048
	m_bLockBw = TRUE;

	m_pDlgFftProc->m_combFreqRefLine.EnableWindow(TRUE);
	m_pDlgFftProc->m_btnRecBw.EnableWindow(TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 分析频带
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::AnalyzeBwCure(void)
{
	U16 freq_ratio = m_stFlawParam.m_stCoreParam.m_anFreqRatio[m_nHardNum][m_nSoftNum];
	m_fFreqLeft = ZXUT_GetFftFreq(m_nBwLeftIdx, freq_ratio);	// 左-3dB
	m_fFreqMax = ZXUT_GetFftFreq(m_nBwMaxIdx, freq_ratio);		// 最大
	m_fFreqRight = ZXUT_GetFftFreq(m_nBwRightIdx, freq_ratio);	// 右-3dB
	m_fFreqCent = (m_fFreqLeft + m_fFreqRight) / 2;		// 中心
	DispMsg(ZXUT_MSG_INFO, "单位：MHz\n\n"
		"    最大频率：%5.2f\n\n"
		"左-3dB频率：%5.2f\n"
		"    中心频率：%5.2f\n"
		"右-3dB频率：%5.2f\n\n"
		"    %s带宽: %5.2f ~ %5.2f",
		m_fFreqMax, m_fFreqLeft, m_fFreqCent, m_fFreqRight,
		m_stFlawParam.m_bBwN3dB ? "-3dB" : "-6dB",
		m_fFreqLeft, m_fFreqRight);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 导出波形数据
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::ExportWaveData(void)
{
/*	FILE* fpDec = fopen("wave_dec.txt", "wt");	// 10进制输出
	FILE* fpHex = fopen("wave_hex.txt", "wt");	// 16进制输出
	if ((fpDec == NULL) || (fpHex == NULL))
	{
		return;
	}

	ST_RQ_DATA& daq_buf = *(m_pstExpInfo->m_apstDaqBuf[m_nHardNum / m_pstExpInfo->m_nTotHard]);
	ST_DAQ_DATA& acc_buf = daq_buf.m_stAccData[0][m_nHardNum % m_pstExpInfo->m_nTotHard][m_nSoftNum];
	for (U32 i = 0; i < acc_buf.m_nSmplDepth; i++)
	{
		fprintf(fpDec, "%d\n", m_anSmplBuf[i]);
		fprintf(fpHex, "%03X\n", m_anSmplBuf[i]);
	}

	fclose(fpDec);
	fclose(fpHex);

	char cmd_line[100];
	sprintf(cmd_line, "C:/WINDOWS/NOTEPAD.EXE %s", "wave_dec.txt");
	::WinExec(cmd_line, SW_SHOWNORMAL);*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 粗减(-10)频率参考线

void CZxutApp::OnFreqRefLineDecCoarse(void)
{
	if (m_bLockBw == FALSE) return;

	if (m_stFlawParam.m_nFreqRefLine > 10)
	{
		m_stFlawParam.m_nFreqRefLine -= 10;
		m_pDlgFftProc->m_combFreqRefLine.SetCurSel(m_stFlawParam.m_nFreqRefLine);
	}

	FreezeUpdFreqRefLine();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 细减(-1)频率参考线

void CZxutApp::OnFreqRefLineDecFine(void)
{
	if (m_bLockBw == FALSE) return;

	if (m_stFlawParam.m_nFreqRefLine > 1)
	{
		m_stFlawParam.m_nFreqRefLine -= 1;
		m_pDlgFftProc->m_combFreqRefLine.SetCurSel(m_stFlawParam.m_nFreqRefLine);
	}

	FreezeUpdFreqRefLine();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 粗加(+10)频率参考线

void CZxutApp::OnFreqRefLineIncCoarse(void)
{
	if (m_bLockBw == FALSE) return;

	if (m_stFlawParam.m_nFreqRefLine + 10 < FFT_CURVE_LEN)
	{
		m_stFlawParam.m_nFreqRefLine += 10;
		m_pDlgFftProc->m_combFreqRefLine.SetCurSel(m_stFlawParam.m_nFreqRefLine);
	}

	FreezeUpdFreqRefLine();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 细加(+1)频率参考线

void CZxutApp::OnFreqRefLineIncFine(void)
{
	if (m_bLockBw == FALSE) return;

	if (m_stFlawParam.m_nFreqRefLine + 1 < FFT_CURVE_LEN)
	{
		m_stFlawParam.m_nFreqRefLine += 1;
		m_pDlgFftProc->m_combFreqRefLine.SetCurSel(m_stFlawParam.m_nFreqRefLine);
	}

	FreezeUpdFreqRefLine();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 波形冻结时更新频率参考线

void CZxutApp::FreezeUpdFreqRefLine(void)
{
	if (m_bSmplEnb == FALSE)
	{
		F32 a = (F32)m_anBwLockData[m_stFlawParam.m_nFreqRefLine];
		F32 b = (F32)m_nBwMaxData;
		F32 delta = (F32)(20.0 * log10(a / b));
		CString info;
		info.Format("%.1f", delta);
		m_pDlgFftProc->m_txtInstGain.SetWindowText(info);

		m_pFftShow->ShowFftView(m_anFftCurve, m_anBwCurve, m_nBwLeftIdx, m_nBwMaxIdx, m_nBwRightIdx, m_nBwMaxCurve,
			m_stFlawParam.m_nFreqRefLine);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 读指定板号

void CZxutApp::RdBrdSn(U8 nBrdSnType)
{
	U8 brd_num = m_nHardNum / m_pstExpInfo->m_nTotHard;
	ZXUT_GetBrdSn(brd_num, nBrdSnType);

	char* str = m_pstExpInfo->m_aastrBrdSn[brd_num][nBrdSnType];
	m_pDlgSysSetting->m_strBrdSn[nBrdSnType].Format("%s", str);

	m_pDlgSysSetting->UpdateData(FALSE);	// 更新到控件
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 写入指定板号

void CZxutApp::WrBrdSn(U8 nBrdSnType)
{
	m_pDlgSysSetting->UpdateData(TRUE);		// 更新到变量

	char str_sn[BRD_SN_TYPE_LEN * 2 + 1];
	//	sprintf(str_sn, "%s", m_pDlgSysSetting->m_strBrdSn[nBrdSnType]);
	strcpy(str_sn, m_pDlgSysSetting->m_strBrdSn[nBrdSnType]);

	U8 brd_num = m_nHardNum / m_pstExpInfo->m_nTotHard;
	S32 ret = ZXUT_SetBrdSn(brd_num, nBrdSnType, str_sn);
	switch (ret)
	{
	case ZRC_API_RET_SUCCESS:
		return;

	case ZRC_INVALID_BRD_SN_LEN:
		DispMsg(ZXUT_MSG_ERR, "板号长度必须为%d位", BRD_SN_TYPE_LEN * 2);
		return;

	case ZRC_BRD_SN_NOT_NUM:
		DispMsg(ZXUT_MSG_WARNING, "板号只能是数字");
		return;

	case ZRC_NOT_ZXUT_PROVIDER:
		DispMsg(ZXUT_MSG_WARNING, "只有设备制造商才可设置板号");
		return;

	case ZRC_BRD_SN_WR_FAIL:
		DispMsg(ZXUT_MSG_WARNING, "设置板号写操作失败");
		return;

	default:
		DispMsg(ZXUT_MSG_WARNING, "设置板号出现未知错误，返回码：%d", ret);
		return;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 测试用户寄存器
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::TstUsrReg(void)
{
	char str[2][20] = { "Error", "Ok" };
	BOOL cmp_ok[8];
	U32 usr_reg[8], tst_buf[8] =
	{
		0x00000000, 0x55555555, 0xAAAAAAAA, 0xFFFFFFFF,
		0x5A5A5A5A, 0xA5A5A5A5, 0x05AFFA50, 0xFA5005AF
	};

	U8 brd_num = m_nHardNum / m_pstExpInfo->m_nTotHard;	// 板号

	for (U8 i = 0; i < 8; i++)
	{
		// 写用户寄存器
		ZXUT_SetUsrReg(brd_num, tst_buf[i]);

		// 读用户寄存器
		usr_reg[i] = ZXUT_GetUsrReg(brd_num);
		cmp_ok[i] = (usr_reg[i] == tst_buf[i]);
	}

	DispMsg(ZXUT_MSG_INFO, "用户寄存器测试结果\n"
		"0 - 0x%08X, \t0x%08X \t%s\n"
		"1 - 0x%08X, \t0x%08X \t%s\n"
		"2 - 0x%08X, \t0x%08X \t%s\n"
		"3 - 0x%08X, \t0x%08X \t%s\n"
		"4 - 0x%08X, \t0x%08X \t%s\n"
		"5 - 0x%08X, \t0x%08X \t%s\n"
		"6 - 0x%08X, \t0x%08X \t%s\n"
		"7 - 0x%08X, \t0x%08X \t%s\n",
		tst_buf[0], usr_reg[0], str[cmp_ok[0]],
		tst_buf[1], usr_reg[1], str[cmp_ok[1]],
		tst_buf[2], usr_reg[2], str[cmp_ok[2]],
		tst_buf[3], usr_reg[3], str[cmp_ok[3]],
		tst_buf[4], usr_reg[4], str[cmp_ok[4]],
		tst_buf[5], usr_reg[5], str[cmp_ok[5]],
		tst_buf[6], usr_reg[6], str[cmp_ok[6]],
		tst_buf[7], usr_reg[7], str[cmp_ok[7]]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 打开探伤设备
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutApp::OpenDevice(void)
{
	ET_ZRC ret_code;
	m_nClientIpAddr =
		(m_stFlawParam.m_anIpAddr[0] << 3 * 8) +
		(m_stFlawParam.m_anIpAddr[1] << 2 * 8) +
		(m_stFlawParam.m_anIpAddr[2] << 1 * 8) +
		(m_stFlawParam.m_anIpAddr[3] << 0 * 8);

	// 打开PCI探伤设备
	ret_code = ZXUT_OpenDevice(ZXUT_TYPE_PCI, 0, 0, &m_pstExpInfo);
	if (ret_code == ZRC_API_RET_SUCCESS)
	{
		m_nZxutType = ZXUT_TYPE_PCI;
	}
	else
	{
		// 已侦测到PCI板卡，但返回值错误
		if (ret_code != ZRC_NO_BRD_INSERT)
		{
			switch (ret_code)
			{
				case ZRC_SYS_INFO_MISMATCH:
					DispMsg(ZXUT_MSG_INFO, "反馈的系统信息不全相同");
					return FALSE;

				case ZRC_INVALID_PCB_VER:
					DispMsg(ZXUT_MSG_INFO, "无效的PCB版本");
					return FALSE;

				case ZRC_INVALID_FPGA_VER:
					DispMsg(ZXUT_MSG_INFO, "无效的FPGA版本");
					return FALSE;

				case ZRC_INVALID_TOT_HARD:
					DispMsg(ZXUT_MSG_INFO, "无效的硬通道总数");
					return FALSE;

				case ZRC_INVALID_TOT_SOFT:
					DispMsg(ZXUT_MSG_INFO, "无效的软通道总数");
					return FALSE;

				default:
					DispMsg(ZXUT_MSG_ERR, "未知错误%d", ret_code);
					return FALSE;
			}
		}

		// PCI通道板没有侦测到，马上连接网络
		ret_code = OpenNetDev();
		switch (ret_code)
		{
		case ZRC_API_RET_SUCCESS:
			break;

		case ZRC_CREATE_SOCKET_FAIL:
			DispMsg(ZXUT_MSG_ERR, "创建TCP套接字失败");
			return FALSE;

		case ZRC_BIND_SERVER_FAIL:
			DispMsg(ZXUT_MSG_ERR, "绑定服务器地址和端口失败");
			return FALSE;

		case ZRC_LISTEN_SERVER_FAIL:
			DispMsg(ZXUT_MSG_ERR, "服务器监听失败");
			return FALSE;

		case ZRC_USR_CANCEL_CONNECT:
			DispMsg(ZXUT_MSG_INFO, "已取消客户端连接，退出系统\n");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		case ZRC_NO_CLIENT_CONNECT:
			DispMsg(ZXUT_MSG_INFO, "一个客户端都没有连接，退出系统\n");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		case ZRC_NO_MAST_BRD:
			DispMsg(ZXUT_MSG_INFO, "没有插入主通道板\n");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		default:
			DispMsg(ZXUT_MSG_ERR, "等待客户端连接出现未知错误%d", ret_code);
			return FALSE;
		}

		ret_code = ZXUT_OpenDevice(ZXUT_TYPE_NET, m_nTotBrd, m_sockZxut, &m_pstExpInfo);
		switch (ret_code)
		{
		case ZRC_API_RET_SUCCESS:
			m_nZxutType = ZXUT_TYPE_NET;
			break;

		case ZRC_SYS_INFO_MISMATCH:
			DispMsg(ZXUT_MSG_INFO, "反馈的系统信息不全相同");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		case ZRC_INVALID_PCB_VER:
			DispMsg(ZXUT_MSG_INFO, "无效的PCB版本");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		case ZRC_INVALID_FPGA_VER:
			DispMsg(ZXUT_MSG_INFO, "无效的FPGA版本");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		case ZRC_INVALID_TOT_HARD:
			DispMsg(ZXUT_MSG_INFO, "无效的硬通道总数");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		case ZRC_INVALID_TOT_SOFT:
			DispMsg(ZXUT_MSG_INFO, "无效的软通道总数");
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;

		default:
			DispMsg(ZXUT_MSG_ERR, "打开网络探伤设备出现未知错误%d", ret_code);
			ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
			return FALSE;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 确认设备版本号是否匹配

#if 1

	if (m_pstExpInfo->m_nDevVer != ZXUT_DEV_VER)
	{
		DispMsg(ZXUT_MSG_ERR, "反馈的设备版本号不匹配，需要V%d.%d，实际：V%d.%d\n",
			ZXUT_DEV_VER / 256, ZXUT_DEV_VER % 256,
			m_pstExpInfo->m_nDevVer / 256, m_pstExpInfo->m_nDevVer % 256);
		ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
		return FALSE;
	}

#endif

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 确认中间件版本号是否匹配

#if 1

	if (m_pstExpInfo->m_nMidVer != ZXUT_MID_VER)
	{
		DispMsg(ZXUT_MSG_ERR, "反馈的中间件版本号不匹配，需要V%d.%d，实际：V%d.%d\n",
			ZXUT_MID_VER / 256, ZXUT_MID_VER % 256,
			m_pstExpInfo->m_nMidVer / 256, m_pstExpInfo->m_nMidVer % 256);
		ZXUT_CloseDevice(APP_EXIT_CMD_RETRY);
		return FALSE;
	}

#endif

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 依照设备类型，设置设备功能标志

	m_bPci = (m_nZxutType == ZXUT_TYPE_PCI);	// PCI设备

	m_bNet = (m_nZxutType == ZXUT_TYPE_NET);	// NET设备
	m_bNetP2 = m_bNet & (m_pstExpInfo->m_nInnerSync == BRD_SYNC_PARA);
	m_bNetS4 = m_bNet & (m_pstExpInfo->m_nInnerSync == BRD_SYNC_SERI);

	if (m_bNetP2)
	{
		m_bAngFltrEnb = TRUE;
		m_bBrdSyncEnb = FALSE;
		m_bDevUpdEnb = TRUE;
		strcpy(m_strZxutType, "NET-P2");
		BRD_NOACC_MAX_DWS = 0;
	}
	else if (m_bNetS4)
	{
		m_bAngFltrEnb = TRUE;
		m_bBrdSyncEnb = TRUE;
		m_bDevUpdEnb = TRUE;
		strcpy(m_strZxutType, "NET-S4");
		BRD_NOACC_MAX_DWS = BRD_NOACC_MAX_DWS_NETS4;
	}
	else if (m_bPci)
	{
		m_bAngFltrEnb = TRUE;
		m_bBrdSyncEnb = FALSE;
		m_bDevUpdEnb = FALSE;
		strcpy(m_strZxutType, "PCI-S4");
		BRD_NOACC_MAX_DWS = BRD_NOACC_MAX_DWS_PCIH7;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 设置Y方向参数

	U8 y_bw = m_pstExpInfo->m_nYBw;		// 12
	m_nSmplWaveHeight = (1 << y_bw);	// 4096
	m_nSmplWaveYRatio = m_nSmplWaveHeight / SHOW_SMPL_HEIGHT;	// 4096 / 512 = 8
	m_nAutoGainHeight = (U16)(0.8f * ((1 << y_bw) - 1));	// 自动增益高度: 80%

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新系统时序参数显示
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::UpdSysTiming(void)
{
	if (m_pDlgFlawParam != NULL)
	{
		m_pDlgFlawParam->UpdSmplTimes();	// 更新采样次数
		m_pDlgFlawParam->UpdAccTimes();		// 更新累积次数
		m_pDlgFlawParam->UpdDaqRate();		// 更新采集率
		m_pDlgFlawParam->UpdNetRate();		// 更新网络传输率
	}

	GetUpdProcEnd();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 1 重复频率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新重复频率

void CZxutApp::UpdRptFreq(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	U8& rf_idx = m_stFlawParam.m_nRfIdx;
	U8 bak = rf_idx;	// 保存旧的
	rf_idx = plvItem->cchTextMax;	// 获取新的
	U32 rpt_freq = RPT_FREQ_VALUE[rf_idx];

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(FALSE);	// 关闭采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	U8 err_hard_num, err_soft_num;
	ET_ZRC ret_code = ZXUT_SetRptFreq(rpt_freq, &err_hard_num, &err_soft_num);
	if (ret_code != ZRC_API_RET_SUCCESS)
	{
		switch (ret_code)
		{
		case ZRC_INVALID_RPT_FREQ:
			DispMsg(ZXUT_MSG_ERR, "超出重复频率范围[%d, %d]", RPT_FREQ_MIN, RPT_FREQ_MAX);
			break;

		case ZRC_NO_ENOUGH_CHAN_TIME:
			DispMsg(ZXUT_MSG_ERR, "%d-%d通道时间不够", err_hard_num + 1, err_soft_num + 1);
			break;

		default:
			DispMsg(ZXUT_MSG_ERR, "无效的错误返回码%d\n", ret_code);
			break;
		}

		rf_idx = bak;	// 恢复旧的
		pdlg->FreshRptFreq();
	}
	else
	{
		UpdSysTiming();	// 更新系统时序
	}

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(TRUE);	// 开启采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 找寻最接近当前的重复频率

void CZxutApp::FindNewRptFreq(void)
{
	BOOL find = FALSE;

	for (S8 i = m_stFlawParam.m_nRfIdx; i >= RF_IDX_MIN; i--)
	{
		m_stFlawParam.m_nRfIdx = i;
		U32 rpt_freq = RPT_FREQ_VALUE[m_stFlawParam.m_nRfIdx];
		if (ZXUT_SetRptFreq(rpt_freq, NULL, NULL) == 0)
		{
			find = TRUE;
			break;	// 已找到，退出
		}
	}

	if (find == FALSE)
	{
		DispMsg(ZXUT_MSG_ERR, "没有可设置的重复频率");	// 一个都没有找到
		return;
	}

	UpdSysTiming();	// 更新系统时序
	m_pFlawParamAdj->FreshRptFreq();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取最大重复频率

void CZxutApp::GetMaxRptFreq(void)
{
	U8& rf_idx = m_stFlawParam.m_nRfIdx;
	U8 bak = rf_idx;	// 保存旧的

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(FALSE);	// 关闭采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	U32 rpt_freq, max_rpt_freq = ZXUT_GetMaxRptFreq();
	BOOL find = FALSE;
	for (S8 i = RF_IDX_MAX; i >= RF_IDX_MIN; i--)
	{
		rpt_freq = RPT_FREQ_VALUE[i];
		if (rpt_freq <= max_rpt_freq)
		{
			find = TRUE;
			rf_idx = i;	// 获取匹配的重复频率
			break;
		}
	}

	if (find == TRUE)
	{
		CString str1, str2;
		if (max_rpt_freq >= 1000)
		{
			str1.Format("%d.%03dKHz", max_rpt_freq / 1000, max_rpt_freq % 1000);
		}
		else
		{
			str1.Format("%dHz", max_rpt_freq);
		}
		if (rpt_freq >= 1000)
		{
			str2.Format("%d.%03dKHz", rpt_freq / 1000, rpt_freq % 1000);
		}
		else
		{
			str2.Format("%dHz", rpt_freq);
		}
		DispMsg(ZXUT_MSG_INFO, "最大重复频率为%s\n匹配重复频率为%s\n", str1, str2);

		U8 err_hard_num, err_soft_num;
		ET_ZRC ret_code = ZXUT_SetRptFreq(rpt_freq, &err_hard_num, &err_soft_num);
		if (ret_code != ZRC_API_RET_SUCCESS)
		{
			switch (ret_code)
			{
			case ZRC_INVALID_RPT_FREQ:
				DispMsg(ZXUT_MSG_ERR, "超出重复频率范围[%d, %d]", RPT_FREQ_MIN, RPT_FREQ_MAX);
				break;

			case ZRC_NO_ENOUGH_CHAN_TIME:
				DispMsg(ZXUT_MSG_ERR, "%d-%d通道时间不够", err_hard_num + 1, err_soft_num + 1);
				break;

			default:
				DispMsg(ZXUT_MSG_ERR, "无效的错误返回码%d\n", ret_code);
				break;
			}

			rf_idx = bak;	// 恢复旧的
		}
		else
		{
			UpdSysTiming();	// 更新系统时序
			m_pFlawParamAdj->FreshRptFreq();
		}
	}
	else
	{
		DispMsg(ZXUT_MSG_ERR, "无匹配的重复频率%dHz", max_rpt_freq);
	}

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(TRUE);	// 开启采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 2 板间同步
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::UpdBrdSync(LV_ITEM* const plvItem)
{
	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(FALSE);	// 关闭采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	U8 brd_sync = plvItem->cchTextMax;
	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		ZXUT_SetBrdSync(i, brd_sync);	// 设置板间同步
	}

	FindNewRptFreq();	// 找寻最接近当前的重复频率

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(TRUE);	// 开启采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 3 通道使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CZxutApp::UpdChanEnb(CDlgChanEnb* pdlg)
{
	BOOL chan_enb[TOT_HARD_NUM][MAX_SOFT_NUM];
	memset(chan_enb, 0x00, sizeof(chan_enb));

	U8 tot_brd = m_pstExpInfo->m_nTotBrd;
	U8 tot_hard = m_pstExpInfo->m_nTotHard;
	U8 tot_soft = m_pstExpInfo->m_nTotSoft;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 主板至少使能一个通道，否则主板无同步脉冲输出

	BOOL find = FALSE;
	for (U8 i = 0; i < tot_brd; i++)
	{
		for (U8 j = 0; j < tot_hard; j++)
		{
			U8 hard_num = i * tot_hard + j;
			for (U8 k = 0; k < tot_soft; k++)
			{
				BOOL chk_sts = pdlg->m_chkChanEnb[hard_num][k].GetCheck();
				chan_enb[hard_num][k] = chk_sts;
				if (chk_sts && (i == 0))
				{
					find = TRUE;	// 主板至少有一个通道使能
				}
			}
		}
	}

	if (find == FALSE)
	{
		DispMsg(ZXUT_MSG_INFO, "主板至少需要一个通道使能！");
		return FALSE;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取当前设置的通道使能

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(FALSE);	// 关闭采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	BOOL old_enb[TOT_HARD_NUM][MAX_SOFT_NUM];
	memcpy(old_enb, m_stFlawParam.m_stCoreParam.m_abChanEnb, sizeof(old_enb));		// 保存旧的
	memcpy(m_stFlawParam.m_stCoreParam.m_abChanEnb, chan_enb, sizeof(chan_enb));	// 获取新的

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 采样深度是否超限

	for (U8 i = 0; i < tot_brd; i++)
	{
		U32 solo_brd_no_acc_dws = ZXUT_GetSoloBrdNoAccDaqDws(i);
		if (solo_brd_no_acc_dws > BRD_NOACC_MAX_DWS)
		{
			DispMsg(ZXUT_MSG_ERR, "当前单板无累积采集双字长度为%d，超出最大限制%d", solo_brd_no_acc_dws, BRD_NOACC_MAX_DWS);

			// 超限则恢复旧的通道使能设置
			memcpy(m_stFlawParam.m_stCoreParam.m_abChanEnb, old_enb, sizeof(old_enb));
			for (U8 i = 0; i < tot_brd; i++)
			{
				for (U8 j = 0; j < tot_hard; j++)
				{
					U8 hard_num = i * tot_hard + j;
					for (U8 k = 0; k < tot_soft; k++)
					{
						BOOL chk_sts = old_enb[hard_num][k];
						pdlg->m_chkChanEnb[hard_num][k].SetCheck(chk_sts);
					}
				}
			}

			if (m_bSmplEnb)
			{
				m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
				ZXUT_SetSmplEnb(TRUE);	// 开启采样
				m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
			}

			return FALSE;	// 超限返回
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////

	for (U8 i = 0; i < tot_brd; i++)
	{
		CString str;
		pdlg->m_edtSynDly[i].GetWindowText(str);
		m_stFlawParam.m_stCoreParam.m_anSynDly[i] = atoi(str);

		for (U8 j = 0; j < tot_hard; j++)
		{
			U8 hard_num = i * tot_hard + j;
			pdlg->m_edtChanShare[hard_num].GetWindowText(str);
			m_stFlawParam.m_anChanShare[hard_num] = atoi(str);

			for (U8 k = 0; k < tot_soft; k++)
			{
				m_stFlawParam.m_stCoreParam.m_anChanShare[hard_num][k] = m_stFlawParam.m_anChanShare[hard_num];
			}
		}
	}

	FindNewRptFreq();	// (1) 找寻最接近当前的重复频率
	SetFlawParam();		// (2) 重新设置探伤参数(特别是保证先前没有使能的通道参数必需设置)
	DispMsg(ZXUT_MSG_INFO, "通道使能已完成更新！");

	CreateLogChanTab();	// 创建逻辑通道表
	m_pFlawParamAdj->FreshFlawParam();

	if (m_bSmplEnb)
	{
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(FALSE);
		ZXUT_SetSmplEnb(TRUE);	// 开启采样
		m_pDlgZxut->m_btnSmplEnb.EnableWindow(TRUE);
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 4 采样深度
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::UpdSmplDepth(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	U8& sd_idx = m_stFlawParam.m_anSdIdx[m_nHardNum][m_nSoftNum];
	U8 bak = sd_idx;	// 保存旧的
	sd_idx = plvItem->cchTextMax;	// 获取新的
	U32 smpl_depth = m_anSmplDepthValue[sd_idx];

	U16 max_smpl_depth;
	U32 solo_brd_no_acc_dws;
	S32 ret_code = ZXUT_SetSmplDepth(m_nHardNum, m_nSoftNum, smpl_depth, &max_smpl_depth, &solo_brd_no_acc_dws);
	if (ret_code != 0)
	{
		switch (ret_code)
		{
		case ZRC_INVALID_SMPL_DEPTH:
			DispMsg(ZXUT_MSG_ERR, "超出采样深度范围[%d, %d]", SMPL_DEPTH_MIN, m_nSmplDepthMax);
			break;

		case ZRC_NO_ENOUGH_CHAN_TIME:
			DispMsg(ZXUT_MSG_ERR, "当前采样深度为%d，允许的最大采样深度为%d", m_anSmplDepthValue[sd_idx], max_smpl_depth);
			break;

		case ZRC_NO_ENOUGH_BRD_MEM:
			DispMsg(ZXUT_MSG_ERR, "当前单板单次累积双字长度为%d，超出最大限制%d", solo_brd_no_acc_dws, BRD_NOACC_MAX_DWS);
			break;

		default:
			DispMsg(ZXUT_MSG_ERR, "无效的返回值%d", ret_code);
			break;
		}

		sd_idx = bak;	// 恢复旧的
		pdlg->FreshSmplDepth();
		return;
	}

	// 采样深度改变了，需要更新闸门起点和闸门宽度
	ST_GATE_PARAM& gate_param = m_stFlawParam.m_astGateParam[m_nHardNum][m_nSoftNum];
	for (U8 p = 0; p < TOT_GATE_NUM; p++)
	{
		BOOL gate_enb = gate_param.m_bEnb[p];
		if (gate_enb)
		{
			ZXUT_SetGateStart(m_nHardNum, m_nSoftNum, p, gate_param.m_nStart[p] * smpl_depth / SHOW_SMPL_WIDTH);
			ZXUT_SetGateWidth(m_nHardNum, m_nSoftNum, p, gate_param.m_nWidth[p] * smpl_depth / SHOW_SMPL_WIDTH);
		}
	}

	pdlg->FreshFreqRatio();	// 影响检测范围，其实也影响闸门表示的范围，但在进行TAB切换进行了处理
	SetDataSwitch();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 5 零位偏移(ns)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新零位偏移

void CZxutApp::UpdOrigDly(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	S32 orig_dly = plvItem->cchTextMax * 10 + ORIG_DLY_MIN;		// 获取新的

	U32 max_orig_dly;
	S32 ret_code = ZXUT_SetOrigDly(m_nHardNum, m_nSoftNum, orig_dly, &max_orig_dly);
	if (ret_code == ZRC_NO_ENOUGH_CHAN_TIME)
	{
		DispMsg(ZXUT_MSG_ERR, "当前零位偏移为%.2fus，超出最大限制%.2fus", orig_dly * 0.001f, max_orig_dly * 0.001f);	// ns -> us
		pdlg->FreshOrigDly();
		return;
	}

	UpdSysTiming();	// 更新系统时序
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 按键调整零位偏移

void CZxutApp::KeyAdjOrigDly(U8 type)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	S32 orig_dly = core_param.m_anOrigDly[m_nHardNum][m_nSoftNum];

	switch (type)
	{
	case 0: if (orig_dly - 1000 < ORIG_DLY_MIN) { return; }
			else { orig_dly -= 1000; } break;	// -1us
	case 1: if (orig_dly - 10 < ORIG_DLY_MIN) { return; }
			else { orig_dly -= 10; } break;	// -10ns
	case 2: if (orig_dly + 1000 > ORIG_DLY_MAX) { return; }
			else { orig_dly += 1000; } break;	// +1us
	case 3: if (orig_dly + 10 > ORIG_DLY_MAX) { return; }
			else { orig_dly += 10; } break;	// +10ns
	}

	U32 max_orig_dly;
	S32 ret_code = ZXUT_SetOrigDly(m_nHardNum, m_nSoftNum, orig_dly, &max_orig_dly);
	if (ret_code == ZRC_NO_ENOUGH_CHAN_TIME)
	{
		DispMsg(ZXUT_MSG_ERR, "当前零位偏移为%.2fus，超出最大限制%.2fus", orig_dly * 0.001f, max_orig_dly * 0.001f);	// ns -> us
		return;
	}

	m_pFlawParamAdj->FreshOrigDly();
	UpdSysTiming();	// 更新系统时序
}

// +1us, Shift + F6
void CZxutApp::OnOrigDlyIncCorse(void)
{
	KeyAdjOrigDly(0);
}

// +10ns, F6
void CZxutApp::OnOrigDlyIncFine(void)
{
	KeyAdjOrigDly(1);
}

// -1us, Shift + F5
void CZxutApp::OnOrigDlyDecCorse(void)
{
	KeyAdjOrigDly(2);
}

// +1us, F5
void CZxutApp::OnOrigDlyDecFine(void)
{
	KeyAdjOrigDly(3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 6 分频比
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::UpdFreqRatio(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	U16 freq_ratio = plvItem->cchTextMax + 1;	// 获取新的

	U16 max_freq_ratio;
	S32 ret_code = ZXUT_SetFreqRatio(m_nHardNum, m_nSoftNum, freq_ratio, &max_freq_ratio);
	if (ret_code == ZRC_NO_ENOUGH_CHAN_TIME)
	{
		U16 smpl_depth = core_param.m_anSmplDepth[m_nHardNum][m_nSoftNum];
		U32 sound_velo = m_stFlawParam.m_anSoundVelo[m_nHardNum][m_nSoftNum];

		switch (m_stFlawParam.m_nHoriDisp)
		{
		case HORI_DISP_MM:		// mm
		{
			F32 range1 = ZXUT_GetTstRange(freq_ratio, smpl_depth, 0, sound_velo);
			F32 range2 = ZXUT_GetTstRange(max_freq_ratio, smpl_depth, 0, sound_velo);
			TRACE("%.2fmm\n", range2);
			DispMsg(ZXUT_MSG_ERR, "当前检测范围为%.2fmm，超出最大限制%.2fmm", range1, range2);
			break;
		}

		case HORI_DISP_US:		// us
		{
			F32 time1 = ZXUT_GetTstTime(freq_ratio, smpl_depth, 0) * 0.001f;		// ns -> us
			F32 time2 = ZXUT_GetTstTime(max_freq_ratio, smpl_depth, 0) * 0.001f;	// ns -> us
			DispMsg(ZXUT_MSG_ERR, "当前检测时间为%.2fus，超出最大限制%.2fus", time1, time2);
			break;
		}

		case HORI_DISP_DOTS:	// 点数
		{
			DispMsg(ZXUT_MSG_ERR, "当前分频比为%d，超出最大限制%d", freq_ratio, max_freq_ratio);
			break;
		}
		}

		pdlg->FreshFreqRatio();
		return;
	}

	UpdSysTiming();	// 更新系统时序
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 7 平均次数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::UpdAvgTimes(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	U8& at_idx = m_stFlawParam.m_anAtIdx[m_nHardNum][m_nSoftNum];
	U8 bak = at_idx;	// 保存旧的
	at_idx = plvItem->cchTextMax;	// 获取新的
	U8 avg_times = AVG_TIMES_VALUE[at_idx];

	U8 max_avg_times;
	S32 ret_code = ZXUT_SetAvgTimes(m_nHardNum, m_nSoftNum, avg_times, &max_avg_times);
	if (ret_code != 0)
	{
		switch (ret_code)
		{
			case ZRC_INVALID_AVG_TIMES:
				DispMsg(ZXUT_MSG_ERR, "当前平均次数%d非法，必需为1/2/4/8/16之一", AVG_TIMES_VALUE[at_idx]);
				break;

			case ZRC_NO_ENOUGH_CHAN_TIME:
				DispMsg(ZXUT_MSG_ERR, "当前平均次数为%d，超出最大限制%d", AVG_TIMES_VALUE[at_idx], max_avg_times);
				break;

			default:
				DispMsg(ZXUT_MSG_ERR, "未知的错误返回码%d", ret_code);
				break;
		}

		at_idx = bak;	// 新的无效，恢复旧的
		pdlg->FreshAvgTimes();
		return;
	}

	UpdSysTiming();	// 更新系统时序
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 8 采样波形 - 与通道时间无关，仅与系统时序有关
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::UpdSmplWave(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	BOOL smpl_wave = plvItem->cchTextMax;
	BOOL fft_wave = core_param.m_abFftWave[m_nHardNum][m_nSoftNum];
	BOOL cent_freq = core_param.m_abCentFreq[m_nHardNum][m_nSoftNum];
	ZXUT_SetDataSwitch(m_nHardNum, m_nSoftNum, smpl_wave, fft_wave, cent_freq);
	UpdSysTiming();	// 更新系统时序
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 9 FFT处理 - 与通道时间&系统时序均有关
//
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新FFT波形

void CZxutApp::UpdFftWave(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	BOOL smpl_wave = core_param.m_abSmplWave[m_nHardNum][m_nSoftNum];
	BOOL cent_freq = core_param.m_abCentFreq[m_nHardNum][m_nSoftNum];

	BOOL bak = core_param.m_abFftWave[m_nHardNum][m_nSoftNum];	// 保存旧的
	BOOL fft_wave;	// 获取新的
	if (plvItem == NULL)
	{
		fft_wave = m_pDlgFftProc->m_chkFftWave.GetCheck();
	}
	else
	{
		fft_wave = plvItem->cchTextMax;
	}

	ET_ZRC ret_code = ZXUT_SetDataSwitch(m_nHardNum, m_nSoftNum, smpl_wave, fft_wave, cent_freq);
	if (ret_code != ZRC_API_RET_SUCCESS)
	{
		switch (ret_code)
		{
		case ZRC_ZXUT_NOT_SUPPORT:
			DispMsg(ZXUT_MSG_ERR, "设备禁止开启FFT波形");
			break;

		case ZRC_FFT_DISABLE:
			DispMsg(ZXUT_MSG_ERR, "当前探伤参数禁止开启FFT波形");
			break;

		default:
			break;
		}

		// 新的无效，恢复旧的
		if (plvItem == NULL)
		{
			m_pDlgFftProc->m_chkFftWave.SetCheck(bak);
		}
		else
		{
			pdlg->FreshFftWave();
		}

		return;
	}

	UpdSysTiming();	// 更新系统时序
	FreshFftEnbCtrl();	// 刷新FFT使能控件
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新中心频率

void CZxutApp::UpdCentFreq(CFlawParamAdj* pdlg, LV_ITEM* const plvItem)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	BOOL smpl_wave = core_param.m_abSmplWave[m_nHardNum][m_nSoftNum];
	BOOL fft_wave = core_param.m_abFftWave[m_nHardNum][m_nSoftNum];

	BOOL bak = core_param.m_abCentFreq[m_nHardNum][m_nSoftNum];	// 保存旧的
	BOOL cent_freq;	// 获取新的
	if (plvItem == NULL)
	{
		cent_freq = m_pDlgFftProc->m_chkCentFreq.GetCheck();
	}
	else
	{
		cent_freq = plvItem->cchTextMax;
	}

	ET_ZRC ret_code = ZXUT_SetDataSwitch(m_nHardNum, m_nSoftNum, smpl_wave, fft_wave, cent_freq);
	if (ret_code != ZRC_API_RET_SUCCESS)
	{
		switch (ret_code)
		{
		case ZRC_ZXUT_NOT_SUPPORT:
			DispMsg(ZXUT_MSG_ERR, "设备禁止开启中心频率");
			break;

		case ZRC_FFT_DISABLE:
			DispMsg(ZXUT_MSG_ERR, "当前探伤参数禁止开启中心频率");
			break;

		default:
			break;
		}

		// 新的无效，恢复旧的
		if (plvItem == NULL)
		{
			m_pDlgFftProc->m_chkCentFreq.SetCheck(bak);
		}
		else
		{
			pdlg->FreshCentFreq();
		}

		return;
	}

	UpdSysTiming();	// 更新系统时序
	FreshFftEnbCtrl();	// 刷新FFT使能控件
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置数据开关 - 仅在改变“采样深度”或“检波模式”时调用

void CZxutApp::SetDataSwitch(void)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	U8 dem_mode = m_stFlawParam.m_anDemMode[m_nHardNum][m_nSoftNum];
	U16 smpl_depth = core_param.m_anSmplDepth[m_nHardNum][m_nSoftNum];
	BOOL smpl_wave = core_param.m_abSmplWave[m_nHardNum][m_nSoftNum];
	BOOL& fft_wave = core_param.m_abFftWave[m_nHardNum][m_nSoftNum];
	BOOL& cent_freq = core_param.m_abCentFreq[m_nHardNum][m_nSoftNum];

	if ((dem_mode == DEM_MODE_RF) && (smpl_depth == FFT_IN_DOTS))
	{
	}
	else
	{
		// 不满足条件，强制设置禁止
		fft_wave = FALSE;
		cent_freq = FALSE;
	}

	UpdSysTiming();	// 更新系统时序
	FreshFftEnbCtrl();	// 刷新FFT使能控件
	ZXUT_SetDataSwitch(m_nHardNum, m_nSoftNum, smpl_wave, fft_wave, cent_freq);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 刷新FFT使能控件(仅涉及fft_wave & cent_freq)

void CZxutApp::FreshFftEnbCtrl(void)
{
	ST_CORE_PARAM& core_param = m_stFlawParam.m_stCoreParam;
	U8 dem_mode = m_stFlawParam.m_anDemMode[m_nHardNum][m_nSoftNum];
	U16 smpl_depth = core_param.m_anSmplDepth[m_nHardNum][m_nSoftNum];
	BOOL fft_enb = (dem_mode == DEM_MODE_RF) && (smpl_depth == FFT_IN_DOTS);

	if (m_pDlgFftProc != NULL)
	{
		m_pDlgFftProc->m_chkFftWave.EnableWindow(fft_enb);
		m_pDlgFftProc->m_chkCentFreq.EnableWindow(fft_enb);

		BOOL fft_wave = core_param.m_abFftWave[m_nHardNum][m_nSoftNum];
		m_pDlgFftProc->m_chkFftWave.SetCheck(fft_wave);

		BOOL cent_freq = core_param.m_abCentFreq[m_nHardNum][m_nSoftNum];
		m_pDlgFftProc->m_chkCentFreq.SetCheck(cent_freq);
	}

	m_pFlawParamAdj->FreshFftWave();
	m_pFlawParamAdj->FreshCentFreq();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 刷新板卡信息
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CZxutApp::FreshBrdInfo(CDlgBrdInfo* pdlg)
{
	CString str;
	for (U8 i = 0; i < m_pstExpInfo->m_nTotBrd; i++)
	{
		if (m_bNet)
		{
			U8 p = m_anBrdIdx[i];
			str.Format("%d.%d.%d.%d",
				m_stFlawParam.m_anIpAddr[0],
				m_stFlawParam.m_anIpAddr[1],
				m_stFlawParam.m_anIpAddr[2],
				m_stFlawParam.m_anIpAddr[3] + p);
			pdlg->m_txtIpAddr[i].SetWindowText(str);	// IP地址

			str.Format("%02X:%02X:%02X:%02X:%02X:%02X",
				m_pstExpInfo->m_anMacAddr[i][0],
				m_pstExpInfo->m_anMacAddr[i][1],
				m_pstExpInfo->m_anMacAddr[i][2],
				m_pstExpInfo->m_anMacAddr[i][3],
				m_pstExpInfo->m_anMacAddr[i][4],
				m_pstExpInfo->m_anMacAddr[i][5]);
			pdlg->m_txtMacAddr[i].SetWindowText(str);	// MAC地址
		}

		if (m_bPci)
		{
			str.Format("%s", m_pstExpInfo->m_aastrBrdSn[i][0]);
			pdlg->m_txtBrdSn[i][BRD_SN_TYPE_CHAN].SetWindowText(str);	// 只有1个板号，即通道板
		}
		else
		{
			for (U8 j = 0; j < BRD_SN_TYPE_NUM; j++)
			{
				str.Format("%s", m_pstExpInfo->m_aastrBrdSn[i][j]);
				pdlg->m_txtBrdSn[i][j].SetWindowText(str);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 创建套接字
//
////////////////////////////////////////////////////////////////////////////////////////////////////

ET_ZRC CZxutApp::CreateSocket(void)
{
	int iResult;
	sockaddr_in	addrServer;

	// 建立流式Socket
	m_sockOrig = socket(AF_INET, SOCK_STREAM, 0);
	if (ZRC_INVALID_SOCKET == m_sockOrig)
	{
		return ZRC_CREATE_SOCKET_FAIL;	// 创建TCP套接字失败
	}

	// 设置服务器地址信息
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	addrServer.sin_port = htons(m_stFlawParam.m_nNetPort);

	// 绑定服务器地址和端口。若成功，返回零
	iResult = bind(m_sockOrig, (LPSOCKADDR)&addrServer, sizeof(addrServer));
	if (iResult != 0)
	{
		closesocket(m_sockOrig);	// 关闭未连接套接字
		return ZRC_BIND_SERVER_FAIL;	// 绑定服务器地址和端口失败
	}

	// 让服务器的Socket进行监听。若成功设置成监听状态，返回零
	iResult = listen(m_sockOrig, 1);
	if (iResult != 0)
	{
		closesocket(m_sockOrig);	// 关闭未连接套接字
		return ZRC_LISTEN_SERVER_FAIL;	// 服务器监听失败
	}

	return ZRC_API_RET_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 打开NET探伤设备

ET_ZRC CZxutApp::OpenNetDev(void)
{
	// 创建网络通讯套接字
	ET_ZRC ret_code = CreateSocket();
	if (ret_code < 0)
	{
		return ret_code;
	}

	m_pThrdListen = AfxBeginThread(pfnThrdListen, (LPVOID)this,
		THREAD_PRIORITY_LOWEST, 0, 0);	// 最低优先级

	CDlgWaitCnnct dlg;
	if (dlg.DoModal() == IDCANCEL)
	{
		m_bDlgWaitOk = FALSE;
		return ZRC_USR_CANCEL_CONNECT;	// 用户取消连接
	}
	else
	{
		if (m_nTotBrd == 0)
		{
			return ZRC_NO_CLIENT_CONNECT;	// 一个客户端都没有连接
		}

		// 对插入通道板的板号进行冒泡法排序(按照从小到大的顺序)
		for (U8 j = 0; j < m_nTotBrd - 1; j++)
		{
			for (U8 i = 0; i < m_nTotBrd - 1 - j; i++)
			{
				if (m_anBrdIdx[i] > m_anBrdIdx[i + 1])
				{
					// 相邻两个数比较(升序)
					U8 tmp = m_anBrdIdx[i];
					m_anBrdIdx[i] = m_anBrdIdx[i + 1];
					m_anBrdIdx[i + 1] = tmp;
				}
			}
		}

		if (m_anBrdIdx[0] != 0)
		{
			return ZRC_NO_MAST_BRD;	// 没有插入主通道板(左边第一个槽位)
		}

		SOCKET tmp[MAX_BRD_NUM];
		memcpy((void*)tmp, (void*)m_sockZxut, sizeof(tmp));	// 保存套接字
		for (U8 i = 0; i < m_nTotBrd; i++)
		{
			U8 brd_num = m_anBrdIdx[i];
			m_sockZxut[i] = tmp[brd_num];	// 重排套接字
		}

		return ZRC_API_RET_SUCCESS;	// 没有任何错误
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 服务器监听线程
//
////////////////////////////////////////////////////////////////////////////////////////////////////

UINT CZxutApp::pfnThrdListen(LPVOID lpParam)
{
	CZxutApp* This = reinterpret_cast<CZxutApp*>(lpParam);
	return This->ThrdListenHandler();
}

UINT CZxutApp::ThrdListenHandler(void)
{
	while (m_bDlgWaitOk == FALSE)
	{
		Sleep(10);	// 等待，直到对话框被真正建立
	}

	SOCKET			sockNew;
	sockaddr_in		addrClient[MAX_BRD_NUM];
	int				iAddrLen = sizeof(struct sockaddr);
	CString			strClientIpAddr;	// 刚刚建立连接的客户IP地址

	while (1)
	{
		sockNew = accept(m_sockOrig, (struct sockaddr FAR *)&addrClient[m_nTotBrd], &iAddrLen);
		if (sockNew == ZRC_INVALID_SOCKET)
		{
			DispMsg(ZXUT_MSG_ERR, "接收客户机连接错误: %s", GetLastError());
			break;
		}

		if (m_bDlgWaitOk == FALSE)
		{
			break;	// 若等待对话框已退出，则取消监听
		}

		// 获取客户的IP地址
		strClientIpAddr = inet_ntoa(addrClient[m_nTotBrd].sin_addr);
		U8 brd_num = addrClient[m_nTotBrd].sin_addr.S_un.S_un_b.s_b4 - (U8)(m_nClientIpAddr & 0xff);	// 获取板号

		m_sockZxut[brd_num] = sockNew;
		m_anBrdIdx[m_nTotBrd] = brd_num;
		m_nTotBrd++;
		CString msg;
		msg.Format("%s 连接成功!", strClientIpAddr);
		m_pdlgWaitCnnct->SetDlgItemText(IDC_CONNECT_STS[brd_num], msg);

		// 所有指定的客户连接完成，结束监听线程
		if (m_stFlawParam.m_nNeedBrdNum == m_nTotBrd)
		{
			m_bIsClientCnncted = TRUE;
			break;
		}
	}

	closesocket(m_sockOrig);	// 关闭未连接套接字

	return 0;
}
