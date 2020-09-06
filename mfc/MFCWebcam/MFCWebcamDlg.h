
// MFCWebcamDlg.h : header file
//

#pragma once


// CMFCWebcamDlg dialog
class CMFCWebcamDlg : public CDialogEx
{
// Construction
public:
	CMFCWebcamDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCWEBCAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  CStatic mSTInfoMain;
  CStatic mPCCaptured;
  CEdit mEDCode;
  CEdit mEDName;
  
  afx_msg void OnBnClickedCaptureMain();
  afx_msg void OnBnClickedBtRegisterMain();


  cv::Mat mFrameUser;
  CString GenerateFilenameBaseonTime(LPCWCHAR extention);
  afx_msg void OnBnClickedBtSearchMain();
};
