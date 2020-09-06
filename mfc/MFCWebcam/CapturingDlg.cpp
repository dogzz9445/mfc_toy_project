// CCapturingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCWebcam.h"
#include "CapturingDlg.h"
#include "afxdialogex.h"


#define TIMER_CAPTURING 1000

// CCapturingDlg dialog

IMPLEMENT_DYNAMIC(CCapturingDlg, CDialogEx)

CCapturingDlg::CCapturingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAPTURING_DIALOG, pParent)
{

}

CCapturingDlg::~CCapturingDlg()
{
}

void CCapturingDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PC_PICTURE_CAPTURING, mPCPicture);
  DDX_Control(pDX, IDC_BT_CAPTURE_CAPTURING, mBCapture);
  DDX_Control(pDX, IDC_BT_RECAPTURE_CAPTURING, mBRecapture);
  DDX_Control(pDX, IDC_BT_REGISTER_CAPTURING, mBRegister);
}

BOOL CCapturingDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  RECT r;
  mPCPicture.GetClientRect(&r);
  if (!mCamera.Init(cv::Size(r.right, r.bottom)))
  {
    MessageBox(_T("Failed to open webcam.\n"));
  }

  SetTimer(TIMER_CAPTURING, 30, NULL);

  return TRUE;
}


BEGIN_MESSAGE_MAP(CCapturingDlg, CDialogEx)
  ON_WM_DESTROY()
  ON_WM_TIMER()
  ON_BN_CLICKED(IDC_BT_CAPTURE_CAPTURING, &CCapturingDlg::OnBnClickedBtCaptureCapturing)
  ON_BN_CLICKED(IDC_BT_RECAPTURE_CAPTURING, &CCapturingDlg::OnBnClickedBtRecaptureCapturing)
  ON_BN_CLICKED(IDC_BT_REGISTER_CAPTURING, &CCapturingDlg::OnBnClickedBtRegisterCapturing)
END_MESSAGE_MAP()


// CCapturingDlg message handlers


void CCapturingDlg::OnDestroy()
{
  CDialogEx::OnDestroy();

  // TODO: Add your message handler code here
  KillTimer(TIMER_CAPTURING);
}


void CCapturingDlg::OnTimer(UINT_PTR nIDEvent)
{
  // TODO: Add your message handler code here and/or call default
  HDC dc = ::GetDC(mPCPicture.m_hWnd);
  switch (nIDEvent)
  {
  case TIMER_CAPTURING:
    if (!mCamera.Read(dc))
    {
      MessageBox(_T("Failed to read webcam.\n"));
    }
    break;
  default:
    break;
  }
  ::ReleaseDC(mPCPicture.m_hWnd, dc);

  CDialogEx::OnTimer(nIDEvent);
}



void CCapturingDlg::OnBnClickedBtCaptureCapturing()
{
  // TODO: Add your control notification handler code here
  KillTimer(TIMER_CAPTURING);
}


void CCapturingDlg::OnBnClickedBtRecaptureCapturing()
{
  // TODO: Add your control notification handler code here
  SetTimer(TIMER_CAPTURING, 30, NULL);
}


void CCapturingDlg::OnBnClickedBtRegisterCapturing()
{
  // TODO: Add your control notification handler code here
  int nRet = IDC_BT_REGISTER_CAPTURING;
  EndDialog(nRet);

  return;
}
