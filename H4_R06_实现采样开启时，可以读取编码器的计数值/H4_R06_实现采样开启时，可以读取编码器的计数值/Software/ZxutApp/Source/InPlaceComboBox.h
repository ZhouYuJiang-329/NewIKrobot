///////////////////////////////////////////////////////////////////////////////////////////////////
//
// InPlaceComboBox.h - InPlaceComboBox类的接口
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_InPlaceComboBox_H__4FFC25A2_8E11_11D4_B497_98854538F131__INCLUDED_)
#define AFX_InPlaceComboBox_H__4FFC25A2_8E11_11D4_B497_98854538F131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInPlaceComboBox : public CComboBox
{
	// 构造函数
public:
	CInPlaceComboBox(void);
	CInPlaceComboBox(int iItem, int iSubItem, CStringList *plstItems, int nSel);

	// 属性
public:

	// 操作
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceComboBox)
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// 实现
public:
	virtual ~CInPlaceComboBox(void);

	// 生成消息映射函数
protected:
	//{{AFX_MSG(CInPlaceComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy(void);
	afx_msg void OnCloseup(void);
	afx_msg void OnSelchange(void);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int 	m_iItem;
	int 	m_iSubItem;
	int 	m_nSel;
	BOOL	m_bESC;				// 表示ESC键是否被按下
	CStringList m_lstItems;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_InPlaceComboBox_H__4FFC25A2_8E11_11D4_B497_98854538F131__INCLUDED_)
