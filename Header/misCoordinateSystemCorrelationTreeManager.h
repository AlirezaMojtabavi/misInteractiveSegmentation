#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "misLibraryMacroes.h"
#include <itkSimpleFastMutexLock.h>

// The misCoordinateSystemCorrelationTreeManager class is the default implementation for ICoordinateSystemCorrelationManager.
// It stores correlation between coordinate systems as a weighted tree with nodes representing coordinate systems and the biased
// edge between two nodes representing the transform from the source to destination. As the correlation storage is implemented as
// a tree, loops cannot be allowed, i.e. there can only exist one path (a unique computed transform) between a given source 
// and destination coordinate system. As such each coordinate system must be associated with at most 2 other coordinate systems.
// If there are N coordinate systems, exactly N-1 correlations are needed to make the system fully connected so that a correlation
// can be computed between any two coordinate systems.
// The misCoordinateSystemCorrelationTreeManager does not dereference the coordinate system pointers and therefore their 
// validity at any point does not affect its operation. Operation of this class depends on individual correlations between each
// pair of coordinate systems. The transforms representing correlations between coordinate systems are therefore shared pointers
// to ensure that they remain valid as long as misCoordinateSystemCorrelationTreeManager holds a reference to them. The reference
// is released whenever a direct connection is removed (through deconcatenation) or replaced (through a call to SetTransform or 
// concatenation).
class MISLIBRARYEXPORT misCoordinateSystemCorrelationTreeManager : 
	public ICoordinateSystemCorrelationManager< std::string >
{
public:
	typedef std::shared_ptr<IComputedCorrelation> ComputedCorrelationPtr;
	typedef std::shared_ptr< ITimedValidator<TransformConstPtr> > TimedTransformPtr;

	class MISLIBRARYEXPORT Injector
	{
	public:
		virtual ComputedCorrelationPtr CreateComputedCorrelation(
			TransformConstPtr transform, IComputedCorrelation::Status status, 
			const IComputedCorrelation::TimePointType &lastModifiedTime) const;

		virtual TimedTransformPtr CreateTimedTransform(TransformConstPtr transform, bool isTimed, double lifeTime) const;

		virtual std::shared_ptr<ITransform> CreateIdentityTransform() const;
	};

	// Creates an empty correlation manager with no coordinate systems.
	misCoordinateSystemCorrelationTreeManager(std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());
	~misCoordinateSystemCorrelationTreeManager(void);

	// Sets the direct correlation from the source to destination after ensuring that no indirect correlation between them already
	// exists. If there is an indirect correlation between the two coordinate system (even if expired), the call will fail 
	// throwing an exception. If there is a prior direct connection between the two (regardless of the direction), it 
	// will be replaced.
	virtual void SetTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TimedTransformConstPtr transform);
	virtual void SetTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TransformConstPtr transform);

	virtual void RemoveTransform( const CoordinateSystemType & source, const CoordinateSystemType &destination );

	virtual ComputedCorrelationConstPtr GetTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination) const;

	virtual void ConcatTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TransformConstPtr transform);

	virtual void DecatTransform(const CoordinateSystemType &source, const CoordinateSystemType &destination);

	virtual std::list<DirectCorrelation> GetDirectCorrelationsList() const;

	virtual void SetDirectCorrelationsList( const std::list<DirectCorrelation>& newList );

	virtual void PurgeInvalidCorrelations();

private:
	typedef std::shared_ptr<ITransform> TransformPtr;

	// Gets the compound transform from the specified source to destination. Since it uses a recursive method to traverse from 
	// source to destination, when going to the next level, to avoid traversing back to current node, the current node must be 
	// specified to be excluded when traveling from the next node in recursion. It returns the validity status of the correlation.
	// Also, on return, the resultTransform and lastModifiedTime parameters will contain the resulting transform and the last
	// modified time of the correlation (last time any of the transforms along the path from source to destination was set).
	virtual IComputedCorrelation::Status GetTransformRecursive(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, 
		const CoordinateSystemType &excludeFromTraversal, TransformConstPtr &resultTransform, 
		IComputedCorrelation::TimePointType& lastModifiedTime) const;

	// Gets the transform from source to destination if there is a DIRECT correlation between them. If the existing correlation is 
	// from destination to source, inverse of its transform is returned. If no DIRECT correlation between the two exists, a null
	// pointer is returned. The returned transform is a copy of the stored transform and it can be safely modified if necessary or
	// passed out of the class. On return, the output parameter isValid will determine whether the transform is still valid (or
	// it is expired).
	TransformPtr GetDirectTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, bool *isValid = NULL, 
		IComputedCorrelation::TimePointType *transformCreationTime = NULL) const;

	std::list<DirectCorrelation> m_CorrelationTree;
	
	std::shared_ptr<Injector> m_Injector;
	itk::SimpleMutexLock* m_CorrelationTree_mtx;
};