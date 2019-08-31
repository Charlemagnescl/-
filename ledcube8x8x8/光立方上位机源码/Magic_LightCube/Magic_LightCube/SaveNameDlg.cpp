// SaveNameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Magic_LightCube.h"
#include "SaveNameDlg.h"
#include "afxdialogex.h"


// CSaveNameDlg �Ի���

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


// CSaveNameDlg ��Ϣ�������

//���ر༭������
CString CSaveNameDlg::GetSaveName(){
	return m_saveName;
}

//��ձ༭������
void CSaveNameDlg::ClearSaveName(){
	m_saveName = L"";
}

void CSaveNameDlg::OnEnChangeEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
