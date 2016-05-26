#include "stdafx.h"
#include "XmlparserHelper.h"



CXmlparserHelper::CXmlparserHelper()
{
	m_iKey = 0;
}


CXmlparserHelper::~CXmlparserHelper()
{
	m_iKey = 0;
}


bool CXmlparserHelper::XMLParser(CString szFileName, BUTTONLIST& vButtonInfo)
{
	vButtonInfo.clear();
	// Initialize COM
	::CoInitialize(NULL);
	int n = 0;
	BSTR strFindText = L" ";
	m_iKey = 0;
	//Variables to store item's name, parent, text and node type:
	BSTR bstrItemText, bstrItemNode, bstrItemParent, bstrNodeType;

	//Variables to store attribute's name,type and text:	 
	BSTR bstrAttrName, bstrAttrType, bstrAttrText;

	//Initialize COM Library:
	CoInitialize(NULL);

	//Create an instance of the DOMDocument object:
	m_plDomDocument.CreateInstance(__uuidof(DOMDocument30));

	// Load a document:
	_variant_t varXml(szFileName);//XML file to load
	_variant_t varResult((bool)TRUE);//result 

	if (NULL == m_plDomDocument)
	{
		return false;
	}

	varResult = m_plDomDocument->load(varXml);

	if ((bool)varResult == FALSE)
	{
		return false;
	}

	//Collect all or selected nodes by tag name:
	NodeListPtr = m_plDomDocument->getElementsByTagName(strFindText);

	if (NULL == m_plDomDocument->documentElement || NULL == NodeListPtr)
	{
		return false;
	}

	//Output root node:
	m_plDomDocument->documentElement->get_nodeName(&bstrItemText);

	for (int i = 0; i < (NodeListPtr->length); i++)
	{

		if (NULL != pIDOMNode)
		{
			pIDOMNode->Release();
		}

		NodeListPtr->get_item(i, &pIDOMNode);


		if (NULL != pIDOMNode)
		{

			pIDOMNode->get_nodeTypeString(&bstrNodeType);
			CString strElementtext = _T("element");
			CString strNodeType(bstrNodeType);

			if (strNodeType.CompareNoCase(strElementtext) == 0)
			{
				n++;//element node's number

				pIDOMNode->get_nodeName(&bstrItemNode);
				CString strNode = (CString)bstrItemNode;
				pIDOMNode->get_text(&bstrItemText);
				CString strItemText(bstrItemText);
				if (strNode.CompareNoCase(_T("name")) == 0)
				{
					//vButtonInfo.insert(std::pair<int, CString>(m_iKey, strItemText));
					m_iKey++;
				}

				pIDOMNode->get_parentNode(&pIParentNode);
				if (NULL == pIParentNode)
				{
					return false;
				}

				pIParentNode->get_nodeName(&bstrItemParent);

			//	pIDOMNode->get_childNodes(&childList);
				pIDOMNode->get_firstChild(&pIDOMChildNode);
				int j = 0;//loop-index variable
				long length = 0;// number of attributes in the collection

				long iCount = pIDOMChildNode->get_childNodes(&childList);// ->Getlength();

				iCount = childList->Getlength();
				DOMNamedNodeMapPtr = pIDOMNode->attributes;

				if (NULL == DOMNamedNodeMapPtr)
				{
					return false;
				}

				HRESULT hResult = DOMNamedNodeMapPtr->get_length(&length);

				if (SUCCEEDED(hResult))
				{
					//Loop through the number of attributes:
					for (j = 0; j < length; j++)
					{
						//get attribute node:							
						DOMNamedNodeMapPtr->get_item(j, &pIAttrNode);
						if (NULL == pIAttrNode)
						{
							return false;
						}

						pIAttrNode->get_nodeTypeString(&bstrAttrType);//type as string
						pIAttrNode->get_nodeName(&bstrAttrName);
						pIAttrNode->get_text(&bstrAttrText);
					}
				}
			}
		}
	}

	//Do not forget to release interfaces:
	pIDOMNode->Release();
	pIDOMNode = NULL;
	//pIParentNode->Release();
	//pIParentNode = NULL;
	return false;
}

