#ifndef __ZXUT_EXP_H__
#define __ZXUT_EXP_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 特别注意：
//
//		为了提高参数设置的效率，并没有在中间件中对输入参数的有效性(即满足最小值和最大值的条件)
//		进行检查。使用该中间件的程序员必须自行确保调用函数的输入参数是有效的。对于无效的输入参数
//		调用，其函数执行的结果是不可预知的。可能什么也没有影响，也可能对系统的稳定性产生消极影响，
//		在严重的极限情况下，甚至可能导致系统复位或者死机。
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ZxutCmn.h"	// 包含基本数据类型

#define ZXUT_MID_VER	((2 << 8) + (7))	// 设备版本(16位：高8位为主版本号；低8位为次版本号)

////////////////////////////////////////////////////////////////////////////////////////////////////
// API函数返回码(Zxut Return Code, ZRC)

typedef enum _ET_ZRC
{
	ZRC_API_RET_SUCCESS				= 0,		// API函数返回成功

	ZRC_INVALID_ZXUT_TYPE			= -1,		// 无效的设备类型(既不是PCI设备，也不是NET设备)
	ZRC_ZXUT_NOT_SUPPORT			= -2,		// 设备不支持该参数
	ZRC_NOT_ZXUT_PROVIDER			= -3,		// 不是设备供应商，不能调用该API函数
	ZRC_NO_BRD_INSERT				= -4,		// 没有通道板插入
	ZRC_NO_MAST_BRD					= -5,		// 没有插入主通道板(左边第一个槽位)
	ZRC_SYS_INFO_MISMATCH			= -6,		// 反馈的系统信息不全相同
	ZRC_INVALID_BRD_NUM				= -7,		// 无效的板号
	ZRC_INVALID_HARD_NUM			= -8,		// 无效的硬通道号
	ZRC_INVALID_SOFT_NUM			= -9,		// 无效的软通道号
	ZRC_INVALID_NEED_BRD_NUM		= -10,		// 无效的需要板卡数
	ZRC_INVALID_APP_EXIT_CMD		= -11,		// 无效的程序退出码
	ZRC_PCI_IOCTL_FAIL				= -12,		// PCI设备IOCTL失败
	ZRC_INVALID_PCB_VER				= -13,		// 无效的PCB版本
	ZRC_INVALID_FPGA_VER			= -14,		// 无效的FPGA版本
	ZRC_INVALID_TOT_HARD			= -15,		// 无效的硬通道总数
	ZRC_INVALID_TOT_SOFT			= -16,		// 无效的软通道总数

	// 网络通讯及连接
	ZRC_INVALID_SOCKET				= -100,		// 无效的套接字
	ZRC_NO_PROC_DATA				= -101,		// 无处理数据
	ZRC_SOCKET_ERR					= -102,		// 套接字错误
	ZRC_BYTE_NUM_MISMATCH			= -103,		// 字节数不相匹配
	ZRC_CREATE_SOCKET_FAIL			= -104,		// 创建TCP套接字失败
	ZRC_BIND_SERVER_FAIL			= -105,		// 绑定服务器地址和端口失败
	ZRC_LISTEN_SERVER_FAIL			= -106,		// 监听服务器失败
	ZRC_USR_CANCEL_CONNECT			= -107,		// 用户取消连接
	ZRC_NO_CLIENT_CONNECT			= -108,		// 一个客户端都没有连接

	// 板号
	ZRC_INVALID_BRD_SN_TYPE			= -200,		// 无效的板号类型
	ZRC_INVALID_BRD_SN_LEN			= -201,		// 无效的板号长度，应该为10位
	ZRC_BRD_SN_NOT_NUM				= -202,		// 板号不是数字
	ZRC_BRD_SN_WR_FAIL				= -203,		// 板号写失败

	// 实时存储
	ZRC_RT_CREATE_FILE_FAIL			= -250,		// 创建实时存储文件失败
	ZRC_RT_CREATE_FILE_MAP_FAIL		= -251,		// 创建实时存储文件映射失败
	ZRC_RT_NO_ENOUGH_MEM			= -252,		// 实时存储内存不足
	ZRC_RT_MAP_FILE_VIEW_FAIL		= -253,		// 映射实时存储文件视图失败

	// DIO
	ZRC_INVALID_DI_CHAN				= -300,		// 无效的DI通道
	ZRC_INVALID_DO_CHAN				= -301,		// 无效的DO通道
	ZRC_INVALID_DIO_MODE			= -302,		// 无效的DIO模式
	ZRC_INVALID_DI_TST_FREQ			= -303,		// 无效的DI测试频率
	ZRC_INVALID_DI_TST_WIDTH		= -304,		// 无效的DI测试宽度

	// ENC
	ZRC_INVALID_ENC_CHAN			= -400,		// 无效的ENC通道
	ZRC_INVALID_ENC_TYPE			= -401,		// 无效的ENC类型
	ZRC_INVALID_ENC_FLTR			= -402,		// 无效的ENC滤波
	ZRC_INVALID_ENC_TST_MODE		= -420,		// 无效的ENC测试模式
	ZRC_INVALID_ENC_TST_FREQ		= -421,		// 无效的ENC测试频率
	ZRC_INVALID_ENC_TST_PUL_NUM		= -422,		// 无效的ENC测试脉冲数
	ZRC_INVALID_ENC_TST_LINE_NUM	= -423,		// 无效的ENC测试线数

	// 探伤参数
	ZRC_INVALID_TRANS_VOL			= -500,		// 无效的发射电压
	ZRC_INVALID_TRIG_MODE			= -501,		// 无效的触发模式
	ZRC_INVALID_POL_DEF				= -502,		// 无效的极性定义
	ZRC_INVALID_SCAN_SPAN			= -503,		// 无效的扫查间隔
	ZRC_INVALID_BRD_SYNC			= -504,		// 无效的板间同步
	ZRC_INVALID_RPT_FREQ			= -505,		// 无效的重复频率
	ZRC_INVALID_RT_MODE				= -506,		// 无效的收发模式
	ZRC_INVALID_SMPL_TIMES			= -507,		// 无效的采样次数
	ZRC_INVALID_ACC_TIMES			= -508,		// 无效的累积次数
	ZRC_INVALID_DEM_MODE			= -509,		// 无效的检波模式
	ZRC_INVALID_DB_NUM				= -510,		// 无效的dB数值
	ZRC_INVALID_PUL_WIDTH			= -512,		// 无效的脉冲宽度
	ZRC_INVALID_PUL_NUM				= -513,		// 无效的脉冲个数
	ZRC_INVALID_GATE_SEL			= -514,		// 无效的闸门选择
	ZRC_INVALID_ECHO_MODE			= -515,		// 无效的回波模式
	ZRC_INVALID_SMPL_DEPTH			= -516,		// 无效的采样深度
	ZRC_INVALID_ORIG_DLY			= -517,		// 无效的零位偏移
	ZRC_INVALID_FREQ_RATIO			= -518,		// 无效的分频比
	ZRC_INVALID_AVG_TIMES			= -519,		// 无效的平均次数
	ZRC_INVALID_TRACE_TYPE			= -520,		// 无效的跟踪类型
	ZRC_INVALID_TRACE_PNT			= -521,		// 无效的跟踪点
	ZRC_INVALID_GATE_START			= -522,		// 无效的闸门起点
	ZRC_INVALID_GATE_WIDTH			= -523,		// 无效的闸门宽度
	ZRC_INVALID_GATE_HEIGHT			= -524,		// 无效的闸门高度
	ZRC_INVALID_DB_BOOST			= -525,		// 无效的增益提升
	ZRC_INVALID_ANG_FLTR			= -526,		// 无效的模拟滤波器
	ZRC_NO_ENOUGH_CHAN_TIME			= -527,		// 通道时间不够
	ZRC_NO_ENOUGH_BRD_MEM			= -528,		// 板载采样存储器超限
	ZRC_FFT_DISABLE					= -529		// 禁止FFT
} ET_ZRC;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 核心参数

