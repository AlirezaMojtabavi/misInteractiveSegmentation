#include "stdafx.h"
#include "misVisualizationResourceManager.h"

#include "misFileReader.h"
#include "misLogger.h"

using namespace std;

misVisualizationResourceManager::misVisualizationResourceManager(void)
{

	m_ManModel = NULL;
	SetDefaultlandamrkSizes();

}

void misVisualizationResourceManager::SetDefaultlandamrkSizes()
{

	m_NumericalLandmarks.resize(MAXNUMOFLANDMARK);
	m_CheckLandmarks.resize(5);
	m_EntryLandmarks.resize(4);
	m_TargetLandmarks.resize(4);
	m_PointLandmarks.resize(5);
	m_CapturePointLandmark = 0;
}

 

misVisualizationResourceManager* misVisualizationResourceManager::GetInstance()
{
	static bool		instanceFlag = false;

	static misVisualizationResourceManager* s_VisResManger;


	if (!instanceFlag)
	{
		s_VisResManger = new misVisualizationResourceManager;
		s_VisResManger->LoadTextureParallel();
		instanceFlag = true;
		static  bool glewInitedFlag = false;

		if (!glewInitedFlag)
		{
			glewInit();
			glewInitedFlag = true;
		}
		return s_VisResManger;
	}
	else
	{
		return s_VisResManger;
	}
}

