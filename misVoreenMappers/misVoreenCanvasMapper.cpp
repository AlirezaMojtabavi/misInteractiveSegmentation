#include "StdAfx.h"
#include "misVoreenCanvasMapper.h"

#include "meshentryexitpoints.h"
#include "misApplicationSetting.h"
#include "misTransFunctionBuilder.h"
#include "misVTKMattoTgtMatConvertor.h"
#include "singleton.h"

using std::vector;
using namespace voreen;

misVoreenCanvasMapper::misVoreenCanvasMapper(void)
{
	voreen::VoreenApplication* voreenApp = Singleton<voreen::VoreenApplication>::GetInstance();
	if (!voreenApp->isInitilized())
	{

		voreenApp->init();
		voreenApp->initGL();
	}
	m_CanvasProcess = new voreen::CanvasRenderer;
	m_CanvasProcess->initialize();
	m_CanvasProcess->SetOrder(3);
	m_Processors.push_back(m_CanvasProcess);

	SortProcessors();
	/*m_NeedUpdtae=true;*/
	m_Modified = true;
	m_CameraChanged = true;
	m_TFSelector = NULL;
}

misVoreenCanvasMapper::~misVoreenCanvasMapper(void)
{
	delete m_CanvasProcess;
}

void misVoreenCanvasMapper::SetCanvasPart(std::map<misOpenglTexture*, voreen::VolumeHandle*> volumeHandleMap,
	std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> textureMap, tgt::ivec3 size)
{
	SetRayCastPart(volumeHandleMap, textureMap, size);
	m_CanvasProcess->SetInport(m_RayCasterProcess->GetOutPort());
	int* siz = renderer->GetSize();
	tgt::ivec2  wsize;
	wsize[0] = siz[0];
	wsize[1] = siz[1];
	this->SetWindowSize(wsize);
	SortProcessors();
}



void misVoreenCanvasMapper::Render(vtkRenderer *ren, vtkActor *a)
{

	ren->GetRenderWindow()->MakeCurrent();
	double clip_range[2];
	ren->GetActiveCamera()->GetClippingRange(clip_range);

	SetCmaeraProp(ren);
	SetLightSourceProperties(renderer);

	tgt::Camera  cam = this->GetCamera();
	m_CameraChanged = !(cam == m_CuurentCamera);
	m_CuurentCamera = cam;
	if (this->NeedUpdate())
	{
		std::for_each(m_Processors.begin(), m_Processors.end(), [&](voreen::Processor*  process)
		{

			process->beforeProcess();
			if (process->isReady())
				process->process();
			process->afterProcess();

		});
	}
	else
	{
		m_CanvasProcess->process();
	}

	glUseProgram(0);

}

void misVoreenCanvasMapper::SetWindowSize(tgt::ivec2 size)
{
	std::for_each(m_Processors.begin(), m_Processors.end(), [&](voreen::Processor* prs)

	{
		prs->SetWindowSize(size);
	});

	m_Modified = true;//Force to update volume rendering output
}

voreen::CanvasRenderer* misVoreenCanvasMapper::GetCanvasProcess() const
{
	return m_CanvasProcess;
}

void misVoreenCanvasMapper::SortProcessors()
{
	auto SortFunc = [](voreen::Processor* a, voreen::Processor* b)->bool
	{
		return(a->GetOrder() < b->GetOrder());
	};
	sort(m_Processors.begin(), m_Processors.end(), SortFunc);
}

void misVoreenCanvasMapper::SetClipingPlane(tgt::vec4 plane)
{

	std::for_each(m_Processors.begin(), m_Processors.end(), [&](voreen::Processor* prs)

	{
		MeshEntryExitPoints* process = dynamic_cast<MeshEntryExitPoints*>(prs);
		if (process)
		{
			process->SetPlane(plane);
		}
	});

}


void misVoreenCanvasMapper::ClipingOn()
{

	std::for_each(m_Processors.begin(), m_Processors.end(), [&](voreen::Processor* prs)

	{
		MeshEntryExitPoints* process = dynamic_cast<MeshEntryExitPoints*>(prs);
		if (process)
		{
			process->SetCLipWithARbitaryPlane(true);
		}
	});

}
void misVoreenCanvasMapper::ClipingOF()
{

	std::for_each(m_Processors.begin(), m_Processors.end(), [&](voreen::Processor* prs)

	{
		MeshEntryExitPoints* process = dynamic_cast<MeshEntryExitPoints*>(prs);
		if (process)
		{
			process->SetCLipWithARbitaryPlane(false);
		}
	});

}

