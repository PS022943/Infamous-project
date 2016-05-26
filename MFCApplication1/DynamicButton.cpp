// DynamicButton.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"
#include "DynamicButton.h"
#include "CGdiPlusBitmap.h"
#include "MemDC.h"

// CDynamicButton

IMPLEMENT_DYNAMIC(CDynamicButton, CButton)

CDynamicButton::CDynamicButton()
{

}

CDynamicButton::~CDynamicButton()
{
}


BEGIN_MESSAGE_MAP(CDynamicButton, CButton)
END_MESSAGE_MAP()


void CDynamicButton::SetBaseButton(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect)
{
	m_hEngFont = CreateFont(29, 0, 0, 0, 100, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, _T("arial"));

	if (iNumberOfBtn == 3)
	{
		SetThreeButtonPosition(hWnd, strBtnText, iNumberOfBtn, iButtonNumber, rcBtnRect, rcDlgRect);
	}
	else if (iNumberOfBtn == 4)
	{
		SetFourButtonPosition(hWnd, strBtnText, iNumberOfBtn, iButtonNumber, rcBtnRect, rcDlgRect);
	}
	else if (iNumberOfBtn == 5)
	{
		SetFiveButtonPosition(hWnd, strBtnText, iNumberOfBtn, iButtonNumber, rcBtnRect, rcDlgRect);
	}
	else if (iNumberOfBtn == 6)
	{
		SetSixButtonPosition(hWnd, strBtnText, iNumberOfBtn, iButtonNumber, rcBtnRect, rcDlgRect);
	}
	else
	{
		//do Nothing
	}
}

// CDynamicButton message handlers
void CDynamicButton::SetThreeButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect)
{
	int iTextWidth = GetAvgCharWidth(hWnd, strBtnText);
	CRect rcSetBtnRect;
	if (iButtonNumber == 1)
	{
		rcSetBtnRect.left = rcBtnRect.left;
		rcSetBtnRect.top = rcBtnRect.top / 2;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth , 90, TRUE);
	}
	else if (iButtonNumber == 2)
	{
		rcSetBtnRect.left = rcBtnRect.right + (rcDlgRect.right - rcBtnRect.right) / 2;
		rcSetBtnRect.top = rcBtnRect.bottom;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth , 90, TRUE);
	}
	else if (iButtonNumber == 3)
	{
		rcSetBtnRect.left = rcBtnRect.left / 2;
		rcSetBtnRect.top = rcBtnRect.bottom;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth , 90, TRUE);
	}
	else
	{
		//do Nothing
	}
}

// CDynamicButton message handlers
void CDynamicButton::SetFourButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect)
{
	int iTextWidth = GetAvgCharWidth(hWnd, strBtnText);
	CRect rcSetBtnRect;
	if (iButtonNumber == 1)
	{
		rcSetBtnRect.left = rcBtnRect.left;
		rcSetBtnRect.top = rcBtnRect.top / 2;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 2)
	{
		rcSetBtnRect.left = rcBtnRect.right + (rcDlgRect.right - rcBtnRect.right) / 2;
		rcSetBtnRect.top = rcBtnRect.bottom;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 3)
	{
		rcSetBtnRect.left = rcBtnRect.left / 2;
		rcSetBtnRect.top = rcBtnRect.bottom;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 4)
	{
		rcSetBtnRect.left = rcBtnRect.left;
		rcSetBtnRect.top = rcBtnRect.bottom + (rcDlgRect.bottom - rcBtnRect.bottom) / 2;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else
	{
		// Do nothing
	}
}

// CDynamicButton message handlers
void CDynamicButton::SetFiveButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect)
{
	int iTextWidth = GetAvgCharWidth(hWnd, strBtnText);
	CRect rcSetBtnRect;
	if (iButtonNumber == 1)
	{
		rcSetBtnRect.left = rcBtnRect.left;
		rcSetBtnRect.top = rcBtnRect.top / 2;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 2)
	{
		rcSetBtnRect.left = rcBtnRect.right + (rcDlgRect.right - rcBtnRect.right) / 2;
		rcSetBtnRect.top = rcBtnRect.bottom;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 3)
	{
		rcSetBtnRect.left = rcBtnRect.left / 2;
		rcSetBtnRect.top = rcBtnRect.bottom;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 4)
	{
		rcSetBtnRect.left = rcBtnRect.left;
		rcSetBtnRect.top = rcBtnRect.bottom + rcBtnRect.bottom / 2;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else if (iButtonNumber == 5)
	{
		rcSetBtnRect.left = rcBtnRect.left;
		rcSetBtnRect.top = rcBtnRect.bottom + rcBtnRect.bottom / 2;
		::MoveWindow(hWnd, rcSetBtnRect.left, rcSetBtnRect.top, iTextWidth, 90, TRUE);
	}
	else
	{
		// Do nothing
	}
}

// CDynamicButton message handlers
void CDynamicButton::SetSixButtonPosition(HWND hWnd, CString strBtnText, int iNumberOfBtn, int iButtonNumber, CRect rcBtnRect, CRect rcDlgRect)
{

}

// Add by Rajesh[FEB-26-08] for get char width for menu
int CDynamicButton::GetAvgCharWidth(HWND hWnd, CString wszString, HFONT hFont)
{
	int cxChar = 0;
	HDC hdc = NULL;
	//TEXTMETRIC tm;
	//bool bFlag = false;
	SIZE iSize;

	iSize.cx = -1;
	iSize.cy = -1;

	if (hWnd && wszString.GetLength() > 0)
	{
		// get average width of chars
		hdc = ::GetDC(hWnd);				// get handle of device context

		if (hFont)
			SelectObject(hdc, hFont);
		else
			SelectObject(hdc, m_hEngFont);
		if (hdc)
		{
			//GetTextMetrics(hdc, &tm);	// get text matrics
			//cxChar =  tm.tmAveCharWidth + 1;
			GetTextExtentPoint32(hdc, wszString, wcslen(wszString), &iSize);

			::ReleaseDC(hWnd, hdc);

			// Add by Rajesh[FEB-13-08] release memory
			///////////////////////////////////////////
			DeleteObject(hdc);
			hdc = NULL;
			///////////////////////////////////////////
		}
	}
	//return cxChar;//return width.
	return iSize.cx;
}