// SubChildDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "SubChildDialog.h"
#include "afxdialogex.h"


// CSubChildDialog dialog

IMPLEMENT_DYNAMIC(CSubChildDialog, CDialog)

CSubChildDialog::CSubChildDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSubChildDialog::IDD, pParent)
{

}

CSubChildDialog::~CSubChildDialog()
{
}

void CSubChildDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubChildDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CSubChildDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSubChildDialog::OnBnClickedCancel)
	ON_COMMAND_RANGE(1000, 5000, SubButtonPressed)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSubChildDialog message handlers

void CSubChildDialog::SubButtonPressed(UINT nID)
{
	CString strExeFolderPath = GetExeFolderPath();
	strExeFolderPath.Append(L"new 11.xml");

	//CRect rcBtnSzie;
	///m_FirstNodeBtn->GetWindowRect(&rcBtnSzie);
	//CRect rcLocal = m_rcFirstNode;
	CWDXmlParser        xmlParser;
	xmlParser.LoadXmlFile(strExeFolderPath);
	CString wszPhyDoc = xmlParser.GetNodeTagText(L"Teams", 1, L"Part");
	int iButtonCount = _wtoi(wszPhyDoc.GetBuffer());
	for (int iCount = 0; iCount < iButtonCount; iCount++)
	{
		CString wszPhyDocTeamUrl = xmlParser.GetNodeTagText(L"Teams", 1, L"Url", L"Project", iCount + 1);
		CString wszPhyDocTeamBtnId = xmlParser.GetNodeTagText(L"Teams", 1, L"SubTeamBtnId", L"Project", iCount + 1);
		if (_wtoi(wszPhyDocTeamBtnId.GetBuffer()) == nID)
		{
			ShellExecute(0, 0, L"iexplore.exe", wszPhyDocTeamUrl, 0, SW_SHOW);
		}
	}

}

void CSubChildDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CSubChildDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}


CString CSubChildDialog::GetExeFolderPath()
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

