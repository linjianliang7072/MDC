// ProcessTest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <windows.h>
#include "stdio.h"
#include <tlhelp32.h>
#include "Psapi.h"
#include <ctype.h>

bool IsProcessExist(TCHAR *exe_name)
{
	int num = 0;
	
	PROCESSENTRY32 pe32;//用于存放进程信息的结构体
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//创建进程快照

	pe32.dwSize = sizeof(pe32);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	bool exist = false;

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);//获取第一个进程信息到pe32结构体中

	while (bMore)
	{
		for (int i = 0; i < sizeof(pe32.szExeFile); i++)
			pe32.szExeFile[i] = towupper(pe32.szExeFile[i]);
		printf("name: %ls, num: %d, IDs: %d\n", pe32.szExeFile, num, pe32.th32ProcessID);

		if (!_tcscmp(exe_name, pe32.szExeFile))//发现要寻找的进程后结束查找
		{
			exist = true;
			break;
		}
		num++;
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);

	return exist;
}

int main()
{
	/*
	int num = 0;
	TCHAR exe_name[20] = _T("sublime_text.exe");//要查询的进程名

	PROCESSENTRY32 pe32;//用于存放进程信息的结构体
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//创建进程快照

	pe32.dwSize = sizeof(pe32);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed!\n");
		return -1;
	}

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);//获取第一个进程信息到pe32结构体中

	while (bMore)
	{
		printf("name: %ls, num: %d, IDs: %d\n", pe32.szExeFile, num, pe32.th32ProcessID);

		if (!_tcscmp(exe_name, pe32.szExeFile))//发现要寻找的进程后结束查找
		{
			printf("find the file you want: %ls\n", pe32.szExeFile);
			break;
		}
		num++;
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	*/

	bool check = IsProcessExist(_T("SUBLIME_TEXT.EXE"));

	printf("check: %d\n", check);

	getchar();

    return 0;
}

