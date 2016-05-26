
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <afxtempl.h>
#include "WDXmlParser.h"
#include "MemDC.h"
#include "SubChildDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CoInitialize(NULL);
//	_bVisible = FALSE; // use this to hide the dialog on start
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PICTURE_CTRL, m_picCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(1000, 5000, ButtonPressed)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CString CMFCApplication1Dlg::GetExeFolderPath()
{
	TCHAR AppNameTChar[MAX_PATH];
	GetModuleFileName(NULL, AppNameTChar, MAX_PATH);
	CString AppName = AppNameTChar;
	int nIndex = AppName.ReverseFind(_T('\\'));
	if (nIndex > 0)
	{
		AppName = AppName.Left(nIndex);
		AppName += '\\';
	}
	return AppName;
}

void CMFCApplication1Dlg::ButtonPressed(UINT nID)
{
	CString strExeFolderPath = GetExeFolderPath();
	strExeFolderPath.Append(L"new 11.xml");
	
	CRect rcBtnSzie;
	m_FirstNodeBtn->GetWindowRect(&rcBtnSzie);
	CRect rcLocal = m_rcFirstNode;
	CWDXmlParser        xmlParser;
	xmlParser.LoadXmlFile(strExeFolderPath);
	CString wszPhyDoc = xmlParser.GetNodeTagText(L"Teams", 1, L"Part");
	int iButtonCount = _wtoi(wszPhyDoc.GetBuffer());
	for (int iCount = 0; iCount < iButtonCount; iCount++)
	{
		CString wszPhyDocTeamName = xmlParser.GetNodeTagText(_T("Teams"), iCount + 1, _T("TeamName"));
		CString wszPhyDocTeamBtnId = xmlParser.GetNodeTagText(_T("Teams"), iCount + 1, _T("TeamBtnId"));
		if (_wtoi(wszPhyDocTeamBtnId.GetBuffer()) == nID)
		{
			CSubChildDialog subDlgObj;
			subDlgObj.SetSubChildButtonInformation(nID, wszPhyDocTeamName, xmlParser);
			subDlgObj.DoModal();
		}
	}
		/*
		m_FirstNodeBtn = new CDynamicButton();
		if (iCount == 0)
		{
			rcLocal.left = rcBtnSzie.left;
			rcLocal.top = rcBtnSzie.top;
			rcLocal.right = rcLocal.left + 80;
			rcLocal.bottom = rcLocal.top + 80;

			m_FirstNodeBtn->Create(wszPhyDocTeamName, WS_CHILD | WS_VISIBLE | BS_FLAT,
				CRect(rcLocal.left, rcLocal.top, rcLocal.right, rcLocal.bottom), this, _wtoi(wszPhyDocTeamBtnId.GetBuffer()));
			::MoveWindow(m_FirstNodeBtn->m_hWnd, rcLocal.left - 150, rcLocal.top , 90, 90, TRUE);
		}
		else if (iCount == 1)
		{
			rcLocal.left = rcBtnSzie.left;
			rcLocal.top = rcBtnSzie.top;
			rcLocal.right = rcLocal.left + 80;
			rcLocal.bottom = rcLocal.top + 80;

			m_FirstNodeBtn->Create(wszPhyDocTeamName, WS_CHILD | WS_VISIBLE | BS_FLAT,
				CRect(rcLocal.left, rcLocal.top, rcLocal.right, rcLocal.bottom), this, _wtoi(wszPhyDocTeamBtnId.GetBuffer()));
			::MoveWindow(m_FirstNodeBtn->m_hWnd, rcLocal.left, rcLocal.top - 150, 90, 90, TRUE);
			
		}
		else if (iCount == 2)
		{
			rcLocal.left = rcBtnSzie.left;
			rcLocal.top = rcBtnSzie.top;
			rcLocal.right = rcLocal.left + 80;
			rcLocal.bottom = rcLocal.top + 80;

			m_FirstNodeBtn->Create(wszPhyDocTeamName, WS_CHILD | WS_VISIBLE | BS_FLAT,
				CRect(rcLocal.left, rcLocal.top, rcLocal.right, rcLocal.bottom), this, _wtoi(wszPhyDocTeamBtnId.GetBuffer()));
			::MoveWindow(m_FirstNodeBtn->m_hWnd, rcBtnSzie.right + 150, rcLocal.top, 90, 90, TRUE);
		}
		else if (iCount == 3)
		{
			m_FirstNodeBtn->Create(wszPhyDocTeamName, WS_CHILD | WS_VISIBLE | BS_FLAT,
				CRect(rcLocal.left, rcLocal.top, rcLocal.right, rcLocal.bottom), this, _wtoi(wszPhyDocTeamBtnId.GetBuffer()));
			::MoveWindow(m_FirstNodeBtn->m_hWnd, rcLocal.left, rcLocal.bottom + 150, 90, 90, TRUE);
		}
		else
		{
			// do nothing
		}
	}*/
	//CString wszTitle3 = xmlParser.GetNodeTagText("Teams", 1, "TeamName",  "SubTeammember", 1);
	//CString wszTitle4 = xmlParser.GetNodeTagText("Teams", 1, "Position", "SubTeammember", 1);
	//CString wszTitle1 = xmlParser.GetNodeTagText("Teams", 2, "TeamName");
	//CString wszTitle2 = xmlParser.GetNodeTagText(L"Teams", 3, L"TeamName");

	/*CString s;
	GetDlgItem((int)nID)->GetWindowText(s);
	// TODO: Add extra initialization here
	if (s.Compare(L"Physician Doc") == 0)
	{
		GetDlgItem((int)nID)->ShowWindow(SW_HIDE);

		CRect rcBtnSzie;
		CRect rcLocal = m_rcFirstNode;
		rcBtnSzie.left = 180;
		rcBtnSzie.top = 180;
		for (int i = 1; i < 4; i++)
		{
			++nID;
			rcLocal.left = rcBtnSzie.left;
			rcLocal.top = rcBtnSzie.top;
			rcLocal.right = rcLocal.top + 80;
			rcLocal.bottom = rcLocal.left + 50;
			m_FirstNodeBtn = new CDynamicButton();
			m_FirstNodeBtn->Create(_T("Prabhat Singh"), WS_CHILD | WS_VISIBLE | BS_FLAT,
				CRect(rcLocal.left, rcLocal.top, rcLocal.right, rcLocal.bottom), this, nID);

			::MoveWindow(m_FirstNodeBtn->m_hWnd, rcLocal.left + 150, rcLocal.top + 140, 140, 140, TRUE);
			rcBtnSzie.left = 180 * (i + 2);
			//rcBtnSzie.top = 180 * (i + 1);

			m_FirstNodeBtn->ShowWindow(SW_SHOW);
		}
	}
	*/
	//TRACE("BUTTON %d was pressed [%s]\n", w, s);

	//return 0;
}

// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int iPrimaryBtnId = 1001;
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	//Creating a Tooltip
	_ToolTipCtrl.Create(this,
		TTS_NOPREFIX | 
		TTS_BALLOON  |
		TTS_ALWAYSTIP
		);

	// Get the owner window and dialog box rectangles. 

	HWND hwndOwner;
	CRect rc, rcDlg, rcOwner, rcClientDlg;

	if ((hwndOwner = ::GetParent(m_hWnd)) == NULL)
	{
		hwndOwner = ::GetDesktopWindow();
	}
	
	::GetWindowRect(hwndOwner, &rcOwner);
	::GetWindowRect(m_hWnd, &rcDlg);
	
//	CopyRect(&rc, &rcOwner);

	// Offset the owner and dialog box rectangles so that right and bottom 
	// values represent the width and height, and then offset the owner again 
	// to discard space taken up by the dialog box. 

//	OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
//	OffsetRect(&rc, -rc.left, -rc.top);
//	OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

	::MoveWindow(m_hWnd, 0, 0, rcOwner.right, rcOwner.bottom - 50, TRUE);

	// Set the position of Cancel button.
	HWND hWndCanCel = ::GetDlgItem(m_hWnd, IDCANCEL);
	::MoveWindow(hWndCanCel, rcOwner.right - 150, rcOwner.bottom - 200, 90 ,40, TRUE);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rcFirstNode;
	rcFirstNode.left = rcOwner.right / 2;
	rcFirstNode.top = rcOwner.bottom / 2;
	rcFirstNode.right = rcOwner.right / 2 + 45;
	rcFirstNode.bottom = rcOwner.bottom / 2 + 45;

	m_FirstNodeBtn = new CDynamicButton();
	// TODO: Add extra initialization here
	m_FirstNodeBtn->Create(_T("Physiciandocument"), WS_CHILD | WS_VISIBLE | BS_FLAT,
		CRect(rcFirstNode.left, rcFirstNode.top, rcFirstNode.right, rcFirstNode.bottom), this, iPrimaryBtnId);

	::MoveWindow(m_FirstNodeBtn->m_hWnd, rcFirstNode.left, rcFirstNode.top, 90, 90, TRUE);

	m_FirstNodeBtn->ShowWindow(SW_SHOW);

	CString strExeFolderPath = GetExeFolderPath();
	strExeFolderPath.Append(L"new 11.xml");

	CRect rcBtnSzie;
	m_FirstNodeBtn->GetWindowRect(&rcBtnSzie);
	CRect rcLocal = m_rcFirstNode;
	CWDXmlParser        xmlParser;
	xmlParser.LoadXmlFile(strExeFolderPath);
	CString wszPhyDoc = xmlParser.GetNodeTagText(L"Teams", 1, L"Part");
	int iNumberOfBtn = _wtoi(wszPhyDoc.GetBuffer());
	CDynamicButton dynBtnObj;
	int iCount = 0;
	for (iCount = 0; iCount < iNumberOfBtn; iCount++)
	{
		CString wszPhyDocTeamName = xmlParser.GetNodeTagText(_T("Teams"), iCount + 1, _T("TeamName"));
		CString wszPhyDocTeamBtnId = xmlParser.GetNodeTagText(_T("Teams"), iCount + 1, _T("TeamBtnId"));
		int iCtrlBtnId = _wtoi(wszPhyDocTeamBtnId.GetBuffer());
		m_FirstNodeBtn = new CDynamicButton();
		m_FirstNodeBtn->Create(wszPhyDocTeamName, WS_CHILD | WS_VISIBLE | BS_FLAT,
			CRect(0, 0, 0, 0), this, iCtrlBtnId);
		dynBtnObj.SetBaseButton(m_FirstNodeBtn->m_hWnd, wszPhyDocTeamName, iNumberOfBtn, iCount + 1, rcFirstNode, rcOwner);
		m_FirstNodeBtn->ShowWindow(SW_SHOW);
		m_iBtnCtrlIdmap.insert(std::pair<int, int>(iCount, iCtrlBtnId));

		if (SetIconAndTitleForBalloonTip(&_ToolTipCtrl, TTI_INFO, _T("Physician doc")))
		{
			//register tools with the ToolTip control
			_ToolTipCtrl.AddTool(GetDlgItem(iCtrlBtnId), wszPhyDocTeamName);
			_ToolTipCtrl.AddTool(GetDlgItem(IDCANCEL), _T("Close the application."));
			//_ToolTipCtrl.AddTool(GetDlgItem(IDC_STATIC_TEXT), _T("balloon on STATIC\n(don't forget to add <Notify> to StaticCtrl Styles)"));
		}
		else
		{
			//......
		}
	}
	m_iBtnCtrlIdmap.insert(std::pair<int, int>(iCount + 1, iPrimaryBtnId));
	_ToolTipCtrl.AddTool(GetDlgItem(iPrimaryBtnId), L"Physician Document");
	//CopyRect(&m_rcFirstNode, &rcFirstNode);
	
	// Load jpg image on dialog.
