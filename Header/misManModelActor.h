#pragma once

#include "misStickerModelActor.h"
#include "misCamera.h"

class misManModelActor : public misStickerModelActor
{

public:
	static misManModelActor*  New();

	misManModelActor(void);
	~misManModelActor(void);

protected:
	void ModifyManModelOrientation(double* worldPt);

	void GetObjectToCameraVector(double * OC);

	virtual void GetMatrix(vtkMatrix4x4 *result) override;

	void GetLeftUpPoint(double manModelDesiredPosition, double* worldRDPt);

	void GetRightUpPoint(double manModelDesiredPosition, double* worldRUPt);

	double CalculateManModelDesiredPosition();

	misCamera m_PreviousCamera;
	vtkSmartPointer<vtkMatrix4x4> m_LastResult;
	bool m_MatrixInilized;
	int m_Windowsize[2];
};

