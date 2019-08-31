// AnimationDlg.cpp : ʵ���ļ�
//
#include <stdlib.h>
#include "stdafx.h"
#include "Magic_LightCube.h"
#include "AnimationDlg.h"
#include "afxdialogex.h"

//CFile file_animation;
CStdioFile file_animation;
CRect rect_animation;  // ��ɫ�������� 

BYTE StepAnimation[MAX_Array][64];      //�������� ���ھ�̬list��ʾ
BYTE Animation[MAX_Array][MAX_Array][64];	   //���������ڶ���list��ʾ

byte tab_rain[]=
{//rain(s8 menu,s8 num,s8 v);
	0X00,0X84,0X01,0X00,0X00,0X01,0X02,0X44,
	0X84,0X00,0X24,0X08,0X04,0X20,0X80,0X00,
	0X00,0X20,0X00,0X00,0X20,0X00,0X40,0X00,
	0X00,0X04,0X00,0X40,0X00,0X00,0X08,0X00,
	
	0X40,0X00,0X10,0X00,0X00,0X04,0X04,0X11,
	0X00,0X41,0X00,0X00,0X80,0X00,0X40,0X00,
	0X00,0X00,0X00,0X24,0X01,0X18,0X00,0X00,
	0X22,0X10,0X02,0X00,0X40,0X00,0X02,0X00
};

const u8 tab_xuanzhuantiao[]=
{ //��ת��
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//0
	0x00,0x01,0x06,0x08,0x10,0x60,0x80,0x00,
	0x00,0x00,0x01,0x0e,0x70,0x80,0x00,0x00,
	0x00,0x00,0x00,0x0f,0xf0,0x00,0x00,0x00,
	0x00,0x00,0x00,0xf0,0x0f,0x00,0x00,0x00,
	0x00,0x00,0x80,0x70,0x0e,0x01,0x00,0x00,
	0x00,0x80,0x60,0x10,0x08,0x06,0x01,0x00,
	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
	0x40,0x20,0x20,0x10,0x08,0x04,0x04,0x02,
	0x20,0x10,0x10,0x10,0x08,0x08,0x08,0x04,
	0x10,0x10,0x10,0x10,0x08,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x10,0x10,0x10,0x10,
	0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x20,
	0x02,0x04,0x04,0x08,0x10,0x20,0x20,0x40//13
};

int tab00[]={ //��������
	0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,6,5,4,3,2,1,//28
	1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+2,1*8+3,1*8+4,1*8+5,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+5,1*8+4,1*8+3,1*8+2,//20
	2*8+2,2*8+2,2*8+2,2*8+2,2*8+3,2*8+4,2*8+5,2*8+5,2*8+5,2*8+5,2*8+4,2*8+3,//12
	3*8+3,3*8+3,3*8+4,3*8+4,//4+4
	4*8+3,4*8+3,4*8+4,4*8+4,
	5*8+2,5*8+2,5*8+2,5*8+2,5*8+3,5*8+4,5*8+5,5*8+5,5*8+5,5*8+5,5*8+4,5*8+3,//12
	6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+2,6*8+3,6*8+4,6*8+5,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+5,6*8+4,6*8+3,6*8+2,//20
	56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+1,56+2,56+3,56+4,56+5,56+6,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+6,56+5,56+4,56+3,56+2,56+1,//28
};
int tab10[]={//��������
	56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+1,56+2,56+3,56+4,56+5,56+6,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+6,56+5,56+4,56+3,56+2,56+1,//28
	6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+2,6*8+3,6*8+4,6*8+5,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+5,6*8+4,6*8+3,6*8+2,//20
	5*8+2,5*8+2,5*8+2,5*8+2,5*8+3,5*8+4,5*8+5,5*8+5,5*8+5,5*8+5,5*8+4,5*8+3,//12
	4*8+3,4*8+3,4*8+4,4*8+4,
	3*8+3,3*8+3,3*8+4,3*8+4,//4+4
	2*8+2,2*8+2,2*8+2,2*8+2,2*8+3,2*8+4,2*8+5,2*8+5,2*8+5,2*8+5,2*8+4,2*8+3,//12
	1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+2,1*8+3,1*8+4,1*8+5,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+5,1*8+4,1*8+3,1*8+2,//20
	0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,6,5,4,3,2,1,//28
};

int tab01[]={//�ƶ�����
	0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,6,5,4,3,2,1,0,0,0,0,0,0,0,//28
	1,2,3,4,5,6,6,6,6,6,6,5,4,3,2,1,1,1,1,1,//20
	2,3,4,5,5,5,5,4,3,2,2,2,//12
	3,4,4,3,//
	3,4,4,3,
	2,3,4,5,5,5,5,4,3,2,2,2,//12
	1,2,3,4,5,6,6,6,6,6,6,5,4,3,2,1,1,1,1,1,//20
	0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,6,5,4,3,2,1,0,0,0,0,0,0,0,//28
};

const u16 tab_water[]=
{
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0140,0x0080,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0140,0x0220,0x0140,0x0080,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x01c0,0x0220,0x0410,0x0410,0x0410,0x0220,0x01c0,0x0000,0x0000,0x0000,0x0000,0x0000,			 
0x0000,0x0000,0x0000,0x03e0,0x0410,0x0808,0x0808,0x0808,0x0808,0x0808,0x0410,0x03e0,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x07f0,0x0808,0x1004,0x1004,0x1004,0x1004,0x1004,0x1004,0x1004,0x0808,0x07f0,0x0000,0x0000,0x0000,
0x0000,0x0ff8,0x1004,0x2002,0x2002,0x2002,0x2002,0x2002,0x2002,0x2002,0x2002,0x2002,0x1004,0x0ff8,0x0000,0x0000,
0x1ffc,0x2002,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x2002,0x1ffc,0x0000
};

// CAnimationDlg �Ի���

IMPLEMENT_DYNAMIC(CAnimationDlg, CDialogEx)

CAnimationDlg::CAnimationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnimationDlg::IDD, pParent)
{
	memset(array_animation,0x00,64);
	m_Radio1 = 0;
}

CAnimationDlg::~CAnimationDlg()
{
}

void CAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATIC, m_listStatic);
	DDX_Control(pDX, IDC_BUTTON_SAVE1, m_buttonSave1);
	DDX_Control(pDX, IDC_LIST_ANIMATION, m_listAnimation);
	DDX_Control(pDX, IDC_CHECK_KEEP, m_checkKeep);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_sliderSpeed);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio1);
	DDX_Control(pDX, IDC_BUTTON_DELETE1, m_buttonDelete1);
	DDX_Control(pDX, IDC_BUTTON_UPDATE1, m_buttonUpdate1);
}


