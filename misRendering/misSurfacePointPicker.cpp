#include "stdafx.h"
#include "misSurfacePointPicker.h"

#include "misMathUtils.h"

using namespace itk;
vtkStandardNewMacro(misSurfacePointPicker);

misSurfacePointPicker::misSurfacePointPicker()
{
  this->PointId = -1;
}

double misSurfacePointPicker::IntersectWithLine(double p1[3], double p2[3], double tol, 
                                        vtkAssemblyPath *path, vtkProp3D *p, 
                                        vtkAbstractMapper3D *m)
{
 
  vtkIdType numFace;

  vtkIdType ptCell, minptCell;
  int i;
  double ray[3], rayFactor, tMin,  t;
  vtkDataSet *input;
  vtkMapper *mapper;
  vtkAbstractVolumeMapper *volumeMapper;

  // Get the underlying dataset
  //
  if ( (mapper=vtkMapper::SafeDownCast(m)) != NULL )
    {
    input = mapper->GetInput();
    }
  else if ( (volumeMapper=vtkAbstractVolumeMapper::SafeDownCast(m)) != NULL )
    {
    input = volumeMapper->GetDataSetInput();
    }
  else
    {
    return 2.0;
    }

  if ( (numFace = input->GetNumberOfCells()) < 1 )
    {
    return 2.0;
    }

  //   Determine appropriate info
  //
  for (i=0; i<3; i++)
    {
    ray[i] = p2[i] - p1[i];
    }
  if (( rayFactor = vtkMath::Dot(ray,ray)) == 0.0 ) 
    {
    vtkErrorMacro("Cannot process points");
    return 2.0;
    }

   
   
  vtkIdList* idList=vtkIdList::New();
	double  RetPos[3];
	
	tMin=this->GlobalTMin;	
	if (numFace<100)
		return VTK_DOUBLE_MAX;

  for (minptCell=(-1),tMin=VTK_DOUBLE_MAX,ptCell=0; ptCell<numFace; ptCell++) 
    {
		idList->Reset();
		input->GetCellPoints(ptCell,idList);
		double  v1[3],v2[3],v3[3];
		input->GetPoint(idList->GetId(0),v1);
 		input->GetPoint(idList->GetId(1),v2);
		input->GetPoint(idList->GetId(2),v3);
    
		/*-------------------------*/
		//if ((tMin!=this->GlobalTMin)&&(t>tMin))
		//	continue;
		int ret=this->rayIntersectsTriangle(p1,p2,v1,v2,v3,RetPos);
		t = (ray[0]*(RetPos[0]-p1[0]) + ray[1]*(RetPos[1]-p1[1]) + ray[2]*(RetPos[2]-p1[2])) /rayFactor;
		if (ret==1)
		{
			  if ( t < tMin ) 
			  {
				  tMin=t;	
				  minptCell=idList->GetId(0);
				  this->PickedPositions->InsertNextPoint(RetPos);
   			  }
		 }
  }
 
  //  Now compare this against other actors.
  //
  /*if ( tMin < this->GlobalTMin ) 
    {
		this->MarkPicked(path, p, m, tMin, RetPos);
		this->PointId = minptCell;
		vtkDebugMacro("Picked point id= " << minptCell);
	}*/
	 
  return tMin;
}

void misSurfacePointPicker::Initialize()
{
  this->PointId = (-1);
  this->vtkPicker::Initialize();
}

