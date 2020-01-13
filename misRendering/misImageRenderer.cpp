#include "StdAfx.h"
#include "misImageRenderer.h"

#include "misGeoActor.h"
#include "misImageActor.h"

using namespace std;

misImageRenderer::~misImageRenderer(void)
{
}

void misImageRenderer::Render()
{
	
	
	if(this->Delegate!=0 && this->Delegate->GetUsed())
	{
		this->Delegate->Render(this);
		return;
	}

	double   t1, t2;
	int      i;
	vtkProp  *aProp;
	int *size;

	// If Draw is not on, ignore the render.
	if (!this->Draw)
	{
		vtkDebugMacro("Ignoring render because Draw is off.");
		return;
	}

	t1 = vtkTimerLog::GetUniversalTime();

	this->InvokeEvent(vtkCommand::StartEvent,NULL);

	size = this->RenderWindow->GetSize();

	// if backing store is on and we have a stored image
	if (this->BackingStore && this->BackingImage &&
		this->MTime < this->RenderTime &&
		this->ActiveCamera->GetMTime() < this->RenderTime &&
		this->RenderWindow->GetMTime() < this->RenderTime &&
		this->BackingStoreSize[0] == size[0] &&
		this->BackingStoreSize[1] == size[1])      
	{
		int mods = 0;
		vtkLight *light;

		// now we just need to check the lights and actors
		vtkCollectionSimpleIterator sit;
		for(this->Lights->InitTraversal(sit); 
			(light = this->Lights->GetNextLight(sit)); )
		{
			if (light->GetSwitch() && 
				light->GetMTime() > this->RenderTime)
			{
				mods = 1;
				goto completed_mod_check;
			}
		}
		vtkCollectionSimpleIterator pit;
		for (this->Props->InitTraversal(pit); 
			(aProp = this->Props->GetNextProp(pit)); )
		{
			// if it's invisible, we can skip the rest 
			if (aProp->GetVisibility())
			{
				if (aProp->GetRedrawMTime() > this->RenderTime)
				{
					mods = 1;
					goto completed_mod_check;
				}
			}
		}

completed_mod_check:

		if (!mods)
		{
			int rx1, ry1, rx2, ry2;

			// backing store should be OK, lets use it
			// calc the pixel range for the renderer
			rx1 = static_cast<int>(this->Viewport[0]*
				(this->RenderWindow->GetSize()[0] - 1));
			ry1 = static_cast<int>(this->Viewport[1]*
				(this->RenderWindow->GetSize()[1] - 1));
			rx2 = static_cast<int>(this->Viewport[2]*
				(this->RenderWindow->GetSize()[0] - 1));
			ry2 = static_cast<int>(this->Viewport[3]*
				(this->RenderWindow->GetSize()[1] - 1));
			this->RenderWindow->SetPixelData(rx1,ry1,rx2,ry2,this->BackingImage,0);
			this->InvokeEvent(vtkCommand::EndEvent,NULL);
			return;
		}
	}

	// Create the initial list of visible props
	// This will be passed through AllocateTime(), where
	// a time is allocated for each prop, and the list
	// maybe re-ordered by the cullers. Also create the
	// sublists for the props that need ray casting, and
	// the props that need to be rendered into an image.
	// Fill these in later (in AllocateTime) - get a 
	// count of them there too
	if ( this->Props->GetNumberOfItems() > 0 )
	{
		this->PropArray = new vtkProp *[this->Props->GetNumberOfItems()];
	}
	else
	{
		this->PropArray = NULL;
	}

	this->PropArrayCount = 0;
	vtkCollectionSimpleIterator pit;
	for ( this->Props->InitTraversal(pit); 
		(aProp = this->Props->GetNextProp(pit)); )
	{
		if ( aProp->GetVisibility() )
		{
			this->PropArray[this->PropArrayCount++] = aProp;
		}
	}


	//commented for performance  consideration

	//if ( this->PropArrayCount == 0 )
	//{
	//	vtkDEBUGLOGGINGMacro( << "There are no visible props!" );
	//}
	//else
	//{
	//	// Call all the culling methods to set allocated time
	//	// for each prop and re-order the prop list if desired

	//	if (m_UsingCulling)
	//		this->AllocateTime();
	//}

	// do the render library specific stuff
	if(this->Pass!=0)
	{
		vtkRenderState s(this);
		s.SetPropArrayAndCount(this->PropArray,this->PropArrayCount);
		s.SetFrameBuffer(0);
		this->Pass->Render(&s);
	}
	else
	{
		this->DeviceRender();
	}
	
	GLenum   error= glGetError();
	if (error!=GL_NO_ERROR)
	{
		const GLubyte *errString;
		errString = gluErrorString(error);
		cout<<"OpenGL error:"<<errString<<std::endl;
	}

 
	// If we aborted, restore old estimated times
	// Setting the allocated render time to zero also sets the 
	// estimated render time to zero, so that when we add back
	// in the old value we have set it correctly.
	if ( this->RenderWindow->GetAbortRender() )
	{
		for ( i = 0; i < this->PropArrayCount; i++ )
		{
			this->PropArray[i]->RestoreEstimatedRenderTime();
		}
	}

	// Clean up the space we allocated before. If the PropArray exists,
	// they all should exist
	if ( this->PropArray)
	{
		delete [] this->PropArray;
		this->PropArray                = NULL;
	}

	if (this->BackingStore)
	{
		if (this->BackingImage)
		{
			delete [] this->BackingImage;
		}

		int rx1, ry1, rx2, ry2;

		// backing store should be OK, lets use it
		// calc the pixel range for the renderer
		rx1 = static_cast<int>(this->Viewport[0]*(size[0] - 1));
		ry1 = static_cast<int>(this->Viewport[1]*(size[1] - 1));
		rx2 = static_cast<int>(this->Viewport[2]*(size[0] - 1));
		ry2 = static_cast<int>(this->Viewport[3]*(size[1] - 1));
		this->BackingImage = this->RenderWindow->GetPixelData(rx1,ry1,rx2,ry2,0);
		this->BackingStoreSize[0] = size[0];
		this->BackingStoreSize[1] = size[1];
	}


	// If we aborted, do not record the last render time.
	// Lets play around with determining the acuracy of the 
	// EstimatedRenderTimes.  We can try to adjust for bad 
	// estimates with the TimeFactor.
	if ( ! this->RenderWindow->GetAbortRender() )
	{
		// Measure the actual RenderTime
		t2 = vtkTimerLog::GetUniversalTime();
		this->LastRenderTimeInSeconds = static_cast<double>(t2 - t1);

		if (this->LastRenderTimeInSeconds == 0.0)
		{
			this->LastRenderTimeInSeconds = 0.0001;
		}
		this->TimeFactor = this->AllocatedRenderTime/this->LastRenderTimeInSeconds;
	}

}

