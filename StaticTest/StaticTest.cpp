// StaticTest.cpp : ���x DLL ���ó�ʽ�ąR����ʽ��
//

#include "stdafx.h"
#include "StaticTest.h"
#include "mdc_common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "libmdccommon.lib")

STATICTEST_API int fnStaticTest(void)
{
	WriteLog(_T("test"), _T("abc"));
	return 0;
}