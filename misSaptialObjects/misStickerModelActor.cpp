#include "stdafx.h"
#include "misManModelActor.h"

vtkCxxSetObjectMacro(misStickerModelActor, m_Renderer, vtkRenderer);



// Creates a follower with no camera set
misStickerModelActor::misStickerModelActor()
{
	Device = vtkActor::New();
	m_Renderer = NULL;
	Camera = 0;
	m_ParallelOffset[0] = 30.0;
	m_ParallelOffset[1] = 50.0;

}

misStickerModelActor::~misStickerModelActor()
{
	if (m_Renderer)
	{
		m_Renderer->UnRegister(this);
	}
	Device->Delete();
}

// Copy the follower's composite 4x4 matrix into the matrix provided.
void misStickerModelActor::GetMatrix(vtkMatrix4x4 *result)
{

	double widthInWordldCoordinate = 0;
	double heightInWordldCoordinate = 0;

	double worldRUPt[4];
	m_Renderer->SetViewPoint(1.0, 1.0, 0.2);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldRUPt);

	double worldLUPt[4];
	m_Renderer->SetViewPoint(-1.0, 1.0, 0.2);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldLUPt);

	if (worldLUPt[3])
	{
		worldLUPt[0] /= worldLUPt[3];
		worldLUPt[1] /= worldLUPt[3];
		worldLUPt[2] /= worldLUPt[3];
		worldLUPt[3] = 1.0;
	}

	double worldRDPt[4];
	m_Renderer->SetViewPoint(1.0, -1.0, 0.2);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldRDPt);

	double worldLDPt[4];
	m_Renderer->SetViewPoint(-1.0, -1.0, 0.2);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldLDPt);
	if (worldLDPt[3])
	{
		worldLDPt[0] /= worldLDPt[3];
		worldRDPt[1] /= worldLDPt[3];
		worldLDPt[2] /= worldLDPt[3];
		worldLDPt[3] = 1.0;
	}

	double height[3];
	for (int i = 0; i < 3; i++)
		height[i] = worldRDPt[i] - worldRUPt[i];
	heightInWordldCoordinate = vtkMath::Dot(height, height);
	heightInWordldCoordinate = sqrt(heightInWordldCoordinate);

	double width[3];
	for (int i = 0; i < 3; i++)
		width[i] = worldRUPt[i] - worldLUPt[i];
	widthInWordldCoordinate = vtkMath::Dot(width, width);
	widthInWordldCoordinate = sqrt(widthInWordldCoordinate);

	float m_3DZoomScaleFactor = 1;
	if (heightInWordldCoordinate > widthInWordldCoordinate)
		m_3DZoomScaleFactor = widthInWordldCoordinate / m_ScaleRatio;
	else
		m_3DZoomScaleFactor = heightInWordldCoordinate / m_ScaleRatio;

	Transform->Push();
	Transform->PostMultiply();
	Transform->Identity();
	auto translation = Transform->TransformDoublePoint(0, 0, 0);
	//	Transform->Translate(-translation[0], -translation[1], -translation[2]);

	int parallelProjection = m_Renderer->GetActiveCamera()->GetParallelProjection();
	double manPosition[4];


	int* size = m_Renderer->GetRenderWindow()->GetSize();
	int displayCoord[2];
	if (parallelProjection)
	{
		float val1 = m_ParallelOffset[0] * (float(size[0]) / 700.0);
		displayCoord[0] = size[0] - val1;
		float val2 = m_ParallelOffset[1] * (float(size[1]) / 700.0);
		displayCoord[1] = size[1] - val2;
	}
	else
	{
		displayCoord[0] = size[0] - m_Offset[0];
		displayCoord[1] = size[1] - m_Offset[1];

	}
	double* bound = GetBounds();

	m_Renderer->SetDisplayPoint(displayCoord[0], displayCoord[1], 0.2);
	m_Renderer->DisplayToWorld();
	m_Renderer->GetWorldPoint(manPosition);

	Transform->Scale(m_3DZoomScaleFactor, m_3DZoomScaleFactor, m_3DZoomScaleFactor);

	//this chunk of code come from 'vtkFollower::GetMatrix(vtkMatrix4x4 *result)'
	double *pos, *vup;
	double Rx[3], Ry[3], Rz[3];
	vtkMatrix4x4 *matrix = vtkMatrix4x4::New();
	int i;
	double distance;
	Camera = m_Renderer->GetActiveCamera();
	if (Camera)
	{
		// do the rotation
		// first rotate y 
		pos = Camera->GetPosition();
		vup = Camera->GetViewUp();

		if (Camera->GetParallelProjection())
		{
			Camera->GetDirectionOfProjection(Rz);
			Rz[0] = -Rz[0];
			Rz[1] = -Rz[1];
			Rz[2] = -Rz[2];
		}
		else
		{
			distance = sqrt(
				(pos[0] - manPosition[0])*(pos[0] - manPosition[0]) +
				(pos[1] - manPosition[1])*(pos[1] - manPosition[1]) +
				(pos[2] - manPosition[2])*(pos[2] - manPosition[2]));
			for (i = 0; i < 3; i++)
			{
				Rz[i] = (pos[i] - manPosition[i]) / distance;
			}
		}

		// We cannot directly use the vup angle since it can be aligned with Rz:
		//vtkMath::Cross(vup,Rz,Rx);
		//vtkMath::Normalize(Rx);
		//vtkMath::Cross(Rz,Rx,Ry);       

		//instead use the view right angle:
		double dop[3], vur[3];
		Camera->GetDirectionOfProjection(dop);

		vtkMath::Cross(dop, vup, vur);
		vtkMath::Normalize(vur);

		vtkMath::Cross(Rz, vur, Ry);
		vtkMath::Normalize(Ry);
		vtkMath::Cross(Ry, Rz, Rx);

		matrix->Element[0][0] = Rx[0];
		matrix->Element[1][0] = Rx[1];
		matrix->Element[2][0] = Rx[2];
		matrix->Element[0][1] = Ry[0];
		matrix->Element[1][1] = Ry[1];
		matrix->Element[2][1] = Ry[2];
		matrix->Element[0][2] = Rz[0];
		matrix->Element[1][2] = Rz[1];
		matrix->Element[2][2] = Rz[2];

		Transform->Concatenate(matrix);
	}
	Transform->Translate(manPosition);
	// Transform->Scale(  1, 1,  1);   
	Transform->GetMatrix(result);
	Transform->Pop();

}

