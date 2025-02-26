#pragma once

#include "ZxutApp.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 探伤参数位置(行)定义
//
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 1列

const U32 ROW_LOC_CHAN_NUM		= 0;
const U32 COL_LOC_CHAN_NUM		= 1;

const U32 ROW_LOC_TRIG_MODE		= 1;
const U32 COL_LOC_TRIG_MODE		= 1;

const U32 ROW_LOC_TRIG_POL		= 2;
const U32 COL_LOC_TRIG_POL		= 1;

const U32 ROW_LOC_BRD_SYNC		= 3;
const U32 COL_LOC_BRD_SYNC		= 1;

const U32 ROW_LOC_RPT_FREQ		= 4;
const U32 COL_LOC_RPT_FREQ		= 1;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 3列

const U32 ROW_LOC_TRANS_VOL		= 0;
const U32 COL_LOC_TRANS_VOL		= 3;

const U32 ROW_LOC_PUL_WIDTH		= 1;
const U32 COL_LOC_PUL_WIDTH		= 3;

const U32 ROW_LOC_PUL_NUM		= 2;
const U32 COL_LOC_PUL_NUM		= 3;

const U32 ROW_LOC_SMPL_DEPTH	= 3;
const U32 COL_LOC_SMPL_DEPTH	= 3;

const U32 ROW_LOC_RT_MODE		= 4;
const U32 COL_LOC_RT_MODE		= 3;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 5列

const U32 ROW_LOC_DB_NUM		= 0;
const U32 COL_LOC_DB_NUM		= 5;

const U32 ROW_LOC_DB_BOOST		= 1;
const U32 COL_LOC_DB_BOOST		= 5;

const U32 ROW_LOC_ORIG_DLY		= 2;
const U32 COL_LOC_ORIG_DLY		= 5;

const U32 ROW_LOC_FREQ_RATIO	= 3;
const U32 COL_LOC_FREQ_RATIO	= 5;

const U32 ROW_LOC_HORI_DISP	    = 4;
const U32 COL_LOC_HORI_DISP	    = 5;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 7列

const U32 ROW_LOC_VERT_DISP		= 0;
const U32 COL_LOC_VERT_DISP		= 7;

const U32 ROW_LOC_AVG_TIMES		= 1;
const U32 COL_LOC_AVG_TIMES		= 7;

const U32 ROW_LOC_DISP_UPD		= 2;
const U32 COL_LOC_DISP_UPD		= 7;

const U32 ROW_LOC_SOUND_VELO	= 3;
const U32 COL_LOC_SOUND_VELO	= 7;

const U32 ROW_LOC_FLAW_REF		= 4;
const U32 COL_LOC_FLAW_REF		= 7;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 9列

const U32 ROW_LOC_TRACE_ENB		= 0;
const U32 COL_LOC_TRACE_ENB		= 9;

const U32 ROW_LOC_TRACE_TYPE	= 1;
const U32 COL_LOC_TRACE_TYPE	= 9;

const U32 ROW_LOC_ANG_FLTR		= 3;
const U32 COL_LOC_ANG_FLTR		= 9;

const U32 ROW_LOC_DEM_MODE		= 4;
const U32 COL_LOC_DEM_MODE		= 9;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 11列

const U32 ROW_LOC_SMPL_WAVE	    = 0;
const U32 COL_LOC_SMPL_WAVE	    = 11;

const U32 ROW_LOC_FFT_WAVE	    = 1;
const U32 COL_LOC_FFT_WAVE	    = 11;

const U32 ROW_LOC_CENT_FREQ	    = 2;
const U32 COL_LOC_CENT_FREQ	    = 11;

class CFlawParamAdj : public CListCtrl
{
	DECLARE_DYNAMIC(CFlawParamAdj)

public:
	CFont m_fontStyle;
	CZxutApp* m_pApp;

	U8 x_nTotBrd;
	U8 x_nTotHard;

	CFlawParamAdj(void);
	~CFlawParamAdj(void);

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

