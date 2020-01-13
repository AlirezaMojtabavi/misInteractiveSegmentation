#include "StdAfx.h"
#include "misArrow.h"

vtkCxxRevisionMacro(misArrow, "$Revision: 1.7 $");
vtkStandardNewMacro(misArrow);

vtkCxxSetObjectMacro( misArrow, UserDefinedTip, vtkPolyData );
vtkCxxSetObjectMacro( misArrow, UserDefinedShaft, vtkPolyData );

//----------------------------------------------------------------------------
misArrow::misArrow()
{
	this->AxisLabels = 1;

	this->XAxisLabelText = NULL;
	this->YAxisLabelText = NULL;
	this->ZAxisLabelText = NULL;

	this->SetXAxisLabelText("X");
	this->SetYAxisLabelText("Y");
	this->SetZAxisLabelText("Z");

	this->XAxisShaft = vtkActor::New();
	this->XAxisShaft->GetProperty()->SetColor(1, 0, 0);
	this->YAxisShaft = vtkActor::New();
	this->YAxisShaft->GetProperty()->SetColor(0, 1, 0);
	this->ZAxisShaft = vtkActor::New();
	this->ZAxisShaft->GetProperty()->SetColor(0, 0, 1);

	this->XAxisTip = vtkActor::New();
	this->XAxisTip->GetProperty()->SetColor(1, 0, 0);
	this->YAxisTip = vtkActor::New();
	this->YAxisTip->GetProperty()->SetColor(0, 1, 0);
	this->ZAxisTip = vtkActor::New();
	this->ZAxisTip->GetProperty()->SetColor(0, 0, 1);

	this->CylinderSource = vtkCylinderSource::New();
	this->CylinderSource->SetHeight(1.0);

	this->LineSource = vtkLineSource::New();
	this->LineSource->SetPoint1( 0.0, 0.0, 0.0 );
	this->LineSource->SetPoint2( 0.0, 1.0, 0.0 );

	this->ConeSource = vtkConeSource::New();
	this->ConeSource->SetDirection( 0, 1, 0 );
	this->ConeSource->SetHeight( 1.0 );

	this->SphereSource = vtkSphereSource::New();

	vtkPolyDataMapper *shaftMapper = vtkPolyDataMapper::New();

	this->XAxisShaft->SetMapper( shaftMapper );
	this->YAxisShaft->SetMapper( shaftMapper );
	this->ZAxisShaft->SetMapper( shaftMapper );

	shaftMapper->Delete();

	vtkPolyDataMapper *tipMapper = vtkPolyDataMapper::New();

	this->XAxisTip->SetMapper( tipMapper );
	this->YAxisTip->SetMapper( tipMapper );
	this->ZAxisTip->SetMapper( tipMapper );

	tipMapper->Delete();

	this->TotalLength[0] = 1.0;
	this->TotalLength[1] = 1.0;
	this->TotalLength[2] = 1.0;

	this->NormalizedShaftLength[0] = 0.8;
	this->NormalizedShaftLength[1] = 0.8;
	this->NormalizedShaftLength[2] = 0.8;

	this->NormalizedTipLength[0] = 0.2;
	this->NormalizedTipLength[1] = 0.2;
	this->NormalizedTipLength[2] = 0.2;

	this->NormalizedLabelPosition[0] = 1.0;
	this->NormalizedLabelPosition[1] = 1.0;
	this->NormalizedLabelPosition[2] = 1.0;

	this->ConeResolution = 16;
	this->SphereResolution = 16;
	this->CylinderResolution = 16;

	this->ConeRadius = 0.4;
	this->SphereRadius = 0.5;
	this->CylinderRadius = 0.05;

	this->ShaftType = misArrow::LINE_SHAFT;
	this->TipType   = misArrow::CONE_TIP;

	this->UserDefinedTip = NULL;
	this->UserDefinedShaft = NULL;

	this->XAxisLabel = vtkCaptionActor2D::New();
	this->YAxisLabel = vtkCaptionActor2D::New();
	this->ZAxisLabel = vtkCaptionActor2D::New();

	this->XAxisLabel->ThreeDimensionalLeaderOff();
	this->XAxisLabel->LeaderOff();
	this->XAxisLabel->BorderOff();
	this->XAxisLabel->SetPosition(0, 0);

	this->YAxisLabel->ThreeDimensionalLeaderOff();
	this->YAxisLabel->LeaderOff();
	this->YAxisLabel->BorderOff();
	this->YAxisLabel->SetPosition(0, 0);

	this->ZAxisLabel->ThreeDimensionalLeaderOff();
	this->ZAxisLabel->LeaderOff();
	this->ZAxisLabel->BorderOff();
	this->ZAxisLabel->SetPosition(0, 0);

	this->UpdateProps();
}

