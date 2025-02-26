#pragma once

const U8 SN_TCG_TP_NUM = 0;		// 序号
const U8 SN_TCG_TP_LOC = 1;		// 位置
const U8 SN_TCG_TP_GAIN = 2;	// 增益

class CDlgTcgProc : public CDialog
{
	DECLARE_DYNAMIC(CDlgTcgProc)

public:
	CDlgTcgProc(CWnd* pParent = NULL);   // 标准构造函数
	enum { IDD = IDD_TCG_PROC };
	virtual ~CDlgTcgProc(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);

	CZxutApp* m_pApp;

	CListCtrl m_lstTcgTp;
	void FreshTcgColText(void);

	CButton m_chkTcgEnb;
	CButton m_btnTcgTpAdd;
	CButton m_btnTcgTpDel;
	CButton m_btnTcgTpRst;

	void SelTcgTp(U8 idx);	// 选择测试点
	void FreshTcgTp(void);	// 更新TCG参数
	void SortTcgTp(void);	// 参考点排序

	U8 m_nTcgTpIdx;	// 当前测试点
	void FreshTcgBtnSts(void);	// 更新按钮状态
	void ProcTcgEnb(BOOL enb);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedChkEnvlpEnb(void);
	afx_msg void OnBnClickedChkTcgEnb(void);
	afx_msg void OnBnClickedBtnTcgAddTp(void);
	afx_msg void OnBnClickedBtnTcgDelTp(void);
	afx_msg void OnBnClickedBtnTcgRstTp(void);
	afx_msg void OnNMClickLstTcgTp(NMHDR *pNMHDR, LRESULT *pResult);
};
