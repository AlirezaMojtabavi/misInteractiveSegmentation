#pragma once

#include "CorrelationData.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemCorrelationsDataAdapter.h"

class IDatasetManager;

template <typename T>
class misTimedValidator;

namespace parcast
{

	template <typename ElemType, int Size>
	class IArrayBinaryCodec;

	class ICoordinateSystemDataAccess;
	class ICorrelationDataAccess;

	class misCoordinateSystemCorrelationsDataAdapter : public parcast::ICoordinateSystemCorrelationsDataAdapter
	{
	public:
		misCoordinateSystemCorrelationsDataAdapter(
			IDatasetManager* datasetManager,
			std::shared_ptr<parcast::ICoordinateSystemDataAccess> coordSysDataAccess,
			std::shared_ptr<parcast::ICorrelationDataAccess> correlationDataAccess,
			std::shared_ptr<parcast::IArrayBinaryCodec<double, 16>> transformCodec);

		virtual void SaveCorrelations() override;
		virtual void LoadCorrelations() override;

	private:
		using CorrelationType = ICoordinateSystemCorrelationManager<std::string>::DirectCorrelation;
		using TimedTransform = const misTimedValidator<ICoordinateSystemCorrelationManager<std::string>::TransformConstPtr>;

		parcast::CorrelationData CreateCorrelationData(const CorrelationType& correlation, const std::string& solutionUid) const;
		CorrelationType CreateCorrelation(const parcast::CorrelationData& correlationData) const;

		IDatasetManager* m_DatasetManager;
		std::shared_ptr<parcast::ICoordinateSystemDataAccess> m_CoordSysDataAccess;
		std::shared_ptr<parcast::ICorrelationDataAccess> m_CorrelationDataAccess;
		std::shared_ptr<parcast::IArrayBinaryCodec<double, 16>>  m_ArrayBinaryCodec;
	};

}