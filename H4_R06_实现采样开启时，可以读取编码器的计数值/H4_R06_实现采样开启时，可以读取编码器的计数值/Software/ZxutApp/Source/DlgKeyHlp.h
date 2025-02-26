#pragma once

class CDlgKeyHlp : public CDialog
{
	DECLARE_DYNAMIC(CDlgKeyHlp)

public:
	CDlgKeyHlp(CWnd* pParent = NULL);   // 标准构造函数
	enum { IDD = IDD_KEY_HLP };
	virtual ~CDlgKeyHlp(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
