// SaveNameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Magic_LightCube.h"
#include "SaveNameDlg.h"
#include "afxdialogex.h"


// CSaveNameDlg 对话框

IMPLEMENT_DYNAMIC(CSaveNameDlg, CDialogEx)

CSaveNameDlg::CSaveNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaveNameDlg::IDD, pParent)
	, m_saveName(_T(""))
{

}

CSaveNameDlg::~CSaveNameDlg()
{
}

void CSaveNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_saveName);
}


BEGIN_MESSAGE_MAP(CSaveNameDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CSaveNameDlg::OnEnChangeEditName)
END_MESSAGE_MAP()


// CSaveNameDlg 消息处理程序

//返回编辑框内容
CString CSaveNameDlg::GetSaveName(){
	return m_saveName;
}

//清空编辑框内容
void CSaveNameDlg::ClearSaveName(){
	m_saveName = L"";
}

void CSaveNameDlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
