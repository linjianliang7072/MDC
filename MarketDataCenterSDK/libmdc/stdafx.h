// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
//

#pragma once

#define _AFXDLL

#include "targetver.h"

// Windows 標頭檔: 
#include <afx.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <iostream>


// TODO:  在此參考您的程式所需要的其他標頭

#include "zmq.hpp"
#include "unistd.h"

#pragma comment(lib, "libzmq.lib")
/*
#ifdef _DEBUG
#pragma comment(lib, "libcmtd.lib")
#else
#pragma comment(lib, "libcmt.lib")
#endif
*/