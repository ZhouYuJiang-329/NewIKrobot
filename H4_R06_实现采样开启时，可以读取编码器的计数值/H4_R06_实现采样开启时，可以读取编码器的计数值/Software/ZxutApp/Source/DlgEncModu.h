#pragma once

class CDlgEncModu : public CDialog
{
	DECLARE_DYNAMIC(CDlgEncModu)

public:
	CDlgEncModu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEncModu(void);
	enum { IDD = IDD_ENC_MODU };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CZxutApp* m_pApp;
	U8 x_nTotBrd;
	U8 x_nTotHard;

	////////////////////////////////////////////////////////////////////////////////////////////////

	// 使能
	CButton m_chkEncEnb[TOT_ENC_NUM + 1];
	afx_msg void OnBnClickedChkEncEnb(void);
	void EnbEncCtrl(U8 enc_chan, BOOL enb);

	// 编码器计数值
	CStatic m_txtEabCntr[TOT_ENC_NUM];
	CStatic m_txtEzCntr[TOT_ENC_NUM];
	void UpdEncCntr(U32* encab_cntr, U32* encz_cntr);

	// 回零使能
	CButton m_chkEncZe[TOT_ENC_NUM + 1];
	afx_msg void OnBnClickedChkEncZe(void);

	// 复位编码器
	CButton m_btnRstEncCntr[TOT_ENC_NUM + 1];
	void RstEncCntr(void);
	afx_msg void OnBnClickedBtnRstEncCntr(void);

	// 极性
	CButton m_chkEncPol[TOT_ENC_NUM + 1];
	afx_msg void OnBnClickedChkEncPol(void);

	// 扫查编码器
	CButton m_radScanEnc[TOT_ENC_NUM];
	afx_msg void OnBnClickedRadScanEnc(void);

	// 类型
	CComboBox m_combEncType[TOT_ENC_NUM + 1];
	afx_msg void OnCbnSelchangeComboEncType(void);

	// 滤波
	CComboBox m_combEncFltr[TOT_ENC_NUM + 1];
	afx_msg void OnCbnSelchangeComboEncFltr(void);

	CEdit m_edtScanSpan;	// 扫查间隔

	////////////////////////////////////////////////////////////////////////////////////////////////

	void FreshEncTstCtrl(void);	// 刷新编码器测试控件

	// 测试使能
	CButton m_chkEncTstEnb;
	afx_msg void OnBnClickedChkEncTstEnb(void);

	CButton m_btnEncTstTrig;
	afx_msg void OnBnClickedBtnEncTstTrig(void);	// 触发

	CEdit m_edtEncTstPulNum;	// 测试脉冲数

	CEdit m_edtEncTstLineNum;	// 测试线数

	CButton m_chkEncTstCont;
	afx_msg void OnBnClickedChkEncTstCont(void);	// 持续测试

	// 测试频率
	CEdit m_edtEncTstFreq;

	CStatic m_txtEncTstFreq;
	void GetEncTstFreq(CString& str);	// 编码器测试频率

	CStatic m_txtEncScanFreq;
	void GetEncScanFreq(CString& str);	// 编码器扫查频率

	CStatic m_txtEncMeasFreq;
	void GetEncMeasFreq(CString& str);	// 编码器测量频率

	afx_msg void OnBnClickedBtnRstEncMeas(void);	// 复位编码器测量结果
	void UpdEncMeasRes(ST_RQ_DATA& daq_buf);		// 更新编码器测量结果

	U8 m_nEncChan;
	CComboBox m_combEncIdx;	// 编码器选择
	afx_msg void OnCbnSelchangeCombEncChan(void);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnRdEncCntr();
};
