
// Magic_LightCubeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Magic_LightCube.h"
#include "Magic_LightCubeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Plies 8
#define View 3
#define Axis_X 8
#define Axis_Y 8


enum STATE { LOW, HIGH };
STATE m_arrayDot[Plies][View][Axis_X][Axis_Y];
//点阵显示背景区域
CRect rect(Coordinate_x1,Coordinate_y1,Coordinate_x2,Coordinate_y2);

/************临时变量****************/
//	CString s[8] = { L"0",L"1",L"2",L"3",L"4",L"5",L"6",L"7",};
//	byte s1[64];
//	byte s2[64];
//	byte s3[64];
//	byte s4[64];


/*数组初始化*/
void CMagic_LightCubeDlg::InitArray()
{
	/******************************
		鼠标位置 数组 
	ptxy[0] - 储存某层 0-第一层 1-第二层 ......7-第八层
	ptxy[1] - 储存某视角 0 - 前视图、1 - 左视图、2 - 俯视图
	ptxy[2] - 储存 x轴 数据
	ptxy[3] - 储存 y轴 数据
	*******************************/
	int ptxy[4] = {0,0,0,0};

	memset(hex_array,0x00,64);		// 初始化

	for(int n=0; n<sizeof(rc_array_dot)/sizeof(rc_array_dot[0]); n++){
		for(int m=0; m<sizeof(rc_array_dot[0])/sizeof(rc_array_dot[0][0]); m++){
			for(int i=0; i<sizeof(rc_array_dot[0][0])/sizeof(rc_array_dot[0][0][0]); i++){
				for(int j=0; j<sizeof(rc_array_dot[0][0][0])/sizeof(rc_array_dot[0][0][0][0]); j++){
					//
					rc_array_dot[n][m][i][j].SetRect(Coordinate_x1+Size_dot*(i+1)+Dot_add*n,
						Coordinate_y1+Size_dot*(j+1)+Dot_add*m,Coordinate_x1+Size_dot*(2+i)+Dot_add*n,
						Coordinate_y1+Size_dot*(j+2)+Dot_add*m);

					m_arrayDot[n][m][i][j] = LOW; //初始化 每个点 为低电平
				}}}}
}

/* 画点阵*/
void CMagic_LightCubeDlg::DrawAllDot(){
	CClientDC dc(this);
	//CWindowDC dc(this);

	for(int n=0; n<sizeof(rc_array_dot)/sizeof(rc_array_dot[0]); n++){
		for(int m=0; m<sizeof(rc_array_dot[0])/sizeof(rc_array_dot[0][0]); m++){
			for(int i=0; i<sizeof(rc_array_dot[0][0])/sizeof(rc_array_dot[0][0][0]); i++){
				for(int j=0; j<sizeof(rc_array_dot[0][0][0])/sizeof(rc_array_dot[0][0][0][0]); j++){
					CBrush brush;
					if(m_arrayDot[n][m][i][j] == HIGH ){
						brush.CreateSolidBrush(RGB(51,153,255));
					}else{
						brush.CreateSolidBrush(RGB(192,192,192));
					}
					CBrush * pOldBrush=dc.SelectObject(&brush);

					dc.Rectangle(rc_array_dot[n][m][i][j]);
				}}}}

	m_oglWindow.CallRender();

}

//点阵背景
void CMagic_LightCubeDlg::DrawBackground(){
	CPaintDC dc(this);
	//CWindowDC dc(this);
	dc.Rectangle(rect);
	dc.FillSolidRect(rect,RGB(204,204,204));
}

