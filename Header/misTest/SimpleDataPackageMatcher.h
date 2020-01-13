#pragma once

#include "CompareCollections.h"
#include "ISimpleDataPackage.h"
#include "misCompeleteImageContainedPolydataDependensiesStrct.h"
#include "misCompeletePlanDataDependensiesStrct.h"
#include "misVolumeDataDependensies.h"
#include "misVolumeDataMatcher.h"
#include "PolyDataMatcher.h"
#include "misCompeletePolyDataDependensiesStrct.h"
#include "misStrctVolumeData.h"

namespace parcast
{
	class SimpleDataPackageMatcherExceptPlanRels
	{
	public:
		SimpleDataPackageMatcherExceptPlanRels(std::shared_ptr<ISimpleDataPackage> package)
			: m_Package(package)
		{
		}

		static void CheckEqual(std::shared_ptr<ISimpleDataPackage> a, std::shared_ptr<ISimpleDataPackage> b)
		{
			BOOST_CHECK(AreEqual(a, b));
		}

		bool operator()(std::shared_ptr<ISimpleDataPackage> other)
		{
			return AreEqual(m_Package, other);
		}

		static bool AreInheritedTypesEqual(std::shared_ptr<ISimpleDataPackage>& a,
			std::shared_ptr<ISimpleDataPackage>& b)
		{
			if (typeid(a) != typeid(b))
				return false;
			return true;
		}

		static bool AreEqual(std::shared_ptr<ISimpleDataPackage> a, std::shared_ptr<ISimpleDataPackage> b)
		{
			bool isEqual = true;
			isEqual &= a->GetName() == b->GetName();
			isEqual &= a->GetObjectType() == b->GetObjectType();
			isEqual &= a->GetObjectUID() == b->GetObjectUID();
			isEqual &= a->GetParametricSpline() == b->GetParametricSpline();
			isEqual &= CompareUnorderedCollections(
				a->GetImageContainedPolydataDependencies(), b->GetImageContainedPolydataDependencies(),
				AreImageContainedPolyDataDataDepsEqual);
			isEqual &= CompareUnorderedCollections(
				a->GetImageDataDependencies(), b->GetImageDataDependencies(), AreImageDataDepsEqual);
			isEqual &= CompareUnorderedCollections(
				a->GetLandMarkPoints(), b->GetLandMarkPoints(), AreLandmarkPointEqual);
			isEqual &= CompareUnorderedCollections(
				a->GetPolyDataDependencies(), b->GetPolyDataDependencies(), ArePolyDataDepsEqual);
			isEqual &= CompareUnorderedCollections(
				a->GetVolumeDataDependencies(), b->GetVolumeDataDependencies(), AreVolumeDataDepsEqual);
			isEqual &= AreInheritedTypesEqual(a, b);
			return isEqual;
		}

	private:

		static bool ArePlanDataPropertiesEqual(const misShortPlanningViewingStruct& a, const misShortPlanningViewingStruct& b)
		{
			return
				a.name == b.name &&
				a.objectUID == b.objectUID &&
				a.visibility == b.visibility &&
				a.useable == b.useable &&
				AreColorEqual(a.color, b.color) &&
				std::equal(a.TargetPoint, a.TargetPoint + 3, b.TargetPoint) &&
				std::equal(a.EntryPoint, a.EntryPoint + 3, b.EntryPoint) &&
				a.TargetpointName == b.TargetpointName &&
				a.Transparency == b.Transparency;
		}

		static bool AreColorEqual(const misColorStruct& a, const misColorStruct& b)
		{
			return
				a.red == b.red &&
				a.green == b.green &&
				a.blue == b.blue &&
				a.alpha == b.alpha;
		}

		static bool AreImageDataDepsEqual(std::shared_ptr<ICompeleteImageDependencies> a, std::shared_ptr<ICompeleteImageDependencies> b)
		{
			if (!a->GetImage() && !b->GetImage())
				return true;

			if (b->GetImage() && a->GetImage())
				return a->GetImage()->GetUID() == b->GetImage()->GetUID() &&
				a->GetName() == b->GetName() &&
				a->GetObjectUID() == b->GetObjectUID() &&
				a->GetOpacity() == b->GetOpacity() &&
				a->GetVisibility() == b->GetVisibility();

			return false;
		}

		static bool AreShort3DModelViewingEqual(
			const misShort3DModelViewingStrct& a, const misShort3DModelViewingStrct& b)
		{
			return a.color == b.color &&
				a.name == b.name &&
				a.objectContainerUID == b.objectContainerUID &&
				a.objectMarginAlarm == b.objectMarginAlarm &&
				a.objectMarginValue == b.objectMarginValue &&
				a.objectShowMargin == b.objectShowMargin &&
				a.objectUID == b.objectUID &&
				a.opacity == b.opacity &&
				a.parentImageUID == b.parentImageUID &&
				a.renderingType == b.renderingType &&
				a.segmentedObjectVisibility == b.segmentedObjectVisibility &&
				a.type == b.type &&
				a.useable == b.useable &&
				a.visibility3D == b.visibility3D &&
				a.volume == b.volume;
		}