BEGIN_MESSAGE_MAP(CAnimationDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_STATIC, &CAnimationDlg::OnLbnSelchangeListStatic)
	ON_BN_CLICKED(IDC_BUTTON_SAVE1, &CAnimationDlg::OnBnClickedButtonSave1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SAVE2, &CAnimationDlg::OnBnClickedButtonSave2)
	ON_LBN_DBLCLK(IDC_LIST_ANIMATION, &CAnimationDlg::OnLbnDblclkListAnimation)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CAnimationDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK_KEEP, &CAnimationDlg::OnBnClickedCheckKeep)
	ON_WM_TIMER()
	ON_MESSAGE(WM_TEST_MESSAGE, &CAnimationDlg::MessageFromParent)
	ON_MESSAGE(WM_TURN_MESSAGE, &CAnimationDlg::MessageTurn)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO1, &CAnimationDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAnimationDlg::OnBnClickedRadio2)
	ON_LBN_SELCHANGE(IDC_LIST_ANIMATION, &CAnimationDlg::OnLbnSelchangeListAnimation)
	ON_BN_CLICKED(IDC_BUTTON_DELETE1, &CAnimationDlg::OnBnClickedButtonDelete1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE2, &CAnimationDlg::OnBnClickedButtonDelete2)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE1, &CAnimationDlg::OnBnClickedButtonUpdate1)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CAnimationDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CAnimationDlg ��Ϣ�������

/*
void CAnimationDlg::DelaySecond(int second){
	COleDateTime start_time= COleDateTime::GetCurrentTime();
	COleDateTimeSpan end_time= COleDateTime::GetCurrentTime()-start_time;
	while(end_time.GetTotalSeconds()< second) //ʵ����ʱ2��
	{ 
		MSG msg;
		GetMessage(&msg,NULL,0,0);
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
		end_time = COleDateTime::GetCurrentTime()-start_time;
	}
}
*/
/*
void CAnimationDlg::DelayMicrosecond(int microsecond){
	
	DWORD dwStart = GetTickCount();
	DWORD dwEnd = dwStart;
	do
	{
		MSG msg;
		GetMessage(&msg,NULL,0,0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		dwEnd = GetTickCount()-dwStart;
	}while(dwEnd < microsecond);
}
*/

void CAnimationDlg::InitAnimationDlg(){

	m_listAnimation.AddString(L"����0");
	m_listAnimation.AddString(L"����1");
	m_listAnimation.AddString(L"����2");
	m_listAnimation.AddString(L"����3");
	m_listAnimation.AddString(L"����4");
	m_listAnimation.AddString(L"����5");
	m_listAnimation.AddString(L"����6");
	m_listAnimation.AddString(L"����7");
	m_listAnimation.AddString(L"����8");
	m_listAnimation.AddString(L"����9");
	m_listAnimation.AddString(L"����10");
	m_listAnimation.AddString(L"����11");
	m_listAnimation.AddString(L"����12");
	m_listAnimation.AddString(L"����13");
	m_listAnimation.AddString(L"����14");
	/*m_listAnimation.AddString(L"����15");
	m_listAnimation.AddString(L"����16");
	m_listAnimation.AddString(L"����17");
	m_listAnimation.AddString(L"����18");
	m_listAnimation.AddString(L"����19");
	m_listAnimation.AddString(L"����20");
	m_listAnimation.AddString(L"����21");
	*/
	m_sliderSpeed.SetRange(50, 600); 
	m_sliderSpeed.SetTicFreq(50);
	m_sliderSpeed.SetPos(200);
	speed = m_sliderSpeed.GetPos();
	m_Radio1 = 0;
	Custom_C = 0;  //�Զ��嶯������
	
}

void CAnimationDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio1 = 0;
}

void CAnimationDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio1 = 1;
	/*
	CString c;
	c.Format(L"%d",m_listAnimation.GetCount());
	AfxMessageBox(c);
	*/
}

//���ո�������Ϣ
LRESULT CAnimationDlg::MessageFromParent(WPARAM wParam, LPARAM lParam){
	// TODO: �����û��Զ�����Ϣ
	switch(lParam){
	case -1:  //change tab �л�ѡ���
		GetDlgItemText(IDC_CHECK_KEEP,checkStr);
		if(checkStr == L"Pause"){
			m_checkKeep.SetWindowText(L"Play");
			m_checkKeep.SetCheck(BST_UNCHECKED);
			KillTimer(flag_list_animation);
		}
		break;
	case 0:
		memcpy(StepAnimation[ListStatic],(byte *)wParam,64);
		break;
	}
	return 0;
}