tgt::RenderTarget* misVoreenCanvasMapper::GetVolumeRenderOutputTarget()
{

	tgt::RenderTarget*  out = NULL;
	std::for_each(m_Processors.begin(), m_Processors.end(), [&](voreen::Processor* prs)

	{
		MultiVolumeRaycaster* process = dynamic_cast<MultiVolumeRaycaster*>(prs);
		if (process)
		{
			out = process->GetOutPort();
		}
	});
	return  out;
}


bool misVoreenCanvasMapper::NeedUpdate()
{

	bool val = misApplicationSetting::GetInstance()->m_VisulaizationSetting.useRayCastOnCameraChange;
	if (!val)
	{
		return  true;
	}

	bool neeedUpdate = false;
	if (this->GetCropping() != NoCut)
	{
		neeedUpdate = true;
	}
	if (m_CameraChanged)
	{
		neeedUpdate = true;
	}
	if (m_Modified)
	{
		neeedUpdate = true;
		m_Modified = false;
	}

	return  neeedUpdate;
}

void misVoreenCanvasMapper::Modify()
{
	this->m_Modified = true;
}

void misVoreenCanvasMapper::RnderProxyGeometry(bool val)
{
	this->SetRenderEntryToScene(val);
}

int misVoreenCanvasMapper::FindNearestPoint(double p1[3], double p2[3], double tol, double* intersectedPoint)
{


	int numberOfVolume = this->m_RayCasterProcess->GetNumofActiveVolumes();

	if (numberOfVolume == 0)
		return 2;

	float dot = -1;
	float step = 0.0;

	vector<int> previousIndex;
	previousIndex.resize(this->m_RayCasterProcess->GetNumofActiveVolumes(), -1);

	struct pointData
	{
		double    opacity;
		double    position[3];

		pointData()
		{
			opacity = 0.0;
			position[0] = 0.0;
			position[1] = 0.0;
			position[2] = 0.0;
		}

		void operator =(pointData right)
		{
			this->opacity = right.opacity;

			this->position[0] = right.position[0];
			this->position[1] = right.position[1];
			this->position[2] = right.position[2];
		}

	};

	vector<pointData> lineData;
	double lineSize = 10000;
	lineData.resize(lineSize);
	pointData currentData;

	double  currentPosition[3];
	bool  rangeChecX, rangeChecY, rangeChecz;
	float totalOpacity = 0;

	float currentPositionOpacity;
	int counter = 0;

	double lineNormal[3];
	lineNormal[0] = p2[0] - p1[0];
	lineNormal[1] = p2[1] - p1[1];
	lineNormal[2] = p2[2] - p1[2];
	vtkMath::Normalize(lineNormal);

	while ((dot <= 0) && (totalOpacity < 1.3))
	{
		this->FindNewPositionOnLine(currentPosition, p1, lineNormal, step);
		dot = this->IsInside(currentPosition, p1, p2);

		currentPositionOpacity = -1;
		for (int i = 0; i < this->m_RayCasterProcess->GetNumofActiveVolumes(); i++)
		{
			voreen::VolumeHandle*  volume = this->getHandle(i);
			misOpenglTexture*  texture = NULL;
			if (volume)
			{
				texture = volume->getVolume()->getTexture();
			}
			if (!texture)
				continue;
			tgt::mat4   mat = volume->getVolume()->GetRelativeTransform();
			mat = tgt::mat4::identity;
			misVTKMattoTgtMatConvertor convertor;
			vtkSmartPointer<vtkMatrix4x4> matrix = convertor(mat);
			vtkSmartPointer<vtkTransform> pTrans = vtkSmartPointer<vtkTransform>::New();
			pTrans->SetMatrix(matrix);
			double* transformedPosition = pTrans->TransformDoublePoint(currentPosition);
			int index = this->GetIndexInImagePointer(texture, transformedPosition, rangeChecX, rangeChecY, rangeChecz);
			auto dims = texture->getDimensions();
			int sizeImage = dims[0] * dims[1] * dims[2];

			if ((index >= sizeImage) || (index < 0))
				continue;

			if (previousIndex[i] == index)
				continue;

			previousIndex[i] = index;

			double mainImageValue = 0;
			if (texture->getDataType() == GL_UNSIGNED_BYTE)
				mainImageValue = texture->texel<unsigned char>(index);
			else if (texture->getDataType() == GL_SHORT)
				mainImageValue = texture->texel<short>(index);
			else if (texture->getDataType() == GL_UNSIGNED_SHORT)
				mainImageValue = texture->texel<unsigned short>(index);
			else
				continue;

			double *tableRange = texture->GetTableRange();
			double intensity = misTransFunctionBuilder::ConvertIntensityToKeyValue(tableRange, mainImageValue);
			auto color = this->m_TFSelector->GetCorrespondingTransFunColor(texture, intensity);/*m_SelectionElemnts[i].m_TransferFunction->getMappingForValue(intensity);*/


			if (-1 == currentPositionOpacity) // Note : On first point finding
			{
				currentPositionOpacity = 0.0;
			}
			currentPositionOpacity = currentPositionOpacity + double(color.alpha) / 255.0;


		}//end  vector


		if (currentPositionOpacity != -1) // a valid point has been find
		{
			totalOpacity = totalOpacity + currentPositionOpacity;

			currentData.opacity = currentPositionOpacity;
			currentData.position[0] = currentPosition[0];
			currentData.position[1] = currentPosition[1];
			currentData.position[2] = currentPosition[2];

			_ASSERT(!((0 == currentData.position[0]) && (0 == currentData.position[1]) && (0 == currentData.position[2])));

			if (counter < lineSize)
			{
				lineData[counter] = currentData;
			}
			else
			{
				_ASSERT(false == true);
			}

			counter++;
		}


	}//end while

	pointData currentPoint, nextPoint;

	double maxOpacity = 0;
	double maxOpaciyID = 0;
	for (int i = 1; i < lineData.size() - 1; i++)
	{
		currentPoint = lineData[i];
		if (currentPoint.opacity > maxOpacity)
		{
			maxOpacity = currentPoint.opacity;
			maxOpaciyID = i;
		}
	}

	if (maxOpacity == 0)
	{
		return 0;
	}

	double opacityAcumulator = 0.0;
	for (int i = 1; i < counter - 1; i++)
	{
		currentPoint = lineData[i];
		nextPoint = lineData[i + 1];

		opacityAcumulator = opacityAcumulator + currentPoint.opacity;


		if ((currentPoint.opacity > 0.95) || (opacityAcumulator > 0.99))
		{
			_ASSERT(!((0 == nextPoint.position[0]) && (0 == nextPoint.position[1]) && (0 == nextPoint.position[2])));

			intersectedPoint[0] = nextPoint.position[0];
			intersectedPoint[1] = nextPoint.position[1];
			intersectedPoint[2] = nextPoint.position[2];

			return  1;
		}
	}

	// find the maximum point
	if (maxOpaciyID > 0)
	{
		currentPoint = lineData[maxOpaciyID];
		_ASSERT(!((0 == currentPoint.position[0]) && (0 == currentPoint.position[1]) && (0 == currentPoint.position[2])));

		intersectedPoint[0] = nextPoint.position[0];
		intersectedPoint[1] = nextPoint.position[1];
		intersectedPoint[2] = nextPoint.position[2];

		return  1;
	}

	return  0;
}



