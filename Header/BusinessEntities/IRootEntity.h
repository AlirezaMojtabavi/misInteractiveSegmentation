#pragma once


namespace parcast
{

	class ITreatmentSolution;

	class IRootEntity
	{
	public:

		virtual ~IRootEntity() = default;
		virtual std::shared_ptr<ITreatmentSolution> GetCurrentSolution() const = 0;

	};

}