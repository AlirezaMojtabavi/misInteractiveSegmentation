#include "StdAfx.h"
#include "misRenderWinow.h"
#include "vtkWin32OpenGLRenderWindow.h"

#include "vtkIdList.h"
#include "vtkCommand.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLRenderer.h"
#include "vtkOpenGLRenderWindow.h"
#include "vtkOpenGLError.h"
#include "vtkRendererCollection.h"
#include "vtkWin32RenderWindowInteractor.h"

#include <math.h>
#include <sstream>

#include "vtkOpenGLError.h"
// ----------------------------------------------------------------------------
void AdjustWindowRectForBorders(const int borders, const int x, const int y,
	const int width, const int height, RECT &r)
{
	DWORD style = WS_CLIPCHILDREN /*| WS_CLIPSIBLINGS*/;
	if (borders)
	{
		style |= WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style |= WS_POPUP;
	}
	r.left = x;
	r.top = y;
	r.right = r.left + width;
	r.bottom = r.top + height;
	BOOL result = AdjustWindowRect(&r, style, FALSE);
	if (!result)
	{
		vtkGenericWarningMacro("AdjustWindowRect failed, error: "
			<< GetLastError());
	}
}
misRenderWinow::misRenderWinow(void)
{

	m_Timer=vtkTimerLog::New();
	m_avgFrameRate=0;
	m_index=0;


}

misRenderWinow::~misRenderWinow(void)
{
	
	LONG_PTR  res=SetWindowLongPtrW(this->WindowId,sizeof(vtkLONG),NULL);
 
}


void misRenderWinow::CreateAWindow()
{
	this->VTKRegisterClass();

	if (this->WindowIdReferenceCount == 0)
	{
		static int count = 1;
		char *windowName;

		if (!this->WindowId)
		{
			this->DeviceContext = 0;

			int len = static_cast<int>(strlen("Visualization Toolkit - Win32OpenGL #"))
				+ (int)ceil((double)log10((double)(count + 1)))
				+ 1;
			windowName = new char[len];
			sprintf(windowName, "Visualization Toolkit - Win32OpenGL #%i", count++);
			this->SetWindowName(windowName);
			delete[] windowName;

#ifdef UNICODE
			wchar_t *wname = new wchar_t[mbstowcs(NULL, this->WindowName, 32000) + 1];
			mbstowcs(wname, this->WindowName, 32000);
#endif
			int x = ((this->Position[0] >= 0) ? this->Position[0] : 5);
			int y = ((this->Position[1] >= 0) ? this->Position[1] : 5);
			int height = ((this->Size[1] > 0) ? this->Size[1] : 300);
			int width = ((this->Size[0] > 0) ? this->Size[0] : 300);

			/* create window */
			if (this->ParentId)
			{
#ifdef UNICODE
				this->WindowId = CreateWindow(
					L"vtkOpenGL", wname,
					WS_CHILD | WS_CLIPCHILDREN /*| WS_CLIPSIBLINGS*/,
					x, y, width, height,
					this->ParentId, NULL, this->ApplicationInstance, NULL);
#else
				this->WindowId = CreateWindow(
					"vtkOpenGL", this->WindowName,
					WS_CHILD | WS_CLIPCHILDREN /*| WS_CLIPSIBLINGS*/,
					x, y, width, height,
					this->ParentId, NULL, this->ApplicationInstance, NULL);
#endif
			}
			else
			{
				DWORD style;
				if (this->Borders)
				{
					style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN /*| WS_CLIPSIBLINGS*/;
				}
				else
				{
					style = WS_POPUP | WS_CLIPCHILDREN /*| WS_CLIPSIBLINGS*/;
				}
				RECT r;
				AdjustWindowRectForBorders(this->Borders, x, y, width, height, r);
#ifdef UNICODE
				this->WindowId = CreateWindow(
					L"vtkOpenGL", wname, style,
					x, y, r.right - r.left, r.bottom - r.top,
					NULL, NULL, this->ApplicationInstance, NULL);
#else
				this->WindowId = CreateWindow(
					"vtkOpenGL", this->WindowName, style,
					x, y, r.right - r.left, r.bottom - r.top,
					NULL, NULL, this->ApplicationInstance, NULL);
#endif
			}
#ifdef UNICODE
			delete[] wname;
#endif

			if (!this->WindowId)
			{
				vtkErrorMacro("Could not create window, error:  " << GetLastError());
				return;
			}
			// extract the create info

			/* display window */
			if (!this->OffScreenRendering)
			{
				ShowWindow(this->WindowId, SW_SHOW);
			}
			//UpdateWindow(this->WindowId);
			this->OwnWindow = 1;
			vtkSetWindowLong(this->WindowId, sizeof(vtkLONG), (intptr_t)this);
		}
		if (!this->DeviceContext)
		{
			this->DeviceContext = GetDC(this->WindowId);
		}
		if (this->StereoCapableWindow)
		{
			this->SetupPixelFormatPaletteAndContext(this->DeviceContext, PFD_SUPPORT_OPENGL |
				PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER |
				PFD_STEREO, this->GetDebug(), 32, 32);
		}
		else
		{
			this->SetupPixelFormatPaletteAndContext(this->DeviceContext, PFD_SUPPORT_OPENGL |
				PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
				this->GetDebug(), 32, 32);
		}
		this->MakeCurrent();

		// wipe out any existing display lists
		this->ReleaseGraphicsResources(this);
		this->OpenGLInit();
		this->Mapped = 1;
		this->WindowIdReferenceCount = 1;
	}
	else
	{
		++this->WindowIdReferenceCount;
	}
}