/*
	List Static ��غ���
	ѡ����Ӧ���������桢���¡�ɾ����̬���溯��
	ѡ����Ӧ -- sel change -- OnLbnSelchangeListStatic
	����  --  save1    -- OnBnClickedButtonSave1
	����  --  update1  -- OnBnClickedButtonUpdate1
	ɾ��  --  delete1  -- OnBnClickedButtonDelete1
*/
//list static �� ѡ����Ӧ
void CAnimationDlg::OnLbnSelchangeListStatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pWnd1 = GetParent()->GetParent();	

	CString list_name;   
    int nCurSel;    
	m_listStatic.GetText(m_listStatic.GetCurSel(),list_name);
	nCurSel = _tstoi(list_name);                              //CStringת int
	if(m_listStatic.GetSelCount() == 1){  //  ѡ��ĳ һ�� ʱ ��ʾ�������� ������ʾ
		GetDlgItemText(IDC_CHECK_KEEP,checkStr);
		if(checkStr == L"Play"){      //����������ͣ��ֹͣʱ��liststatic �б���Ч
			::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE
				,(WPARAM)(&StepAnimation[nCurSel]),-3);
		}
	}
}
//list static ���澲̬����
void CAnimationDlg::OnBnClickedButtonSave1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString list ;
	ListStatic = m_listStatic.GetCount();
	list.Format(L"%d",ListStatic);
	//AfxMessageBox(list);
	m_listStatic.AddString(list);       //�����б���Ŀ

	pWnd1 = GetParent()->GetParent();	
	::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,NULL,-2);
	/*
	INT_PTR nRes;
	nRes = m_saveNameDlg.DoModal();
	if (IDCANCEL == nRes){   
		//���ȡ��
		m_saveNameDlg.ClearSaveName();   //���save name�༭��
		return ;
	}else{
		//���ȷ��
		UpdateData(TRUE);
		m_listStatic.AddString(m_saveNameDlg.GetSaveName());
		m_listStatic.SetCurSel(0);
		UpdateData(false);
		m_saveNameDlg.ClearSaveName();   //���save name�༭��
	}
	*/
}
//list static ���¾�̬����
void CAnimationDlg::OnBnClickedButtonUpdate1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString list_update;
	if(m_listStatic.GetSelCount() == 1){			//ѡ��һ����Ŀ
		ListStatic = m_listStatic.GetCurSel();		//�õ�ѡ����Ŀ��
		m_listStatic.GetText(m_listStatic.GetCurSel(),list_update);
		m_listStatic.InsertString(m_listStatic.GetCurSel(),list_update);
		//֪ͨ������ �����������
		pWnd1 = GetParent()->GetParent();	
		::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,NULL,-2);
		//ɾ���ϵ���
		m_listStatic.DeleteString(m_listStatic.GetCurSel()+1);
	}
}
//list static ɾ����̬����
void CAnimationDlg::OnBnClickedButtonDelete1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString list;
	if(m_listStatic.GetSelCount() == 0){
		;  //δѡ��list��Ŀ����ִ�ж���
	}else if(m_listStatic.GetSelCount() == 1){  //ѡ��һ����Ŀ����ɾ��ѡ��
		//list1.Format(L"%d",m_listStatic.GetCurSel());
		//AfxMessageBox(list1);
		if((m_listStatic.GetCurSel()+1) == m_listStatic.GetCount()){ //ѡ�������һ��
			m_listStatic.DeleteString(m_listStatic.GetCurSel());  //ɾ��ѡ����
		}else{  
			for(int i = m_listStatic.GetCurSel()+1;i<m_listStatic.GetCount();i++){
				list.Format(L"%d",i-1);					//�õ���ǰ����
				m_listStatic.DeleteString(i);			//ɾ����һ��
				m_listStatic.InsertString(i,list);     //������һ�У�����Ϊ��һ�е�����
				memcpy(StepAnimation[i-1] ,StepAnimation[i],64);
			}
			m_listStatic.DeleteString(m_listStatic.GetCurSel());  //ɾ��ѡ����
		}
	}
	//ѡ�ж����Ŀ��������ȫ��
	else if(m_listStatic.GetSelCount() > 1 && m_listStatic.GetSelCount() < m_listStatic.GetCount()){
		if((m_listStatic.GetCurSel()+1) == m_listStatic.GetCount()){ //ѡ�����а������һ��
			listStatic_max = (m_listStatic.GetSelCount()+ abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1)-1);
			listStatic_min = abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1);
			for(int i = listStatic_max;i>=listStatic_min;i--){
				m_listStatic.DeleteString(i);    //�Ӵ���Сɾ��
			}
		}else{
			for(int i = m_listStatic.GetCurSel()+1;i<m_listStatic.GetCount();i++){
				list.Format(L"%d",i-m_listStatic.GetSelCount());			//�õ�ѡ��������С����
				m_listStatic.DeleteString(i);							//ɾ����һ��
				m_listStatic.InsertString(i,list);						//������һ�У�����Ϊ��С����
				memcpy(StepAnimation[i-m_listStatic.GetSelCount()] ,StepAnimation[i],64);
			}
			listStatic_max = (m_listStatic.GetSelCount()+ abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1)-1);
			listStatic_min = abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1);
			for(int i = listStatic_max;i>=listStatic_min;i--){
				m_listStatic.DeleteString(i);    //�Ӵ���Сɾ��
			}
		}
	}
	//ѡ��ȫ����
	else if(m_listStatic.GetSelCount() == m_listStatic.GetCount()){
		m_listStatic.ResetContent();  // ѡ������list��Ŀ�������list
	}
}

/*
	List Animation ��غ���
	ѡ����Ӧ���������桢ɾ����������
	ѡ����Ӧ -- sel change -- OnLbnSelchangeListAnimation
	����  --  save2    -- OnBnClickedButtonSave2
	ɾ��  --  delete2  -- OnBnClickedButtonDelete2
*/
//list animation ���涯��
void CAnimationDlg::OnBnClickedButtonSave2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Pause"){
		m_checkKeep.SetWindowText(L"Play");
		m_checkKeep.SetCheck(BST_UNCHECKED);
		KillTimer(flag_list_animation);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}

	INT_PTR nRes;
	if(m_listStatic.GetSelCount()>1){    //�ж�ѡ�ж���������1
		//��������ļ���·��
		CString AnimationPath = GetExePath()+L"\\"+L"YFRobot Magic-LightCube"+L"\\";
		if(!PathIsDirectory(AnimationPath)){   //�ж��ļ����Ƿ����
			if(!CreateDirectory(AnimationPath, NULL)){
				AfxMessageBox(L"Folder to create a failure!");
				return ;
			}
		}
		nRes = m_saveNameDlg.DoModal();		//�����Ի���
		if (IDCANCEL == nRes){   
			//���ȡ��
			m_saveNameDlg.ClearSaveName();   //���save name�༭��
			return ;
		}else{
			//���ȷ��
			if(m_saveNameDlg.GetSaveName() == ""){
				AfxMessageBox(L"The name cannot be empty!");
			}else if(m_listAnimation.SelectString(-1,m_saveNameDlg.GetSaveName()) != LB_ERR){
				AfxMessageBox(L"The name cannot be repeated!");
			}else{
				UpdateData(TRUE); 
				writeBuf = "";
				file_animation.Open(AnimationPath+m_saveNameDlg.GetSaveName()+L".txt",
					CFile::modeCreate | CFile::modeReadWrite);
				int listmin = abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1);
				for(int j=listmin;j<=m_listStatic.GetCurSel();j++){
					for(int i=0;i<64;i++){
						write_buffer[i].Format(L"%02x", StepAnimation[j][i]);
						writeBuf += write_buffer[i];
					}
					memcpy(Animation[m_listAnimation.GetCount()][j-listmin],StepAnimation[j],64);//�����鱣����ִ�ж�������
					writeBuf += " ";
				}
				Animation_s[m_listAnimation.GetCount()] = m_listStatic.GetSelCount();  //���涯������
				file_animation.Write(writeBuf,writeBuf.GetLength()*2);

				file_animation.Close();

				m_listAnimation.AddString(m_saveNameDlg.GetSaveName());
				m_listAnimation.SetCurSel(m_listAnimation.GetCount()-1);
				UpdateData(false);

				m_saveNameDlg.ClearSaveName();   //���save name�༭��
			}
		}
	}else{
		AfxMessageBox(L"The option for at least two items!");
	}
}

// �õ���������λ��
CString CAnimationDlg::GetExePath(){
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);//�õ�����ģ�����ƣ�ȫ·��
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\'); 
    path = path.Left(pos); 

	//�õ�����·��
	//TCHAR exeFullPath[MAX_PATH];			// MAX_PATH
	//GetCurrentDirectory(MAX_PATH,exeFullPath);
	//AfxMessageBox(exeFullPath);

	//AfxMessageBox(path);
	return path;
}