/*
	判断鼠标坐标并返回坐在点阵位置
*/
void CMagic_LightCubeDlg::PtInArea(const CPoint pt)
{
	for(int n=0; n<sizeof(rc_array_dot)/sizeof(rc_array_dot[0]); n++){
		for(int m=0; m<sizeof(rc_array_dot[0])/sizeof(rc_array_dot[0][0]); m++){
			for(int i=0; i<sizeof(rc_array_dot[0][0])/sizeof(rc_array_dot[0][0][0]); i++){
				for(int j=0; j<sizeof(rc_array_dot[0][0][0])/sizeof(rc_array_dot[0][0][0][0]); j++){
					if(rc_array_dot[n][m][i][j].PtInRect(pt)){
						ptxy[0] = ((long double)pt.x/(Coordinate_x1+Dot_add))<=1? 0 : ((long double)pt.x/(Coordinate_x1+Dot_add*2))<=1? 1 
							: ((long double)pt.x/(Coordinate_x1+Dot_add*3))<=1? 2 : ((long double)pt.x/(Coordinate_x1+Dot_add*4))<=1? 3 
							: ((long double)pt.x/(Coordinate_x1+Dot_add*5))<=1? 4 : ((long double)pt.x/(Coordinate_x1+Dot_add*6))<=1? 5 
							: ((long double)pt.x/(Coordinate_x1+Dot_add*7))<=1? 6 : 7  ;
						ptxy[1] = ((long double)pt.y/(Coordinate_y1+Dot_add))<=1? 0 : ((long double)pt.y/(Coordinate_y1+Dot_add*2))<=1? 1 : 2;
						ptxy[2] = int(((pt.x-((Coordinate_x1+Size_dot+Dot_add*ptxy[0])))/Size_dot));
						ptxy[3] = int(((pt.y-((Coordinate_y1+Size_dot+Dot_add*ptxy[1])))/Size_dot));

						CString str ;
						str.Format(L"%d+%d+%d+%d",ptxy[0],ptxy[1],ptxy[2],ptxy[3]);
						//SetWindowText(str);
						//AfxMessageBox(str);      //弹窗显示信息

						if(m_arrayDot[ptxy[0]][ptxy[1]][ptxy[2]][ptxy[3]]==LOW){ 
							m_arrayDot[ptxy[0]][ptxy[1]][ptxy[2]][ptxy[3]]=HIGH;
							DotShift(ptxy[0],ptxy[1],ptxy[2],ptxy[3]);
						}else{ 
							m_arrayDot[ptxy[0]][ptxy[1]][ptxy[2]][ptxy[3]] = LOW;
							DotShift(ptxy[0],ptxy[1],ptxy[2],ptxy[3]);
						}
						DrawAllDot();
						ViewArray();			// 编辑框显示数组
						SendData();

					}}}}}
}

// 编辑框显示数组
void CMagic_LightCubeDlg::ViewArray(){
	UpdateData(true);
	m_editArray = "";		//清空编辑框
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			// 2进制转换16进制 -- 移位操作
			hex_array[i*8+j] = (m_arrayDot[i][2][j][0]<<7)+(m_arrayDot[i][2][j][1]<<6)
				+(m_arrayDot[i][2][j][2]<<5)+(m_arrayDot[i][2][j][3]<<4)+(m_arrayDot[i][2][j][4]<<3)
				+(m_arrayDot[i][2][j][5]<<2)+(m_arrayDot[i][2][j][6]<<1)+ (m_arrayDot[i][2][j][7]<<0);
			str_array[i*8+j].Format(L"0X%02x, ", hex_array[i*8+j]);
			m_editArray += str_array[i*8+j];
		}}
	UpdateData(false);

	//m_edit.SetSel(-1,-1);
	//this->SetDlgItemTextW(IDC_EDIT1,m_editArray);   //将m_EditReceive内容显示到ID为IDC_EDIT1的编辑框的最后位置
	//m_edit.LineScroll(m_edit.GetLineCount()-1,0);   //将垂直滚动条滚动到最后一行

}
void CMagic_LightCubeDlg::ViewTheArray(byte hexArray[]){
	UpdateData(true);
	m_editArray = "";		//清空编辑框

	memmove(hex_array, hexArray, 64);
	for(int i=0;i<64;i++){
		str_array[i].Format(L"0X%02x, ", hex_array[i]);
		m_editArray += str_array[i];
	}
	UpdateData(false);
}

//点视角转换
void CMagic_LightCubeDlg::DotShift(UINT plies,UINT view,UINT axis_x,UINT axis_y){
	switch(view){
	case 0:
		m_arrayDot[axis_x][view+1][7-plies][axis_y] = m_arrayDot[plies][view][axis_x][axis_y];
		m_arrayDot[axis_y][view+2][axis_x][7-plies] = m_arrayDot[plies][view][axis_x][axis_y];
		break;
	case 1:
		m_arrayDot[7-axis_x][view-1][plies][axis_y] = m_arrayDot[plies][view][axis_x][axis_y];
		m_arrayDot[axis_y][view+1][plies][axis_x] = m_arrayDot[plies][view][axis_x][axis_y];
		break;
	case 2:
		m_arrayDot[7-axis_y][view-2][axis_x][plies] = m_arrayDot[plies][view][axis_x][axis_y];
		m_arrayDot[axis_x][view-1][axis_y][plies] = m_arrayDot[plies][view][axis_x][axis_y];
		break;
	default:
		break;
	}
}

