
// Magic_LightCube.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "resource.h" 

// CMagic_LightCubeApp:
// �йش����ʵ�֣������ Magic_LightCube.cpp
//

class CMagic_LightCubeApp : public CWinApp
{
public:
	CMagic_LightCubeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMagic_LightCubeApp theApp;
