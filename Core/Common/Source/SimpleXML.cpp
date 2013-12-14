#include "../Include/SimpleXML.h"

namespace CB{
	namespace SXML{
		CNode::CNode(CNode* pParent, const CString& strName) :
			m_pParent(pParent),
			m_strName(strName),
			m_bSet(false),
			m_uOnMissingNodeRead(NodeErrorReact::ThrowException),
			m_uOnMissingNodeWrite(NodeErrorReact::ThrowException),
			m_uOnValueProcess(ValueErrorReact::ThrowException)
		{}

		CNode::CNode(const CNode& Node) :
			m_pParent(Node.m_pParent),
			m_strName(Node.m_strName),
			m_bSet(Node.m_bSet),
			m_strValue(Node.m_strValue),
			m_uOnMissingNodeRead(Node.m_uOnMissingNodeRead),
			m_uOnMissingNodeWrite(Node.m_uOnMissingNodeWrite),
			m_uOnValueProcess(Node.m_uOnValueProcess)
		{}

		void	CNode::SetOnMissingNode(const NodeErrorReact uReadReaction, const NodeErrorReact uWriteReaction){
			this->m_uOnMissingNodeRead = uReadReaction;
			this->m_uOnMissingNodeWrite = uWriteReaction;
			if(this->HasNodes()){
				CNodeList::CEnumerator Enumerator = this->m_NodeList.GetEnumerator();
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
					Enumerator.Get()->SetOnMissingNode(uWriteReaction, uWriteReaction);
				}
			}
		}

		void	CNode::SetOnValueProcess(const ValueErrorReact uReaction){
			this->m_uOnValueProcess = uReaction;
			if(this->HasNodes()){
				CNodeList::CEnumerator En = this->m_NodeList.GetEnumerator();
				for(En.ToFirst(); En.IsValid(); En.Next()){
					En.Get()->SetOnValueProcess(uReaction);
				}
			}
		}

		const NodeErrorReact	CNode::GetOnMissingNodeReadReaction() const{
			return this->m_uOnMissingNodeRead;
		}

		const NodeErrorReact	CNode::GetOnMissingNodeWriteReaction() const{
			return this->m_uOnMissingNodeWrite;
		}

		const ValueErrorReact	CNode::GetOnValueProcessReaction() const{
			return this->m_uOnValueProcess;
		}

		const CString	CNode::GetName() const{
			return this->m_strName;
		}

		const CString	CNode::GetValue() const{
			if(!this->m_bSet){
				if(this->m_uOnValueProcess == ValueErrorReact::ThrowException){
					throw Exception::CSXMLValueProcessingException(this->m_strName, CR_INFO());
				}
				else return L"";
			}
			return this->m_strValue;
		}

		const int32	CNode::GetInt32() const{
			return this->GetInt32(0);
		}

		const uint32	CNode::GetUInt32() const{
			return this->GetUInt32(0);
		}

		const float32	CNode::GetFloat() const{
			return this->GetFloat(0.0f);
		}

		const bool	CNode::GetBool() const{
			return this->GetBool(false);
		}

		const CString	CNode::GetValue(const CString& strDefault) const{
			if(!this->m_bSet){
				if(this->m_uOnValueProcess == ValueErrorReact::ThrowException){
					throw Exception::CSXMLValueProcessingException(this->m_strName, CR_INFO());
				}
				return strDefault;
			}
			return this->m_strValue;
		}

		const int32	CNode::GetInt32(const int32 iDefault) const{
			if(!this->m_bSet){
				if(this->m_uOnValueProcess == ValueErrorReact::ThrowException){
					throw Exception::CSXMLValueProcessingException(this->m_strName, CR_INFO());
				}
				return iDefault;
			}
			int iValue = 0;
			if(!String::ToInt32(this->m_strValue, iValue)){
				if(this->m_uOnValueProcess == ValueErrorReact::UseDefault){
					return iDefault;
				}
				else{
					throw Exception::CSXMLValueParsingException(this->m_strName, this->m_strValue, 
						CR_INFO());
				}
			}
			return iValue;
		}

