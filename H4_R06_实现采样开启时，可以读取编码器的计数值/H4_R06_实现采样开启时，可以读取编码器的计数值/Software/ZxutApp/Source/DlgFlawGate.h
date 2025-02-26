#pragma once

#include "FlawGateAdj.h"

class CDlgFlawGate : public CDialog
{
	DECLARE_DYNAMIC(CDlgFlawGate)

public:
	CDlgFlawGate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFlawGate(void);
	enum { IDD = IDD_FLAW_GATE };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(void);

	CZxutApp* m_pApp;
	CFlawGateAdj m_dlgFlawGateAdj;

	////////////////////////////////////////////////////////////////////////////////////////////////

	CFont m_fntTxt;
	void UpdGateRes(U8 gate_sel);

	DECLARE_MESSAGE_MAP()
};
