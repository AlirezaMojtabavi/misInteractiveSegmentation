#pragma  once

#include "I2DRepresentation.h"
#include "IImage.h"
#include "misImagePlaneInformationStrct.h"
#include "misPanoramicMapper.h"
#include "misPlaneContrast.h"
#include "misRepresentation.h"

// The misPanoramicRepresentation class wrap actors and mapper of panoramic viewing
class misPanoramicRepresentation : public I2DRepresetation
{
public:
	typedef itk::Point<double, 3> PointType;
	//igstkStandardClassBasicTraitsMacro(misPanoramicRepresentation, misRepresentation);
	//igstkNewMacro(Self);

	misPanoramicRepresentation(std::shared_ptr<IRepresentation> mainRep);
	void SetWindowLevel(misWindowLevelStr windowLevel) override;

	// Get window Level of the displayed image
	misWindowLevelStr GetWindowLevel();

	// direction height)
	void SetCurveLength(double val);

	// Set the slice offset for extracting a panoramic view
	void SetSlice(double slice);

	// Set points created from spline 
	void SetPanoramicCurve(const std::vector<itk::Point<double, 3>>& points);

	// Set/Get 3D image 
	void SetImage(std::shared_ptr<IImage> image);
	std::shared_ptr<IImage> GetImage();
	void SetVisibilityOfMainTexture(misPlaneEnum planeIndex, bool val) override;
	bool GetVisibilityOfMainTexture(misPlaneEnum planeIndex) const override;
	void SetDefautltVisibiltyPlanesMap(std::shared_ptr<IVisibiltyHolder>) override;

protected:
	std::vector<misImagePlaneInformationStrct> m_planeInformation;

private:
	// This function initializes the window level values, Color of the image and it's transparency according to the other 
	// representations.
	void InitializeInformation();


public:
	void ApplyDefaultVisibilityMap(const std::map<misPlaneEnum, bool>& imageVisibiltes) override;
	misUID GetImageUID(misPlaneEnum planeIndex) override;
	void ApplyTransformToScene(misPlaneEnum sourcePlane, misPlaneEnum targetPlane,
		vtkSmartPointer<vtkTransform> transform) override;
	std::shared_ptr<IImage> GetImage(misPlaneEnum planeIndex) override;
	void RemovePlane(int planeindex) override;
	void SetImageSource(std::shared_ptr<IImage> pImage, misPlaneEnum planeIndex, misLayerEnum layerIndex) override;
	void SetTextureID(misPlaneEnum planeIndex, misLayerEnum layerIndex, int val) override;
	void SetMinOpacityForSettingWinLev(double threshold) override;
	void SetTexture(misOpenglTexture* pTexture) override;
	void SetTexture(misOpenglTexture* pTexture, misPlaneEnum planeIndex) override;
	void SetTexture(misLayerEnum layerIndex, misOpenglTexture* pTexture) override;
	void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture) override;
	void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture,
		misTexturePropertyStruct externalSetPlane) override;
	misWindowLevelStr GetViewingProprties() override;
	misWindowLevelStr GetViewingProprties(misPlaneEnum planeIndex) override;
	IMAGEORIENTATION GetOrientation() override;
	void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) override;
	void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) override;
	void SetColorValueToTexture(misDoubleColorStruct colorVal) override;
	void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) override;
	void SetOpacityValueToTexture(float opacityValue) override;
	void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) override;
	void SetPolyDataTransferFunction(int planeIndex, ImageContainedTransferFuncs ImgCntTF) override;
	void SetVisibilityOfSegmentedImage(misPlaneEnum planeIndex, bool val) override;
	void SetVisibilityOfFmriImage(misPlaneEnum planeIndex, bool val) override;
	void SetApplyColor(int val) override;
	void SetApplyColor(misPlaneEnum planeIndex, int val) override;
	void RemoveColorMap(misPlaneEnum planeIndex) override;
	bool UpdateRepTransformMatrix(misPlaneEnum planeIndex, vtkMatrix4x4* TransformMatrix) override;
	void SetTransferFunction(std::shared_ptr<TransFuncIntensity> tf) override;
	void SetTransferFunction(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf) override;
	void SetFmriTransferFunctionID(int val) override;
	void SetFmriTransferFunctionID(misPlaneEnum planeIndex, int val) override;
	void Reset() override;
	void RemoveLayer(misPlaneEnum planeIndex, misLayerEnum layerIndex) override;
	void InitilizeLayers() override;
	void SetIsAlphaSetForBlending(int val) override;
	void SetIsAlphaSetForBlending(misPlaneEnum planeIndex, int val) override;
	void SetErasedObjDisplayStatus(bool showErased) override;
	misPlaneEnum GetPlaneWithMaximumVisibility() override;
	void SetErasedObjectColor(misColorStruct ColorStr) override;
	void SetWindowLevelTransferFunction(misPlaneEnum planeIndex) override;
	void SetWindowLevelTransferFunction() override;
	float GetOpacityValueOfTexture(misPlaneEnum planeIndex) override;
private:
	misImagePlaneInformationStrct m_Information;
	misOpenglTexture* m_ImageTexture;
	misWindowLevelStr m_WinLevel;
	vtkSmartPointer<misPanoramicMapper> m_PanoramicMapper;
	vtkSmartPointer<vtkActor> m_Actor;
	std::shared_ptr<IImage> m_Image;
	const double m_PanoramicSliceResolution, m_PanoramicSliceRange, m_PanoramicCurveResolution;
	const double m_Precision;
	std::shared_ptr<IRepresentation> m_MainRepresentation;
};