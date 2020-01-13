#pragma once


#include "misModelObserver.h"
#include "misSubsequenceLayout.h"

class MISLIBRARYEXPORT misGroupTab :public misOldObject
{
private:
	std::string   m_tabNmae;
	misModelObserver::Pointer  m_Observer;

public:

	typedef misGroupTab                         Self;
	typedef misOldObject                    Superclass;
	typedef ::itk::SmartPointer< Self >       Pointer;
	typedef ::itk::SmartPointer< const Self > ConstPointer;
	static Pointer New(void);
	void SetObserver(misModelObserver::Pointer observer);
	int get_m_ID() const;
	void set_m_ID(int left);
	std::string get_m_Name() const;
	std::string get_m_TabName() const;
	void   set_m_TabName(std::string left);
	bool  GetSubTab(std::string name, misSubsequenceLayout&  subtab);
	void set_m_Name(std::string left);
	int GetSubTabCount() { return m_SubTabs.size(); }
	std::list<misSubsequenceLayout> m_SubTabs;
	typedef std::list<misSubsequenceLayout>  ListType;
private:
	int m_ID;
	std::string m_Name;
};

 
