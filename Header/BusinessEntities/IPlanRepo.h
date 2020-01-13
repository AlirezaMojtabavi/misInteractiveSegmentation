#pragma once


namespace parcast
{
	class IPlan;
	class IPlanRepo
	{
	public:
		virtual ~IPlanRepo() = default;
		virtual std::weak_ptr<IPlan> Get(std::string const& uid) = 0;
		virtual void Delete(std::string const& uid) = 0;
		virtual std::weak_ptr<IPlan> CreateNewPlan(std::string  const& parentImageUid) = 0;
		virtual void Clear() = 0;
		virtual std::vector<std::weak_ptr<IPlan> > GetAllPlans() const = 0;
	};
}
