#pragma once

#include "FlawParamAdj.h"

class CDlgFlawParam : public CDialog
{
	DECLARE_DYNAMIC(CDlgFlawParam)

public:
	CDlgFlawParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFlawParam(void);
	enum { IDD = IDD_FLAW_PARAM };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);
	virtual void OnOK(void);

	CZxutApp* m_pApp;

	CStatic m_txtNetRate;		// 网络速率
	CButton m_btnNetRate;
	void UpdNetRate(void);
	afx_msg void OnBnClickedBtnNetRate(void);

	CStatic m_txtDaqRate;		// 采集率
	void UpdDaqRate(void);

	CStatic m_txtSmplTimes;		// 采样次数
	void UpdSmplTimes(void);

	CStatic m_txtAccTimes;		// 累积次数
	void UpdAccTimes(void);

	CStatic m_txtSpDiff;		// 声程差
	void UpdSpDiff(void);

	CButton m_btnSyncParam;		// 参数同步
	afx_msg void OnBnClickedBtnSyncParam(void);

	// 以2dB步进进行增减
	CButton m_btnDbPlus;
	CButton m_btnDbMinus;
	afx_msg void OnBnClickedBtnDbPlus(void);
	afx_msg void OnBnClickedBtnDbMinus(void);

	CButton m_btnAutoGain;		// 自动增益
	afx_msg void OnBnClickedBtnAutoGain(void);

	CButton m_btnTstVertLinear;
	CEdit m_edtTstSpan;
	afx_msg void OnBnClickedBtnTstVertLinear(void);	// 垂直线性测量

	CButton m_chkDacCalib;
	afx_msg void OnBnClickedChkDacCalib(void);

	CButton m_btnTstUsrReg;
	afx_msg void OnBnClickedBtnTstUsrReg(void);		// 测试用户寄存器

	afx_msg void OnBnClickedBtnChanEnb(void);		// 通道使能对话框

	afx_msg void OnBnClickedBtnMaxRptFreq(void);	// 获取最大重复频率

	CEdit m_edtMaxDaqRate;	// 最大采集率

	DECLARE_MESSAGE_MAP()

private:
	CFlawParamAdj m_dlgFlawParamAdj;
};
