#pragma once
namespace parcast
{

	struct VolumeColormap
	{
		std::string Uid;
		std::string VolumeUid;
		std::string Name;
		std::string Viewing;
		bool AutomaticColorMode;
		float	MinimumThreshold;
		float	MaximumThreshold;
		bool	UseDefaultThreshold;
		bool	UseDefaultMaximumThreshold;

		struct ColorType
		{
			double Alpha;
			long long int Red;
			long long int Green;
			long long int Blue;
		};
		ColorType Color;
	};
}