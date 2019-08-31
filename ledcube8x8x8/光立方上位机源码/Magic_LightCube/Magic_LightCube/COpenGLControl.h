#pragma once

#ifndef _COPenGLControl_
#define _COPenGLControl_

#include "gl/gl.h"
#include "gl/glu.h"

#include <afxwin.h>
class COpenGLControl :
	public CWnd
{
public:
	COpenGLControl();
	virtual ~COpenGLControl();

	UINT_PTR m_unpTimer;

private:
	CWnd *hWnd;
	HDC hdc;
	HGLRC hrc;
	int m_nPixelFormat;
	CRect m_rect;
	CRect m_oldWindow;
	CRect m_originalRect;
	float m_angle;
	float m_fPosX, m_fPosY;
	float m_fRotX, m_fRotY;
	float m_fLastX, m_fLastY;
	float m_fZoom;

public:
	void oglCreate(CRect rect, CWnd* parent);
	void oglInitialize(void);
	void Render();
	void DrawPlane(float size, float step);
	void DrawCube(float size, int resolution);
	void COpenGLControl::CallRender();


	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDraw(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#endif

