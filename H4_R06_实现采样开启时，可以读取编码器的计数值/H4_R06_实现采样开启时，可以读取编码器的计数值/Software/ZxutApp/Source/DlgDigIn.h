#pragma once

#include "Led.h"

class CDlgDigIn : public CDialog
{
	DECLARE_DYNAMIC(CDlgDigIn)

public:
	CDlgDigIn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDigIn(void);
	enum { IDD = IDD_DIG_IN };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CZxutApp* m_pApp;
	U8 x_nTotBrd;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	////////////////////////////////////////////////////////////////////////////////////////////////

	CButton m_chkDiTstEnb;
	afx_msg void OnBnClickedChkDiTstEnb(void);

	CEdit m_edtDiTstFreq;
	CEdit m_edtDiTstWidth;
	CStatic m_txtDiTstNote;

	CComboBox m_combDiTstIdx;
	afx_msg void OnCbnSelchangeComboDiTstChan(void);

	// DI结果
	CLed m_ledDiRes[TOT_DI_NUM];
	void UpdDigIn(U8 dig_in);

	// 时基
	CComboBox m_combDiBase;
	afx_msg void OnCbnSelchangeComboDiBase(void);

	// 使能
	CButton m_chkDiEnb[TOT_DI_NUM];
	void SetDiEnb(U8 di_chan);
	afx_msg void OnBnClickedChkDiEnb0(void);
	afx_msg void OnBnClickedChkDiEnb1(void);
	afx_msg void OnBnClickedChkDiEnb2(void);
	afx_msg void OnBnClickedChkDiEnb3(void);
	afx_msg void OnBnClickedChkDiEnb4(void);
	afx_msg void OnBnClickedChkDiEnb5(void);
	afx_msg void OnBnClickedChkDiEnb6(void);
	afx_msg void OnBnClickedChkDiEnb7(void);

	// 模式
	CComboBox m_combDiMode[TOT_DI_NUM];
	void SetDiMode(U8 di_chan);
	afx_msg void OnCbnSelchangeComboDiMode0(void);
	afx_msg void OnCbnSelchangeComboDiMode1(void);
	afx_msg void OnCbnSelchangeComboDiMode2(void);
	afx_msg void OnCbnSelchangeComboDiMode3(void);
	afx_msg void OnCbnSelchangeComboDiMode4(void);
	afx_msg void OnCbnSelchangeComboDiMode5(void);
	afx_msg void OnCbnSelchangeComboDiMode6(void);
	afx_msg void OnCbnSelchangeComboDiMode7(void);

	// 极性
	CComboBox m_combDiPol[TOT_DI_NUM];
	void SetDiPol(U8 di_chan);
	afx_msg void OnCbnSelchangeComboDiPol0(void);
	afx_msg void OnCbnSelchangeComboDiPol1(void);
	afx_msg void OnCbnSelchangeComboDiPol2(void);
	afx_msg void OnCbnSelchangeComboDiPol3(void);
	afx_msg void OnCbnSelchangeComboDiPol4(void);
	afx_msg void OnCbnSelchangeComboDiPol5(void);
	afx_msg void OnCbnSelchangeComboDiPol6(void);
	afx_msg void OnCbnSelchangeComboDiPol7(void);

	// 宽度
	CSpinButtonCtrl m_spinDiWidth[TOT_DI_NUM];
	CStatic m_txtDiWidth[TOT_DI_NUM];
	void UpdDiWidth(void);

	// 延迟
	CSpinButtonCtrl m_spinDiDly[TOT_DO_NUM];
	CStatic m_txtDiDly[TOT_DI_NUM];
	void UpdDiDly(void);

	// 清除
	CButton m_btnDiClr[TOT_DI_NUM];
	void SetDiClr(U8 di_chan);
	afx_msg void OnBnClickedBtnDiClr0(void);
	afx_msg void OnBnClickedBtnDiClr1(void);
	afx_msg void OnBnClickedBtnDiClr2(void);
	afx_msg void OnBnClickedBtnDiClr3(void);
	afx_msg void OnBnClickedBtnDiClr4(void);
	afx_msg void OnBnClickedBtnDiClr5(void);
	afx_msg void OnBnClickedBtnDiClr6(void);
	afx_msg void OnBnClickedBtnDiClr7(void);

	afx_msg void OnBnClickedBtnAuoTstDo(void);
	afx_msg void OnBnClickedBtnAllDiSet(void);
	afx_msg void OnBnClickedBtnAllDiClr(void);

	void EnbDiWidthDly(U8 nDiChan, BOOL bEnb);	// 使能DI宽度和延迟控件

	DECLARE_MESSAGE_MAP()
};
