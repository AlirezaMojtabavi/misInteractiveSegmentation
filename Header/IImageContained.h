#pragma once
#include "misImageByteAnalysis.h"
#include "misColorTable.h"
#include "misImageContainedPolyDataStructs.h"
#include "misPolyDatasSpecifications.h"


class misPolyData;
 
class IImageContained: public ICoordinateSystem
{
public:
	virtual ~IImageContained() = default;
	virtual void ShowMargin(bool status) = 0;
	virtual std::shared_ptr<misImageByteAnalysis>      GetSegmentedImage() const = 0;
	virtual misColorTable* GetColorMap2D() = 0;
	virtual misColorTable* GetColorMap3D() = 0;
	virtual misPolyDatesColormapTypedef  GetPolyDatasColorMap(void) = 0;
	virtual void SetImage(std::shared_ptr<misImageByteAnalysis>  val) = 0;
	virtual misResultCode::ResultIds    ReplaceTempPolyDayaUID(misUID tempPolyDataUID, misUID realPolyDataUID) = 0;
	virtual void ReleaseResource(void) = 0;
	virtual void ResetSetting(void) = 0;
	virtual int GetNumberofObjects(void) = 0;
	virtual misResultCode::ResultIds DeleteAllObjects(void) = 0;
	virtual misResultCode::ResultIds AddNewObject(vtkImageData* pNewImage, misPolyData*  pPolyData) = 0;
	virtual misResultCode::ResultIds AddNewObject(vtkImageData* pNewImage, misUID ParrentImageUID, misUID polydataUID,
	                                              misColorStruct ploydataColor)  = 0;
	virtual misResultCode::ResultIds AddToExistedObject(misUID polydataUID, vtkImageData* pNewImage,
	                                                    misUID ParrentImageUID) = 0;
	virtual misResultCode::ResultIds AddToExistedObject(misUID newPolydataUID, misUID oldPolydataUID,
	                                                    vtkImageData* pNewImage, misUID ParrentImageUID) = 0;
	virtual misResultCode::ResultIds ReplaceWithExistedObject(misUID polydataUID, vtkImageData* pNewImage,
	                                                          misUID ParrentImageUID) = 0;
	virtual misResultCode::ResultIds ReplaceWithExistedObject(misUID newPolydataUID, misUID oldPolydataUID,
	                                                          vtkImageData* pNewImage, misUID ParrentImageUID) = 0;
	virtual misResultCode::ResultIds DeleteObject(misUID polyDataUID) = 0;
	virtual misResultCode::ResultIds DeleteObjectForced(misUID polyDataUID) = 0;
	virtual misResultCode::ResultIds SetObjectColor(misUID polyDataUID, misColorStruct polyDataColor) = 0;
	virtual misResultCode::ResultIds SetObjectName(misUID polydataUID, std::string polydataName) = 0;
	virtual int	SetViewableObjectAll(void) = 0;
	virtual int	 SetViewableObjectNone(void) = 0;
	virtual int	 SetViewableObjectUIDsOnly(SelectedPolyDatasTypedef viewableObjects) = 0;
	virtual int	 SetViewableObjectByMap(misObjectVisibilityMap visiblityMap) = 0;
	virtual void	ChangeObjectOpacity(misUID segmentedObject, double opacity) = 0;
	virtual vtkImageData*            GetImageOfSpecificPolyData(misUID polydataUID) = 0;
	virtual ImagePolyDataContenStrct GetOLDPolyDataProperties(misUID polydataUID) = 0;
	virtual misPolyDataPropInImageContainted GetNEWPolyDataProperties(misUID polydataUID) = 0;
	virtual PropertiesOfPixelInImageType     GetPixelData(const double* pixelPosition) = 0;
	virtual PolyDatasPropertyByImageTypdef		GetPolydataPropertyStruct() = 0;
	virtual bool IsSpecificImageExisted(misUID objectUID) = 0;
	virtual bool IsSegmentedImageExisted() = 0;
	virtual void SetOpacityScale(double opacityScale) = 0;
	virtual void AddObjectExtent(misUID objectUID, int* objectExtent) = 0;
	virtual void CopyAllSegmentedObjectToNewStructure() = 0;
	virtual void SetAlarmMargin(misUID objectUID, bool val) = 0;
	virtual bool GetAlarmMargin(misUID objectUID) = 0;
	virtual void ShowMarginRegion(misUID objectUID, bool val) = 0;
	virtual bool GetShowMarginRegion(misUID objectUID) = 0;
	virtual void SetMarginValue(misUID objectUID, double marginVal) = 0;
	virtual double GetMarginValue(misUID objectUID) = 0;
	virtual std::string GetParentImageUID() const = 0;
	virtual void SetParentImageUID(std::string val) = 0;
	virtual PolyDatasPropertyByImageTypdef GetPolyDataProperties() const = 0;
	virtual void SetPolyDataProperties(const PolyDatasPropertyByImageTypdef& val) = 0;
	virtual void UseDepositColorForBordersOff() = 0;
	
};
