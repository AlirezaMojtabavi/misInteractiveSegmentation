#pragma once
#include "misToolProperties.h"

class I3DLandmarkViewer;

namespace parcast
{
	class IToolRepresentationDecider
	{
	public:
		virtual misToolRepresentationType GetToolRepType() = 0;
		virtual ~IToolRepresentationDecider() = 0;
	};
}