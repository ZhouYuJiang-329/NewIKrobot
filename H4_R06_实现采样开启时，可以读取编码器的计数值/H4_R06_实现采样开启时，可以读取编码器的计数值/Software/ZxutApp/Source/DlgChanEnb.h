#pragma once

class CZxutApp;

class CDlgChanEnb : public CDialog
{
	DECLARE_DYNAMIC(CDlgChanEnb)

public:
	CDlgChanEnb(CWnd* pParent = NULL);   // 标准构造函数
	enum { IDD = IDD_CHAN_ENB };
	virtual ~CDlgChanEnb(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);

	DECLARE_MESSAGE_MAP()

public:
	CZxutApp* m_pApp;

	U8 x_nTotBrd;
	U8 x_nTotHard;
	U8 x_nTotSoft;

	CButton m_grpBrd	[MAX_BRD_NUM];
	CButton m_btnSet	[MAX_BRD_NUM];
	CButton m_btnClr	[MAX_BRD_NUM];

	CButton m_txtHard	[TOT_HARD_NUM];

	CButton m_chkChanEnb[TOT_HARD_NUM][MAX_SOFT_NUM];

	void ExecChanEnb(U8 brd, BOOL enb);
	void UpdChanEnbCtrl(void);	// 更新通道使能控件

	CButton m_btnUpdChanEnb;
	afx_msg void OnBnClickedBtnUpdChanEnb(void);

	void OnBnClickedBtnBrd(BOOL enb);

	CButton m_btnAllSet;
	afx_msg void OnBnClickedBtnSetBrd(void);
	afx_msg void OnBnClickedBtnSetAll(void);

	CButton m_btnAllClr;
	afx_msg void OnBnClickedBtnClrBrd(void);
	afx_msg void OnBnClickedBtnClrAll(void);

	CEdit m_edtChanShare[TOT_HARD_NUM];	// 通道时间占额
	CEdit m_edtSynDly[MAX_BRD_NUM];		// 同步延迟
};
