
 

namespace parcast
{


	class PlanTransformUpdater
	{
	public:
		misPlanTransformUpdater(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationMnager,
			std::shared_ptr<parcast::ITransformFactory> transformFactory)
			:m_CSCorrelationManager(correlationMnager),
			m_TransformFactory(transformFactory)
		{

		}
		void Update(misUID refrenceUID, misUID planUId, misUID parentImageUid, parcast::VectorD3 toolFace)
		{
			auto const correlation = m_CSCorrelationManager->GetTransform(parentImageUid, planUId);
			auto const transform = correlation->GetTransform();
			double transMat[16];
			transform->GetMarixElements(transMat);
			auto planVec = parcast::VectorD3(transMat[2], transMat[6], transMat[10]);
			auto yAxis = parcast::VectorMath::CrossProduct(planVec, toolFace);
			yAxis.Normalize();
			auto xAxis = parcast::VectorMath::CrossProduct(yAxis, planVec);
			xAxis.Normalize();
			double newTransMat[16] =
			{ xAxis[0], yAxis[0], planVec[0], transMat[3],
				xAxis[1], yAxis[1], planVec[1], transMat[7],
				xAxis[2], yAxis[2], planVec[2], transMat[11],
				0,0,0,1 };
			auto const newTransform = m_TransformFactory->Create(newTransMat);
			m_CSCorrelationManager->SetTransform(parentImageUid, planUId, newTransform);
		}
	private:
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
		std::shared_ptr<parcast::ITransformFactory> m_TransformFactory;
	};

}
