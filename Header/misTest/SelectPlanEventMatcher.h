#pragma once

namespace parcast
{

	class SelectPlanEventMatcher
	{
	public:
		SelectPlanEventMatcher(
			std::string expectedPlanUid, std::string expectedTabName, std::string expectedSubTabName)
			: ExpectedPlanUid(expectedPlanUid),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName)
		{
		}

		bool operator()(itk::EventObject const &event)
		{
			auto selPlanEv = dynamic_cast<misSelectedPlanEventCore const*>(&event);
			if (selPlanEv == nullptr)
				return false;

			return parcast::ChainBool().
				Add(ExpectedPlanUid == selPlanEv->Get()).
				Add(ExpectedTabName == selPlanEv->GetTabName()).
				Add(ExpectedSubTabName == selPlanEv->GetSubTabName());
		}

	private:

		const std::string ExpectedPlanUid;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}
