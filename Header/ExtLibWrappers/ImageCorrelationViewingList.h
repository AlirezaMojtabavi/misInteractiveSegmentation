#pragma once
#include "IImageCorrelationViewingList.h"
#include "ICoordinateSystemRepository.h"
#include "ICoordinateSystemCorrelationManager.h"

namespace parcast
{

	class ImageCorrelationViewingList : public IImageCorrelationViewingList
	{

	public:
		explicit ImageCorrelationViewingList(
			std::shared_ptr<ICoordinateSystemRepository> coordinateSystemRepository,
			std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager);

		std::vector<ImageViewingCorrelationStruct> Get(ImageListViewingType viewingType) const override;

	private:

		std::shared_ptr<ICoordinateSystemRepository> m_CoordinateSystemRepository;
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CSCorrelationManager;

	};

}