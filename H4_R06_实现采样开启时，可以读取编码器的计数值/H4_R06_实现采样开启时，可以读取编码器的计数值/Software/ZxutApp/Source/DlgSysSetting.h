#pragma once

class CZxutApp;

class CDlgSysSetting : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysSetting)

public:
	enum { IDD = IDD_SYS_SETTING };
	CDlgSysSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysSetting(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(VOID);
	virtual void OnOK(void);

	CZxutApp* m_pApp;
	U8 x_nTotBrd;
	CEdit m_edtIpAddr[5];
	CEdit m_edtNetPort;

	CStatic m_txtCpuTemp[MAX_BRD_NUM];	// 核心板温度值
	CStatic m_txtPcbTemp[MAX_BRD_NUM];	// 通道板温度值
	CStatic m_txtDifTemp[MAX_BRD_NUM];	// 温差
	void UpdTempValue(U8 brd_num);

	afx_msg void OnBnClickedBtnUpdSetNetCfg(void);	// 更新设定的网络配置
	afx_msg void OnBnClickedBtnUpdDefNetCfg(void);	// 更新缺省的网络配置

	afx_msg void OnBnClickedBtnBrdInfo(void);	// 读取通道板信息

	CEdit m_edtNeedBrdNum;

	CButton m_chkSmplAct;
	afx_msg void OnBnClickedChkSmplAct(void);		// 一打开软件就开启采样

	CButton m_btnUpdSetNetCfg;
	CButton m_btnUpdDefNetCfg;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 板号

	CString		m_strBrdSn	[BRD_SN_TYPE_NUM];
	CEdit		m_edtBrdSn	[BRD_SN_TYPE_NUM];
	CButton		m_btnBrdSnRd[BRD_SN_TYPE_NUM];
	CButton		m_btnBrdSnWr[BRD_SN_TYPE_NUM];

	// 核心板
	afx_msg void OnBnClickedBtnSnRdCore(void);
	afx_msg void OnBnClickedBtnSnWrCore(void);

	// 通道板
	afx_msg void OnBnClickedBtnSnRdChan(void);
	afx_msg void OnBnClickedBtnSnWrChan(void);

	// 高压模块
	afx_msg void OnBnClickedBtnSnRdHv(void);
	afx_msg void OnBnClickedBtnSnWrHv(void);

	// 电源模块
	afx_msg void OnBnClickedBtnSnRdPwr(void);
	afx_msg void OnBnClickedBtnSnWrPwr(void);

	void UpdBrdSn(void);

	DECLARE_MESSAGE_MAP()
};