/*
bool CXmlparserHelper::XMLParser(CString strFilePath, CString strPipeline, std::map<int, CString>& XMLFileComponentmap, bool bIsCreator)
{
	// Initialize COM
	::CoInitialize(NULL);
	int iXMLMapFileCount = 1;

	HRESULT hr = m_plDomDocument.CreateInstance(__uuidof(DOMDocument30));

	strFilePath.Append(_T("\\"));
	strFilePath.Append(_T("new11.xml"));

	_bstr_t bstrFileName;
	bstrFileName = strFilePath.AllocSysString();

	variant_t vResult;
	vResult = m_plDomDocument->load(bstrFileName);

	if (((bool)vResult) != TRUE) // success!
	{
	
		return false;;
	}

	hr = m_plDomDocument->get_documentElement(&pXMLElement);
	if (FAILED(hr))
	{
		return false;
	}

	//Retrieve a list of the child nodes.
	hr = pXMLElement->get_childNodes(&pChildList);
	if (FAILED(hr))
	{
		return false;
	}

	long lChildListCount = pChildList->Getlength();

	CString sTempPipeline, sTempVersion, sNodeText;
	CString sVersion;

	for (long lChildCount = 0; lChildCount < lChildListCount; lChildCount++)
	{
		// Retrieve the first child in the list.
		hr = pChildList->get_item(lChildCount, &pChildNode);
		if (FAILED(hr))
		{
			return false;
		}

		_bstr_t bstrText;
		MSXML2::IXMLDOMNodePtr pInfoNode = NULL;
		pInfoNode = pChildNode->selectSingleNode((LPCSTR)"VERSION");  //Able to get the text within the  child element
		bstrText = pInfoNode->text;
		
		CString version_names;
		version_names = (LPCTSTR)bstrText;
		if (version_names == "Common Components" || version_names == strPipeline)
		{
			if (lChildCount == 1)
			{
				if (!bIsCreator)
				{
					continue;
				}
			}

			if (lChildCount > 1)
			{
				sTempPipeline = strPipeline.Mid(0, 7);

				sNodeText = (LPCTSTR)bstrText;

				if (sTempPipeline == sNodeText.Mid(0, 7))
				{
					sTempVersion = strPipeline.Mid(8, 2);
					sVersion = sNodeText.Mid(8, 2);
					int iTempVersion, iVersion;

					if (strPipeline.GetLength() == 10)
					{
						iTempVersion = _ttoi(sTempVersion);
						iVersion = _ttoi(sVersion);

						if (iTempVersion < iVersion)
						{
							continue;
						}
					}
					else if (strPipeline.Mid(0, 11) == sNodeText.Mid(0, 11))
					{
						sTempVersion = strPipeline.Mid(11, 4);

						double dTempVersion, dVersion;
						sVersion = sNodeText.Mid(11, 4);

						dTempVersion = _ttof(sTempVersion);
						dVersion = _ttof(sVersion);

						if (dTempVersion < dVersion)
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}

			MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
			pNodeList = pChildNode->GetchildNodes();// nextSibling;

			long lNodeList = pNodeList->Getlength();
			CString sComponentName;
			_bstr_t bstrElementName;
			_bstr_t bstrElementText;
			MSXML2::IXMLDOMNodePtr pInfoListNode = NULL;

			//Add condition to load the MAP based on the version selected


			for (long lCount = 1; lCount < lNodeList; lCount++)
			{
				CString strCount;
				strCount.Format(_T("%ld"), lCount);

				bstrElementName = L"Component" + _bstr_t(strCount);

				pInfoListNode = pChildNode->selectSingleNode(bstrElementName);
				bstrElementText = pInfoListNode->text;

				sComponentName = (LPCTSTR)bstrElementText;
				XMLFileComponentmap[iXMLMapFileCount] = sComponentName.MakeLower();
				iXMLMapFileCount++;
			}
		//}
		//if (flag1 == 1)
		//{
		//	_bstr_t b("Steve");
		//	CString cs;
		//	cs = (LPCTSTR)b;
		//	CString version_name = "Libraries";
		//	
		//		if (lChildCount > 0)
		//		{
		//			sTempPipeline = strPipeline.Mid(0, 7);

		//			sNodeText = (LPCTSTR)bstrText;

		//			if (sTempPipeline == sNodeText.Mid(0, 7))
		//			{
		//				sTempVersion = strPipeline.Mid(8, 2);
		//				sVersion = sNodeText.Mid(8, 2);
		//				int iTempVersion, iVersion;

		//				if (strPipeline.GetLength() == 10)
		//				{
		//					iTempVersion = _ttoi(sTempVersion);
		//					iVersion = _ttoi(sVersion);

		//					if (iTempVersion < iVersion)
		//					{
		//						continue;
		//					}
		//				}
		//				else if (strPipeline.Mid(0, 11) == sNodeText.Mid(0, 11))
		//				{
		//					sTempVersion = strPipeline.Mid(11, 4);

		//					double dTempVersion, dVersion;
		//					sVersion = sNodeText.Mid(11, 4);

		//					dTempVersion = _ttof(sTempVersion);
		//					dVersion = _ttof(sVersion);

		//					if (dTempVersion < dVersion)
		//					{
		//						continue;
		//					}
		//				}
		//			}
		//			else
		//			{
		//				continue;
		//			}
		//		}

		//		MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
		//		pNodeList = pChildNode->GetchildNodes();// nextSibling;

		//		long lNodeList = pNodeList->Getlength();
		//		CString sComponentName;
		//		_bstr_t bstrElementName;
		//		_bstr_t bstrElementText;
		//		MSXML2::IXMLDOMNodePtr pInfoListNode = NULL;

		//		//Add condition to load the MAP based on the version selected


		//		for (long lCount = 1; lCount < lNodeList; lCount++)
		//		{
		//			CString strCount;
		//			strCount.Format(_T("%ld"), lCount);

		//			bstrElementName = L"Component" + _bstr_t(strCount);

		//			pInfoListNode = pChildNode->selectSingleNode(bstrElementName);
		//			bstrElementText = pInfoListNode->text;

		//			sComponentName = (LPCTSTR)bstrElementText;
		//			XMLFileComponentmap[iXMLMapFileCount] = sComponentName.MakeLower();
		//			iXMLMapFileCount++;
		//		}
		//	}
		}
	}
	return true;
}

*/