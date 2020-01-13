#include "misGpuAxialMultiplaneRepresentation.h"
#include "vtkTransform.h"
#pragma once
#pragma message("misMultiPlaneRep was include ")


class misMultiPlaneRep: public misObject
{

public:

	misMultiPlaneRep();
	virtual ~misMultiPlaneRep();

	igstkStandardClassBasicTraitsMacro(misMultiPlaneRep,misObject);
	static Pointer New(); 
	
	void SetSliceNumber(int sliceNumber);
	void SetCurrentImagePos( double currentImagePosition);
	void SetFixedImage(vtkImageData *fixedImageData);
	void SetMovingImage(vtkImageData *movingImageData);

	void SetFixedTexture(misOpenglTexture *fixedTexture, misPlanePoint fixedPlanePoint, misImageDataModality fixedModality);
	void SetMovingTexture(misOpenglTexture *movingTexture, misPlanePoint movingPlanePoint, misImageDataModality movingModality);

	void SetTransform(vtkTransform *transform);
	
	misGpuAxialMultiplaneRepresentation::Pointer GetFixedPlane();
	misGpuAxialMultiplaneRepresentation::Pointer GetMovingPlane();

	void Update();

	void SetImagePropertiesToFixedPlane(misImageGeoProperties newFixedImageProp);
	void SetImagePropertiesToMovingPlane(misImageGeoProperties newMovingImageProp);

	void GenerateFixedPlaneMesh(misPlanePoint PlanePoint);
	void GenerateMovingPlaneMesh(misPlanePoint PlanePoint);


	void SetFixedSliceNumber(int FixedSliceNumber);
	void SetMovingSliceNumber(int MovingSliceNumber);

	void ApplyLookupTable();

	void SetMovingPlaneGrayScaleMappingOff();
	void SetFixedPlaneGrayScaleMappingOn();

	void SetProgram(GLuint program);

	void SetFixedSlice(float SliceValue);
	void SetMovingSlice(float SliceValue);

	

private:

	misGpuAxialMultiplaneRepresentation::Pointer m_FixedPlane;
	misGpuAxialMultiplaneRepresentation::Pointer m_MovingPlane;
	vtkTransform *m_MovingPlaneTransfrom;
	vtkImageData *m_MovingImage;
	vtkImageData *m_FixedImage;

	vtkLookupTable *m_LookUpTable;
	int m_NormalizedSliceNumber;

	
};