void misSurfacePointPicker::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Point Id: " << this->PointId << "\n";
}
 int misSurfacePointPicker::Pick(double selectionX, double selectionY, double selectionZ,
                    vtkRenderer *renderer)
{
  int i;
  vtkProp *prop;
  vtkCamera *camera;
  vtkAbstractMapper3D *mapper = NULL;
  double p1World[4], p2World[4], p1Mapper[4], p2Mapper[4];
  int picked=0;
  int *winSize;
  double x, y, t;
  double *viewport;
  double cameraPos[4], cameraFP[4];
  double *displayCoords, *worldCoords;
  double *clipRange;
  double ray[3], rayLength;
  int pickable;
  int LODId;
  double windowLowerLeft[4], windowUpperRight[4];
  double bounds[6], tol;
  double tF, tB;
  double hitPosition[3];
  double cameraDOP[3];
  
  //  Initialize picking process
  this->Initialize();
  this->Renderer = renderer;
  this->SelectionPoint[0] = selectionX;
  this->SelectionPoint[1] = selectionY;
  this->SelectionPoint[2] = selectionZ;

  // Invoke start pick method if defined
  this->InvokeEvent(vtkCommand::StartPickEvent,NULL);

  if ( renderer == NULL )
    {
    vtkErrorMacro(<<"Must specify renderer!");
    return 0;
    }

  // Get camera focal point and position. Convert to display (screen) 
  // coordinates. We need a depth value for z-buffer.
  //
  camera = renderer->GetActiveCamera();
  camera->GetPosition((double *)cameraPos); cameraPos[3] = 1.0;
  camera->GetFocalPoint((double *)cameraFP); cameraFP[3] = 1.0;

  renderer->SetWorldPoint(cameraFP[0],cameraFP[1],cameraFP[2],cameraFP[3]);
  renderer->WorldToDisplay();
  displayCoords = renderer->GetDisplayPoint();
  selectionZ = displayCoords[2];

  // Convert the selection point into world coordinates.
  //
  renderer->SetDisplayPoint(selectionX, selectionY, selectionZ);
  renderer->DisplayToWorld();
  worldCoords = renderer->GetWorldPoint();
  if ( worldCoords[3] == 0.0 )
    {
    vtkErrorMacro(<<"Bad homogeneous coordinates");
    return 0;
    }
  for (i=0; i < 3; i++) 
    {
    this->PickPosition[i] = worldCoords[i] / worldCoords[3];
    }
  
  //  Compute the ray endpoints.  The ray is along the line running from
  //  the camera position to the selection point, starting where this line
  //  intersects the front clipping plane, and terminating where this
  //  line intersects the back clipping plane.
  for (i=0; i<3; i++)
    {
    ray[i] = this->PickPosition[i] - cameraPos[i];
    }
  for (i=0; i<3; i++)
    {
    cameraDOP[i] = cameraFP[i] - cameraPos[i];
    }

  vtkMath::Normalize(cameraDOP);

  if (( rayLength = vtkMath::Dot(cameraDOP,ray)) == 0.0 ) 
    {
    vtkWarningMacro("Cannot process points");
    return 0;
    } 

  clipRange = camera->GetClippingRange();

  if ( camera->GetParallelProjection() )
    {
    tF = clipRange[0] - rayLength;
    tB = clipRange[1] - rayLength;
    for (i=0; i<3; i++) 
      {
      p1World[i] = this->PickPosition[i] + tF*cameraDOP[i];
      p2World[i] = this->PickPosition[i] + tB*cameraDOP[i];
      }
    }
  else
    {
    tF = clipRange[0] / rayLength;
    tB = clipRange[1] / rayLength;
    for (i=0; i<3; i++) 
      {
      p1World[i] = cameraPos[i] + tF*ray[i];
      p2World[i] = cameraPos[i] + tB*ray[i];
      }
    }
  p1World[3] = p2World[3] = 1.0;

  // Compute the tolerance in world coordinates.  Do this by
  // determining the world coordinates of the diagonal points of the
  // window, computing the width of the window in world coordinates, and 
  // multiplying by the tolerance.
  //
  viewport = renderer->GetViewport();
  winSize = renderer->GetRenderWindow()->GetSize();
  x = winSize[0] * viewport[0];
  y = winSize[1] * viewport[1];
  renderer->SetDisplayPoint(x, y, selectionZ);
  renderer->DisplayToWorld();
  renderer->GetWorldPoint(windowLowerLeft);

  x = winSize[0] * viewport[2];
  y = winSize[1] * viewport[3];
  renderer->SetDisplayPoint(x, y, selectionZ);
  renderer->DisplayToWorld();
  renderer->GetWorldPoint(windowUpperRight);

  for (tol=0.0,i=0; i<3; i++) 
    {
    tol += (windowUpperRight[i] - windowLowerLeft[i]) *
      (windowUpperRight[i] - windowLowerLeft[i]);
    }
  
  tol = sqrt (tol) * this->Tolerance;

  //  Loop over all props.  Transform ray (defined from position of
  //  camera to selection point) into coordinates of mapper (not
  //  transformed to actors coordinates!  Reduces overall computation!!!).
  //  Note that only vtkProp3D's can be picked by vtkPicker.
  //
  vtkPropCollection *props;
  vtkProp *propCandidate;
  if ( this->PickFromList ) 
    {
    props = this->GetPickList();
    }
  else 
    {
    props = renderer->GetViewProps();
    }

  vtkActor *actor;
  vtkLODProp3D *prop3D;
  vtkVolume *volume;
  vtkImageActor *imageActor = 0;
  vtkAssemblyPath *path;
  vtkProperty *tempProperty;
  this->Transform->PostMultiply();
  vtkCollectionSimpleIterator pit;
  double scale[3];
  for ( props->InitTraversal(pit); (prop=props->GetNextProp(pit)); )
    {
    for ( prop->InitPathTraversal(); (path=prop->GetNextPath()); )
      {
      pickable = 0;
      actor = NULL;
      propCandidate = path->GetLastNode()->GetViewProp();
      if ( propCandidate->GetPickable() && propCandidate->GetVisibility() )
        {
        pickable = 1;
        if ( (actor=vtkActor::SafeDownCast(propCandidate)) != NULL )
          {
          mapper = actor->GetMapper();
          if ( actor->GetProperty()->GetOpacity() <= 0.0 )
            {
            pickable = 0;
            }
          }
        else if ( (prop3D=vtkLODProp3D::SafeDownCast(propCandidate)) != NULL )
          {
          LODId = prop3D->GetPickLODID();
          mapper = prop3D->GetLODMapper(LODId);

          // if the mapper is a vtkMapper (as opposed to a vtkVolumeMapper), 
          // then check the transparency to see if the object is pickable
          if ( vtkMapper::SafeDownCast(mapper) != NULL)
            {
            prop3D->GetLODProperty(LODId, &tempProperty);
            if ( tempProperty->GetOpacity() <= 0.0 )
              {
              pickable = 0;
              }
            }
          }
        else if ( (volume=vtkVolume::SafeDownCast(propCandidate)) != NULL )
          {
          mapper = volume->GetMapper();
          }
        else if ( (imageActor=vtkImageActor::SafeDownCast(propCandidate)) )
          {
          mapper = 0;
          }
        else 
          {
          pickable = 0; //only vtkProp3D's (actors and volumes) can be picked
          }
        }

      //  If actor can be picked, get its composite matrix, invert it, and
      //  use the inverted matrix to transform the ray points into mapper
      //  coordinates. 
      if ( pickable  &&  mapper != NULL )
        {
        vtkMatrix4x4 *LastMatrix = path->GetLastNode()->GetMatrix();
        if (LastMatrix == NULL)
          {
          vtkErrorMacro (<< "Pick: Null matrix.");
          return 0;
          }
        this->Transform->SetMatrix(LastMatrix);
        this->Transform->Push();
        this->Transform->Inverse();
        this->Transform->GetScale(scale); //need to scale the tolerance

        this->Transform->TransformPoint(p1World,p1Mapper);
        this->Transform->TransformPoint(p2World,p2Mapper);

        for (i=0; i<3; i++) 
          {
          ray[i] = p2Mapper[i] - p1Mapper[i];
          }

        this->Transform->Pop();

        //  Have the ray endpoints in mapper space, now need to compare this
        //  with the mapper bounds to see whether intersection is possible.
        //
        //  Get the bounding box of the modeller.  Note that the tolerance is
        //  added to the bounding box to make sure things on the edge of the
        //  bounding box are picked correctly.
        mapper->GetBounds(bounds);
        bounds[0] -= tol; bounds[1] += tol; 
        bounds[2] -= tol; bounds[3] += tol; 
        bounds[4] -= tol; bounds[5] += tol; 
        if ( vtkBox::IntersectBox(bounds, (double *)p1Mapper, 
                                  ray, hitPosition, t) )
          {
          t = this->IntersectWithLine((double *)p1Mapper, (double *)p2Mapper, 
                                      tol*0.333*(scale[0]+scale[1]+scale[2]), path, 
                                      (vtkProp3D *)propCandidate, mapper);
          if ( t < VTK_DOUBLE_MAX )
            {
            picked = 1;
            if ( ! this->Prop3Ds->IsItemPresent(prop) )
              {
              this->Prop3Ds->AddItem((vtkProp3D *)prop);
              }
     /*       this->PickedPositions->InsertNextPoint
              ((1.0 - t)*p1World[0] + t*p2World[0],
               (1.0 - t)*p1World[1] + t*p2World[1],
               (1.0 - t)*p1World[2] + t*p2World[2]);*/

            // backwards compatibility: also add to this->Actors
            if (actor)
              {
              this->Actors->AddItem(actor);
              }
            }
          }
        }
      else if ( pickable && imageActor )
        { // special case for imageActor, which has no mapper
        vtkMatrix4x4 *LastMatrix = path->GetLastNode()->GetMatrix();
        if (LastMatrix == NULL)
          {
          vtkErrorMacro (<< "Pick: Null matrix.");
          return 0;
          }
        this->Transform->SetMatrix(LastMatrix);
        this->Transform->Push();
        this->Transform->Inverse();

        this->Transform->TransformPoint(p1World,p1Mapper);
        this->Transform->TransformPoint(p2World,p2Mapper);

        this->Transform->Pop();

        //  Have the ray endpoints in data space, now need to compare this
        //  with the displayed image bounds.
        imageActor->GetDisplayBounds(bounds);

        t = VTK_DOUBLE_MAX;

        for (i = 0; i < 3; i++)
          {
          if (bounds[2*i] == bounds[2*i+1] && p2Mapper[i] != p1Mapper[i])
            {
            t = (p2World[i] - bounds[2*i])/(p2Mapper[i] - p1Mapper[i]);
            break;
            }
          }

        if (t < VTK_DOUBLE_MAX)
          {
          hitPosition[0] = (1.0 - t)*p1Mapper[0] + t*p2Mapper[0];
          hitPosition[1] = (1.0 - t)*p1Mapper[1] + t*p2Mapper[1];
          hitPosition[2] = (1.0 - t)*p1Mapper[2] + t*p2Mapper[2];
          if ((bounds[0] == bounds[1] || (hitPosition[0] >= bounds[0]-tol &&
                                          hitPosition[0] <= bounds[1]+tol)) &&
              (bounds[2] == bounds[3] || (hitPosition[1] >= bounds[2]-tol &&
                                          hitPosition[1] <= bounds[3]+tol)) &&
              (bounds[4] == bounds[5] || (hitPosition[2] >= bounds[4]-tol &&
                                          hitPosition[2] <= bounds[5]+tol)))
            {
            picked = 1;

            // the following code is handled in MarkPicked for other Prop3Ds
            this->Mapper = mapper; // mapper is null
            this->DataSet = imageActor->GetInput();
            this->MapperPosition[0] = hitPosition[0];
            this->MapperPosition[1] = hitPosition[1];
            this->MapperPosition[2] = hitPosition[2];
            this->Transform->TransformPoint(hitPosition,this->PickPosition);
            imageActor->Pick();
            this->InvokeEvent(vtkCommand::PickEvent,NULL);

            this->Prop3Ds->AddItem(imageActor);
            /*this->PickedPositions->InsertNextPoint
              ((1.0 - t)*p1World[0] + t*p2World[0],
               (1.0 - t)*p1World[1] + t*p2World[1],
               (1.0 - t)*p1World[2] + t*p2World[2]);*/
            }
          }
        }//if visible and pickable not transparent and has mapper
      }//for all parts
    }//for all actors

  // Invoke end pick method if defined
  this->InvokeEvent(vtkCommand::EndPickEvent,NULL);

  return picked;
}


