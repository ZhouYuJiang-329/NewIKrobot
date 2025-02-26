#pragma once

class CZxutApp;

class CDlgDevUpd : public CDialog
{
	DECLARE_DYNAMIC(CDlgDevUpd)

public:
	enum { IDD = IDD_DEV_UPD };

	CDlgDevUpd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDevUpd(void);
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);

	CZxutApp* m_pApp;

	U8 x_nTotBrd;

	CButton m_chkDuBrd[MAX_BRD_NUM];
	CButton m_btnDuBrdAll;
	CButton m_btnDuBrdClr;

	CButton m_chkDuTypeBoot;
	CButton m_chkDuTypeDtb;
	CButton m_chkDuTypeKernel;
	CButton m_chkDuTypeRootfs;
	CButton m_chkDuTypeCfg;
	CButton m_chkDuTypeDrv;
	CButton m_chkDuTypeApp;
	CButton m_btnDuTypeAll;
	CButton m_btnDuTypeClr;

	CButton m_btnDuUpd;
	afx_msg void OnBnClickedBtnDuUpd(void);

	void FreshDuCtrl(BOOL bSmplEnb);

	afx_msg void OnBnClickedBtnDuBrdAll(void);
	afx_msg void OnBnClickedBtnDuBrdClr(void);
	afx_msg void OnBnClickedBtnDuTypeAll(void);
	afx_msg void OnBnClickedBtnDuTypeClr(void);

	void DuTypeEnb(BOOL enb);

	DECLARE_MESSAGE_MAP()
};
