#include "StdAfx.h"
#include "ZxutApp.h"
#include "DataProcThrd.h"

CDataProcThrd::CDataProcThrd(void)
{
	m_hEventAckStopThrd = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_bTermThrdFlg = FALSE;
	m_pThreadFunc = CDataProcThrd::EntryPoint;
}

CDataProcThrd::~CDataProcThrd(void)
{
	if (m_ThreadCtx.m_hThread)
	{
		CloseHandle(m_ThreadCtx.m_hThread);
		m_ThreadCtx.m_hThread = NULL;
	}

	if (m_hEventAckStopThrd)
	{
		CloseHandle(m_hEventAckStopThrd);
		m_hEventAckStopThrd = NULL;
	}
}

void CDataProcThrd::Kill(void)
{
	if (m_hEventAckStopThrd && (m_ThreadCtx.m_nExitCode == STILL_ACTIVE))
	{
		m_bTermThrdFlg = TRUE;
		if (WaitForSingleObject(m_hEventAckStopThrd, 1000) == WAIT_TIMEOUT)
		{
			// 超时，需要强制杀死数据处理线程
			TRACE("*** 1秒钟超时，已强制杀死数据处理线程\n");
			SignExitCode();
			TerminateThread(m_ThreadCtx.m_hThread, m_ThreadCtx.m_nExitCode);
		}
		else
		{
			// 线程已退出
			TRACE("已杀死数据处理线程\n");
		}
		Sleep(5);	// 等待继承类完全退出
	}
}

DWORD CDataProcThrd::Start(LPVOID lpArg, int nThrdPriority)
{
	m_ThreadCtx.m_pUserData = lpArg;
	m_ThreadCtx.m_hThread = (HANDLE)_beginthreadex(
		NULL, 0, m_pThreadFunc, this,
		CREATE_SUSPENDED,	// 暂停执行
		&m_ThreadCtx.m_nTID);
	m_ThreadCtx.m_nExitCode = STILL_ACTIVE;
	::SetThreadPriority(m_ThreadCtx.m_hThread, nThrdPriority);
	::ResumeThread(m_ThreadCtx.m_hThread);
	return GetLastError();
}

unsigned int WINAPI CDataProcThrd::EntryPoint(LPVOID pArg)
{
	CDataProcThrd *pParent = reinterpret_cast<CDataProcThrd*>(pArg);
	pParent->Run(pParent->m_ThreadCtx.m_pUserData);
	return pParent->m_ThreadCtx.m_nExitCode;
}

void CDataProcThrd::SignExitCode(void)
{
	m_ThreadCtx.m_nExitCode = (unsigned int)0;
}

void CDataProcThrd::Run(LPVOID lpArg)
{
	CZxutApp* pApp = (CZxutApp*)lpArg;

	while (TRUE)
	{
		if (m_bTermThrdFlg == FALSE)
		{
			pApp->ThrdDataProcHandler();	// 调用数据处理线程函数
		}
		else
		{
			break;
		}
	}

	TRACE("成功退出数据处理线程\n");
	SetEvent(m_hEventAckStopThrd);
	SignExitCode();
}
