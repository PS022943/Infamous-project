#pragma once
#include <afx.h>
#include <string>
#include <vector>
#include <map>
using namespace std;
//Structure for BUTTON
typedef struct _stButton
{
	int iID;
	int iOrder; // Add member variable by Rajesh[JAN-07-08]
	bool bOnToolBarBtn; // Add by Rajesh[APR-06-08]
	bool bNonStaticBtn;	// Add by Rajesh[JUNE-11-08] for position update of static buttons in toolbar list
	int iStrLcid;		// Add by Rajesh[APR-06-08]
	CString wszKeyName;	// Add by Rajesh[APR-06-08]
	//Bitmap* hBitmap;
	CString wszImageText;
	CString wszBName;
	CString wszBDescription;
	CString wszBSite;
	
	_stButton()
	{
		bOnToolBarBtn = false; // Add by Rajesh[APR-06-08]
		bNonStaticBtn = false; // Add by Rajesh[JUNE-11-08] for position update of static buttons in toolbar list
		iStrLcid = -1;	// Add by Rajesh[APR-06-08]
		wszKeyName = _T("");
		iID = -1;
		iOrder = -1; // Add member variable by Rajesh[JAN-07-08]
		wszImageText = _T("");
		wszBName = _T("");
		wszBDescription = _T("");
		wszBSite = _T("");
	}
	~_stButton()
	{

	}

}STBUTTON;

typedef map<int, STBUTTON> BUTTONLIST;