	void InitFlawParamTitle(void);
	void FreshFlawParam(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 调节参数

	void AdjChanNum(LV_ITEM* const plvItem);
	void AdjTrigMode(LV_ITEM* const plvItem);
	void AdjTrigPol(LV_ITEM* const plvItem);
	void AdjBrdSync(LV_ITEM* const plvItem);
	void AdjRptFreq(LV_ITEM* const plvItem);

	void AdjTransVol(LV_ITEM* const plvItem);
	void AdjPulWidth(LV_ITEM* const plvItem);
	void AdjPulNum(LV_ITEM* const plvItem);
	void AdjSmplDepth(LV_ITEM* const plvItem);
	void AdjRtMode(LV_ITEM* const plvItem);

	void AdjDbNum(LV_ITEM* const plvItem);
	void AdjDbBoost(LV_ITEM* const plvItem);
	void AdjOrigDly(LV_ITEM* const plvItem);
	void AdjFreqRatio(LV_ITEM* const plvItem);
	void AdjHoriDisp(LV_ITEM* const plvItem);

	void AdjVertDisp(LV_ITEM* const plvItem);
	void AdjAvgTimes(LV_ITEM* const plvItem);
	void AdjDispUpd(LV_ITEM* const plvItem);
	void AdjSoundVelo(LV_ITEM* const plvItem);
	void AdjFlawRef(LV_ITEM* const plvItem);

	void AdjTraceEnb(LV_ITEM* const plvItem);
	void AdjTraceType(LV_ITEM* const plvItem);
	void AdjAngFltr(LV_ITEM* const plvItem);
	void AdjDemMode(LV_ITEM* const plvItem);

	void AdjSmplWave(LV_ITEM* const plvItem);
	void AdjFftWave(LV_ITEM* const plvItem);
	void AdjCentFreq(LV_ITEM* const plvItem);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 选择参数

	void OptChanNum(const int& nRow, const int& nCol);
	void OptTrigMode(const int& nRow, const int& nCol);
	void OptTrigPol(const int& nRow, const int& nCol);
	void OptBrdSync(const int& nRow, const int& nCol);
	void OptRptFreq(const int& nRow, const int& nCol);

	void OptTransVol(const int& nRow, const int& nCol);
	void OptPulWidth(const int& nRow, const int& nCol);
	void OptPulNum(const int& nRow, const int& nCol);
	void OptSmplDepth(const int& nRow, const int& nCol);
	void OptRtMode(const int& nRow, const int& nCol);

	void OptDbNum(const int& nRow, const int& nCol);
	void OptDbBoost(const int& nRow, const int& nCol);
	void OptOrigDly(const int& nRow, const int& nCol);
	void OptFreqRatio(const int& nRow, const int& nCol);
	void OptHoriDisp(const int& nRow, const int& nCol);

	void OptVertDisp(const int& nRow, const int& nCol);
	void OptAvgTimes(const int& nRow, const int& nCol);
	void OptDispUpd(const int& nRow, const int& nCol);
	void OptSoundVelo(const int& nRow, const int& nCol);
	void OptFlawRef(const int& nRow, const int& nCol);

	void OptTraceEnb(const int& nRow, const int& nCol);
	void OptTraceType(const int& nRow, const int& nCol);
	void OptAngFltr(const int& nRow, const int& nCol);
	void OptDemMode(const int& nRow, const int& nCol);

	void OptSmplWave(const int& nRow, const int& nCol);
	void OptFftWave(const int& nRow, const int& nCol);
	void OptCentFreq(const int& nRow, const int& nCol);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 刷新参数

	void FreshChanNum(void);
	void FreshTrigMode(void);
	void FreshTrigPol(void);
	void FreshBrdSync(void);
	void FreshRptFreq(void);

	void FreshTransVol(void);
	void FreshPulWidth(void);
	void FreshPulNum(void);
	void FreshSmplDepth(void);
	void FreshRtMode(void);

	void FreshDbNum(void);
	void FreshDbBoost(void);
	void FreshOrigDly(void);
	void FreshFreqRatio(void);
	void FreshHoriDisp(void);

	void FreshVertDisp(void);
	void FreshAvgTimes(void);
	void FreshDispUpd(void);
	void FreshSoundVelo(void);
	void FreshFlawRef(void);

	void FreshTraceEnb(void);
	void FreshTraceType(void);
	void FreshAngFltr(void);
	void FreshDemMode(void);

	void FreshSmplWave(void);
	void FreshFftWave(void);
	void FreshCentFreq(void);

	DECLARE_MESSAGE_MAP()
};