typedef struct _ST_CORE_PARAM
{
	U8		m_nBrdSync;			// 板间同步
	U32		m_nRptFreq;			// 重复频率

	U32		m_anSynDly[MAX_BRD_NUM];	// 同步延迟

	BOOL	m_abChanEnb[TOT_HARD_NUM][MAX_SOFT_NUM];	// 通道使能
	U32		m_anChanShare[TOT_HARD_NUM][MAX_SOFT_NUM];	// 通道时间占额
	U16		m_anSmplDepth[TOT_HARD_NUM][MAX_SOFT_NUM];	// 采样深度
	S32		m_anOrigDly[TOT_HARD_NUM][MAX_SOFT_NUM];	// 零位延迟(ns)
	U16		m_anFreqRatio[TOT_HARD_NUM][MAX_SOFT_NUM];	// 分频比
	U8		m_anAvgTimes[TOT_HARD_NUM][MAX_SOFT_NUM];	// 平均次数
	BOOL	m_abSmplWave[TOT_HARD_NUM][MAX_SOFT_NUM];	// 采样波形
	BOOL	m_abFftWave[TOT_HARD_NUM][MAX_SOFT_NUM];	// FFT波形
	BOOL	m_abCentFreq[TOT_HARD_NUM][MAX_SOFT_NUM];	// 中心频率
} ST_CORE_PARAM;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 中间件导出信息

