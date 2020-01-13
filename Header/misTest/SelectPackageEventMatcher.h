#pragma once
#include "ChainBool.h"

namespace parcast
{

	class SelectPackageEventMatcher
	{
	public:
		SelectPackageEventMatcher(std::string expectedPackageUid, std::string expectedTabName, std::string expectedSubTabName)
			: ExpectedPackageUid(expectedPackageUid),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName) 
		{ }

		bool operator()(itk::EventObject const &event)
		{
			auto selPkgEv = dynamic_cast<misSelectedPackageEventCore const*>(&event);
			if (selPkgEv == nullptr)
				return false;

			return parcast::ChainBool().
				Add(ExpectedPackageUid == selPkgEv->Get()).
				Add(ExpectedTabName == selPkgEv->GetTabName()).
				Add(ExpectedSubTabName == selPkgEv->GetSubTabName());
		}

	private:
		const std::string ExpectedPackageUid;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}