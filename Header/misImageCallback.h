#pragma once

#include "I2DRepresentation.h"
#include "misPlanarRepresentation.h"

//color/level setting
class  misImageCallback : public vtkCommand
{

 
	

public:
	static misImageCallback* New();
 
	misImageCallback();
	std::shared_ptr<I2DRepresetation> GetImageRep() const ;
	void SetImageRep(std::shared_ptr<I2DRepresetation> val);
	void SetSize(int* size);
	void SetCurrentWindowLevel(misWindowLevelStr winLevStr);
	void SetDefaultWindowLevel(misWindowLevelStr winLevStr);
	//-----------------------------

	void Execute(vtkObject *caller,unsigned long event,void *vtkNotUsed(callData));
	//void SetContrastChaningScaling(double scale);
	void SetContrastInteraction( bool cntr );
	bool GetContrastInteraction();

	
private:
	template <typename T>
	inline T sign(T x)
	{
		if (x == 0)
			return 0;
		return x > 0 ? 1 : -1;
	}
	
	misWindowLevelStr m_CurrentLevelWindow;
	misWindowLevelStr m_InitialLevelWindow;

	double m_Scaling;
	int    m_size[2];
	int    flag;

	bool m_IsContrastInteractionActive;
	std::weak_ptr<I2DRepresetation>  m_pImageRep;


	void UpdateCurrentWindowLevel(vtkInteractorStyleImage *interaction);
	void UpdateScaling(void);

};
