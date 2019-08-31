
// Magic_LightCubeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"
#include "afxcmn.h"
#include "AnimationDlg.h"
#include "MusicDlg.h"
#include "COpenGLControl.h"


#define Size_dot 14                               //每个点尺寸
#define Coordinate_x1 25                          //点阵背景开始坐标 x轴
#define Coordinate_y1 25                          //点阵背景开始坐标 y轴
#define Coordinate_x2 (Size_dot*73+Coordinate_x1) //点阵背景结束坐标 x轴
#define Coordinate_y2 (Size_dot*28+Coordinate_y1) //点阵背景结束坐标 y轴
#define Dot_add  Size_dot*9                       //每层点阵 坐标差

/**************
//点阵数组
*Plies - 横向 8层 8*8点阵  
*View  - 纵向 3个视角  0 - 前视图、1 - 左视图、2 - 俯视图
*Axis_X  - 点阵x轴
*Axis_Y  - 点阵y轴
**************/



// CMagic_LightCubeDlg 对话框
class CMagic_LightCubeDlg : public CDialogEx
{
// 构造
public:
	CMagic_LightCubeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Magic_LightCube_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	COpenGLControl m_oglWindow;

// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:
	#define Plies 8
	#define View 3
	#define Axis_X 8
	#define Axis_Y 8
	
/**************
//点阵数组
*Plies 8 - 横向 8层 8*8点阵  
*View  3 - 纵向 3个视角  0 - 前视图、1 - 左视图、2 - 俯视图
*Axis_X  8 - 点阵x轴
*Axis_Y  8 - 点阵y轴
**************/
	CRect rc_array_dot[Plies][View][Axis_X][Axis_Y];
	
	int ptxy[4];			// 保存鼠标所在位置返回值
	byte hex_array[64];     // byte数组   数组数据发送
	CString str_array[64];  // 字符型数组 编辑框显示
	CByteArray Array;       // 8位无符号byte 
	BOOL Flag_send ;        // 串口连接标志

	CMscomm1 m_mscom;
	CComboBox m_combCom;
	CComboBox m_combBaud;
	CString m_editArray;
	CEdit m_edit;
	CButton m_Send;
	CTabCtrl m_tab;
	CAnimationDlg m_animationDlg;
	CMusicDlg m_musicDlg;

public:	//函数
	//自定义函数
	void InitArray();						    //初始化数组
	void EditInit();							//初始化编辑框字体
	void ChildWindowInit();						//tab 控件初始化
	void DrawAllDot();                          //画点阵
	void DrawBackground();                      //画背景
	void PtInArea(const CPoint pt);             //判断鼠标是否在点阵区域内，并响应
	void ViewArray();                           //编辑框显示数组（2进制）
	void ViewTheArray(byte hexArray[]);         //编辑框显示数组（16进制）
	void SendData();                            //发送数据函数
	void DotShift(UINT plies,UINT view,UINT axis_x,UINT axis_y); //3个视角转换函数
	BOOL Hex2Bin(byte a[]);                     //十六进制转二进制函数
	void updateInterface(byte* x);              //更新界面函数
	void cleanInterface();                      //清除界面函数

	//系统响应函数
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);      //鼠标左键弹起响应（暂未使用）
	afx_msg void OnBnClickedButtonAllon();					  //全部点亮按键
	afx_msg void OnBnClickedButtonAlloff();                   //全部熄灭按键
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);      //鼠标移动响应（暂未使用）
	afx_msg void OnBnClickedButtonConnect();                  //串口连接按键
	afx_msg void OnBnClickedButtonSend();                     //发送数据按键
	afx_msg void OnBnClickedButtonTest();                     //测试按键
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);      //tab选项卡改变响应
	afx_msg LRESULT OnAnimationMessage(WPARAM wParam, LPARAM lParam);      //子窗口Animation消息响应
	afx_msg void OnClose();                                   //强制退出

	//串口函数
	void OnCommMscomm1();
	void Setting();

	DECLARE_EVENTSINK_MAP()

};
