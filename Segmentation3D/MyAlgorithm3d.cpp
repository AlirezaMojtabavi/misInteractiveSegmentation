#include "stdafx.h"
#include "MyAlgorithm3d.h"


MyAlgorithm3d::MyAlgorithm3d(std::vector<misPixelType> intensity, std::vector<coordinate3D> seeds)
	:m_intensity(intensity), m_Seeds(seeds)
{
}

void MyAlgorithm3d::SetInternalImage(misInternalImageType::Pointer _InternalImage)
{
	IS_InternalImage = _InternalImage;
}

 
misInternalImageType * MyAlgorithm3d::GetFastMarching()
{
	return fastMarching->GetOutput();
}

misOutputImageType * MyAlgorithm3d::GetThresholder()
{
	return thresholder->GetOutput();
}

void MyAlgorithm3d::FastMarching(const double distance)
{
	int size = m_Seeds.size();

	std::vector<misInternalImageType::IndexType>  seedPosition(size);
	std::vector<NodeType> node(size);

	const double initialDistance = distance;
	const double seedValue = -initialDistance;

	seeds->Initialize();

	for (int i = 0; i < size; i++)
	{
		seedPosition[i][0] = m_Seeds[i]._x;
		seedPosition[i][1] = m_Seeds[i]._y;
		seedPosition[i][2] = m_Seeds[i]._z;

		node[i].SetValue(seedValue);
		node[i].SetIndex(seedPosition[i]);

		seeds->InsertElement(i, node[i]);
	}

	cout << "\n\n";

	fastMarching->SetTrialPoints(seeds);
	fastMarching->SetSpeedConstant(1.0);

	IS_InternalImage->Update();

	fastMarching->SetOutputRegion(IS_InternalImage->GetBufferedRegion());
	fastMarching->SetOutputSpacing(IS_InternalImage->GetSpacing());
	fastMarching->SetOutputOrigin(IS_InternalImage->GetOrigin());
	fastMarching->SetOutputDirection(IS_InternalImage->GetDirection());
}

void MyAlgorithm3d::LevelSet(short int	 lower, short int	 upper, double edge, double weight)
{
	thresholder->SetLowerThreshold(-1000);
	thresholder->SetUpperThreshold(0);

	thresholder->SetOutsideValue(0.0);
	thresholder->SetInsideValue(1550);

	SegmentationSpeedFunction->SetLowerThreshold(lower);
	SegmentationSpeedFunction->SetUpperThreshold(upper);
	SegmentationSpeedFunction->SetEdgeWeight(edge);
	SegmentationSpeedFunction->SetFeatureImage(IS_InternalImage);

	double curvature = (lower + upper) / 2;
	thresholdSegmentation->SetSegmentationFunction(SegmentationSpeedFunction);
	thresholdSegmentation->SetPropagationScaling(1.0);

	thresholdSegmentation->SetCurvatureScaling(weight * curvature);

	thresholdSegmentation->SetMaximumRMSError(0.01);
	thresholdSegmentation->SetNumberOfIterations(300);
	thresholdSegmentation->SetIsoSurfaceValue(0.0);

	thresholdSegmentation->SetInput(fastMarching->GetOutput());
	thresholdSegmentation->SetFeatureImage(IS_InternalImage);

	thresholder->SetInput(thresholdSegmentation->GetOutput());

	//thresholder->Update();
}

void MyAlgorithm3d::LevelSet(double edge, double weight)
{
	/*auto window = IS_MyCanvas3D->GetMinMaxIntensity();
	double lower = window[0];
	double upper = window[1];

	cout << "lower : " << lower << "\t\t" << "upper : " << upper << endl;

	thresholder->SetLowerThreshold(-1000);
	thresholder->SetUpperThreshold(0);

	thresholder->SetOutsideValue(0.0);
	thresholder->SetInsideValue(255.0);

	SegmentationSpeedFunction->SetLowerThreshold(lower);
	SegmentationSpeedFunction->SetUpperThreshold(upper);
	SegmentationSpeedFunction->SetEdgeWeight(edge);
	SegmentationSpeedFunction->SetFeatureImage(IS_InternalImage);

	double curvature = (lower + upper) / 2;
	thresholdSegmentation->SetSegmentationFunction(SegmentationSpeedFunction);
	thresholdSegmentation->SetPropagationScaling(1.0);

	thresholdSegmentation->SetCurvatureScaling(weight * curvature);

	thresholdSegmentation->SetMaximumRMSError(0.01);
	thresholdSegmentation->SetNumberOfIterations(300);
	thresholdSegmentation->SetIsoSurfaceValue(0.0);

	thresholdSegmentation->SetInput(fastMarching->GetOutput());
	thresholdSegmentation->SetFeatureImage(IS_InternalImage);
	thresholder->SetInput(thresholdSegmentation->GetOutput());*/
	//thresholder->Update();
}

double* MyAlgorithm3d::GetROI()
{
	int size = m_Seeds.size();

	double tempMinX = m_Seeds[0]._x;
	double tempmaxX = m_Seeds[0]._x;
	double tempMinY = m_Seeds[0]._y;
	double tempmaxY = m_Seeds[0]._y;
	double tempMinZ = m_Seeds[0]._z;
	double tempmaxZ = m_Seeds[0]._z;

	for (int i = 0; i < size; i++)
	{
//-----------------X------------------------
		if (m_Seeds[i]._x <= tempMinX) // min
			tempMinX = m_Seeds[i]._x;
		else
			tempMinX = tempMinX;

		if (m_Seeds[i]._x >= tempmaxX) // max
			tempmaxX = m_Seeds[i]._x;
		else
			tempmaxX = tempmaxX;
//-----------------Y------------------------
		if (m_Seeds[i]._y <= tempMinY) // min
			tempMinY = m_Seeds[i]._y;
		else
			tempMinY = tempMinY;
		
		if (m_Seeds[i]._y >= tempmaxY) // max
			tempmaxY = m_Seeds[i]._y;
		else
			tempmaxY = tempmaxY;
//-------------------Z-----------------------
		if (m_Seeds[i]._z <= tempMinZ) // min	
			tempMinZ = m_Seeds[i]._z; 
		else
			tempMinZ = tempMinZ;	

		if (m_Seeds[i]._z >= tempmaxZ) // max
			tempmaxZ = m_Seeds[i]._z;
		else
			tempmaxZ = tempmaxZ;
	}

	ROI[0] = tempMinX;
	ROI[1] = tempmaxX;
	ROI[2] = tempMinY;
	ROI[3] = tempmaxY;
	ROI[4] = tempMinZ;
	ROI[5] = tempmaxZ;

	cout << ROI[0]<<","<< ROI[1]<<","<< ROI[2]<<","<< ROI[3]<<","<< ROI[4]<<","<< ROI[5] <<"\n\n" ;

	return ROI;
}
