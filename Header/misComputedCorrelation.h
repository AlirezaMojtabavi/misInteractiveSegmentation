#pragma once

#include "IComputedCorrelation.h"
#include "ITransform.h"
#include "misLibraryMacroes.h"

// The misComputedCorrelation class is the default implementation for IComputedCorrelation. Accessing the contained transform 
// in an invalid state causes an exception to be thrown.
class MISLIBRARYEXPORT misComputedCorrelation : public IComputedCorrelation
{
public:
	misComputedCorrelation(TransformConstPtr transform, Status status, const TimePointType& lastModifiedTime);

	virtual Status GetStatus() const;
	virtual bool IsValid() const;
	virtual TransformConstPtr GetTransform() const;
	virtual TimePointType GetLastModifiedTime() const;

private:
	TransformConstPtr m_Transform;
	TimePointType m_LastModifiedTime;
	Status m_Status;
};