BOOL CSubChildDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Creating a Tooltip
	_ToolTipCtrl.Create(this,
		TTS_NOPREFIX |
		TTS_BALLOON  | 
		TTS_ALWAYSTIP);

	HWND hwndOwner;
	CRect rc, rcOwner, rcClientDlg;

	if ((hwndOwner = ::GetParent(m_hWnd)) == NULL)
	{
		hwndOwner = ::GetDesktopWindow();
	}

	::GetWindowRect(hwndOwner, &rcOwner);
	
	m_rcDlg.left = rcOwner.right / 6;
	m_rcDlg.right = m_rcDlg.left * 4;
	m_rcDlg.top = rcOwner.bottom / 6;
	m_rcDlg.bottom = m_rcDlg.top * 4;
	::MoveWindow(m_hWnd, m_rcDlg.left, m_rcDlg.top, m_rcDlg.right, m_rcDlg.bottom, TRUE);

	// Set the position of Cancel button.
	HWND hWndCanCel = ::GetDlgItem(m_hWnd, IDCANCEL);
	::MoveWindow(hWndCanCel, m_rcDlg.right - 140, m_rcDlg.bottom - 100, 90, 40, TRUE);

	CRect rcSubChildNodeBtn;
	rcSubChildNodeBtn.left = m_rcDlg.right / 2 - 45;
	rcSubChildNodeBtn.top = m_rcDlg.bottom / 2 - 45;
	rcSubChildNodeBtn.right = m_rcDlg.right / 2 + 45;
	rcSubChildNodeBtn.bottom = m_rcDlg.bottom / 2 + 45;

	m_SubChildNodeBtn = new CDynamicButton();
	// TODO: Add extra initialization here
	m_SubChildNodeBtn->Create(m_strButtonName, WS_CHILD | WS_VISIBLE | BS_FLAT,
		CRect(rcSubChildNodeBtn.left, rcSubChildNodeBtn.top, rcSubChildNodeBtn.right, rcSubChildNodeBtn.bottom), this, m_nBtnId);

	::MoveWindow(m_SubChildNodeBtn->m_hWnd, rcSubChildNodeBtn.left, rcSubChildNodeBtn.top, 90, 90, TRUE);

	m_SubChildNodeBtn->ShowWindow(SW_SHOW);

	CString strExeFolderPath = GetExeFolderPath();
	strExeFolderPath.Append(L"new 11.xml");
	CWDXmlParser xmlParser;
	xmlParser.LoadXmlFile(strExeFolderPath);
	CString wszPhyDoc = xmlParser.GetNodeTagText(L"Teams", 1, L"Part");

	int iNumberOfBtn = _wtoi(wszPhyDoc.GetBuffer());
	CDynamicButton dynBtnObj;
	for (int iCount = 0; iCount < iNumberOfBtn; iCount++)
	{
		CString wszPhyDocTeamName = xmlParser.GetNodeTagText(L"Teams", 1, L"SubName", L"Project", iCount + 1);
		CString wszPhyDocTeamBtnId = xmlParser.GetNodeTagText(L"Teams", 1, L"SubTeamBtnId", L"Project", iCount + 1);
		int iCtrlBtnId = _wtoi(wszPhyDocTeamBtnId.GetBuffer());
		m_SubChildNodeBtn = new CDynamicButton();
		m_SubChildNodeBtn->Create(wszPhyDocTeamName, WS_CHILD | WS_VISIBLE | BS_FLAT,
			CRect(0, 0, 0, 0), this, iCtrlBtnId);
		dynBtnObj.SetBaseButton(m_SubChildNodeBtn->m_hWnd, wszPhyDocTeamName, iNumberOfBtn, iCount + 1, rcSubChildNodeBtn, m_rcDlg);
		m_SubChildNodeBtn->ShowWindow(SW_SHOW);
		m_iBtnCtrlIdmap.insert(std::pair<int, int>(iCount, iCtrlBtnId));

		if (SetIconAndTitleForBalloonTip(&_ToolTipCtrl, TTI_INFO, m_strButtonName))
		{
			//register tools with the ToolTip control
			_ToolTipCtrl.AddTool(GetDlgItem(iCtrlBtnId), wszPhyDocTeamName);
			_ToolTipCtrl.AddTool(GetDlgItem(IDCANCEL), _T("Close the application."));
		}
		else
		{
			//......
		}
	}

	_ToolTipCtrl.AddTool(GetDlgItem(m_nBtnId), m_strButtonName);

	// Set WS_EX_LAYERED on this window 
	SetWindowLong(m_hWnd,
		GWL_EXSTYLE,
		GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Make this window 70% alpha
	::SetLayeredWindowAttributes(m_hWnd, 0, (255 * 90) / 100, LWA_ALPHA);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CSubChildDialog::SetSubChildButtonInformation(UINT nBtnId, CString strButtonName, CWDXmlParser xmlParser)
{
	m_strButtonName = strButtonName;
	m_nBtnId = nBtnId;
}


// gets the actual drawing location of a control relative to the dialog frame
CRect CSubChildDialog::ComputeDrawingRect(int control_id)
{
	CRect r;
	GetDlgItem(control_id)->GetWindowRect(&r);
	ScreenToClient(&r);

	return r;
}

#define SHADOW_WIDTH 6  
// draws the actual shadow
void CSubChildDialog::DrawShadow(CDC* pDC, CRect &r)
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


BOOL CSubChildDialog::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// draw dialog background
	CRect rdlg;
	GetClientRect(&rdlg);
	DWORD dwBackgroundColor = GetSysColor(COLOR_BTNFACE);
	pDC->FillSolidRect(rdlg, dwBackgroundColor);

	// draw shadows
	CRect r1, r2, r3;
	std::map<int, int>::iterator it;
	for (it = m_iBtnCtrlIdmap.begin(); it != m_iBtnCtrlIdmap.end(); ++it)
	{
		r1 = ComputeDrawingRect(it->second);
		DrawShadow(pDC, r1);
	}
	r2 = ComputeDrawingRect(IDCANCEL);
	r3 = ComputeDrawingRect(m_nBtnId);
	
	DrawShadow(pDC, r3);
	DrawShadow(pDC, r2);
	return TRUE;
}

BOOL CSubChildDialog::PreTranslateMessage(MSG* pMsg)
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

BOOL CSubChildDialog::SetIconAndTitleForBalloonTip(CToolTipCtrl *pToolTipCtrl, int tti_ICON, CString title)
{
	return ::SendMessage((HWND)pToolTipCtrl->m_hWnd,
		(UINT)TTM_SETTITLE, // Adds a standard icon and title string to a ToolTip    
		(WPARAM)tti_ICON,
		(LPARAM)(LPCTSTR)title);
}