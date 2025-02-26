#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgKeyHlp.h"

IMPLEMENT_DYNAMIC(CDlgKeyHlp, CDialog)

CDlgKeyHlp::CDlgKeyHlp(CWnd* pParent) : CDialog(CDlgKeyHlp::IDD, pParent)
{
}

CDlgKeyHlp::~CDlgKeyHlp(void)
{
}

void CDlgKeyHlp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgKeyHlp, CDialog)
END_MESSAGE_MAP()
