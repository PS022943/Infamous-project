
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "DynamicButton.h"
#include "PictureCtrl.h"
#include <map>
#include "ConstantUtil.h"

struct PHYSDOC_INFORMATION
{
	CString strTeamName;
	CString strUrlInformation;
	CString ImageLocation;
};

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor
	~CMFCApplication1Dlg(){
		CoUninitialize();
	}
// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

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
	afx_msg void OnBnClickedOk();
	CArray<long, long> lNumbers;
	CArray<long, long> lObjects;
	CArray<LONG_PTR, LONG_PTR> lObjectsPtr;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDynamicButton* m_FirstNodeBtn;
	void ButtonPressed(UINT nID);
	CRect m_rcFirstNode;
	CPictureCtrl m_picCtrl;
	CString GetExeFolderPath();
	PHYSDOC_INFORMATION PhyscDocStruct;
	BUTTONLIST m_PhysDoc_Informationmap;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CRect ComputeDrawingRect(int control_id);   // <-- !!!
	void DrawShadow(CDC* pDC, CRect &r);        // <-- !!!
	CRect m_rcDlg;
	std::map<int, int> m_iBtnCtrlIdmap;
	CToolTipCtrl   _ToolTipCtrl;
	NOTIFYICONDATA _tnd;
	BOOL           _bVisible;

	BOOL SetIconAndTitleForBalloonTip(CToolTipCtrl *pToolTipCtrl,
		int          tti_ICON,
		CString      title);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