//----------------------------------------------------------------------------
misArrow::~misArrow()
{
	this->CylinderSource->Delete();
	this->LineSource->Delete();
	this->ConeSource->Delete();
	this->SphereSource->Delete();

	this->XAxisShaft->Delete();
	this->YAxisShaft->Delete();
	this->ZAxisShaft->Delete();

	this->XAxisTip->Delete();
	this->YAxisTip->Delete();
	this->ZAxisTip->Delete();

	this->SetUserDefinedTip( NULL );
	this->SetUserDefinedShaft( NULL );

	this->SetXAxisLabelText( NULL );
	this->SetYAxisLabelText( NULL );
	this->SetZAxisLabelText( NULL );

	this->XAxisLabel->Delete();
	this->YAxisLabel->Delete();
	this->ZAxisLabel->Delete();
}

//----------------------------------------------------------------------------
// Shallow copy of an actor.
void misArrow::ShallowCopy(vtkProp *prop)
{
	misArrow *a = misArrow::SafeDownCast(prop);
	if ( a != NULL )
	{
		this->SetAxisLabels( a->GetAxisLabels() );
		this->SetXAxisLabelText( a->GetXAxisLabelText() );
		this->SetYAxisLabelText( a->GetYAxisLabelText() );
		this->SetZAxisLabelText( a->GetZAxisLabelText() );
		this->SetTotalLength( a->GetTotalLength() );
		this->SetNormalizedShaftLength( a->GetNormalizedShaftLength() );
		this->SetNormalizedTipLength( a->GetNormalizedTipLength() );
		this->SetNormalizedLabelPosition( a->GetNormalizedLabelPosition() );
		this->SetConeResolution( a->GetConeResolution() );
		this->SetSphereResolution( a->GetSphereResolution() );
		this->SetCylinderResolution( a->GetCylinderResolution() );
		this->SetConeRadius( a->GetConeRadius() );
		this->SetSphereRadius( a->GetSphereRadius() );
		this->SetCylinderRadius( a->GetCylinderRadius() );
		this->SetTipType( a->GetTipType() );
		this->SetShaftType( a->GetShaftType() );
		this->SetUserDefinedTip( a->GetUserDefinedTip() );
		this->SetUserDefinedShaft( a->GetUserDefinedShaft() );
	}

	// Now do superclass
	this->vtkProp3D::ShallowCopy(prop);
}

//----------------------------------------------------------------------------
void misArrow::GetActors(vtkPropCollection *ac)
{
	ac->AddItem( this->XAxisShaft );
	ac->AddItem( this->YAxisShaft );
	ac->AddItem( this->ZAxisShaft );
	ac->AddItem( this->XAxisTip );
	ac->AddItem( this->YAxisTip );
	ac->AddItem( this->ZAxisTip );
}

//----------------------------------------------------------------------------
int misArrow::RenderOpaqueGeometry(vtkViewport *vp)
{
	int renderedSomething = 0;

	this->UpdateProps();

	renderedSomething += this->XAxisShaft->RenderOpaqueGeometry( vp );
	renderedSomething += this->YAxisShaft->RenderOpaqueGeometry( vp );
	renderedSomething += this->ZAxisShaft->RenderOpaqueGeometry( vp );

	renderedSomething += this->XAxisTip->RenderOpaqueGeometry( vp );
	renderedSomething += this->YAxisTip->RenderOpaqueGeometry( vp );
	renderedSomething += this->ZAxisTip->RenderOpaqueGeometry( vp );

	if ( this->AxisLabels )
	{
		renderedSomething += this->XAxisLabel->RenderOpaqueGeometry( vp );
		renderedSomething += this->YAxisLabel->RenderOpaqueGeometry( vp );
		renderedSomething += this->ZAxisLabel->RenderOpaqueGeometry( vp );
	}

	renderedSomething = (renderedSomething > 0)?(1):(0);
	return renderedSomething;
}

