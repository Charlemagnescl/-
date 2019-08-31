
// Magic_LightCube.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "resource.h" 

// CMagic_LightCubeApp:
// 有关此类的实现，请参阅 Magic_LightCube.cpp
//

class CMagic_LightCubeApp : public CWinApp
{
public:
	CMagic_LightCubeApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMagic_LightCubeApp theApp;
