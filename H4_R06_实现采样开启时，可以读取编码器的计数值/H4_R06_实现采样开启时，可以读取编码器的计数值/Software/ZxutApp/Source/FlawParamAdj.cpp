#include "stdafx.h"
#include "InPlaceComboBox.h"
#include "FlawParamAdj.h"
#include "ZxutDlg.h"

IMPLEMENT_DYNAMIC(CFlawParamAdj, CListCtrl)

////////////////////////////////////////////////////////////////////////////////////////////////////
// 消息映射

BEGIN_MESSAGE_MAP(CFlawParamAdj, CListCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CFlawParamAdj::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
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

int CFlawParamAdj::HitTestEx(const CPoint &point, int* const col) const
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

CComboBox* CFlawParamAdj::ShowInPlaceList(const int& Item, const int& Col, CStringList &lstItems,
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
// 构造函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CFlawParamAdj::CFlawParamAdj(void)
{
	///////////////////////////////////////////////////////////////////////////
	// 创建字体，用于显示探伤参数

	m_fontStyle.CreateFont(
		14, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, GB2312_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "Tahoma"
		);

	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pFlawParamAdj = this;
	x_nTotHard = m_pApp->m_pstExpInfo->m_nTotHard;
	x_nTotBrd = m_pApp->m_pstExpInfo->m_nTotBrd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 析构函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

CFlawParamAdj::~CFlawParamAdj(void)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 创建控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

int CFlawParamAdj::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	InitFlawParamTitle();
	FreshFlawParam();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 撤销控件
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::OnDestroy(void)
{
	CListCtrl::OnDestroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置单元前景色
//
////////////////////////////////////////////////////////////////////////////////////////////////////

COLORREF CFlawParamAdj::OnGetCellTextColor (int nRow, int nCol)
{
	return RGB(0, 0, 0);	// 全为黑色
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置单元背景色
//
////////////////////////////////////////////////////////////////////////////////////////////////////

COLORREF CFlawParamAdj::OnGetCellBkColor (int nRow, int nCol)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	// 标题
	BOOL title = (nCol == 0) || (nCol == 2) || (nCol == 4) || (nCol == 6) || (nCol == 8) || (nCol == 10);

	U8 dem_mode = param.m_anDemMode[hard_num][soft_num];

	// 界面闸门禁止，禁止设置跟踪使能
	BOOL intf_enb = param.m_astGateParam[hard_num][soft_num].m_bEnb[GATE_SEL_I];
	BOOL flg1 = (intf_enb == FALSE) && (nRow == ROW_LOC_TRACE_ENB) && (nCol == COL_LOC_TRACE_ENB);

	// 采样深度不是1K或者检波模式不是RF，禁止调节FFT波形和中心频率
	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	BOOL fft_dis = (smpl_depth != FFT_IN_DOTS) || (dem_mode != DEM_MODE_RF);
	BOOL flg2 = fft_dis && (nRow == ROW_LOC_FFT_WAVE) && (nCol == COL_LOC_FFT_WAVE);
	BOOL flg3 = fft_dis && (nRow == ROW_LOC_CENT_FREQ) && (nCol == COL_LOC_CENT_FREQ);

	BOOL flg4 = (nRow == ROW_LOC_BRD_SYNC) && (nCol == COL_LOC_BRD_SYNC) && !m_pApp->m_bBrdSyncEnb;
	BOOL flg6 = (nRow == ROW_LOC_DB_BOOST) && (nCol == COL_LOC_DB_BOOST) && !m_pApp->m_bNetP2;
	BOOL flg7 = (nRow == ROW_LOC_ANG_FLTR) && (nCol == COL_LOC_ANG_FLTR) && !m_pApp->m_bAngFltrEnb;

	if (title)
	{
		return ITEM_BACKGRD_COLOR;
	}
	else if (flg1 || flg2 || flg3 || flg4 || flg6 || flg7)
	{
		return ITEM_DISABLED_COLOR;
	}
	else
	{
		return RGB(255, 255, 255);	// 白色
	}
}

BOOL CFlawParamAdj::PreTranslateMessage(MSG* pMsg)
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
// 初始化探伤参数列表
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::InitFlawParamTitle(void)
{
	InsertColumn( 0, "名称",		LVCFMT_LEFT, 60, 0);
	InsertColumn( 1, "参数值",	LVCFMT_LEFT, 70, 0);
	InsertColumn( 2, "名称",		LVCFMT_LEFT, 60, 0);
	InsertColumn( 3, "参数值",	LVCFMT_LEFT, 70, 0);
	InsertColumn( 4, "名称",		LVCFMT_LEFT, 60, 0);
	InsertColumn( 5, "参数值",	LVCFMT_LEFT, 70, 0);
	InsertColumn( 6, "名称",		LVCFMT_LEFT, 60, 0);
	InsertColumn( 7, "参数值",	LVCFMT_LEFT, 70, 0);
	InsertColumn( 8, "名称",		LVCFMT_LEFT, 60, 0);
	InsertColumn( 9, "参数值",	LVCFMT_LEFT, 70, 0);
	InsertColumn(10, "名称",		LVCFMT_LEFT, 60, 0);
	InsertColumn(11, "参数值",	LVCFMT_LEFT, 70, 0);

	////////////////////////////////////////////////////////////////////////////////////////////////

	InsertItem(ROW_LOC_CHAN_NUM,	"通道");
	InsertItem(ROW_LOC_TRIG_MODE,	"触发模式");
	InsertItem(ROW_LOC_TRIG_POL,	"触发极性");
	InsertItem(ROW_LOC_BRD_SYNC,	"板间同步");
	InsertItem(ROW_LOC_RPT_FREQ,	"重复频率");

	SetItemText(ROW_LOC_TRANS_VOL,		COL_LOC_TRANS_VOL - 1,		"发射电压");
	SetItemText(ROW_LOC_PUL_WIDTH,		COL_LOC_PUL_WIDTH - 1,		"脉冲宽度");
	SetItemText(ROW_LOC_PUL_NUM,		COL_LOC_PUL_NUM - 1,		"脉冲个数");
	SetItemText(ROW_LOC_SMPL_DEPTH,		COL_LOC_SMPL_DEPTH - 1,		"采样点数");
	SetItemText(ROW_LOC_RT_MODE,		COL_LOC_RT_MODE - 1,		"收发模式");

	SetItemText(ROW_LOC_DB_NUM,			COL_LOC_DB_NUM - 1,			"增益");
	SetItemText(ROW_LOC_DB_BOOST,		COL_LOC_DB_BOOST - 1,		"25dB");
	SetItemText(ROW_LOC_ORIG_DLY,		COL_LOC_ORIG_DLY - 1,		"零位偏移");
	SetItemText(ROW_LOC_FREQ_RATIO,		COL_LOC_FREQ_RATIO - 1,		"检测范围");
	SetItemText(ROW_LOC_HORI_DISP,		COL_LOC_HORI_DISP - 1,		"距离显示");

	SetItemText(ROW_LOC_VERT_DISP,		COL_LOC_VERT_DISP - 1,		"波高显示");
	SetItemText(ROW_LOC_AVG_TIMES,		COL_LOC_AVG_TIMES - 1,		"平均次数");
	SetItemText(ROW_LOC_DISP_UPD,		COL_LOC_DISP_UPD - 1,		"显示刷新");
	SetItemText(ROW_LOC_SOUND_VELO,		COL_LOC_SOUND_VELO - 1,		"材料声速");
	SetItemText(ROW_LOC_FLAW_REF,		COL_LOC_FLAW_REF - 1,		"缺陷参考");

	SetItemText(ROW_LOC_TRACE_ENB,		COL_LOC_TRACE_ENB - 1,		"跟踪使能");
	SetItemText(ROW_LOC_TRACE_TYPE,		COL_LOC_TRACE_TYPE - 1,		"跟踪类型");
	SetItemText(ROW_LOC_ANG_FLTR,		COL_LOC_ANG_FLTR - 1,		"模拟滤波");
	SetItemText(ROW_LOC_DEM_MODE,		COL_LOC_DEM_MODE - 1,		"检波模式");

	SetItemText(ROW_LOC_SMPL_WAVE,		COL_LOC_SMPL_WAVE - 1,		"采样回波");
	SetItemText(ROW_LOC_FFT_WAVE,		COL_LOC_FFT_WAVE - 1,		"FFT波形");
	SetItemText(ROW_LOC_CENT_FREQ,		COL_LOC_CENT_FREQ - 1,		"中心频率");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 刷新所有探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::FreshFlawParam(void)
{
	FreshChanNum();
	FreshTrigMode();
	FreshTrigPol();
	FreshBrdSync();
	FreshRptFreq();

	FreshTransVol();
	FreshPulWidth();
	FreshPulNum();
	FreshSmplDepth();
	FreshRtMode();

	FreshDbNum();
	FreshDbBoost();
	FreshOrigDly();
	FreshFreqRatio();
	FreshHoriDisp();

	FreshVertDisp();
	FreshAvgTimes();
	FreshDispUpd();
	FreshSoundVelo();
	FreshFlawRef();

	FreshTraceEnb();
	FreshTraceType();
	FreshAngFltr();
	FreshDemMode();

	FreshSmplWave();
	FreshFftWave();
	FreshCentFreq();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 调节探伤参数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::OnEndlabeledit(NMHDR* pNMHDR,LRESULT* pResult)
{
	LV_DISPINFO  *plvDispInfo = (LV_DISPINFO *)pNMHDR;
	LV_ITEM		 *plvItem = &plvDispInfo->item;

	*pResult = NULL;

	if (plvItem->pszText != NULL)
	{
		SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);

		switch (plvItem->iSubItem)
		{
			case 1:		// 1列
				switch (plvItem->iItem)
				{
					case ROW_LOC_CHAN_NUM:		return AdjChanNum(plvItem);
					case ROW_LOC_TRIG_MODE:		return AdjTrigMode(plvItem);
					case ROW_LOC_TRIG_POL:		return AdjTrigPol(plvItem);
					case ROW_LOC_BRD_SYNC:		return AdjBrdSync(plvItem);
					case ROW_LOC_RPT_FREQ:		return AdjRptFreq(plvItem);
					default: return;
				}

			case 3:		// 3列
				switch (plvItem->iItem)
				{
					case ROW_LOC_TRANS_VOL:		return AdjTransVol(plvItem);
					case ROW_LOC_PUL_WIDTH:		return AdjPulWidth(plvItem);
					case ROW_LOC_PUL_NUM:		return AdjPulNum(plvItem);
					case ROW_LOC_SMPL_DEPTH:	return AdjSmplDepth(plvItem);
					case ROW_LOC_RT_MODE:		return AdjRtMode(plvItem);
					default: return;
				}

			case 5:		// 5列
				switch (plvItem->iItem)
				{
					case ROW_LOC_DB_NUM:		return AdjDbNum(plvItem);
					case ROW_LOC_DB_BOOST:		return AdjDbBoost(plvItem);
					case ROW_LOC_ORIG_DLY:		return AdjOrigDly(plvItem);
					case ROW_LOC_FREQ_RATIO:	return AdjFreqRatio(plvItem);
					case ROW_LOC_HORI_DISP:		return AdjHoriDisp(plvItem);
					default: return;
				}

			case 7:		// 7列
				switch (plvItem->iItem)
				{
					case ROW_LOC_VERT_DISP:		return AdjVertDisp(plvItem);
					case ROW_LOC_AVG_TIMES:		return AdjAvgTimes(plvItem);
					case ROW_LOC_DISP_UPD:		return AdjDispUpd(plvItem);
					case ROW_LOC_SOUND_VELO:	return AdjSoundVelo(plvItem);
					case ROW_LOC_FLAW_REF:		return AdjFlawRef(plvItem);
					default: return;
				}

			case 9:		// 9列
				switch (plvItem->iItem)
				{
					case ROW_LOC_TRACE_ENB:		return AdjTraceEnb(plvItem);
					case ROW_LOC_TRACE_TYPE:	return AdjTraceType(plvItem);
					case ROW_LOC_ANG_FLTR:		return AdjAngFltr(plvItem);
					case ROW_LOC_DEM_MODE:		return AdjDemMode(plvItem);
					default: return;
				}

			case 11:	// 11列
				switch (plvItem->iItem)
				{
					case ROW_LOC_SMPL_WAVE:		return AdjSmplWave(plvItem);
					case ROW_LOC_FFT_WAVE:		return AdjFftWave(plvItem);
					case ROW_LOC_CENT_FREQ:		return AdjCentFreq(plvItem);
					default: return;
				}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 探伤参数选项
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
	int nRow, nCol;

	nRow = HitTestEx(point, &nCol);

	switch (nCol)
	{
		case 1:		// 1列
			switch (nRow)
			{
				case ROW_LOC_CHAN_NUM:		return OptChanNum(nRow, nCol);
				case ROW_LOC_TRIG_MODE:		return OptTrigMode(nRow, nCol);
				case ROW_LOC_TRIG_POL:		return OptTrigPol(nRow, nCol);
				case ROW_LOC_BRD_SYNC:		return OptBrdSync(nRow, nCol);
				case ROW_LOC_RPT_FREQ:		return OptRptFreq(nRow, nCol);
				default: return;
			}

		case 3:		// 3列
			switch (nRow)
			{
				case ROW_LOC_TRANS_VOL:		return OptTransVol(nRow, nCol);
				case ROW_LOC_PUL_WIDTH:		return OptPulWidth(nRow, nCol);
				case ROW_LOC_PUL_NUM:		return OptPulNum(nRow, nCol);
				case ROW_LOC_SMPL_DEPTH:	return OptSmplDepth(nRow, nCol);
				case ROW_LOC_RT_MODE:		return OptRtMode(nRow, nCol);
				default: return;
			}

		case 5:		// 5列
			switch (nRow)
			{
				case ROW_LOC_DB_NUM:		return OptDbNum(nRow, nCol);
				case ROW_LOC_DB_BOOST:		return OptDbBoost(nRow, nCol);
				case ROW_LOC_ORIG_DLY:		return OptOrigDly(nRow, nCol);
				case ROW_LOC_FREQ_RATIO:	return OptFreqRatio(nRow, nCol);
				case ROW_LOC_HORI_DISP:		return OptHoriDisp(nRow, nCol);
				default: return;
			}

		case 7:		// 7列
			switch (nRow)
			{
				case ROW_LOC_VERT_DISP:		return OptVertDisp(nRow, nCol);
				case ROW_LOC_AVG_TIMES:		return OptAvgTimes(nRow, nCol);
				case ROW_LOC_DISP_UPD:		return OptDispUpd(nRow, nCol);
				case ROW_LOC_SOUND_VELO:	return OptSoundVelo(nRow, nCol);
				case ROW_LOC_FLAW_REF:		return OptFlawRef(nRow, nCol);
				default: return;
			}

		case 9:		// 9列
			switch (nRow)
			{
				case ROW_LOC_TRACE_ENB:		return OptTraceEnb(nRow, nCol);
				case ROW_LOC_TRACE_TYPE:	return OptTraceType(nRow, nCol);
				case ROW_LOC_ANG_FLTR:		return OptAngFltr(nRow, nCol);
				case ROW_LOC_DEM_MODE:		return OptDemMode(nRow, nCol);
				default: return;
			}

		case 11:	// 11列
			switch (nRow)
			{
				case ROW_LOC_SMPL_WAVE:		return OptSmplWave(nRow, nCol);
				case ROW_LOC_FFT_WAVE:		return OptFftWave(nRow, nCol);
				case ROW_LOC_CENT_FREQ:		return OptCentFreq(nRow, nCol);
				default: return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 通道编号
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjChanNum(LV_ITEM* const plvItem)
{
	m_pApp->m_stLogChan.m_nLogIdx = plvItem->cchTextMax;
	m_pApp->UpdChanNum();
}

void CFlawParamAdj::FreshChanNum(void)
{
	U8 log_idx = m_pApp->m_stLogChan.m_nLogIdx;
	U8 hard_num = m_pApp->m_stLogChan.m_nLogHard[log_idx];
	U8 soft_num = m_pApp->m_stLogChan.m_nLogSoft[log_idx];
	CString str;
	if (m_pApp->m_bPci)
	{
		str.Format("%d", hard_num + 1);
	}
	else
	{
		str.Format("%d-%d", hard_num + 1, soft_num + 1);
	}
	SetItemText(ROW_LOC_CHAN_NUM, COL_LOC_CHAN_NUM, str);
}

void CFlawParamAdj::OptChanNum(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = 0; i < m_pApp->m_stLogChan.m_nLogTot; i++)
		{
			CString str;
			U8 hard_num = m_pApp->m_stLogChan.m_nLogHard[i];
			U8 soft_num = m_pApp->m_stLogChan.m_nLogSoft[i];
			if (m_pApp->m_bPci)
			{
				str.Format("%d", hard_num + 1);
			}
			else
			{
				str.Format("%d-%d", hard_num + 1, soft_num + 1);
			}

			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, m_pApp->m_stLogChan.m_nLogIdx);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 触发模式
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjTrigMode(LV_ITEM* const plvItem)
{
	U8& nTrigMode = m_pApp->m_stFlawParam.m_nTrigMode;
	nTrigMode = plvItem->cchTextMax;

	// 所有板卡的触发模式均相同
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		ZXUT_SetTrigMode(i, nTrigMode);
	}

	ZXUT_SetRptFreq(m_pApp->m_stFlawParam.m_stCoreParam.m_nRptFreq, NULL, NULL);
	m_pApp->UpdSysTiming();	// 更新系统时序
}

void CFlawParamAdj::FreshTrigMode(void)
{
	U8 nTrigMode = m_pApp->m_stFlawParam.m_nTrigMode;
	SetItemText(ROW_LOC_TRIG_MODE, COL_LOC_TRIG_MODE, TRIG_MODE_STR[nTrigMode]);
}

void CFlawParamAdj::OptTrigMode(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 nTrigMode = m_pApp->m_stFlawParam.m_nTrigMode;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U16 i = TRIG_MODE_MIN; i <= TRIG_MODE_MAX; i++)
		{
			lstItems.AddTail(TRIG_MODE_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, nTrigMode);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 触发极性
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjTrigPol(LV_ITEM* const plvItem)
{
	U8& nTrigPol = m_pApp->m_stFlawParam.m_nTrigPol;
	nTrigPol = plvItem->cchTextMax;

	// 所有板卡的触发极性均相同
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		ZXUT_SetTrigPol(i, nTrigPol);
	}
}

void CFlawParamAdj::FreshTrigPol(void)
{
	U8 nTrigPol = m_pApp->m_stFlawParam.m_nTrigPol;
	SetItemText(ROW_LOC_TRIG_POL, COL_LOC_TRIG_POL, POL_DEF_STR[nTrigPol]);
}

void CFlawParamAdj::OptTrigPol(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 nTrigPol = m_pApp->m_stFlawParam.m_nTrigPol;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U16 i = POL_DEF_MIN; i <= POL_DEF_MAX; i++)
		{
			lstItems.AddTail(POL_DEF_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, nTrigPol);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 板间同步
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjBrdSync(LV_ITEM* const plvItem)
{
	m_pApp->UpdBrdSync(plvItem);
}

void CFlawParamAdj::FreshBrdSync(void)
{
	U8 brd_sync = m_pApp->m_stFlawParam.m_stCoreParam.m_nBrdSync;

	CString str;
	str.Format("%s", BRD_SYNC_STR[brd_sync]);
	SetItemText(ROW_LOC_BRD_SYNC, COL_LOC_BRD_SYNC, str);
}

void CFlawParamAdj::OptBrdSync(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 brd_sync = param.m_stCoreParam.m_nBrdSync;

	if (m_pApp->m_bBrdSyncEnb)
	{
		if (GetWindowLong(m_hWnd, GWL_STYLE))
		{
			for (U16 i = BRD_SYNC_MIN; i <= BRD_SYNC_MAX; i++)
			{
				str.Format("%s", BRD_SYNC_STR[i]);
				lstItems.AddTail(str);
			}

			ShowInPlaceList(nRow, nCol, lstItems, brd_sync);
			lstItems.RemoveAll();
		}
	}
	else
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "%s不支持“板间同步”选择", m_pApp->m_strZxutType);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 重复频率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjRptFreq(LV_ITEM* const plvItem)
{
	m_pApp->UpdRptFreq(this, plvItem);
}

void CFlawParamAdj::FreshRptFreq(void)
{
	U8 rf_idx = m_pApp->m_stFlawParam.m_nRfIdx;
	SetItemText(ROW_LOC_RPT_FREQ, COL_LOC_RPT_FREQ, RPT_FREQ_STR[rf_idx]);
}

void CFlawParamAdj::OptRptFreq(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 rf_idx = m_pApp->m_stFlawParam.m_nRfIdx;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U16 i = RF_IDX_MIN; i <= RF_IDX_MAX; i++)
		{
			lstItems.AddTail(RPT_FREQ_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, rf_idx);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 发射电压
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjTransVol(LV_ITEM* const plvItem)
{
	// 每个通道板上均有高压模块，不过全部设定为相同
	U16& trans_vol = m_pApp->m_stFlawParam.m_nTransVol;
	trans_vol = plvItem->cchTextMax + TRANS_VOL_MIN;
	for (U8 i = 0; i < x_nTotBrd; i++)
	{
		ZXUT_SetTransVol(i, trans_vol);
	}
}

void CFlawParamAdj::FreshTransVol(void)
{
	U16 trans_vol = m_pApp->m_stFlawParam.m_nTransVol;

	CString str;
	str.Format("%dV", trans_vol);
	SetItemText(ROW_LOC_TRANS_VOL, COL_LOC_TRANS_VOL, str);
}

void CFlawParamAdj::OptTransVol(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U16 trans_vol = m_pApp->m_stFlawParam.m_nTransVol;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U16 i = TRANS_VOL_MIN; i <= TRANS_VOL_MAX; i++)
		{
			str.Format("%dV", i);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, trans_vol - TRANS_VOL_MIN);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 脉冲宽度(ns)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjPulWidth(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16& pul_width = param.m_anPulWidth[hard_num][soft_num];

	pul_width = plvItem->cchTextMax * 10 + PUL_WIDTH_MIN;
	ZXUT_SetPulWidth(hard_num, soft_num, pul_width);
}

void CFlawParamAdj::FreshPulWidth(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 pul_width = param.m_anPulWidth[hard_num][soft_num];

	CString str;
	str.Format("%dns", pul_width);
	SetItemText(ROW_LOC_PUL_WIDTH, COL_LOC_PUL_WIDTH, str);
}

void CFlawParamAdj::OptPulWidth(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 pul_width = param.m_anPulWidth[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U32 i = PUL_WIDTH_MIN; i <= PUL_WIDTH_MAX; i += 10)	// 10ns步进
		{
			str.Format("%dns", i);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, (pul_width - PUL_WIDTH_MIN) / 10);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 脉冲个数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjPulNum(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& pul_num = param.m_anPulNum[hard_num][soft_num];

	pul_num = plvItem->cchTextMax;
	ZXUT_SetPulNum(hard_num, soft_num, pul_num + 1);
}

void CFlawParamAdj::FreshPulNum(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 pul_num = param.m_anPulNum[hard_num][soft_num];

	CString str;
	str.Format("%d", pul_num + 1);
	SetItemText(ROW_LOC_PUL_NUM, COL_LOC_PUL_NUM, str);
}

void CFlawParamAdj::OptPulNum(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 pul_num = param.m_anPulNum[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U32 i = PUL_NUM_MIN; i <= PUL_NUM_MAX; i++)
		{
			str.Format("%d", i);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, pul_num);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 采样深度
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjSmplDepth(LV_ITEM* const plvItem)
{
	m_pApp->UpdSmplDepth(this, plvItem);
}

void CFlawParamAdj::FreshSmplDepth(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 sd_idx = param.m_anSdIdx[hard_num][soft_num];

	CString str;
	str.Format("%s", m_pApp->m_asSmplDepthStr[sd_idx]);
	SetItemText(ROW_LOC_SMPL_DEPTH, COL_LOC_SMPL_DEPTH, str);
}

void CFlawParamAdj::OptSmplDepth(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 sd_idx = param.m_anSdIdx[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = 0; i < m_pApp->m_nSmplDepthNum; i++)
		{
			str.Format("%s", m_pApp->m_asSmplDepthStr[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, sd_idx);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 收发方式
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjRtMode(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& rt_mode = param.m_anRtMode[hard_num];

	rt_mode = plvItem->cchTextMax;
	ZXUT_SetRtMode(hard_num, rt_mode);
}

void CFlawParamAdj::FreshRtMode(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 rt_mode = param.m_anRtMode[hard_num];

	CString str;
	str.Format("%s", RT_MODE_STR[rt_mode]);
	SetItemText(ROW_LOC_RT_MODE, COL_LOC_RT_MODE, str);
}

void CFlawParamAdj::OptRtMode(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 rt_mode = param.m_anRtMode[hard_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = RT_MODE_MIN; i <= RT_MODE_MAX; i++)
		{
			str.Format("%s", RT_MODE_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, rt_mode);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 增益
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjDbNum(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16& db_code = param.m_anDbNum[hard_num][soft_num];

	db_code = plvItem->cchTextMax;
	ZXUT_SetDbNum(hard_num, soft_num, db_code);
}

void CFlawParamAdj::FreshDbNum(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 db_code = param.m_anDbNum[hard_num][soft_num];

	CString str;
	str.Format("%.1fdB", db_code * 0.1f);
	SetItemText(ROW_LOC_DB_NUM, COL_LOC_DB_NUM, str);
}

void CFlawParamAdj::OptDbNum(const int& nRow, const int& nCol)
{
	if (m_pApp->m_bDacCalib) return;

	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 db_code = param.m_anDbNum[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		U16 max_db = m_pApp->m_pstExpInfo->m_nMaxGain;
		for (U16 i = DB_NUM_MIN; i <= max_db; i++)
		{
			str.Format("%.1fdB", i * 0.1f);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, db_code);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 阻抗匹配
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjDbBoost(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& db_boost = param.m_anDbBoost[hard_num][soft_num];

	db_boost = plvItem->cchTextMax;
	ZXUT_SetDbBoost(hard_num, soft_num, db_boost);
}

void CFlawParamAdj::FreshDbBoost(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 db_boost = param.m_anDbBoost[hard_num][soft_num];

	CString str;
	str.Format("%s", SW_STS_STR[db_boost]);
	SetItemText(ROW_LOC_DB_BOOST, COL_LOC_DB_BOOST, str);
}

void CFlawParamAdj::OptDbBoost(const int& nRow, const int& nCol)
{
	if (m_pApp->m_bNetP2)
	{
		CStringList lstItems;
		CString str;

		U8 hard_num = m_pApp->m_nHardNum;
		U8 soft_num = m_pApp->m_nSoftNum;
		ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
		U8 db_boost = param.m_anDbBoost[hard_num][soft_num];

		if (GetWindowLong(m_hWnd, GWL_STYLE))
		{
			for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
			{
				str.Format("%s", SW_STS_STR[i]);
				lstItems.AddTail(str);
			}

			ShowInPlaceList(nRow, nCol, lstItems, db_boost);
			lstItems.RemoveAll();
		}
	}
	else
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "%s不支持“25dB提升”选择", m_pApp->m_strZxutType);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 零位延迟(ns)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjOrigDly(LV_ITEM* const plvItem)
{
	m_pApp->UpdOrigDly(this, plvItem);
}

void CFlawParamAdj::FreshOrigDly(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	S32 orig_dly = param.m_stCoreParam.m_anOrigDly[hard_num][soft_num];

	CString str;
	str.Format("%+.2fus", orig_dly * 0.001f);	// ns -> us
	SetItemText(ROW_LOC_ORIG_DLY, COL_LOC_ORIG_DLY, str);
}

void CFlawParamAdj::OptOrigDly(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	S32 orig_dly = param.m_stCoreParam.m_anOrigDly[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (S32 i = ORIG_DLY_MIN; i <= ORIG_DLY_MAX; i += 10)	// 10ns步进
		{
			str.Format("%+.2fus", i * 0.001f);	// ns -> us
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, (orig_dly - ORIG_DLY_MIN) / 10);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 检测范围
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjFreqRatio(LV_ITEM* const plvItem)
{
	m_pApp->UpdFreqRatio(this, plvItem);
}

void CFlawParamAdj::FreshFreqRatio(void)
{
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];

	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
	F32 time = ZXUT_GetTstTime(freq_ratio, smpl_depth, 0) * 0.001f;	// ns -> us
	F32 tst_range = ZXUT_GetTstRange(freq_ratio, smpl_depth, 0, sound_velo);

	switch (param.m_nHoriDisp)
	{
		case HORI_DISP_MM:
			str.Format("%.2f", tst_range);	// mm
			break;

		case HORI_DISP_US:
			str.Format("%.2f", time);		// us
			break;

		case HORI_DISP_DOTS:
			str.Format("%d", freq_ratio);	// 点数(分频比)
	}
	SetItemText(ROW_LOC_FREQ_RATIO, COL_LOC_FREQ_RATIO, str);
}

void CFlawParamAdj::OptFreqRatio(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
		U32 max = 512 * (1 + FREQ_RATIO_MAX) / smpl_depth - 1;
		for (U16 i = FREQ_RATIO_MIN; i <= max; i++)
		{
			U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
			F32 time = ZXUT_GetTstTime(i, smpl_depth, 0) * 0.001f;	// ns -> us
			F32 tst_range = ZXUT_GetTstRange(i, smpl_depth, 0, sound_velo);

			switch (param.m_nHoriDisp)
			{
				case HORI_DISP_MM:
					str.Format("%.2f", tst_range);	// mm
					break;

				case HORI_DISP_US:
					str.Format("%.2f", time);		// us
					break;

				case HORI_DISP_DOTS:
					str.Format("%d", i);			// 点数(分频比)
			}
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, freq_ratio - 1);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 水平显示
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjHoriDisp(LV_ITEM* const plvItem)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& hori_disp = param.m_nHoriDisp;
	hori_disp = plvItem->cchTextMax;
	FreshFreqRatio();
	m_pApp->m_pDlgTcgProc->FreshTcgColText();
}

void CFlawParamAdj::FreshHoriDisp(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 hori_disp = param.m_nHoriDisp;
	SetItemText(ROW_LOC_HORI_DISP, COL_LOC_HORI_DISP, HORI_DISP_STR[hori_disp]);
}

void CFlawParamAdj::OptHoriDisp(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 hori_disp = param.m_nHoriDisp;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = HORI_DISP_MIN; i <= HORI_DISP_MAX; i++)
		{
			str.Format("%s", HORI_DISP_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, hori_disp);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 垂直显示
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjVertDisp(LV_ITEM* const plvItem)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& vert_disp = param.m_nVertDisp;
	vert_disp = plvItem->cchTextMax;
	FreshFreqRatio();
}

void CFlawParamAdj::FreshVertDisp(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 vert_disp = param.m_nVertDisp;
	SetItemText(ROW_LOC_VERT_DISP, COL_LOC_VERT_DISP, VERT_DISP_STR[vert_disp]);
}

void CFlawParamAdj::OptVertDisp(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 vert_disp = param.m_nVertDisp;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = VERT_DISP_MIN; i <= VERT_DISP_MAX; i++)
		{
			str.Format("%s", VERT_DISP_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, vert_disp);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 平均次数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjAvgTimes(LV_ITEM* const plvItem)
{
	m_pApp->UpdAvgTimes(this, plvItem);
}

void CFlawParamAdj::FreshAvgTimes(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 at_idx = param.m_anAtIdx[hard_num][soft_num];

	CString str;
	str.Format("%s", AVG_TIMES_STR[at_idx]);
	SetItemText(ROW_LOC_AVG_TIMES, COL_LOC_AVG_TIMES, str);
}

void CFlawParamAdj::OptAvgTimes(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 at_idx = param.m_anAtIdx[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = AT_IDX_MIN; i <= AT_IDX_MAX; i++)
		{
			str.Format("%s", AVG_TIMES_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, at_idx);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 显示刷新
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjDispUpd(LV_ITEM* const plvItem)
{
	U8& disp_upd = m_pApp->m_stFlawParam.m_nDispUpd;
	disp_upd = plvItem->cchTextMax;
	m_pApp->GetUpdProcEnd();
}

void CFlawParamAdj::FreshDispUpd(void)
{
	U8 disp_upd = m_pApp->m_stFlawParam.m_nDispUpd;

	CString str;
	str.Format("%s", DISP_UPD_STR[disp_upd]);
	SetItemText(ROW_LOC_DISP_UPD, COL_LOC_DISP_UPD, str);
}

void CFlawParamAdj::OptDispUpd(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 disp_upd = m_pApp->m_stFlawParam.m_nDispUpd;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = DISP_UPD_MIN; i <= DISP_UPD_MAX; i++)
		{
			str.Format("%s", DISP_UPD_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, disp_upd);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 材料声速
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjSoundVelo(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U32& sound_velo = param.m_anSoundVelo[hard_num][soft_num];

	sound_velo = plvItem->cchTextMax + SOUND_VELO_MIN;
	FreshFreqRatio();	// 影响检测范围，其实也影响闸门表示的范围，在进行TAB切换进行了处理
}

void CFlawParamAdj::FreshSoundVelo(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];

	CString str;
	str.Format("%dm/s", sound_velo);
	SetItemText(ROW_LOC_SOUND_VELO, COL_LOC_SOUND_VELO, str);
}

void CFlawParamAdj::OptSoundVelo(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U32 i = SOUND_VELO_MIN; i <= SOUND_VELO_MAX; i++)
		{
			str.Format("%dm/s", i);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, sound_velo - SOUND_VELO_MIN);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 缺陷参考
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjFlawRef(LV_ITEM* const plvItem)
{
	m_pApp->m_stFlawParam.m_bFlawRef = plvItem->cchTextMax;
}

void CFlawParamAdj::FreshFlawRef(void)
{
	BOOL flaw_ref = m_pApp->m_stFlawParam.m_bFlawRef;
	SetItemText(ROW_LOC_FLAW_REF, COL_LOC_FLAW_REF, SW_STS_STR[flaw_ref]);
}

void CFlawParamAdj::OptFlawRef(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	BOOL flaw_ref = m_pApp->m_stFlawParam.m_bFlawRef;

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			lstItems.AddTail(SW_STS_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, flaw_ref);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 跟踪使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjTraceEnb(LV_ITEM* const plvItem)
{
/*	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL& trace_enb = param.m_abTraceEnb[hard_num][soft_num];
	trace_enb = plvItem->cchTextMax;

	U8 brd_num = hard_num / x_nTotHard;
	ST_RQ_DATA& daq_buf = *(m_pApp->m_pstExpInfo->m_apstDaqBuf[brd_num]);
	ST_DAQ_DATA& acc_buf = daq_buf.m_stAccData[0][hard_num % x_nTotHard][soft_num];
	ST_GATE_RES& gate_res = acc_buf.m_astGateRes[GATE_SEL_I];

	switch (param.m_anTraceType[hard_num][soft_num])
	{
		case TRACE_TYPE_PEDGE:	// 跟踪前沿
			ZXUT_SetTracePnt(hard_num, soft_num, gate_res.m_xpEdge);
			break;

		case TRACE_TYPE_NEDGE:	// 跟踪后沿
			ZXUT_SetTracePnt(hard_num, soft_num, gate_res.m_xnEdge);
			break;
	}

	ZXUT_SetTraceEnb(hard_num, soft_num, trace_enb);*/
}

void CFlawParamAdj::FreshTraceEnb(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL trace_enb = param.m_abTraceEnb[hard_num][soft_num];

	SetItemText(ROW_LOC_TRACE_ENB, COL_LOC_TRACE_ENB, SW_STS_STR[trace_enb]);
}

void CFlawParamAdj::OptTraceEnb(const int& nRow, const int& nCol)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;

	if (m_pApp->m_stFlawParam.m_astGateParam[hard_num][soft_num].m_bEnb[GATE_SEL_I] == FALSE)
	{
		m_pApp->DispMsg(ZXUT_MSG_WARNING, "界面波闸门没有使能");
		return;
	}

	CStringList lstItems;
	CString str;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL trace_enb = param.m_abTraceEnb[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			lstItems.AddTail(SW_STS_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, trace_enb);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 跟踪类型
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjTraceType(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& trace_type = param.m_anTraceType[hard_num][soft_num];

	trace_type = plvItem->cchTextMax;
	ZXUT_SetTraceType(hard_num, soft_num, trace_type);
}

void CFlawParamAdj::FreshTraceType(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 trace_type = param.m_anTraceType[hard_num][soft_num];

	CString str;
	str.Format("%s", TRACE_TYPE_STR[trace_type]);
	SetItemText(ROW_LOC_TRACE_TYPE, COL_LOC_TRACE_TYPE, str);
}

void CFlawParamAdj::OptTraceType(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 trace_type = param.m_anTraceType[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = TRACE_TYPE_MIN; i <= TRACE_TYPE_MAX; i++)
		{
			str.Format("%s", TRACE_TYPE_STR[i]);
			lstItems.AddTail(str);
		}

		ShowInPlaceList(nRow, nCol, lstItems, trace_type);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 模拟滤波
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjAngFltr(LV_ITEM* const plvItem)
{
	if (m_pApp->m_bAngFltrEnb)
	{
		U8 hard_num = m_pApp->m_nHardNum;
		U8 soft_num = m_pApp->m_nSoftNum;
		ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
		U8& ang_fltr = param.m_anAngFltr[hard_num][soft_num];

		ang_fltr = plvItem->cchTextMax;
		ZXUT_SetAngFltr(hard_num, soft_num, ang_fltr);

		m_pApp->m_pDlgFftProc->m_combAngFltr.SetCurSel(ang_fltr);
	}
}

void CFlawParamAdj::FreshAngFltr(void)
{
	if (m_pApp->m_bAngFltrEnb)
	{
		U8 hard_num = m_pApp->m_nHardNum;
		U8 soft_num = m_pApp->m_nSoftNum;
		ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
		U8 ang_fltr = param.m_anAngFltr[hard_num][soft_num];

		if (m_pApp->m_bPci)
		{
			SetItemText(ROW_LOC_ANG_FLTR, COL_LOC_ANG_FLTR, ANG_FLTR_STR_PCI[ang_fltr]);
		}
		else if (m_pApp->m_bNet)
		{
			SetItemText(ROW_LOC_ANG_FLTR, COL_LOC_ANG_FLTR, ANG_FLTR_STR_NET[ang_fltr]);
		}
	}
}

void CFlawParamAdj::OptAngFltr(const int& nRow, const int& nCol)
{
	if (m_pApp->m_bAngFltrEnb)
	{
		CStringList lstItems;

		U8 hard_num = m_pApp->m_nHardNum;
		U8 soft_num = m_pApp->m_nSoftNum;
		ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
		U8 ang_fltr = param.m_anAngFltr[hard_num][soft_num];

		if (GetWindowLong(m_hWnd, GWL_STYLE))
		{
			if (m_pApp->m_bPci)
			{
				for (U8 i = 0; i < ANG_FLTR_NUM_PCI; i++)
				{
					lstItems.AddTail(ANG_FLTR_STR_PCI[i]);
				}
			}
			else if (m_pApp->m_bNet)
			{
				for (U8 i = 0; i < ANG_FLTR_NUM_NET; i++)
				{
					lstItems.AddTail(ANG_FLTR_STR_NET[i]);
				}
			}

			ShowInPlaceList(nRow, nCol, lstItems, ang_fltr);
			lstItems.RemoveAll();
		}
	}
	else
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "%s不支持“模拟滤波”选择", m_pApp->m_strZxutType);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 检波方式
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjDemMode(LV_ITEM* const plvItem)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8& dem_mode = param.m_anDemMode[hard_num][soft_num];
	dem_mode = plvItem->cchTextMax;

	ZXUT_SetDemMode(hard_num, soft_num, dem_mode);
	m_pApp->SetDataSwitch();
}

void CFlawParamAdj::FreshDemMode(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 dem_mode = param.m_anDemMode[hard_num][soft_num];

	SetItemText(ROW_LOC_DEM_MODE, COL_LOC_DEM_MODE, DEM_MODE_STR[dem_mode]);
}

void CFlawParamAdj::OptDemMode(const int& nRow, const int& nCol)
{
	CStringList lstItems;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U8 dem_mode = param.m_anDemMode[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = DEM_MODE_MIN; i <= DEM_MODE_MAX; i++)
		{
			lstItems.AddTail(DEM_MODE_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, dem_mode);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 采样回波
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjSmplWave(LV_ITEM* const plvItem)
{
	m_pApp->UpdSmplWave(this, plvItem);
}

void CFlawParamAdj::FreshSmplWave(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL smpl_wave = param.m_stCoreParam.m_abSmplWave[hard_num][soft_num];
	SetItemText(ROW_LOC_SMPL_WAVE, COL_LOC_SMPL_WAVE, SW_STS_STR[smpl_wave]);
}

void CFlawParamAdj::OptSmplWave(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL smpl_wave = param.m_stCoreParam.m_abSmplWave[hard_num][soft_num];

	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			lstItems.AddTail(SW_STS_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, smpl_wave);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FFT波形
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjFftWave(LV_ITEM* const plvItem)
{
	m_pApp->UpdFftWave(this, plvItem);
}

void CFlawParamAdj::FreshFftWave(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL fft_wave = param.m_stCoreParam.m_abFftWave[hard_num][soft_num];
	SetItemText(ROW_LOC_FFT_WAVE, COL_LOC_FFT_WAVE, SW_STS_STR[fft_wave]);
}

void CFlawParamAdj::OptFftWave(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	// 采样深度不是1K，禁止调节FFT波形
	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	if (smpl_depth != FFT_IN_DOTS)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "采样深度不是1K，禁止调节FFT波形");
		return;
	}

	U8 dem_mode = param.m_anDemMode[hard_num][soft_num];
	if (dem_mode != DEM_MODE_RF)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "检波模式不是射频，禁止调节FFT波形");
		return;
	}

	BOOL fft_wave = param.m_stCoreParam.m_abFftWave[hard_num][soft_num];
	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			lstItems.AddTail(SW_STS_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, fft_wave);
		lstItems.RemoveAll();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 中心频率
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFlawParamAdj::AdjCentFreq(LV_ITEM* const plvItem)
{
	m_pApp->UpdCentFreq(this, plvItem);
}

void CFlawParamAdj::FreshCentFreq(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	BOOL cent_freq = param.m_stCoreParam.m_abCentFreq[hard_num][soft_num];
	SetItemText(ROW_LOC_CENT_FREQ, COL_LOC_CENT_FREQ, SW_STS_STR[cent_freq]);
}

void CFlawParamAdj::OptCentFreq(const int& nRow, const int& nCol)
{
	CStringList lstItems;
	CString str;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;

	// 采样深度不是1K，禁止调节中心频率
	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];
	if (smpl_depth != FFT_IN_DOTS)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "采样深度不是1K，禁止调节中心频率");
		return;
	}

	U8 dem_mode = param.m_anDemMode[hard_num][soft_num];
	if (dem_mode != DEM_MODE_RF)
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "检波模式不是射频，禁止调节中心频率");
		return;
	}

	BOOL cent_freq = param.m_stCoreParam.m_abCentFreq[hard_num][soft_num];
	if (GetWindowLong(m_hWnd, GWL_STYLE))
	{
		for (U8 i = SW_STS_MIN; i <= SW_STS_MAX; i++)
		{
			lstItems.AddTail(SW_STS_STR[i]);
		}

		ShowInPlaceList(nRow, nCol, lstItems, cent_freq);
		lstItems.RemoveAll();
	}
}