//-----------------------------------------------------------------------------
int misArrow::RenderTranslucentPolygonalGeometry(vtkViewport *vp)
{
	int renderedSomething = 0;

	this->UpdateProps();

	renderedSomething += this->XAxisShaft->RenderTranslucentPolygonalGeometry( vp );
	renderedSomething += this->YAxisShaft->RenderTranslucentPolygonalGeometry( vp );
	renderedSomething += this->ZAxisShaft->RenderTranslucentPolygonalGeometry( vp );

	renderedSomething += this->XAxisTip->RenderTranslucentPolygonalGeometry( vp );
	renderedSomething += this->YAxisTip->RenderTranslucentPolygonalGeometry( vp );
	renderedSomething += this->ZAxisTip->RenderTranslucentPolygonalGeometry( vp );

	if ( this->AxisLabels )
	{
		renderedSomething += this->XAxisLabel->RenderTranslucentPolygonalGeometry( vp );
		renderedSomething += this->YAxisLabel->RenderTranslucentPolygonalGeometry( vp );
		renderedSomething += this->ZAxisLabel->RenderTranslucentPolygonalGeometry( vp );
	}

	renderedSomething = (renderedSomething > 0)?(1):(0);
	return renderedSomething;
}

//-----------------------------------------------------------------------------
// Description:
// Does this prop have some translucent polygonal geometry?
int misArrow::HasTranslucentPolygonalGeometry()
{
	int result = 0;

	this->UpdateProps();

	result |= this->XAxisShaft->HasTranslucentPolygonalGeometry();
	result |= this->YAxisShaft->HasTranslucentPolygonalGeometry();
	result |= this->ZAxisShaft->HasTranslucentPolygonalGeometry();

	result |= this->XAxisTip->HasTranslucentPolygonalGeometry();
	result |= this->YAxisTip->HasTranslucentPolygonalGeometry();
	result |= this->ZAxisTip->HasTranslucentPolygonalGeometry();

	if ( this->AxisLabels )
	{
		result |= this->XAxisLabel->HasTranslucentPolygonalGeometry();
		result |= this->YAxisLabel->HasTranslucentPolygonalGeometry();
		result |= this->ZAxisLabel->HasTranslucentPolygonalGeometry();
	}
	return result;
}

//-----------------------------------------------------------------------------
int misArrow::RenderOverlay(vtkViewport *vp)
{
	int renderedSomething = 0;

	if ( !this->AxisLabels )
	{
		return renderedSomething;
	}

	this->UpdateProps();

	renderedSomething += this->XAxisLabel->RenderOverlay( vp );
	renderedSomething += this->YAxisLabel->RenderOverlay( vp );
	renderedSomething += this->ZAxisLabel->RenderOverlay( vp );

	renderedSomething = (renderedSomething > 0)?(1):(0);
	return renderedSomething;
}

//----------------------------------------------------------------------------
void misArrow::ReleaseGraphicsResources(vtkWindow *win)
{
	this->XAxisShaft->ReleaseGraphicsResources( win );
	this->YAxisShaft->ReleaseGraphicsResources( win );
	this->ZAxisShaft->ReleaseGraphicsResources( win );

	this->XAxisTip->ReleaseGraphicsResources( win );
	this->YAxisTip->ReleaseGraphicsResources( win );
	this->ZAxisTip->ReleaseGraphicsResources( win );

	this->XAxisLabel->ReleaseGraphicsResources( win );
	this->YAxisLabel->ReleaseGraphicsResources( win );
	this->ZAxisLabel->ReleaseGraphicsResources( win );
}

//----------------------------------------------------------------------------
void misArrow::GetBounds(double bounds[6])
{
	double *bds = this->GetBounds();
	bounds[0] = bds[0];
	bounds[1] = bds[1];
	bounds[2] = bds[2];
	bounds[3] = bds[3];
	bounds[4] = bds[4];
	bounds[5] = bds[5];
}

