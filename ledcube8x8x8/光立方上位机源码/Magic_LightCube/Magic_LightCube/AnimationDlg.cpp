// AnimationDlg.cpp : 实现文件
//
#include <stdlib.h>
#include "stdafx.h"
#include "Magic_LightCube.h"
#include "AnimationDlg.h"
#include "afxdialogex.h"

//CFile file_animation;
CStdioFile file_animation;
CRect rect_animation;  // 白色背景区域 

BYTE StepAnimation[MAX_Array][64];      //动画步数 用于静态list显示
BYTE Animation[MAX_Array][MAX_Array][64];	   //动画，用于动画list显示

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
{ //旋转条
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

int tab00[]={ //从下往上
	0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,6,5,4,3,2,1,//28
	1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+2,1*8+3,1*8+4,1*8+5,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+5,1*8+4,1*8+3,1*8+2,//20
	2*8+2,2*8+2,2*8+2,2*8+2,2*8+3,2*8+4,2*8+5,2*8+5,2*8+5,2*8+5,2*8+4,2*8+3,//12
	3*8+3,3*8+3,3*8+4,3*8+4,//4+4
	4*8+3,4*8+3,4*8+4,4*8+4,
	5*8+2,5*8+2,5*8+2,5*8+2,5*8+3,5*8+4,5*8+5,5*8+5,5*8+5,5*8+5,5*8+4,5*8+3,//12
	6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+2,6*8+3,6*8+4,6*8+5,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+5,6*8+4,6*8+3,6*8+2,//20
	56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+1,56+2,56+3,56+4,56+5,56+6,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+6,56+5,56+4,56+3,56+2,56+1,//28
};
int tab10[]={//从上往下
	56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+0,56+1,56+2,56+3,56+4,56+5,56+6,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+7,56+6,56+5,56+4,56+3,56+2,56+1,//28
	6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+1,6*8+2,6*8+3,6*8+4,6*8+5,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+6,6*8+5,6*8+4,6*8+3,6*8+2,//20
	5*8+2,5*8+2,5*8+2,5*8+2,5*8+3,5*8+4,5*8+5,5*8+5,5*8+5,5*8+5,5*8+4,5*8+3,//12
	4*8+3,4*8+3,4*8+4,4*8+4,
	3*8+3,3*8+3,3*8+4,3*8+4,//4+4
	2*8+2,2*8+2,2*8+2,2*8+2,2*8+3,2*8+4,2*8+5,2*8+5,2*8+5,2*8+5,2*8+4,2*8+3,//12
	1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+1,1*8+2,1*8+3,1*8+4,1*8+5,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+6,1*8+5,1*8+4,1*8+3,1*8+2,//20
	0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,6,5,4,3,2,1,//28
};

int tab01[]={//移动距离
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

// CAnimationDlg 对话框

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


// CAnimationDlg 消息处理程序

/*
void CAnimationDlg::DelaySecond(int second){
	COleDateTime start_time= COleDateTime::GetCurrentTime();
	COleDateTimeSpan end_time= COleDateTime::GetCurrentTime()-start_time;
	while(end_time.GetTotalSeconds()< second) //实现延时2秒
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

	m_listAnimation.AddString(L"动画0");
	m_listAnimation.AddString(L"动画1");
	m_listAnimation.AddString(L"动画2");
	m_listAnimation.AddString(L"动画3");
	m_listAnimation.AddString(L"动画4");
	m_listAnimation.AddString(L"动画5");
	m_listAnimation.AddString(L"动画6");
	m_listAnimation.AddString(L"动画7");
	m_listAnimation.AddString(L"动画8");
	m_listAnimation.AddString(L"动画9");
	m_listAnimation.AddString(L"动画10");
	m_listAnimation.AddString(L"动画11");
	m_listAnimation.AddString(L"动画12");
	m_listAnimation.AddString(L"动画13");
	m_listAnimation.AddString(L"动画14");
	/*m_listAnimation.AddString(L"动画15");
	m_listAnimation.AddString(L"动画16");
	m_listAnimation.AddString(L"动画17");
	m_listAnimation.AddString(L"动画18");
	m_listAnimation.AddString(L"动画19");
	m_listAnimation.AddString(L"动画20");
	m_listAnimation.AddString(L"动画21");
	*/
	m_sliderSpeed.SetRange(50, 600); 
	m_sliderSpeed.SetTicFreq(50);
	m_sliderSpeed.SetPos(200);
	speed = m_sliderSpeed.GetPos();
	m_Radio1 = 0;
	Custom_C = 0;  //自定义动画计数
	
}

void CAnimationDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio1 = 0;
}

void CAnimationDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio1 = 1;
	/*
	CString c;
	c.Format(L"%d",m_listAnimation.GetCount());
	AfxMessageBox(c);
	*/
}

//接收父窗口消息
LRESULT CAnimationDlg::MessageFromParent(WPARAM wParam, LPARAM lParam){
	// TODO: 处理用户自定义消息
	switch(lParam){
	case -1:  //change tab 切换选项卡，
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
	List Static 相关函数
	选择响应函数；保存、更新、删除静态画面函数
	选择响应 -- sel change -- OnLbnSelchangeListStatic
	保存  --  save1    -- OnBnClickedButtonSave1
	更新  --  update1  -- OnBnClickedButtonUpdate1
	删除  --  delete1  -- OnBnClickedButtonDelete1
*/
//list static 项 选择响应
void CAnimationDlg::OnLbnSelchangeListStatic()
{
	// TODO: 在此添加控件通知处理程序代码
	pWnd1 = GetParent()->GetParent();	

	CString list_name;   
    int nCurSel;    
	m_listStatic.GetText(m_listStatic.GetCurSel(),list_name);
	nCurSel = _tstoi(list_name);                              //CString转 int
	if(m_listStatic.GetSelCount() == 1){  //  选中某 一项 时 显示到主界面 否则不显示
		GetDlgItemText(IDC_CHECK_KEEP,checkStr);
		if(checkStr == L"Play"){      //动画处于暂停或停止时，liststatic 列表有效
			::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE
				,(WPARAM)(&StepAnimation[nCurSel]),-3);
		}
	}
}
//list static 保存静态画面
void CAnimationDlg::OnBnClickedButtonSave1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString list ;
	ListStatic = m_listStatic.GetCount();
	list.Format(L"%d",ListStatic);
	//AfxMessageBox(list);
	m_listStatic.AddString(list);       //增加列表项目

	pWnd1 = GetParent()->GetParent();	
	::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,NULL,-2);
	/*
	INT_PTR nRes;
	nRes = m_saveNameDlg.DoModal();
	if (IDCANCEL == nRes){   
		//点击取消
		m_saveNameDlg.ClearSaveName();   //清空save name编辑框
		return ;
	}else{
		//点击确定
		UpdateData(TRUE);
		m_listStatic.AddString(m_saveNameDlg.GetSaveName());
		m_listStatic.SetCurSel(0);
		UpdateData(false);
		m_saveNameDlg.ClearSaveName();   //清空save name编辑框
	}
	*/
}
//list static 更新静态画面
void CAnimationDlg::OnBnClickedButtonUpdate1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString list_update;
	if(m_listStatic.GetSelCount() == 1){			//选择一个项目
		ListStatic = m_listStatic.GetCurSel();		//得到选中项目数
		m_listStatic.GetText(m_listStatic.GetCurSel(),list_update);
		m_listStatic.InsertString(m_listStatic.GetCurSel(),list_update);
		//通知父窗口 发送数组回来
		pWnd1 = GetParent()->GetParent();	
		::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,NULL,-2);
		//删除老的项
		m_listStatic.DeleteString(m_listStatic.GetCurSel()+1);
	}
}
//list static 删除静态画面
void CAnimationDlg::OnBnClickedButtonDelete1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString list;
	if(m_listStatic.GetSelCount() == 0){
		;  //未选中list项目，不执行动作
	}else if(m_listStatic.GetSelCount() == 1){  //选择一个项目，即删除选择
		//list1.Format(L"%d",m_listStatic.GetCurSel());
		//AfxMessageBox(list1);
		if((m_listStatic.GetCurSel()+1) == m_listStatic.GetCount()){ //选择了最后一项
			m_listStatic.DeleteString(m_listStatic.GetCurSel());  //删除选择项
		}else{  
			for(int i = m_listStatic.GetCurSel()+1;i<m_listStatic.GetCount();i++){
				list.Format(L"%d",i-1);					//得到当前数字
				m_listStatic.DeleteString(i);			//删除下一行
				m_listStatic.InsertString(i,list);     //插入新一行，命名为上一行的数字
				memcpy(StepAnimation[i-1] ,StepAnimation[i],64);
			}
			m_listStatic.DeleteString(m_listStatic.GetCurSel());  //删除选择项
		}
	}
	//选中多个项目，但不是全部
	else if(m_listStatic.GetSelCount() > 1 && m_listStatic.GetSelCount() < m_listStatic.GetCount()){
		if((m_listStatic.GetCurSel()+1) == m_listStatic.GetCount()){ //选择项中包含最后一项
			listStatic_max = (m_listStatic.GetSelCount()+ abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1)-1);
			listStatic_min = abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1);
			for(int i = listStatic_max;i>=listStatic_min;i--){
				m_listStatic.DeleteString(i);    //从大至小删除
			}
		}else{
			for(int i = m_listStatic.GetCurSel()+1;i<m_listStatic.GetCount();i++){
				list.Format(L"%d",i-m_listStatic.GetSelCount());			//得到选中项中最小数字
				m_listStatic.DeleteString(i);							//删除下一行
				m_listStatic.InsertString(i,list);						//插入新一行，命名为最小数字
				memcpy(StepAnimation[i-m_listStatic.GetSelCount()] ,StepAnimation[i],64);
			}
			listStatic_max = (m_listStatic.GetSelCount()+ abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1)-1);
			listStatic_min = abs(m_listStatic.GetSelCount()-m_listStatic.GetCurSel()-1);
			for(int i = listStatic_max;i>=listStatic_min;i--){
				m_listStatic.DeleteString(i);    //从大至小删除
			}
		}
	}
	//选中全部项
	else if(m_listStatic.GetSelCount() == m_listStatic.GetCount()){
		m_listStatic.ResetContent();  // 选中所有list项目，即清空list
	}
}

