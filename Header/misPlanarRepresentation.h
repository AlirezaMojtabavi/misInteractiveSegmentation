#pragma once

#include "I2DRepresentation.h"
#include "misRepresentation.h"
#include "VisualizationGeneralTypes.h"
#include "BusinessEntities\Point.h"
#include "misTexturePropertyStruct.h"

#define LayerCount 4

class ITransform;
class misImageGeoProperties;
class misImagePlaneInformationStrct;
class misInteractorSTyleImageExtend;
class misOpenglTexture;
class IImageSlicerMapper;
class IImage;
class ICornerProperties;

struct misDoubleColorStruct;
struct misTexturePlanePoint;

typedef itk::Point<double, 3> PointType;

struct PlaneProperties
{
	double m_PlaneWidth;
	double m_PlaneHeight;
};

class misPlanarRepresentation : public misRepresentation, public I2DRepresetation
{
public:
	misPlanarRepresentation(std::string name, IImageSlicerMapper*);
	~misPlanarRepresentation();
	misImageGeoProperties *				  m_ImageGeoProp;
	void UpdateCorrelated();
	void SetTexture(misOpenglTexture* pTexture) final;
	void SetTexture(misOpenglTexture* pTexture, misPlaneEnum planeIndex)final;
	void SetTexture(misLayerEnum layerIndex, misOpenglTexture* pTexture)final;
	void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture)final;
	void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture, misTexturePropertyStruct externalSetPlane)final;
	void SetTextureTransform(tgt::mat4  pTrans);
	void SetTextureTransform(misPlaneEnum planeIndex, tgt::mat4 pTrans);
	void SetWindowLevel(misWindowLevelStr winlevStr) override;
	void SetWindowLevel(misWindowLevelStr winlevStr, misPlaneEnum palenIndex);
	void SetWindowLevel(misLayerEnum layerIndex, misWindowLevelStr winlevStr);
	void SetWindowLevel(misPlaneEnum planeIndex, misLayerEnum layerIndex, misWindowLevelStr winlevStr);
	void SetWindowLevelForSelectedPlane(misWindowLevelStr winlevStr);
	void SetImageStyle(misInteractorSTyleImageExtend* val);
	void GrayscaleOff();
	void GrayscaleOff(int index);
	void GrayscaleOff(misPlaneEnum planeIndex, misLayerEnum layerIndex);
	void GrayscaleOn();
	void GrayscaleOn(int index);
	void GrayscaleOn(misPlaneEnum planeIndex, misLayerEnum layerIndex);
	IMAGEORIENTATION  GetOrientation() final;
	void SetOrientation(IMAGEORIENTATION newOrientation);
	parcast::PointD3 	GetCenter();
	parcast::PointD3 	GetCenter(int planeIndex);
 	vtkActor* GetQuadPlane();
	vtkSmartPointer<vtkTransform> CalculateTransformBetWeenImagePlane(misPlaneEnum sourcePlane, misPlaneEnum targetPlane);
	float GetOpacityValueOfTexture(misPlaneEnum planeIndex) final;
	void SetImageSource(std::shared_ptr<IImage> pImage, misPlaneEnum planeIndex, misLayerEnum layerIndex) final;
	misTexturePropertyStruct GetImageProperties(misPlaneEnum planeIndex, misLayerEnum layerIndex);
	std::shared_ptr<IImage> GetImage(misPlaneEnum planeIndex) final;
	std::shared_ptr<IImage> GetImage() final;

	misUID GetImageUID(misPlaneEnum planeIndex) final;
	void Reset() final;
	void RemoveLayer(misPlaneEnum planeIndex, misLayerEnum layerIndex) final;
	void RemovePlane(int planeindex) final;
	void InitilizeLayers() final;
	void SetIsAlphaSetForBlending(int val) final;
	void SetIsAlphaSetForBlending(misPlaneEnum planeIndex, int val) final;
	void SetTransferFunction(std::shared_ptr<TransFuncIntensity> tf) final;
	void SetTransferFunction(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf) final;
	void SetFmriTransferFunctionID(int val) final;
	void SetFmriTransferFunctionID(misPlaneEnum planeIndex, int val) final;
	void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val)final;
	void SetVisibilityOfSegmentedImage(misPlaneEnum planeIndex, bool val) final;
	void SetVisibilityOfFmriImage(misPlaneEnum planeIndex, bool val) final;
	void SetApplyColor(int val) final;
	void SetApplyColor(misPlaneEnum planeIndex, int val) final;
	void SetProgram(GLuint program);
	void SetColorValueToTexture(misDoubleColorStruct colorVal) final;
	void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) final;
	void SetOpacityValueToTexture(float opacityValue) final;
	void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) final;
	void RemoveColorMap(misPlaneEnum planeIndex) final;
	bool UpdateRepTransformMatrix(misPlaneEnum planeIndex, vtkMatrix4x4* TransformMatrix) final;
	void ApplyTransformToScene(misPlaneEnum sourcePlane, misPlaneEnum targetPlane, vtkSmartPointer<vtkTransform> transform) final;
	misWindowLevelStr GetViewingProprties() final;
	misWindowLevelStr GetViewingProprties(misPlaneEnum planeIndex) final;
	void SetViewingProperties(misPlaneEnum planeIndex, misWindowLevelStr winlevStr);
	void SetMinOpacityForSettingWinLev(double threshold);
	void SetErasedObjDisplayStatus(bool showErased) final;
	misPlaneEnum GetPlaneWithMaximumVisibility() final;
	void SetErasedObjectColor(misColorStruct ColorStr) final;
	void SetWindowLevelTransferFunction(misPlaneEnum	planeIndex) final;
	void SetWindowLevelTransferFunction()final;
	void SetTextureID(misPlaneEnum planeIndex, misLayerEnum layerIndex, int val) final;
	void SetVisibilityOfMainTexture(misPlaneEnum planeIndex, bool val) override;
	bool GetVisibilityOfMainTexture(misPlaneEnum planeIndex) const override;
	void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) final;
	void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp);
	void SetPolyDataTransferFunction(int planeIndex, ImageContainedTransferFuncs ImgCntTF) final;
	void ClearColorMapIDs(int groupIndex);
	void ClearFmriTransferFunctionIDs(int groupIndex);

	// Set coordinate system reference UID
	void SetRefrenecCoordinateSystemUID(const misUID& uid);
	std::vector<misImagePlaneInformationStrct> GetPlaneInformation();
	void ApplyDefaultVisibilityMap(const std::map<misPlaneEnum, bool>& imageVisibiltes) final;
	void SetDefautltVisibiltyPlanesMap(std::shared_ptr<IVisibiltyHolder> planes) override;
	std::shared_ptr<IVisibiltyHolder> GetVisibiltyHolder();
protected:
	std::vector<misImagePlaneInformationStrct> m_planeInformation;
	std::shared_ptr<ICornerProperties> m_CornerProperties;
	IMAGEORIENTATION m_Orientation;

private:

	std::shared_ptr<ITransform> GetImageNormalizationTransform(misPlaneEnum plane);
	void GeneratePlaneMesh(misTexturePropertyStruct  prop);
	void GeneratePlaneMesh(misPlaneEnum planeIndex, misTexturePropertyStruct  prop);
	void SetRepresentationType();
	void SetCornerProperties();
	// Since the texture on the card is managed by m_TransferFunction, it must be kept alive during the life time of the rep.
	std::shared_ptr<TransFuncIntensity> m_TransferFunction[2];
	int	m_TransferfuncID;
	double m_MinOpacityForSettingWinLev;
	misOpenglTexture* m_RefrencePlaneTexture;
	misUID m_ReferenceUID;// see SetRefrenecCoordinateSystemUID
	std::shared_ptr<IVisibiltyHolder> m_VisibiltyHolder;
	IImageSlicerMapper* m_SliceMapper;
	bool m_ContrastChanged;
};