//list animation ɾ������
void CAnimationDlg::OnBnClickedButtonDelete2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetExePath();
	flag_list_animation = m_listAnimation.GetCurSel();
	if(flag_list_animation == -1){

	}else if(flag_list_animation < 15){
		AfxMessageBox(L"Fixed animation group, please do not delete��");
	}else{
		KillTimer(flag_list_animation);
		GetDlgItemText(IDC_CHECK_KEEP,checkStr);
		if(checkStr == L"Pause"){
			m_checkKeep.SetWindowText(L"Play");
			m_checkKeep.SetCheck(BST_UNCHECKED);

			m_buttonSave1.EnableWindow(true);
			m_buttonUpdate1.EnableWindow(true);
		}	
		//���������˳�����ݱ任
		for(int j = m_listAnimation.GetCurSel();j<m_listAnimation.GetCount();j++){
			for(int i = 0;i<Animation_s[m_listAnimation.GetCurSel()+1];i++){
				//����һ���Ķ����鸴�Ƹ���ǰ������
				memcpy(Animation[j][i],Animation[j+1][i],64);
			}
		}
		m_listAnimation.DeleteString(m_listAnimation.GetCurSel());  //ɾ��ѡ����
		m_listAnimation.SetCurSel(flag_list_animation-1);

		pWnd1 = GetParent()->GetParent();	
		::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,
			NULL,-1);            //������Ϣ�������ڣ�֪ͨ�������
	}
}

//�򿪶���
void CAnimationDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Pause"){
		m_checkKeep.SetWindowText(L"Play");
		m_checkKeep.SetCheck(BST_UNCHECKED);
		KillTimer(flag_list_animation);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}

	TCHAR szFileFilter[]=L"txt�ļ�(*.txt)|*.txt|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT
		|OFN_NOCHANGEDIR,szFileFilter,NULL);
	if(dlg.DoModal()==IDOK){
		CString strFilePath = dlg.GetPathName();	 //�����ļ�·��
		CString strFileName = dlg.GetFileName();       //�����ļ���
		CString strFileTitle = dlg.GetFileTitle();   //�����ļ�����
		if(file_animation.Open(strFilePath, CFile::modeRead | CFile::typeBinary)){
			file_animation.SeekToBegin(); 
			LONGLONG FileLen = (LONGLONG)file_animation.GetLength();
			//file_animation.Read(readBuf.GetBuffer(FileLen),FileLen*2);
			//memcpy(readBuf,readBuf,FileLen);
			file_animation.Read(readBuf,(UINT)FileLen); 

			CString head0,head1;
			head0.Format(L"%d",readBuf[0]);
			head1.Format(L"%d",readBuf[1]);
			if(head0 == "-1"&&head1 == "-2"){   //��� ͷ ff fe
				//AfxMessageBox(L"0������");
				int j = 0;
				for(int i = 2;i < FileLen;){
					if(readBuf[i] == ' '){			//�ж��Ƿ�һ֡�����������
						i+=2;
						j++;
					}
					ConvertHexChar(readBuf[i]);
					ConvertHexChar(readBuf[i+2]);
					readBuff[j][(i-2*(j+1))/4-j*64] =(ConvertHexChar(readBuf[i])<<4) 
						+ ConvertHexChar(readBuf[i+2]);
					i+=4;
				}
			}else{
				int j = 0;
				for(int i=0;i < FileLen;){
					if(readBuf[i] == ' '){			//�ж��Ƿ�һ֡�����������
						i+=2;
						j++;
					}
					ConvertHexChar(readBuf[i]);
					ConvertHexChar(readBuf[i+2]);
					readBuff[j][(i-j*2)/4-j*64] =(ConvertHexChar(readBuf[i])<<4)
						+ ConvertHexChar(readBuf[i+2]);
					i+=4;
				}
			}
			file_animation.Close();
			int step_nub = ((UINT)FileLen)/2/129;     //�����ܲ���
			for(int i = 0;i<step_nub;i++){
				memcpy(Animation[m_listAnimation.GetCount()][i],readBuff[i],64);//�����鱣����ִ�ж�������
			}
			Animation_s[m_listAnimation.GetCount()] = (UINT)FileLen/2/129;  //���涯������
			m_listAnimation.AddString(strFileTitle);
			m_listAnimation.SetCurSel(m_listAnimation.GetCount()-1);
		}else{
			AfxMessageBox(L"File Read Failure!!");
		}
	}
}

//��ASCII��ת��Ϊ16������
BYTE CAnimationDlg::ConvertHexChar(BYTE ch){
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;        
	else
		return -1;
}

void CAnimationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

    GetClientRect(rect_animation);
	dc.Rectangle(rect_animation);
	dc.FillSolidRect(rect_animation,RGB(255,255,255));
}

//����͸�� ����
HBRUSH CAnimationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID()==IDC_STATIC||pWnd->GetDlgCtrlID()==IDC_BUTTON_SAVE1
		 ||pWnd->GetDlgCtrlID()==IDC_BUTTON_SAVE2||pWnd->GetDlgCtrlID()==IDC_BUTTON_STOP
		 ||pWnd->GetDlgCtrlID()==IDC_CHECK_KEEP||pWnd->GetDlgCtrlID()==IDC_SLIDER_SPEED
		 ||pWnd->GetDlgCtrlID()==IDC_RADIO1||pWnd->GetDlgCtrlID()==IDC_RADIO2
		 ||pWnd->GetDlgCtrlID()==IDC_STATIC_EACH)//��Ŀؼ�ID
	{
		//pDC->SetTextColor(RGB(0,0,0));                 //����������ɫ
		pDC->SetBkMode(TRANSPARENT);					     //�������屳��Ϊ͸��
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);    // ���ñ���ɫ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//Speed ������Ӧ����
void CAnimationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Play"){
		speed = m_sliderSpeed.GetPos();
	}else if(checkStr == L"Pause"){
		speed = m_sliderSpeed.GetPos();
		SetTimer(flag_list_animation,speed,NULL);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//Play ������Ӧ����
void CAnimationDlg::OnBnClickedCheckKeep()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	BST_INDETERMINATE - �Իһ�������
	BST_UNCHECKED     - δѡ��
	BST_CHECKED       - ѡ��
	*/
	pWnd1 = GetParent()->GetParent();
	if(BST_CHECKED == m_checkKeep.GetCheck()){
		m_checkKeep.SetWindowText(L"Pause");
		flag_list_animation = m_listAnimation.GetCurSel();

		if(flag_list_animation==-1){
			for(int i = 0;i<sizeof(A)/sizeof(A[0]);i++){
				A[i][0] = 0;
			}
			flag_list_animation = 0 ;
			SetTimer(flag_list_animation,speed,NULL);
			m_listAnimation.SetCurSel(flag_list_animation);
		}else{
			SetTimer(flag_list_animation,speed,NULL);
		}
		m_buttonSave1.EnableWindow(false);
		m_buttonUpdate1.EnableWindow(false);

	}else{
		m_checkKeep.SetWindowText(L"Play");
		KillTimer(flag_list_animation);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}
}

