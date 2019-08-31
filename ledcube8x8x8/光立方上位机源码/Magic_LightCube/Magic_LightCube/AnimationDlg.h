#pragma once
#include "afxwin.h"
#include "SaveNameDlg.h"
#include "afxcmn.h"

#define MAX_Array 1024
#define Array_size 64

// CAnimationDlg �Ի���

class CAnimationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnimationDlg)

public:
	CAnimationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAnimationDlg();


	// �Ի�������
	enum { IDD = IDD_ANIMATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//����
	CSaveNameDlg m_saveNameDlg;
	CListBox m_listStatic;
	CListBox m_listAnimation;
	CButton m_buttonSave1;
	CButton m_checkKeep;
	CSliderCtrl m_sliderSpeed;
	CButton m_buttonDelete1;
	CButton m_buttonUpdate1;

	CWnd* pWnd1 ;                   //���ڻ�ȡ����ָ��
	byte array_animation[64];       //����
	int flag_list_animation;		//list��
	int speed;						//�ٶȵ���
	CString checkStr;				//play����ֵ
	int m_Radio1;					//ѡ��ִ��˳��

	int A[20][10];                     //��������
	int Custom_C;                      //�Զ��嶯������
	int ListStatic,listStatic_max,listStatic_min;
	int Animation_s[1024];             //���ڴ��涯������

	CString write_buffer[64];
	CString writeBuf;
	char readBuf[12900];
	BYTE readBuff[1024][64];

public:
	//ϵͳ��Ӧ����
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

	//�Զ��庯��
	void InitAnimationDlg();					//��ʼ������
	BYTE ConvertHexChar(BYTE ch);               //asciiתʮ������
	CString GetExePath();                       //�õ�������·��

	void Custom(int flag);					//�Զ��嶯��
	void Animation0();						//����0
	void Animation0_0(int y);
	void Animation0_1(int y);
	void Animation1();						//����1
	void Animation1_0(int y);
	void Animation1_1(int y);
	void Animation2();						//����2
	void Animation2_0(int y);
	void Animation2_1(int y);
	void Animation3();						//����3
	void Animation4();						//����4
	void Animation5();						//����5
	void Animation6();						//����6
	void Animation7(int empty, int kind);   //����7
	void Animation7_0(byte *a,int n);
	void Animation7_1(byte *a,int n);
	void Animation8(int isUp);              //����8
	void Animation9();                      //����9
	void Animation9_0(int y);
	void Animation9_1(int y);
	void Animation9_2(int y);
	void Animation10(int kind,int cw);      //����10
	void Animation11();					    //����11
	void Animation12(int cw);               //����12
	void Animation13();                     //����13
	void Animation14(int x,int y);          //����14
	void Animation15(int y);                
	void Animation16(int y);
	void Animation17(int y);
	void Animation18(int y);
	void Animation19(int y);
	void AnimationMove(byte *a,int kind,int direction,int length);
	void SendToParent();                    //������������
	
};
