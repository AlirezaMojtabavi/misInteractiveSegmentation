#include "stdafx.h"
#include "misCorrectionTransformBox.h"
#include "misMathUtils.h"
#include "misitkTypdef.h"
#include "misROI.h"

using namespace std;

misCorrectionTransformBox::misCorrectionTransformBox()
	: m_CallBack(vtkCallbackCommand::New()), m_Enabled(false), m_lastCellId(-1)
	, m_FaceSelectCounter(0), TranslationEnabled(1), RotationEnabled(1), ScalingEnabled(1), InsideOut(0), OutlineFaceWires(0),
	OutlineCursorWires(1.0), m_SecondFaceIsSelected(false), m_Renderer(NULL), m_SelectedFaceActor(nullptr)
{
	m_CallBack->SetClientData(this);
	m_CallBack->SetCallback(misCorrectionTransformBox::ProcessEvents);
	ReadDefalutCubeTexture();
	vtkSmartPointer<vtkPolyDataMapper> hexMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	m_HexActor = vtkActor::New();
	m_HexActor->SetMapper(hexMapper);
	m_HexPolyData = vtkPolyData::New();
	m_Points = vtkPoints::New(VTK_DOUBLE);
	m_Points->SetNumberOfPoints(31);//8 corners; 6 faces; 1 center
	m_HexPolyData->SetPoints(m_Points);
	vtkIdType pts[4];
	vtkCellArray *cells = vtkCellArray::New();
	cells->Allocate(cells->EstimateSize(6, 4));
	//---FACE 1 ----
	pts[0] = 0; pts[1] = 1; pts[2] = 2; pts[3] = 3;
	cells->InsertNextCell(4, pts);
	//---FACE 2 ----
	pts[0] = 4; pts[1] = 5; pts[2] = 6; pts[3] = 7;
	cells->InsertNextCell(4, pts);
	//---FACE 3 ----
	pts[0] = 8; pts[1] = 9; pts[2] = 10; pts[3] = 11;
	cells->InsertNextCell(4, pts);
	//---FACE 4 ----
	pts[0] = 12; pts[1] = 13; pts[2] = 14; pts[3] = 15;
	cells->InsertNextCell(4, pts);
	//---FACE 5 ----
	pts[0] = 16; pts[1] = 17; pts[2] = 18; pts[3] = 19;
	cells->InsertNextCell(4, pts);
	//---FACE 6 ----
	pts[0] = 20; pts[1] = 21; pts[2] = 22; pts[3] = 23;
	cells->InsertNextCell(4, pts);
	m_HexPolyData->SetPolys(cells);
	cells->Delete();
	m_HexPolyData->BuildCells();

	hexMapper->SetInputData(m_HexPolyData);

	// The face of the hexahedra
	cells = vtkCellArray::New();
	cells->Allocate(cells->EstimateSize(1, 4));
	cells->InsertNextCell(4, pts); //temporary, replaced later
	HexFacePolyData = vtkPolyData::New();
	HexFacePolyData->SetPoints(m_Points);
	HexFacePolyData->SetPolys(cells);
	HexFaceMapper = vtkPolyDataMapper::New();
	HexFaceMapper->SetInputData(HexFacePolyData);
	HexFace = vtkActor::New();
	HexFace->SetMapper(HexFaceMapper);
	cells->Delete();
	OutlinePolyData = vtkPolyData::New();
	OutlinePolyData->SetPoints(m_Points);
	OutlineMapper = vtkPolyDataMapper::New();
	OutlineMapper->SetInputData(OutlinePolyData);
	HexOutline = vtkActor::New();
	HexOutline->SetMapper(OutlineMapper);
	cells = vtkCellArray::New();
	cells->Allocate(cells->EstimateSize(15, 2));
	OutlinePolyData->SetLines(cells);
	cells->Delete();
	CreateDefaultProperties();
	GenerateOutline();
	m_Handles.resize(7.0);
	HandleMapper.resize(m_Handles.size());
	HandleGeometry.resize(m_Handles.size());
	std::fill(m_Handles.begin(), m_Handles.end(), vtkSmartPointer<vtkActor>::New());
	std::fill(HandleMapper.begin(), HandleMapper.end(), vtkSmartPointer<vtkPolyDataMapper>::New());
	std::fill(HandleGeometry.begin(), HandleGeometry.end(), vtkSmartPointer<vtkSphereSource>::New());
	for (int i = 0; i < m_Handles.size(); i++)
	{
		HandleGeometry[i]->SetThetaResolution(16);
		HandleGeometry[i]->SetPhiResolution(8);
		HandleMapper[i]->SetInputConnection(HandleGeometry[i]->GetOutputPort());
		m_Handles[i]->SetMapper(HandleMapper[i]);
	}
	HandlePicker = vtkCellPicker::New();
	HandlePicker->SetTolerance(0.001);
	for (int i = 0; i < 7; i++)
		HandlePicker->AddPickList(m_Handles[i]);
	HandlePicker->PickFromListOn();
	HexPicker = vtkCellPicker::New();
	HexPicker->SetTolerance(0.001);
	HexPicker->AddPickList(m_HexActor);
	HexPicker->PickFromListOn();
	FillDefaultFaceInformation();
	UseDefaultFacesInformation();
}

