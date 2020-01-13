#include <vector>
#include <string>

 
#include "DICOMParser.h"
#include "DICOMAppHelperModified.h"
#include "misDataManagerTypes.h"
#include "misStrctDicomIO.h"
 #include "misMacros.h"

struct misImagesProperties
{
	std::string	imagePath;
	tgt::vec3	imageOrientation;
	tgt::vec3	imagePosition;

	misImagesProperties() :imagePosition(0.0f),imageOrientation(0.0f),imagePath("")
	{
	}
};
typedef std::vector<misImagesProperties> misImagesPropertiesList;

class misSerieCheckValidation 
{
public:

	misSerieCheckValidation();

	imageListTypdef GetSortedList( imageListTypdef slices, unsigned minOfSliceNumber);
	tgt::vec3		GetSpacing();
	void			RequestStop();
	std::string GetPatientPosition();
	float* GetImageOrientationPatient();

private:
	bool CheckDimension(int Row,int Column);
	bool CheckNumberOfComponent(int NumberOfComponent);
	bool CheckBitDepth(int bitDepth);
	void CheckInputData(void);
	double CalcSpacing( std::vector<float> spacingLst);
	void Reset();
	misImagesPropertiesList GetImagesPropertiesList(imageListTypdef slices);
	misImagesPropertiesList	SelectSlicesBasedOnMainOrientation(misImagesPropertiesList imgPropLst);
	misImagesPropertiesList SortSlicesBasedOnMainOrientation(misImagesPropertiesList imagesPropertiesList);
	imageListTypdef			CheckSortedImagesBasedOnSpacing(misImagesPropertiesList imagesPropertiesList, unsigned minOfSliceNumber);
	std::vector<float>	GetSpacingList( misImagesPropertiesList &imagesPropertiesList );

	DICOMAppHelperModified *AppHelper;
	misSerieCheckData		DataOfFirst;
	tgt::vec3	m_Spacing;
	bool		m_CancelRequested;
	std::string m_PatientPosition;
	float* m_ImageOrientationPatient;
};