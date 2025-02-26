#pragma once

typedef signed __int64		S64;	// 64位有符号数
typedef unsigned __int64	U64;	// 64位无符号数

////////////////////////////////////////////////////////////////////////////////////////////////////
// 开关状态

const U8 SW_STS_OFF			= 0;
const U8 SW_STS_ON			= 1;

const U8 SW_STS_MIN			= SW_STS_OFF;
const U8 SW_STS_MAX			= SW_STS_ON;

const U8 SW_STS_INIT		= SW_STS_OFF;

const char SW_STS_STR[][20] =
{
	"OFF", "ON"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 收发方式

const U8 RT_MODE_MIN		= RT_MODE_SOLO;
const U8 RT_MODE_MAX		= RT_MODE_DUAL;

const U8 RT_MODE_INIT		= RT_MODE_SOLO;

const char RT_MODE_STR[][20] =
{
	"单晶",		// 自发自收
	"双晶"		// 单发单收
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 跟踪类型

const U8 TRACE_TYPE_MIN		= TRACE_TYPE_PEDGE;
const U8 TRACE_TYPE_MAX		= TRACE_TYPE_NEDGE;

const U8 TRACE_TYPE_INIT	= TRACE_TYPE_PEDGE;

const char TRACE_TYPE_STR[][20] =
{
	"前沿", "后沿"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 检波方式

const U8 DEM_MODE_MIN		= DEM_MODE_FULL;
const U8 DEM_MODE_MAX		= DEM_MODE_RF;

const U8 DEM_MODE_INIT		= DEM_MODE_FULL;

const char	DEM_MODE_STR[][20] =
{
	"全检波", "正检波", "负检波", "射频"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 平均次数

const U8 AT_IDX_1			= 0;
const U8 AT_IDX_2			= 1;
const U8 AT_IDX_4			= 2;
const U8 AT_IDX_8			= 3;
const U8 AT_IDX_16			= 4;

const U16 AT_IDX_MIN		= AT_IDX_1;
const U16 AT_IDX_MAX		= AT_IDX_16;		// 最大16次平均

const U32 AVG_TIMES_VALUE[] =
{
	1, 2, 4, 8, 16
};

const char AVG_TIMES_STR[][20] =
{
	"1", "2", "4", "8", "16"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 触发模式

const U8 TRIG_MODE_MIN		= TRIG_MODE_TIME;
const U8 TRIG_MODE_MAX		= TRIG_MODE_EXT;

const U8 TRIG_MODE_INIT		= TRIG_MODE_TIME;

const char TRIG_MODE_STR[][20] =
{
	"定时触发", "编码触发", "外部触发"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 模拟滤波器

const char ANG_FLTR_STR_PCI[][20] =
{
	"1~6", "3~15", "5~21", "0.5~21"
};

const char ANG_FLTR_STR_NET[][20] =
{
	"无",
	"LPF 2", "LPF 5", "LPF 10", "LPF 15",
	"HPF 1", "HPF 2", "HPF 5", "HPF 10",
	"1 ~ 2", "1 ~ 5", "1 ~ 10", "1 ~ 15",
	"2 ~ 5", "2 ~ 10", "2 ~ 15",
	"5 ~ 10", "5 ~ 15",
	"10 ~ 15"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 重复频率索引

const U8 RF_IDX_1HZ		= 0;

const U8 RF_IDX_10HZ	= 1;
const U8 RF_IDX_20HZ	= 2;
const U8 RF_IDX_3HZ		= 3;
const U8 RF_IDX_40HZ	= 4;
const U8 RF_IDX_50HZ	= 5;
const U8 RF_IDX_60HZ	= 6;
const U8 RF_IDX_70HZ	= 7;
const U8 RF_IDX_80HZ	= 8;
const U8 RF_IDX_90HZ	= 9;

const U8 RF_IDX_100HZ	= 10;
const U8 RF_IDX_200HZ	= 11;
const U8 RF_IDX_300HZ	= 12;
const U8 RF_IDX_400HZ	= 13;
const U8 RF_IDX_500HZ	= 14;
const U8 RF_IDX_600HZ	= 15;
const U8 RF_IDX_700HZ	= 16;
const U8 RF_IDX_800HZ	= 17;
const U8 RF_IDX_900HZ	= 18;

const U8 RF_IDX_1KHZ	= 19;
const U8 RF_IDX_2KHZ	= 20;
const U8 RF_IDX_3KHZ	= 21;
const U8 RF_IDX_4KHZ	= 22;
const U8 RF_IDX_5KHZ	= 23;
const U8 RF_IDX_6KHZ	= 24;
const U8 RF_IDX_7KHZ	= 25;
const U8 RF_IDX_8KHZ	= 26;
const U8 RF_IDX_9KHZ	= 27;

const U8 RF_IDX_10KHZ	= 28;
const U8 RF_IDX_20KHZ	= 29;
const U8 RF_IDX_30KHZ	= 30;
const U8 RF_IDX_40KHZ	= 31;
const U8 RF_IDX_50KHZ	= 32;

const U8 RF_IDX_MIN = RF_IDX_1HZ;
const U8 RF_IDX_MAX = RF_IDX_50KHZ;

const U32 RPT_FREQ_VALUE[] =
{
	1,
	10, 20,    30,    40,    50,   60,   70,   80,   90,
	100, 200,   300,   400,   500,  600,  700,  800,  900,
	1000, 2000,  3000,  4000,  5000, 6000, 7000, 8000, 9000,
	10000, 20000, 30000, 40000, 50000
};

const char RPT_FREQ_STR[][20] =
{
	"1Hz",
	"10Hz", "20Hz", "30Hz", "40Hz", "50Hz", "60Hz", "70Hz", "80Hz", "90Hz",
	"100Hz", "200Hz", "300Hz", "400Hz", "500Hz", "600Hz", "700Hz", "800Hz", "900Hz",
	"1KHz", "2KHz", "3KHz", "4KHz", "5KHz", "6KHz", "7KHz", "8KHz", "9KHz",
	"10KHz", "20KHz", "30KHz", "40KHz", "50KHz"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 水平显示

const U8 HORI_DISP_MM	= 0;	// 毫米
const U8 HORI_DISP_US	= 1;	// 微秒
const U8 HORI_DISP_DOTS = 2;	// 点数

const U8 HORI_DISP_MIN = HORI_DISP_MM;
const U8 HORI_DISP_MAX = HORI_DISP_DOTS;

const U8 HORI_DISP_INIT = HORI_DISP_MM;

const char HORI_DISP_STR[][20] =
{
	"mm", "us", "点数"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 垂直显示

const U8 VERT_DISP_PERC = 0;	// 百分比
const U8 VERT_DISP_DOTS = 1;	// 点数

const U8 VERT_DISP_MIN = VERT_DISP_PERC;
const U8 VERT_DISP_MAX = VERT_DISP_DOTS;

const U8 VERT_DISP_INIT = VERT_DISP_PERC;

const char VERT_DISP_STR[][20] =
{
	"%", "点数"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示刷新

#define DISP_UPD_1HZ	0		// 1Hz低频刷新
#define DISP_UPD_2HZ	1		// 2Hz低频刷新
#define DISP_UPD_5HZ	2		// 3Hz低频刷新
#define DISP_UPD_10HZ	3		// 10Hz低频刷新
#define DISP_UPD_20HZ	4		// 10Hz低频刷新
#define DISP_UPD_REAL	5		// 实时刷新

const U8 DISP_UPD_MIN = DISP_UPD_1HZ;
const U8 DISP_UPD_MAX = DISP_UPD_REAL;

const U8 DISP_UPD_INIT = DISP_UPD_2HZ;

const char DISP_UPD_STR[][20] =
{
	"1Hz", "2Hz", "5Hz", "10Hz", "20Hz", "实时"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 编码器滤波

const U8 ENC_FLTR_MIN = ENC_FLTR_10KHZ;
const U8 ENC_FLTR_MAX = ENC_FLTR_500KHZ;

const char ENC_FLTR_STR[ENC_FLTR_NUM][20] =
{
	"<=10KHz", "<=20KHz", "<=50KHz", "<=100KHz", "<=200KHz", "<=500KHz"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 闸门索引

const U32 GATE_SEL_MIN	= GATE_SEL_A;
const U32 GATE_SEL_MAX	= GATE_SEL_I;

const U32 GATE_SEL_INIT	= GATE_SEL_A;

const char GATE_SEL_STR[][20] =
{
	"闸门A", "闸门B", "闸门C", "闸门I"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 闸门极性

const U8 GATE_POL_MIN = POL_DEF_NEG;
const U8 GATE_POL_MAX = POL_DEF_POS;

const U8 GATE_POL_INIT = POL_DEF_POS;

const char GATE_POL_STR[][20] =
{
	"波谷", "波峰"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 极性定义

const U8 POL_DEF_MIN = POL_DEF_NEG;
const U8 POL_DEF_MAX = POL_DEF_POS;

const U8 POL_DEF_INIT = POL_DEF_POS;

const char POL_DEF_STR[][20] =
{
	"负极性", "正极性"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 缺陷类型

const U8 FLAW_TYPE_PEAK		= 0;	// 峰值
const U8 FLAW_TYPE_PEDGE	= 1;	// 前沿
const U8 FLAW_TYPE_NEDGE	= 2;	// 后沿

const U8 FLAW_TYPE_MIN = FLAW_TYPE_PEAK;
const U8 FLAW_TYPE_MAX = FLAW_TYPE_NEDGE;

const U8 FLAW_TYPE_INIT = FLAW_TYPE_PEAK;

const char FLAW_TYPE_STR[][20] =
{
	"峰值", "前沿", "后沿"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 板间同步

const U8 BRD_SYNC_MIN = BRD_SYNC_SERI;
const U8 BRD_SYNC_MAX = BRD_SYNC_PARA;

const U8 BRD_SYNC_INIT = BRD_SYNC_PARA;

const char BRD_SYNC_STR[][20] =
{
	"串行", "并行"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 编码器类型

const U8 ENC_TYPE_MAX = 3;

const char ENC_TYPE_STR[][20] =
{
	"单脉冲", "双脉冲", "四脉冲"
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 材料声速

const U32 SOUND_VELO_MIN	= 1000;
const U32 SOUND_VELO_MAX	= 8000;
const U32 SOUND_VELO_INIT	= 5940;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 逻辑通道

typedef struct _ST_LOG_CHAN
{
	U8 m_nLogIdx;	// 逻辑通道索引
	U8 m_nLogTot;	// 逻辑通道总数

	U8 m_nLogHard[TOT_LOG_NUM];		// 每个逻辑通道的硬编号
	U8 m_nLogSoft[TOT_LOG_NUM];		// 每个逻辑通道的软编号
} ST_LOG_CHAN;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 闸门参数

const U32 GATE_START_INIT	= 600;
const U32 GATE_WIDTH_INIT	= 60;
const U16 GATE_HEIGHT_INIT	= 400;

typedef struct _ST_GATE_PARAM
{
	U16		m_nStart	[TOT_GATE_NUM];	// 闸门起点
	U16		m_nWidth	[TOT_GATE_NUM];	// 闸门宽度
	U16		m_nHeight	[TOT_GATE_NUM];	// 闸门高度
	U8		m_nPol		[TOT_GATE_NUM];	// 闸门极性
	U8		m_nType		[TOT_GATE_NUM];	// 缺陷类型
	BOOL	m_bEnb		[TOT_GATE_NUM];	// 闸门使能
} ST_GATE_PARAM;

const U16 GATE_WIDTH_MIN = 5;	// 最小的闸门宽度
const U16 GATE_HEIGHT_MIN = 4;	// 最小的闸门高度

////////////////////////////////////////////////////////////////////////////////////////////////////
// 数字输入（DI）

typedef struct _ST_DIG_IN
{
	U16		m_nBase;					// 时基：10

	U8		m_bEnb	[TOT_DI_NUM];		// 使能: 1
	U8		m_nMode	[TOT_DI_NUM];		// 模式: 1
	U8		m_nPol	[TOT_DI_NUM];		// 极性: 1
	U16		m_nWidth[TOT_DI_NUM];		// 宽度：10
	U16		m_nDly	[TOT_DI_NUM];		// 延迟：10

	U8		m_bTstEnb;		// 测试使能
	U16		m_nTstFreq;		// 测试频率
	U16		m_nTstWidth;	// 测试宽度, us
	U8		m_nTstChan;		// 测试通道
} ST_DIG_IN;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 数字输出（DO）

typedef struct _ST_DIG_OUT
{
	U16		m_nBase;					// 时基：10

	U8		m_bEnb	[TOT_DI_NUM];		// 使能: 1
	U8		m_nMode	[TOT_DI_NUM];		// 模式: 1
	U8		m_nPol	[TOT_DI_NUM];		// 极性: 1
	U16		m_nWidth[TOT_DI_NUM];		// 宽度：10
	U16		m_nDly	[TOT_DI_NUM];		// 延迟：10
} ST_DIG_OUT;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 编码器（ENC）

typedef struct _ST_ENC_MODU
{
	U8		m_nTstEnb;					// 测试使能
	U32		m_nTstPulNum;				// 测试脉冲数(1 ~ 60k)
	U32		m_nTstLineNum;				// 测试线数(100 ~ 10k)
	U32		m_nTstFreq;					// 测试频率(100Hz ~ 500KHz)
	BOOL	m_bTstCont;					// 持续测试

	U8		m_nFltr	[TOT_ENC_NUM];		// 滤波
	U8		m_bEnb	[TOT_ENC_NUM];		// 使能
	U8		m_nPol	[TOT_ENC_NUM];		// 极性
	U8		m_bZe	[TOT_ENC_NUM];		// 回零使能
	U8		m_nType	[TOT_ENC_NUM];		// 类型
	U8		m_bScan	[TOT_ENC_NUM];		// 扫查
} ST_ENC_MODU;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 采样参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

const U32 PARAM_SIG_BEG = 0x0055AAFF;
const U32 PARAM_SIG_END = 0xFFAA5500;

typedef struct _ST_FLAW_PARAM
{
	U32				m_nSigBeg;			// 开始标识

	U8				m_nNeedBrdNum;		// 需要板卡数

	U8				m_anIpAddr[5];		// IP地址
	U32				m_nNetPort;			// 网络端口

	U8				m_nDispUpd;			// 显示更新：10Hz / 实时
	U8				m_nHoriDisp;		// 水平显示
	U8				m_nVertDisp;		// 垂直显示

	U32				m_nVltSpan;			// 垂直线性测试(VLT)间隔
	U32				m_nFreqRefLine;		// 幅频曲线中的频率参考线
	BOOL			m_bBwN3dB;			// -3dB计算频带
	BOOL			m_bSmplAct;			// 采样激活(是否一打开软件就开启采样)
	BOOL			m_bFlawRef;			// 缺陷参考是否显示

	U32				m_nRtMemTime;		// 实时存储时间(秒)

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 系统参数

	U16				m_nTransVol;		// 发射电压
	U16				m_nScanSpan;		// 扫查间隔
	U8				m_nTrigMode;		// 触发模式: 定时/编码/外部
	U8				m_nTrigPol;			// 触发极性：正/负
	U8				m_nRfIdx;			// 重复频率(rpt_freq)，索引
	U32				m_nMaxDaqRate;		// 最大采集率(Hz)

	U32				m_anChanShare[TOT_HARD_NUM];

	ST_CORE_PARAM	m_stCoreParam;		// 核心参数

	ST_DIG_IN		m_stDigIn;			// 数字输入(DI)
	ST_DIG_OUT		m_stDigOut;			// 数字输出(DO)
	ST_ENC_MODU		m_stEncModu[MAX_BRD_NUM];	// 编码器(ENC)

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 通道参数

	U8				m_anRtMode		[TOT_HARD_NUM];	// 收发模式

	U8				m_anAngFltr		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 模拟滤波(PCI)
	U16				m_anDbNum		[TOT_HARD_NUM][MAX_SOFT_NUM];	// dB码
	U8				m_anDbBoost		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 阻抗匹配(P2)
	U16				m_anPulWidth	[TOT_HARD_NUM][MAX_SOFT_NUM];	// 脉冲宽度(ns)
	U8				m_anPulNum		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 脉冲个数
	U8				m_anDemMode		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 检波模式
	U32				m_anSoundVelo	[TOT_HARD_NUM][MAX_SOFT_NUM];	// 材料声速
	U8				m_anFftGate		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 选择哪个闸门内的数据做FFT

	U8				m_anSdIdx		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 采样深度(smpl_depth)，索引
	U8				m_anAtIdx		[TOT_HARD_NUM][MAX_SOFT_NUM];	// 平均次数(avg_times)，索引

	BOOL			m_abTraceEnb	[TOT_HARD_NUM][MAX_SOFT_NUM];	// 界面波跟踪
	U8				m_anTraceType	[TOT_HARD_NUM][MAX_SOFT_NUM];	// 跟踪类型

	ST_GATE_PARAM	m_astGateParam	[TOT_HARD_NUM][MAX_SOFT_NUM];	// 闸门A, B, C, I
	ST_TCG_PARAM	m_stTcgParam	[TOT_HARD_NUM][MAX_SOFT_NUM];	// TCG参数

	U32				m_nSigEnd;		// 结束标识
} ST_FLAW_PARAM;
