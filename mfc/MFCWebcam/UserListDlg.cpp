// CUserListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCWebcam.h"
#include "UserListDlg.h"
#include "afxdialogex.h"

#include "UserDAO.h"

// CUserListDlg dialog

IMPLEMENT_DYNAMIC(CUserListDlg, CDialogEx)

CUserListDlg::CUserListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERLIST_DIALOG, pParent)
{
}

CUserListDlg::~CUserListDlg()
{
}

void CUserListDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LC_USERLIST, mLCUser);
}


BEGIN_MESSAGE_MAP(CUserListDlg, CDialogEx)
  ON_BN_CLICKED(IDC_BTN_REFRESH_USERLIST, &CUserListDlg::OnBnClickedBtnRefreshUserlist)
  ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUserListDlg message handlers


void CUserListDlg::OnBnClickedBtnRefreshUserlist()
{
  // TODO: Add your control notification handler code here

  SelectAll();
}


BOOL CUserListDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // TODO:  Add extra initialization here
  mLCUser.CreateHead();
  SelectAll();

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CUserListDlg::OnDestroy()
{
  CDialogEx::OnDestroy();

  // TODO: Add your message handler code here
}


BOOL CUserListDlg::SelectAll()
{
  UserDAO dao;
  std::vector<CUser> users = dao.SelectAll();
  size_t size = users.size();
  mLCUser.CreateBody(users);

  return TRUE;
}

int CUserListDlg::GetSelectedItem()
{
  
  return mLCUser.GetNextItem(-1, LVNI_SELECTED);
}