int misImageRenderer::UpdateGeometry( void )
{

	this->NumberOfPropsRendered = 0;

	if ( this->PropArrayCount == 0 )
	{
		this->InvokeEvent(vtkCommand::EndEvent,NULL);
		return 0;
	}



	if (this->Selector)
	{
		// When selector is present, we are performing a selection,
		// so do the selection rendering pass instead of the normal passes.
		// Delegate the rendering of the props to the selector itself.
		this->NumberOfPropsRendered = this->Selector->Render(this,
			this->PropArray, this->PropArrayCount);
		this->InvokeEvent(vtkCommand::EndEvent,NULL);
		this->RenderTime.Modified();
		vtkDebugMacro("Rendered " << this->NumberOfPropsRendered << " actors" );
		return this->NumberOfPropsRendered;
	}

	GLboolean depth_Enabled = glIsEnabled(GL_DEPTH_TEST);
	if (!depth_Enabled )
		glEnable(GL_DEPTH_TEST);
	vector<misGeoActor*> overlayActors;//actor,s that need to render without z checking
	for (int  i = 0; i < this->PropArrayCount; i++ )
	{

		misGeoActor* pGeoActor=dynamic_cast<misGeoActor*>(PropArray[i]);
		if((pGeoActor)&&(pGeoActor->GetDisbaleDepthDest()))

		{
			overlayActors.push_back(pGeoActor);
		}		
		else
		{
			this->NumberOfPropsRendered +=
				this->PropArray[i]->RenderOpaqueGeometry(this);
		}

 

	}

	// do the render library specific stuff about translucent polygonal geometry.
	// As it can be expensive, do a quick check if we can skip this step
	int hasTranslucentPolygonalGeometry=0;
	for (int i = 0; !hasTranslucentPolygonalGeometry && i < this->PropArrayCount;
		i++ )
	{ 
		hasTranslucentPolygonalGeometry=
			this->PropArray[i]->HasTranslucentPolygonalGeometry();
	}
	if(hasTranslucentPolygonalGeometry)
	{
		this->DeviceRenderTranslucentPolygonalGeometry();
	}

	// loop through props and give them a chance to
	// render themselves as volumetric geometry.
	for (int  i = 0; i < this->PropArrayCount; i++ )
	{
		this->NumberOfPropsRendered +=
			this->PropArray[i]->RenderVolumetricGeometry(this);
	}

	// loop through props and give them a chance to
	// render themselves as an overlay (or underlay)
	for (int  i = 0; i < this->PropArrayCount; i++ )
	{
		this->NumberOfPropsRendered +=
			this->PropArray[i]->RenderOverlay(this);
	}



	std::for_each(overlayActors.begin(),overlayActors.end(),[&](misGeoActor*  actor)
		
	{
		glDisable(GL_DEPTH_TEST);
		this->NumberOfPropsRendered +=
			actor->RenderOpaqueGeometry(this);
		glEnable(GL_DEPTH_TEST);
	}
	);
	

	this->InvokeEvent(vtkCommand::EndEvent,NULL);
	this->RenderTime.Modified();

	vtkDebugMacro( << "Rendered " <<
		this->NumberOfPropsRendered << " actors" );

	
	return  this->NumberOfPropsRendered;

}

misImageRenderer::misImageRenderer( void )
{

}

 

 


