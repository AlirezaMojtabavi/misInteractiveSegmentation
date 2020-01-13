#pragma once
#include "BusinessEntities\Point.h"
#include "ITransform.h"

namespace parcast
{

	class IAutomaticVirtualTipUpdater
	{

	public:
		virtual ~IAutomaticVirtualTipUpdater() = default;

		virtual void SetEnabled(bool isAutomaticMode) = 0;
		virtual void Update(
			std::weak_ptr<const ITransform> toolTransform,
			parcast::PointD3 const& targetPos,
			double const& targetRadius)  = 0;
		virtual boost::optional<double> GetLength() const = 0;
	};

}