void misRenderWinow::Render()
{
	m_Timer->StartTimer();
	int *size;
	int x,y;
	float *p1;

	// if we are in the middle of an abort check then return now
	if (this->InAbortCheck)
	{
		return;
	}

	// if we are in a render already from somewhere else abort now
	if (this->InRender)
	{
		return;
	}

	// if SetSize has not yet been called (from a script, possible off
	// screen use, other scenarios?) then call it here with reasonable
	// default values
	//if (0 == this->Size[0] && 0 == this->Size[1])
	//{
	//	this->SetSize(300, 300);
	//}


	double width = this->Size[0] ;
	double height = this->Size[1] ;

	if ((0 ==width )&& (0 == height))
	{
		return;
	}

	// reset the Abort flag
	this->AbortRender = 0;
	this->InRender = 1;

	//	vtkDebugMacro(<< "Starting Render Method.\n");
	this->InvokeEvent(vtkCommand::StartEvent,NULL);

	this->NeverRendered = 0;

	if ( this->Interactor && ! this->Interactor->GetInitialized() )
	{
		this->Interactor->Initialize();
	}

	// CAUTION:
	// This method uses this->GetSize() and allocates buffers using that size. 
	// Remember that GetSize() will returns a size scaled by the TileScale factor.
	// We should use GetActualSize() when we don't want the size to be scaled.

	// if there is a reason for an AccumulationBuffer
	if ( this->SubFrames || this->AAFrames || this->FDFrames)
	{
		// check the current size
		size = this->GetSize();
		unsigned int bufferSize = 3*size[0]*size[1];
		// If there is not a buffer or the size is too small
		// re-allocate it
		if( !this->AccumulationBuffer
			|| bufferSize > this->AccumulationBufferSize)
		{
			// it is OK to delete null, no sense in two if's
			delete [] this->AccumulationBuffer;
			// Save the size of the buffer
			this->AccumulationBufferSize = 3*size[0]*size[1];
			this->AccumulationBuffer = new float [this->AccumulationBufferSize];
			memset(this->AccumulationBuffer,0,this->AccumulationBufferSize*sizeof(float));
		}
	}

	// handle any sub frames
	if (this->SubFrames)
	{
		// get the size
		size = this->GetSize();

		//	pTimer->StartTimer();
		// draw the images
		this->DoAARender();
		// now accumulate the images
		if ((!this->AAFrames) && (!this->FDFrames))
		{
			p1 = this->AccumulationBuffer;
			unsigned char *p2;
			unsigned char *p3;
			if (this->ResultFrame)
			{
				p2 = this->ResultFrame;
			}
			else
			{
				p2 = this->GetPixelData(0,0,size[0]-1,size[1]-1,!this->DoubleBuffer);
			}
			p3 = p2;
			for (y = 0; y < size[1]; y++)
			{
				for (x = 0; x < size[0]; x++)
				{
					*p1 += *p2; p1++; p2++;
					*p1 += *p2; p1++; p2++;
					*p1 += *p2; p1++; p2++;
				}
			}
			delete [] p3;
		}

		// if this is the last sub frame then convert back into unsigned char
		this->CurrentSubFrame++;
		if (this->CurrentSubFrame >= this->SubFrames)
		{
			double num;
			unsigned char *p2 = new unsigned char [3*size[0]*size[1]];

			num = this->SubFrames;
			if (this->AAFrames)
			{
				num *= this->AAFrames;
			}
			if (this->FDFrames)
			{
				num *= this->FDFrames;
			}

			this->ResultFrame = p2;
			p1 = this->AccumulationBuffer;
			for (y = 0; y < size[1]; y++)
			{
				for (x = 0; x < size[0]; x++)
				{
					*p2 = static_cast<unsigned char>(*p1/num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1/num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1/num);
					p1++;
					p2++;
				}
			}

			this->CurrentSubFrame = 0;

			this->CopyResultFrame();

			// free any memory
			delete [] this->AccumulationBuffer;
			this->AccumulationBuffer = NULL;
		}
	}
	else // no subframes
	{
		// get the size
		size = this->GetSize();


		//	pTimer->StartTimer();
		// draw the images
		this->DoAARender();
		//	pTimer->StopTimer();
		//	int el=pTimer->GetElapsedTime();
		//	cout<<"elabse in DoAARender: "<<el<<std::endl;
		// if we had some accumulation occur
		if (this->AccumulationBuffer)
		{
			double num;
			unsigned char *p2 = new unsigned char [3*size[0]*size[1]];

			if (this->AAFrames)
			{
				num = this->AAFrames;
			}
			else
			{
				num = 1;
			}
			if (this->FDFrames)
			{
				num *= this->FDFrames;
			}

			this->ResultFrame = p2;
			p1 = this->AccumulationBuffer;
			for (y = 0; y < size[1]; y++)
			{
				for (x = 0; x < size[0]; x++)
				{
					*p2 = static_cast<unsigned char>(*p1/num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1/num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1/num);
					p1++;
					p2++;
				}
			}

			delete [] this->AccumulationBuffer;
			this->AccumulationBuffer = NULL;
		}
		//	pTimer->StartTimer();

		this->CopyResultFrame();
		//	pTimer->StopTimer();
		//	int el2=pTimer->GetElapsedTime();
		//	cout<<"elabse in CopyResultFrame: "<<el2<<std::endl;

	}

	if (this->ResultFrame)
	{
		delete [] this->ResultFrame;
		this->ResultFrame = NULL;
	}

	this->InRender = 0;
	//	pTimer->StartTimer();

	this->InvokeEvent(vtkCommand::EndEvent,NULL);	
	m_Timer->StopTimer();
	double  val = m_Timer->GetElapsedTime();
	m_index++;
	m_avgFrameRate = m_avgFrameRate + static_cast<float>(val);
}

