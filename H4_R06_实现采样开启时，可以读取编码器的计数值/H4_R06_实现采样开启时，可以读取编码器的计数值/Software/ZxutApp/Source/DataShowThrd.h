#pragma once

class CDataShowThrd
{
public:
	CDataShowThrd(void);
	~CDataShowThrd(void);

	void Kill(void);			// 杀死运行线程
	DWORD Start(LPVOID lpArg, int nThrdPriority);		// 启动线程运行

private:
	void Run(LPVOID lpArg);		// 线程实际运行程序
	static unsigned int WINAPI EntryPoint(LPVOID pArg);	// 线程入口程序
	void SignExitCode(void);	// 设置退出码

	volatile BOOL m_bTermThrdFlg;
	HANDLE m_hEventAckStopThrd;		// 结束线程事件

	HANDLE m_hEventWait;

	CThreadContext m_ThreadCtx;		// 线程上下文
	LPTHREAD_ROUTINE m_pThreadFunc;
};
