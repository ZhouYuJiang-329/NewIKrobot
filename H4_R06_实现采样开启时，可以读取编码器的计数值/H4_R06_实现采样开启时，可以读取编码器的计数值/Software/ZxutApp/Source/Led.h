#pragma once

typedef enum _ET_LED_TYPE
{
	LED_CIRCLE	= 0,	// 圆形
	LED_SQUARE	= 1		// 正方形
} ET_LED_TYPE;

typedef enum _ET_LED_STATE
{
	LED_ON		= 0,	// 开
	LED_OFF		= 1,	// 关
	LED_DIS		= 2		// 禁止
} ET_LED_STATE;

class CLed : public CStatic
{
public:
	CLed(void);
	virtual ~CLed(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 颜色

	COLORREF m_crBK;
	void SetBKColor(COLORREF C);
	COLORREF GetBKColor(void);

	COLORREF m_crOnFG;
	CBrush *m_brOnFG;
	HPEN m_penOn;
	void SetOnFgColor(COLORREF C);
	COLORREF GetOnFgColor(void);

	COLORREF m_crOffFG;
	CBrush *m_brOffFG;
	HPEN m_penOff;
	void SetOffFgColor(COLORREF C);
	COLORREF GetOffFgColor(void);

	COLORREF m_crDisFG;
	CBrush *m_brDisFG;
	HPEN m_penDis;
	void SetDisFgColor(COLORREF C);
	COLORREF GetDisFgColor(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 类型

	ET_LED_TYPE m_nType;
	ET_LED_TYPE GetType(void);
	void SetType(ET_LED_TYPE type);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 状态

	ET_LED_STATE m_etState;
	ET_LED_STATE GetState();
	void SetState(ET_LED_STATE etState);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 显示文本

	bool m_bTextOn;
	bool GetTextOnOff();
	void SetTextOnOff(bool val);

	CString m_sOnString;
	CString GetOnText();
	void SetOnText(CString str);

	CString m_sOffString;
	CString GetOffText();
	void SetOffText(CString str);

protected:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	void DrawFigure(void);
};