//�ظ�����˳��
LRESULT CAnimationDlg::MessageTurn(WPARAM wParam, LPARAM lParam){
	// TODO: �����û��Զ�����Ϣ
	switch(lParam){
	case 0:
		//SetTimer(flag_list_animation,speed,NULL);
		break;
	case 1:
		KillTimer(flag_list_animation);
		memset(array_animation,0x00,64);
		flag_list_animation++;
		if(flag_list_animation == m_listAnimation.GetCount()){
			flag_list_animation = 0;
		}
		m_listAnimation.SetCurSel(flag_list_animation);

		SetTimer(flag_list_animation,speed,NULL);
		break;
	}
	return 0;
}

void CAnimationDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(flag_list_animation);
	flag_list_animation = -1;
	pWnd1 = GetParent()->GetParent();	
	::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,
		NULL,flag_list_animation);            //������Ϣ�������ڣ�֪ͨ�������
	
	//����ʼ����������A[][]
	for(int i = 0;i<sizeof(A)/sizeof(A[0]);i++){
		for(int j = 0;j<sizeof(A[0])/sizeof(A[0][0]);j++){
			A[i][j] = 0;
		}}
	//�ж�Play ��ť״̬
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Pause"){
		m_checkKeep.SetWindowText(L"Play");
		m_checkKeep.SetCheck(BST_UNCHECKED);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}
	m_listAnimation.SetCurSel(flag_list_animation);    //����listbox
	m_listStatic.SetSel(-1,0);
}

//���������� list animation�б� �¼�
void CAnimationDlg::OnLbnSelchangeListAnimation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(flag_list_animation);
	for(int i = 0;i<sizeof(A)/sizeof(A[0]);i++){
		A[i][0] = 0;
	}
	Custom_C = 0;
	A[9][0] = 7;A[10][1] = 13;A[12][2] = 0;

	pWnd1 = GetParent()->GetParent();							//�õ������ھ��
	flag_list_animation = m_listAnimation.GetCurSel();          //��ȡlist�б��  

	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == "Play"){
		m_checkKeep.SetWindowText(L"Pause");
		m_checkKeep.SetCheck(BST_CHECKED);
	}else if(checkStr == "Pause"){}

	memset(array_animation,0x00,64);
	if(!SetTimer(flag_list_animation,speed,NULL)){
			AfxMessageBox(L"Animation loading failure, please open it again!");
	}

	m_buttonSave1.EnableWindow(false);
	m_buttonUpdate1.EnableWindow(false);
}

// ������˫�� list animation�б� �¼�
void CAnimationDlg::OnLbnDblclkListAnimation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAnimationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent){
	case 0:
		Animation0();
		break;
	case 1:
		Animation1();
		break;
	case 2:
		Animation2();
		break;
	case 3:
		Animation3();
		break;
	case 4:
		Animation4();
		break;
	case 5:
		Animation5();
		break;
	case 6:
		Animation6();
		break;
	case 7:
		Animation7(0,0); 
		break;
	case 8:
		Animation8(0); //��0 Ϊ����
		break;
	case 9:
		Animation9();
		break;
	case 10:
		Animation10(0,1);
		break;
	case 11:
		Animation11();
		break;
	case 12:
		Animation12(1);
		break;
	case 13:
		Animation13();
		break;
	case 14:
		Animation14(4,4);
		break;
	default:
		//AfxMessageBox(L"");
		Custom(flag_list_animation);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//������Ϣ��������
void CAnimationDlg::SendToParent(){
	::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,
		(WPARAM)(&array_animation),flag_list_animation);
}

//�Զ��嶯��
void CAnimationDlg::Custom(int flag){
	if(Custom_C>= 0 && Custom_C < (Animation_s[flag])-1){	

		::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,(WPARAM)(&Animation[flag][Custom_C]),-3);
		Custom_C++;
	}else if(Custom_C == (Animation_s[flag])-1){
		::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,(WPARAM)(&Animation[flag][Custom_C]),-3);
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		Custom_C = 0;
	}
}

/* 
����Ч��0
*/
void CAnimationDlg::Animation0(){
	if(A[0][0] >= 0&& A[0][0]<8){
		Animation0_0(A[0][0]);
		SendToParent();
		A[0][0]++;
	}
	else if(A[0][0]==8){
		A[0][0]++;
		A[0][1] = 6;
		Animation0_1(A[0][1]);
		SendToParent();
		A[0][1]--;
	}
	else if(A[0][0] == 9 && A[0][1] > 0){
		Animation0_1(A[0][1]);
		SendToParent();
		A[0][1]--;
	}
	else if(A[0][0] == 9 && A[0][1]== 0){
		A[0][0] = 1;
		Animation0_1(A[0][1]);
		SendToParent();
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);  //����������Ϣ
	}
}

//����Ч��0-0 -- ����ͼ˳�����8���� 
void CAnimationDlg::Animation0_0(int y){
	memset(array_animation,0x00,64);
	for(int z=0;z<8;z++){
		array_animation[z+y*8]=0xff;
	}
}
//����Ч��0-1 -- ����ͼ�������8���� 
void CAnimationDlg::Animation0_1(int y){
	memset(array_animation,0x00,64);
	for(int z=7;z>=0;z--){
		array_animation[z+y*8]=0xff;
	}
}