/*
	List Animation 相关函数
	选择响应函数；保存、删除动画函数
	选择响应 -- sel change -- OnLbnSelchangeListAnimation
	保存  --  save2    -- OnBnClickedButtonSave2
	删除  --  delete2  -- OnBnClickedButtonDelete2
*/
//list animation 保存动画
void CAnimationDlg::OnBnClickedButtonSave2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Pause"){
		m_checkKeep.SetWindowText(L"Play");
		m_checkKeep.SetCheck(BST_UNCHECKED);
		KillTimer(flag_list_animation);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}

	INT_PTR nRes;
	if(m_listStatic.GetSelCount()>1){    //判断选中动画，超过1
		//动画存放文件夹路径
		CString AnimationPath = GetExePath()+L"\\"+L"YFRobot Magic-LightCube"+L"\\";
		if(!PathIsDirectory(AnimationPath)){   //判断文件夹是否存在
			if(!CreateDirectory(AnimationPath, NULL)){
				AfxMessageBox(L"Folder to create a failure!");
				return ;
			}
		}
		nRes = m_saveNameDlg.DoModal();		//弹出对话框
		if (IDCANCEL == nRes){   
			//点击取消
			m_saveNameDlg.ClearSaveName();   //清空save name编辑框
			return ;
		}else{
			//点击确定
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
					memcpy(Animation[m_listAnimation.GetCount()][j-listmin],StepAnimation[j],64);//将数组保存至执行动画数组
					writeBuf += " ";
				}
				Animation_s[m_listAnimation.GetCount()] = m_listStatic.GetSelCount();  //保存动画步数
				file_animation.Write(writeBuf,writeBuf.GetLength()*2);

				file_animation.Close();

				m_listAnimation.AddString(m_saveNameDlg.GetSaveName());
				m_listAnimation.SetCurSel(m_listAnimation.GetCount()-1);
				UpdateData(false);

				m_saveNameDlg.ClearSaveName();   //清空save name编辑框
			}
		}
	}else{
		AfxMessageBox(L"The option for at least two items!");
	}
}

