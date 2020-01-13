#pragma once

class ITrackingTool;

namespace parcast
{

	class IStaticTransformUpdater
	{
	public:
		virtual void Update(std::shared_ptr<ITrackingTool> subjectTool) = 0;
	};

}