//串口设置
void CMagic_LightCubeDlg::Setting(){

	Flag_send = FALSE;   //初始化同步输出标志

	/*串口选择组合框*/
	
	CString str ;
	for(int i=0;i<17;i++){
		str.Format(_T("com %d"),i+1);
		m_combCom.InsertString(i,str);
	}
	m_combCom.SetCurSel(2);				//预置COM口
	//m_combCom.SetItemHeight=20 ;
	//m_combCom.ResetContent();
	//波特率选择组合框
	
	//CString str1[]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),
	//	            _T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")};
					
	CString str1[]={_T("9600"),_T("19200"),_T("38400"),_T("57600"),_T("115200")};
	for(int i=0;i<5;i++)
	{
		int judge_tf = m_combBaud.AddString(str1[i]);
		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
		{
			MessageBox(_T("build baud error!"));
		} 
	}
	m_combBaud.SetCurSel(3);   //预置波特率为"57600"
	//m_combBaud.ResetContent();

	//初始化按钮状态
	m_Send.EnableWindow(false);
	m_combBaud.EnableWindow(true);
	m_combCom.EnableWindow(true);
}

/**************************
发送数据
发送格式：'$'+'M'+'>'+[data length]+[cmd]+[data]+[checksum]

***************************/
void CMagic_LightCubeDlg::SendData(){
	if (Flag_send == 1){   //串口连接标志判断

		//UpdateData(true);		      //更新控件数据
		byte checksum = 0;			  //校验和
		Array.RemoveAll();

		Array.SetSize(65);

		//Array.SetAt(0,byte('$'));    //前缀1 -- 0x24 
		//Array.SetAt(1,byte('M'));    //前缀2 -- 0x4D
		//Array.SetAt(2,byte('>'));    //写 “>” -- 0x3E 读“<” -- 0x3C
		//Array.SetAt(3,0x40);         //data length 
		//checksum ^= 0x40;
		//Array.SetAt(4,0x6E);         //cmd 命令
		//checksum ^= 0x6E;
		Array.SetAt(0, 0xf2);
		for(int i=1;i<65;i++)        //data
		{
			Array.SetAt(i,hex_array[i]);
			//checksum ^= hex_array[i]&0xFF;
		}
		//Array.SetAt(69,checksum);   //校验和
		m_mscom.put_Output(COleVariant(Array)); 
		//AfxMessageBox(L"发送数据中……");
	}
	else{ //串口未连接，不做数据输出		
	}
}

//十六进制转二进制
BOOL CMagic_LightCubeDlg::Hex2Bin(byte a[]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			m_arrayDot[i][2][j][0]=STATE((a[i*8+j]&0x80)>>7); m_arrayDot[i][2][j][1]=STATE((a[i*8+j]&0x40)>>6); 
			m_arrayDot[i][2][j][2]=STATE((a[i*8+j]&0x20)>>5); m_arrayDot[i][2][j][3]=STATE((a[i*8+j]&0x10)>>4); 
			m_arrayDot[i][2][j][4]=STATE((a[i*8+j]&0x08)>>3); m_arrayDot[i][2][j][5]=STATE((a[i*8+j]&0x04)>>2);
			m_arrayDot[i][2][j][6]=STATE((a[i*8+j]&0x02)>>1); m_arrayDot[i][2][j][7]=STATE(a[i*8+j]&0x01);
			for(int k= 0;k<8;k++){
				DotShift(i,2,j,k);
			}
		}}
	return m_arrayDot[8][3][8][8];
}

//编辑框字体
void CMagic_LightCubeDlg::EditInit(){
	CFont *m_Font;
    m_Font = new CFont; 
    m_Font->CreateFont(16,7,0,0,100,
        0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS ,L"Courier New");//Arial
	m_edit.SetMargins(20,10);
	m_edit.SetFont(m_Font,true);
	//m_edit.SetReadOnly(true);
}

