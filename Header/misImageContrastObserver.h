#pragma once

#include "I2DRepresentation.h"
#include "misPlanarRepresentation.h"
#include "WindowLevelSetting.h"

 
class  misImageContrastObserver : public vtkCommand
{

public:
	static misImageContrastObserver* New();
	vtkBaseTypeMacro(misImageContrastObserver, vtkCommand);
	void SetWindowLevel(std::shared_ptr<parcast::WindowLevelSetting> windowLevel);

	std::shared_ptr<I2DRepresetation> GetImageRep() const ;
	void SetImageRep(std::shared_ptr<I2DRepresetation> val);
	void Execute(vtkObject *caller,unsigned long event,void *vtkNotUsed(callData));

private:

	std::weak_ptr<I2DRepresetation>  m_pImageRep;
	std::shared_ptr<parcast::WindowLevelSetting>  m_WindowLevelSetting;
};
