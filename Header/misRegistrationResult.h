#pragma once

#include "misEnums.h"
#include "misTypes.h"

// keep registration result information  -------------------------------------
//---

class  misRegistrationResult

{
public:

	misRegistrationResult(void);
	void Reset();
	void DeepCopy(misRegistrationResult* pInputStr);
	void SetLandmarkRegistraionData(misUID packageUID,vtkMatrix4x4* pLandmarkReg);
	bool SetReferenceToolUID(misUID referenceToolUID);
	void SetSurfaceRegistraionData(vtkMatrix4x4* pSurfaceReg);
	misRegistationStatus GetRegistrationStatus() const;
	void SetRegistrationStatus(misRegistationStatus val);
	void ResetSurfaceRegistraionData();
	vtkMatrix4x4* GetSurfaceRegMatrix() const;
	void SetSurfaceRegMatrix(vtkMatrix4x4* val);
	vtkMatrix4x4* GetLandmarkRegMatrix() const;
	void SetLandmarkRegMatrix(vtkMatrix4x4* val);
 	misUID GetReferenceToolUID() const;
	misUID GetPackageUID() const;
	void SetPackageUID(const misUID& packageUID);

private:

	misUID                m_PackageUID;
	misUID				  ReferenceToolUID;
	misRegistationStatus  registrationStatus;
	vtkMatrix4x4*		  m_LandmarkRegMatrix;
	vtkMatrix4x4*		  m_SurfaceRegMatrix;
};
