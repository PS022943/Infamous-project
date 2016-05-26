#pragma once


// CDynamicButton

class CGdiPlusBitmapResource;

class CDynamicButton : public CButton
{
	DECLARE_DYNAMIC(CDynamicButton)

public:
	CDynamicButton();
	virtual ~CDynamicButton();
	void SetBaseButton(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect);
	void SetThreeButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect);
	void SetFourButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect);
	void SetFiveButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect);
	void SetSixButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect);
	int GetAvgCharWidth(HWND hWnd, CString wszString, HFONT hFont = NULL);
	HFONT m_hEngFont;
protected:
	DECLARE_MESSAGE_MAP()
};


