#include "stdafx.h"
#include "COpenGLControl.h"

#include <gl/gl.h>
#include <gl/glu.h>

#define Plies 8
#define View 3
#define Axis_X 8
#define Axis_Y 8

enum STATE { LOW, HIGH };
extern STATE m_arrayDot[Plies][View][Axis_X][Axis_Y];

COpenGLControl::COpenGLControl()
{
	m_fPosX = 0.0f;    // X position of model in camera view
	m_fPosY = 0.0f;    // Y position of model in camera view
	m_fZoom = 10.0f;   // Zoom on model in camera view
	m_fRotX = 0.0f;    // Rotation on model in camera view
	m_fRotY = 0.0f;    // Rotation on model in camera view
	m_fLastX = m_fLastY = 0.0f;
}


COpenGLControl::~COpenGLControl()
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW |
		CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	const char c[] = "OpenGL";

	CreateEx(0, (LPCTSTR)className, (LPCTSTR)c, WS_CHILD | WS_VISIBLE |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	m_oldWindow = rect;
	m_originalRect = rect;
	
	hWnd = parent;
}
BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void COpenGLControl::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()
	ValidateRect(NULL);

}


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	oglInitialize();

	return 0;
}

void COpenGLControl::oglInitialize(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
	   sizeof(PIXELFORMATDESCRIPTOR),
	   1,
	   PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	   PFD_TYPE_RGBA,
	   32,    // bit depth
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   16,    // z-buffer depth
	   0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
	glClearDepth(1.0f);
	m_angle = 0.0f;
	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Send draw request
	OnDraw(NULL);

}

void COpenGLControl::OnDraw(CDC* pDC)
{
	//TODO
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
	Render();
	SwapBuffers(hdc);
}




void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
		case 1:
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Draw OpenGL scene
			Render();

			//Swap buffers
			SwapBuffers(hdc);

			break;
		}
		default:
			break;
	}
	
	CWnd::OnTimer(nIDEvent);
}


void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
		return;

	glViewport(0, 0, cx,cy);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);	
	
}

void COpenGLControl::Render()
{
	//3d paint
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(18, 30, -40, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	m_angle += 1.0f;
	if (m_angle > 360.0f)
		m_angle = 0.0f;

	//glTranslatef(0.0f, 0.0f, -5.0f);
	//glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
	//glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
	//glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCube(9.0, 8);
	glPopMatrix();

}

void COpenGLControl::DrawPlane(float size, float step)
{
	float sizef = size / step;
	bool flag = false;
	int i, j, k;
	int targetX =4, targetY =1, targetZ = 6;
	glNormal3f(0.0f, -1.0f, 0.0f);
	for (float y = 0.0f,j =0; y < size; y += step + 1.0, j++)
	{
		for (float z = 0, k =0; z < size; z += step + 1.0, k++)
		{
			for (float x = 0, i =0; x < size; x += step + 1.0, i++)
			{
				if (m_arrayDot[(int)k][0][(int)i][(int)j] == HIGH)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glColor3f(0.2, 0.6, 1.0);
					
					flag = true;
				}
				glBegin(GL_QUADS);

				glVertex3f(x, y, z);
				glVertex3f(x + step, y, z);
				glVertex3f(x + step, y, z + step);
				glVertex3f(x, y, z + step);

				glVertex3f(x, y + step, z);
				glVertex3f(x + step, y + step, z);
				glVertex3f(x + step, y + step, z + step);
				glVertex3f(x, y + step, z + step);

				glEnd();
				if (flag) {
					glColor3f(0, 0, 0);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					flag = false;
				}


			}
		}
	}


	for (float x = 0.0f, i =0; x < size; x += step + 1.0, i++)
	{
		for (float y = 0, j = 0; y < size; y += step + 1.0, j++)
		{
			for (float z = 0, k = 0; z < size; z += step + 1.0, k++)
			{
				if (m_arrayDot[(int)k][0][(int)i][(int)j] == HIGH)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glColor3f(0.2, 0.6, 1.0);

					flag = true;
				}
				glBegin(GL_QUADS);

				glVertex3f(x, y, z);
				glVertex3f(x , y, z + step);
				glVertex3f(x , y + step, z + step);
				glVertex3f(x, y + step, z);

				glVertex3f(x + step, y, z);
				glVertex3f(x +step, y, z + step);
				glVertex3f(x + step, y + step, z + step);
				glVertex3f(x + step, y + step, z);

				glEnd();
				if (flag) {
					glColor3f(0, 0, 0);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					flag = false;
				}


			}
		}
	}

	for (float z = 0.0f, k = 0; z < size; z += step + 1.0, k++)
	{
		for (float y = 0, j = 0; y < size; y += step + 1.0, j++)
		{
			for (float x = 0, i = 0; x < size; x += step + 1.0, i++)
			{
				if (m_arrayDot[(int)k][0][(int)i][(int)j] == HIGH)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glColor3f(0.2, 0.6, 1.0);

					flag = true;
				}
				glBegin(GL_QUADS);

				glVertex3f(x, y, z);
				glVertex3f(x + step, y, z);
				glVertex3f(x + step, y + step, z);
				glVertex3f(x, y + step, z);

				glVertex3f(x, y, z + step);
				glVertex3f(x + step, y, z + step);
				glVertex3f(x + step, y + step, z + step);
				glVertex3f(x, y + step, z + step);

				glEnd();
				if (flag) {
					glColor3f(0, 0, 0);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					flag = false;
				}


			}
		}
	}

}

void COpenGLControl::DrawCube(float size, int resolution)
{
	float step = size / resolution;
	float sizef = size + 1.0 * resolution;

	glPushMatrix();
	//glTranslatef(-sizef/3,sizef/3, sizef/3);
	//upforward
	COpenGLControl::DrawPlane(size + 1.0 * resolution, step);

	////leftforward
	//glPushMatrix();
	//glRotated(90.0f, 0.0, 0.0, 1.0);
	//glScalef(1.0, -1.0, 1.0);
	//COpenGLControl::DrawPlane(size + 1.0 * resolution, step);
	//glPopMatrix();

	////front
	//glPushMatrix();
	//glRotated(90.0f, -1.0, 0.0, 0.0);
	//glScalef(1.0, -1.0, 1.0);
	//COpenGLControl::DrawPlane(size + 1.0 * resolution, step);
	//glPopMatrix();

	glPopMatrix();
}


void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX = (float)point.x;
	m_fLastY = (float)point.y;

	if (nFlags & MK_LBUTTON)
	{
		m_fRotX += (float)0.5f * diffY;

		if ((m_fRotX > 360.f) || (m_fRotX < -360.f))
		{
			m_fRotX = 0.0f;
		}

		m_fRotY += (float)0.5f * diffX;

		if ((m_fRotY > 360.f) || (m_fRotY < -360.f))
		{
			m_fRotY = 0.0f;
		}
		//m_fRotX += 10.0f;
		OnDraw(NULL);
	}
	else if (nFlags & MK_MBUTTON)
	{
		m_fPosX -= (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
		OnDraw(NULL);
	}

	

	CWnd::OnMouseMove(nFlags, point);
}


void COpenGLControl::CallRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw OpenGL scene
	Render();

	//Swap buffers
	SwapBuffers(hdc);
}