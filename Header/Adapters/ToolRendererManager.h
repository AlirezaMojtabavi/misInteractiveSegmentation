#pragma once
#include "ICoordinateSystemRenderer.h"

namespace parcast
{
	class ToolRendererManager
	{
	public:
		ToolRendererManager() = default;
		void AddToolRenderer(std::weak_ptr<ICoordinateSystemRenderer> tool);
		void DisplayTools();
		void HideTools();
		void ClearTools();
	private:
		std::vector<std::weak_ptr<ICoordinateSystemRenderer>> m_Tools;
	};
}