void misStickerModelActor::PrintSelf(ostream& os, vtkIndent indent)
{
	Superclass::PrintSelf(os, indent);

}

int misStickerModelActor::RenderOpaqueGeometry(vtkViewport *vp)
{
	if (!Mapper)
	{
		return 0;
	}

	if (!Property)
	{
		// force creation of a property
		GetProperty();
	}

	if (GetIsOpaque())
	{
		vtkRenderer *ren = static_cast<vtkRenderer *>(vp);
		Render(ren);
		return 1;
	}
	return 0;
}

//-----------------------------------------------------------------------------
int misStickerModelActor::RenderTranslucentPolygonalGeometry(vtkViewport *vp)
{
	if (!Mapper)
	{
		return 0;
	}

	if (!Property)
	{
		// force creation of a property
		GetProperty();
	}

	if (!GetIsOpaque())
	{
		vtkRenderer *ren = static_cast<vtkRenderer *>(vp);
		Render(ren);
		return 1;
	}
	return 0;
}

//-----------------------------------------------------------------------------
// Description:
// Does this prop have some translucent polygonal geometry?
int misStickerModelActor::HasTranslucentPolygonalGeometry()
{
	if (!Mapper)
	{
		return 0;
	}
	// make sure we have a property
	if (!Property)
	{
		// force creation of a property
		GetProperty();
	}

	// is this actor opaque ?
	return !GetIsOpaque();
}

//-----------------------------------------------------------------------------
// This causes the actor to be rendered. It, in turn, will render the actor's
// property and then mapper.  
void misStickerModelActor::Render(vtkRenderer *ren)
{

	Property->Render(this, ren);
	vtkMatrix4x4 *matrix = Device->GetUserMatrix();
	if (!matrix)
	{
		matrix = vtkMatrix4x4::New();
		Device->SetUserMatrix(matrix);
	}
	Device->SetProperty(Property);
	Property->Render(this, ren);
	if (BackfaceProperty)
	{
		BackfaceProperty->BackfaceRender(this, ren);
		Device->SetBackfaceProperty(BackfaceProperty);
	}
	// make sure the device has the same matrix
	GetMatrix(matrix);
	Device->SetUserMatrix(matrix);
	Device->Render(ren, Mapper);


}

void misStickerModelActor::GetMatrix(double m[16])
{
	GetMatrix(Matrix);
	vtkMatrix4x4::DeepCopy(m, Matrix);
}



void misStickerModelActor::SetCamera(vtkCamera* pCamera)
{
	Camera = pCamera;

}

void misStickerModelActor::SetObjectPosition(double ObjectPos[3]) {
	m_ObjectPosition[0] = ObjectPos[0];
	m_ObjectPosition[1] = ObjectPos[1];
	m_ObjectPosition[2] = ObjectPos[2];
}


misStickerModelActor * misStickerModelActor::New(double scaleRatio, double* offset)
{
	misStickerModelActor*  sticker = new misStickerModelActor();
	sticker->SetScaleRatio(scaleRatio);
	sticker->SetOffset(offset);
	return sticker;
}



void misStickerModelActor::SetScaleRatio(double val)
{
	m_ScaleRatio = val;
}



void misStickerModelActor::SetOffset(double* val)
{
	m_Offset[0] = val[0];
	m_Offset[1] = val[1];
}