misSurfacePointPicker::~misSurfacePointPicker(void)
{
}
 

int misSurfacePointPicker::rayIntersectsTriangle(double *p1, double *p2, 
	double *v0, double *v1, double *v2,double* RetPoint)
{
	//Ray R, Triangle T, Point* I 
	typedef Vector<double,3>  VectorType;


	VectorType  Point0,Point1;
	Point0[0]=p1[0];Point0[1]=p1[1];Point0[2]=p1[2];
	Point1[0]=p2[0];Point1[1]=p2[1];Point1[2]=p2[2];

	misRay  ray(Point0,Point1);


	VectorType    u, v, n;             // triangle vectors
	VectorType    dir, w0, w;          // ray vectors
	float     r, a, b;             // params to calc ray-plane intersect

	VectorType  Tv0,Tv1,Tv2;
	VectorType  RetPointVector;

	Tv0[0]=v0[0];Tv0[1]=v0[1];Tv0[2]=v0[2];

	Tv1[0]=v1[0];Tv1[1]=v1[1];Tv1[2]=v1[2];

	Tv2[0]=v2[0];Tv2[1]=v2[1];Tv2[2]=v2[2];


	// get triangle edge vectors and plane normal
	u = Tv1 - Tv0;
	v = Tv2 - Tv0;
	n = CrossProduct( u , v);             // cross product
	if ((n[0] == 0)&&(n[1]==0)&&(n[2]==0))            // triangle is degenerate
		return -1;                 // do not deal with this case

	dir = ray.m_p1 - ray.m_p0;             // ray direction vector
	w0 = ray.m_p0 - Tv0;
	a = static_cast<float> (-n * w0);
	b = static_cast<float> (n * dir);

	if (fabs(b) < 0.000001) {     // ray is parallel to triangle plane
		if (a == 0)                // ray lies in triangle plane
			return 2;
		else return 0;             // ray disjoint from plane
	}

	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0)                   // ray goes away from triangle
		return 0;                  // => no intersect
	// for a segment, also test if (r > 1.0) => no intersect

	RetPointVector = ray.m_p0 +  dir*r;           // intersect point of ray and plane

	// is I inside T?
	float    uu, uv, vv, wu, wv, D;
	uu = static_cast<float>(u * u);
	uv = static_cast<float>(u * v);
	vv = static_cast<float>(v * v);
	w = RetPointVector - Tv0;
	wu =  static_cast<float>(w * u);
	wv = static_cast<float>(w * v);
	D = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / D;

	RetPoint[0]=RetPointVector[0];RetPoint[1]=RetPointVector[1];RetPoint[2]=RetPointVector[2];

	if (s < 0.0 || s > 1.0)        // I is outside T
		return 0;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
		return 0;

	return 1;                      // I is in T

	//double e1[3],e2[3],h[3],s[3],q[3];
	//double a,f,u,v;
	//
	//vector(e1,v1,v0);
	//vector(e2,v2,v0);
	//vtkMath::Cross(h,d,e2);
	//a = vtkMath::Dot(e1,h);
	//
	//if (a > -0.00001 && a < 0.00001)
	//	return(false);
	//
	//f = 1/a;
	//vector(s,p,v0);
	//u = f * (vtkMath::Dot(s,h));
	//
	//if (u < 0.0 || u > 1.0)
	//	return(false);
	//
	//vtkMath::Cross(q,s,e1);
	//v = f * vtkMath::Dot(d,q);
	//if (v < 0.0 || u + v > 1.0)
	//	return(false);
	//// at this stage we can compute t to find out where 
	//// the intersection point is on the line
	//double t = f * vtkMath::Dot(e2,q);
	//if (t > 0.00001) // ray intersection
	//	return(true);
	//else // this means that there is a line intersection  
	//	 // but not a ray intersectione
	//	 return (false);
}
