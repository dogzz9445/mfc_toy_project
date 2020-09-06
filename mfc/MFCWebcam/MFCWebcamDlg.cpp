
// MFCWebcamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCWebcam.h"
#include "MFCWebcamDlg.h"
#include "afxdialogex.h"

// 다이얼로그 이벤트: 버튼 클릭
#include "CapturingDlg.h"
#include "UserListDlg.h"

// DB 처리
#include "UserDAO.h"
#include "User.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCWebcamDlg dialog



CMFCWebcamDlg::CMFCWebcamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCWEBCAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCWebcamDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_STATIC_MAIN_INFO, mSTInfoMain);
  DDX_Control(pDX, IDC_CAPTURED, mPCCaptured);
  DDX_Control(pDX, IDC_EDIT_CODE, mEDCode);
  DDX_Control(pDX, IDC_EDIT_NAME, mEDName);
}

BEGIN_MESSAGE_MAP(CMFCWebcamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_CAPTURE_MAIN, &CMFCWebcamDlg::OnBnClickedCaptureMain)
  ON_BN_CLICKED(IDC_BT_REGISTER_MAIN, &CMFCWebcamDlg::OnBnClickedBtRegisterMain)
  ON_BN_CLICKED(IDC_BT_SEARCH_MAIN, &CMFCWebcamDlg::OnBnClickedBtSearchMain)
END_MESSAGE_MAP()


// CMFCWebcamDlg message handlers

BOOL CMFCWebcamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
  CFont font;
  LOGFONT lf;
  ::ZeroMemory(&lf, sizeof(lf));
  lf.lfHeight = 30;
  lf.lfWeight = FW_BOLD;
  ::lstrcpy(lf.lfFaceName, (LPCWCHAR)"사용자 등록 화면");
  font.CreateFontIndirect(&lf);
  GetDlgItem(IDC_STATIC_MAIN_INFO)->SetFont(&font);
  font.Detach();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCWebcamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCWebcamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCWebcamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//--------------------------------------------
// 버튼 이벤트
//--------------------------------------------

void CMFCWebcamDlg::OnBnClickedCaptureMain()
{
  // TODO: Add your control notification handler code here
  CCapturingDlg dlg;
  INT_PTR returnCode = -1;
  returnCode = dlg.DoModal();
  HDC dc = ::GetDC(mPCCaptured.m_hWnd);
  switch (returnCode)
  {
  case IDC_BT_REGISTER_CAPTURING:
  case IDOK:
    {
      CRect rect;
      mPCCaptured.GetClientRect(&rect);
      dlg.mCamera.Resize(cv::Size(rect.Width(), rect.Height()));
      dlg.mCamera.Draw(dc);
      mFrameUser = dlg.mCamera.getFrame();
      break;
    }
  case IDCANCEL:
    MessageBox(_T("Empty data.\n"));
    break;

  case -1:
  default:
    MessageBox(_T("ERROR.\n"));
    break;
  }
  ::ReleaseDC(mPCCaptured.m_hWnd, dc);
}

void CMFCWebcamDlg::OnBnClickedBtRegisterMain()
{
  // TODO: Add your control notification handler code here
  HDC dc = ::GetWindowDC(m_hWnd);

  CUser user;
  CString name;
  GetDlgItemText(IDC_EDIT_NAME, name);
  if (name.IsEmpty())
  {
    MessageBox(_T("이름을 입력하세요."));
    ::ReleaseDC(m_hWnd, dc);
    return;
  }
  user.setName(name);

  if (mFrameUser.empty())
  {
    MessageBox(_T("사진을 등록하세요."));
    ::ReleaseDC(m_hWnd, dc);
    return;
  }
  CString filename = GenerateFilenameBaseonTime(L"jpg");
  cv::String path((LPCSTR)IMAGE_URL + (CStringA)filename);
  cv::imwrite(path.c_str(), mFrameUser);
  user.setImgUrl(filename);
  user.setImgSize(0);

  UserDAO dao;
  CUser savedUser = dao.AddUser(user);
  CString format;
  format.Format(L"%d", savedUser.getId());
  mEDCode.SetWindowTextW((LPCTSTR)format);

  ::ReleaseDC(m_hWnd, dc);
}

void CMFCWebcamDlg::OnBnClickedBtSearchMain()
{
  // TODO: Add your control notification handler code here
  HDC dc = ::GetWindowDC(m_hWnd);

  CUserListDlg dlg;
  INT_PTR returnCode = -1;
  returnCode = dlg.DoModal();
  switch (returnCode)
  {
  case IDOK:
  {
    break;
  }
  case IDCANCEL:
    break;

  case -1:
  default:
    MessageBox(_T("ERROR.\n"));
    break;
  }

  ::ReleaseDC(m_hWnd, dc);
}


//--------------------------------------------
// Utils
//--------------------------------------------

CString CMFCWebcamDlg::GenerateFilenameBaseonTime(LPCWCHAR extention)
{
  time_t curTime = time(NULL);
  struct tm *pLocal = localtime(&curTime);
  srand(curTime);

  CString filename;
  filename.Format(L"%04d%02d%02d%02d%02d%02d_%05d.", 
    pLocal->tm_year + 1900, pLocal->tm_mon + 1, pLocal->tm_mday,
    pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec, rand() % 10000);
  filename.AppendFormat(extention);
  delete pLocal;
  return filename;
}
