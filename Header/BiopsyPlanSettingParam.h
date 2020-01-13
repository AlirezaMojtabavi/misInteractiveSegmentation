#pragma once

namespace parcast
{
	struct PlanSettingParam
	{
		struct IntersectionColor
		{
			float r;
			float g;
			float b;
			float opacity;
		}intersectionColor;

		float intersectionRadius;
		float borderInlineOpacity;
		float borderOpacity;
		bool displayCrossSection;
		bool displayProjection;
		float planDiameter;
		float dashLineSize;
	};
}