//----------------------------------------------------------------------------
// Get the bounds for this Actor as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
double *misArrow::GetBounds()
{
	double bounds[6];
	int i;

	this->XAxisShaft->GetBounds(this->Bounds);

	this->YAxisShaft->GetBounds(bounds);
	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i+1] =
			(bounds[2*i+1]>this->Bounds[2*i+1])?(bounds[2*i+1]):(this->Bounds[2*i+1]);
	}

	this->ZAxisShaft->GetBounds(bounds);
	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i+1] = 
			(bounds[2*i+1]>this->Bounds[2*i+1])?(bounds[2*i+1]):(this->Bounds[2*i+1]);
	}

	this->XAxisTip->GetBounds(bounds);
	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i+1] = 
			(bounds[2*i+1]>this->Bounds[2*i+1])?(bounds[2*i+1]):(this->Bounds[2*i+1]);
	}

	this->YAxisTip->GetBounds(bounds);
	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i+1] = 
			(bounds[2*i+1]>this->Bounds[2*i+1])?(bounds[2*i+1]):(this->Bounds[2*i+1]);
	}

	this->ZAxisTip->GetBounds(bounds);
	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i+1] = 
			(bounds[2*i+1]>this->Bounds[2*i+1])?(bounds[2*i+1]):(this->Bounds[2*i+1]);
	}

	double dbounds[6];
	(vtkPolyDataMapper::SafeDownCast(this->YAxisShaft->GetMapper()))->
		GetInput()->GetBounds( dbounds );

	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i+1] = 
			(dbounds[2*i+1]>this->Bounds[2*i+1])?(dbounds[2*i+1]):(this->Bounds[2*i+1]);
	}

	// We want this actor to rotate / re-center about the origin, so give it
	// the bounds it would have if the axes were symmetric.
	for ( i = 0; i < 3; ++i )
	{
		this->Bounds[2*i] = -this->Bounds[2*i+1];
	}

	return this->Bounds;
}

//----------------------------------------------------------------------------
unsigned long int misArrow::GetMTime()
{
	unsigned long mTime = this->Superclass::GetMTime();
	return mTime;
}

//----------------------------------------------------------------------------
unsigned long int misArrow::GetRedrawMTime()
{
	unsigned long mTime = this->GetMTime();
	return mTime;
}

//----------------------------------------------------------------------------
void misArrow::SetTotalLength( double x, double y, double z )
{
	if ( this->TotalLength[0] != x ||
		this->TotalLength[1] != y ||
		this->TotalLength[2] != z )
	{
		this->TotalLength[0] = x;
		this->TotalLength[1] = y;
		this->TotalLength[2] = z;

		if ( x < 0.0 || y < 0.0 || z < 0.0 )
		{
			vtkGenericWarningMacro("One or more axes lengths are < 0 \
								   and may produce unexpected results.");
		}

		this->Modified();

		this->UpdateProps();
	}
}

//----------------------------------------------------------------------------
void misArrow::SetNormalizedShaftLength( double x, double y, double z )
{
	if ( this->NormalizedShaftLength[0] != x ||
		this->NormalizedShaftLength[1] != y ||
		this->NormalizedShaftLength[2] != z )
	{
		this->NormalizedShaftLength[0] = x;
		this->NormalizedShaftLength[1] = y;
		this->NormalizedShaftLength[2] = z;

		if ( x < 0.0 || x > 1.0 || y < 0.0 || y > 1.0 || z < 0.0 || z > 1.0 )
		{
			vtkGenericWarningMacro( "One or more normalized shaft lengths \
									are < 0 or > 1 and may produce unexpected results." );
		}

		this->Modified();

		this->UpdateProps();
	}
}

//----------------------------------------------------------------------------
void misArrow::SetNormalizedTipLength( double x, double y, double z )
{
	if ( this->NormalizedTipLength[0] != x ||
		this->NormalizedTipLength[1] != y ||
		this->NormalizedTipLength[2] != z )
	{
		this->NormalizedTipLength[0] = x;
		this->NormalizedTipLength[1] = y;
		this->NormalizedTipLength[2] = z;

		if ( x < 0.0 || x > 1.0 || y < 0.0 || y > 1.0 || z < 0.0 || z > 1.0 )
		{
			vtkGenericWarningMacro( "One or more normalized tip lengths \
									are < 0 or > 1 and may produce unexpected results." );
		}

		this->Modified();

		this->UpdateProps();
	}
}

