
#include "pch.h"
#include "MyAlgorithm3d.h"


MyAlgorithm3d::MyAlgorithm3d(InternalImageType::Pointer _InternalImage, SeedList list)
	:IS_InternalImage(_InternalImage), IS_SeedList(list)
{
	IS_InternalImage = _InternalImage;
}


InternalImageType * MyAlgorithm3d::Get_FastMarching()
{
	return fastMarching->GetOutput();
}

OutputImageType * MyAlgorithm3d::Get_thresholder()
{
	return thresholder->GetOutput();
}


void MyAlgorithm3d::Set_Function(itk::SmartPointer<MySpeedFunction3DType> _Function)
{
	my_function = _Function;
}

void MyAlgorithm3d::FastMarching(const double distance)
{
	int size = IS_SeedList.get_vector().size();

	std::vector<InternalImageType::IndexType>  seedPosition(size);
	std::vector<NodeType> node(size);

	const double initialDistance = distance;
	const double seedValue = -initialDistance;

	seeds->Initialize();

	for (int i = 0; i < size; i++)
	{
		seedPosition[i][0] = IS_SeedList.get_vector()[i]._x;
		seedPosition[i][1] = IS_SeedList.get_vector()[i]._y;
		seedPosition[i][2] = IS_SeedList.get_vector()[i]._z;

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

void MyAlgorithm3d::Level_Set(int lower, int upper, double edge, double weight)
{
	thresholder->SetLowerThreshold(-1000);
	thresholder->SetUpperThreshold(0);

	thresholder->SetOutsideValue(0.0);
	thresholder->SetInsideValue(255.0);

	my_function->SetLowerThreshold(lower);
	my_function->SetUpperThreshold(upper);
	my_function->SetEdgeWeight(edge);
	my_function->SetFeatureImage(IS_InternalImage);

	double curvature = (lower + upper) / 2;
	thresholdSegmentation->SetSegmentationFunction(my_function);
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

void MyAlgorithm3d::Level_Set(double edge, double weight)
{
	auto window = IS_SeedList.get_min_max();
	double lower = window[0];
	double upper = window[1];

	cout << "lower : " << lower << "\t\t" << "upper : " << upper << endl;

	thresholder->SetLowerThreshold(-1000);
	thresholder->SetUpperThreshold(0);

	thresholder->SetOutsideValue(0.0);
	thresholder->SetInsideValue(255.0);

	my_function->SetLowerThreshold(lower);
	my_function->SetUpperThreshold(upper);
	my_function->SetEdgeWeight(edge);
	my_function->SetFeatureImage(IS_InternalImage);

	double curvature = (lower + upper) / 2;
	thresholdSegmentation->SetSegmentationFunction(my_function);
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
