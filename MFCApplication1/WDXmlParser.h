#include <comutil.h>
#include <atlbase.h>
#include <comdef.h>
#include "atlstr.h"
#include <string>
#include "atlenc.h"
#include "stdafx.h"
#pragma once

class CWDXmlParser
{
	private:
		CAtlString m_element;
		CAtlString m_text;
		bool m_bFind;
		bool m_bEnd;
		int m_nIndex;
		int m_currentIndex;
		CAtlString m_tag;
		CAtlString m_subElement;
		CAtlString m_attribute;
		int m_nSubIndex;
		int m_iCurrentSubIndex;

		MSXML2::IXMLDOMDocumentPtr m_pIXMLDOMDocument;

	public:
		CWDXmlParser(void);
		~CWDXmlParser(void);		

		bool IterateChildNodes(MSXML2::IXMLDOMNodePtr pNode);
		
		VARIANT_BOOL LoadXmlFile(CAtlString szXmlFile);

		VARIANT_BOOL LoadXmlBuffer(wchar_t * szXmlBuffer);
	
		
		 CAtlString GetTextFromXml(CAtlString element);
		 CAtlString GetNodeTagText(CAtlString element, int nIndex,CAtlString tag,
		 CAtlString subElement=_T(""), int nSubIndex=0,CAtlString attribute =L"");

		 void SearchForText(MSXML2::IXMLDOMNodePtr pNode);
		 bool IterateAttibutes(MSXML2::IXMLDOMNodePtr pNode);

		 void Release();

		 long GetChildNodeListCount(CAtlString sElementTagName);
		 std::string GetLastErrorAsString();
};
/*=============================================================================================*/