#pragma once

#include "FlawParamAdj.h"
#include "ColorStaticST.h"

#include "DlgFlawParam.h"
#include "DlgFlawGate.h"
#include "DlgEncModu.h"
#include "DlgSysSetting.h"
#include "DlgTcgProc.h"
#include "DlgDigIn.h"
#include "DlgDigOut.h"
#include "DlgFftProc.h"
#include "DlgChanEnb.h"
#include "DlgDevUpd.h"

#include "Led.h"

const U8 TAB_FLAW_PARAM		= 0;	// 探伤参数
const U8 TAB_FLAW_GATE		= 1;	// 探伤闸门
const U8 TAB_DIG_IN			= 2;	// 数字输入
const U8 TAB_DIG_OUT		= 3;	// 数字输出
const U8 TAB_ENC_MODU		= 4;	// 编码器
const U8 TAB_TCG_PROC		= 5;	// TCG处理
const U8 TAB_SYS_SETTING	= 6;	// IP地址
const U8 TAB_FFT_PROC		= 7;	// FFT处理
const U8 TAB_DEV_UPD		= 8;	// 设备更新

class CZxutDlg : public CDialog
{
public:
	CZxutDlg(CWnd* pParent = NULL);	// 标准构造函数
	enum { IDD = IDD_ZXUT_APP };
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog(void);
	virtual void OnOK(void);
	virtual void OnCancel(void);

	afx_msg void OnPaint(void);
	afx_msg HCURSOR OnQueryDragIcon(void);

	HICON m_hIcon;

	////////////////////////////////////////////////////////////////////////////////////////////////

	CZxutApp* m_pApp;
	CTabCtrl m_tabZxut;

	CDlgFlawParam m_dlgFlawParam;	// 探伤参数
	CDlgFlawGate m_dlgFlawGate;		// 探伤闸门
	CDlgDigIn m_dlgDigIn;			// 数字输入
	CDlgDigOut m_dlgDigOut;			// 数字输出
	CDlgEncModu m_dlgEncModu;		// 编码器
	CDlgTcgProc m_dlgTcgProc;		// TCG处理
	CDlgSysSetting m_dlgSysSetting;	// 系统设置
	CDlgFftProc m_dlgFftProc;		// FFT处理
	CDlgChanEnb m_dlgChanEnb;		// 通道使能
	CDlgDevUpd m_dlgDevUpd;			// 设备更新

	CFont m_fntTxt;
	CColorStaticST m_txtPeakDist;	// 峰值距离
	CColorStaticST m_txtPeakHeight;	// 峰值高度

	CButton m_chkAutoGain;

	UINT_PTR m_iTimerID;
	CStatic m_txtRunTime;
	U32 m_nTimeCntr;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CLed m_ledOverHeight;

	////////////////////////////////////////////////////////////////////////////////////////////////

	CButton m_btnSmplEnb;
	afx_msg void OnBnClickedBtnSmplEnb(void);

	CButton m_btnClientExit;
	afx_msg void OnBnClickedBtnClientExit(void);

	CButton m_btnClientReboot;
	afx_msg void OnBnClickedBtnClientReboot(void);

	CButton m_btnClientHalt;
	afx_msg void OnBnClickedBtnClientHalt(void);

	afx_msg void OnTcnSelchangeTabZxut(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtnKeyHlp(void);
	afx_msg void OnBnClickedBtnWaveExport(void);
	afx_msg void OnBnClickedBtnAbout(void);

	CButton m_chkRtMem;
	CEdit m_edtRtMem;
	afx_msg void OnBnClickedChkRtMem(void);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
