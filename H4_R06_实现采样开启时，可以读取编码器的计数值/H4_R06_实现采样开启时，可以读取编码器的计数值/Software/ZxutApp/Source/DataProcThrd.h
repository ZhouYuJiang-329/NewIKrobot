#pragma once

typedef unsigned int (WINAPI *LPTHREAD_ROUTINE)(LPVOID lpThreadData);

class CThreadContext
{
public:
	CThreadContext(void)
	{
		memset(this, 0, sizeof(this));
	}

	HANDLE 			m_hThread;		// 线程句柄
	unsigned int  	m_nTID;			// 线程ID
	LPVOID 			m_pUserData;	// 用户数据指针
	unsigned int  	m_nExitCode;	// 线程退出码
};

class CDataProcThrd
{
public:
	CDataProcThrd(void);
	~CDataProcThrd(void);

	void Kill(void);			// 杀死运行线程
	DWORD Start(LPVOID lpArg, int nThrdPriority);		// 启动线程运行

private:
	void Run(LPVOID lpArg);		// 线程实际运行程序
	static unsigned int WINAPI EntryPoint(LPVOID pArg);	// 线程入口程序
	void SignExitCode(void);	// 设置退出码

	volatile BOOL m_bTermThrdFlg;
	HANDLE m_hEventAckStopThrd;		// 结束线程事件

	CThreadContext m_ThreadCtx;		// 线程上下文
	LPTHREAD_ROUTINE m_pThreadFunc;
};