// 得到程序所在位置
CString CAnimationDlg::GetExePath(){
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);//得到程序模块名称，全路径
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\'); 
    path = path.Left(pos); 

	//得到程序路径
	//TCHAR exeFullPath[MAX_PATH];			// MAX_PATH
	//GetCurrentDirectory(MAX_PATH,exeFullPath);
	//AfxMessageBox(exeFullPath);

	//AfxMessageBox(path);
	return path;
}

//list animation 删除动画
void CAnimationDlg::OnBnClickedButtonDelete2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetExePath();
	flag_list_animation = m_listAnimation.GetCurSel();
	if(flag_list_animation == -1){

	}else if(flag_list_animation < 15){
		AfxMessageBox(L"Fixed animation group, please do not delete！");
	}else{
		KillTimer(flag_list_animation);
		GetDlgItemText(IDC_CHECK_KEEP,checkStr);
		if(checkStr == L"Pause"){
			m_checkKeep.SetWindowText(L"Play");
			m_checkKeep.SetCheck(BST_UNCHECKED);

			m_buttonSave1.EnableWindow(true);
			m_buttonUpdate1.EnableWindow(true);
		}	
		//动画组调整顺序，数据变换
		for(int j = m_listAnimation.GetCurSel();j<m_listAnimation.GetCount();j++){
			for(int i = 0;i<Animation_s[m_listAnimation.GetCurSel()+1];i++){
				//将下一个的动画组复制给当前动画组
				memcpy(Animation[j][i],Animation[j+1][i],64);
			}
		}
		m_listAnimation.DeleteString(m_listAnimation.GetCurSel());  //删除选择项
		m_listAnimation.SetCurSel(flag_list_animation-1);

		pWnd1 = GetParent()->GetParent();	
		::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,
			NULL,-1);            //发送消息至父窗口，通知清除界面
	}
}