/*
����Ч��1
*/
void CAnimationDlg::Animation1(){
	if(A[1][0] >= 0 &&A[1][0] < 8 ){
		Animation1_0(A[1][0]);
		SendToParent();
		A[1][0]++;
	}
	else if(A[1][0]==8){
		A[1][0]++;
		A[1][1] = 1;
		Animation1_1(A[1][1]);
		SendToParent();
		A[1][1]++;
	}
	else if(A[1][0] == 9 && A[1][1] < 7){
		Animation1_1(A[1][1]);
		SendToParent();
		A[1][1]++;
	}
	else if(A[1][0] == 9 && A[1][1]== 7){
		A[1][0] = 1;
		Animation1_1(A[1][1]);
		SendToParent();
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

//����Ч��1-0
void CAnimationDlg::Animation1_0(int y){
	memset(array_animation,0x01<<y,64);
}
//����Ч��1-1
void CAnimationDlg::Animation1_1(int y){
	memset(array_animation,0x80>>y,64);
}

/*
����Ч��2
*/
void CAnimationDlg::Animation2(){
	if(A[2][0] >=0 && A[2][0]< 8){
		Animation2_0(A[2][0]);
		SendToParent();
		A[2][0]++;
	}
	else if(A[2][0] == 8){
		A[2][0]++;
		A[2][1] = 6;
		Animation2_1(A[2][1]);
		SendToParent();
		A[2][1]--;
	}else if(A[2][0] == 9&&A[2][1] >0 ){
		Animation2_1(A[2][1]);
		SendToParent();
		A[2][1]--;
	}else if(A[2][0] == 9&&A[2][1] == 0){
		A[2][0]= 1;
		Animation2_1(A[2][1]);
		SendToParent();
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

//����Ч��2-0
void CAnimationDlg::Animation2_0(int y){
	memset(array_animation,0x00,64);
	for(int z=0;z<8;z++){
		array_animation[z*8+y]=0xff;
	}
}
//����Ч��2-1
void CAnimationDlg::Animation2_1(int y){
	memset(array_animation,0x00,64);
	for(int z=7;z>=0;z--){
		array_animation[z*8+y]=0xff;
	}
}

/*
  ����3 - ǰ��ͼ 1�� 64����˳�����
*/
void CAnimationDlg::Animation3(){
	if(A[3][0]>=0 && A[3][0]<63){
		array_animation[A[3][0]]=0x01;
		SendToParent();
		A[3][0]++;
	}else if (A[3][0]==63){
		array_animation[A[3][0]]=0x01;
		SendToParent();
		A[3][0]=0;
		memset(array_animation,0x00,64);
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

/*
  ����4 - ����ͼ ��ʱ�� �� ��ת
*/
void CAnimationDlg::Animation4(){
	if(A[4][0]==0){
		memset(array_animation,0x80,64);
		SendToParent();
		A[4][0]++;
		A[4][1] = 0;
	}else if (A[4][0]>0 && A[4][1]<27){
		if(A[4][1]<7){
			for(int k=0;k<8;k++){
				array_animation[k*8] |= (0x80>>(A[4][1]+1));
				array_animation[k*8+7-A[4][1]]=0;
			}
		}else if(A[4][1]<14){
			for(int k=0;k<8;k++){
				array_animation[k*8+A[4][1]-6]=0x01;
				array_animation[k*8]>>=0x01;
			}
		}else if(A[4][1]<21){
			for(int k=0;k<8;k++){	
				array_animation[k*8+A[4][1]-14]=0;
				array_animation[k*8+7]|=(0x01<<(A[4][1]-13));
			}
		}else if(A[4][1]<27){
			for(int k=0;k<8;k++){	
				array_animation[k*8+27-A[4][1]]=0x80;
				array_animation[k*8+7]<<=1;
			}
		}
		A[4][1] ++;
		SendToParent();
	}else if(A[4][1] == 27){
		memset(array_animation,0x80,64);
		SendToParent();
		A[4][1] = 0;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

/*
  ����5 - ����ͼ ˳ʱ�� �� ��ת
*/
void CAnimationDlg::Animation5(){
	if(A[5][0]==0){
		memset(array_animation,0x80,64);
		SendToParent();
		A[5][0]++;
		A[5][1] = 0;
	}else if (A[5][0]>0&&A[5][1]<27){
		if(A[5][1]<7){
			for(int k=0;k<8;k++){
				array_animation[k*8+7] |= (0x80>>(A[5][1]+1));
				array_animation[k*8+A[5][1]]=0;
			}
		}else if(A[5][1]<14){
			for(int k=0;k<8;k++){
				array_animation[k*8+13-A[5][1]]=0x01;
				array_animation[k*8+7]>>=0x01;
			}
		}else if(A[5][1]<21){
			for(int k=0;k<8;k++){	
				array_animation[k*8+21-A[5][1]]=0;
				array_animation[k*8]|=(0x01<<(A[5][1]-13));
			}
		}else if(A[5][1]<27){
			for(int k=0;k<8;k++){	
				array_animation[k*8+A[5][1]-20]=0x80;
				array_animation[k*8]<<=1;
			}
		}
		A[5][1] ++;
		SendToParent();
	}else if(A[5][1] ==27){
		memset(array_animation,0x80,64);
		SendToParent();
		A[5][1] = 0;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

/*
  ����6 - ����ͼ ��ʱ�� �� ��ת
*/
void CAnimationDlg::Animation6(){
	if(A[6][0]==0){
		  for(int k=0;k<8;k++){
			 array_animation[7*8+k]=0xff;
		  }
		SendToParent();
		A[6][0]++;
		A[6][1] = 0;
	}else if (A[6][0]>0 && A[6][1]<27){
		if(A[6][1]<7){
			for(int k=0;k<8;k++){
				array_animation[(6-A[6][1])*8+k] = 0x01;
				array_animation[7*8+k]>>=1;
			}
		}else if(A[6][1]<14){
			for(int k=0;k<8;k++){
				array_animation[k] |= (0x01<<(A[6][1]-6));
				array_animation[(14-A[6][1])*8+k]=0;
			}
		}else if(A[6][1]<21){
			for(int k=0;k<8;k++){	
				array_animation[(A[6][1]-13)*8+k]=0x80;
				array_animation[k]<<=1;
			}
		}else if(A[6][1]<27){
			for(int k=0;k<8;k++){	
				array_animation[7*8+k] |= 0x80>>(A[6][1]-20);
				array_animation[(A[6][1]-21)*8+k]=0;
			}
		}
		A[6][1] ++;
		SendToParent();
	}else if(A[6][1] ==27){
		for(int k=0;k<8;k++){	
				array_animation[7*8+k] |= 0x80>>(A[6][1]-20);
				array_animation[(A[6][1]-21)*8+k]=0;
		}
		A[6][1] = 0;
		SendToParent();
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

/*
  ����7 - empty=0,ʵ1��; kind=0���Ͻ�,1���Ͻ�,2���½�,3���½�
*/
void CAnimationDlg::Animation7(int empty, int kind){
	if(A[7][0]<=8){
		if(empty == 0){
			Animation7_0(array_animation,A[7][0]);
		}else{
			Animation7_1(array_animation,A[7][0]);
		}
		if(kind == 0){
			;
		}else if(kind == 1){
			AnimationMove(array_animation,0,1,8-A[7][0]);
		}else if(kind ==2){
			AnimationMove(array_animation,2,1,8-A[7][0]);
		}else{
			AnimationMove(array_animation,0,1,8-A[7][0]);
			AnimationMove(array_animation,2,1,8-A[7][0]);
		}
		SendToParent();
		A[7][0] ++;
	}else if(A[7][0] == 9){
		A[7][1] = 7;
		
		if(empty == 0){
			Animation7_0(array_animation,A[7][1]);
		}else{
			Animation7_1(array_animation,A[7][1]);
		}
		if(kind == 0){
			AnimationMove(array_animation,0,1,8-A[7][1]);
			
		}else if(kind == 1){
			AnimationMove(array_animation,0,1,8-A[7][1]);
			AnimationMove(array_animation,2,1,8-A[7][1]);
		}else if(kind ==2){
			;
		}else{
			AnimationMove(array_animation,2,1,8-A[7][1]);
		}
		A[7][1] --;
		SendToParent();
		
		A[7][0]++;
	}else if(A[7][0] == 10 && A[7][1] > 0){
		if(empty == 0){
			Animation7_0(array_animation,A[7][1]);
		}else{
			Animation7_1(array_animation,A[7][1]);
		}
		if(kind == 0){
			AnimationMove(array_animation,0,1,8-A[7][1]);
			
		}else if(kind == 1){
			AnimationMove(array_animation,0,1,8-A[7][1]);
			AnimationMove(array_animation,2,1,8-A[7][1]);
		}else if(kind ==2){
			;
		}else{
			AnimationMove(array_animation,2,1,8-A[7][1]);
		}
		A[7][1] --;
		SendToParent();
	}else if(A[7][0] == 10 && A[7][1] == 0 ){
		if(empty == 0){
			Animation7_0(array_animation,A[7][1]);
		}else{
			Animation7_1(array_animation,A[7][1]);
		}
		if(kind == 0){
			AnimationMove(array_animation,0,1,8-A[7][1]);
			
		}else if(kind == 1){
			AnimationMove(array_animation,0,1,8-A[7][1]);
			AnimationMove(array_animation,2,1,8-A[7][1]);
		}else if(kind ==2){
			;
		}else{
			AnimationMove(array_animation,2,1,8-A[7][1]);
		}
		SendToParent();

		A[7][0] = 0;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}
void CAnimationDlg::Animation7_0(byte *a,int n){
	int i,j;
	for(i=0;i<64;i++){
		a[i]=0;
	}
	j=0xff>>(8-n);
	/***************************/	
	a[0]=j;
	a[n-1]=j;
	a[(n-1)*8]=j;
	a[(n-1)*8+n-1]=j;
	for(i=0;i<n;i++)
	{
		j=(0x01|(0x01<<(n-1)));
		/************x��*************/
		a[i*8]|=j;
		a[i*8+n-1]|=j;
		/************z��*************/
		a[i]|=j;
		a[(n-1)*8+i]|=j;
	}
}
void CAnimationDlg::Animation7_1(byte *a,int n){
	int x,z;
	for(z=0;z<8;z++){
		for(x=0;x<8;x++)
		{
			if(z<n&&x<n)
				a[z*8+x]=0xff>>(8-n);
			else
				a[z*8+x]=0;
		}	
	}
}

/*
  ����8 - Rain  0 Ϊ�� ��0 Ϊ����
*/
void CAnimationDlg::Animation8(int isUp){
	if(isUp ==0){
		if(A[8][0] == 0){
			for(int x=0;x<8;x++){
				array_animation[x]=tab_rain[x];
			}
			SendToParent();
			A[8][0]++;
		}else if(A[8][0] >0 && A[8][0] <7){

			AnimationMove(array_animation,2,1,1);
			for(int x=0;x<8;x++){
				array_animation[x]=tab_rain[A[8][0]*8+x];
			}
			SendToParent();
			A[8][0]++;
		}else if(A[8][0] == 7){
			AnimationMove(array_animation,2,1,1);
			for(int x=0;x<8;x++){
				array_animation[x]=tab_rain[A[8][0]*8+x];
			}
			SendToParent();
			A[8][0] = 0;
			SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		}
	}else{
		if(A[8][0] == 0){
			for(int x=0;x<8;x++){
				array_animation[56+x]=tab_rain[x];
			}
			SendToParent();
			A[8][0]++;
		}else if(A[8][0] >0 && A[8][0] <7){

			AnimationMove(array_animation,2,0,1);
			for(int x=0;x<8;x++){
				array_animation[56+x]=tab_rain[A[8][0]*8+x];
			}
			SendToParent();
			A[8][0]++;
		}else if(A[8][0] == 7){
			AnimationMove(array_animation,2,0,1);
			for(int x=0;x<8;x++){
				array_animation[56+x]=tab_rain[A[8][0]*8+x];
			}
			SendToParent();
			A[8][0] = 0;
			SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		}
	}
}

/*
  ����9 - Up  
*/
void CAnimationDlg::Animation9(){
	if(A[9][0] >= 0&& A[9][0]<8){
		Animation9_0(A[9][0]);
		SendToParent();
		A[9][0]--;
		A[9][1] = 7;
	}
	else if(A[9][0]== -1&& A[9][1] > 0){
		Animation9_1(A[9][1]);
		SendToParent();
		A[9][1]--;
		A[9][2] = 1;
	}
	else if(A[9][0] == -1 && A[9][2] < 7){
		Animation9_2(A[9][2]);
		SendToParent();
		A[9][2]++;
	}
	else if(A[9][0] == -1 && A[9][2] == 7){
		Animation9_2(A[9][2]);
		SendToParent();
		A[9][0] = 7;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}
void CAnimationDlg::Animation9_0(int y){
	for(int z=0;z<8;z++){
		array_animation[z+y*8]=0xff;
	}
}
void CAnimationDlg::Animation9_1(int y){
	for(int z=7;z>=0;z--){
		array_animation[z+y*8]=0x00;
	}
}
void CAnimationDlg::Animation9_2(int y){
	memset(array_animation,0x00,64);
	for(int z=7;z>=0;z--){
		array_animation[z+y*8]=0xff;
	}
}

/*
  ����10 - ��ת
  king  0 ���� 1 ʵ��
  cw    0 ˳ʱ�� 1 ��ʱ��
*/
void CAnimationDlg::Animation10(int kind,int cw){
	if(cw ==1){
		if(A[10][0]>=0 && A[10][0]<13){
			for(int z=0;z<8;z++){
				for(int x=0;x<8;x++){
					if(x>1&&x<6&&z>1&&z<6&&kind!=1)
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][0]*8+x]&0xc3;
					else
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][0]*8+x];
				}
			}
			SendToParent();
			A[10][0]++;
		}else if(A[10][0] == 13){
			for(int z=0;z<8;z++){
				for(int x=0;x<8;x++){
					if(x>1&&x<6&&z>1&&z<6&&kind!=1)
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][0]*8+x]&0xc3;
					else
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][0]*8+x];
				}
			}
			SendToParent();
			A[10][0]=0;
			SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		}
	}else{
		if(A[10][1]>0 && A[10][1]<=13){
			for(int z=0;z<8;z++){
				for(int x=0;x<8;x++){
					if(x>1&&x<6&&z>1&&z<6&&kind!=1)
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][1]*8+x]&0xc3;
					else
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][1]*8+x];
				}
			}
			SendToParent();
			A[10][1]--;
		}else if(A[10][1] == 0){
			for(int z=0;z<8;z++){
				for(int x=0;x<8;x++){
					if(x>1&&x<6&&z>1&&z<6&&kind!=1)
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][1]*8+x]&0xc3;
					else
						array_animation[z*8+x]=tab_xuanzhuantiao[A[10][1]*8+x];
				}
			}
			SendToParent();
			A[10][1]=13;
			SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		}
	}
}

