#pragma once

#include "IDatasetManager.h"
#include "IPlanCoordSysConverter.h"
#include "IPlanTransformCalculator.h"
#include "ITransformFactory.h"

namespace parcast
{

	class PlanCoordSysConverter : public IPlanCoordSysConverter
	{
	public:
		PlanCoordSysConverter(
			IDatasetManager* datasetManager, std::shared_ptr<const IPlanTransformCalculator> planTransformCalculator,
			std::shared_ptr<ITransformFactory> transformFactory);

		void Convert() override;

	private:
		IDatasetManager* m_DatasetManager;
		std::shared_ptr<const IPlanTransformCalculator> m_PlanTransCalculator;
		std::shared_ptr<ITransformFactory> m_TransformFactory;
	};

}
