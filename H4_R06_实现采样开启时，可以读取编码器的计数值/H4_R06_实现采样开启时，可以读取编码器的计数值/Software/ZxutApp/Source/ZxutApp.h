#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#ifdef WIN_X64
	#ifdef _DEBUG
		#pragma comment(lib, "../Product/64/Debug/ZxutMid.lib")
	#else
		#pragma comment(lib, "../Product/64/Release/ZxutMid.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(lib, "../Product/32/Debug/ZxutMid.lib")
	#else
		#pragma comment(lib, "../Product/32/Release/ZxutMid.lib")
	#endif
#endif

#pragma comment(lib, "Version.lib")

#include "resource.h"		// 主符号
#include "ZxutExp.h"
#include "DataProcThrd.h"
#include "DataShowThrd.h"

class CZxutDlg;
class CSmplShow;
class CFftShow;
class CFlawParamAdj;
class CFlawGateAdj;
class CDlgWaitCnnct;

class CDlgFlawParam;
class CDlgFlawGate;
class CDlgTcgProc;
class CDlgEncModu;
class CDlgDigIn;
class CDlgDigOut;
class CDlgFftProc;
class CDlgChanEnb;
class CDlgSysSetting;
class CDlgDevUpd;
class CDlgBrdInfo;

const char FLAW_PARAM_FILE_NAME[] = "FlawParam.zxut";	// 探伤参数文件名

#define ITEM_BACKGRD_COLOR	RGB(240, 240, 240)	// 背景，浅灰色
#define ITEM_DISABLED_COLOR	RGB(255, 255, 0)	// 禁止，黄色

////////////////////////////////////////////////////////////////////////////////////////////////////
// 消息类型

const U32 ZXUT_MSG_ASK		= 0x00;			// 询问
const U32 ZXUT_MSG_ERR		= 0x01;			// 错误
const U32 ZXUT_MSG_WARNING	= 0x02;			// 警告
const U32 ZXUT_MSG_INFO		= 0x03;			// 提示

////////////////////////////////////////////////////////////////////////////////////////////////////
// 波形显示窗口

const U16 SHOW_SMPL_WIDTH	= 1024;		// 采样波形宽度
const U16 SHOW_SMPL_HEIGHT	= 512;		// 采样波形高度

const U16 SHOW_FFT_WIDTH	= 512;		// FFT波形宽度
const U16 SHOW_FFT_HEIGHT	= 180;		// FFT波形高度

const U16 FFT_CURVE_LEN		= 305;		// FFT曲线长度