void CAnimationDlg::Animation11(){
	Animation10(0,0);
}

/*
  ����12 - ������ת
  cw    0 ˳ʱ�� 1 ��ʱ��
*/
void CAnimationDlg::Animation12(int cw){
	if(cw==1){
		if(A[12][0] == 0){
			for(int z=0;z<8;z++)
				for(int x=0;x<8;x++)
					array_animation[z*8+x]=tab_xuanzhuantiao[x];
			SendToParent();
			A[12][0]++;
			A[12][1] = 13;
		}else if(A[12][0] >0 && A[12][1]>0){
			AnimationMove(array_animation,2,1,1);				
			for(int x=0;x<8;x++){
				array_animation[x]=tab_xuanzhuantiao[A[12][1]*8+x];
			}
			SendToParent();
			A[12][1] --;
		}else if(A[12][0] >0 && A[12][1]==0){
			AnimationMove(array_animation,2,1,1);				
			for(int x=0;x<8;x++){
				array_animation[x]=tab_xuanzhuantiao[A[12][1]*8+x];
			}
			SendToParent();
			A[12][1] = 13;
			SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		}
	}else{
		if(A[12][2] == 0){
			for(int z=0;z<8;z++)
				for(int x=0;x<8;x++)
					array_animation[z*8+x]=tab_xuanzhuantiao[x];
			SendToParent();
			A[12][2]++;
			A[12][3] = 0;
		}
		else if(A[12][2]>0 && A[12][3] <13){
			AnimationMove(array_animation,2,1,1);
			for(int x=0;x<8;x++){
				array_animation[x]=tab_xuanzhuantiao[A[12][3]*8+x];
			}
			SendToParent();
			A[12][3] ++;
		}else if(A[12][2]> 0 && A[12][3] == 13){
			AnimationMove(array_animation,2,1,1);
			for(int x=0;x<8;x++)
				array_animation[x]=tab_xuanzhuantiao[A[12][3]*8+x];
			SendToParent();
			A[12][3] = 0;
			SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
		}
	}
}

