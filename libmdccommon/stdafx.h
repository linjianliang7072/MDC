﻿// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 從 Windows 標頭排除不常使用的成員
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 明確定義部分的 CString 建構函式
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // 在對話方塊中移除 MFC 控制項的支援

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 從 Windows 標頭排除不常使用的成員
#endif

#include <afx.h>
#include <afxwin.h>         // MFC 核心與標準元件



// TODO:  在此參考您的程式所需要的其他標頭
