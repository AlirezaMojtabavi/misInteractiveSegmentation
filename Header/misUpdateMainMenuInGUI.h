#pragma once
#include "misUpadateTabStateAbstract.h"

class misUpdateMainMenuInGUI
{
public:
	misUpdateMainMenuInGUI(itk::Object::Pointer parent);
	void UpdateMainMenuInGUI(TabAbstractStateListTypdef states);
private:
	std::shared_ptr<misUpadateTabStateAbstract>  m_UpadateTabStateAbstract;
	itk::Object::Pointer m_Parent;

};

