#pragma once
#include <vector>
#include <string>

#include "DICOMConfig.h"
#include "DICOMTypes.h"
#include "DICOMCallback.h"

#ifdef _MSC_VER
#pragma warning ( default: 4018 )
#endif

class DICOMParser;

// Function object for sorting strings
struct ltstdstr
{
	bool operator()(const dicom_stl::string &s1, const dicom_stl::string &s2) const
	{
		return s1 < s2;
	}
};

// Helper structure for DICOM elements
struct DICOMTagInfo
{
	doublebyte group;
	doublebyte element;
	DICOMParser::VRTypes datatype;
	const char* description;
};


// Helper class use for ordering DICOM images based on different
// (group, element) tags.
class DICOM_EXPORT DICOMOrderingElements
{
public:
	DICOMOrderingElements()
	{
		// Default values to something "valid"
		SliceNumber = -1;
		SliceLocation = 0.0;
		ImagePositionPatient[0] = 0.0;
		ImagePositionPatient[1] = 0.0;
		ImagePositionPatient[2] = 0.0;
		ImageOrientationPatient[0] = 1.0;
		ImageOrientationPatient[1] = 0.0;
		ImageOrientationPatient[2] = 0.0;
		ImageOrientationPatient[3] = 0.0;
		ImageOrientationPatient[4] = 1.0;
		ImageOrientationPatient[5] = 0.0;
	}

	int SliceNumber;
	float SliceLocation;
	float ImagePositionPatient[3];
	float ImageOrientationPatient[6];
};

class DICOMAppHelperImplementation;