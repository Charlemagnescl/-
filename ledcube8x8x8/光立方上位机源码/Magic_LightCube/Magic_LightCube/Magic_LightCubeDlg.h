
// Magic_LightCubeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"
#include "afxcmn.h"
#include "AnimationDlg.h"
#include "MusicDlg.h"
#include "COpenGLControl.h"


#define Size_dot 14                               //ÿ����ߴ�
#define Coordinate_x1 25                          //���󱳾���ʼ���� x��
#define Coordinate_y1 25                          //���󱳾���ʼ���� y��
#define Coordinate_x2 (Size_dot*73+Coordinate_x1) //���󱳾��������� x��
#define Coordinate_y2 (Size_dot*28+Coordinate_y1) //���󱳾��������� y��
#define Dot_add  Size_dot*9                       //ÿ����� �����

/**************
//��������
*Plies - ���� 8�� 8*8����  
*View  - ���� 3���ӽ�  0 - ǰ��ͼ��1 - ����ͼ��2 - ����ͼ
*Axis_X  - ����x��
*Axis_Y  - ����y��
**************/



// CMagic_LightCubeDlg �Ի���
class CMagic_LightCubeDlg : public CDialogEx
{
// ����
public:
	CMagic_LightCubeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Magic_LightCube_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	COpenGLControl m_oglWindow;

// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
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
//��������
*Plies 8 - ���� 8�� 8*8����  
*View  3 - ���� 3���ӽ�  0 - ǰ��ͼ��1 - ����ͼ��2 - ����ͼ
*Axis_X  8 - ����x��
*Axis_Y  8 - ����y��
**************/
	CRect rc_array_dot[Plies][View][Axis_X][Axis_Y];
	
	int ptxy[4];			// �����������λ�÷���ֵ
	byte hex_array[64];     // byte����   �������ݷ���
	CString str_array[64];  // �ַ������� �༭����ʾ
	CByteArray Array;       // 8λ�޷���byte 
	BOOL Flag_send ;        // �������ӱ�־

	CMscomm1 m_mscom;
	CComboBox m_combCom;
	CComboBox m_combBaud;
	CString m_editArray;
	CEdit m_edit;
	CButton m_Send;
	CTabCtrl m_tab;
	CAnimationDlg m_animationDlg;
	CMusicDlg m_musicDlg;

public:	//����
	//�Զ��庯��
	void InitArray();						    //��ʼ������
	void EditInit();							//��ʼ���༭������
	void ChildWindowInit();						//tab �ؼ���ʼ��
	void DrawAllDot();                          //������
	void DrawBackground();                      //������
	void PtInArea(const CPoint pt);             //�ж�����Ƿ��ڵ��������ڣ�����Ӧ
	void ViewArray();                           //�༭����ʾ���飨2���ƣ�
	void ViewTheArray(byte hexArray[]);         //�༭����ʾ���飨16���ƣ�
	void SendData();                            //�������ݺ���
	void DotShift(UINT plies,UINT view,UINT axis_x,UINT axis_y); //3���ӽ�ת������
	BOOL Hex2Bin(byte a[]);                     //ʮ������ת�����ƺ���
	void updateInterface(byte* x);              //���½��溯��
	void cleanInterface();                      //������溯��

	//ϵͳ��Ӧ����
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);      //������������Ӧ����δʹ�ã�
	afx_msg void OnBnClickedButtonAllon();					  //ȫ����������
	afx_msg void OnBnClickedButtonAlloff();                   //ȫ��Ϩ�𰴼�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);      //����ƶ���Ӧ����δʹ�ã�
	afx_msg void OnBnClickedButtonConnect();                  //�������Ӱ���
	afx_msg void OnBnClickedButtonSend();                     //�������ݰ���
	afx_msg void OnBnClickedButtonTest();                     //���԰���
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);      //tabѡ��ı���Ӧ
	afx_msg LRESULT OnAnimationMessage(WPARAM wParam, LPARAM lParam);      //�Ӵ���Animation��Ϣ��Ӧ
	afx_msg void OnClose();                                   //ǿ���˳�

	//���ں���
	void OnCommMscomm1();
	void Setting();

	DECLARE_EVENTSINK_MAP()

};
