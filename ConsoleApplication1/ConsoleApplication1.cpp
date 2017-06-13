// ConsoleApplication1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "ConsoleApplication1.h"
#include "StaticTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "StaticTest.lib")

// 僅有的一個應用程式物件

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

	fnStaticTest();

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 並於失敗時列印錯誤
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 配合您的需要變更錯誤碼
            wprintf(L"嚴重錯誤: MFC 初始化失敗\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此撰寫應用程式行為的程式碼。
        }
    }
    else
    {
        // TODO: 配合您的需要變更錯誤碼
        wprintf(L"嚴重錯誤: GetModuleHandle 失敗\n");
        nRetCode = 1;
    }

	getchar();

    return nRetCode;
}
