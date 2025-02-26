#pragma once

class CDlgDigOut : public CDialog
{
	DECLARE_DYNAMIC(CDlgDigOut)

public:
	CDlgDigOut(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDigOut(void);
	enum { IDD = IDD_DIG_OUT };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);

	CZxutApp* m_pApp;
	U8 x_nTotBrd;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	////////////////////////////////////////////////////////////////////////////////////////////////

	// 时基
	CComboBox m_combDoBase;
	afx_msg void OnCbnSelchangeComboDoBase(void);

	// 使能
	CButton m_chkDoEnb[TOT_DO_NUM];
	void SetDoEnb(U8 do_chan);
	afx_msg void OnBnClickedChkDoEnb0(void);
	afx_msg void OnBnClickedChkDoEnb1(void);
	afx_msg void OnBnClickedChkDoEnb2(void);
	afx_msg void OnBnClickedChkDoEnb3(void);
	afx_msg void OnBnClickedChkDoEnb4(void);
	afx_msg void OnBnClickedChkDoEnb5(void);
	afx_msg void OnBnClickedChkDoEnb6(void);
	afx_msg void OnBnClickedChkDoEnb7(void);

	// 模式
	CComboBox m_combDoMode[TOT_DO_NUM];
	void SetDoMode(U8 do_chan);
	afx_msg void OnCbnSelchangeComboDoMode0(void);
	afx_msg void OnCbnSelchangeComboDoMode1(void);
	afx_msg void OnCbnSelchangeComboDoMode2(void);
	afx_msg void OnCbnSelchangeComboDoMode3(void);
	afx_msg void OnCbnSelchangeComboDoMode4(void);
	afx_msg void OnCbnSelchangeComboDoMode5(void);
	afx_msg void OnCbnSelchangeComboDoMode6(void);
	afx_msg void OnCbnSelchangeComboDoMode7(void);

	// 极性
	CComboBox m_combDoPol[TOT_DO_NUM];
	void SetDoPol(U8 do_chan);
	afx_msg void OnCbnSelchangeComboDoPol0(void);
	afx_msg void OnCbnSelchangeComboDoPol1(void);
	afx_msg void OnCbnSelchangeComboDoPol2(void);
	afx_msg void OnCbnSelchangeComboDoPol3(void);
	afx_msg void OnCbnSelchangeComboDoPol4(void);
	afx_msg void OnCbnSelchangeComboDoPol5(void);
	afx_msg void OnCbnSelchangeComboDoPol6(void);
	afx_msg void OnCbnSelchangeComboDoPol7(void);

	// 宽度
	CSpinButtonCtrl m_spinDoWidth[TOT_DO_NUM];
	CStatic m_txtDoWidth[TOT_DO_NUM];
	void UpdDoWidth(void);

	// 延迟
	CSpinButtonCtrl m_spinDoDly[TOT_DO_NUM];
	CStatic m_txtDoDly[TOT_DO_NUM];
	void UpdDoDly(void);

	// 触发 - 仅针对脉冲模式
	CButton m_btnDoTrig[TOT_DO_NUM];
	void SetDoTrig(U8 do_chan);
	afx_msg void OnBnClickedBtnDoTrig0(void);
	afx_msg void OnBnClickedBtnDoTrig1(void);
	afx_msg void OnBnClickedBtnDoTrig2(void);
	afx_msg void OnBnClickedBtnDoTrig3(void);
	afx_msg void OnBnClickedBtnDoTrig4(void);
	afx_msg void OnBnClickedBtnDoTrig5(void);
	afx_msg void OnBnClickedBtnDoTrig6(void);
	afx_msg void OnBnClickedBtnDoTrig7(void);

	// 命令 - 仅针对电平模式
	CButton m_chkDoCmd[TOT_DO_NUM];
	void SetDoCmd(U8 do_chan);
	afx_msg void OnBnClickedChkDoCmd0(void);
	afx_msg void OnBnClickedChkDoCmd1(void);
	afx_msg void OnBnClickedChkDoCmd2(void);
	afx_msg void OnBnClickedChkDoCmd3(void);
	afx_msg void OnBnClickedChkDoCmd4(void);
	afx_msg void OnBnClickedChkDoCmd5(void);
	afx_msg void OnBnClickedChkDoCmd6(void);
	afx_msg void OnBnClickedChkDoCmd7(void);

	void SetDoWhole(U8 byte);
	afx_msg void OnBnClickedBtnAuoTstDo(void);	// 自动测试

	afx_msg void OnBnClickedBtnAllDoSet(void);	// 全部置位
	afx_msg void OnBnClickedBtnAllDoClr(void);	// 全部清零

	void EnbDoWidthDly(U8 nDoChan, BOOL bEnb);	// 使能DO宽度和延迟控件

	DECLARE_MESSAGE_MAP()
};
