#pragma once

#include "misEnums.h"
#include "misImageContainedDataType.h"
#include "misImage.h"

struct objectProperties 
{
	long int volume;
	int  marginPixelNo;
	//int  objectExtent[6];

	objectProperties(void)
	{
	   volume = -1;
	   marginPixelNo = 0;
	//   objectExtent[0] = -1;
	   //objectExtent[1] = -1;
	   //objectExtent[2] = -1;
	   //objectExtent[3] = -1;
	   //objectExtent[4] = -1;
	   //objectExtent[5] = -1;
	};
};

typedef std::map<int, objectProperties>    misObjectByteTypedef;
typedef std::vector<int> misAllocatedByteNumbersTypdef;

class  misImageByteAnalysis : public misImage
{

public:
	
	misImageByteAnalysis(void);
	~misImageByteAnalysis(void);

	misResultCode::ResultIds InitializeFromImage(vtkImageData* pImage);
	void SetVolume(int val) { m_Volume = val; }
	void SetData(ImageContainedDataType* val) { m_pData = val; }
	misResultCode::ResultIds  SetAllValuesTo(int Value);
	misResultCode::ResultIds  AddToExistedObject(int index, vtkImageData* pImage);
	misResultCode::ResultIds CheckImageCriteria( vtkImageData* pImage ) ;
	char* GetRawImageSegmentedPointer( vtkImageData* pImage ) const;
	misResultCode::ResultIds  ReplaceObject(int index, vtkImageData* pImage);
	misResultCode::ResultIds  ClearObject(int index);
	void ClearAll(void);
	long int   GetVolume(int index);
	vtkImageData*   GetImageByIndex(int index);
	misRGObjectType  GetObjectType(int ObjectIndex, const int positionInImage[3] ) const;
	virtual void Update() final;
private:
	
	void clearObjectVolume(int index);	
	void CheckObjectExtendValidity(int* objectDimention);
	long int UpdateObjectVolume(int index);
	misResultCode::ResultIds AddToObjectInternal (int index,char* segmentedImage);
	misResultCode::ResultIds ReplaceObjectInternal (int index,char* segmentedImage);
	inline misRGObjectType GetObjectType(int ObjectIndex,ImageContainedDataType imageValue ) const;
	void UpdateRawImageData();
	int		m_Volume;
	int*	m_Dims;
	double* m_Origin;
	bool    m_InitlizedImage;
	misObjectByteTypedef  m_IDVolmeMap;
	ImageContainedDataType* m_pData;
};



