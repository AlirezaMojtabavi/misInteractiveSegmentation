#pragma once

#include "ChainBool.h"
#include "misNavigationEvent.h"

namespace parcast
{

	class VirtualTipAutomaticLengthEventMatcher
	{
	public:
		VirtualTipAutomaticLengthEventMatcher(const double& length, std::string expectedTabName, std::string expectedSubTabName)
			: ExpectedLength(length),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName)
		{ }

		bool operator()(itk::EventObject const &event)
		{
			auto ev = dynamic_cast<misVirtualTipAutomaticLengthEventCore const*>(&event);
			if (!ev)
				return false;

			auto received = ev->Get();

			return ChainBool().Add(ExpectedLength == received).
				Add(ExpectedTabName == ev->GetTabName()).
				Add(ExpectedSubTabName == ev->GetSubTabName());
		}

	private:
		const double ExpectedLength;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}
