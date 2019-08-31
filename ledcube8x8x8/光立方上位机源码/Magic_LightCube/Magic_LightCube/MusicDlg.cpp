// MusicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Magic_LightCube.h"
#include "MusicDlg.h"
#include "afxdialogex.h"

CRect rect_music;  // ��ɫ�������� 

// CMusicDlg �Ի���

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


// CMusicDlg ��Ϣ�������


void CMusicDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	GetClientRect(rect_music);
	dc.Rectangle(rect_music);
	dc.FillSolidRect(rect_music,RGB(255,255,255));

	CFont font;
	font.CreatePointFont(150,_T("����"),NULL);
	GetDlgItem(IDC_STATIC_MUSIC)->SetFont(&font);
}

//����͸�� ����
HBRUSH CMusicDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID()==IDC_STATIC_MUSIC)//��Ŀؼ�ID
	{
		//pDC->SetTextColor(RGB(0,0,0));                 //����������ɫ
		pDC->SetBkMode(TRANSPARENT);					     //�������屳��Ϊ͸��
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);    // ���ñ���ɫ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

