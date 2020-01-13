#pragma  once 
#include "vtkSmartPointer.h"
#include "misImageActor.h"
#include "misEnums.h"
#include "vtkMatrix4x4.h"
#include "misColorStruct.h"
#include "misStrct3DLayer.h"
#include "BusinessEntities\Point.h"

typedef std::vector<misStrct3DLayer>  layerRep; 

class misImagePlaneInformationStrct 
{
	
public:
	
	misImagePlaneInformationStrct();;
	void Reset();;
	void SetExtends(const int* extends);
	const int* GetExtends() const;
	virtual parcast::PointD3   GetPlaneCenter();
	 void SetMapper(vtkMapper *);
	void GeneratePlaneMesh();
	vtkSmartPointer<misImageActor> GetActor();
	
	layerRep m_Layers;
	misImageViewingType	m_ImageViewingType;
	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
	double*	m_PlaneSpacing;
	bool m_showErased;
	misColorStruct	m_ErasedObjectColor;
private:
	vtkSmartPointer<misImageActor> m_pQuadActor;
	int m_PlaneExtent[6] ;
};