misCorrectionTransformBox::~misCorrectionTransformBox()
{
	m_HexActor->Delete();
	HexFace->Delete();
	HexFaceMapper->Delete();
	HexFacePolyData->Delete();
	HexOutline->Delete();
	OutlineMapper->Delete();
	OutlinePolyData->Delete();
	HandlePicker->Delete();
	HexPicker->Delete();
	HandleProperty->Delete();
	SelectedHandleProperty->Delete();
	FaceProperty->Delete();
	SelectedFaceProperty->Delete();
	OutlineProperty->Delete();
	SelectedOutlineProperty->Delete();
}

void misCorrectionTransformBox::SetEnabled(int enabling)
{
	if (!m_Renderer)
		return;
	if (enabling)
		EnabledOn();
	else
		EnabledOff();
	m_Renderer->Render();
}

void misCorrectionTransformBox::ProcessEvents(vtkObject* vtkNotUsed(object),
	unsigned long event,
	void* clientdata,
	void* vtkNotUsed(calldata))
{
	misCorrectionTransformBox* self = reinterpret_cast<misCorrectionTransformBox *>(clientdata);
	switch (event)
	{
	case vtkCommand::LeftButtonPressEvent:
		self->OnLeftButtonDown();
		break;
	}
}

void misCorrectionTransformBox::SizeHandles()
{
	for (int i = 0; i < HandleGeometry.size(); i++)
		HandleGeometry[i]->SetRadius(5.0);
}

int misCorrectionTransformBox::HighlightHandle(vtkProp *prop)
{
	m_SelectedFaceActor = static_cast<vtkActor *>(prop);
	if (!m_SelectedFaceActor)
		return -1;
	for (int i = 0; i < 6; i++) //find attached face
	{
		if (m_SelectedFaceActor == m_Handles[i])
		{
			return i;
		}
	}
	return -1;
}

void misCorrectionTransformBox::SetDefaultSelectedFace(int LastcellId)
{
	if ((LastcellId < 0) || (LastcellId > 5))
	{
		return;
	}
	vtkIdType npts;
	vtkIdType *pts;
	vtkCellArray *cells = HexFacePolyData->GetPolys();
	m_HexPolyData->GetCellPoints(LastcellId, npts, pts);
	HexFacePolyData->Modified();
	cells->ReplaceCell(0, npts, pts);
	SetBlankTextureToAllFaces();
}

void misCorrectionTransformBox::OnLeftButtonDown()
{
	int X = m_Interactor->GetEventPosition()[0];
	int Y = m_Interactor->GetEventPosition()[1];

	// Okay, we can process this. Try to pick handles first;
	// if no handles picked, then pick the bounding box.
	if (!m_Renderer || !m_Renderer->IsInViewport(X, Y))
	{
		return;
	}
	HandlePicker->Pick(X, Y, 0.0, m_Renderer);
	vtkAssemblyPath * path = HandlePicker->GetPath();
	if (path != NULL)
	{
		UpdateFacesTexture(
			HighlightHandle(path->GetFirstNode()->GetViewProp()));
		HandlePicker->GetPickPosition(LastPickPosition);
	}
	else
	{
		HexPicker->Pick(X, Y, 0.0, m_Renderer);
		path = HexPicker->GetPath();
		if (path != NULL)
		{
			HexPicker->GetPickPosition(LastPickPosition);
			if (!m_Interactor->GetShiftKey())
			{
				HighlightHandle(NULL);
				UpdateFacesTexture(HexPicker->GetCellId());
			}
			else
			{
				m_SelectedFaceActor = m_Handles[6];
			}
		}
		else
		{
			UpdateFacesTexture(HighlightHandle(NULL));
			return;
		}
	}

	m_CallBack->SetAbortFlag(1);
	m_Interactor->InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
	m_Interactor->Render();
}

void misCorrectionTransformBox::GetDirection(const double Nx[3], const double Ny[3], const double Nz[3], double dir[3])
{
	double dotNy, dotNz;
	double y[3];

	if (vtkMath::Dot(Nx, Nx) != 0)
	{
		dir[0] = Nx[0];
		dir[1] = Nx[1];
		dir[2] = Nx[2];
	}
	else
	{
		dotNy = vtkMath::Dot(Ny, Ny);
		dotNz = vtkMath::Dot(Nz, Nz);
		if (dotNy != 0 && dotNz != 0)
		{
			vtkMath::Cross(Ny, Nz, dir);
		}
		else if (dotNy != 0)
		{
			//dir must have been initialized to the 
			//corresponding coordinate direction before calling
			//this method
			vtkMath::Cross(Ny, dir, y);
			vtkMath::Cross(y, Ny, dir);
		}
		else if (dotNz != 0)
		{
			//dir must have been initialized to the 
			//corresponding coordinate direction before calling
			//this method
			vtkMath::Cross(Nz, dir, y);
			vtkMath::Cross(y, Nz, dir);
		}
	}
}
void misCorrectionTransformBox::ComputeNormals()
{
	double *pts =
		static_cast<vtkDoubleArray *>(m_Points->GetData())->GetPointer(0);
	double *p0 = pts;
	double *px = pts + 3 * 1;
	double *py = pts + 3 * 3;
	double *pz = pts + 3 * 4;
	int i;

	for (i = 0; i < 3; i++)
	{
		N[0][i] = p0[i] - px[i];
		N[2][i] = p0[i] - py[i];
		N[4][i] = p0[i] - pz[i];
	}
	vtkMath::Normalize(N[0]);
	vtkMath::Normalize(N[2]);
	vtkMath::Normalize(N[4]);
	for (i = 0; i < 3; i++)
	{
		N[1][i] = -N[0][i];
		N[3][i] = -N[2][i];
		N[5][i] = -N[4][i];
	}
}