//	HWND hWndStaticPictureCtrl = ::GetDlgItem(m_hWnd, IDC_STATIC_PICTURE_CTRL);
//	::MoveWindow(hWndStaticPictureCtrl, 10, 10, rcOwner.right, rcOwner.bottom, TRUE);
//	m_picCtrl.Load(CString(_T("Pic4.jpg")));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CMFCApplication1Dlg::SetIconAndTitleForBalloonTip(CToolTipCtrl *pToolTipCtrl, int tti_ICON, CString title)
{
	return ::SendMessage((HWND)pToolTipCtrl->m_hWnd,
		(UINT)TTM_SETTITLE, // Adds a standard icon and title string to a ToolTip    
		(WPARAM)tti_ICON,
		(LPARAM)(LPCTSTR)title);
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	RECT rcOwner;
	HWND	hwndOwner = ::GetDesktopWindow();
	::GetWindowRect(hwndOwner, &rcOwner);
	MoveWindow(0, 0, rcOwner.right, rcOwner.bottom, TRUE);
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, 900, 900);

	// TODO: Add your message handler code here
}


// gets the actual drawing location of a control relative to the dialog frame
CRect CMFCApplication1Dlg::ComputeDrawingRect(int control_id)
{
	CRect r;
	GetDlgItem(control_id)->GetWindowRect(&r);
	ScreenToClient(&r);

	return r;
}