//=============================================================
//----------------------------------------------------------------------------
// Handle rendering any antialiased frames.
void misRenderWinow::DoAARender()
{
	int i;

	// handle any anti aliasing
	if (this->AAFrames)
	{
		int *size;
		int x,y;
		float *p1;
		vtkRenderer *aren;
		vtkCamera *acam;
		double *dpoint;
		double offsets[2];
		double origfocus[4];
		double worldOffset[3];

		// get the size
		size = this->GetSize();

		origfocus[3] = 1.0;

		for (i = 0; i < this->AAFrames; i++)
		{
			// jitter the cameras
			offsets[0] = vtkMath::Random() - 0.5;
			offsets[1] = vtkMath::Random() - 0.5;

			vtkCollectionSimpleIterator rsit;
			for (this->Renderers->InitTraversal(rsit);
				(aren = this->Renderers->GetNextRenderer(rsit)); )
			{
				acam = aren->GetActiveCamera();

				// calculate the amount to jitter
				acam->GetFocalPoint(origfocus);
				aren->SetWorldPoint(origfocus);
				aren->WorldToDisplay();
				dpoint = aren->GetDisplayPoint();
				aren->SetDisplayPoint(dpoint[0] + offsets[0],
					dpoint[1] + offsets[1],
					dpoint[2]);
				aren->DisplayToWorld();
				dpoint = aren->GetWorldPoint();
				dpoint[0] /= dpoint[3];
				dpoint[1] /= dpoint[3];
				dpoint[2] /= dpoint[3];
				acam->SetFocalPoint(dpoint);

				worldOffset[0] = dpoint[0] - origfocus[0];
				worldOffset[1] = dpoint[1] - origfocus[1];
				worldOffset[2] = dpoint[2] - origfocus[2];

				acam->GetPosition(dpoint);
				acam->SetPosition(dpoint[0]+worldOffset[0],
					dpoint[1]+worldOffset[1],
					dpoint[2]+worldOffset[2]);
			}

			// draw the images
			this->DoFDRender();

			// restore the jitter to normal
			for (this->Renderers->InitTraversal(rsit);
				(aren = this->Renderers->GetNextRenderer(rsit)); )
			{
				acam = aren->GetActiveCamera();

				// calculate the amount to jitter
				acam->GetFocalPoint(origfocus);
				aren->SetWorldPoint(origfocus);
				aren->WorldToDisplay();
				dpoint = aren->GetDisplayPoint();
				aren->SetDisplayPoint(dpoint[0] - offsets[0],
					dpoint[1] - offsets[1],
					dpoint[2]);
				aren->DisplayToWorld();
				dpoint = aren->GetWorldPoint();
				dpoint[0] /= dpoint[3];
				dpoint[1] /= dpoint[3];
				dpoint[2] /= dpoint[3];
				acam->SetFocalPoint(dpoint);

				worldOffset[0] = dpoint[0] - origfocus[0];
				worldOffset[1] = dpoint[1] - origfocus[1];
				worldOffset[2] = dpoint[2] - origfocus[2];

				acam->GetPosition(dpoint);
				acam->SetPosition(dpoint[0]+worldOffset[0],
					dpoint[1]+worldOffset[1],
					dpoint[2]+worldOffset[2]);
			}


			// now accumulate the images
			p1 = this->AccumulationBuffer;
			if (!this->FDFrames)
			{
				unsigned char *p2;
				unsigned char *p3;
				if (this->ResultFrame)
				{
					p2 = this->ResultFrame;
				}
				else
				{
					p2 = this->GetPixelData(0,0,size[0]-1,size[1]-1,!this->DoubleBuffer);
				}
				p3 = p2;
				for (y = 0; y < size[1]; y++)
				{
					for (x = 0; x < size[0]; x++)
					{
						*p1 += static_cast<float>(*p2);
						p1++;
						p2++;
						*p1 += static_cast<float>(*p2);
						p1++;
						p2++;
						*p1 += static_cast<float>(*p2);
						p1++;
						p2++;
					}
				}
				delete [] p3;
			}
		}
	}
	else
	{
		this->DoFDRender();
	}
}

