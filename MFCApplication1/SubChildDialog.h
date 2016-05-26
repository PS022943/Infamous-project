#pragma once

#include "DynamicButton.h"
#include "WDXmlParser.h"
#include "WndShadow.h"
#include <map>

// CSubChildDialog dialog

class CSubChildDialog : public CDialog
{
	DECLARE_DYNAMIC(CSubChildDialog)

public:
	CSubChildDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubChildDialog();

// Dialog Data
	enum { IDD = IDD_SUBCHILDDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SubButtonPressed(UINT nID);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CDynamicButton* m_SubChildNodeBtn;
	void SetSubChildButtonInformation(UINT nBtnId, CString strButtonName, CWDXmlParser xmlParser);
private:
	UINT m_nBtnId;
	CString m_strButtonName;
	CString GetExeFolderPath();
	int		m_nColorB;
	int		m_nColorG;
	int		m_nColorR;
	int		m_nSize;
	int		m_nSharpness;
	int		m_nDarkness;
	int		m_nPosX;
	int		m_nPosY;
	CWndShadow m_Shadow;
	CRect ComputeDrawingRect(int control_id);   // <-- !!!
	void DrawShadow(CDC* pDC, CRect &r);        // <-- !!!
	CRect m_rcDlg;
	std::map<int, int> m_iBtnCtrlIdmap;
//	CWDXmlParser m_wdXmlParser;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CToolTipCtrl   _ToolTipCtrl;
	NOTIFYICONDATA _tnd;
	BOOL           _bVisible;

	BOOL SetIconAndTitleForBalloonTip(CToolTipCtrl *pToolTipCtrl,
		int          tti_ICON,
		CString      title);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
