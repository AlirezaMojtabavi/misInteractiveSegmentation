#pragma once

#ifndef misImageDirectionCalculation_H
#define misImageDirectionCalculation_H

#include "misObject.h"
#include "misImage.h"

class  misImageDirectionCalculation :public misObject
{
private:

	vtkTransform* m_FinalTransform;
	vtkTransform* m_Model3DTransform;
	vtkTransform* m_ImageTransform;

protected:
	misCreateVariableWithProtectedSetGetMacro(ConfirmedDirectionStatus,bool);

public:

	igstkStandardClassBasicTraitsMacro( misImageDirectionCalculation, misObject );

	//void SetInputImage(misImage* pImage);
 //   void UpdateTransform(void);
    vtkTransform* GetConfirmedTransform(void);

	misImageDirectionCalculation(void);
	~misImageDirectionCalculation(void);
};

#endif
