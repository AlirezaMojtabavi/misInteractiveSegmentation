#pragma once
#ifndef __misVisulizationResourceMnager__
#define __misVisulizationResourceMnager__

#define   MAXNUMOFLANDMARK    20

#include "mis3DSImporter.h"
#include "misLandmarkenums.h"
#include "misObject.h"

class  misVisualizationResourceManager
{




public:

	static  misVisualizationResourceManager*  GetInstance();
	void Release();
	vtkSmartPointer<vtkTexture>  GetAxialTexture();
	vtkSmartPointer<vtkTexture>  GetCoranlaTexture();
	vtkSmartPointer<vtkTexture>  GetSagittalTexture();
	vtkSmartPointer<vtkTexture> GetLandmarkTexture(int index, LANDMARKLABLETYPE LndType);
	vtkPolyData*  GetArrowStl();
	std::vector<vtkSmartPointer<vtkActor>> GetManModel();
	std::vector<bachBlock>  m_ManModelBlocks;
	misVisualizationResourceManager(void);
	void SetDefaultlandamrkSizes();
	void LoadTextureParallel();
	void FillTextures();
 
private:

 

	std::vector<vtkSmartPointer<vtkTexture>> m_NumericalLandmarks;
	std::vector<vtkSmartPointer<vtkTexture>> m_CheckLandmarks;
	std::vector<vtkSmartPointer<vtkTexture>> m_EntryLandmarks;
	std::vector<vtkSmartPointer<vtkTexture>> m_TargetLandmarks;
	std::vector<vtkSmartPointer<vtkTexture>> m_PointLandmarks;
	vtkSmartPointer<vtkTexture> m_CapturePointLandmark;

	vtkActorCollection*  m_ManModel;

	void ReadAxialTexture(void);
	void ReadCoranlaTexture(void);
	void ReadSagittalTexture(void);

	vtkSmartPointer<vtkTexture> m_AxialTexture;
	vtkSmartPointer<vtkTexture> m_CoronalTexture;
	vtkSmartPointer<vtkTexture> m_SagittalTexture;

	vtkSmartPointer<vtkTexture> ExtractNumericalTexture( int index );
	vtkSmartPointer<vtkTexture> ExtractCheckTexture( int index );
	vtkSmartPointer<vtkTexture> ExtractEntryTexture( int index );
	vtkSmartPointer<vtkTexture> ExtractTargetTexture( int index );
	vtkSmartPointer<vtkTexture> ExtractPointTexture( int index );
	vtkSmartPointer<vtkTexture> ExtractCapturePointTexture();
 
	void FillNumericalLandmarkLables();
	void FillCheckLandmarkLables();
	void FillEntryLandmarkLables();
	void FillTargetLandmarkLables();
	void FillPointLandmarkLables();
	void FillCapturePointLandmarkLable();

};

#endif
