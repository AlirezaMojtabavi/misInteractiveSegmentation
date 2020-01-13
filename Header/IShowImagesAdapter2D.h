#pragma once
#include "ICompeleteImageDependencies.h"

namespace parcast
{
	class IShowImagesAdapter2D
	{
	public:
		virtual void ShowImages(std::shared_ptr<const ICompeleteImageDependencies> images) const= 0;
		virtual ~IShowImagesAdapter2D() = default;
	};
}
