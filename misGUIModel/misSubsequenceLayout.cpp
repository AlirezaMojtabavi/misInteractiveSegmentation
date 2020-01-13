#include "stdafx.h"
#include "misSubsequenceLayout.h"

#include "misWindowModel.h"

using  namespace std;

int  misSubsequenceLayout:: GetActiveWindow() const
{
    return m_ActiveWindow;
}


//##ModelId=47D7E55D01D4
void misSubsequenceLayout::SetActiveWindow(int left)
{
    m_ActiveWindow = left;
}


//##ModelId=47D7E55D0213
int misSubsequenceLayout::GetFullScreenWindowID() const
{
    return m_FullScreenWindowID;
}


//##ModelId=47D7E55D0223
void misSubsequenceLayout::SetullScreenWindowID(int  left)
{
    m_FullScreenWindowID = left;
}


//##ModelId=47D7E55D0271
int misSubsequenceLayout::GetID() const
{
    return m_ID;
}


//##ModelId=47D7E55D0290
void misSubsequenceLayout::SetID(int left)
{
    m_ID = left;
}


//##ModelId=47D7E55D02CE
string misSubsequenceLayout::GetName() const
{
    return m_Name;
}


//##ModelId=47D7E55D02FD
void misSubsequenceLayout::SetName(string left)
{
    m_Name = left;
}

//##ModelId=4885B14C02DE
void* misSubsequenceLayout::get_m_MainHandle() const
{
    return m_MainHandle;
}


//##ModelId=4885B14C030D
void misSubsequenceLayout::set_m_MainHandle(void* left)
{
    m_MainHandle = left;
}


//##ModelId=4885B2C5036B
void misSubsequenceLayout::AddWindow(misWindowModel window)
{

	window.SetParentSequenceName(this->m_ParentTabName);
	window.SetParentSubSequenceName(this->GetName());
	this->childWindows.push_front(window);
}

//##ModelId=4885BAE00242
bool  misSubsequenceLayout::GetWindow(string name,misWindowModel& window)
{
	//FindAndReturnInListByName(name,this->childWindows);
		
	ListType::const_iterator   iter=this->childWindows.begin();
	ListType::const_iterator   iterEnd=this->childWindows.end();
	while (iter!=iterEnd)
	{
		string windowNmae=(*iter).GetName();
		if (windowNmae==name)
		{
			window= *iter;
			return true;
		}
		iter++;
	}
return false;
}

bool misSubsequenceLayout::GetWindow(int id, misWindowModel& window )
{
	auto found = std::find_if(childWindows.begin(), childWindows.end(), [&](auto window)
	{
		if (id == window.GetWindowIndex())
			return true;
		return false;
	});
	if (found != childWindows.end())
	{
		window = *found;
		return true;
	}
	return false;
}


////=========================================
//void misSubsequenceLayout::UnSelected()
//{
//	this->m_Active=true;
//	ListType::const_iterator   iter=this->childWindows.begin();
//	ListType::const_iterator   iterEnd=this->childWindows.end();
//	while (iter!=iterEnd)
//	{
//		void* pHybrid=(*iter)->Get3DViewer();
//		if (pHybrid)
//		{
//			//pHybrid->Active(false);
//			(*iter)->active=false;
//
//		}
//		iter++;
//	}
//
//}

//void misSubsequenceLayout::UpdateWindoesSize()
//{
//	this->m_Active=true;
//	for_each(childWindows.begin(),childWindows.end(),[&](misWindowModel  window)
//	{
//		void* pHybrid=window->Get3DViewer();
//		if (pHybrid)
//		{
//			window->UpdateWindowSize();
//
//		}
//	
//	}	);
//}

void misSubsequenceLayout::SetParentTabName( string parentTabName )
{
     this->m_ParentTabName  = parentTabName;
	 ListType::const_iterator   iter;


	 std::for_each(this->childWindows.begin(),this->childWindows.end(),[&](misWindowModel& model)
	 {
		 model.SetParentSequenceName(parentTabName);
	 });
}

string misSubsequenceLayout::get_m_ParentTabName( )
{
  return m_ParentTabName;
}

misSubsequenceLayout::misSubsequenceLayout()
{

}

bool misSubsequenceLayout::Active() const
{
	return m_Active;
}

void misSubsequenceLayout::Active(bool val)
{
	m_Active = val;
}

int misSubsequenceLayout::GetNumOfWindows()
{
	return static_cast<int>(childWindows.size());
}

misSubsequenceLayout::ListType misSubsequenceLayout::GetchildWindows()
{
	return childWindows;
}