void misCorrectionTransformBox::CreateDefaultProperties()
{
	// m_Handles properties
	HandleProperty = vtkProperty::New();

	SelectedHandleProperty = vtkProperty::New();

	// Face properties
	FaceProperty = vtkProperty::New();
	FaceProperty->SetOpacity(0.0);

	SelectedFaceProperty = vtkProperty::New();
	SelectedFaceProperty->SetOpacity(0.01);

	// Outline properties
	OutlineProperty = vtkProperty::New();
	OutlineProperty->SetAmbient(1.0);
	OutlineProperty->SetLineWidth(5.0);

	SelectedOutlineProperty = vtkProperty::New();
	SelectedOutlineProperty->SetAmbient(1.0);
	SelectedOutlineProperty->SetLineWidth(2.0);
}

void misCorrectionTransformBox::PlaceWidget(double bds[6])
{
	m_Points->SetPoint(0, bds[0], bds[3], bds[5]);//-x ,+y ,+z
	m_Points->SetPoint(1, bds[0], bds[3], bds[4]);//-x ,+y,-z
	m_Points->SetPoint(2, bds[0], bds[2], bds[4]);//-x,-y,-z
	m_Points->SetPoint(3, bds[0], bds[2], bds[5]);//-x,-y,+z
	m_Points->SetPoint(4, bds[1], bds[3], bds[5]);//+x,+y,+z
	m_Points->SetPoint(5, bds[1], bds[3], bds[4]);//+x,+y,-z
	m_Points->SetPoint(6, bds[1], bds[2], bds[4]);//+x,-y,-z
	m_Points->SetPoint(7, bds[1], bds[2], bds[5]);//+x,-y,+z
	m_Points->SetPoint(8, bds[0], bds[3], bds[5]);//-x,+y,+z
	m_Points->SetPoint(9, bds[1], bds[3], bds[5]);//+x,+y,+z
	m_Points->SetPoint(10, bds[1], bds[2], bds[5]);//+x,-y,+z
	m_Points->SetPoint(11, bds[0], bds[2], bds[5]);//-x,-y,+z
	m_Points->SetPoint(12, bds[0], bds[3], bds[4]);//-x,y,-z
	m_Points->SetPoint(13, bds[1], bds[3], bds[4]);//+x,+y,-z
	m_Points->SetPoint(14, bds[1], bds[2], bds[4]);//+x,-y,-z
	m_Points->SetPoint(15, bds[0], bds[2], bds[4]);//-x,-y,-z
	m_Points->SetPoint(16, bds[0], bds[3], bds[4]);//-x,+y,-z
	m_Points->SetPoint(17, bds[1], bds[3], bds[4]);//+x,+y,-z
	m_Points->SetPoint(18, bds[1], bds[3], bds[5]);//+x,+y,+z
	m_Points->SetPoint(19, bds[0], bds[3], bds[5]);//-x,+y,+z
	m_Points->SetPoint(20, bds[0], bds[2], bds[4]);//-x,-y,-z
	m_Points->SetPoint(21, bds[1], bds[2], bds[4]);//+x,-y,-z
	m_Points->SetPoint(22, bds[1], bds[2], bds[5]);//+x,-y,+z
	m_Points->SetPoint(23, bds[0], bds[2], bds[5]);//-x,-y,+z
	ComputeNormals();
	SizeHandles();
}

vtkSmartPointer<vtkRenderWindowInteractor> misCorrectionTransformBox::GetInteractor() const
{
	return m_Interactor;
}

void misCorrectionTransformBox::GenerateOutline()
{
	// Whatever the case may be, we have to reset the Lines of the
	// OutlinePolyData (i.e. nuke all current line data)
	vtkCellArray *cells = OutlinePolyData->GetLines();
	cells->Reset();

	// Now the outline lines
	if (!OutlineFaceWires && !OutlineCursorWires)
	{
		return;
	}
	vtkIdType pts[2];
	if (OutlineFaceWires)
	{
		pts[0] = 0; pts[1] = 7;       //the -x face
		cells->InsertNextCell(2, pts);
		pts[0] = 3; pts[1] = 4;
		cells->InsertNextCell(2, pts);
		pts[0] = 1; pts[1] = 6;       //the +x face
		cells->InsertNextCell(2, pts);
		pts[0] = 2; pts[1] = 5;
		cells->InsertNextCell(2, pts);
		pts[0] = 1; pts[1] = 4;       //the -y face
		cells->InsertNextCell(2, pts);
		pts[0] = 0; pts[1] = 5;
		cells->InsertNextCell(2, pts);
		pts[0] = 3; pts[1] = 6;       //the +y face
		cells->InsertNextCell(2, pts);
		pts[0] = 2; pts[1] = 7;
		cells->InsertNextCell(2, pts);
		pts[0] = 0; pts[1] = 2;       //the -z face
		cells->InsertNextCell(2, pts);
		pts[0] = 1; pts[1] = 3;
		cells->InsertNextCell(2, pts);
		pts[0] = 4; pts[1] = 6;       //the +Z face
		cells->InsertNextCell(2, pts);
		pts[0] = 5; pts[1] = 7;
		cells->InsertNextCell(2, pts);
	}
	if (OutlineCursorWires)
	{
		pts[0] = 8; pts[1] = 9;         //the x cursor line
		cells->InsertNextCell(2, pts);
		pts[0] = 10; pts[1] = 11;       //the y cursor line
		cells->InsertNextCell(2, pts);
		pts[0] = 12; pts[1] = 13;       //the z cursor line
		cells->InsertNextCell(2, pts);
	}
	OutlinePolyData->Modified();
	if (OutlineProperty)
	{
		OutlineProperty->SetRepresentationToWireframe();
		SelectedOutlineProperty->SetRepresentationToWireframe();
	}
}

