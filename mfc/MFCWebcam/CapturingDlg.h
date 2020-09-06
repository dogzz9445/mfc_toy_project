#pragma once

#include "Webcam.h"
// CCapturingDlg dialog

class CCapturingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCapturingDlg)

public:
	CCapturingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCapturingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPTURING_DIALOG };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  virtual BOOL OnInitDialog();
  afx_msg void OnDestroy();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
  CStatic mPCPicture;
  CButton mBCapture;
  CButton mBRecapture;
  CButton mBRegister;

  CWebcam mCamera;
  afx_msg void OnBnClickedBtCaptureCapturing();
  afx_msg void OnBnClickedBtRecaptureCapturing();
  afx_msg void OnBnClickedBtRegisterCapturing();
};
