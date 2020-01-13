#pragma once

#include "misGUITypes.h"

class misSolutionProperty;
class misTabAndSubTabName;

class misSolutionControlGuiAdapter
{
public:
	misSolutionControlGuiAdapter(
		std::shared_ptr<misSolutionProperty> solutionProperty, misTabAndSubTabName* tabAndSubTabName,  itk::Object::Pointer parent);
	~misSolutionControlGuiAdapter();

	void UpdateGerenralPropertiesInGUI(TabAbstractStateListTypdef states);
	void UpdateMainMenuInGUI(TabAbstractStateListTypdef states, const std::string& sequnec, const std::string& subSequnec);

private:

	void UpdateAdressesInGUI(void);
	void UpdatePatientUploadingStatusInGUI(void);
	std::shared_ptr<misSolutionProperty> m_SoloutionProperty;
	misTabAndSubTabName* m_TabAndSubTabName;
	itk::Object::Pointer m_Parent;
 
};

