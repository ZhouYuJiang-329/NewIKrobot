#pragma once

class CZxutApp;

class CDlgAbout : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAbout(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);

	enum { IDD = IDD_ABOUT };

	CZxutApp* m_pApp;

	DECLARE_MESSAGE_MAP()
};
