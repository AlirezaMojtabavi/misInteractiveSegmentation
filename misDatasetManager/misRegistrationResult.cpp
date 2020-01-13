#include "StdAfx.h"
#include "misRegistrationResult.h"

misRegistrationResult::misRegistrationResult()
	: m_LandmarkRegMatrix(vtkMatrix4x4::New()), m_SurfaceRegMatrix(vtkMatrix4x4::New())
{
	this->Reset();
}
void misRegistrationResult::DeepCopy( misRegistrationResult* pInputStr )
{
	if (pInputStr)
	{
		this->m_PackageUID         = pInputStr->GetPackageUID();
		this->ReferenceToolUID   = pInputStr->GetReferenceToolUID();
		this->registrationStatus = pInputStr->GetRegistrationStatus();

		this->m_LandmarkRegMatrix->DeepCopy(pInputStr->GetLandmarkRegMatrix());
		this->m_SurfaceRegMatrix->DeepCopy(pInputStr->GetSurfaceRegMatrix());
	}
	else
	{
		this->Reset();
	}
}

void misRegistrationResult::SetLandmarkRegistraionData( misUID packageUID,vtkMatrix4x4* pLandmarkReg )
{
	this->m_PackageUID = packageUID;

	if (pLandmarkReg)
	{
		this->m_LandmarkRegMatrix->DeepCopy(pLandmarkReg);

		this->registrationStatus = landmarkBasedRegistration;
	}
	else
	{
		this->Reset();
	}
}

void misRegistrationResult::SetSurfaceRegistraionData( vtkMatrix4x4* pSurfaceReg)
{
	if (landmarkBasedRegistration == this->registrationStatus)
	{
		if ( pSurfaceReg)
		{
			this->m_SurfaceRegMatrix->DeepCopy(pSurfaceReg);
			this->registrationStatus = surfaceBasedRegistration;
		}
	}
	else
	{
		this->m_SurfaceRegMatrix->Identity();
	}
}

void misRegistrationResult::ResetSurfaceRegistraionData()
{
	if (surfaceBasedRegistration == this->GetRegistrationStatus())
	{
		this->m_SurfaceRegMatrix->Identity();

		this->registrationStatus = landmarkBasedRegistration;
	}
}



void misRegistrationResult::Reset()
{
	m_PackageUID = "";
	ReferenceToolUID = "";
	registrationStatus = NoRegistartion;

	m_LandmarkRegMatrix->Identity();
	m_SurfaceRegMatrix->Identity();
}

bool misRegistrationResult::SetReferenceToolUID( misUID referenceToolUID )
{
	if (this->ReferenceToolUID == referenceToolUID)
	{
		return true;
	}

	if(referenceToolUID == "")
	{
		_ASSERT(0);
		return false;
	}

	if(this->ReferenceToolUID == "")
	{
		this->ReferenceToolUID = referenceToolUID; 
		return true;
	}
 return false;
}



misRegistationStatus misRegistrationResult::GetRegistrationStatus() const
{
	return registrationStatus;
}

void misRegistrationResult::SetRegistrationStatus( misRegistationStatus val )
{
	registrationStatus = val;
}

vtkMatrix4x4* misRegistrationResult::GetLandmarkRegMatrix() const
{
	return m_LandmarkRegMatrix;
}

void misRegistrationResult::SetLandmarkRegMatrix( vtkMatrix4x4* val )
{
	m_LandmarkRegMatrix = val;
}

vtkMatrix4x4* misRegistrationResult::GetSurfaceRegMatrix() const
{
	return m_SurfaceRegMatrix;
}

void misRegistrationResult::SetSurfaceRegMatrix( vtkMatrix4x4* val )
{
	m_SurfaceRegMatrix = val;
}

misUID misRegistrationResult::GetPackageUID() const
{
	return m_PackageUID;
}

void misRegistrationResult::SetPackageUID( const misUID& packageUID )
{
	m_PackageUID = packageUID;
}

misUID misRegistrationResult::GetReferenceToolUID() const
{
	return ReferenceToolUID;
}

