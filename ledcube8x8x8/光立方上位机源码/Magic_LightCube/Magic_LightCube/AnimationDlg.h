#pragma once
#include "afxwin.h"
#include "SaveNameDlg.h"
#include "afxcmn.h"

#define MAX_Array 1024
#define Array_size 64

// CAnimationDlg 对话框

class CAnimationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnimationDlg)

public:
	CAnimationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAnimationDlg();


	// 对话框数据
	enum { IDD = IDD_ANIMATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//变量
	CSaveNameDlg m_saveNameDlg;
	CListBox m_listStatic;
	CListBox m_listAnimation;
	CButton m_buttonSave1;
	CButton m_checkKeep;
	CSliderCtrl m_sliderSpeed;
	CButton m_buttonDelete1;
	CButton m_buttonUpdate1;

	CWnd* pWnd1 ;                   //用于获取窗口指针
	byte array_animation[64];       //数组
	int flag_list_animation;		//list号
	int speed;						//速度调节
	CString checkStr;				//play按键值
	int m_Radio1;					//选择执行顺序

	int A[20][10];                     //动画计数
	int Custom_C;                      //自定义动画计数
	int ListStatic,listStatic_max,listStatic_min;
	int Animation_s[1024];             //用于储存动画步数

	CString write_buffer[64];
	CString writeBuf;
	char readBuf[12900];
	BYTE readBuff[1024][64];

public:
	//系统响应函数
	afx_msg void OnLbnSelchangeListStatic();
	afx_msg void OnLbnDblclkListAnimation();
	afx_msg void OnBnClickedButtonSave1();
	afx_msg void OnBnClickedButtonSave2();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCheckKeep();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnLbnSelchangeListAnimation();
	afx_msg void OnBnClickedButtonDelete1();
	afx_msg void OnBnClickedButtonDelete2();
	afx_msg void OnBnClickedButtonUpdate1();
	afx_msg void OnBnClickedButtonOpen();
	LRESULT MessageFromParent(WPARAM wParam, LPARAM lParam);
	LRESULT MessageTurn(WPARAM wParam, LPARAM lParam);

	//自定义函数
	void InitAnimationDlg();					//初始化函数
	BYTE ConvertHexChar(BYTE ch);               //ascii转十六进制
	CString GetExePath();                       //得到程序本身路径

	void Custom(int flag);					//自定义动画
	void Animation0();						//动画0
	void Animation0_0(int y);
	void Animation0_1(int y);
	void Animation1();						//动画1
	void Animation1_0(int y);
	void Animation1_1(int y);
	void Animation2();						//动画2
	void Animation2_0(int y);
	void Animation2_1(int y);
	void Animation3();						//动画3
	void Animation4();						//动画4
	void Animation5();						//动画5
	void Animation6();						//动画6
	void Animation7(int empty, int kind);   //动画7
	void Animation7_0(byte *a,int n);
	void Animation7_1(byte *a,int n);
	void Animation8(int isUp);              //动画8
	void Animation9();                      //动画9
	void Animation9_0(int y);
	void Animation9_1(int y);
	void Animation9_2(int y);
	void Animation10(int kind,int cw);      //动画10
	void Animation11();					    //动画11
	void Animation12(int cw);               //动画12
	void Animation13();                     //动画13
	void Animation14(int x,int y);          //动画14
	void Animation15(int y);                
	void Animation16(int y);
	void Animation17(int y);
	void Animation18(int y);
	void Animation19(int y);
	void AnimationMove(byte *a,int kind,int direction,int length);
	void SendToParent();                    //发送至父窗口
	
};
