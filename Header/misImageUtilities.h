#pragma once

class IImage;

enum misImageWithDifficultiesForUploadingEnum;

typedef std::vector<misImageWithDifficultiesForUploadingEnum> misImgeProblemList;

class misImageUtilities
{
	//NOTE: This class is provided to collect all static method which do something on IImage
public:

	static bool CompareImageProperties(vtkImageData* pImage1, vtkImageData* pImage2);
	static bool CheckImageRangeValidity(std::shared_ptr<IImage> pMisImage);
	static void	ConvertImageBasedOnDataType(std::shared_ptr<IImage> pMisImage);
	static misImgeProblemList CheckImageValidity(std::shared_ptr<IImage> pMisImage);
};