		const uint32	CNode::GetUInt32(const uint32 uDefault) const{
			if(!this->m_bSet){
				if(this->m_uOnValueProcess == ValueErrorReact::ThrowException){
					throw Exception::CSXMLValueProcessingException(this->m_strName, CR_INFO());
				}
				return uDefault;
			}
			uint32 uValue = 0;
			if(!String::ToUInt32(this->m_strValue, uValue)){
				if(this->m_uOnValueProcess == ValueErrorReact::UseDefault){
					return uDefault;
				}
				else{
					throw Exception::CSXMLValueParsingException(this->m_strName, this->m_strValue, CR_INFO());
				}
			}
			return uValue;
		}

		const float32	CNode::GetFloat(const float32 fDefault) const{
			if(!this->m_bSet){
				if(this->m_uOnValueProcess == ValueErrorReact::ThrowException){
					throw Exception::CSXMLValueProcessingException(this->m_strName, CR_INFO());
				}
				return fDefault;
			}
			float fValue = 0.0f;
			if(!String::ToFloat(this->m_strValue, fValue)){
				if(this->m_uOnValueProcess == ValueErrorReact::UseDefault){
					return fDefault;
				}
				else{
					throw Exception::CSXMLValueParsingException(this->m_strName, this->m_strValue, CR_INFO());
				}
			}
			return fValue;
		}

		const bool	CNode::GetBool(const bool bDefault) const{
			if(!this->m_bSet){
				if(this->m_uOnValueProcess == ValueErrorReact::ThrowException){
					throw Exception::CSXMLValueProcessingException(this->m_strName, CR_INFO());
				}
				return bDefault;
			}
			bool bValue = false;
			if(!String::ToBool(this->m_strValue, bValue)){
				if(this->m_uOnValueProcess == ValueErrorReact::UseDefault){
					return bDefault;
				}
				else{
					throw Exception::CSXMLValueParsingException(this->m_strName, this->m_strValue, CR_INFO());
				}
			}
			return bValue;
		}

