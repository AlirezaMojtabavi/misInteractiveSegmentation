#pragma once

class IImage;

namespace parcast
{

	class IImageFactory
	{
	public:
		virtual std::shared_ptr<IImage> CreateImage() const = 0;
	};

}