//----------------------------------------------------------------------------
// Handle rendering any focal depth frames.
void misRenderWinow::DoFDRender()
{
	int i;

	// handle any focal depth
	if (this->FDFrames)
	{
		int *size;
		int x,y;
		unsigned char *p2;
		unsigned char *p3;
		float *p1;
		vtkRenderer *aren;
		vtkCamera *acam;
		double focalDisk;
		double *vpn, *dpoint;
		double vec[3];
		vtkTransform *aTrans = vtkTransform::New();
		double offsets[2];
		double *orig;
		vtkCollectionSimpleIterator rsit;

		// get the size
		size = this->GetSize();

		orig = new double [3*this->Renderers->GetNumberOfItems()];

		for (i = 0; i < this->FDFrames; i++)
		{
			int j = 0;

			offsets[0] = vtkMath::Random(); // radius
			offsets[1] = vtkMath::Random()*360.0; // angle

			// store offsets for each renderer
			for (this->Renderers->InitTraversal(rsit);
				(aren = this->Renderers->GetNextRenderer(rsit)); )
			{
				acam = aren->GetActiveCamera();
				focalDisk = acam->GetFocalDisk()*offsets[0];

				vpn = acam->GetViewPlaneNormal();
				aTrans->Identity();
				aTrans->Scale(focalDisk,focalDisk,focalDisk);
				aTrans->RotateWXYZ(-offsets[1],vpn[0],vpn[1],vpn[2]);
				aTrans->TransformVector(acam->GetViewUp(),vec);

				dpoint = acam->GetPosition();

				// store the position for later
				memcpy(orig + j*3,dpoint,3 * sizeof (double));
				j++;

				acam->SetPosition(dpoint[0]+vec[0],
					dpoint[1]+vec[1],
					dpoint[2]+vec[2]);
			}

			// draw the images
			this->DoStereoRender();

			// restore the jitter to normal
			j = 0;
			for (this->Renderers->InitTraversal(rsit);
				(aren = this->Renderers->GetNextRenderer(rsit)); )
			{
				acam = aren->GetActiveCamera();
				acam->SetPosition(orig + j*3);
				j++;
			}

			// get the pixels for accumulation
			// now accumulate the images
			p1 = this->AccumulationBuffer;
			if (this->ResultFrame)
			{
				p2 = this->ResultFrame;
			}
			else
			{
				p2 = this->GetPixelData(0,0,size[0]-1,size[1]-1,!this->DoubleBuffer);
			}
			p3 = p2;
			for (y = 0; y < size[1]; y++)
			{
				for (x = 0; x < size[0]; x++)
				{
					*p1 += static_cast<float>(*p2);
					p1++;
					p2++;
					*p1 += static_cast<float>(*p2);
					p1++;
					p2++;
					*p1 += static_cast<float>(*p2);
					p1++;
					p2++;
				}
			}
			delete [] p3;
		}

		// free memory
		delete [] orig;
		aTrans->Delete();
	}
	else
	{
		this->DoStereoRender();
	}
}