/*
  ����13 - ɳ©
*/
void CAnimationDlg::Animation13(){
	if(A[13][0]<127){
		array_animation[tab00[A[13][0]]]=(0x01<<tab01[A[13][0]]);
		SendToParent();
		array_animation[tab00[A[13][0]]]=0;
		A[13][0]++;
	}else if(A[13][0]==127){
		array_animation[tab00[A[13][0]]]=(0x01<<tab01[A[13][0]]);
		SendToParent();
		array_animation[tab00[A[13][0]]]=0;
		A[13][0]++;
		A[13][1] = 0;
	}else if(A[13][0]==128&&A[13][1]<128){
		array_animation[tab10[A[13][1]]]|=(0x01<<tab01[A[13][1]]);
		if(A[13][1]>=8){
			array_animation[tab10[A[13][1]-8]]^=(0x01<<tab01[A[13][1]-8]);//^��ʾ���
		}
		SendToParent();
		A[13][1]++;
	}else if(A[13][0]==128&&A[13][1]==128){
		array_animation[7]|=0x01;
		array_animation[0]=0x01;
		SendToParent();
		A[13][1]++;
		A[13][2]=1;
	}else if(A[13][1]==129&&A[13][2]<127){

		if(A[13][2]<8){
			array_animation[8-A[13][2]] = 0;
		}
		array_animation[tab00[A[13][2]]] |= (0x01<<tab01[A[13][2]]);
		SendToParent();
		A[13][2]++;
	}else if(A[13][1]==129&&A[13][2]==127){
		if(A[13][2]<8){
			array_animation[8-A[13][2]] = 0;
		}
		array_animation[tab00[A[13][2]]] |= (0x01<<tab01[A[13][2]]);
		SendToParent();
		A[13][2]++;
		A[13][3] = 0;
	}else if(A[13][2] ==128&&A[13][3]<127){
		array_animation[tab10[A[13][3]]]^=(0x01<<tab01[A[13][3]]);
		SendToParent();
		A[13][3]++;
	}else if(A[13][2] ==128 && A[13][3]==127){
		array_animation[tab10[A[13][3]]]^=(0x01<<tab01[A[13][3]]);
		SendToParent();
		A[13][0]=0;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}


}


/*
  ����14 - ˮ��
*/
void CAnimationDlg::Animation14(int x,int y){

	if(A[14][0] >=0 && A[14][0] <7){
		array_animation[y+A[14][0]*8]= 0x01<<x;
		if(A[14][0] >0){
			array_animation[y+(A[14][0]-1)*8]=0;
		}
		SendToParent();
		A[14][0]++;
	}//����
	else if(A[14][0] == 7){
		array_animation[y+A[14][0]*8]= 0x01<<x;
		array_animation[y+(A[14][0]-1)*8]=0;
		SendToParent();
		A[14][0]++;
		A[14][1] = 0;
	}else if(A[14][0] == 8 && A[14][1]<6){
		for(int i=0;i<8;i++)
			array_animation[i+56]=tab_water[A[14][1]*16+7-y+i]>>(7-x);
		SendToParent();
		A[14][1]++;
	}//��ɢ
	else if(A[14][0] == 8&& A[14][1]==6){
		for(int i=0;i<8;i++)
			array_animation[i+56]=tab_water[A[14][1]*16+7-y+i]>>(7-x);
		SendToParent();
		A[14][0] = 0;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

/*
  ����14 - ˮ��2
*/
void CAnimationDlg::Animation15(int y){
}

void CAnimationDlg::Animation16(int y){}
void CAnimationDlg::Animation17(int y){}
void CAnimationDlg::Animation18(int y){}
void CAnimationDlg::Animation19(int y){}

void CAnimationDlg::AnimationMove(byte *a,int kind,int direction,int length)// kind=0 x��,1 y��,2 z�᣻
	//direction=0,����,1����;length�ƶ�λ��������Ϊ8
{
	int i,x,z;
	if(kind==0)//x��
	{
		if(direction==1) //����
			for(z=0;z<8;z++)
			{
				for(x=7;x>=length;x--)
					a[z*8+x]=a[z*8+(x-length)];
				for(x=0;x<length;x++)
					a[z*8+x]=0;			
			}	
		else			 //����
			for(z=0;z<8;z++)
			{
				for(x=length;x<8;x++)
					a[z*8+(x-length)]=a[z*8+x];
				for(x=(8-length);x<8;x++)
					a[z*8+x]=0;			
			}				
	}
	else if(kind==1)//y��  
	{
		if(direction==1)//����
			for(i=0;i<64;i++)
				a[i]<<=length;
		else			//����
			for(i=0;i<64;i++)
				a[i]>>=length;
	}
	else		   //z��
	{
		if(direction==1) //����
			for(x=0;x<8;x++)
			{
				for(z=7;z>=length;z--)
					a[z*8+x]=a[(z-length)*8+x];
				for(z=0;z<length;z++)
					a[z*8+x]=0;			
			}	
		else			 //����
			for(x=0;x<8;x++)
			{
				for(z=length;z<8;z++)
					a[(z-length)*8+x]=a[z*8+x];
				for(z=(8-length);z<8;z++)
					a[z*8+x]=0;			
			}					
	}
}