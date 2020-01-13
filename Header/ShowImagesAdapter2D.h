#pragma once
#include "IShowImagesAdapter2D.h"
#include "IPackage2DDataRenderingAdapter.h"

namespace parcast
{
	class ShowImagesAdapter2D :
		public IShowImagesAdapter2D
	{
	public:
		ShowImagesAdapter2D(std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> );
		void ShowImages(std::shared_ptr<const ICompeleteImageDependencies> images) const override;
	private:
		std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> m_2DViewers;

	};
}