void misVisualizationResourceManager::Release()
{
	m_AxialTexture = nullptr;
	m_SagittalTexture = nullptr;
	m_CoronalTexture = nullptr;
	m_NumericalLandmarks.clear();
	m_CheckLandmarks.clear();
	m_EntryLandmarks.clear();
	m_TargetLandmarks.clear();
	m_PointLandmarks.clear();
	m_CapturePointLandmark = nullptr;
	SetDefaultlandamrkSizes();
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::GetAxialTexture()
{

	if (!m_AxialTexture)
	{
		ReadAxialTexture();
	}
	return m_AxialTexture;


}

vtkSmartPointer<vtkTexture>  misVisualizationResourceManager::GetCoranlaTexture()
{
	if (!m_CoronalTexture)
	{
		ReadCoranlaTexture();
	}
	return m_CoronalTexture;
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::GetSagittalTexture()
{
	if (!m_SagittalTexture)
	{
		ReadSagittalTexture();
	}

	return m_SagittalTexture;
}

void misVisualizationResourceManager::ReadAxialTexture(void)
{
	m_AxialTexture = vtkSmartPointer<vtkTexture>::New();
	vtkPNGReader* pPngReader = vtkPNGReader::New();
	char dirFile[100];
	GetCurrentDirectoryA(99, dirFile);
	string  axialPath;
	axialPath.append(dirFile);
	axialPath.append("\\Resources\\axial.png");
	pPngReader->SetFileName((char*)axialPath.c_str());
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFileA((char*)axialPath.c_str(), &FindFileData);
	_ASSERT(hFind != INVALID_HANDLE_VALUE);
 	m_AxialTexture->SetInputConnection(pPngReader->GetOutputPort());
	m_AxialTexture->Update();
	pPngReader->Delete();
}

void misVisualizationResourceManager::ReadCoranlaTexture(void)
{
	m_CoronalTexture = vtkSmartPointer<vtkTexture>::New();
	vtkPNGReader* pPngReader = vtkPNGReader::New();
	char dirFile[100];
	GetCurrentDirectoryA(99, dirFile);
	string  axialPath;
	axialPath.append(dirFile);
	axialPath.append("\\Resources\\coronal.png");

	pPngReader->SetFileName((char*)axialPath.c_str());
	m_CoronalTexture->SetInputConnection(pPngReader->GetOutputPort());
	m_CoronalTexture->Update();
	pPngReader->Delete();
}

void misVisualizationResourceManager::ReadSagittalTexture(void)
{
	m_SagittalTexture = vtkSmartPointer<vtkTexture>::New();
	vtkPNGReader* pPngReader = vtkPNGReader::New();
	char dirFile[100];
	GetCurrentDirectoryA(99, dirFile);
	string axialPath;
	axialPath.append(dirFile);
	axialPath.append("\\Resources\\sagittal.png");

	pPngReader->SetFileName((char*)axialPath.c_str());
	m_SagittalTexture->SetInputConnection(pPngReader->GetOutputPort());
	m_SagittalTexture->Update();
	pPngReader->Delete();
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::GetLandmarkTexture(int index, LANDMARKLABLETYPE LndType)
{

	vtkSmartPointer<vtkTexture> result = 0;

	if (LndType == NUMERICALLANDMARK)
		result = ExtractNumericalTexture(index);

	else if (LndType == CHECKLANDMARK)
		result = ExtractCheckTexture(index);

	else if (LndType == ENTRYLANDMARK)
		result = ExtractEntryTexture(index);

	else if (LndType == TARGETLANDMARK)
		result = ExtractTargetTexture(index);

	else if (LndType == POINTLANDMARK)
		result = ExtractPointTexture(index);

	else if (LndType == CAPTUREPOINTLANDMARK)
		result = ExtractCapturePointTexture();

	return  result;
}

void misVisualizationResourceManager::FillTextures()
{
	FillNumericalLandmarkLables();
	FillCheckLandmarkLables();
	FillEntryLandmarkLables();
	FillTargetLandmarkLables();
	FillPointLandmarkLables();
	FillCapturePointLandmarkLable();
}

void misVisualizationResourceManager::LoadTextureParallel()
{
	FillTextures();
}

std::vector<vtkSmartPointer<vtkActor>>  misVisualizationResourceManager::GetManModel()
{
	static auto first = true;
	static 	std::vector<vtkSmartPointer<vtkActor>> result;

	if (first)
	{
		std::string modelName;
		char directory[101];
		GetCurrentDirectoryA(100, directory);
		modelName.append(directory);
		modelName.append("\\Resources");
		modelName.append("\\3d Model\\Man\\Man 20.3DS");
		mis3DSImporter* importer = mis3DSImporter::New();
		importer->SetFileName(modelName.c_str());
		importer->ComputeNormalsOn();
		importer->Read();
		m_ManModelBlocks = importer->getBatches();
		auto  actorCollection = importer->getActors();
		first = false;

		for_each(m_ManModelBlocks.cbegin(), m_ManModelBlocks.cend(), [&](const bachBlock& block)
		{
			vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
			vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			mapper->SetInputConnection(block.algorithm);
			actor->SetProperty(block.prop);
			actor->SetMapper(mapper);
			result.push_back(actor);
		}
		);
	}
		return  result;
 
}

void misVisualizationResourceManager::FillNumericalLandmarkLables()
{
	for (int i = 0; i < MAXNUMOFLANDMARK; i++)
	{
		vtkSmartPointer<vtkTexture> pTexture = vtkSmartPointer<vtkTexture>::New();
		vtkPNGReader* pPngReader = vtkPNGReader::New();
		char dirFile[100];
		GetCurrentDirectoryA(99, dirFile);
		std::string imageFilePathStr;
		imageFilePathStr.append(dirFile);
		imageFilePathStr.append("\\Resources\\landmarks\\landmark_");
		imageFilePathStr.append(std::to_string(i + 1));
		imageFilePathStr.append(".png");
		pPngReader->SetFileName(imageFilePathStr.c_str());
		pTexture->SetInputConnection(pPngReader->GetOutputPort());
		pTexture->Update();
		pPngReader->Delete();
		m_NumericalLandmarks[i] = pTexture;
	}
}

void misVisualizationResourceManager::FillCheckLandmarkLables()
{
	for (int i = 0; i < 5; i++)
	{
		vtkSmartPointer<vtkTexture> pTexture = vtkSmartPointer<vtkTexture>::New();
		vtkPNGReader* pPngReader = vtkPNGReader::New();
		char dirFile[100];
		GetCurrentDirectoryA(99, dirFile);
		std::ostringstream imageFilePathStr;
		imageFilePathStr << dirFile << "\\Resources\\landmarks\\landmark_C" << i + 1 << ".png";
		pPngReader->SetFileName(imageFilePathStr.str().c_str());
		pTexture->SetInputConnection(pPngReader->GetOutputPort());
		pTexture->Update();
		pPngReader->Delete();
		m_CheckLandmarks[i] = pTexture;
	}
}

void misVisualizationResourceManager::FillEntryLandmarkLables()
{
	for (int i = 0; i < 4; i++)
	{
		vtkSmartPointer<vtkTexture> pTexture = vtkSmartPointer<vtkTexture>::New();
		vtkPNGReader* pPngReader = vtkPNGReader::New();
		char dirFile[100];
		GetCurrentDirectoryA(99, dirFile);
		std::ostringstream imageFilePathStr;
		imageFilePathStr << dirFile << "\\Resources\\landmarks\\landmark_E" << i + 1 << ".png";
		pPngReader->SetFileName(imageFilePathStr.str().c_str());
		pTexture->SetInputConnection(pPngReader->GetOutputPort());
		pTexture->Update();
		pPngReader->Delete();
		m_EntryLandmarks[i] = pTexture;
	}
}

void misVisualizationResourceManager::FillTargetLandmarkLables()
{
	for (int i = 0; i < 4; i++)
	{
		vtkSmartPointer<vtkTexture> pTexture = vtkSmartPointer<vtkTexture>::New();
		vtkPNGReader* pPngReader = vtkPNGReader::New();
		char dirFile[100];
		GetCurrentDirectoryA(99, dirFile);
		std::ostringstream imageFilePathStr;
		imageFilePathStr << dirFile << "\\Resources\\landmarks\\landmark_T" << i + 1 << ".png";
		pPngReader->SetFileName(imageFilePathStr.str().c_str());
		pTexture->SetInputConnection(pPngReader->GetOutputPort());
		pTexture->Update();
		pPngReader->Delete();
		m_TargetLandmarks[i] = pTexture;
	}
}

void misVisualizationResourceManager::FillPointLandmarkLables()
{
	for (int i = 0; i < 5; i++)
	{
		vtkSmartPointer<vtkTexture> pTexture = vtkSmartPointer<vtkTexture>::New();
		vtkPNGReader* pPngReader = vtkPNGReader::New();
		char dirFile[100];
		GetCurrentDirectoryA(99, dirFile);
		std::ostringstream imageFilePathStr;
		imageFilePathStr << dirFile << "\\Resources\\landmarks\\landmark_P" << i + 1 << ".png";
		pPngReader->SetFileName(imageFilePathStr.str().c_str());
		pTexture->SetInputConnection(pPngReader->GetOutputPort());
		pTexture->Update();
		pPngReader->Delete();
		m_PointLandmarks[i] = pTexture;
	}
}

void misVisualizationResourceManager::FillCapturePointLandmarkLable()
{
	if (!m_CapturePointLandmark)
		m_CapturePointLandmark = vtkSmartPointer<vtkTexture>::New();

	vtkPNGReader* pPngReader = vtkPNGReader::New();
	char dirFile[100];
	GetCurrentDirectoryA(99, dirFile);
	string  lnadpathPath(dirFile);
	lnadpathPath.append("\\Resources\\landmarks\\landmark_CP.png");

	pPngReader->SetFileName((char*)lnadpathPath.c_str());
	m_CapturePointLandmark->SetInputConnection(pPngReader->GetOutputPort());
	m_CapturePointLandmark->Update();
	pPngReader->Delete();
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::ExtractNumericalTexture(int index)
{
	_ASSERT(index > 0);
	if (index - 1 < m_NumericalLandmarks.size())
		return m_NumericalLandmarks[index - 1];
	return  NULL;
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::ExtractCheckTexture(int index)
{
	_ASSERT(index > 0);
	if (index - 1 < m_CheckLandmarks.size())
		return m_CheckLandmarks[index - 1];
	else
		return  NULL;
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::ExtractEntryTexture(int index)
{
	_ASSERT(index > 0);
	if (index - 1 < m_EntryLandmarks.size())
		return m_EntryLandmarks[index - 1];
	return  NULL;
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::ExtractTargetTexture(int index)
{
	_ASSERT(index > 0);
	if (index - 1 < m_TargetLandmarks.size())
		return m_TargetLandmarks[index - 1];
	return  NULL;
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::ExtractPointTexture(int index)
{
	_ASSERT(index > 0);
	if (index - 1 < m_PointLandmarks.size())
		return m_PointLandmarks[index - 1];
	return  NULL;
}

vtkSmartPointer<vtkTexture> misVisualizationResourceManager::ExtractCapturePointTexture()
{
	if (m_CapturePointLandmark)
		return m_CapturePointLandmark;
	return  NULL;
}

vtkPolyData* misVisualizationResourceManager::GetArrowStl()
{

	string filename;
	filename.append("3d Model\\Arrow\\");
	filename.append("Arrow");
	filename.append(".STL");
	vtkSTLReader* stlReader = vtkSTLReader::New();
	stlReader->MergingOff();

	char dirFile[100];
	GetCurrentDirectoryA(99, dirFile);
	string  lnadpathPath;
	lnadpathPath.append(dirFile);
	lnadpathPath.append("\\Resources\\");
	lnadpathPath.append(filename);
	stlReader->SetFileName(/*(char*)*/lnadpathPath.c_str());
	stlReader->Update();
	return stlReader->GetOutput();

}

