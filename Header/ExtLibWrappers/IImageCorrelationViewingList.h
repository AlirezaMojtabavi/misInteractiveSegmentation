#pragma once
#include "misGuiStructures.h"

namespace parcast
{

	class IImageCorrelationViewingList
	{
	public:
		virtual ~IImageCorrelationViewingList() = default;
		virtual std::vector<ImageViewingCorrelationStruct> Get(ImageListViewingType viewingType) const = 0;
	};

}