//打开动画
void CAnimationDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Pause"){
		m_checkKeep.SetWindowText(L"Play");
		m_checkKeep.SetCheck(BST_UNCHECKED);
		KillTimer(flag_list_animation);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}

	TCHAR szFileFilter[]=L"txt文件(*.txt)|*.txt|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT
		|OFN_NOCHANGEDIR,szFileFilter,NULL);
	if(dlg.DoModal()==IDOK){
		CString strFilePath = dlg.GetPathName();	 //返回文件路径
		CString strFileName = dlg.GetFileName();       //返回文件名
		CString strFileTitle = dlg.GetFileTitle();   //返回文件标题
		if(file_animation.Open(strFilePath, CFile::modeRead | CFile::typeBinary)){
			file_animation.SeekToBegin(); 
			LONGLONG FileLen = (LONGLONG)file_animation.GetLength();
			//file_animation.Read(readBuf.GetBuffer(FileLen),FileLen*2);
			//memcpy(readBuf,readBuf,FileLen);
			file_animation.Read(readBuf,(UINT)FileLen); 

			CString head0,head1;
			head0.Format(L"%d",readBuf[0]);
			head1.Format(L"%d",readBuf[1]);
			if(head0 == "-1"&&head1 == "-2"){   //多个 头 ff fe
				//AfxMessageBox(L"0不计数");
				int j = 0;
				for(int i = 2;i < FileLen;){
					if(readBuf[i] == ' '){			//判断是否一帧动画数组结束
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
					if(readBuf[i] == ' '){			//判断是否一帧动画数组结束
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
			int step_nub = ((UINT)FileLen)/2/129;     //动画总步数
			for(int i = 0;i<step_nub;i++){
				memcpy(Animation[m_listAnimation.GetCount()][i],readBuff[i],64);//将数组保存至执行动画数组
			}
			Animation_s[m_listAnimation.GetCount()] = (UINT)FileLen/2/129;  //保存动画步数
			m_listAnimation.AddString(strFileTitle);
			m_listAnimation.SetCurSel(m_listAnimation.GetCount()-1);
		}else{
			AfxMessageBox(L"File Read Failure!!");
		}
	}
}

//将ASCII码转化为16进制数
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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

    GetClientRect(rect_animation);
	dc.Rectangle(rect_animation);
	dc.FillSolidRect(rect_animation,RGB(255,255,255));
}

//背景透明 代码
HBRUSH CAnimationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID()==IDC_STATIC||pWnd->GetDlgCtrlID()==IDC_BUTTON_SAVE1
		 ||pWnd->GetDlgCtrlID()==IDC_BUTTON_SAVE2||pWnd->GetDlgCtrlID()==IDC_BUTTON_STOP
		 ||pWnd->GetDlgCtrlID()==IDC_CHECK_KEEP||pWnd->GetDlgCtrlID()==IDC_SLIDER_SPEED
		 ||pWnd->GetDlgCtrlID()==IDC_RADIO1||pWnd->GetDlgCtrlID()==IDC_RADIO2
		 ||pWnd->GetDlgCtrlID()==IDC_STATIC_EACH)//你的控件ID
	{
		//pDC->SetTextColor(RGB(0,0,0));                 //设置字体颜色
		pDC->SetBkMode(TRANSPARENT);					     //设置字体背景为透明
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);    // 设置背景色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//Speed 滑块响应函数
void CAnimationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Play"){
		speed = m_sliderSpeed.GetPos();
	}else if(checkStr == L"Pause"){
		speed = m_sliderSpeed.GetPos();
		SetTimer(flag_list_animation,speed,NULL);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//Play 按键响应函数
void CAnimationDlg::OnBnClickedCheckKeep()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	BST_INDETERMINATE - 以灰化不可用
	BST_UNCHECKED     - 未选中
	BST_CHECKED       - 选中
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

//重复或者顺序
LRESULT CAnimationDlg::MessageTurn(WPARAM wParam, LPARAM lParam){
	// TODO: 处理用户自定义消息
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
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(flag_list_animation);
	flag_list_animation = -1;
	pWnd1 = GetParent()->GetParent();	
	::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,
		NULL,flag_list_animation);            //发送消息至父窗口，通知清除界面
	
	//并初始化计数数组A[][]
	for(int i = 0;i<sizeof(A)/sizeof(A[0]);i++){
		for(int j = 0;j<sizeof(A[0])/sizeof(A[0][0]);j++){
			A[i][j] = 0;
		}}
	//判断Play 按钮状态
	GetDlgItemText(IDC_CHECK_KEEP,checkStr);
	if(checkStr == L"Pause"){
		m_checkKeep.SetWindowText(L"Play");
		m_checkKeep.SetCheck(BST_UNCHECKED);
		m_buttonSave1.EnableWindow(true);
		m_buttonUpdate1.EnableWindow(true);
	}
	m_listAnimation.SetCurSel(flag_list_animation);    //跳出listbox
	m_listStatic.SetSel(-1,0);
}

//鼠标左键单击 list animation列表 事件
void CAnimationDlg::OnLbnSelchangeListAnimation()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(flag_list_animation);
	for(int i = 0;i<sizeof(A)/sizeof(A[0]);i++){
		A[i][0] = 0;
	}
	Custom_C = 0;
	A[9][0] = 7;A[10][1] = 13;A[12][2] = 0;

	pWnd1 = GetParent()->GetParent();							//得到父窗口句柄
	flag_list_animation = m_listAnimation.GetCurSel();          //获取list列表号  

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

// 鼠标左键双击 list animation列表 事件
void CAnimationDlg::OnLbnDblclkListAnimation()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAnimationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		Animation8(0); //非0 为上升
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

//发送消息至父窗口
void CAnimationDlg::SendToParent(){
	::SendMessage(pWnd1->m_hWnd,WM_ANIMATION_MESSAGE,
		(WPARAM)(&array_animation),flag_list_animation);
}

//自定义动画
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
动画效果0
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
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);  //动画结束消息
	}
}

//动画效果0-0 -- 俯视图顺序点亮8个面 
void CAnimationDlg::Animation0_0(int y){
	memset(array_animation,0x00,64);
	for(int z=0;z<8;z++){
		array_animation[z+y*8]=0xff;
	}
}
//动画效果0-1 -- 俯视图倒序点亮8个面 
void CAnimationDlg::Animation0_1(int y){
	memset(array_animation,0x00,64);
	for(int z=7;z>=0;z--){
		array_animation[z+y*8]=0xff;
	}
}