//----------------------------------------------------------------------------
// Handle rendering the two different views for stereo rendering.
void misRenderWinow::DoStereoRender()
{
	vtkCollectionSimpleIterator rsit;

	//this->Start();
	this->StereoUpdate();

	if (this->StereoType != VTK_STEREO_RIGHT)
	{ // render the left eye
		vtkRenderer *aren;
		for (this->Renderers->InitTraversal(rsit);
			(aren = this->Renderers->GetNextRenderer(rsit)); )
		{
			// Ugly piece of code - we need to know if the camera already
			// exists or not. If it does not yet exist, we must reset the
			// camera here - otherwise it will never be done (missing its
			// oppportunity to be reset in the Render method of the
			// vtkRenderer because it will already exist by that point...)
			if ( !aren->IsActiveCameraCreated() )
			{
				aren->ResetCamera();
			}
			aren->GetActiveCamera()->SetLeftEye(1);
		}
		this->Renderers->Render();
	}

	if (this->StereoRender)
	{
		this->StereoMidpoint();
		if (this->StereoType != VTK_STEREO_LEFT)
		{ // render the right eye
			vtkRenderer *aren;
			for (this->Renderers->InitTraversal(rsit);
				(aren = this->Renderers->GetNextRenderer(rsit)); )
			{
				// Duplicate the ugly code here too. Of course, most
				// times the left eye will have been rendered before
				// the right eye, but it is possible that the user sets
				// everything up and renders just the right eye - so we
				// need this check here too.
				if ( !aren->IsActiveCameraCreated() )
				{
					aren->ResetCamera();
				}
				aren->GetActiveCamera()->SetLeftEye(0);
			}
			this->Renderers->Render();
		}
		this->StereoRenderComplete();
	}

}

