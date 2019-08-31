// MusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Magic_LightCube.h"
#include "MusicDlg.h"
#include "afxdialogex.h"

CRect rect_music;  // 白色背景区域 

// CMusicDlg 对话框

IMPLEMENT_DYNAMIC(CMusicDlg, CDialogEx)

CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicDlg::IDD, pParent)
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_MUSIC, m_musicStatic);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMusicDlg 消息处理程序


void CMusicDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	GetClientRect(rect_music);
	dc.Rectangle(rect_music);
	dc.FillSolidRect(rect_music,RGB(255,255,255));

	CFont font;
	font.CreatePointFont(150,_T("宋体"),NULL);
	GetDlgItem(IDC_STATIC_MUSIC)->SetFont(&font);
}

//背景透明 代码
HBRUSH CMusicDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID()==IDC_STATIC_MUSIC)//你的控件ID
	{
		//pDC->SetTextColor(RGB(0,0,0));                 //设置字体颜色
		pDC->SetBkMode(TRANSPARENT);					     //设置字体背景为透明
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);    // 设置背景色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