//tab 控件初始化
void CMagic_LightCubeDlg::ChildWindowInit(){
	CRect tabRect;//(24,1,-1,-1);
	m_tab.InsertItem(0, _T("Animation"));
	m_tab.InsertItem(1, _T("Music"));
	m_animationDlg.Create(IDD_ANIMATION_DIALOG,&m_tab);
	m_musicDlg.Create(IDD_MUSIC_DIALOG,&m_tab);
	m_tab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect 
	tabRect.left += 1;                  
    tabRect.right -= 1;   
    tabRect.top += 23;   
    tabRect.bottom -= 1;  
	m_animationDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, 
		tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
	m_musicDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, 
		tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
	m_animationDlg.InitAnimationDlg();
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMagic_LightCubeDlg 对话框

CMagic_LightCubeDlg::CMagic_LightCubeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMagic_LightCubeDlg::IDD, pParent)
	, m_editArray(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMagic_LightCubeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ARRAY, m_editArray);
	DDX_Control(pDX, IDC_EDIT_ARRAY, m_edit);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	DDX_Control(pDX, IDC_COMBO_COM, m_combCom);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_combBaud);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_Send);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMagic_LightCubeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_ALLON, &CMagic_LightCubeDlg::OnBnClickedButtonAllon)
	ON_BN_CLICKED(IDC_BUTTON_ALLOFF, &CMagic_LightCubeDlg::OnBnClickedButtonAlloff)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMagic_LightCubeDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMagic_LightCubeDlg::OnBnClickedButtonSend)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMagic_LightCubeDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMagic_LightCubeDlg::OnBnClickedButtonTest)
	ON_MESSAGE(WM_ANIMATION_MESSAGE, &CMagic_LightCubeDlg::OnAnimationMessage)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMagic_LightCubeDlg 消息处理程序

BOOL CMagic_LightCubeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CRect rect;

	GetDlgItem(IDC_Canvas)->GetWindowRect(rect);

	ScreenToClient(rect);

	m_oglWindow.oglCreate(rect, this);

	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);

	//SetWindowText(L"Magic-LightCube");

	InitArray();         // 数组初始化
	ViewArray();         // 编辑框初始化
	Setting();           // 串口设置初始化
	EditInit();          // 编辑框字体初始化

	ChildWindowInit();   // Tab 控件初始化 

	DrawBackground(); // 画背景
	DrawAllDot();     // 画点阵

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMagic_LightCubeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMagic_LightCubeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawBackground(); // 画背景
		DrawAllDot();     // 画点阵

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMagic_LightCubeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMagic_LightCubeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PtInArea(point);     // 鼠标位置判断、显示编辑框数组、发送数据

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMagic_LightCubeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnMouseMove(nFlags, point);
}

//全点亮
void CMagic_LightCubeDlg::OnBnClickedButtonAllon()
{
	// TODO: 在此添加控件通知处理程序代码
	byte allOn[64];
	memset(allOn,0XFF,64);
	updateInterface(allOn);
}

//全熄灭
void CMagic_LightCubeDlg::OnBnClickedButtonAlloff()
{
	// TODO: 在此添加控件通知处理程序代码
	byte allOff[64];
	memset(allOff,0X00,64);
	updateInterface(allOff);
}

void CMagic_LightCubeDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,str1,n;					             //定义字符串
	GetDlgItemText(IDC_BUTTON_CONNECT,str);
	CWnd *h1;
	h1=GetDlgItem(IDC_BUTTON_CONNECT);		         //指向控件的caption

	if(!m_mscom.get_PortOpen()){
		m_combBaud.GetLBText(m_combBaud.GetCurSel(),str1);  //取得所选的字符串，并存放在str1里面
		str1=str1+','+'n'+','+'8'+','+'1';			        //这句话很关键

		m_mscom.put_CommPort((m_combCom.GetCurSel())+1);	//选择串口

		m_mscom.put_InputMode(1);			  //设置输入方式为二进制方式
		m_mscom.put_Settings(str1);		      //波特率为（波特率组Á合框）无校验，8数据位，1个停止位
		m_mscom.put_InputLen(1024);		      //设置当前接收区数据长度为1024
		m_mscom.put_RThreshold(1);			  //缓冲区一个字符引发事件
		m_mscom.put_RTSEnable(1);			  //设置RT允许

		m_mscom.put_PortOpen(true);		      //打开串口
		m_Send.EnableWindow(true);            //Send按钮有效
		m_combBaud.EnableWindow(false);       //波特率选择框无效
		m_combCom.EnableWindow(false);        //COM口选择框无效
		Flag_send = TRUE;					  //串口连接 同步输出数据
		if(m_mscom.get_PortOpen()){
			str=_T("Disconnect");
			UpdateData(true);
			h1->SetWindowText(str);			  //改变按钮名称为"Disconnect"
		}		
	}else{
		m_mscom.put_PortOpen(false);
		m_Send.EnableWindow(false);			  //Send按钮无效
		m_combBaud.EnableWindow(true);		  //波特率选择框有效
		m_combCom.EnableWindow(true);         //COM口选择框有效
		Flag_send = FALSE;					  //未连接串口不同步输出数组
		if(str != _T("Connect")){
			str = _T("Connect");
			UpdateData(true);
			h1->SetWindowText(str);			  //改变按钮名称为"Connect"
		}
	}
}

