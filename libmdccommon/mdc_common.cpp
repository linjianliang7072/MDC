#include "stdafx.h"
#include "mdc_common.h"

TCHAR g_logspath[256] = { 0 };
TCHAR g_VMsg[256];

HANDLE g_hLogex = CreateMutex(NULL, FALSE, NULL);

volatile int	g_LogDate = -1;

const CString LOG_NAME = _T("%s\\MDCSDK_%04d%02d%02d.log");

//---------------------------------------------------------------------------
//  建立日誌資料夾
//---------------------------------------------------------------------------
void CreateLogFolder()
{
	OutputDebugString(TEXT("CreateLogFolder\n"));
	GetCurrentDirectory(256, g_logspath);
	_tcscat_s(g_logspath, _T("\\Logs"));
	CreateDirectory(g_logspath, NULL);

	/*
	CString sPath;
	sPath.Format(_T("\\%04d%02d%02d"), CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
	_tcscat_s(g_logspath, sPath);
	CreateDirectory(g_logspath, NULL);
	*/
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//  輸出日誌函數
//---------------------------------------------------------------------------
#ifdef _LIB
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
		sPath.Format(LOG_NAME, g_logspath, CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
		WORD whandle = 0xFEFF;
		FILE* fp = _tfopen(sPath, _T("a"));
		fwrite(&whandle, 2, 1, fp);
		fclose(fp);
		g_LogDate = CTime::GetCurrentTime().GetDay();
	}

	FILE *pFile;
	sPath.Format(LOG_NAME, g_logspath, CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(), CTime::GetCurrentTime().GetDay());
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
#ifdef _LIB
void WriteLog(TCHAR* mevent, TCHAR* msg)
#else
void __stdcall WriteLog(TCHAR* mevent, TCHAR* msg)
#endif
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	WriteLog(_T("%s - %s"), mevent, msg);
}
