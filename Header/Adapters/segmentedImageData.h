#pragma once

namespace parcast
{
	typedef std::shared_ptr<std::vector<std::uint8_t>> ByteArrayPtr;
	struct SegmentedImageData
	{
		std::string	ImageUid;
		std::string	ImagePrimaryUid;
		std::string	SolutionUid;
		std::string	ImageName;
		ByteArrayPtr Extent;
		ByteArrayPtr Spacing;
		ByteArrayPtr Roi;
	};
}