		static bool AreImageContainedPolyDataDataDepsEqual(std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> ap,
			std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> bp)
		{
			return ap->GetAllObjectVisibility() == bp->GetAllObjectVisibility() &&
				ap->GetObjectUID() == bp->GetObjectUID() &&
				CompareUnorderedCollections(ap->GetPolydataStrcViewing(), bp->GetPolydataStrcViewing(), AreShort3DModelViewingEqual);
		}

		static bool AreLandmarkPointEqual(const misLandmarkPointStrct& a, const misLandmarkPointStrct& b)
		{
			return a.direction == b.direction &&
				a.pointType == b.pointType &&
				a.position == b.position;
		}

		static bool ArePolyDataDepsEqual(
			const misCompeletePolyDataDependensiesStrct& a, const misCompeletePolyDataDependensiesStrct& b)
		{

			return a.color == b.color &&
				a.name == b.name &&
				a.objectUID == b.objectUID &&
				a.opacity == b.opacity &&
				a.parentImageUID == b.parentImageUID &&
				a.Visibility == b.Visibility &&
				PolyDataMatcher::AreEqual(*a.objectPointer, *b.objectPointer);
		}

		static bool AreVolumeDataDepsEqual(
			std::shared_ptr<IVolumeDataDependency> ap,
			std::shared_ptr<IVolumeDataDependency> bp)
		{

			if (!(ap->GetAllObjectVisibility() == bp->GetAllObjectVisibility() &&
				ap->GetAutomaticallyCreated() == bp->GetAutomaticallyCreated() &&
				ap->GetObjectUID() == bp->GetObjectUID() &&
				ap->GetVisibilityIn2D() == bp->GetVisibilityIn2D()))
				return false;
			if (ap->GetImage() && bp->GetImage() && ap->GetImage()->GetUID() != bp->GetImage()->GetUID())
				return false;
			if (ap->GetTransferFunction() && bp->GetTransferFunction())
				return *ap->GetTransferFunction() == *bp->GetTransferFunction();
			return true;
		}

		static bool AreVolumeDataEqual(const misVolumeData& a, const misVolumeData& b)
		{
			return false;
		}

		std::shared_ptr<ISimpleDataPackage> m_Package;
	};


	class SimpleDataPackageMatcher
	{
	public:
		SimpleDataPackageMatcher(std::shared_ptr<ISimpleDataPackage> package)
			: m_Package(package)
		{
		}

		static void CheckEqual(std::shared_ptr<ISimpleDataPackage> a, std::shared_ptr<ISimpleDataPackage> b)
		{
			BOOST_CHECK(AreEqual(a, b));
		}

		bool operator()(std::shared_ptr<ISimpleDataPackage> other)
		{
			return AreEqual(m_Package, other);
		}

		static bool AreInheritedTypesEqual(std::shared_ptr<ISimpleDataPackage>& a,
			std::shared_ptr<ISimpleDataPackage>& b)
		{
			if(typeid(a) != typeid(b))
				return false;
			return true;
		}

		static bool AreEqual(std::shared_ptr<ISimpleDataPackage> a, std::shared_ptr<ISimpleDataPackage> b)
		{
			bool isEqual = true;
			isEqual &= SimpleDataPackageMatcherExceptPlanRels::AreEqual(a, b);
			isEqual &= CompareUnorderedCollections(
				*a->GetPlanDataDependencies(), *b->GetPlanDataDependencies(), ArePlanDataDepsEqual);

			return isEqual;
		}

	private:

		static bool ArePlanDataDepsEqual(
			std::shared_ptr<parcast::IPackagePlanRel> ap,
			std::shared_ptr<parcast::IPackagePlanRel> bp)
		{
			return ap->GetPlanEntity()->GetUID() == bp->GetPlanEntity()->GetUID() &&
				ap->GetPackage()->GetObjectUID() == bp->GetPackage()->GetObjectUID() &&
				Mis3DModelObjectOpacityPropertiesEqual(ap->GetVisibility(), bp->GetVisibility());
		}

		static bool Mis3DModelObjectOpacityPropertiesEqual(mis3DModelObjectOpacityPropertiesStrct& a, mis3DModelObjectOpacityPropertiesStrct& b)
		{
			return
				a.GetOpacityIn2DScene() == b.GetOpacityIn2DScene() &&
				a.GetVisibilityIn3DScene() == b.GetVisibilityIn3DScene();
		}

		std::shared_ptr<ISimpleDataPackage> m_Package;
	};

}

