///////////////////////////////////////////////////////////////////////////////////////////////////
//
// InPlaceComboBox.cpp - InPlaceComboBox类的实现
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InPlaceComboBox.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// CInPlaceComboBox

CInPlaceComboBox::CInPlaceComboBox(void)
{
}

CInPlaceComboBox::CInPlaceComboBox(int iItem, int iSubItem,
	CStringList *plstItems, int nSel)
{
	m_iItem = iItem;
	m_iSubItem = iSubItem;

	m_lstItems.AddTail(plstItems);
	m_nSel = nSel;
	m_bESC = FALSE;
}

CInPlaceComboBox::~CInPlaceComboBox(void)
{
}

BEGIN_MESSAGE_MAP(CInPlaceComboBox, CComboBox)
	//{{AFX_MSG_MAP(CInPlaceComboBox)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_NCDESTROY()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////
// CInPlaceComboBox消息处理函数

int CInPlaceComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (-1 == CComboBox::OnCreate(lpCreateStruct))
		return -1;

	// Set the proper font
	CFont* font = GetParent()->GetFont();
	SetFont(font);

	for (POSITION pos = m_lstItems.GetHeadPosition(); pos != NULL;)
	{
		AddString((LPCTSTR) (m_lstItems.GetNext(pos)));
	}

	SetCurSel(m_nSel);
	SetFocus();

	return 0;
}

BOOL CInPlaceComboBox::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		if (pMsg->wParam == VK_RETURN
			|| pMsg->wParam == VK_ESCAPE)
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);

			return TRUE;				// DO NOT process further
		}
	}

	// 将上下键调换
	if (pMsg->wParam == VK_UP)
		pMsg->wParam = VK_DOWN;
	else if (pMsg->wParam == VK_DOWN)
		pMsg->wParam = VK_UP;
	else if (pMsg->wParam == VK_PRIOR)
		pMsg->wParam = VK_NEXT;
	else if (pMsg->wParam == VK_NEXT)
		pMsg->wParam = VK_PRIOR;

	return CComboBox::PreTranslateMessage(pMsg);
}

void CInPlaceComboBox::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);

	PostMessage(WM_CLOSE);
}

void CInPlaceComboBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (VK_ESCAPE == nChar)
			m_bESC = TRUE;

		GetParent()->SetFocus();

		return;
	}

	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}

void CInPlaceComboBox::OnNcDestroy(void)
{
	CComboBox::OnNcDestroy();

	delete this;
}

void CInPlaceComboBox::OnCloseup(void)
{
	GetParent()->SetFocus();
}

void CInPlaceComboBox::OnSelchange(void)
{
	// TODO: Add your control notification handler code here
	CString str;
	GetWindowText(str);

	// Send Notification to parent of ListView ctrl
	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_TEXT;
	dispinfo.item.iItem = m_iItem;
	dispinfo.item.iSubItem = m_iSubItem;
	dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
	dispinfo.item.cchTextMax = GetCurSel();//str.GetLength();

	GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);
}
