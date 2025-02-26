#include "stdafx.h"
#include "ZxutApp.h"
#include "DlgTcgProc.h"

IMPLEMENT_DYNAMIC(CDlgTcgProc, CDialog)

CDlgTcgProc::CDlgTcgProc(CWnd* pParent) : CDialog(CDlgTcgProc::IDD, pParent)
{
	m_pApp = (CZxutApp*)AfxGetApp();
	m_pApp->m_pDlgTcgProc = this;
}

CDlgTcgProc::~CDlgTcgProc(void)
{
}

void CDlgTcgProc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LST_TCG_TP, m_lstTcgTp);
	DDX_Control(pDX, IDC_CHK_TCG_ENB, m_chkTcgEnb);
	DDX_Control(pDX, IDC_BTN_TCG_ADD_TP, m_btnTcgTpAdd);
	DDX_Control(pDX, IDC_BTN_TCG_DEL_TP, m_btnTcgTpDel);
	DDX_Control(pDX, IDC_BTN_TCG_RST_TP, m_btnTcgTpRst);
}

BEGIN_MESSAGE_MAP(CDlgTcgProc, CDialog)
	ON_BN_CLICKED(IDC_CHK_ENVLP_ENB, &CDlgTcgProc::OnBnClickedChkEnvlpEnb)
	ON_BN_CLICKED(IDC_CHK_TCG_ENB, &CDlgTcgProc::OnBnClickedChkTcgEnb)
	ON_BN_CLICKED(IDC_BTN_TCG_ADD_TP, &CDlgTcgProc::OnBnClickedBtnTcgAddTp)
	ON_BN_CLICKED(IDC_BTN_TCG_DEL_TP, &CDlgTcgProc::OnBnClickedBtnTcgDelTp)
	ON_BN_CLICKED(IDC_BTN_TCG_RST_TP, &CDlgTcgProc::OnBnClickedBtnTcgRstTp)
	ON_NOTIFY(NM_CLICK, IDC_LST_TCG_TP, &CDlgTcgProc::OnNMClickLstTcgTp)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 初始化对话框