void misCorrectionTransformBox::AddDefaultTexture()
{
	vtkFloatArray * pTextureCoordinates = vtkFloatArray::New();
	pTextureCoordinates->SetNumberOfComponents(2);
	pTextureCoordinates->Allocate(2 * 24);
	for (int cellID = 0; cellID < 6; cellID++)
	{
		FillFaceTextureDefault(pTextureCoordinates, cellID);
	}
	m_HexPolyData->GetPointData()->SetTCoords(pTextureCoordinates);
	m_HexActor->SetTexture(m_DefaultCubeTexture);
	OutlineProperty->SetRepresentationToSurface();
	SelectedOutlineProperty->SetRepresentationToSurface();
	pTextureCoordinates->Delete();
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinate(misTextureEnum Text)
{
	misFloatPointsListTypdef returnCoordinate;
	switch (Text)
	{
	case Texture_A:
	{
		returnCoordinate = GetCoordinateA();
		break;
	}
	case Texture_P:
	{
		returnCoordinate = GetCoordinateP();
		break;
	}
	case Texture_S:
	{
		returnCoordinate = GetCoordinateS();
		break;
	}
	case Texture_I:
	{
		returnCoordinate = GetCoordinateI();
		break;
	}
	case Texture_R:
	{
		returnCoordinate = GetCoordinateR();
		break;
	}
	case Texture_L:
	{
		returnCoordinate = GetCoordinateL();
		break;
	}
	case Texture_Blank:
	{
		returnCoordinate = GetCoordinateBlank();
		break;
	}
	case none:
	{
		returnCoordinate = GetCoordinateStrip();
		break;
	}
	default:
		returnCoordinate = GetCoordinateStrip();

	}
	return returnCoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateA()
{
	misFloatPointsListTypdef Acoordinate;//=new misFloatPointsListTypdef;
	misFloatPointStrct APopint;
	APopint[0] = 0.0; APopint[1] = 1.0;
	Acoordinate.push_back(APopint);
	APopint[0] = 0.1; APopint[1] = 1.0;
	Acoordinate.push_back(APopint);
	APopint[0] = 0.1; APopint[1] = 0.0;
	Acoordinate.push_back(APopint);
	APopint[0] = 0.0; APopint[1] = 0.0;
	Acoordinate.push_back(APopint);
	return Acoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateP()
{
	misFloatPointsListTypdef Pcoordinate;
	misFloatPointStrct Ppoint;
	Ppoint[0] = 0.2; Ppoint[1] = 1.0;
	Pcoordinate.push_back(Ppoint);
	Ppoint[0] = 0.1; Ppoint[1] = 1.0;
	Pcoordinate.push_back(Ppoint);
	Ppoint[0] = 0.1; Ppoint[1] = 0.0;
	Pcoordinate.push_back(Ppoint);
	Ppoint[0] = 0.2; Ppoint[1] = 0.0;
	Pcoordinate.push_back(Ppoint);
	return Pcoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateS()
{
	misFloatPointsListTypdef Scoordinate;
	misFloatPointStrct Spoint;
	Spoint[0] = 0.3; Spoint[1] = 1.0;
	Scoordinate.push_back(Spoint);
	Spoint[0] = 0.2; Spoint[1] = 1.0;
	Scoordinate.push_back(Spoint);
	Spoint[0] = 0.2; Spoint[1] = 0.0;
	Scoordinate.push_back(Spoint);
	Spoint[0] = 0.3; Spoint[1] = 0.0;
	Scoordinate.push_back(Spoint);
	return Scoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateR()
{
	misFloatPointsListTypdef Rcoordinate;
	misFloatPointStrct Rpoint;
	Rpoint[0] = 0.5; Rpoint[1] = 0.0;
	Rcoordinate.push_back(Rpoint);
	Rpoint[0] = 0.5; Rpoint[1] = 1.0;
	Rcoordinate.push_back(Rpoint);
	Rpoint[0] = 0.4; Rpoint[1] = 1.0;
	Rcoordinate.push_back(Rpoint);
	Rpoint[0] = 0.4; Rpoint[1] = 0.0;
	Rcoordinate.push_back(Rpoint);
	return Rcoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateL()
{
	misFloatPointsListTypdef Lcoordinate;
	misFloatPointStrct Lpoint;
	Lpoint[0] = 0.5; Lpoint[1] = 0.0;
	Lcoordinate.push_back(Lpoint);
	Lpoint[0] = 0.5; Lpoint[1] = 1.0;
	Lcoordinate.push_back(Lpoint);
	Lpoint[0] = 0.6; Lpoint[1] = 1.0;
	Lcoordinate.push_back(Lpoint);
	Lpoint[0] = 0.6; Lpoint[1] = 0.0;
	Lcoordinate.push_back(Lpoint);
	return Lcoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateI()
{
	misFloatPointsListTypdef Icoordinate;
	misFloatPointStrct Ipoint;
	Ipoint[0] = 0.3; Ipoint[1] = 1.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.4; Ipoint[1] = 1.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.4; Ipoint[1] = 0.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.3; Ipoint[1] = 0.0;
	Icoordinate.push_back(Ipoint);
	return Icoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateBlank()
{
	misFloatPointsListTypdef Icoordinate;
	misFloatPointStrct Ipoint;
	Ipoint[0] = 0.6; Ipoint[1] = 1.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.7; Ipoint[1] = 1.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.7; Ipoint[1] = 0.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.6; Ipoint[1] = 0.0;
	Icoordinate.push_back(Ipoint);
	return Icoordinate;
}

misFloatPointsListTypdef misCorrectionTransformBox::GetCoordinateStrip()
{
	misFloatPointsListTypdef Icoordinate;
	misFloatPointStrct Ipoint;
	Ipoint[0] = 0.9; Ipoint[1] = 1.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 1.0; Ipoint[1] = 1.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 1.0; Ipoint[1] = 0.0;
	Icoordinate.push_back(Ipoint);
	Ipoint[0] = 0.9; Ipoint[1] = 0.0;
	Icoordinate.push_back(Ipoint);
	return Icoordinate;
}

#pragma endregion Get coordinate
misIntPointStrct misCorrectionTransformBox::GetFacePoints(int CellId)
{
	misIntPointStrct facePoint;
	switch (CellId)
	{
	case 0:
	{
		facePoint[0] = 0; facePoint[1] = 1; facePoint[2] = 2; facePoint[3] = 3;
		break;
	}
	case 1:
	{
		facePoint[0] = 4; facePoint[1] = 5; facePoint[2] = 6; facePoint[3] = 7;
		break;
	}
	case 2:
	{
		facePoint[0] = 8; facePoint[1] = 9; facePoint[2] = 10; facePoint[3] = 11;
		break;
	}
	case 3:
	{
		facePoint[0] = 12;  facePoint[1] = 13; facePoint[2] = 14; facePoint[3] = 15;
		break;
	}
	case 4:
	{
		facePoint[0] = 16;  facePoint[1] = 17; facePoint[2] = 18; facePoint[3] = 19;
		break;
	}
	case 5:
	{
		facePoint[0] = 20;  facePoint[1] = 21; facePoint[2] = 22; facePoint[3] = 23;
		break;
	}
	}
	return facePoint;
}

void misCorrectionTransformBox::AddTexture(misIntPointStrct pointstr, misFloatPointsListTypdef coordinateLst)
{
	float coordinates[2];
	misFloatPointStrct  coordinateStr;
	misFloatPointsListTypdef::iterator coordinate_iter;
	int i = 0;
	for (coordinate_iter = coordinateLst.begin(); coordinate_iter != coordinateLst.end(); coordinate_iter++)
	{
		coordinateStr = (*coordinate_iter);
		int pointId = pointstr[i];
		coordinates[0] = coordinateStr[0]; coordinates[1] = coordinateStr[1];
		m_pTextureCoordinates->SetTuple(pointId, coordinates);
		i++;
	}
}

misTextureEnum misCorrectionTransformBox::GetOppositeTexture(misTextureEnum text)
{
	misTextureEnum returnText;
	switch (text)
	{
	case Texture_A:
	{
		returnText = Texture_P;
		break;
	}
	case Texture_P:
	{
		returnText = Texture_A;
		break;
	}
	case Texture_S:
	{
		returnText = Texture_I;
		break;
	}
	case Texture_I:
	{
		returnText = Texture_S;
		break;
	}
	case Texture_R:
	{
		returnText = Texture_L;
		break;
	}
	case Texture_L:
	{
		returnText = Texture_R;
		break;
	}
	}
	return returnText;

}

int misCorrectionTransformBox::GetOppositeCellId(int CellId)
{
	int returnId;
	switch (CellId)
	{
	case 0:
	{
		returnId = 1;
		break;
	}

	case 1:
	{
		returnId = 0;
		break;
	}

	case 2:
	{
		returnId = 3;
		break;
	}

	case 3:
	{
		returnId = 2;
		break;
	}

	case 4:
	{
		returnId = 5;
		break;
	}

	case 5:
	{
		returnId = 4;
		break;
	}
	}

	return returnId;
}

void misCorrectionTransformBox::SetBounding(double bounds[6])
{
	for (int i = 0; i < 6; i++)
	{
		m_bounds[i] = bounds[i];
	}
	PlaceWidget(bounds);
}

double * misCorrectionTransformBox::GetFaceNormal(int cellId)
{
	double* Rvector = new double[3];
	if ((cellId >= 0) && (cellId < 6))
	{
		switch (cellId)
		{
		case 0:
		{
			Rvector[0] = -1;	Rvector[1] = 0; Rvector[2] = 0;
			break;
		}
		case 1:
		{
			Rvector[0] = 1;	Rvector[1] = 0; Rvector[2] = 0;
			break;
		}
		case 2:
		{
			Rvector[0] = 0;	Rvector[1] = 0; Rvector[2] = 1;
			break;
		}
		case 3:
		{
			Rvector[0] = 0;	Rvector[1] = 0; Rvector[2] = -1;
			break;
		}
		case 4:
		{
			Rvector[0] = 0;	Rvector[1] = 1; Rvector[2] = 0;
			break;
		}
		case 5:
		{
			Rvector[0] = 0;	Rvector[1] = -1; Rvector[2] = 0;
			break;
		}
		}
		return Rvector;
	}
	return 0;
}
void misCorrectionTransformBox::SetVolume(vtkProp3D * volume)
{
	m_volume = volume;
}

void misCorrectionTransformBox::SetBlankTextureToAllFaces()
{
	vtkSmartPointer<vtkFloatArray>  pTextureCoordinates = ExtractCubeTextureCoordinate();
	for (int cellID = 0; cellID < 6; cellID++)
		FillFaceTexture(pTextureCoordinates, cellID, Texture_Blank);
	m_HexPolyData->GetPointData()->SetTCoords(pTextureCoordinates);
	m_HexActor->SetTexture(m_DefaultCubeTexture);
	OutlineProperty->SetRepresentationToSurface();
	SelectedOutlineProperty->SetRepresentationToSurface();
}

void misCorrectionTransformBox::ReadDefalutCubeTexture()
{
	vtkPNGReader *pReaeder = vtkPNGReader::New();
	char dirFile[100];
	GetCurrentDirectoryA(99, dirFile);
	string  cubeCoverPath;
	cubeCoverPath.append(dirFile);
	cubeCoverPath.append("\\Resources\\CubeCover2.png");
	pReaeder->SetFileName((char*)cubeCoverPath.c_str());
	pReaeder->Update();
	vtkImageData*  pImagePng = pReaeder->GetOutput();
	int num = pImagePng->GetNumberOfScalarComponents();
	m_DefaultCubeTexture = vtkTexture::New();
	m_DefaultCubeTexture->SetInputData(pReaeder->GetOutput());
	m_DefaultCubeTexture->Update();
}

void misCorrectionTransformBox::Reset()
{
	m_lastCellId = -1;
	m_FaceSelectCounter = 0;
	m_SecondFaceIsSelected = false;
	SetBlankTextureToAllFaces();
}

int  misCorrectionTransformBox::GetDefalutCellID(misTextureEnum textureName)
{
	int cellID;
	switch (textureName)
	{
	case Texture_R:
		cellID = 0;
		break;

	case Texture_L:
		cellID = 1;
		break;

	case Texture_I:
		cellID = 2;
		break;

	case Texture_S:
		cellID = 3;
		break;

	case Texture_A:
		cellID = 4;
		break;

	case Texture_P:
		cellID = 5;
		break;

	default:
		cellID = -1;
	}

	return cellID;
}

misTextureEnum misCorrectionTransformBox::GetDefaultTextureName(int cellID)
{
	misTextureEnum textureName;
	switch (cellID)
	{
	case 0:
		textureName = Texture_R;
		break;

	case 1:
		textureName = Texture_L;
		break;

	case 2:
		textureName = Texture_I;
		break;

	case 3:
		textureName = Texture_S;
		break;

	case 4:
		textureName = Texture_A;
		break;

	case 5:
		textureName = Texture_P;
		break;

	default:
		textureName = none;

	}
	return textureName;
}

int misCorrectionTransformBox::GetLastSelectedFaceID()
{
	return m_lastCellId;
}

void misCorrectionTransformBox::FillDefaultFaceInformation()
{
	m_FacesInformationDefault.clear();
	misTextureEnum  textureName;
	misFaceInformation faceInformation;
	for (int i = 0; i < 6; i++)
	{
		textureName = GetDefaultTextureName(i);

		faceInformation.cellID = i;
		faceInformation.textureName = textureName;

		m_FacesInformationDefault.push_back(faceInformation);
	}
}

void misCorrectionTransformBox::UpdateFacesTexture(int cellId)
{
	auto pTextureCoordinates = ExtractCubeTextureCoordinate();
	misFaceInformation faceInformation;
	for (int i = 0; i < m_FacesInformationApplied.size(); i++)
	{
		faceInformation = m_FacesInformationApplied[i];
		// dell id is equal to index:i
		if (Texture_Blank == faceInformation.textureName)
		{
			if (cellId == i)
				FillFaceTexture(pTextureCoordinates, i, Texture_Strip);
			else
				FillFaceTexture(pTextureCoordinates, i, Texture_Blank);
		}
		else
			FillFaceTexture(pTextureCoordinates, i, faceInformation.textureName);
	}

	m_HexPolyData->GetPointData()->SetTCoords(pTextureCoordinates);
	m_HexActor->SetTexture(m_DefaultCubeTexture);
	OutlineProperty->SetRepresentationToSurface();
	SelectedOutlineProperty->SetRepresentationToSurface();
	m_lastCellId = cellId;
	m_Interactor->InvokeEvent(misSelectedFaceEvent);
}

void misCorrectionTransformBox::UpdateFacesTexture()
{
	UpdateFacesTexture(-1);
}

void misCorrectionTransformBox::SetAppliedFaceInformation(faceInformationListTypdef facesInformationApplied)
{
	m_FacesInformationApplied = facesInformationApplied;
	UpdateFacesTexture();
}

void misCorrectionTransformBox::UseDefaultFacesInformation()
{
	m_FacesInformationApplied = m_FacesInformationDefault;
}

#pragma region Fill Texture in the texture coordinate

void misCorrectionTransformBox::FillFaceTextureDefault(vtkFloatArray * pTextureCoordinates, int cellID)
{
	misFloatPointsListTypdef   allCoordinate;
	misFloatPointStrct         coordinates;
	float fCoordinates[2];
	misIntPointStrct facePoints = GetFacePoints(cellID);
	misTextureEnum textureName = GetDefaultTextureName(cellID);
	allCoordinate = GetCoordinate(textureName);
	coordinates = allCoordinate[0];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[0], fCoordinates);
	coordinates = allCoordinate[1];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[1], fCoordinates);
	coordinates = allCoordinate[2];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[2], fCoordinates);
	coordinates = allCoordinate[3];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[3], fCoordinates);
};

void misCorrectionTransformBox::FillFaceTexture(vtkFloatArray * pTextureCoordinates, int cellID, misTextureEnum textureName)
{
	misFloatPointsListTypdef   allCoordinate;
	misFloatPointStrct         coordinates;
	float fCoordinates[2];
	misIntPointStrct facePoints = GetFacePoints(cellID);
	allCoordinate = GetCoordinate(textureName);
	coordinates = allCoordinate[0];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[0], fCoordinates);
	coordinates = allCoordinate[1];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[1], fCoordinates);
	coordinates = allCoordinate[2];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[2], fCoordinates);
	coordinates = allCoordinate[3];
	fCoordinates[0] = coordinates[0]; fCoordinates[1] = coordinates[1];
	pTextureCoordinates->SetTuple(facePoints[3], fCoordinates);
};

void misCorrectionTransformBox::EnabledOn()
{
	if (m_Enabled)
		return;
	m_Enabled = true;
	vtkRenderWindowInteractor *interactor = m_Interactor;
	interactor->AddObserver(vtkCommand::MouseMoveEvent, m_CallBack, 1.0);
	interactor->AddObserver(vtkCommand::LeftButtonPressEvent, m_CallBack, 1.0);
	interactor->AddObserver(vtkCommand::RightButtonPressEvent, m_CallBack, 1.0);
	m_Renderer->AddActor(m_HexActor);
	m_Renderer->AddActor(HexOutline);
	m_HexActor->SetProperty(OutlineProperty);
	HexOutline->SetProperty(OutlineProperty);
	m_Renderer->AddActor(HexFace);
	HexFace->SetProperty(FaceProperty);
	for (int j = 0; j < m_Handles.size(); j++)
	{
		m_Renderer->AddActor(m_Handles[j]);
		m_Handles[j]->SetProperty(HandleProperty);
	}
	m_Interactor->InvokeEvent(vtkCommand::EnableEvent, NULL);
}
void misCorrectionTransformBox::EnabledOff()
{
	if (!m_Enabled) //already disabled, just return
		return;

	m_Enabled = false;
	m_Interactor->RemoveObserver(m_CallBack);
	m_Renderer->RemoveActor(m_HexActor);
	m_Renderer->RemoveActor(HexOutline);
	m_Renderer->RemoveActor(HexFace);
	for (int i = 0; i < m_Handles.size(); i++)
		m_Renderer->RemoveActor(m_Handles[i]);
	m_SelectedFaceActor = NULL;
	m_Interactor->InvokeEvent(vtkCommand::DisableEvent, NULL);

}
void misCorrectionTransformBox::SetInteractor(vtkRenderWindowInteractor* interactor)
{
	m_Renderer = interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
	m_Interactor = interactor;
	m_Interactor->AddObserver(vtkCommand::LeftButtonPressEvent, m_CallBack);
	m_Interactor->AddObserver(vtkCommand::MouseMoveEvent, m_CallBack);
}

vtkSmartPointer<vtkFloatArray> misCorrectionTransformBox::ExtractCubeTextureCoordinate()
{
	vtkSmartPointer<vtkFloatArray> pTextureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
	pTextureCoordinates->SetNumberOfComponents(2);
	pTextureCoordinates->Allocate(2 * 24);
	return pTextureCoordinates;
}
void misCorrectionTransformBox::On()
{
	EnabledOn();
}

void misCorrectionTransformBox::Off()
{
	EnabledOff();
}

void misCorrectionTransformBox::InitilizeTransformCorrectionBox(vtkRenderWindowInteractor* interactor, vtkProp3D* VolumeRep,
	const misROI& roi)
{
	AddActorToBoxWidget(interactor, VolumeRep, roi);
	EnabledOn();
	UseDefaultFacesInformation();
	UpdateFacesTexture();
}
void misCorrectionTransformBox::AddActorToBoxWidget(vtkRenderWindowInteractor* interactor, vtkProp3D* VolumeRep,
	const misROI& roi)
{
	SetInteractor(interactor);
	UpdateOrientationCorrectionBox(VolumeRep, roi);
	On();
}
void misCorrectionTransformBox::UpdateOrientationCorrectionBox(vtkProp3D* VolumeRep, misROI roi)
{
	double bounds[6];
	bounds[0] = roi[0];
	bounds[1] = roi[1];
	bounds[2] = roi[2];
	bounds[3] = roi[3];
	bounds[4] = roi[4];
	bounds[5] = roi[5];
	SetBounding(bounds);
	SetVolume(VolumeRep);
}

bool misCorrectionTransformBox::CheckNewFaceSelectedValidity(void)
{
	int lastSelectFaceID = GetLastSelectedFaceID();

	for (int i = 0; i < m_FacesInformationApplied.size(); i++)
	{
		if (lastSelectFaceID == m_FacesInformationApplied[i].cellID)
		{
			if (Texture_Blank != m_FacesInformationApplied[i].textureName)
			{
				return false;
			}
		}
	}
	return true;
}

void misCorrectionTransformBox::UpdateBoxWidgetFacesInformation(misFaceInformation newFaceInformation)
{
	if (-1 == newFaceInformation.cellID)
		return;
	m_FacesInformationApplied[newFaceInformation.cellID] = newFaceInformation;
	int oppCellID = GetOppositeCellId(newFaceInformation.cellID);
	misTextureEnum oppTexName = GetOppositeTexture(newFaceInformation.textureName);
	misFaceInformation oppFaceInformation;
	oppFaceInformation.cellID = oppCellID;
	oppFaceInformation.textureName = oppTexName;
	m_FacesInformationApplied[oppCellID] = oppFaceInformation;
	// apply to he box widget
	SetAppliedFaceInformation(m_FacesInformationApplied);
}

void misCorrectionTransformBox::ResetTexture()
{
	m_FaceInformation2nd.Reset();
	m_FaceInformation1st.Reset();
	misFaceInformation defaultTexture;
	defaultTexture.textureName = Texture_Blank;
	m_FacesInformationApplied.clear();

	for (int i = 0; i < 6; i++)
	{
		defaultTexture.cellID = i;
		m_FacesInformationApplied.push_back(defaultTexture);
	}
}

misFaceInformation misCorrectionTransformBox::GetFaceInformation1st() const
{
	return m_FaceInformation1st;
}

misFaceInformation misCorrectionTransformBox::GetFaceInformation2nd() const
{
	return m_FaceInformation2nd;
}

void misCorrectionTransformBox::UpdateFaceSelection(misTextureEnum appliedTexture)
{
	if (-1 == m_FaceInformation1st.cellID)
	{
		m_FaceInformation1st.cellID = GetLastSelectedFaceID();
		m_FaceInformation1st.textureName = appliedTexture;
		UpdateBoxWidgetFacesInformation(m_FaceInformation1st);
	}
	// the second in not filled yet
	else if (-1 == m_FaceInformation2nd.cellID)
	{
		int newCellID = GetLastSelectedFaceID();

		if (newCellID != m_FaceInformation1st.cellID)
		{
			int preOpoface = GetOppositeCellId(m_FaceInformation1st.cellID);
			if (preOpoface != newCellID)
			{
				m_FaceInformation2nd.cellID = GetLastSelectedFaceID();
				m_FaceInformation2nd.textureName = appliedTexture;
				UpdateBoxWidgetFacesInformation(m_FaceInformation2nd);
				m_SecondFaceIsSelected = true;
			}
		}
	}
}

vtkSmartPointer<vtkMatrix4x4> misCorrectionTransformBox::CalculatePrimeryMatrix(void)
{
	vtkSmartPointer<vtkMatrix4x4> primaryMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
	primaryMatrix->Identity();
	int defaultCellID1;
	int defaultCellID2;
	defaultCellID1 = GetDefalutCellID(m_FaceInformation1st.textureName);
	defaultCellID2 = GetDefalutCellID(m_FaceInformation2nd.textureName);
	// Delete pointers afterwards.
	double* faceNormal0 = GetFaceNormal(defaultCellID1);
	double* faceNormal1 = GetFaceNormal(defaultCellID2);
	double* faceNormal2 = misMathUtils::GetCrossProduct(faceNormal0, faceNormal1);
	misMathUtils::FillElemetInMatrix(primaryMatrix, faceNormal0, 0);
	misMathUtils::FillElemetInMatrix(primaryMatrix, faceNormal1, 1);
	misMathUtils::FillElemetInMatrix(primaryMatrix, faceNormal2, 2);
	if (faceNormal0)
		delete faceNormal0;
	if (faceNormal1)
		delete faceNormal1;
	if (faceNormal2)
		delete faceNormal2;
	return primaryMatrix;
}
vtkSmartPointer<vtkMatrix4x4> misCorrectionTransformBox::CalculatedSecondryMatrix(void)
{
	vtkSmartPointer<vtkMatrix4x4> secMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
	secMatrix->Identity();
	double* faceNormal0 = GetFaceNormal(m_FaceInformation1st.cellID);
	double* faceNormal1 = GetFaceNormal(m_FaceInformation2nd.cellID);
	double * faceNormal2 = misMathUtils::GetCrossProduct(faceNormal0, faceNormal1);
	misMathUtils::FillElemetInMatrix(secMatrix, faceNormal0, 0);
	misMathUtils::FillElemetInMatrix(secMatrix, faceNormal1, 1);
	misMathUtils::FillElemetInMatrix(secMatrix, faceNormal2, 2);
	if (faceNormal0)
		delete faceNormal0;
	if (faceNormal1)
		delete faceNormal1;
	if (faceNormal2)
		delete faceNormal2;
	return secMatrix;
}

bool misCorrectionTransformBox::GetSecondFaceIsSelected() const
{
	return m_SecondFaceIsSelected;
}

faceInformationListTypdef misCorrectionTransformBox::GetFacesInformationApplied() const
{
	return m_FacesInformationApplied;
}

void misCorrectionTransformBox::SetFacesInformationApplied(faceInformationListTypdef val)
{
	m_FacesInformationApplied = val;
}
