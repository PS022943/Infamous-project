#include "StdAfx.h"
#include "WDXmlParser.h"

//Constructor
CWDXmlParser::CWDXmlParser(void)
{

	m_bFind=false;
	m_element=_T("");
	m_text=_T("");
	m_nIndex =0;
	m_currentIndex=0;
	m_tag=_T("");
	m_subElement=_T("");
	m_attribute=_T("");
	m_iCurrentSubIndex=0;

	m_pIXMLDOMDocument = NULL;
}


//Destructor
CWDXmlParser::~CWDXmlParser(void)
{
}

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string CWDXmlParser::GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

VARIANT_BOOL  CWDXmlParser::LoadXmlFile(CAtlString szXmlFile)
{
	 VARIANT_BOOL vBool=false;
	 if (SUCCEEDED(m_pIXMLDOMDocument.CreateInstance(__uuidof(DOMDocument30))))
	 {
		 vBool = m_pIXMLDOMDocument->load(_variant_t(szXmlFile));
	 }
	 std::string stringdata = GetLastErrorAsString();
  return vBool;
}


VARIANT_BOOL CWDXmlParser::LoadXmlBuffer(wchar_t *szXmlBuffer)
{
	VARIANT_BOOL vBool=false;
	if (SUCCEEDED(m_pIXMLDOMDocument.CreateInstance(__uuidof(DOMDocument30))))
	{
		 vBool = m_pIXMLDOMDocument->loadXML(szXmlBuffer);
	}
	return vBool;
}


CAtlString CWDXmlParser::GetTextFromXml(CAtlString element)
{
	
	m_text=_T("");
	m_element=element;
	
	MSXML2::IXMLDOMNodePtr pNode = m_pIXMLDOMDocument;
	if (pNode)
	{
		IterateChildNodes(pNode);
	}
	if(m_text.GetLength()>0)
	{
		return m_text;
	}
	else
		return NULL;

}
CAtlString CWDXmlParser::GetNodeTagText(CAtlString element, int nIndex, CAtlString tag, CAtlString subElement, int nSubIndex,CAtlString attribute)
{
	m_currentIndex=0;
	m_iCurrentSubIndex=0;
	m_tag=tag;
	m_text=_T("");
	m_element=element;

	m_nIndex=nIndex;
	m_attribute=L"";
	m_subElement=_T("");
	if(subElement.GetLength()>0)
	{
		m_subElement=subElement;
		m_nSubIndex=nSubIndex;
	}
	if(attribute.GetLength())
	{
		m_attribute=attribute;
	}
	MSXML2::IXMLDOMNodePtr pNode = m_pIXMLDOMDocument;
	if (pNode)
	{
		IterateChildNodes(pNode);
	}
	if(m_text.GetLength()>0)
	{
		return m_text;
	}
	else
		return NULL;

}


bool CWDXmlParser::IterateChildNodes(MSXML2::IXMLDOMNodePtr pNode)
{
	BSTR bstrNodeName;
	m_bEnd=false;
	pNode->get_nodeName(&bstrNodeName);

	MSXML2::DOMNodeType eEnum;
	pNode->get_nodeType(&eEnum);

	if(m_element ==  L"rdf:RDF")
	{
		
		if( bstrNodeName ==m_element)
		{
			m_text= L"rdf:RDF";
			m_bEnd = true;
		}
	}
	if (eEnum == MSXML2::NODE_ELEMENT)
	{
		if(m_element.CompareNoCase(bstrNodeName) == 0)
			m_currentIndex++;
		
	}
	if(m_currentIndex==m_nIndex)
	{
		if(m_subElement.GetLength()>0 && m_nSubIndex>0)
		{

			if(m_subElement.CompareNoCase(bstrNodeName)== 0)
				m_iCurrentSubIndex++;
	
			

			if(m_iCurrentSubIndex==m_nSubIndex)
			{
				if(m_element.CompareNoCase(bstrNodeName) == 0)
				{
					m_iCurrentSubIndex++;
				}
				SearchForText(pNode);
			}
		}
		else
		{
			SearchForText(pNode);
		}
	}

	SysFreeString(bstrNodeName);
	MSXML2::IXMLDOMNodePtr pChild = pNode->GetfirstChild();

	while( pChild && !m_bEnd  )
	{
		IterateChildNodes(pChild);
		pChild = pChild->GetnextSibling();
	}
	return true;
}


void CWDXmlParser::SearchForText(MSXML2::IXMLDOMNodePtr pNode)
{
	BSTR bstrNodeName;

	CAtlString szOutput;
	pNode->get_nodeName(&bstrNodeName);

	MSXML2::DOMNodeType eEnum;
	pNode->get_nodeType(&eEnum);

	if (eEnum == MSXML2::NODE_TEXT)
	{
	
		if(!m_attribute.GetLength())
		{
			if(m_bFind )
			{
				m_text = (BSTR)pNode->Gettext();
				m_bFind=false;
				m_bEnd=true;
			}	
		}
	}
	else if (eEnum == MSXML2::NODE_ELEMENT)
	{
		if(m_attribute.GetLength())
		{
			IterateAttibutes(pNode);
		}
		else
		{
			if(m_subElement.GetLength() && m_nSubIndex < 0)
			{
				if(m_subElement.CompareNoCase(bstrNodeName) == 0)
					m_bEnd = true;
			}
		if(m_bFind)
		{
			if(m_tag.CompareNoCase(bstrNodeName))
				m_bFind = false;
		}

		if(m_tag.CompareNoCase(bstrNodeName) == 0)
			m_bFind=true;
		
		}		
	}
	

	SysFreeString(bstrNodeName);
}
bool CWDXmlParser::IterateAttibutes(MSXML2::IXMLDOMNodePtr pNode)
{
	MSXML2::IXMLDOMNamedNodeMapPtr pAttrs = pNode->Getattributes();

	if(pAttrs)
	{
		MSXML2::IXMLDOMNodePtr pChild = pAttrs->nextNode();
		while(pChild)
		{
			BSTR bstrName;
			VARIANT vValue;
			
			pChild->get_nodeName(&bstrName);

		
			pChild->get_nodeValue(&vValue);
			
			_bstr_t strValue;
			switch ( vValue.vt )
			{
			case VT_BSTR:
					if(m_attribute.CompareNoCase(bstrName)== 0)
					{
						m_text = V_BSTR(&vValue);
						m_bEnd=true;
					}
				break;
			default:
				strValue = _T("Unsupport type");
				break;
			}
			
			//_bstr_t strAttrib = bstrName + _bstr_t("=") + strValue;
			SysFreeString(bstrName);
			VariantClear(&vValue);
			
			pChild = pAttrs->nextNode();
			
		}
	}
	return true;
}

void CWDXmlParser::Release()
{
	if(m_pIXMLDOMDocument)
	{
		m_pIXMLDOMDocument.Release();
		m_pIXMLDOMDocument = NULL;
	}
}

long CWDXmlParser::GetChildNodeListCount(CAtlString sElementTagName)
{
	long lChildNodeListCount = 0;
	MSXML2::IXMLDOMNodeListPtr pNodeChildList;

	MSXML2::IXMLDOMNodeListPtr pNodeList = m_pIXMLDOMDocument->getElementsByTagName((_bstr_t)sElementTagName);
	MSXML2::IXMLDOMNodePtr pNode = m_pIXMLDOMDocument->GetfirstChild();
	pNode->get_childNodes(&pNodeChildList);
	pNodeChildList->get_length(&lChildNodeListCount);
	pNodeList->get_length(&lChildNodeListCount);
	return lChildNodeListCount;
}