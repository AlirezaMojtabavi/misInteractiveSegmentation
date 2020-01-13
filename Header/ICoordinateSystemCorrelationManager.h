#pragma once

#include "IComputedCorrelation.h"
#include "ICoordinateSystem.h"
#include "ITimedValidator.h"
#include "ITransform.h"
#include "misLibraryMacroes.h"

// The ICoordinateSystemCorrelationManager template provides a type independent abstract interface for classes that maintain
// a set of coordinate systems and their correlations with one another.
// It allows other subsystems that assign a local coordinate system to different spatial objects (such as tracker, tracking
// tools, medical images, ...) to store spatial correlation between those spatial objects by specifying two spatial objects
// and the means of transforming the source coordinate system to destination coordinate system. Thus, these subsystems can
// create an interconnected network of spatial objects in which a transform can be computed to transform each of the coordinate
// systems to another one, provided that the two coordinate systems are either directly or indirectly connected.
// The following example should clarify the usage of ICoordinateSystemCorrelationManager.
// Imagine a tracker, 3 tracking tools (one for navigation, one for registration, and one used as reference for registration), and 
// two medical images (a CT and an MR image). These elements form our setup for image guided surgery. Different tasks throughout
// an image guided surgery application require knowledge of a spatial correlation between each two of the elements. 
// - A correlation between the two images must be worked out before they can be used together. 
// - Both images must be usable in navigation and therefore there must be a correlation between the navigation tool tip and the
//   images.
// - For the navigation to be possible, a fixed correlation between one of the tracking tools (reference) and the images must
//   exist. This is the registration transform.
// - To work out the registration transform, a more specialized tracking tool (registration tool) is used, and thus its correlation
//   with the reference tool must be known during the registration process.
// - and the list could go on ...
// Assuming the above 6 elements, we can build a connected, directional, weighted tree whose vertices are the elements, and 
// whose edges determine the transform from the element on the source vertex to the destination vertex. That is, we shall need 
// exactly 5 transforms (one for each edge). Then, correlation between each two elements can be found by taking the correlation 
// initially to be an identical transform and consecutively concatenate it to the transforms on the edges along the way to 
// the destination vertex. For each edge, if it is traversalong its direction, its nominal transform is concatenated, and 
// if it is traversed in the opposite direction, its inverse transform is used in concatenation.
// Other particular implementations of this abstract concept might be introduced which use a graph (rather than a tree) for
// storing coordinate systems and their correlations.
// The types of the coordinate system objects is irrelevant to their correlations, and therefore it is taken as a template 
// argument. Furthermore, ICoordinateSystemCorrelationManager implementations only store pointers to const ITransform
// objects and the retrieved transforms are either mutable copies of the original transform or newly generated ones. Therefore 
// integrity of the transforms is guaranteed even though the ICoordinateSystemCorrelationManager is shared by different subsystems.
//
// NOTE: It is of utmost importance that the interpretation of the transform from source to destination be strictly shared
// by all the clients using the same instance of ICoordinateSystemCorrelationManager. As a convention, all client code can 
// assume that the transform from source to destination signifies a transform that scales, rotates, and translates the source
// coordinate system (origin point and axes) to lie on the destination coordinate system.
template < typename CST >
class ICoordinateSystemCorrelationManager
{
public:
	typedef CST CoordinateSystemType;
	typedef std::shared_ptr<const ITransform> TransformConstPtr;
	typedef std::shared_ptr< const ITimedValidator<TransformConstPtr> > TimedTransformConstPtr;
	typedef std::shared_ptr<const IComputedCorrelation> ComputedCorrelationConstPtr;

	// The whole correlation tree is retrieved as a list of direct correlation items.
	struct MISLIBRARYEXPORT DirectCorrelation
	{
		DirectCorrelation(const CoordinateSystemType &source, const CoordinateSystemType &destination, 
			TimedTransformConstPtr transform)
			: m_Source(source), m_Destination(destination), m_Correlation(transform) { }

		CoordinateSystemType m_Source;
		CoordinateSystemType m_Destination;
		TimedTransformConstPtr m_Correlation;
	};

	// Sets the direct correlation transform between specified pair of source and destination coordinate systems. If the direct 
	// connection from source to destination already exists, it will be replaced.
	virtual void SetTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TransformConstPtr transform) = 0;

	// This overload of SetTransform, in addition to setting the transform, ensures that the stored transform will be valid for
	// limited time by storing a timed version of transform.
	virtual void SetTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TimedTransformConstPtr transform) = 0;

	// Removes the direct correlation between two coordinate systems if any has been set previously using SetTransform 
	// (regardless of the direction in which the direct correlation has previously been set)
	virtual void RemoveTransform(const CoordinateSystemType & source, const CoordinateSystemType &destination) = 0;

	// Gets the computed transform from the source to destination coordinate systems. See IComputedCorrelation.
	virtual ComputedCorrelationConstPtr GetTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination) const = 0;

	// If there already exists a direct connection from the source to destination, it concatenates the specified
	// transform to it, otherwise sets it as the new direct connection. See DecatTransform()
	virtual void ConcatTransform(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TransformConstPtr transform) = 0;

	// Decatenates a previously concatenated transform to the direct connection between source and destination. If only one 
	// transform has been set on the pair (no concatenations), the connection is removed.
	virtual void DecatTransform(const CoordinateSystemType & source, const CoordinateSystemType &destination) = 0;

	// Retrieves all the contents of the correlation manager as a list of direct correlation items. This can be used to store
	// all the correlation data to a permanent storage. See SetDirectCorrelationsList().
	virtual std::list<DirectCorrelation> GetDirectCorrelationsList() const = 0;

	// Replace the contents of the correlation manager with a new list of direct correlation items. If the correlation manager
	// already contains data, they will be removed. This can be used to restore data from a permanent storage back to the 
	// correlation manager. See GetDirectCorrelationsList().
	virtual void SetDirectCorrelationsList(const std::list<DirectCorrelation>& newList) = 0;

	// Purges the internal storage of direct correlations of those that are expired.
	virtual void PurgeInvalidCorrelations() = 0;

	virtual ~ICoordinateSystemCorrelationManager() { }
};

template <typename T> 
std::ostream& operator<<(std::ostream& outStr, const ICoordinateSystemCorrelationManager<T>& correlationManager)
{
	auto directCorrelations = correlationManager.GetDirectCorrelationsList();
	outStr << "CorrelationManager{ ";
	for (auto corrItr = directCorrelations.cbegin(); corrItr != directCorrelations.cend(); ++corrItr)
	{
		if (corrItr != directCorrelations.cbegin())
			outStr << std::endl;
		outStr << "DirectCorrelation{ Source{ " << corrItr->m_Source << " }, Destination{ " << corrItr->m_Destination << 
			" }, TimedTransform{ " << *corrItr->m_Correlation << " }";
	}
	return outStr << " }" << std::endl;
}