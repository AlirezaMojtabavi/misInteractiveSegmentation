#include "stdafx.h"
#include "misImageContrastObserver.h"

vtkStandardNewMacro(misImageContrastObserver);

void misImageContrastObserver::SetWindowLevel(std::shared_ptr<parcast::WindowLevelSetting> windowLevel)
{
	m_WindowLevelSetting = windowLevel;
}

std::shared_ptr<I2DRepresetation> misImageContrastObserver::GetImageRep() const
{
	return m_pImageRep.lock();
}

void misImageContrastObserver::SetImageRep(std::shared_ptr<I2DRepresetation> val)
{
	m_pImageRep = val; 
}

void misImageContrastObserver::Execute(vtkObject *caller,unsigned long event,void *vtkNotUsed(calu8lData))
{
	if (event == vtkCommand::ResetWindowLevelEvent)
		m_WindowLevelSetting->Reset();

	if (event == vtkCommand::WindowLevelEvent)
	{
		auto *interaction = dynamic_cast<vtkInteractorStyleImage *>(caller);
		auto startPosition = parcast::Point<int, 2>(interaction->GetWindowLevelStartPosition()[0],
			interaction->GetWindowLevelStartPosition()[1]);
		auto currentPosition = parcast::Point<int, 2>(interaction->GetWindowLevelCurrentPosition()[0],
			interaction->GetWindowLevelCurrentPosition()[1]);

		m_WindowLevelSetting->Update(startPosition, currentPosition);
		m_WindowLevelSetting->SetContrastInteraction(true);

	}
	else
		m_WindowLevelSetting->SetContrastInteraction(false);
	auto imageRep = m_pImageRep.lock();
	if (imageRep)
		imageRep->SetWindowLevel(m_WindowLevelSetting->GetCurrentWindowLevel());

}

 

 


