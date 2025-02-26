#include "stdafx.h"
#include "InPlaceComboBox.h"
#include "FlawGateAdj.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CFlawGateAdj, CListCtrl)

////////////////////////////////////////////////////////////////////////////////////////////////////
// 消息映射

BEGIN_MESSAGE_MAP(CFlawGateAdj, CListCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CFlawGateAdj::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

	switch (lplvcd->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
			{
				int nCol = lplvcd->iSubItem;
				int iRow = (int) lplvcd->nmcd.dwItemSpec;

				lplvcd->clrTextBk = OnGetCellBkColor(iRow, nCol);
				lplvcd->clrText = OnGetCellTextColor(iRow, nCol);
			}

			*pResult = CDRF_DODEFAULT;
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int CFlawGateAdj::HitTestEx(const CPoint &point, int* const col) const
{
	int colnum = 0;
	int row = HitTest(point, NULL);
	if(col) *col = 0;

	// Make sure that the ListView is in LVS_REPORT
	if((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
		return row;

	// Get the top and bottom row visible
	row = GetTopIndex();
	int bottom = row + GetCountPerPage();
	if(bottom > GetItemCount())
		bottom = GetItemCount();

	// Get the number of columns
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();

	// Loop through the visible rows
	for(;row <= bottom;row++)
	{
		// Get bounding rect of item and check whether point falls in it.
		CRect rect;
		GetItemRect(row, &rect, LVIR_BOUNDS);
		if(rect.PtInRect(point))
		{
			// Now find the column
			for(colnum = 0; colnum < nColumnCount; colnum++)
			{
				int colwidth = GetColumnWidth(colnum);
				if(point.x >= rect.left
					&& point.x <= (rect.left + colwidth))
				{
					if(col) *col = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

CComboBox* CFlawGateAdj::ShowInPlaceList(const int& Item, const int& Col, CStringList &lstItems,
										  const int& Sel, const U8& Flag)
{
	// Get the column offset
	int offset = 0;
	for(int i = 0; i < Col; i++)
		offset += GetColumnWidth(i);

	CRect rect;
	GetItemRect(Item,&rect,LVIR_BOUNDS);

	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(&rcClient);
	if(offset + rect.left < 0 || offset + rect.left > rcClient.right)
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}

	rect.left += offset;//+4;
	rect.right = rect.left + GetColumnWidth(Col);

	int height;
	if (0 == Flag)
	{
		height = rect.bottom-rect.top-1;
		rect.top -= 2;
		rect.bottom += 10*height;
		if(rect.right > rcClient.right)
		{
			rect.right = rcClient.right;
		}
	}
	else
	{
		height = 0;
	}

	DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL
		| CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;

	CComboBox *pList = new CInPlaceComboBox(Item, Col, &lstItems, Sel);
	pList->Create(dwStyle, rect, this, NULL);
	if (0 == Flag)
	{
		pList->SetItemHeight(-1, height);
	}
	pList->SetHorizontalExtent(GetColumnWidth(Col));
	return pList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 构造闸门
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CFlawGateAdj::CFlawGateAdj(void)
{
	///////////////////////////////////////////////////////////////////////////
	// 创建字体，用于显示探伤闸门

	m_fontStyle.CreateFont(
		14, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, GB2312_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "Tahoma"
		);

	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pFlawGateAdj = this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 析构闸门
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CFlawGateAdj::~CFlawGateAdj(void)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 创建控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

int CFlawGateAdj::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	LRESULT dwStyle = SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | WS_CHILD;
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);
	ModifyStyleEx(0, WS_EX_STATICEDGE);

	SetFont(&m_fontStyle);
	InitFlawGate();
	FreshFlawGate();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 撤销控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::OnDestroy(void)
{
	CListCtrl::OnDestroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置单元前景色
//
////////////////////////////////////////////////////////////////////////////////////////////////////

COLORREF CFlawGateAdj::OnGetCellTextColor (int nRow, int nCol)
{
	return RGB(0, 0, 0);	// 全部为黑色
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置单元背景色
//
////////////////////////////////////////////////////////////////////////////////////////////////////

COLORREF CFlawGateAdj::OnGetCellBkColor (int nRow, int nCol)
{
	BOOL title = (nCol == 0) || (nCol == 2) || (nCol == 4) || (nCol == 6);

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	BOOL gate_enb[TOT_GATE_NUM];
	for (U8 p = 0; p < TOT_GATE_NUM; p++)
	{
		gate_enb[p] = param.m_astGateParam[hard_num][soft_num].m_bEnb[p];
	}

	BOOL trace_enb = param.m_abTraceEnb[hard_num][soft_num];

	if ((nRow == 7) && (nCol == 1))
	{
		return ITEM_DISABLED_COLOR;	// 闸门A恒定使能
	}
	else if (title)
	{
		return ITEM_BACKGRD_COLOR;
	}
	else if (trace_enb)	// 闸门跟踪使能，禁止调节所有闸门参数
	{
		return ITEM_DISABLED_COLOR;
	}
	else if (
		(!gate_enb[0] && (nCol == 1) && (nRow != 7)) ||
		(!gate_enb[1] && (nCol == 3) && (nRow != 7)) ||
		(!gate_enb[2] && (nCol == 5) && (nRow != 7)) ||
		(!gate_enb[3] && (nCol == 7) && (nRow != 7)))
	{
		return ITEM_DISABLED_COLOR;	// 闸门关闭，禁止调节除闸门使能之外的项目
	}
	else
	{
		return RGB (255, 255, 255);	// 白色
	}
}

BOOL CFlawGateAdj::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		if (pMsg->wParam == VK_RETURN
			|| pMsg->wParam == VK_ESCAPE)
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);

			return true;				// DO NOT process further
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

	return CListCtrl::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化探伤闸门列表
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::InitFlawGate(void)
{
	InsertColumn(0, "闸门A",	LVCFMT_LEFT, 60, 0);
	InsertColumn(1, "参数值",	LVCFMT_LEFT, 100, 0);
	InsertColumn(2, "闸门B",	LVCFMT_LEFT, 60, 0);
	InsertColumn(3, "参数值",	LVCFMT_LEFT, 100, 0);
	InsertColumn(4, "闸门C",	LVCFMT_LEFT, 60, 0);
	InsertColumn(5, "参数值",	LVCFMT_LEFT, 100, 0);
	InsertColumn(6, "闸门I",	LVCFMT_LEFT, 60, 0);
	InsertColumn(7, "参数值",	LVCFMT_LEFT, 100, 0);

	////////////////////////////////////////////////////////////////////////////////////////////////

		InsertItem(ROW_LOC_GATE_START,		"闸门起点");
		InsertItem(ROW_LOC_GATE_WIDTH,		"闸门宽度");
		InsertItem(ROW_LOC_GATE_HEIGHT,		"闸门高度");
		InsertItem(ROW_LOC_GATE_POL,		"闸门极性");
		InsertItem(ROW_LOC_FLAW_TYPE,		"缺陷类型");
		InsertItem(ROW_LOC_PEAK_HORI,		"闸门声程");
		InsertItem(ROW_LOC_PEAK_VERT,		"闸门波高");
		InsertItem(ROW_LOC_GATE_ENB,		"闸门使能");

	for (U8 i = 0; i < 3; i++)
	{
		SetItemText(ROW_LOC_GATE_START,		(i + 1) * 2, "闸门起点");
		SetItemText(ROW_LOC_GATE_WIDTH,		(i + 1) * 2, "闸门宽度");
		SetItemText(ROW_LOC_GATE_HEIGHT,	(i + 1) * 2, "闸门高度");
		SetItemText(ROW_LOC_GATE_POL,		(i + 1) * 2, "闸门极性");
		SetItemText(ROW_LOC_FLAW_TYPE,		(i + 1) * 2, "缺陷类型");
		SetItemText(ROW_LOC_PEAK_HORI,		(i + 1) * 2, "闸门声程");
		SetItemText(ROW_LOC_PEAK_VERT,		(i + 1) * 2, "闸门波高");
		SetItemText(ROW_LOC_GATE_ENB,		(i + 1) * 2, "闸门使能");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 刷新所有探伤闸门
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::FreshFlawGate(void)
{
	for (U8 p = 0; p < TOT_GATE_NUM; p++)
	{
		FreshGateStart(p);
		FreshGateWidth(p);
		FreshGateHeight(p);
		FreshGatePol(p);
		FreshFlawType(p);
		FreshGateEnb(p);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 调节探伤闸门
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::OnEndlabeledit(NMHDR* pNMHDR,LRESULT* pResult)
{
	LV_DISPINFO  *plvDispInfo = (LV_DISPINFO *)pNMHDR;
	LV_ITEM		 *plvItem = &plvDispInfo->item;

	*pResult = NULL;

	if (plvItem->pszText != NULL)
	{
		SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);

		switch(plvItem->iItem)
		{
			case ROW_LOC_GATE_START:	return AdjGateStart(plvItem);
			case ROW_LOC_GATE_WIDTH:	return AdjGateWidth(plvItem);
			case ROW_LOC_GATE_HEIGHT:	return AdjGateHeight(plvItem);
			case ROW_LOC_GATE_POL:		return AdjGatePol(plvItem);
			case ROW_LOC_FLAW_TYPE:		return AdjFlawType(plvItem);
			case ROW_LOC_GATE_ENB:		return AdjGateEnb(plvItem);
			default: return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 探伤闸门选项
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
	int nRow, nCol;

	if (m_pApp->m_stFlawParam.m_abTraceEnb[m_pApp->m_nHardNum][m_pApp->m_nSoftNum])
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "跟踪已使能，不能调节闸门参数");
		return;
	}

	nRow = HitTestEx(point, &nCol);
	switch (nRow)
	{
		case ROW_LOC_GATE_START:	return OptGateStart(nRow, nCol);
		case ROW_LOC_GATE_WIDTH:	return OptGateWidth(nRow, nCol);
		case ROW_LOC_GATE_HEIGHT:	return OptGateHeight(nRow, nCol);
		case ROW_LOC_GATE_POL:		return OptGatePol(nRow, nCol);
		case ROW_LOC_FLAW_TYPE:		return OptFlawType(nRow, nCol);
		case ROW_LOC_GATE_ENB:		return OptGateEnb(nRow, nCol);
		default: return;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门起点
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::AdjGateStart(LV_ITEM* const plvItem)
{
	U8 gate_sel = (plvItem->iSubItem - 1) / 2;	// 闸门索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	U16& gate_start = param.m_astGateParam[hard_num][soft_num].m_nStart[gate_sel];
	gate_start = plvItem->cchTextMax;

	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	ZXUT_SetGateStart(hard_num, soft_num, gate_sel, gate_start * smpl_depth / SHOW_SMPL_WIDTH);
}

void CFlawGateAdj::FreshGateStart(U8 gate_sel)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	U16 gate_start = param.m_astGateParam[hard_num][soft_num].m_nStart[gate_sel];
	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
	U16 start = gate_start * smpl_depth / SHOW_SMPL_WIDTH;
	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
	F32 time = ZXUT_GetTstTime(freq_ratio, start, 0) * 0.001f;	// ns -> us
	F32 range = ZXUT_GetTstRange(freq_ratio, start, 0, sound_velo);

	switch (param.m_nHoriDisp)
	{
		case HORI_DISP_MM:
			str.Format("%.2f", range);	// mm
			break;

		case HORI_DISP_US:
			str.Format("%.2f", time);	// us
			break;

		case HORI_DISP_DOTS:
			str.Format("%d", start);	// 点数
	}
	SetItemText(ROW_LOC_GATE_START, nCol, str);
}

void CFlawGateAdj::OptGateStart(const int& nRow, const int& nCol)
{
	U8 gate_sel = (nCol - 1) / 2;	// 闸门索引
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 gate_start = param.m_astGateParam[hard_num][soft_num].m_nStart[gate_sel];
	U16 gate_width = param.m_astGateParam[hard_num][soft_num].m_nWidth[gate_sel];

	BOOL enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];
	if (enb == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "闸门尚未使能，不能调节闸门起点");
		return;
	}

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
		U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
		for (U16 i = 0; i < SHOW_SMPL_WIDTH - gate_width; i++)
		{
			U32 start = i * smpl_depth / SHOW_SMPL_WIDTH;
			U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
			F32 time = ZXUT_GetTstTime(freq_ratio, start, 0) * 0.001f;	// ns -> us
			F32 range = ZXUT_GetTstRange(freq_ratio, start, 0, sound_velo);

			switch (param.m_nHoriDisp)
			{
				case HORI_DISP_MM:
					str.Format("%.2f", range);	// mm
					break;

				case HORI_DISP_US:
					str.Format("%.2f", time);	// us
					break;

				case HORI_DISP_DOTS:
					str.Format("%d", start);	// 点数
			}
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, gate_start);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门宽度
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::AdjGateWidth(LV_ITEM* const plvItem)
{
	U8 gate_sel = (plvItem->iSubItem - 1) / 2;	// 闸门索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16& gate_width = param.m_astGateParam[hard_num][soft_num].m_nWidth[gate_sel];

	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	gate_width = plvItem->cchTextMax + GATE_WIDTH_MIN;
	ZXUT_SetGateWidth(hard_num, soft_num, gate_sel, gate_width * smpl_depth / SHOW_SMPL_WIDTH);
}

void CFlawGateAdj::FreshGateWidth(U8 gate_sel)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 gate_width = param.m_astGateParam[hard_num][soft_num].m_nWidth[gate_sel];

	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
	U16 width = gate_width * smpl_depth / SHOW_SMPL_WIDTH;
	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
	F32 time = ZXUT_GetTstTime(freq_ratio, width, 0) * 0.001f;	// ns -> us
	F32 range = ZXUT_GetTstRange(freq_ratio, width, 0, sound_velo);

	switch (param.m_nHoriDisp)
	{
		case HORI_DISP_MM:
			str.Format("%.2f", range);		// mm
			break;

		case HORI_DISP_US:
			str.Format("%.2f", time);		// us
			break;

		case HORI_DISP_DOTS:
			str.Format("%d", gate_width);	// 点数
	}
	SetItemText(ROW_LOC_GATE_WIDTH, nCol, str);
}

void CFlawGateAdj::OptGateWidth(const int& nRow, const int& nCol)
{
	U8 gate_sel = (nCol - 1) / 2;	// 闸门索引
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 gate_start = param.m_astGateParam[hard_num][soft_num].m_nStart[gate_sel];
	U16 gate_width = param.m_astGateParam[hard_num][soft_num].m_nWidth[gate_sel];

	BOOL enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];
	if (enb == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "闸门尚未使能，不能调节闸门宽度");
		return;
	}

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
		U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
		for (U16 i = GATE_WIDTH_MIN; i < SHOW_SMPL_WIDTH - gate_start; i++)
		{
			U32 width = i * smpl_depth / SHOW_SMPL_WIDTH;
			U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
			F32 time = ZXUT_GetTstTime(freq_ratio, width, 0) * 0.001f;	// ns -> us
			F32 range = ZXUT_GetTstRange(freq_ratio, width, 0, sound_velo);

			switch (param.m_nHoriDisp)
			{
				case HORI_DISP_MM:
					str.Format("%.2f", range);	// mm
					break;

				case HORI_DISP_US:
					str.Format("%.2f", time);	// us
					break;

				case HORI_DISP_DOTS:
					str.Format("%d", width);	// 点数
			}
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, gate_width - GATE_WIDTH_MIN);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门高度
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::AdjGateHeight(LV_ITEM* const plvItem)
{
	U8 gate_sel = (plvItem->iSubItem - 1) / 2;	// 闸门索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16& gate_height = param.m_astGateParam[hard_num][soft_num].m_nHeight[gate_sel];

	gate_height = plvItem->cchTextMax + GATE_HEIGHT_MIN;
	ZXUT_SetGateHeight(hard_num, soft_num, gate_sel, gate_height * m_pApp->m_nSmplWaveYRatio);
}

void CFlawGateAdj::FreshGateHeight(U8 gate_sel)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 gate_height = param.m_astGateParam[hard_num][soft_num].m_nHeight[gate_sel];

	if (param.m_nVertDisp == VERT_DISP_PERC)
		str.Format("%.1f%%", gate_height * 100.0f / SHOW_SMPL_HEIGHT);
	else
		str.Format("%d", gate_height * m_pApp->m_nSmplWaveYRatio);
	SetItemText(ROW_LOC_GATE_HEIGHT, nCol, str);
}

void CFlawGateAdj::OptGateHeight(const int& nRow, const int& nCol)
{
	U8 gate_sel = (nCol - 1) / 2;	// 闸门索引
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 gate_height = param.m_astGateParam[hard_num][soft_num].m_nHeight[gate_sel];

	BOOL enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];
	if (enb == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "闸门尚未使能，不能调节闸门高度");
		return;
	}

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U16 i = GATE_HEIGHT_MIN; i < SHOW_SMPL_HEIGHT - GATE_HEIGHT_MIN + 2; i++)
		{
			if (param.m_nVertDisp == VERT_DISP_PERC)
				str.Format("%.1f%%", i * 100.0f / SHOW_SMPL_HEIGHT);
			else
				str.Format("%d", i * m_pApp->m_nSmplWaveYRatio);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, gate_height - GATE_HEIGHT_MIN);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门极性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::AdjGatePol(LV_ITEM* const plvItem)
{
	U8 gate_sel = (plvItem->iSubItem - 1) / 2;	// 闸门索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& gate_pol = param.m_astGateParam[hard_num][soft_num].m_nPol[gate_sel];

	gate_pol = plvItem->cchTextMax;
	ZXUT_SetGatePol(hard_num, soft_num, gate_sel, gate_pol);
}

void CFlawGateAdj::FreshGatePol(U8 gate_sel)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 gate_pol = param.m_astGateParam[hard_num][soft_num].m_nPol[gate_sel];

	SetItemText(ROW_LOC_GATE_POL, nCol, GATE_POL_STR[gate_pol]);
}

void CFlawGateAdj::OptGatePol(const int& nRow, const int& nCol)
{
	U8 gate_sel = (nCol - 1) / 2;	// 闸门索引
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 gate_pol = param.m_astGateParam[hard_num][soft_num].m_nPol[gate_sel];

	BOOL enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];
	if (enb == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "闸门尚未使能，不能调节闸门极性");
		return;
	}

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			str.Format("%s", GATE_POL_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, gate_pol);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 缺陷类型
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::AdjFlawType(LV_ITEM* const plvItem)
{
	U8 gate_sel = (plvItem->iSubItem - 1) / 2;	// 闸门索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& flaw_type = param.m_astGateParam[hard_num][soft_num].m_nType[gate_sel];

	flaw_type = plvItem->cchTextMax;
}

void CFlawGateAdj::FreshFlawType(U8 gate_sel)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 flaw_type = param.m_astGateParam[hard_num][soft_num].m_nType[gate_sel];

	SetItemText(ROW_LOC_FLAW_TYPE, nCol, FLAW_TYPE_STR[flaw_type]);
}

void CFlawGateAdj::OptFlawType(const int& nRow, const int& nCol)
{
	U8 gate_sel = (nCol - 1) / 2;	// 闸门索引
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 flaw_type = param.m_astGateParam[hard_num][soft_num].m_nType[gate_sel];

	BOOL enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];
	if (enb == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "闸门尚未使能，不能调节缺陷类型");
		return;
	}

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = FLAW_TYPE_MIN; i <= FLAW_TYPE_MAX; i++)
		{
			str.Format("%s", FLAW_TYPE_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, flaw_type);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门声程显示
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::FreshPeakHori(U8 gate_sel, CString& str)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引
	SetItemText(ROW_LOC_PEAK_HORI, nCol, str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门波高显示
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::FreshPeakVert(U8 gate_sel, CString& str)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引
	SetItemText(ROW_LOC_PEAK_VERT, nCol, str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 闸门使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawGateAdj::AdjGateEnb(LV_ITEM* const plvItem)
{
	U8 gate_sel = (plvItem->iSubItem - 1) / 2;	// 闸门索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL& gate_enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];

	gate_enb = plvItem->cchTextMax;

	// 刷新闸门参数显示，以便背景色生效
	CString str = "";
	FreshGateStart(gate_sel);
	FreshGateWidth(gate_sel);
	FreshGateHeight(gate_sel);
	FreshGatePol(gate_sel);
	FreshFlawType(gate_sel);
	FreshPeakHori(gate_sel, str);
	FreshPeakVert(gate_sel, str);
}

void CFlawGateAdj::FreshGateEnb(U8 gate_sel)
{
	U8 nCol = gate_sel * 2 + 1;	// 列索引

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL gate_enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];

	SetItemText(ROW_LOC_GATE_ENB, nCol, SW_STS_STR[gate_enb]);
}

void CFlawGateAdj::OptGateEnb(const int& nRow, const int& nCol)
{
	U8 gate_sel = (nCol - 1) / 2;	// 闸门索引
	CStringList lstItems;
	CString str;

	if (gate_sel == GATE_SEL_A)
	{
		m_pApp->DispMsg(ZXUT_MSG_INFO, "闸门A恒定使能");
		return;
	}

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL gate_enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[gate_sel];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			str.Format("%s", SW_STS_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, gate_enb);
		lstItems.RemoveAll();
	}
}