//----------------------------------------------------------------------------
void misArrow::SetNormalizedLabelPosition( double x, double y, double z )
{
	if ( this->NormalizedLabelPosition[0] != x ||
		this->NormalizedLabelPosition[1] != y ||
		this->NormalizedLabelPosition[2] != z )
	{
		this->NormalizedLabelPosition[0] = x;
		this->NormalizedLabelPosition[1] = y;
		this->NormalizedLabelPosition[2] = z;

		if ( x < 0.0 || y < 0.0 || z < 0.0 )
		{
			vtkGenericWarningMacro( "One or more label positions are < 0 \
									and may produce unexpected results." );
		}

		this->Modified();

		this->UpdateProps();
	}
}

//----------------------------------------------------------------------------
void misArrow::SetShaftType( int type )
{
	if ( this->ShaftType != type )
	{
		if (type < misArrow::CYLINDER_SHAFT || \
			type > misArrow::USER_DEFINED_SHAFT)
		{
			vtkErrorMacro( "Undefined axes shaft type." );
			return;
		}

		if ( type == misArrow::USER_DEFINED_SHAFT && \
			this->UserDefinedShaft == NULL)
		{
			vtkErrorMacro( "Set the user defined shaft before changing the type." );
			return;
		}

		this->ShaftType = type;

		this->Modified();

		this->UpdateProps();
	}
}

//----------------------------------------------------------------------------
void misArrow::SetTipType( int type )
{
	if ( this->TipType != type )
	{
		if (type < misArrow::CONE_TIP || \
			type > misArrow::USER_DEFINED_TIP)
		{
			vtkErrorMacro( "Undefined axes tip type." );
			return;
		}

		if ( type == misArrow::USER_DEFINED_TIP && \
			this->UserDefinedTip == NULL)
		{
			vtkErrorMacro( "Set the user defined tip before changing the type." );
			return;
		}

		this->TipType = type;

		this->Modified();

		this->UpdateProps();
	}
}

