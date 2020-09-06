#pragma once


#include "ListCtrlUser.h"
// CUserListDlg dialog

class CUserListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserListDlg)

public:
	CUserListDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUserListDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERLIST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedBtnRefreshUserlist();
  virtual BOOL OnInitDialog();


  CListCtrlUser mLCUser;
  BOOL SelectAll();
  int GetSelectedItem();
};