		CNode&	CNode::Add(const CString& strName){
			try{
				this->m_NodeList.Add(new CNode(this, strName));
				CNode& Node = *this->m_NodeList.Last();
				
				Node.SetOnMissingNode(this->m_uOnMissingNodeRead, this->m_uOnMissingNodeWrite);
				Node.SetOnValueProcess(this->m_uOnValueProcess);

				return Node;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, 
					CR_INFO(), Exception);
			}
		}

		CNode&	CNode::Add(const CString& strName, const CString& strValue){
			try{
				CNode& Node = this->Add(strName);
				Node.Set(strValue);
				return Node;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, CR_INFO(), Exception);
			}
		}

		CNode&	CNode::Add(const CString& strName, const int32 iValue){
			try{
				CNode& Node = this->Add(strName);
				Node.Set(iValue);
				return Node;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, CR_INFO(), Exception);
			}
		}

		CNode&	CNode::Add(const CString& strName, const float32 fValue){
			try{
				CNode& Node = this->Add(strName);
				Node.Set(fValue);
				return Node;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, CR_INFO(), Exception);
			}
		}

		CNode&	CNode::Add(const CString& strName, const bool bValue){
			try{
				CNode& Node = this->Add(strName);
				Node.Set(bValue);
				return Node;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, CR_INFO(), Exception);
			}
		}

		const bool CompareNodeName(const CNode::CNodeList::CItem& Node, const CString& strName){
			return Node->GetName() == strName;
		}

		CNode&	CNode::Get(const CString& strName){
			try{
				CNodeList::CEnumerator En = this->m_NodeList.GetEnumerator();
				if(Collection::TryFind(this->m_NodeList, CompareNodeName, strName, En)){
					return *En.Get();
				}
				if(this->m_uOnMissingNodeWrite == NodeErrorReact::CreateNew){
					return this->Add(strName);
				}
				if(this->m_uOnMissingNodeWrite == NodeErrorReact::Ignore){
					return *this;
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CInvalidArgumentException(L"strName", strName, 
					L"Node name not found.", CR_INFO(), Exception);
			}
			throw Exception::CSXMLNodeMissingException(strName, this->m_strName, CR_INFO());
		}

		const CNode&	CNode::Get(const CString& strName) const{
			try{
				CNodeList::CEnumerator En = this->m_NodeList.GetEnumerator();
				if(Collection::TryFind(this->m_NodeList, CompareNodeName, strName, En)){
					return *En.Get();
				}
				if(this->m_uOnMissingNodeRead == NodeErrorReact::Ignore){
					return *this;
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CInvalidArgumentException(L"strName", strName, 
					L"Node name not found.", CR_INFO(), Exception);
			}
			throw Exception::CSXMLNodeMissingException(strName, this->m_strName, CR_INFO());
		}

		const uint32	CNode::GetLength() const{
			return this->m_NodeList.GetLength();
		}

		const bool	CNode::IsEmpty() const{
			return this->m_NodeList.IsEmpty();
		}

		CNode&	CNode::Get(const uint32 uIndex){
			return *this->m_NodeList.Get(uIndex);
		}

		const CNode&	CNode::Get(const uint32 uIndex) const {
			return *this->m_NodeList.Get(uIndex);
		}

		CNode::CNodeEnumerator	CNode::GetEnumerator() const{
			return this->m_NodeList.GetEnumerator();
		}

		const bool	CNode::Contains(const CString& strName) const{
			try{
				return Collection::Contains(this->m_NodeList, CompareNodeName, strName);
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(
					L"Error while checking for node " + strName + L" existance if parent " + this->m_strName + L".", CR_INFO(), Exception);
			}
		}

		void	CNode::Set(const CString& strValue){
			this->m_strValue = strValue;
			this->m_bSet = true;
		}

		void	CNode::Set(const int32 iValue){
			this->m_strValue = String::FromInt32(iValue);
			this->m_bSet = true;
		}

		void	CNode::Set(const float32 fValue){
			this->m_strValue = String::FromFloat(fValue);
			this->m_bSet = true;
		}

		void	CNode::Set(const bool bValue){
			this->m_strValue = String::FromBool(bValue);
			this->m_bSet = true;
		}

		void	CNode::ResetValue(){
			this->m_strValue.Clear();
			this->m_bSet = false;
		}

		void	CNode::Remove(const CString& strName){
			try{
				CNodeList::CEnumerator En = this->m_NodeList.GetEnumerator();
				if(Collection::TryFind(this->m_NodeList, CompareNodeName, strName, En)){
					CAutoPtr<CNode> pNode = this->m_NodeList.Remove(En);
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeMissingException(strName, this->m_strName,
					CR_INFO(), Exception);
			}
		}

		void	CNode::Remove(){
			try{
				if(this->m_pParent){
					this->m_pParent->Remove(this->m_strName);
				}
				else{
					throw Exception::CSXMLException(
						L"Parentless node L" + this->m_strName + L" cannot remove itself.", CR_INFO());
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, 
					CR_INFO(), Exception);
			}
		}

		void	CNode::Clear(){
			this->m_NodeList.Clear();
		}

		const bool	CNode::HasNodes() const{
			return !this->m_NodeList.IsEmpty();
		}

		CNode&	CNode::operator[](const CString& strName){
			return this->Get(strName);
		}

		const CNode&	CNode::operator[](const CString& strName) const{
			return this->Get(strName);
		}

		CNode&	CNode::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		const CNode&	CNode::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		const CString	CNode::ToString() const{
			return this->ToString(false, false, 0);
		}
		
		const CString	CNode::ToString(const bool bWithNewLines) const{
			return this->ToString(bWithNewLines, false, 0);
		}

		const CString	CNode::ToString(const bool bWithNewString, const bool bNested) const{
			return this->ToString(bWithNewString, bNested, 0);
		}

		const uint32	CNode::Parse(const CString& strText, const uint32 uStartIndex){
			try{
				const Collection::CList<wchar_t> whiteList = String::ToArray(L" \t\n\r");

				uint32 uIndex = uStartIndex;
				for(; uIndex < strText.GetLength(); uIndex++){
					if(String::MultiCompare(strText, uIndex, whiteList)){
						continue;
					}

					if(strText.SubCompare(uIndex, L"</")){
						return this->ParseEndTag(strText, uStartIndex, uIndex);
					}

					if(strText.SubCompare(uIndex, L"<")){
						uIndex = this->ParseStartTag(strText, uIndex);
					}								
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, 
					CR_INFO(), Exception);
			}
			throw Exception::CSXMLException(
				L"No ending tag for SXML node: " + this->m_strName + L".", CR_INFO());
		}

		const uint32	CNode::ParseStartTag(const CString& strText, const uint32 uIndex){
			uint32 uEndPos = uIndex;
			bool bEnded = false;
			if(!strText.Find(L">", uIndex, uEndPos)){
				throw Exception::CSXMLException(L"Failed to find ending bracet.", CR_INFO());
			}
			if(uIndex + 1 == uEndPos){
				throw Exception::CSXMLException(L"No endging tag found.", CR_INFO());
			}
			if(strText.SubCompare(uEndPos - 1, L"/")){
				bEnded = true;
				uEndPos--;
			}

			try{
				CNode& Node = this->Add(strText.SubStringIndexed(uIndex+1, uEndPos).Trim());
				if(!bEnded){
					return Node.Parse(strText, uEndPos + 1);
				}
				return uEndPos + 1;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while adding new node to " + this->m_strName + L" node.", 
					CR_INFO(), Exception);
			}
		}

		const uint32	CNode::ParseEndTag(const CString& strText, const uint32 uStartIndex, const uint32 uIndex){
			uint32 uEndPos = uIndex;
			if(!strText.Find(L">", uIndex, uEndPos)){
				throw Exception::CSXMLException(
					L"Didn't found ending bracet for tag.", CR_INFO());
			}
			if(uIndex + 2 == uEndPos){
				throw Exception::CSXMLException(
					L"Invalid ending tag bracet position.", CR_INFO());
			}

			if(this->m_strName != strText.SubStringIndexed(uIndex + 2, uEndPos).Trim()){
				throw Exception::CSXMLException(
					L"Inalid enging tag for node: " + this->m_strName + L".", CR_INFO());
			}

			try{
				if(!this->HasNodes()){
					this->Set(strText.SubStringIndexed(uStartIndex, uIndex).Trim());
				}
				return uIndex + 1;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while concluding end tag parsing for node " + this->m_strName + L".",
					CR_INFO(), Exception);
			}
		}

		const CString	CNode::CreateNewLines(const bool bWithNewLines) const{
			if(bWithNewLines){
				return L"\n";
			}
			return L"";
		}

		const CString	CNode::CreateTabs(const bool bNested, const uint32 uNestLevel) const{
			if(!bNested){
				return L"";
			}
			CString strReturn;
			for(uint32 uIndex = 0; uIndex < uNestLevel; uIndex++){
				strReturn += L"\t";
			}
			return strReturn;
		}

		const CString	CNode::ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const{
			try{
				if(!this->m_bSet && !this->HasNodes()){
					return this->CreateTabs(bNested, uNestLevel) + L"<" + this->m_strName + L" />" + this->CreateNewLines(bWithNewLines);
				}
				Collection::CStringList RetList;

				RetList.Add(this->CreateTabs(bNested, uNestLevel));
				RetList.Add(L"<" + this->m_strName + L">");
				if(this->HasNodes()){
					RetList.Add(this->CreateNewLines(bWithNewLines));

					CNodeList::CEnumerator Enumerator = this->m_NodeList.GetEnumerator();
					for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
						RetList.Add(Enumerator.Get()->ToString(bWithNewLines, bNested, uNestLevel + 1));
					}
				}
				else{
					RetList.Add(this->m_strValue);
				}
				if(this->HasNodes()){
					RetList.Add(this->CreateTabs(bNested, uNestLevel));
				}
				RetList.Add(L"</" + this->m_strName + L">");
				RetList.Add(this->CreateNewLines(bWithNewLines));

				return RetList.ToString();
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while converting node " + this->m_strName,
					CR_INFO(), Exception);
			}
		}

		//=================================================================
		//	Root DEFINITION
		//=================================================================

		CRoot::CRoot() : 
			m_Root(0, L"")
		{}

		void	CRoot::SetOnMissingNode(const NodeErrorReact uReadReaction, const NodeErrorReact uWriteReaction){
			this->m_Root.SetOnMissingNode(uReadReaction, uWriteReaction);
		}

		void	CRoot::SetOnValueProcess(const ValueErrorReact uReaction){
			this->m_Root.SetOnValueProcess(uReaction);
		}

		const NodeErrorReact	CRoot::GetOnMissingNodeReadReaction() const{
			return this->m_Root.GetOnMissingNodeReadReaction();
		}

		const NodeErrorReact	CRoot::GetOnMissingNodeWriteReaction() const{
			return this->m_Root.GetOnMissingNodeWriteReaction();
		}

		const ValueErrorReact	CRoot::GetOnValueProcessReaction() const{
			return this->m_Root.GetOnValueProcessReaction();
		}

		CNode&	CRoot::Add(const CString& strName){
			return this->m_Root.Add(strName);
		}

		CNode&	CRoot::Add(const CString& strName, const int32 iValue){
			return this->m_Root.Add(strName, iValue);
		}

		CNode&	CRoot::Add(const CString& strName, const float32 fValue){
			return this->m_Root.Add(strName, fValue);
		}

		CNode&	CRoot::Add(const CString& strName, const CString& strValue){
			return this->m_Root.Add(strName, strValue);
		}

		CNode&	CRoot::Get(const CString& strName){
			return this->m_Root.Get(strName);
		}

		const CNode&	CRoot::Get(const CString& strName) const{
			return this->m_Root.Get(strName);
		}

		CNode&	CRoot::Get(const uint32 uIndex){
			return this->m_Root.Get(uIndex);
		}

		const CNode&	CRoot::Get(const uint32 uIndex) const{
			return this->m_Root.Get(uIndex);
		}

		CNode::CNodeEnumerator	CRoot::GetEnumerator() const{
			return this->m_Root.GetEnumerator();
		}

		const bool	CRoot::Contains(const CString& strName) const{
			return this->m_Root.Contains(strName);
		}

		void	CRoot::Remove(const CString& strName){
			this->m_Root.Remove(strName);
		}

		void	CRoot::Clear(){
			this->m_Root.Clear();
		}

		const bool	CRoot::HasNodes() const{
			return this->m_Root.HasNodes();
		}

		const bool	CRoot::IsEmpty() const{
			return !this->m_Root.HasNodes();
		}

		const uint32	CRoot::GetLength() const{
			return this->m_Root.GetLength();
		}

		CNode&	CRoot::operator[](const CString& strName){
			return this->m_Root.Get(strName);
		}

		const CNode&	CRoot::operator[](const CString& strName) const{
			return this->m_Root.Get(strName);
		}

		CNode&	CRoot::operator[](const uint32 uIndex) {
			return this->m_Root.Get(uIndex);
		}

		const CNode&	CRoot::operator[](const uint32 uIndex) const{
			return this->m_Root.Get(uIndex);
		}

		void	CRoot::Parse(const CString& strText){
			static const Collection::CList<wchar_t> whiteList = String::ToArray(L" \n\t\r");

			for(uint32 uIndex = 0; uIndex < strText.GetLength(); uIndex++){
				if(String::MultiCompare(strText, uIndex, whiteList)){
					continue;
				}

				if(strText.SubCompare(uIndex, L"<")){
					uIndex = this->m_Root.ParseStartTag(strText, uIndex);
				}
			}
		}

		const CString	CRoot::ToString() const{
			return this->ToString(false, false);
		}

		const CString	CRoot::ToString(const bool bWithNewLines) const{
			return this->ToString(bWithNewLines, false);
		}

		const CString	CRoot::ToString(const bool bWithNewLines, const bool bNested) const{
			try{
				Collection::CStringList RetList;

				CNode::CNodeList::CEnumerator En = this->m_Root.m_NodeList.GetEnumerator();
				for(En.ToFirst(); En.IsValid(); En.Next()){
					RetList.Add(En.Get()->ToString(bWithNewLines, bNested, 0));
				}
				if(bWithNewLines){
					RetList.Add(this->m_Root.CreateNewLines(bWithNewLines));
				}

				return RetList.ToString();
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(
					L"Error while converting SXML Root to string.", CR_INFO(), Exception);
			}
		}
	}

	namespace Exception{
		//	====SXML Exception Class====

		CSXMLException::CSXMLException(const CSXMLException& Exception) : 
			CException(Exception)
		{
		}

		CSXMLException::CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CException(strMessage, strFunction, strFile, uLine)
		{
		}

		CSXMLException::CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception) :
			CException(strMessage, strFunction, strFile, uLine, Exception)
		{
		}

		CException*	CSXMLException::CreateCopy() const{
			return new CSXMLException(*this);
		}

		//	====SXML Node Exception Class====
		CSXMLNodeException::CSXMLNodeException(const CSXMLNodeException& Exception) :
			CSXMLException(Exception),
			m_strNodeName(Exception.m_strNodeName)
		{
		}

		CSXMLNodeException::CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLException(L"Error in Simple XML Node.", strFunction, strFile, uLine),
			m_strNodeName(strName)
		{
		}

		CSXMLNodeException::CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CSXMLException(L"Error in Simple XML Node {0}.", strFunction, strFile, uLine, InnerException),
			m_strNodeName(strName)
		{
		}

		const CString	CSXMLNodeException::GetMessage() const{
			Collection::CStringList varList;

			varList.Add(this->m_strNodeName);

			return String::VarReplace(this->m_strMessage, varList, true);
		}

		CException*	CSXMLNodeException::CreateCopy() const{
			return new CSXMLNodeException(*this);
		}

		//	====SXML Node Missing Exception Class====
		const CString	g_strNodeMissingError = L"Missing node {1} in Simple XML parent {0}.";

		CSXMLNodeMissingException::CSXMLNodeMissingException(const CSXMLNodeMissingException& Exception) :
			CSXMLNodeException(Exception),
			m_strChildName(Exception.m_strChildName)
		{
			this->m_strMessage = g_strNodeMissingError;
		}

		CSXMLNodeMissingException::CSXMLNodeMissingException(const CString& strName, const CString& strParentName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLNodeException(strParentName, strFunction, strFile, uLine),
			m_strChildName(strName)
		{
			this->m_strMessage = g_strNodeMissingError;
		}

		CSXMLNodeMissingException::CSXMLNodeMissingException(const CString& strName, const CString& strParentName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CSXMLNodeException(strParentName, strFunction, strFile, uLine, InnerException),
			m_strChildName(strName)
		{
			this->m_strMessage = g_strNodeMissingError;
		}

		const CString	CSXMLNodeMissingException::GetMessage() const{
			Collection::CStringList varList;

			varList.Add(this->m_strNodeName);
			varList.Add(this->m_strChildName);

			return String::VarReplace(this->m_strMessage, varList, true);
		}

		CException*	CSXMLNodeMissingException::CreateCopy() const{
			return new CSXMLNodeMissingException(*this);
		}

		//	====SXML Value Pocessing Exception====
		const CString g_strValueProcessingError = L"Error while processing value in Simple XML Node {0}.";

		CSXMLValueProcessingException::CSXMLValueProcessingException(const CSXMLValueProcessingException& Exception) :
			CSXMLNodeException(Exception)
		{
			this->m_strMessage = g_strValueProcessingError;
		}

		CSXMLValueProcessingException::CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLNodeException(strName, strFunction, strFile, uLine)
		{
			this->m_strMessage = g_strValueProcessingError;
		}

		CSXMLValueProcessingException::CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception) :
			CSXMLNodeException(strName, strFunction, strFile, uLine, Exception)
		{
			this->m_strMessage = g_strValueProcessingError;
		}

		CException*	CSXMLValueProcessingException::CreateCopy() const{
			return new CSXMLValueProcessingException(*this);
		}

		//	====SXML Value Parsing Exception====
		const CString g_strValueParsingError = L"Error while parsing value {1} in Simple XML Node {0}.";

		CSXMLValueParsingException::CSXMLValueParsingException(const CSXMLValueParsingException& Exception) :
			CSXMLValueProcessingException(Exception),
			m_strValue(Exception.m_strValue)
		{
			this->m_strMessage = g_strValueParsingError;
		}

		CSXMLValueParsingException::CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLValueProcessingException(strName, strFunction, strFile, uLine),
			m_strValue(strValue)
		{
			this->m_strMessage = g_strValueParsingError;
		}

		CSXMLValueParsingException::CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception) :
			CSXMLValueProcessingException(strName, strFunction, strFile, uLine, Exception),
			m_strValue(strValue)
		{
			this->m_strMessage = g_strValueParsingError;
		}

		const CString	CSXMLValueParsingException::GetMessage() const{
			Collection::CStringList varList;

			varList.Add(this->m_strNodeName);
			varList.Add(this->m_strValue);

			return String::VarReplace(this->m_strMessage, varList, true);
		}

		CException*	CSXMLValueParsingException::CreateCopy() const{
			return new CSXMLValueParsingException(*this);
		}
	}
}