/*
动画效果1
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

//动画效果1-0
void CAnimationDlg::Animation1_0(int y){
	memset(array_animation,0x01<<y,64);
}
//动画效果1-1
void CAnimationDlg::Animation1_1(int y){
	memset(array_animation,0x80>>y,64);
}

/*
动画效果2
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

//动画效果2-0
void CAnimationDlg::Animation2_0(int y){
	memset(array_animation,0x00,64);
	for(int z=0;z<8;z++){
		array_animation[z*8+y]=0xff;
	}
}
//动画效果2-1
void CAnimationDlg::Animation2_1(int y){
	memset(array_animation,0x00,64);
	for(int z=7;z>=0;z--){
		array_animation[z*8+y]=0xff;
	}
}

/*
  动画3 - 前视图 1面 64个点顺序点亮
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
  动画4 - 俯视图 逆时针 面 旋转
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
  动画5 - 俯视图 顺时针 面 旋转
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
  动画6 - 左视图 逆时针 面 旋转
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
  动画7 - empty=0,实1空; kind=0左上角,1右上角,2左下角,3右下脚
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
		/************x行*************/
		a[i*8]|=j;
		a[i*8+n-1]|=j;
		/************z列*************/
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
  动画8 - Rain  0 为下 非0 为上升
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
  动画9 - Up  
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
  动画10 - 旋转
  king  0 空心 1 实心
  cw    0 顺时针 1 逆时针
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
  动画12 - 曲面旋转
  cw    0 顺时针 1 逆时针
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
  动画13 - 沙漏
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
			array_animation[tab10[A[13][1]-8]]^=(0x01<<tab01[A[13][1]-8]);//^表示异或
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
  动画14 - 水滴
*/
void CAnimationDlg::Animation14(int x,int y){

	if(A[14][0] >=0 && A[14][0] <7){
		array_animation[y+A[14][0]*8]= 0x01<<x;
		if(A[14][0] >0){
			array_animation[y+(A[14][0]-1)*8]=0;
		}
		SendToParent();
		A[14][0]++;
	}//下落
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
	}//扩散
	else if(A[14][0] == 8&& A[14][1]==6){
		for(int i=0;i<8;i++)
			array_animation[i+56]=tab_water[A[14][1]*16+7-y+i]>>(7-x);
		SendToParent();
		A[14][0] = 0;
		SendMessage(WM_TURN_MESSAGE,NULL,m_Radio1);
	}
}

/*
  动画14 - 水滴2
*/
void CAnimationDlg::Animation15(int y){
}

void CAnimationDlg::Animation16(int y){}
void CAnimationDlg::Animation17(int y){}
void CAnimationDlg::Animation18(int y){}
void CAnimationDlg::Animation19(int y){}

void CAnimationDlg::AnimationMove(byte *a,int kind,int direction,int length)// kind=0 x轴,1 y轴,2 z轴；
	//direction=0,负向,1正向;length移动位数，不能为8
{
	int i,x,z;
	if(kind==0)//x轴
	{
		if(direction==1) //正向
			for(z=0;z<8;z++)
			{
				for(x=7;x>=length;x--)
					a[z*8+x]=a[z*8+(x-length)];
				for(x=0;x<length;x++)
					a[z*8+x]=0;			
			}	
		else			 //负向
			for(z=0;z<8;z++)
			{
				for(x=length;x<8;x++)
					a[z*8+(x-length)]=a[z*8+x];
				for(x=(8-length);x<8;x++)
					a[z*8+x]=0;			
			}				
	}
	else if(kind==1)//y轴  
	{
		if(direction==1)//正向
			for(i=0;i<64;i++)
				a[i]<<=length;
		else			//负向
			for(i=0;i<64;i++)
				a[i]>>=length;
	}
	else		   //z轴
	{
		if(direction==1) //正向
			for(x=0;x<8;x++)
			{
				for(z=7;z>=length;z--)
					a[z*8+x]=a[(z-length)*8+x];
				for(z=0;z<length;z++)
					a[z*8+x]=0;			
			}	
		else			 //负向
			for(x=0;x<8;x++)
			{
				for(z=length;z<8;z++)
					a[(z-length)*8+x]=a[z*8+x];
				for(z=(8-length);z<8;z++)
					a[z*8+x]=0;			
			}					
	}
}