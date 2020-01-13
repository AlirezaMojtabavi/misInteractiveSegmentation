#include "StdAfx.h"
#include "misImageUtilities.h"
#include "misApplicationSetting.h"
#include "IImage.h"
#include "misImageDataProperties.h"

void misImageUtilities::ConvertImageBasedOnDataType(std::shared_ptr<IImage> pMisImage)
{
	vtkSmartPointer<vtkImageData> rawImage = vtkSmartPointer<vtkImageData>::New();
	int  scalartype = VTK_SHORT;
	if (pMisImage->GetImageModality() == MRI)
	{
		scalartype = VTK_UNSIGNED_SHORT;
	}

	auto extent = pMisImage->GetRawImageData()->GetExtent();
	rawImage->SetExtent(extent);
	auto dims = pMisImage->GetRawImageData()->GetDimensions();
	int sourceImageSize = dims[0] * dims[1] * dims[2];
	auto spacing = pMisImage->GetRawImageData()->GetSpacing();
	rawImage->SetSpacing(spacing);
	auto Origin = pMisImage->GetRawImageData()->GetOrigin();
	rawImage->SetOrigin(Origin);
	rawImage->AllocateScalars(scalartype, 1);
	auto sourcePtr = static_cast<float*>(pMisImage->GetRawImageData()->GetScalarPointer());
	if (rawImage->GetScalarType() == VTK_UNSIGNED_SHORT)
	{
		auto destinationPtr = (unsigned short*)(rawImage->GetScalarPointer());
		for (int i = 0; i < sourceImageSize; i++)
		{
			destinationPtr[i] = sourcePtr[i];
		}
	}
	else if (rawImage->GetScalarType() == VTK_SHORT)
	{
		auto destinationPtr = (short*)(rawImage->GetScalarPointer());
		for (int i = 0; i < sourceImageSize; i++)
		{
			destinationPtr[i] = sourcePtr[i];
		}
	}
	pMisImage->SetRawImageData(rawImage);
}

bool misImageUtilities::CompareImageProperties(vtkImageData* pImage1, vtkImageData* pImage2)
{
	if ((!pImage1) || (!pImage2))
	{
		return false;
	}

	int *dimsIn1, *dimsIn2;
	double *spacingIn1, *spacingIn2;
	double *originIn1, *originIn2;
	int *extentIn1, *extentIn2;

	dimsIn1 = pImage1->GetDimensions();
	spacingIn1 = pImage1->GetSpacing();
	originIn1 = pImage1->GetOrigin();
	extentIn1 = pImage1->GetExtent();

	dimsIn2 = pImage2->GetDimensions();
	spacingIn2 = pImage2->GetSpacing();
	originIn2 = pImage2->GetOrigin();
	extentIn2 = pImage2->GetExtent();

	int res1, res2, res3, res4, res5, resFinal;

	if ((dimsIn1[0] == dimsIn2[0]) && (dimsIn1[1] == dimsIn2[1]) && (dimsIn1[2] == dimsIn2[2]))
	{
		res1 = 1;
	}
	else
	{
		res1 = 0;
	}

	if ((spacingIn1[0] == spacingIn2[0]) && (spacingIn1[1] == spacingIn2[1]) && (spacingIn1[2] == spacingIn2[2]))
	{
		res2 = 1;
	}
	else
	{
		res2 = 0;
	}

	if ((originIn1[0] == originIn2[0]) && (originIn1[1] == originIn2[1]) && (originIn1[2] == originIn2[2]))
	{
		res3 = 1;
	}
	else
	{
		res3 = 0;
	}

	if ((extentIn1[0] == extentIn2[0]) && (extentIn1[1] == extentIn2[1]) && (extentIn1[2] == extentIn2[2]))
	{
		res4 = 1;
	}
	else
	{
		res4 = 0;
	}

	if ((extentIn1[3] == extentIn2[3]) && (extentIn1[4] == extentIn2[4]) && (extentIn1[2] == extentIn2[4]))
	{
		res5 = 1;
	}
	else
	{
		res5 = 0;
	}

	resFinal = res1 * res2 *res3 *res4 *res5;
	return resFinal;
}

bool misImageUtilities::CheckImageRangeValidity(std::shared_ptr<IImage> pMisImage)
{
	bool result = false;
	auto rangeTmp = pMisImage->GetImageDataProperties()->imageProperties.Range;
	auto appSetting = misApplicationSetting::GetInstance();

	switch (pMisImage->GetImageModality())
	{
	case MRI:
		if (rangeTmp[0] >= appSetting->GetDataUploadingSetting().m_MinMRIRange &&
			rangeTmp[1] <= appSetting->GetDataUploadingSetting().m_MaxMRIRange)
		{
			result = true;
		}
		break;
	case CT:
		if (rangeTmp[0] >= appSetting->GetDataUploadingSetting().m_MinCTRange &&
			rangeTmp[1] <= appSetting->GetDataUploadingSetting().m_MaxCTRange)
		{
			result = true;
		}
		break;
	}
	return result;
}

misImgeProblemList misImageUtilities::CheckImageValidity(std::shared_ptr<IImage> pMisImage)
{
	// Note : InAcceptedImageProblem and WrongImageComponent return as a first error
	// Note : this function is not valid for misImageContained
	misImgeProblemList imageProblemList;
	if (misApplicationSetting::GetInstance()->m_WorkflowButtonSet == AnimalImaging)
	{
		imageProblemList.push_back(NoProblemInImage);
		return imageProblemList;
	}
	if (0 == pMisImage)
	{
		imageProblemList.push_back(InAcceptedImageProblem);
		return imageProblemList;
	}

	int minimumAccptedImageNumber =
		misApplicationSetting::GetInstance()->m_DataUploadingSetting.m_MinimumImageNumberIsAccptedForNavigation;
	double validSpacing = misApplicationSetting::GetInstance()->m_DataUploadingSetting.m_MaxImageSpacaingIsAccptedForNavigation;

	// TODO : scaler range difficulties must add to image difficulties
	//int scalarComponents = pMisImage->GetRawImageData()->GetNumberOfScalarComponents();	
	//if (1 != scalarComponents) /// check minimum Image Number
	//	imageProblemList.push_back(WrongImageComponent);

	int* dims = pMisImage->GetRawImageData()->GetDimensions();
	if (dims[2] < minimumAccptedImageNumber) /// check minimum Image Number
	{
		imageProblemList.push_back(wrongImageNumberForUploading);
	}

	auto spacing = pMisImage->GetRawImageData()->GetSpacing();
	if (validSpacing < spacing[2]) // check scaler component
	{
		imageProblemList.push_back(InsufficientImageSpacing);
	}

	if (imageProblemList.empty())
	{
		imageProblemList.push_back(NoProblemInImage);
	}
	return imageProblemList;
}
