// ConsoleApplication1.cpp : ���x����̨���ó�ʽ���M���c��
//

#include "stdafx.h"
#include "ConsoleApplication1.h"
#include "StaticTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "StaticTest.lib")

// �H�е�һ�����ó�ʽ���

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

	fnStaticTest();

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // ��ʼ�� MFC �K�ʧ���r��ӡ�e�`
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: ���������Ҫ׃���e�`�a
            wprintf(L"�����e�`: MFC ��ʼ��ʧ��\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: �ڴ�׫�����ó�ʽ�О�ĳ�ʽ�a��
        }
    }
    else
    {
        // TODO: ���������Ҫ׃���e�`�a
        wprintf(L"�����e�`: GetModuleHandle ʧ��\n");
        nRetCode = 1;
    }

	getchar();

    return nRetCode;
}