//----------------------------------------------------------------------------
void misArrow::UpdateProps()
{
	static long long Counter = 0.0;

	this->CylinderSource->SetRadius( this->CylinderRadius );
	this->CylinderSource->SetResolution( this->CylinderResolution );

	this->ConeSource->SetResolution( this->ConeResolution );
	this->ConeSource->SetRadius( this->ConeRadius );


	//switch ( this->ShaftType )
	//{
	//case misArrow::CYLINDER_SHAFT:
	//	(vtkPolyDataMapper::SafeDownCast(this->XAxisShaft->GetMapper()))->
	//		SetInputConnection( this->CylinderSource->GetOutputPort() );
	//	break;
	//case misArrow::LINE_SHAFT:
	//	(vtkPolyDataMapper::SafeDownCast(this->XAxisShaft->GetMapper()))->
	//		SetInputConnection( this->LineSource->GetOutputPort() );
	//	break;
	//case misArrow::USER_DEFINED_SHAFT:
	//	(vtkPolyDataMapper::SafeDownCast(this->XAxisShaft->GetMapper()))->
	//		SetInputConnection( this->UserDefinedShaft->GetProducerPort() );
	//}

	//switch ( this->TipType )
	//{
	//case misArrow::CONE_TIP:
	//	(vtkPolyDataMapper::SafeDownCast(this->XAxisTip->GetMapper()))->
	//		SetInputConnection( this->ConeSource->GetOutputPort() );
	//	break;
	//case misArrow::SPHERE_TIP:
	//	(vtkPolyDataMapper::SafeDownCast(this->XAxisTip->GetMapper()))->
	//		SetInputConnection( this->SphereSource->GetOutputPort() );
	//	break;
	//case misArrow::USER_DEFINED_TIP:
	//	(vtkPolyDataMapper::SafeDownCast(this->XAxisTip->GetMapper()))->
	//		SetInputConnection( this->UserDefinedTip->GetProducerPort() );
	//}

	//(vtkPolyDataMapper::SafeDownCast(this->XAxisTip->GetMapper()))->
	//	
	//(vtkPolyDataMapper::SafeDownCast(this->XAxisShaft->GetMapper()))->
		

	if ( this->GetUserTransform() )
	{
		this->XAxisShaft->SetUserTransform( NULL );
		this->YAxisShaft->SetUserTransform( NULL );
		this->ZAxisShaft->SetUserTransform( NULL );
		this->XAxisTip->SetUserTransform( NULL );
		this->YAxisTip->SetUserTransform( NULL );
		this->ZAxisTip->SetUserTransform( NULL );
	}

	double scale[3];
	double bounds[6];

	(vtkPolyDataMapper::SafeDownCast(this->XAxisShaft->GetMapper()))->
		GetInput()->GetBounds( bounds );

	// The shaft and tip geometry are both initially along direction 0 1 0
	// in the case of cylinder, line, and cone.  Build up the axis from
	// constituent elements defined in their default positions.

	int i;
	for ( i = 0; i < 3; ++i )
	{
		scale[i] =
			this->NormalizedShaftLength[i]*this->TotalLength[i] /
			(bounds[3] - bounds[2]);
	}

	vtkTransform *xTransform = vtkTransform::New();
	
	xTransform->RotateX( 0 );
	xTransform->RotateZ( 0 );
	xTransform->RotateY( 0 );


	xTransform->Scale( scale[0], scale[0], scale[0] );

	xTransform->Translate( -(bounds[0]+bounds[1])/2,
		-bounds[2],
		-(bounds[4]+bounds[5])/2 );

	this->XAxisShaft->SetScale( xTransform->GetScale() );
	this->XAxisShaft->SetPosition( xTransform->GetPosition() );
	this->XAxisShaft->SetOrientation( xTransform->GetOrientation() );

	(vtkPolyDataMapper::SafeDownCast(this->XAxisTip->GetMapper()))->
		GetInput()->GetBounds( bounds );

	xTransform->Identity();

	xTransform->RotateX( 0 );
	xTransform->RotateZ( 0 );
	xTransform->RotateY( 0 );


	xTransform->Scale( this->TotalLength[0], this->TotalLength[0], this->TotalLength[0] );

	xTransform->Translate( 0, (1.0 - this->NormalizedTipLength[0]), 0 );

	xTransform->Scale( this->NormalizedTipLength[0],
		this->NormalizedTipLength[0],
		this->NormalizedTipLength[0] );


	xTransform->Translate( -(bounds[0]+bounds[1])/2,
		-bounds[2],
		-(bounds[4]+bounds[5])/2 );


	this->XAxisTip->SetScale( xTransform->GetScale() );
	this->XAxisTip->SetPosition( xTransform->GetPosition() );
	this->XAxisTip->SetOrientation( xTransform->GetOrientation() );

	xTransform->Delete();
	
	this->XAxisShaft->GetBounds(bounds);
	double offset = this->NormalizedLabelPosition[0]*(bounds[1]-bounds[0]);
	this->XAxisLabel->SetAttachmentPoint( bounds[0] + offset,
		bounds[2] - (bounds[3]-bounds[2])*2.0,
		bounds[5] + (bounds[5]-bounds[4])/2.0);
}

//----------------------------------------------------------------------------
vtkProperty *misArrow::GetXAxisTipProperty()
{
	return this->XAxisTip->GetProperty();
}

//----------------------------------------------------------------------------
vtkProperty *misArrow::GetYAxisTipProperty()
{
	return this->YAxisTip->GetProperty();
}

//----------------------------------------------------------------------------
vtkProperty *misArrow::GetZAxisTipProperty()
{
	return this->ZAxisTip->GetProperty();
}

//----------------------------------------------------------------------------
vtkProperty *misArrow::GetXAxisShaftProperty()
{
	return this->XAxisShaft->GetProperty();
}

//----------------------------------------------------------------------------
vtkProperty *misArrow::GetYAxisShaftProperty()
{
	return this->YAxisShaft->GetProperty();
}

//----------------------------------------------------------------------------
vtkProperty *misArrow::GetZAxisShaftProperty()
{
	return this->ZAxisShaft->GetProperty();
}

