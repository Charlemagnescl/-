#pragma once

// CSaveNameDlg �Ի���

class CSaveNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveNameDlg)

public:
	CSaveNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSaveNameDlg();

// �Ի�������
	enum { IDD = IDD_SAVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_saveName;
	CString GetSaveName();
	void ClearSaveName();
	afx_msg void OnEnChangeEditName();
};