void misRenderWinow::SetSize( int x,int  y)
{

	RECT  rc;
	GetClientRect(this->WindowId,&rc);
	LONG  width=rc.right-rc.left;
	LONG  height=rc.bottom-rc.top;

	if ((x>width)||(y>height))
	{
		return  ;
	}
	_ASSERT(x<=width);
	_ASSERT(y<=height);

	static int resizing = 0;
	if ((this->Size[0] != x) || (this->Size[1] != y))
	{
		this->Modified();
		this->Size[0] = x;
		this->Size[1] = y;

		if (this->Interactor)
		{
			this->Interactor->SetSize(x, y);
		}

		if (this->OffScreenRendering)
		{
			if(!this->CreatingOffScreenWindow)
			{
				if (!resizing)
				{
					resizing = 1;
					this->CleanUpOffScreenRendering();
					this->CreateOffScreenWindow(x,y);
					resizing = 0;
				}
			}
		}

		/*	else if (this->Mapped)
		{
		if (!resizing)
		{
		resizing = 1;

		if (this->ParentId)
		{
		SetWindowExtEx(this->DeviceContext,x,y,NULL);
		SetViewportExtEx(this->DeviceContext,x,y,NULL);
		SetWindowPos(this->WindowId,HWND_TOP,0,0,
		x, y, SWP_NOMOVE | SWP_NOZORDER);
		}
		else
		{
		SetWindowPos(this->WindowId,HWND_TOP,0,0,
		x+2*GetSystemMetrics(SM_CXFRAME),
		y+2*GetSystemMetrics(SM_CYFRAME) +GetSystemMetrics(SM_CYCAPTION),
		SWP_NOMOVE | SWP_NOZORDER);
		}
		resizing = 0;
		}
		}*/
	}
}

void misRenderWinow::Frame()
{
	this->MakeCurrent();
	if (!this->AbortRender && this->DoubleBuffer && this->SwapBuffers)
	{
		// use global scope to get Win32 API SwapBuffers and not be
		// confused with this->SwapBuffers
		
		::SwapBuffers(this->DeviceContext);


	}
	else
	{
		glFlush();
	}
}