BEGIN_EVENTSINK_MAP(CMagic_LightCubeDlg, CDialogEx)
	ON_EVENT(CMagic_LightCubeDlg, IDC_MSCOMM1, 1, CMagic_LightCubeDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMagic_LightCubeDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	if(m_mscom.get_CommEvent()==2){
		char str[1024]={0};
		long k;
		VARIANT InputData=m_mscom.get_Input();	//读缓冲区
		COleSafeArray fs;
		fs=InputData;							//VARIANT型变À量转换为COleSafeArray型变量
		for(k=0;k<((LONG)fs.GetOneDimSize());k++)
		{
			fs.GetElement(&k,str+k);			//转换为BYTE型数组
		}
		//m_EditReceive += str;					//接收到编辑框里面
		//UpdateData(false);

		//m_Edit.SetSel(-1,-1);
		//this->SetDlgItemTextW(IDC_EDIT1,m_EditReceive);  //将m_EditReceive内容显示到ID为IDC_EDIT1的编辑框的最后位置
		//m_Edit.LineScroll(m_Edit.GetLineCount()-1,0);    ////将垂直滚动条滚动到最后一行
	}
}

//发送数据
void CMagic_LightCubeDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	SendData();
}

//tab 选项卡改变
void CMagic_LightCubeDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;													// 标签控件客户区的Rect   
  
    // 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 24;   
    tabRect.bottom -= 1; 

	switch(m_tab.GetCurSel())
	{
	case 0:
		//选择标签Animation ，隐藏Music 对话框，显示Animation对话框
		m_animationDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
		m_musicDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
		break;
	case 1:
		//选择标签Music ，隐藏Animation 对话框，显示Music对话框
		m_animationDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_musicDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
		::SendMessage(m_animationDlg,WM_TEST_MESSAGE,NULL,-1);  //切换tab选项卡 发送消息至子对话框
		//AfxMessageBox(L"TAB");
		break;
	default:
		break;
	}
}

//测试按键（不显示）
void CMagic_LightCubeDlg::OnBnClickedButtonTest(){
	// TODO: 在此添加控件通知处理程序代码
}

//清屏
void CMagic_LightCubeDlg::cleanInterface()
{
	//这里写上创建线程做什么的函数
	byte cleaner[64];
	memset(cleaner, 0x00, 64);
	ViewTheArray(cleaner);
	Hex2Bin(cleaner);
	DrawAllDot();
	SendData();
}

//更新主屏幕
void CMagic_LightCubeDlg::updateInterface(byte* x)
{
	//这里写上创建线程做什么的函数
	ViewTheArray(x);
	Hex2Bin(x);
	DrawAllDot();
	SendData();
}

// 子窗口 Animation 消息接收函数
LRESULT CMagic_LightCubeDlg::OnAnimationMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: 处理用户自定义消息 

	//CString *str=(CString*) wParam;

	CString lp;
	double* a=(double*)lParam;
	lp.Format(L"%d",a);

	switch(lParam){
	case -3:
		updateInterface((byte*) wParam);
		break;
	case -2:
		::SendMessage(m_animationDlg,WM_TEST_MESSAGE,(WPARAM)(&hex_array),0);
		break;
	case -1:
		cleanInterface();    //	全局清0
		break;
	case 0:
		updateInterface((byte*) wParam);
		break;
	default:
		updateInterface((byte*) wParam);
		break;
	}
	return 0;
}

//强制退出函数
void CMagic_LightCubeDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
	CDialogEx::OnClose();
}