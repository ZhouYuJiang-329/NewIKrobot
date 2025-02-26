#pragma once

#include "ColorStaticST.h"

class CDlgFftProc : public CDialog
{
	DECLARE_DYNAMIC(CDlgFftProc)

public:
	CDlgFftProc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFftProc(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);

	enum { IDD = IDD_FFT_PROC };

	CZxutApp* m_pApp;

	CStatic m_txtMaxFreq;		// 软件求中心频率

	CStatic m_txtCentFreq;		// 硬件求中心频率
	CStatic m_txtLeftFreq;		// 左-6dB
	CStatic m_txtRightFreq;		// 右-6dB
	CStatic m_txtBw;			// BW
	CStatic m_txtRBw;			// 相对BW

	CComboBox m_combFftGate;		// FFT闸门
	afx_msg void OnCbnSelchangeComboFftGate(void);

	CComboBox m_combFreqRefLine;	// 瞬时频率
	afx_msg void OnCbnSelchangeComboFreqRefLine(void);

	CStatic m_txtInstGain;

	CButton m_radN3dB, m_radN6dB;	// 频带选择
	afx_msg void OnBnClickedRadN3db(void);
	afx_msg void OnBnClickedRadN6db(void);

	CComboBox m_combAngFltr;		// 模拟滤波器
	afx_msg void OnCbnSelchangeComboAngFltr(void);

	CButton m_chkScanFreq;	// 扫频开关
	afx_msg void OnBnClickedChkScanFreq(void);

	CButton m_chkLockBw;	// 锁定频带
	afx_msg void OnBnClickedChkLockBw(void);

	CButton m_btnAnalysizeBw;		// 频带分析
	afx_msg void OnBnClickedBtnGetBw();

	CButton m_btnRecBw;		// 频带记录
	afx_msg void OnBnClickedBtnRecBw(void);

	CButton m_chkFftWave;	// FFT波形
	afx_msg void OnBnClickedChkFftWave();

	CButton m_chkCentFreq;	// 中心频率
	afx_msg void OnBnClickedChkCentFreq();

	DECLARE_MESSAGE_MAP()
};
