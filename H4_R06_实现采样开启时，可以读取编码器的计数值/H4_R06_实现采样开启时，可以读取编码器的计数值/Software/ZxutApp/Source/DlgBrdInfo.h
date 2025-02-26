#pragma once

class CDlgBrdInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgBrdInfo)

public:
	CDlgBrdInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBrdInfo(void);
	virtual BOOL OnInitDialog(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	enum { IDD = IDD_BRD_INFO };

	CStatic m_txtIpAddr	[MAX_BRD_NUM];
	CStatic m_txtMacAddr[MAX_BRD_NUM];

	CStatic m_txtBrdSn	[MAX_BRD_NUM][BRD_SN_TYPE_NUM];

	CZxutApp* m_pApp;

	DECLARE_MESSAGE_MAP()
};