typedef struct _ST_EXP_INFO
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// 版本信息

	U8			m_nPcbVer;		// PCB版本
	U16			m_nFpgaVer;		// FPGA版本
	U16			m_nDevVer;		// 设备版本
	U16			m_nMidVer;		// 中间件版本

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 位宽信息

	U8			m_nStBw;		// 采样次数
	U8			m_nAtBw;		// 累积次数
	U8			m_nXBw;			// 采样深度
	U8			m_nYBw;			// 采样位数
	U8			m_nTBw;			// 时间小数

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 配置信息

	U8			m_nTotBrd;		// 已连接通道板卡总数
	U8			m_nTotHard;		// 板内硬通道总数
	U8			m_nTotSoft;		// 每个硬通道包含的软通道总数
	U8			m_nInnerSync;	// 板内通道同步方式
	U16			m_nMaxGain;		// 最大增益，1100表示110dB

	U8			m_anMacAddr[MAX_BRD_NUM][6];	// 网卡MAC地址
	char		m_aastrBrdSn[MAX_BRD_NUM][BRD_SN_TYPE_NUM][BRD_SN_TYPE_LEN * 2 + 1];	// 板号

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 系统时序解析结果

	U32			m_nDaqRate;		// 采集率
	U8			m_nSmplTimes;	// 采样次数
	U8			m_nAccTimes;	// 累积次数

	F32			m_afBrdNetRate[MAX_BRD_NUM];		// 每块板卡的网络速率(NET)
	F32			m_fSysNetRate;	// 整个系统的网络速率(NET)
} ST_EXP_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 导入(IMPORT)/导出(EXPORT)定义
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ZXUT_MID_H__
	#define ZXUT_API __declspec(dllimport)	// 应用程序导入函数
