#include "stdafx.h"
#include "..\Header\ShowImagesAdapter2D.h"


parcast::ShowImagesAdapter2D::ShowImagesAdapter2D(std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> viewers)
	: m_2DViewers(viewers)
{
}

void parcast::ShowImagesAdapter2D::ShowImages(std::shared_ptr<const ICompeleteImageDependencies> images) const
{

}
 