misVoreenCanvasMapper* misVoreenCanvasMapper::New()
{
	return  new misVoreenCanvasMapper;
}






float misVoreenCanvasMapper::IsInside(double * position, double * p1, double * p2)
{
	double vec1[3];
	double vec2[3];
	for (int ii = 0; ii < 3; ii++)
		vec1[ii] = position[ii] - p1[ii];

	for (int ii = 0; ii < 3; ii++)
		vec2[ii] = position[ii] - p2[ii];


	float dot = vtkMath::Dot(vec1, vec2);
	return dot;
}

void misVoreenCanvasMapper::FindNewPositionOnLine(double * newPosition, double * startPosition, double * lineNormal, float& step)
{
	step = step + 0.4 /** 0.9*/;
	for (int ii = 0; ii < 3; ii++)
		newPosition[ii] = startPosition[ii] + lineNormal[ii] * step;
}

int  misVoreenCanvasMapper::GetIndexInImagePointer(misOpenglTexture* pImage, double * position, bool &rangeChecX, bool &rangeChecY, bool &rangeChecz)
{

	auto  dims = pImage->GetTexturePropertyStrct().GetDimensions();
	auto origin = pImage->GetTexturePropertyStrct().Origin;
	auto spaceing = pImage->GetTexturePropertyStrct().Spacing;
	misROI  roi = pImage->GetROI();
	bool res = roi.ContainsPoint(position[0], position[1], position[2]);
	if (!res)
		return  -1;
	int   i, j, k;
	i = (position[0] - origin[0]) / spaceing[0];
	j = (position[1] - origin[1]) / spaceing[1];
	k = (position[2] - origin[2]) / spaceing[2];


	rangeChecX = (i >= 0) && (i <= dims[0]);
	rangeChecY = (j >= 0) && (j <= dims[1]);
	rangeChecz = (k >= 0) && (k <= dims[2]);

	if (!rangeChecX || !rangeChecY || !rangeChecz)
		return  -1;


	int index = i + j * dims[0] + k * dims[0] * dims[1];
	return index;
}

void misVoreenCanvasMapper::SetTransferFunctionSelector(misTransferFunctionSelecting* viewerTFSelector)
{
	if (viewerTFSelector)
	{
		this->m_TFSelector = viewerTFSelector;
	}
	else
		_ASSERT(0 == 1);
}