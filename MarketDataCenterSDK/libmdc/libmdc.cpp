// libmdc.cpp : 定義 DLL 應用程式的匯出函式。
//

#include "stdafx.h"
#include "libmdc.h"


volatile int	g_LogDate = -1;

TCHAR g_logspath[256] = { 0 };
TCHAR g_VMsg[256];

HANDLE g_hLogex = CreateMutex(NULL, FALSE, NULL);

zmq::context_t *zmq_context = NULL;
zmq::socket_t *req_socket = NULL;

bool is_inited = false;

std::string agent_port = "tcp://*:8888";

//-----------------------------------------------------------------------------------
//  萬國碼轉多字元碼
//-----------------------------------------------------------------------------------
#ifdef _STATIC
void UnicodeToAnsi(TCHAR *unicode, char* ansi)
#else
void __stdcall UnicodeToAnsi(TCHAR *unicode, char* ansi)
#endif
{
	int n = WideCharToMultiByte(CP_ACP, 0, unicode, -1, NULL, 0, NULL, FALSE);
	WideCharToMultiByte(CP_ACP, 0, unicode, -1, ansi, n, NULL, FALSE);
}

//-----------------------------------------------------------------------------------
//  多字元碼轉萬國碼
//-----------------------------------------------------------------------------------
#ifdef _STATIC
void AnsiToUnicode(char* ansi, TCHAR* unicode)
#else
void __stdcall AnsiToUnicode(char* ansi, TCHAR* unicode)
#endif
{
	int n = MultiByteToWideChar(CP_ACP, 0, ansi, (int)strlen(ansi) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, ansi, (int)strlen(ansi) + 1, unicode, n);
}