#define SHADOW_WIDTH 6  
// draws the actual shadow
void CMFCApplication1Dlg::DrawShadow(CDC* pDC, CRect &r)
{
	DWORD dwBackgroundColor = GetSysColor(COLOR_BTNFACE);
	DWORD dwDarkestColor = RGB(GetRValue(dwBackgroundColor) / 2,
		GetGValue(dwBackgroundColor) / 2,
		GetBValue(dwBackgroundColor) / 2); // dialog background halftone as base color for shadow
	int nOffset;
	for (nOffset = SHADOW_WIDTH; nOffset > 0; nOffset--)
	{
		DWORD dwCurrentColorR = (GetRValue(dwDarkestColor)*(SHADOW_WIDTH - nOffset)
			+ GetRValue(dwBackgroundColor)*nOffset) / SHADOW_WIDTH;
		DWORD dwCurrentColorG = (GetGValue(dwDarkestColor)*(SHADOW_WIDTH - nOffset)
			+ GetGValue(dwBackgroundColor)*nOffset) / SHADOW_WIDTH;
		DWORD dwCurrentColorB = (GetBValue(dwDarkestColor)*(SHADOW_WIDTH - nOffset)
			+ GetBValue(dwBackgroundColor)*nOffset) / SHADOW_WIDTH;
		pDC->FillSolidRect(r + CPoint(nOffset, nOffset), RGB(dwCurrentColorR, dwCurrentColorG, dwCurrentColorB));
	}
}


BOOL CMFCApplication1Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// draw dialog background
	CRect rdlg;
	GetClientRect(&rdlg);
	DWORD dwBackgroundColor = GetSysColor(COLOR_BTNFACE);
	pDC->FillSolidRect(rdlg, dwBackgroundColor);

	// draw shadows
	CRect r1, r2;
	std::map<int, int>::iterator it;
	for (it = m_iBtnCtrlIdmap.begin(); it != m_iBtnCtrlIdmap.end(); ++it)
	{
		r1 = ComputeDrawingRect(it->second);
		DrawShadow(pDC, r1);
	}
	r2 = ComputeDrawingRect(IDCANCEL);
	// DrawShadow(pDC, r3);
	DrawShadow(pDC, r2);
	return TRUE;
}

BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEMOVE)
	{
		_ToolTipCtrl.RelayEvent(pMsg); // pass the mouse message to the ToolTip control for processing
	}

	// NO ESCAPE or RETURN key	
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN ||
			pMsg->wParam == VK_ESCAPE)
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);

			return TRUE;				// DO NOT process further
		}
	}

	// NO ALT+ key
	if (pMsg->message == WM_SYSCOMMAND)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}