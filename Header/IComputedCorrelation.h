#pragma once

#include "ITransform.h"
#include "misLibraryMacroes.h"

// IComputedCorrelation provides an abstract interface to classes serving as light-weight containers for correlations computed by 
// ICoordinateSystemCorrelationManager implementations. Before the contained transform is used, its status must be checked for 
// validity.
class IComputedCorrelation
{
public:
	typedef std::shared_ptr<const ITransform> TransformConstPtr;
	typedef boost::chrono::high_resolution_clock::time_point TimePointType;

	// Status of the computed transform from one coordinate system to another.
	enum Status
	{
		// A correlation between the two was found and it is represented by the accompanying transform.
		Valid,

		// A correlation between the two was found, however it is not valid. It might have been expired and therefore be unreliable.
		Invalid,

		// A correlation between the two coordinate systems was not found and the accompanying transform must not be used.
		NoCorrelation
	};

	// Gets the status of the computation result. See Status.
	virtual Status GetStatus() const = 0;

	// Short-hand method that determines whether the status is Status::Valid.
	virtual bool IsValid() const = 0;

	// Gets the last time any of the transforms on the path from the source to destination coordinate system in the correlation 
	// manager was set or modified.
	virtual TimePointType GetLastModifiedTime() const = 0;

	// Gets the computed transform. Make sure that the computation result is valid before accessing the transform. Errors might
	// occur if the transform is used in an invalid state.
	virtual TransformConstPtr GetTransform() const = 0;

	virtual ~IComputedCorrelation(void) { }
};

