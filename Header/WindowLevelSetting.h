#pragma once
#include "BusinessEntities\Point.h"
#include <misWindowLevelStr.h>
namespace parcast
{
	class WindowLevelSetting
	{
	public:
		WindowLevelSetting();
		void Update(const parcast::Point<int, 2>& startPosition, const parcast::Point<int, 2>& currentPosition);
		void Reset();
		void UpdateScaling(void);
		void SetContrastInteraction(bool );
		bool GetContrastInteraction();
		void SetSize(int* size);
		void SetCurrentWindowLevel(misWindowLevelStr winLevStr);
		void SetDefaultWindowLevel(misWindowLevelStr winLevStr);
		misWindowLevelStr GetCurrentWindowLevel() const;

	private:
		misWindowLevelStr m_CurrentLevelWindow;
		misWindowLevelStr m_InitialLevelWindow;
		parcast::Point<int, 2> m_PrevStartPosition;
		template <typename T>
		inline T sign(T x)
		{
			if (x == 0)
				return 0;
			return x > 0 ? 1 : -1;
		}


		double m_Scaling;
		int    m_size[2];
		int    flag;

		bool m_IsContrastInteractionActive;
	};

}