//
////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDlgTcgProc::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	CString str;

	if (param.m_nHoriDisp == HORI_DISP_US)
	{
		str.Format("位置(us)");
	}
	else
	{
		str.Format("位置(mm)");
	}
	m_lstTcgTp.InsertColumn(SN_TCG_TP_LOC,	str,	LVCFMT_RIGHT, 100);

	m_lstTcgTp.InsertColumn(SN_TCG_TP_NUM,	"序号",	LVCFMT_RIGHT, 50);
	m_lstTcgTp.InsertColumn(SN_TCG_TP_GAIN,	"增益(dB)",	LVCFMT_RIGHT, 80);
	m_lstTcgTp.DeleteAllItems();	// 删除当前所有内容

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT;
	m_lstTcgTp.GetColumn(SN_TCG_TP_NUM, &lvc);
	lvc.fmt &= ~LVCFMT_JUSTIFYMASK;
	lvc.fmt |= LVCFMT_RIGHT;		// 这里指定第1列的对齐方式
	m_lstTcgTp.SetColumn(SN_TCG_TP_NUM, &lvc);

	// 设置控件扩展属性
	DWORD dwExtStyle = m_lstTcgTp.GetExtendedStyle();
	dwExtStyle |= LVS_EX_FULLROWSELECT;	// 整行选中
	dwExtStyle |= LVS_EX_GRIDLINES;		// 显示栅格线
	m_lstTcgTp.SetExtendedStyle(dwExtStyle);

	m_nTcgTpIdx = 0;

	FreshTcgBtnSts();

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	m_chkTcgEnb.SetCheck(tcg_param.tp_bTcgEnb);

	ProcTcgEnb(tcg_param.tp_bTcgEnb);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新TCG测试点，切换TAB时
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::FreshTcgTp(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	U8 hori_disp = param.m_nHoriDisp;

	m_lstTcgTp.DeleteAllItems();	// 删除当前所有内容

	if (tcg_param.tp_nTcgTpTot == 0) return;	// 无测试点，返回

	LVITEM lvi;
	lvi.mask =  LVIF_TEXT;

	char strNum[100], strLoc[100], strGain[100];
	for (U8 i = 0; i < tcg_param.tp_nTcgTpTot; i++)
	{
		lvi.iItem = i;

		// 序号
		lvi.iSubItem = SN_TCG_TP_NUM;
		sprintf(strNum, "%d", i + 1);
		lvi.pszText = strNum;
		m_lstTcgTp.InsertItem(&lvi);

		// 位置
		lvi.iSubItem = SN_TCG_TP_LOC;
		if (hori_disp == HORI_DISP_MM)
		{
			sprintf(strLoc, "%.3f", tcg_param.tp_fTcgTpDist[i]);	// mm
		}
		else
		{
			sprintf(strLoc, "%.3f", tcg_param.tp_nTcgTpTime[i] / 1000.0f);	// us
		}
		lvi.pszText = strLoc;
		m_lstTcgTp.SetItem(&lvi);

		// 增益
		lvi.iSubItem = SN_TCG_TP_GAIN;
		sprintf(strGain, "%d.%d", tcg_param.tp_nTcgTpGain[i] / 10, tcg_param.tp_nTcgTpGain[i] % 10);
		lvi.pszText = strGain;
		m_lstTcgTp.SetItem(&lvi);
	}

	SelTcgTp(m_nTcgTpIdx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 包络使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::OnBnClickedChkEnvlpEnb(void)
{
	m_pApp->m_bEnvlpEnb = ((CButton*)GetDlgItem(IDC_CHK_ENVLP_ENB))->GetCheck();
	memset(m_pApp->m_anEnvlpBuf, 0x00, sizeof(m_pApp->m_anEnvlpBuf));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 增加测试点
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::OnBnClickedBtnTcgAddTp(void)
{
	ST_GATE_RES& gate_res = m_pApp->m_stGateRes[GATE_SEL_A];
	U16 x = gate_res.gr_xPeak;
	U16 y = gate_res.gr_yPeak;
	U16 t = gate_res.gr_tPeak;

	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
	U8 hori_disp = param.m_nHoriDisp;
	U32 sound_velo = param.m_anSoundVelo[hard_num][soft_num];
	F32 pdist = ZXUT_GetTstRange(freq_ratio, x, t, sound_velo);	// mm
	U32 ptime = ZXUT_GetTstTime(freq_ratio, x, t);	// ns

	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	tcg_param.tp_nTcgTpTot++;
	m_nTcgTpIdx = tcg_param.tp_nTcgTpTot - 1;

	////////////////////////////////////////////////////////////////////////////////////////////////

	// +，需要衰减；-，需要放大
	S16 delta = (S16)((20 * log10((F32)y) - 20 * log10((F32)m_pApp->m_nAutoGainHeight)) * 10);
	U16 db_code = param.m_anDbNum[hard_num][soft_num] - delta;	// 类似于自动增益

	tcg_param.tp_fTcgTpDist[m_nTcgTpIdx] = pdist;	// mm
	tcg_param.tp_nTcgTpTime[m_nTcgTpIdx] = ptime;	// ns
	tcg_param.tp_nTcgTpGain[m_nTcgTpIdx] = db_code;

	////////////////////////////////////////////////////////////////////////////////////////////////

	SortTcgTp();
	FreshTcgTp();
	SelTcgTp(m_nTcgTpIdx);

	FreshTcgBtnSts();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 删除测试点
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::OnBnClickedBtnTcgDelTp(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;

	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	U8& nTcgTpTot = tcg_param.tp_nTcgTpTot;

	S32 res = m_pApp->DispMsg(ZXUT_MSG_ASK, "真的要删除第%d个TCG测试点吗？", m_nTcgTpIdx + 1);
	if (res != IDYES) return;	// 不确认，直接返回

	if (m_nTcgTpIdx == nTcgTpTot - 1)
	{
		// 最后一个测试点，仅改变测试点总数
		nTcgTpTot--;
		m_nTcgTpIdx = nTcgTpTot - 1;
	}
	else
	{
		// 中间测试点，后面的往前面移
		for (U8 i = m_nTcgTpIdx + 1; i < nTcgTpTot; i++)
		{
			tcg_param.tp_fTcgTpDist[i - 1] = tcg_param.tp_fTcgTpDist[i];
			tcg_param.tp_nTcgTpTime[i - 1] = tcg_param.tp_nTcgTpTime[i];
			tcg_param.tp_nTcgTpGain[i - 1] = tcg_param.tp_nTcgTpGain[i];
		}
		nTcgTpTot--;
	}

	FreshTcgBtnSts();

	if (nTcgTpTot == 0)
	{
		m_lstTcgTp.DeleteAllItems();	// 删除当前所有内容
		return;
	}

	SortTcgTp();
	FreshTcgTp();
	SelTcgTp(m_nTcgTpIdx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 重设测试点
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::OnBnClickedBtnTcgRstTp(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];

	S32 res = m_pApp->DispMsg(ZXUT_MSG_ASK, "真的要清除所有TCG测试点吗？");
	if (res != IDYES) return;	// 不确认，直接返回

	m_lstTcgTp.DeleteAllItems();	// 删除当前所有内容

	tcg_param.tp_nTcgTpTot = 0;
	m_nTcgTpIdx = 0;
	for (U8 i = 0; i < TCG_TP_NUM_MAX; i++)
	{
		tcg_param.tp_fTcgTpDist[i] = 0.0f;	// mm
		tcg_param.tp_nTcgTpTime[i] = 0;		// ns
		tcg_param.tp_nTcgTpGain[i] = 0;
	}

	FreshTcgBtnSts();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 选择测试点
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::SelTcgTp(U8 idx)
{
	if (idx >= (U32)m_lstTcgTp.GetItemCount())
	{
		m_pApp->DispMsg(ZXUT_MSG_ERR, "选择的测试点无效");
		return;
	}

	m_lstTcgTp.SetItemState(idx, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_lstTcgTp.EnsureVisible(idx, FALSE);
	m_lstTcgTp.SetFocus();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 左键单击
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::OnNMClickLstTcgTp(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem < 0)
	{
		return;
	}

	m_nTcgTpIdx = pNMListView->iItem;
	*pResult = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 参考点排序
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::SortTcgTp(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	U8 nTcgTpTot = tcg_param.tp_nTcgTpTot;

	if ((nTcgTpTot == 0) || (nTcgTpTot == 1)) return;	// 若只有一个测试点或者没有，则不用排序

	U8 i, j;
	U16 tmpGain;
	F32 tmpDist;
	U32 tmpTime;
	for (j = 0; j < nTcgTpTot - 1; j++)
	{
		for (i = 0; i < nTcgTpTot - 1 - j; i++)
		{
			// 按距离的升序排序
			if (tcg_param.tp_fTcgTpDist[i] > tcg_param.tp_fTcgTpDist[i + 1])
			{
				tmpDist = tcg_param.tp_fTcgTpDist[i];
				tcg_param.tp_fTcgTpDist[i] = tcg_param.tp_fTcgTpDist[i + 1];
				tcg_param.tp_fTcgTpDist[i + 1] = tmpDist;

				tmpTime = tcg_param.tp_nTcgTpTime[i];
				tcg_param.tp_nTcgTpTime[i] = tcg_param.tp_nTcgTpTime[i + 1];
				tcg_param.tp_nTcgTpTime[i + 1] = tmpTime;

				tmpGain = tcg_param.tp_nTcgTpGain[i];
				tcg_param.tp_nTcgTpGain[i] = tcg_param.tp_nTcgTpGain[i + 1];
				tcg_param.tp_nTcgTpGain[i + 1] = tmpGain;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 更新按钮状态
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::FreshTcgBtnSts(void)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	U8 nTcgTpTot = tcg_param.tp_nTcgTpTot;
	U8 bTcgEnb = tcg_param.tp_bTcgEnb;
	BOOL bSmplEnb = m_pApp->m_bSmplEnb;

	// TCG使能：采样开启，且至少有2个测试点
	m_chkTcgEnb.EnableWindow((bSmplEnb == TRUE) && (nTcgTpTot >= 2));

	// 测试点列表使能：采样开启，且至少有1个测试点
	m_lstTcgTp.EnableWindow ((bSmplEnb == TRUE) && (nTcgTpTot >= 1));

	// 增加测试点：采样开启
	m_btnTcgTpAdd.EnableWindow((bTcgEnb == FALSE) && (bSmplEnb == TRUE));

	// 删除/重设测试点：TCG关闭，且至少有1个测试点
	m_btnTcgTpDel.EnableWindow((bTcgEnb == FALSE) & (nTcgTpTot >= 1));
	m_btnTcgTpRst.EnableWindow((bTcgEnb == FALSE) & (nTcgTpTot >= 1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TCG使能
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::OnBnClickedChkTcgEnb(void)
{
	ProcTcgEnb(m_chkTcgEnb.GetCheck());
	FreshTcgBtnSts();
}

void CDlgTcgProc::ProcTcgEnb(BOOL enb)
{
	U8 hard_num = m_pApp->m_nHardNum;
	U8 soft_num = m_pApp->m_nSoftNum;
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	ST_TCG_PARAM& tcg_param = param.m_stTcgParam[hard_num][soft_num];
	U8& tcg_enb = tcg_param.tp_bTcgEnb;
	tcg_enb = enb;
	U8 nTcgTpTot = tcg_param.tp_nTcgTpTot;

	U16 freq_ratio = param.m_stCoreParam.m_anFreqRatio[hard_num][soft_num];
	U16 smpl_depth = param.m_stCoreParam.m_anSmplDepth[hard_num][soft_num];

	U32 tot_time = ZXUT_GetTstTime(freq_ratio, smpl_depth, 0); // 当前采样深度共需要多长TCG时间

	if (tcg_enb == TRUE)
	{
		// 开启TCG，还需发送总时间、测试点点数、测试点时间和测试点增益
		ZXUT_SetTcgTotTime(hard_num, soft_num, tot_time);
		ZXUT_SetTcgTpTot(hard_num, soft_num, nTcgTpTot);

		for (U8 i = 0; i < nTcgTpTot; i++)
		{
			ZXUT_SetTcgTpIdx(hard_num, soft_num, i);
			ZXUT_SetTcgTpTime(hard_num, soft_num, tcg_param.tp_nTcgTpTime[i]);
			ZXUT_SetTcgTpGain(hard_num, soft_num, tcg_param.tp_nTcgTpGain[i]);
		}

		ZXUT_SetTcgEnb(hard_num, soft_num, tcg_enb);
	}
	else
	{
		// 关闭TCG，仅需发送该命令
		ZXUT_SetTcgEnb(hard_num, soft_num, tcg_enb);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 设置指定列号的文本
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgTcgProc::FreshTcgColText(void)
{
	ST_FLAW_PARAM& param = m_pApp->m_stFlawParam;
	CString str;
	if (param.m_nHoriDisp == HORI_DISP_US)
	{
		str.Format("位置(us)");
	}
	else
	{
		str.Format("位置(mm)");
	}

	LVCOLUMN pColumn;
	m_lstTcgTp.GetColumn(SN_TCG_TP_LOC, &pColumn);
	pColumn.pszText=(LPTSTR)(LPCSTR)str;
	m_lstTcgTp.SetColumn(SN_TCG_TP_LOC, &pColumn);
}
