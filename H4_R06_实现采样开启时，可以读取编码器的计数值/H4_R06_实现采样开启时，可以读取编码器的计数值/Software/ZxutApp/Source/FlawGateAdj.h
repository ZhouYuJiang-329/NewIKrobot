#pragma once

#include "ZxutApp.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 探伤闸门位置(行)定义

const U32 ROW_LOC_GATE_START	= 0;
const U32 ROW_LOC_GATE_WIDTH	= 1;
const U32 ROW_LOC_GATE_HEIGHT	= 2;
const U32 ROW_LOC_GATE_POL		= 3;
const U32 ROW_LOC_FLAW_TYPE		= 4;
const U32 ROW_LOC_PEAK_HORI		= 5;
const U32 ROW_LOC_PEAK_VERT		= 6;
const U32 ROW_LOC_GATE_ENB		= 7;

const U32 COL_LOC_GATE[] = {1, 3, 5, 7};

class CFlawGateAdj : public CListCtrl
{
	DECLARE_DYNAMIC(CFlawGateAdj)

public:
	CFont m_fontStyle;
	CZxutApp* m_pApp;

	CFlawGateAdj(void);
	~CFlawGateAdj(void);

	virtual COLORREF OnGetCellTextColor (int nRow, int nCol);
	virtual COLORREF OnGetCellBkColor (int nRow, int nCol);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	int HitTestEx(const CPoint &point, int* const col) const;
	CComboBox* ShowInPlaceList(const int& Item, const int& Col, CStringList &lstItems,
		const int& Sel, const U8& Flag = 0);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);

	void InitFlawGate(void);
	void FreshFlawGate(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 调节闸门

	void AdjGateStart(LV_ITEM* const plvItem);
	void AdjGateWidth(LV_ITEM* const plvItem);
	void AdjGateHeight(LV_ITEM* const plvItem);
	void AdjGatePol(LV_ITEM* const plvItem);
	void AdjFlawType(LV_ITEM* const plvItem);
	void AdjGateEnb(LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 选择闸门

	void OptGateStart(const int& nRow, const int& nCol);
	void OptGateWidth(const int& nRow, const int& nCol);
	void OptGateHeight(const int& nRow, const int& nCol);
	void OptGatePol(const int& nRow, const int& nCol);
	void OptFlawType(const int& nRow, const int& nCol);
	void OptGateEnb(const int& nRow, const int& nCol);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 刷新闸门

	void FreshGateStart(U8 gate_sel);
	void FreshGateWidth(U8 gate_sel);
	void FreshGateHeight(U8 gate_sel);
	void FreshGatePol(U8 gate_sel);
	void FreshFlawType(U8 gate_sel);
	void FreshPeakHori(U8 gate_sel, CString& str);
	void FreshPeakVert(U8 gate_sel, CString& str);
	void FreshGateEnb(U8 gate_sel);

	DECLARE_MESSAGE_MAP()
};
