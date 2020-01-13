#pragma once
#ifndef misStandardMatrix_H
#define misStandardMatrix_H

#include "misPrimaeryNeededHeader.h"
#include "misStrctPatientData.h"

class    misStandardMatrix
{
public:
	static   vtkMatrix4x4* GetTranformMatrix   (misPatientPosition  patientPosition);
	static   vtkMatrix4x4* GetInvTranformMatrix(misPatientPosition  patientPosition);

	static   bool          CompareTransform(vtkMatrix4x4* firstMatrix, vtkMatrix4x4* secondMatrix);

	misStandardMatrix(void);
	~misStandardMatrix(void);
};

#endif