#include "FlawParamDef.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CZxutApp类定义
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class CZxutApp : public CWinAppEx
{
public:
	CZxutApp(void);
	~CZxutApp(void);

	virtual BOOL InitInstance(void);
	virtual int ExitInstance(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	S32	DispMsg(U8 nMsgType, const char *fmt, ...);		// 依据字符串，显示信息

	char m_strSoftPlat[100];	// 软件平台: 32/64, Debug/Release

	CZxutDlg*		m_pDlgZxut;
	CFlawParamAdj*	m_pFlawParamAdj;
	CFlawGateAdj*	m_pFlawGateAdj;
	CSmplShow*		m_pSmplShow;
	CFftShow*		m_pFftShow;

	CDlgWaitCnnct*	m_pdlgWaitCnnct;
	CDlgFlawParam*	m_pDlgFlawParam;
	CDlgFlawGate*	m_pDlgFlawGate;
	CDlgDigIn*		m_pDlgDigIn;
	CDlgDigOut*		m_pDlgDigOut;
	CDlgEncModu*	m_pDlgEncModu;
	CDlgTcgProc*	m_pDlgTcgProc;
	CDlgSysSetting* m_pDlgSysSetting;
	CDlgFftProc*	m_pDlgFftProc;
	CDlgDevUpd*		m_pDlgDevUpd;

	ST_EXP_INFO*	m_pstExpInfo;

	HACCEL m_hAcc;	// 快捷键

	U8 m_nAppExitCmd;			// 退出时发送给客户的命令码

	HANDLE m_hAppOpenMutex;		// 应用程序打开互斥量
	BOOL m_bAppOpenMutex;		// TRUE，二次打开应用程序

	void ExportWaveData(void);	// 导出波形数据
	void TstUsrReg(void);		// 测试用户寄存器

	U32 m_nEabCntr[TOT_ENC_NUM];
	U32 m_nEzCntr[TOT_ENC_NUM];

	BOOL m_bSmplEnb;
	void SetSmplEnb(void);		// 设置采样使能

	void FreshBrdInfo(CDlgBrdInfo* pdlg);	// 刷新板卡信息

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 闸门调节
	//
	////////////////////////////////////////////////////////////////////////////////////////////////

	U16 m_nSmplWaveHeight;	// 采样波形高度(2^12=4096)
	U16 m_nSmplWaveYRatio;

	BOOL LmtGateParamAdj(U8 nGateIdx);	// 限制闸门参数调节

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门BCI使能

	afx_msg void OnGbEnb(void);
	afx_msg void OnGcEnb(void);
	afx_msg void OnGiEnb(void);

	void AdjGateEnb(U8 nGateIdx);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门起点

	void AdjGateStart(U8 nGateIdx, BOOL bAdjDec, U8 nAdjGrain);

	afx_msg void OnGaStartDecFine(void);
	afx_msg void OnGaStartDecCoarse(void);
	afx_msg void OnGaStartIncFine(void);
	afx_msg void OnGaStartIncCoarse(void);

	afx_msg void OnGbStartDecFine(void);
	afx_msg void OnGbStartDecCoarse(void);
	afx_msg void OnGbStartIncFine(void);
	afx_msg void OnGbStartIncCoarse(void);

	afx_msg void OnGcStartDecFine(void);
	afx_msg void OnGcStartDecCoarse(void);
	afx_msg void OnGcStartIncFine(void);
	afx_msg void OnGcStartIncCoarse(void);

	afx_msg void OnGiStartDecFine(void);
	afx_msg void OnGiStartDecCoarse(void);
	afx_msg void OnGiStartIncFine(void);
	afx_msg void OnGiStartIncCoarse(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门宽度

	void AdjGateWidth(U8 nGateIdx, BOOL bAdjDec, U8 nAdjGrain);

	afx_msg void OnGaWidthDecFine(void);
	afx_msg void OnGaWidthDecCoarse(void);
	afx_msg void OnGaWidthIncFine(void);
	afx_msg void OnGaWidthIncCoarse(void);

	afx_msg void OnGbWidthDecFine(void);
	afx_msg void OnGbWidthDecCoarse(void);
	afx_msg void OnGbWidthIncFine(void);
	afx_msg void OnGbWidthIncCoarse(void);

	afx_msg void OnGcWidthDecFine(void);
	afx_msg void OnGcWidthDecCoarse(void);
	afx_msg void OnGcWidthIncFine(void);
	afx_msg void OnGcWidthIncCoarse(void);

	afx_msg void OnGiWidthDecFine(void);
	afx_msg void OnGiWidthDecCoarse(void);
	afx_msg void OnGiWidthIncFine(void);
	afx_msg void OnGiWidthIncCoarse(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 闸门高度

	void AdjGateHeight(U8 nGateIdx, BOOL bAdjDec, U8 nAdjGrain);

	afx_msg void OnGaHeightDecFine(void);
	afx_msg void OnGaHeightDecCoarse(void);
	afx_msg void OnGaHeightIncFine(void);
	afx_msg void OnGaHeightIncCoarse(void);

	afx_msg void OnGbHeightDecFine(void);
	afx_msg void OnGbHeightDecCoarse(void);
	afx_msg void OnGbHeightIncFine(void);
	afx_msg void OnGbHeightIncCoarse(void);

	afx_msg void OnGcHeightDecFine(void);
	afx_msg void OnGcHeightDecCoarse(void);
	afx_msg void OnGcHeightIncFine(void);
	afx_msg void OnGcHeightIncCoarse(void);

	afx_msg void OnGiHeightDecFine(void);
	afx_msg void OnGiHeightDecCoarse(void);
	afx_msg void OnGiHeightIncFine(void);
	afx_msg void OnGiHeightIncCoarse(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 扫频

	BOOL m_bScanFreq;			// 扫频使能
	FILE* m_fpFreqBand;			// 频带分析文件

	U8 m_anFftCurve[512];		// FFT曲线

	U8 m_anBwCurve[512];		// BW曲线
	U8 m_anBwLockCurve[512];	// BW锁定曲线

	U16 m_anBwData[512];		// BW数据
	U16 m_anBwLockData[512];	// BW锁定数据

	U16 m_nBwMaxData;
	U8 m_nBwMaxCurve;
	U16 m_nBwLeftIdx;
	U16 m_nBwMaxIdx;
	U16 m_nBwRightIdx;

	BOOL m_bLockBw;			// 频带锁定
	void LockBwCurve(void);
	void AnalyzeBwCure(void);

	F32 m_fFreqLeft;	// 左-3dB
	F32 m_fFreqCent;	// 中心频率
	F32 m_fFreqRight;	// 右-3dB
	F32 m_fFreqMax;		// 最大频率

	void ClrFftRes(void);		// 清除FFT结果

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 判伤结果更新

	U32 m_nUpdProcCntr[TOT_GATE_NUM];
	U32 m_nUpdProcEnd;		// 根据刷新率计算得到的终值
	void GetUpdProcEnd(void);

	ST_GATE_RES m_stGateRes[TOT_GATE_NUM];	// 闸门判伤结果

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 频率参考线

	afx_msg void OnFreqRefLineDecCoarse(void);
	afx_msg void OnFreqRefLineDecFine(void);
	afx_msg void OnFreqRefLineIncCoarse(void);
	afx_msg void OnFreqRefLineIncFine(void);

	void FreezeUpdFreqRefLine(void);	// 波形冻结时更新频率参考线

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 温度处理

	F32 m_fCpuTempValue[MAX_BRD_NUM];	// 核心板上CPU温度值
	F32 m_fPcbTempValue[MAX_BRD_NUM];	// 载板PCB温度值

	F32 m_fAvgCpuTemp, m_fAvgPcbTemp;	// 当前板卡平均后的CPU和PCB温度

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 包络

	BOOL m_bEnvlpEnb;					// 使能
	U16 m_anEnvlpBuf[SMPL_DEPTH_MAX];	// 缓冲区

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 用于求两个闸门之间的声程差

	F32 m_fGateDfctXInfo;	// 伤波闸门X信息
	F32 m_fGateBttmXInfo;	// 底波闸门X信息

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 当前通道

	ST_LOG_CHAN m_stLogChan;	// 逻辑通道

	U8 m_nHardNum;	// 当前硬编号
	U8 m_nSoftNum;	// 当前硬通道对应的软编号

	void CreateLogChanTab(void);	// 创建逻辑通道表
	void SetCrrntChan(void);

	afx_msg void OnChanInc(void);	// +通道
	afx_msg void OnChanDec(void);	// -通道
	void UpdChanNum(void);	// 更新通道编号

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 增益调节

	afx_msg void OnGainIncCoarse(void);	// +2dB
	afx_msg void OnGainDecCoarse(void);	// -2dB

	afx_msg void OnGainIncFine(void);	// +0.1dB
	afx_msg void OnGainDecFine(void);	// -0.1dB

	BOOL m_bDacCalib;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 自动增益

	BOOL m_bAutoGain;		// 标志
	U16 m_nAutoGainCntr;	// 处理间隔
	U16 m_nAutoGainHeight;	// 自动增益高度
	void GenAuotoGain(void);
	void ProcAutoGain(void);

	afx_msg void OnAutoGain(void);		// 自动增益

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 获取文件信息

	CString m_strAppName;	// 产品名称
	CString m_strAppVer;	// 产品版本
	void GetFileInfo(const char* strFile, CString& strName, CString& strVer);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 测量垂直线性线程

	CWinThread* m_pThrdTstVertLinear;
	static UINT pfnThrdTstVertLinear(LPVOID lpParam);
	UINT ThrdTstVertLinearHandler(void);
	void TstVertLinear(void);

	U16 m_nAvgWaveHeight;	// 平均处理之后的闸门A内的波高

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 数据处理线程

	CDataProcThrd* m_pDataProcThrd/*[MAX_BRD_NUM]*/;
	void CreateDataProcThrd(void);		// 创建数据处理线程
	void KillDataProcThrd(void);		// 杀死数据处理线程
	void ThrdDataProcHandler(void/*const U8 nBrdNum*/);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 数据显示线程

	CDataShowThrd* m_pDataShowThrd;
	void CreateDataShowThrd(void);
	void KillDataShowThrd(void);
	void ThrdDataShowHandler(void);

//	ST_RQ_DATA m_stRqData[1/*MAX_BRD_NUM*/][100/*LMT_RQ_NUM*/];
	ST_RQ_DATA m_stRqData[1/*MAX_BRD_NUM*/][1000/*LMT_RQ_NUM*/];
	BOOL m_bRqDataUpd[MAX_BRD_NUM];	// 更新了环形队列
	ST_RQ_DATA m_stRqShow;	// 当前显示的环形队列数据

	BOOL m_bDataProc;	// 当前通道数据正被处理

	HWND m_hSmplShowWnd;	// 采样显示窗口句柄
	HWND m_hFftShowWnd;		// FFT显示窗口句柄

	U16 m_anSmplBuf[SMPL_DEPTH_MAX];	// 采样波形缓冲区

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 设备初始化

	BOOL InitDevice(void);	// 初始化探伤设备
	BOOL OpenDevice(void);	// 打开探伤设备(确定已连接客户数)

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 设备类型(P2: 板内2个通道并行; S4: 板内4个通道串行)

	U8 m_nZxutType;
	char m_strZxutType[100];

	BOOL m_bPci;	// PCI设备, 皆为S4

	BOOL m_bNet;	// NET设备, 皆基于Xilinx FPGA
	BOOL m_bNetP2;	// P2版本
	BOOL m_bNetS4;	// S4版本

	BOOL m_bAngFltrEnb;	// 模拟滤波使能
	BOOL m_bBrdSyncEnb;	// 板间同步使能
	BOOL m_bDevUpdEnb;	// 设备更新使能

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 探伤参数

	ST_FLAW_PARAM m_stFlawParam;	// 探伤参数

	void InitFlawParam(void);		// 初始化探伤参数
	void RdFlawParam(void);			// 读探伤参数
	void WrFlawParam(void);			// 写探伤参数
	void SyncFlawParam(void);		// 同步探伤参数
	void SetFlawParam(void);		// 设置探伤参数

	void SetDiParam(void);			// 设置DI参数
	void SetDoParam(void);			// 设置DO参数
	void SetEncParam(void);			// 设置ENC参数

	void RdBrdSn(U8 nBrdSnType);	// 读取指定板号
	void WrBrdSn(U8 nBrdSnType);	// 写入指定板号

	U32 BRD_NOACC_MAX_DWS;	// 板内所有通道的数据量双字限制(单次累积)

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 核心参数(ST_CORE_PARAM)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////

	void UpdSysTiming(void);	// 更新系统时序参数显示

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 1 重复频率

	void UpdRptFreq(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);
	void FindNewRptFreq(void);		// 找寻新的重复频率
	void GetMaxRptFreq(void);	// 获取最大重复频率

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 2 板间同步

	void UpdBrdSync(LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 3 通道使能

	BOOL UpdChanEnb(CDlgChanEnb* pdlg);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 4 采样深度

	U8 m_nSmplDepthNum;
	U16 m_anSmplDepthValue[32];
	U16 m_nSmplDepthMax;
	char m_asSmplDepthStr[32][10];
	void GenSmplDepthMenu(void);

	void UpdSmplDepth(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 5 零位偏移

	void UpdOrigDly(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 6 分频比

	void UpdFreqRatio(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 7 平均次数

	void UpdAvgTimes(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 8 采样波形

	void UpdSmplWave(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 9 FFT处理

	void UpdFftWave(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);	// FFT波形
	void UpdCentFreq(CFlawParamAdj* pdlg, LV_ITEM* const plvItem);	// 中心频率
	void FreshFftEnbCtrl(void);	// 刷新FFT使能控件
	void SetDataSwitch(void);	// 设置数据开关

	ST_COMP_NUM m_astFftData[FFT_IN_DOTS];	// FFT输入和输出

	void ProcFftData(ST_DAQ_DATA& acc_buf);	// 处理FFT数据

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 按键调整零位偏移

	void KeyAdjOrigDly(U8 type);

	afx_msg void OnOrigDlyIncCorse(void);	// 粗调+
	afx_msg void OnOrigDlyIncFine(void);	// 精调+
	afx_msg void OnOrigDlyDecCorse(void);	// 粗调-
	afx_msg void OnOrigDlyDecFine(void);	// 精调-

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 创建网络连接

	U8 m_nTotBrd;	// 连接的板卡总数
	U8 m_anBrdIdx[MAX_BRD_NUM];	// 包含连接板卡的板号

	U32 m_nClientIpAddr;	// 客户端IP首地址
	SOCKET m_sockOrig;		// 未连接套接字
	SOCKET m_sockZxut[MAX_BRD_NUM];	// 已连接客户机的套接字
	ET_ZRC CreateSocket(void);	// 创建套接字
	ET_ZRC OpenNetDev(void);	// 打开NET探伤设备

	// 监听客户机线程
	CWinThread* m_pThrdListen;
	static UINT pfnThrdListen(LPVOID lpParam);
	UINT ThrdListenHandler(void);

	BOOL m_bIsClientCnncted;	// 客户机连接上了吗?
	BOOL m_bDlgWaitOk;

	BOOL m_bRtMemEnb;

	DECLARE_MESSAGE_MAP()
};

extern CZxutApp theApp;