#else
	#define ZXUT_API __declspec(dllexport)	// DLL导出函数
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 接口函数声明列表
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
	extern "C" {
#endif

	////////////////////////////////////////////////////////////////////////////////////////////////
	// *** 设备制造商专用，最终用户请勿调用 ***

	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetBrdSn(U8 nBrdNum, U8 nBrdSnType, const char* strBrdSn);	// 写入指定板序列号
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDacCalib(U8 nHardNum, U8 nSoftNum);			// 设置DAC校准
	ZXUT_API U32	FAR PASCAL ZXUT_GetUsrReg(U8 nBrdNum);						// 获取用户寄存器
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetUsrReg(U8 nBrdNum, U32 nUsrReg);			// 设置用户寄存器
	ZXUT_API void	FAR PASCAL ZXUT_UpdDevSoft(U32 nClientIpAddr, U8 anBrdIdx[MAX_BRD_NUM], BOOL bUpdBrd[MAX_BRD_NUM], BOOL bUpdType[UPD_TYPE_NUM]);	// 更新设备软件

	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiTstEnb(U8 nBrdNum, BOOL bTstEnb);			// 设置DI测试使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiTstFreq(U8 nBrdNum, U16 nTstFreq);			// 设置DI测试频率(Hz)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiTstWidth(U8 nBrdNum, U16 nTstWidth);		// 设置DI测试宽度(ms)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiTstChan(U8 nBrdNum, U8 nTstChan);			// 设置DI测试通道

	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncTstEnb(U8 nBrdNum, BOOL bEncTstEnb);		// 设置编码器测试使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncTstPulNum(U8 nBrdNum, U32 nEncTstPulNum);	// 设置编码器测试脉冲数
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncTstLineNum(U8 nBrdNum, U32 nEncTstLineNum);	// 设置编码器测试线数
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncTstFreq(U8 nBrdNum, U32 nEncTstFreq);		// 设置编码器测试频率(Hz)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncTstMode(U8 nBrdNum, U8 nEncTstMode);		// 设置编码器测试模式(猝发/持续)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncMeasChan(U8 nBrdNum, U8 nEncChan);			// 设置编码器测量通道，并复位测量结果
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncTstTrig(U8 nBrdNum);	// 设置编码器测试触发

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 设备接口函数

	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_OpenDevice(U8 nZxutType, U8 nTotBrd, SOCKET sockZxut[MAX_BRD_NUM], ST_EXP_INFO** ppstExtInfo);	// 打开探伤设备
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_CloseDevice(U8 nAppExitCmd);	// 关闭探伤设备
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetNetCfg(U8 nBrdNum, U8 anIpAddr[5], U32 nNetPort);		// 设置网络配置
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_GetBrdSn(U8 nBrdNum, U8 nBrdSnType);	// 获取指定板序列号
	ZXUT_API void	FAR PASCAL ZXUT_SetCoreParamPtr(ST_CORE_PARAM* pstCoreParam);	// 设置核心参数指针
	ZXUT_API void	FAR PASCAL ZXUT_SetMaxDaqRate(U32 nMaxDaqRate);	// 设置最大采集率

	ZXUT_API U32	FAR PASCAL ZXUT_GetRqNum(U8 nBrdNum, U8* pbRqFull);	// 获取可用数据个数，附带环形队列满标志
	ZXUT_API U32	FAR PASCAL ZXUT_GetRqData(U8 nBrdNum, U32 nRqNum, ST_RQ_DATA* pstRqData);	// 获取采样数据

	ZXUT_API F32	FAR PASCAL ZXUT_TransPcbTempValue(U16 nTempCode);	// 将PCB温度码转换为温度值
	ZXUT_API F32	FAR PASCAL ZXUT_TransFpgaTempValue(U16 nTempCode);	// 将FPGA温度码转换为温度值

	ZXUT_API U32	FAR PASCAL ZXUT_GetEncCntr(U8 nBrdNum, U8 nEncIdx);	// 获取指定编码器的计数值

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 系统参数接口函数

	// 通用
	ZXUT_API void	FAR PASCAL ZXUT_SetSmplEnb(BOOL bSmplEnb);					// 设置采样使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTransVol(U8 nBrdNum, U16 nTransVol);		// 设置发射电压
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTrigMode(U8 nBrdNum, U8 nTrigMode);		// 设置触发模式
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTrigPol(U8 nBrdNum, U8 nTrigPol);		// 设置触发极性
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetScanEnc(U8 nBrdNum, U8 nScanEnc);		// 设置扫查编码器
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetScanSpan(U8 nBrdNum, U32 nScanSpan);		// 设置扫查间隔
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetBrdSync(U8 nBrdNum, U8 nBrdSync);		// 设置板间同步方式
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetRptFreq(U32 nRptFreq, U8* pnHardNum, U8* pnSoftNum);	// 设置重复频率

	// 数字输入(DI)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiEnb(U8 nBrdNum, U8 nDiChan, BOOL bDiEnb);		// 设置DI使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiMode(U8 nBrdNum, U8 nDiChan, U8 nDiMode);		// 设置DI模式
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiPol(U8 nBrdNum, U8 nDiChan, U8 nDiPol);		// 设置DI极性
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiClr(U8 nBrdNum, U8 nDiChan);					// 设置DI清除
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiWidth(U8 nBrdNum, U8 nDiChan, U16 nDiWidth);	// 设置DI宽度
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiDly(U8 nBrdNum, U8 nDiChan, U16 nDiDly);		// 设置DI延迟
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDiBase(U8 nBrdNum, U16 nDiBase);					// 设置DI时基

	// 数字输出(DO)，仅主板DO生效
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoEnb(U8 nDoChan, BOOL bDoEnb);		// 设置DO使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoMode(U8 nDoChan, U8 nDoMode);		// 设置DO模式
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoPol(U8 nDoChan, U8 nDoPol);		// 设置DO极性
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoCmd(U8 nDoChan, BOOL bDoCmd);		// 设置DO命令
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoWidth(U8 nDoChan, U16 nDoWidth);	// 设置DO宽度
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoDly(U8 nDoChan, U16 nDoDly);		// 设置DO延迟
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDoBase(U16 nDoBase);					// 设置DO时基

	// 编码器(ENC)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEabCntr(U8 nBrdNum, U8 nEncChan, U32 nEabCntr);	// 设置编码器AB相计数值
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEzCntr(U8 nBrdNum, U8 nEncChan, U32 nEzCntr);	// 设置编码器Z相计数值
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncEnb(U8 nBrdNum, U8 nEncChan, BOOL bEncEnb);	// 设置编码器使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncType(U8 nBrdNum, U8 nEncChan, U8 nEncType);	// 设置编码器类型
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncPol(U8 nBrdNum, U8 nEncChan, U8 nEncPol);		// 设置编码器极性
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncZe(U8 nBrdNum, U8 nEncChan, BOOL bEncZe);		// 设置编码器回零使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEncFltr(U8 nBrdNum, U8 nEncChan, U8 nEncFltr);	// 设置编码器滤波

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 通道参数接口函数

	// 通用
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetRtMode(U8 nHardNum, U8 nRtMode);		// 设置收发模式
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetChanEnb(U8 nHardNum, U8 nSoftNum, BOOL bChanEnb);	// 设置通道使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetAngFltr(U8 nHardNum, U8 nSoftNum, U8 nAngFltr);		// 设置模拟滤波器
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDemMode(U8 nHardNum, U8 nSoftNum, U8 nDemMode);		// 设置检波模式
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDbNum(U8 nHardNum, U8 nSoftNum, U16 nDbNum);			// 设置增益数
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDbBoost(U8 nHardNum, U8 nSoftNum, U8 nDbBoost);		// 设置增益提升
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetPulWidth(U8 nHardNum, U8 nSoftNum, U16 nPulWidth);	// 设置发射脉冲宽度(ns)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetPulNum(U8 nHardNum, U8 nSoftNum, U8 nPulNum);		// 设置发射脉冲个数
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetFftGate(U8 nHardNum, U8 nSoftNum, U8 nFftGate);		// 设置FFT闸门
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetEchoMode(U8 nHardNum, U8 nSoftNum, U8 nEchoMode);	// 设置回波模式

	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetSmplDepth(U8 nHardNum, U8 nSoftNum, U16 nSmplDepth, U16* pnMaxSmplDepth, U32* pnSoloBrdNoAccDws);	// 设置采样深度
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetOrigDly(U8 nHardNum, U8 nSoftNum, S32 nOrigDly, U32* pnMaxOrigDly);			// 设置零位偏移(ns)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetFreqRatio(U8 nHardNum, U8 nSoftNum, U16 nFreqRatio, U16* pnMaxFreqRatio);	// 设置分频比
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetAvgTimes(U8 nHardNum, U8 nSoftNum, U8 nAvgTimes, U8* pnMaxAvgTimes);			// 设置平均次数
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetDataSwitch(U8 nHardNum, U8 nSoftNum, BOOL bSmplWave, BOOL bFftWave, BOOL bCentFreq);	// 设置数据开关

	// 界面波闸门跟踪
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTraceEnb(U8 nHardNum, U8 nSoftNum, BOOL bTraceEnb);	// 设置跟踪使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTraceType(U8 nHardNum, U8 nSoftNum, U8 nTraceType);	// 设置跟踪类型
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTracePnt(U8 nHardNum, U8 nSoftNum, U16 nTracePnt);	// 设置跟踪点

	// 探伤闸门ABCI
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetGateStart(U8 nHardNum, U8 nSoftNum, U8 nGateSel, U16 nGateStart);	// 设置闸门起点
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetGateWidth(U8 nHardNum, U8 nSoftNum, U8 nGateSel, U16 nGateWidth);	// 设置闸门宽度
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetGateHeight(U8 nHardNum, U8 nSoftNum, U8 nGateSel, U16 nGateHeight);	// 设置闸门高度
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetGatePol(U8 nHardNum, U8 nSoftNum, U8 nGateSel, U8 nGatePol);			// 设置闸门极性

	// TCG(距离补偿)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTcgEnb(U8 nHardNum, U8 nSoftNum, BOOL bTcgEnb);			// 设置TCG使能
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTcgTotTime(U8 nHardNum, U8 nSoftNum, U32 nTcgTotTime);	// 设置TCG总时间(ns)
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTcgTpTot(U8 nHardNum, U8 nSoftNum, U8 nTcgTpTot);		// 设置TCG测试点点数
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTcgTpIdx(U8 nHardNum, U8 nSoftNum, U8 nTcgTpIdx);		// 设置TCG测试点序号
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTcgTpTime(U8 nHardNum, U8 nSoftNum, U32 nTcgTpTime);		// 设置TCG测试点时间
	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_SetTcgTpGain(U8 nHardNum, U8 nSoftNum, U16 nTcgTpGain);		// 设置TCG测试点增益

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 封装接口函数

	ZXUT_API F32	FAR PASCAL ZXUT_GetFftFreq(U16 nSmplIdx, U16 nFreqRatio);	// 获取FFT频率
	ZXUT_API U32	FAR PASCAL ZXUT_GetTstTime(U16 nFreqRatio, U16 xCoord, U16 tCoord);	// 获取检测时间(ns)
	ZXUT_API F32	FAR PASCAL ZXUT_GetTstRange(U16 nFreqRatio, U16 xCoord, U16 tCoord, U32 nSoundVelo);	// 获取检测范围(mm)
	ZXUT_API U32	FAR PASCAL ZXUT_GetMaxRptFreq(void);	// 获取最大重复频率

	ZXUT_API U32	FAR PASCAL ZXUT_GetSoloBrdNoAccDaqDws(U8 nBrdNum);	// 获取单块板卡无累积的采集双字数

	ZXUT_API void	FAR PASCAL ZXUT_FftInit(S32 nFftNum);				// FFT初始化
	ZXUT_API void	FAR PASCAL ZXUT_FftExec(ST_COMP_NUM* pstFftData);	// FFT执行

	ZXUT_API ET_ZRC	FAR PASCAL ZXUT_InitRtMem(U8 nHardNum, U8 nSoftNum, BOOL nRtMemEnb, U32 nRtMemTime,
		char* strRtMemFileName, U32* pnRtMemTimes, U64* pnRtMemFileSize);	// 初始化实时存储

#ifdef __cplusplus
	}
#endif

#endif // #ifndef __ZXUT_EXP_H__
