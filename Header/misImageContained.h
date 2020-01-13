#pragma once
 

#include "mis3DModelViewingProperties.h"
#include "misColorImage.h"
#include "misColorTable.h"
#include "misImage.h"
#include "misImageByteAnalysis.h"
#include "misImageContainedPolyDataStructs.h"
#include "misObject.h"
#include "misPolyData.h"
#include "misPolyDatasSpecifications.h"
#include "misResultCode.h"
#include "misSeconderyNeededHeader.h"
#include "IImageContained.h"

enum PolyDataColorSortOrder
{
	AscendingVolume,
	DescendingVolume,
	NoOrder
};

enum RenderingObjectType
{
	Segmented2D,
	Segmented3D
};

typedef  std::vector<misUID>                       SelectedPolyDatasTypedef;
typedef  std::vector<int>                          IDsTypdef;

class   misImageContained :	 public IImageContained
{
 

public:
	virtual std::string GetUID() const override ;
	virtual void SetUID(const std::string& id) override ; 

	misCreateVariableWithProtectedSetGetMacro(ModificationFlag,bool);
	misCreateVariableWithProtectedSetGetMacro(ModificationFlagBinariesPart,bool);
	misCreateVariableWithSetGetMacroWithModificationFlag(Name,std::string);
	misCreateVariableWithSetGetMacroWithModificationFlag(PolyDataSortOrder,PolyDataColorSortOrder);
	misCreateVariableWithSetGetMacroWithModificationFlag(ApplyObjectTransparency,bool);
	misCreateVariableWithSetGetMacroWithModificationFlag(ObjectTransparency,double);
	void ShowMargin(bool status);
	misPrivateBooleanVariableWithPublicAccessorsMacro(m_UseDepositColorForBorders, UseDepositColorForBorders);
	std::shared_ptr<misImageByteAnalysis>      GetSegmentedImage() const;
	misColorTable* GetColorMap2D();
	misColorTable* GetColorMap3D();
	misPolyDatesColormapTypedef  GetPolyDatasColorMap(void);
	misUID m_PackageUID;	
	void SetImage(std::shared_ptr<misImageByteAnalysis>  val);
	//  description:            avoid using this function, use with care !!!!
	misResultCode::ResultIds    ReplaceTempPolyDayaUID( misUID tempPolyDataUID, misUID realPolyDataUID );
	void ReleaseResource(void); 
	void ResetSetting(void);
	int GetNumberofObjects(void);
	misResultCode::ResultIds DeleteAllObjects(void);
	misResultCode::ResultIds AddNewObject(vtkImageData* pNewImage, misPolyData*  pPolyData);
	misResultCode::ResultIds AddNewObject(vtkImageData* pNewImage, misUID ParrentImageUID,misUID polydataUID, misColorStruct ploydataColor);
	misResultCode::ResultIds AddToExistedObject(misUID polydataUID, vtkImageData* pNewImage, misUID ParrentImageUID);
	misResultCode::ResultIds AddToExistedObject(misUID newPolydataUID, misUID oldPolydataUID, vtkImageData* pNewImage, misUID ParrentImageUID);
	misResultCode::ResultIds ReplaceWithExistedObject(misUID polydataUID, vtkImageData* pNewImage, misUID ParrentImageUID);
	misResultCode::ResultIds ReplaceWithExistedObject(misUID newPolydataUID, misUID oldPolydataUID, vtkImageData* pNewImage, misUID ParrentImageUID);
	misResultCode::ResultIds DeleteObject(misUID  polyDataUID);
	misResultCode::ResultIds DeleteObjectForced( misUID polyDataUID );
	misResultCode::ResultIds SetObjectColor(misUID  polyDataUID,misColorStruct polyDataColor);
	misResultCode::ResultIds SetObjectName(misUID polydataUID , std::string polydataName);
	int	SetViewableObjectAll (void);
	int	 SetViewableObjectNone(void);
	int	 SetViewableObjectUIDsOnly(SelectedPolyDatasTypedef viewableObjects);
	int	 SetViewableObjectByMap(misObjectVisibilityMap visiblityMap);
	void	ChangeObjectOpacity(misUID segmentedObject , double opacity);
	vtkImageData*            GetImageOfSpecificPolyData(misUID polydataUID);
	ImagePolyDataContenStrct GetOLDPolyDataProperties(misUID polydataUID);	
	misPolyDataPropInImageContainted GetNEWPolyDataProperties(misUID polydataUID);
	PropertiesOfPixelInImageType     GetPixelData(const double* pixelPosition);
	PolyDatasPropertyByImageTypdef		GetPolydataPropertyStruct(){return GetPolyDataProperties();}
	// temp public:
	misImageContained(void);
	bool IsSpecificImageExisted(misUID objectUID);
	bool IsSegmentedImageExisted();
	void SetOpacityScale(double opacityScale);
	void AddObjectExtent(misUID objectUID , int* objectExtent);
	void CopyAllSegmentedObjectToNewStructure();
	void SetAlarmMargin(misUID objectUID , bool val);
	bool GetAlarmMargin(misUID objectUID);
	void ShowMarginRegion( misUID objectUID , bool val );
	bool GetShowMarginRegion(misUID objectUID);
	void SetMarginValue(misUID objectUID , double marginVal);
	double GetMarginValue(misUID objectUID);
	bool   m_AddBorder;
	std::string GetParentImageUID() const;
	void SetParentImageUID(std::string val);
	PolyDatasPropertyByImageTypdef GetPolyDataProperties() const;
	void SetPolyDataProperties(const PolyDatasPropertyByImageTypdef& val);
 
private:
	misResultCode::ResultIds  InitializeImage(vtkImageData* pNewImage, misUID   parrentImageUID);
	misResultCode::ResultIds  UpdateFreeIndexes(void);
	void UpdateMaxAllocatedIndex(void);
	inline misResultCode::ResultIds  UpdateViewableObjects(void);
	inline misResultCode::ResultIds  UpdateOutputColorMap2D(void);
	inline misResultCode::ResultIds  UpdateOutputColorMap3D(void);
	bool FindDuplicatedPolyData(misUID  polyDataUID);	
	// It must check size and UID
	misResultCode::ResultIds CheckNewObjectValidity(vtkImageData* pNewImage,misUID   parrentImageUID);
	void CallModificationObserver(void);;
	void BuildColorMap( IDsTypdef &localOrderVisiblity, misColorTable* localColorMap,  RenderingObjectType renderingType );
	void Sort2Dand3DIndex();
	void SortAscendingOrDescendingIndex( IDsTypdef &localOrderedIndex, misPresentationDimension presentationDim );
	int GetNumberOfViewableObject();
	misPolyDatasSpecifications* m_polyDatsSpecifications;
	PolyDatasPropertyByImageTypdef m_PolyDataProperties;
	 int m_MaxObjectNumber;
	 int m_MaxAllocatedIndex;
	 bool m_InputImageHasbeenInitialized;
	 std::shared_ptr<misImageByteAnalysis>  m_Image;
	 misColorTable* m_ViewableObjectColorTable2D;
	 misColorTable*	m_ViewableObjectColorTable3D;
	 bool m_OutputColormapIsUpdated;
	 IDsTypdef m_FreeIndexes;
	 IDsTypdef m_OrderdVisibleIndexes2D;
	 IDsTypdef m_OrderdVisibleIndexes3D;
	 bool  m_ViewAbleObjectsAreUpdated;
	 bool  m_ShowMargin;
	 double m_OpacityScale;  
	 std::string m_DataObjectUID;
	 std::string m_ParentImageUID;
};

typedef  std::vector< std::shared_ptr<IImageContained>>			  ImageContainedPolyDataListTypedef;