void misRenderWinow::SetupPixelFormatPaletteAndContext(
	HDC hDC, DWORD dwFlags,
	int debug, int bpp,
	int zbpp)
{
	// Create a dummy window, needed for calling wglGetProcAddress.
#ifdef UNICODE
	HWND tempId = CreateWindow(L"vtkOpenGL", 0, 0, 0, 0, 1, 1, 0, 0, this->ApplicationInstance, 0);
#else
	HWND tempId = CreateWindow("vtkOpenGL", 0, 0, 0, 0, 1, 1, 0, 0, this->ApplicationInstance, 0);
#endif
	HDC tempDC = GetDC(tempId);
	PIXELFORMATDESCRIPTOR tempPfd;
	memset(&tempPfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	tempPfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	tempPfd.nVersion = 1;
	tempPfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	tempPfd.iPixelType = PFD_TYPE_RGBA;
	int tempPixelFormat = ChoosePixelFormat(tempDC, &tempPfd);
	SetPixelFormat(tempDC, tempPixelFormat, &tempPfd);
	HGLRC tempContext = wglCreateContext(tempDC);
	wglMakeCurrent(tempDC, tempContext);

	// make sure glew is initialized with fake window
	this->OpenGLInit();

	// First we try to use the newer wglChoosePixelFormatARB which enables
	// features like multisamples.
	PIXELFORMATDESCRIPTOR pfd;
	int pixelFormat = 0;
	if (wglChoosePixelFormatARB)
	{
		int attrib[] = {
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_SUPPORT_OPENGL_ARB, TRUE,
			WGL_DRAW_TO_WINDOW_ARB, TRUE,
			WGL_DOUBLE_BUFFER_ARB, TRUE,
			WGL_COLOR_BITS_ARB, bpp / 4 * 3,
			WGL_DEPTH_BITS_ARB, zbpp / 4 * 3,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		unsigned int n = 14;
		if (this->AlphaBitPlanes)
		{
			attrib[n] = WGL_ALPHA_BITS_ARB;
			attrib[n + 1] = bpp / 4;
			n += 2;
		}
		if (this->StencilCapable)
		{
			attrib[n] = WGL_STENCIL_BITS_ARB;
			attrib[n + 1] = 8;
			n += 2;
		}
		unsigned int stereoAttributeIndex = 0;
		if (dwFlags & PFD_STEREO)
		{
			attrib[n] = WGL_STEREO_ARB;
			attrib[n + 1] = TRUE;
			stereoAttributeIndex = n + 1;
			n += 2;
		}
		unsigned int multiSampleAttributeIndex = 0;
		if (this->MultiSamples > 1 &&
			wglewIsSupported("WGL_ARB_multisample"))
		{
			attrib[n] = WGL_SAMPLE_BUFFERS_ARB;
			attrib[n + 1] = 1;
			attrib[n + 2] = WGL_SAMPLES_ARB;
			attrib[n + 3] = this->MultiSamples;
			multiSampleAttributeIndex = n + 3;
			n += 4;
		}
		unsigned int numFormats;
		if (!wglChoosePixelFormatARB(hDC, attrib, 0, 1, &pixelFormat, &numFormats)
			|| numFormats == 0)
		{
			// If the requested number of multisamples does not work, try
			// scaling down the number of multisamples a few times.
			if (multiSampleAttributeIndex)
			{
				attrib[multiSampleAttributeIndex] /= 2;
				if (!wglChoosePixelFormatARB(hDC, attrib, 0, 1,
					&pixelFormat, &numFormats) || numFormats == 0)
				{
					attrib[multiSampleAttributeIndex] /= 2;
					wglChoosePixelFormatARB(hDC, attrib, 0, 1, &pixelFormat, &numFormats);
				}
			}
			// try dropping stereo
			if (stereoAttributeIndex && numFormats == 0)
			{
				attrib[stereoAttributeIndex] = FALSE;
				wglChoosePixelFormatARB(hDC, attrib, 0, 1, &pixelFormat, &numFormats);
			}
		}

		DescribePixelFormat(hDC, pixelFormat, sizeof(pfd), &pfd);
		if (!SetPixelFormat(hDC, pixelFormat, &pfd))
		{
			pixelFormat = 0;
		}
		else
		{
			if (debug && (dwFlags & PFD_STEREO) && !(pfd.dwFlags & PFD_STEREO))
			{
				vtkGenericWarningMacro("No Stereo Available!");
				this->StereoCapableWindow = 0;
			}
		}
	}
	else
	{
		vtkErrorMacro("failed to get wglChoosePixelFormatARB");
	}

	// see if we can get a 3.2 context
	if (pixelFormat)
	{
		this->SetupPalette(hDC);

		// create a context
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
			reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
		if (wglCreateContextAttribsARB)
		{
			int iContextAttribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				WGL_CONTEXT_FLAGS_ARB, 0,
				// WGL_CONTEXT_PROFILE_MASK_ARB,
				// WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				// WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				0 // End of attributes list
			};

			this->ContextId = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);
		}
		if (this->ContextId)
		{
			this->SetContextSupportsOpenGL32(true);
		}
		else
		{
			this->ContextId = wglCreateContext(hDC);
		}
		if (this->ContextId == NULL)
		{
			vtkErrorMacro("wglCreateContext failed in CreateAWindow(), error: " << GetLastError());
		}
	}

	// Delete the dummy window
	wglMakeCurrent(tempDC, 0);
	wglDeleteContext(tempContext);
	ReleaseDC(tempId, tempDC);
	::DestroyWindow(tempId); // windows api

							 // If we got a valid pixel format in the process, we are done.
							 // Otherwise fail as the OpenGL does not support even 2.1
	if (!pixelFormat)
	{
		vtkErrorMacro("failed to get valid pixel format.");
	}

	return;
}