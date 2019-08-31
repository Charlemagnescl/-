#pragma once

// CSaveNameDlg 对话框

class CSaveNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveNameDlg)

public:
	CSaveNameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaveNameDlg();

// 对话框数据
	enum { IDD = IDD_SAVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_saveName;
	CString GetSaveName();
	void ClearSaveName();
	afx_msg void OnEnChangeEditName();
};