//---------------------------------------------------------------------------
//  建立日誌資料夾
//---------------------------------------------------------------------------
void CreateLogFolder()
{
	OutputDebugString(TEXT("CreateLogFolder\n"));
	GetCurrentDirectory(256, g_logspath);
	_tcscat_s(g_logspath, _T("\\Logs"));
	CreateDirectory(g_logspath, NULL);

	CString sPath;
	sPath.Format(_T("\\%04d%02d%02d"), CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
	_tcscat_s(g_logspath, sPath);
	CreateDirectory(g_logspath, NULL);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//  輸出日誌函數
//---------------------------------------------------------------------------
#ifdef _STATIC
void WriteLog(TCHAR* sFormat, ...)
#else
void __stdcall WriteLog(TCHAR* sFormat, ...)
#endif
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (_tcscmp(g_logspath, _TEXT("")) == 0)
	{
		CreateLogFolder();
	}

	WaitForSingleObject(g_hLogex, 50);

	CString sPath;

	//	依日期設定檔名
	if (g_LogDate != CTime::GetCurrentTime().GetDay())
	{
		CreateLogFolder();
		sPath.Format(_T("%s\\%04d-%02d-%02d.log"), g_logspath, CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
		WORD whandle = 0xFEFF;
		FILE* fp = _tfopen(sPath, _T("a"));
		fwrite(&whandle, 2, 1, fp);
		fclose(fp);
		g_LogDate = CTime::GetCurrentTime().GetDay();
	}

	FILE *pFile;
	sPath.Format(_T("%s\\%04d-%02d-%02d.log"), g_logspath, CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
	pFile = _tfopen(sPath, _T("a+, ccs=UNICODE"));

	if (NULL == pFile)
	{
		ReleaseMutex(g_hLogex);
		return;
	}

	CString			sTemp;
	CTime			tNow = CTime::GetCurrentTime();
	TCHAR			sBuffer[1024];
	va_list			pArgList;

	//	取出格式化字串
	va_start(pArgList, sFormat);
	_vsnwprintf(sBuffer, sizeof(sBuffer) / sizeof(TCHAR), sFormat, pArgList);
	va_end(pArgList);

	//	寫入檔案
	SYSTEMTIME		t;
	GetSystemTime(&t);
	sTemp.Format(_T("[%02d:%02d:%02d.%03d] %s .\n"), tNow.GetHour(), tNow.GetMinute(), tNow.GetSecond(), t.wMilliseconds, sBuffer);

	_ftprintf(pFile, sTemp);
	fclose(pFile);
	ReleaseMutex(g_hLogex);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//  輸出日誌函數
//---------------------------------------------------------------------------
#ifdef _STATIC
void WriteLog(TCHAR* mevent, TCHAR* msg)
#else
void __stdcall WriteLog(TCHAR* mevent, TCHAR* msg)
#endif
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	WriteLog(_T("%s - %s"), mevent, msg);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//  格式化日誌
//---------------------------------------------------------------------------
void VWriteLog(TCHAR* sFormat, ...)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (_tcscmp(g_logspath, _TEXT("")) == 0)
	{
		CreateLogFolder();
	}

	WaitForSingleObject(g_hLogex, 50);

	CString sPath;

	//	依日期設定檔名
	if (g_LogDate != CTime::GetCurrentTime().GetDay())
	{
		CreateLogFolder();
		sPath.Format(_T("%s\\%04d-%02d-%02d.log"), g_logspath, CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
		WORD whandle = 0xFEFF;
		FILE* fp = _tfopen(sPath, _T("a"));
		fwrite(&whandle, 2, 1, fp);
		fclose(fp);
		g_LogDate = CTime::GetCurrentTime().GetDay();
	}

	FILE *pFile;
	sPath.Format(_T("%s\\%04d-%02d-%02d.log"), g_logspath, CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
	pFile = _tfopen(sPath, _T("a+, ccs=UNICODE"));

	if (NULL == pFile)
	{
		ReleaseMutex(g_hLogex);
		return;
	}

	CString			sTemp;
	CTime			tNow = CTime::GetCurrentTime();
	TCHAR			sBuffer[1024];
	va_list			pArgList;

	//	取出格式化字串
	va_start(pArgList, sFormat);
	_vsnwprintf(sBuffer, sizeof(sBuffer) / sizeof(TCHAR), sFormat, pArgList);
	va_end(pArgList);

	//	寫入檔案
	SYSTEMTIME		t;
	GetSystemTime(&t);
	sTemp.Format(_T("[%02d:%02d:%02d.%03d] %s .\n"), tNow.GetHour(), tNow.GetMinute(), tNow.GetSecond(), t.wMilliseconds, sBuffer);

	_ftprintf(pFile, sTemp);
	fclose(pFile);

	//	複製錯誤訊息
	_tcsncpy(g_VMsg, sBuffer, sizeof(g_VMsg) / sizeof(TCHAR));
	ReleaseMutex(g_hLogex);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//  固定化日誌
//---------------------------------------------------------------------------
void VWriteLog(TCHAR* mevent, CString msg)
{
	VWriteLog(_T("%s - %s"), mevent, msg);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
//  輸出日誌函數
//-----------------------------------------------------------------------------------
void VWriteLog(TCHAR* mevent, int num)
{
	CString msg;
	msg.Format(_T("%d"), num);
	VWriteLog(mevent, msg.GetBuffer(msg.GetLength()));
}

LIBMDC_API void WINAPI mdc_set_agent_addr(char *ip, char *port)
{

}

LIBMDC_API int WINAPI mdc_init()
{
	VWriteLog(_T("mdc_init"), "begin");

	if (!is_inited)
	{
		zmq_context = new zmq::context_t(1);
		req_socket = new zmq::socket_t(*zmq_context, ZMQ_REP);

		is_inited = true;
	}
	VWriteLog(_T("mdc_init"), "end");
	return 0;
}

LIBMDC_API int WINAPI mdc_close()
{
	if (is_inited)
	{
		if (req_socket) req_socket->close();
		if (zmq_context) zmq_context->close();

		is_inited = false;
	}

	return 0;
}

LIBMDC_API int WINAPI mdc_destory()
{
	if (req_socket) delete req_socket;
	if (zmq_context) delete zmq_context;

	return 0;
}
/*
LIBMDC_API int WINAPI mdc_get_last_message(TCHAR* message)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	_tcscpy(message, g_VMsg);
	return 0;
}
*/