#pragma once

namespace parcast
{
	class ITransformFactory;
	class IVectorRotator;

	class PlanTransformUpdater
	{
	public:
		PlanTransformUpdater(
			std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationMnager,
			std::shared_ptr<ITransformFactory> transformFactory,
			std::shared_ptr<IVectorRotator> vectorRotator);

		void Rotate(const std::string& planUId, const std::string& parentImageUid, double angle);
		void RotateToLastAccumulatedAngle(const std::string& planUId, const std::string& parentImageUid);

	private:
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
		std::shared_ptr<ITransformFactory> m_TransformFactory;
		std::shared_ptr<IVectorRotator> m_VectorRotator;
		double m_AccumulatedAngle = 0.0;
		 
		void Rotate(const std::string& planUId, const std::string& parentImageUid, double angle, bool absolute);

	};

}
