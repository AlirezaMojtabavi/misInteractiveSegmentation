#include "stdafx.h"

#include "misRenderWindow.h"
 
void AdjustWindowRectForBorders(HWND hwnd, DWORD style, const int x, const int y,
	const int width, const int height, RECT &r);

misRenderWindow::misRenderWindow()
{
}


misRenderWindow::~misRenderWindow()
{
	LONG_PTR  res = vtkSetWindowLong(this->WindowId, sizeof(vtkLONG), NULL);
}

void misRenderWindow::CreateAWindow()
{
	WNDCLASS wndClass;
	 
#ifdef UNICODE
	if (!GetClassInfo(this->ApplicationInstance, L"vtkOpenGL", &wndClass))
#else
	if (!GetClassInfo(this->ApplicationInstance, "vtkOpenGL", &wndClass))
#endif
	{
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS| CS_PARENTDC| CS_SAVEBITS;
		wndClass.lpfnWndProc = vtkWin32OpenGLRenderWindow::WndProc;
		wndClass.cbClsExtra = 0;
		wndClass.hInstance = this->ApplicationInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
#ifdef UNICODE
		wndClass.lpszClassName = L"vtkOpenGL";
#else
		wndClass.lpszClassName = "vtkOpenGL";
#endif
		 
		 
		 
		wndClass.cbWndExtra = 2 * sizeof(vtkLONG);
		RegisterClass(&wndClass);
	}
	 
	if (this->WindowIdReferenceCount == 0)
	{
		if (!this->WindowId)
		{
			this->DeviceContext = 0;

			 
			 
			if (!strcmp(this->GetWindowName(), "Visualization Toolkit - OpenGL"))
			{
				static int count = 1;
				std::stringstream windowName;
				windowName << "Visualization Toolkit - Win32OpenGL #" << count++;
				this->SetWindowName(windowName.str().c_str());
			}

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
					WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
					x, y, width, height,
					this->ParentId, NULL, this->ApplicationInstance, NULL);
#else
				this->WindowId = CreateWindow(
					"vtkOpenGL", this->WindowName,
					WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
					x, y, width, height,
					this->ParentId, NULL, this->ApplicationInstance, NULL);
#endif
			}
			else
			{
				DWORD style = WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
				if (this->Borders)
				{
					style |= WS_OVERLAPPEDWINDOW;
				}
				else
				{
					style |= WS_POPUP;
				}
				RECT r;
				AdjustWindowRectForBorders(0, style, x, y, width, height, r);
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
			 

			 
			if (!this->OffScreenRendering)
			{
				ShowWindow(this->WindowId, SW_SHOW);
			}
			 
			this->OwnWindow = 1;
			vtkSetWindowLong(this->WindowId, sizeof(vtkLONG), (intptr_t)this);
		}
		auto old = vtkSetWindowLong(this->WindowId, sizeof(vtkLONG), (intptr_t)this);

		if (!this->DeviceContext)
		{
			this->DeviceContext = GetDC(this->WindowId);
		}
		DWORD flags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		if (this->StereoCapableWindow)
		{
			flags |= PFD_STEREO;
		}
		this->SetupPixelFormat(this->DeviceContext, flags, this->GetDebug(), 32, 32);
		this->SetupPalette(this->DeviceContext);
		this->ContextId = wglCreateContext(this->DeviceContext);
		if (this->ContextId == NULL)
		{
			vtkErrorMacro("wglCreateContext failed in CreateAWindow(), error: " << GetLastError());
		}
		this->MakeCurrent();

		 
		vtkRenderer* ren;
		vtkCollectionSimpleIterator rsit;
		for (this->Renderers->InitTraversal(rsit);
			(ren = this->Renderers->GetNextRenderer(rsit));)
		{
			ren->SetRenderWindow(0);
			ren->SetRenderWindow(this);
		}
		this->OpenGLInit();
		this->Mapped = 1;
		this->WindowIdReferenceCount = 1;
	}
	else
	{
		++this->WindowIdReferenceCount;
	}
}
//----------------------------------------------------------------------------
// Ask each renderer owned by this RenderWindow to render its image and
// synchronize this process.
void misRenderWindow::Render()
{
	int *size;
	int x, y;
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
 

	// reset the Abort flag
	this->AbortRender = 0;
	this->InRender = 1;

	vtkDebugMacro(<< "Starting Render Method.\n");
	this->InvokeEvent(vtkCommand::StartEvent, NULL);

	this->NeverRendered = 0;

	if (this->Interactor && !this->Interactor->GetInitialized())
	{
		this->Interactor->Initialize();
	}

	// CAUTION:
	// This method uses this->GetSize() and allocates buffers using that size.
	// Remember that GetSize() will returns a size scaled by the TileScale factor.
	// We should use GetActualSize() when we don't want the size to be scaled.

	// if there is a reason for an AccumulationBuffer
	if (this->SubFrames || this->AAFrames || this->FDFrames)
	{
		// check the current size
		size = this->GetSize();
		unsigned int bufferSize = 3 * size[0] * size[1];
		// If there is not a buffer or the size is too small
		// re-allocate it
		if (!this->AccumulationBuffer
			|| bufferSize > this->AccumulationBufferSize)
		{
			// it is OK to delete null, no sense in two if's
			delete[] this->AccumulationBuffer;
			// Save the size of the buffer
			this->AccumulationBufferSize = 3 * size[0] * size[1];
			this->AccumulationBuffer = new float[this->AccumulationBufferSize];
			memset(this->AccumulationBuffer, 0, this->AccumulationBufferSize * sizeof(float));
		}
	}

	// handle any sub frames
	if (this->SubFrames)
	{
		// get the size
		size = this->GetSize();

		// draw the images
		this->DoAARender();

		// now accumulate the images
		if ((!this->AAFrames) && (!this->FDFrames))
		{
			p1 = this->AccumulationBuffer;
			unsigned char *p2;
			unsigned char *p3 = NULL;
			if (this->ResultFrame)
			{
				p2 = this->ResultFrame;
			}
			else
			{
				p2 = this->GetPixelData(0, 0, size[0] - 1, size[1] - 1, !this->DoubleBuffer);
				p3 = p2;
			}
			for (y = 0; y < size[1]; y++)
			{
				for (x = 0; x < size[0]; x++)
				{
					*p1 += *p2; p1++; p2++;
					*p1 += *p2; p1++; p2++;
					*p1 += *p2; p1++; p2++;
				}
			}
			if (p3)
			{
				delete[] p3;
			}
		}

		// if this is the last sub frame then convert back into unsigned char
		this->CurrentSubFrame++;
		if (this->CurrentSubFrame >= this->SubFrames)
		{
			double num;
			unsigned char *p2 = new unsigned char[3 * size[0] * size[1]];

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
					*p2 = static_cast<unsigned char>(*p1 / num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1 / num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1 / num);
					p1++;
					p2++;
				}
			}

			this->CurrentSubFrame = 0;
			this->CopyResultFrame();

			// free any memory
			delete[] this->AccumulationBuffer;
			this->AccumulationBuffer = NULL;
		}
	}
	else // no subframes
	{
		// get the size
		size = this->GetSize();

		this->DoAARender();
		// if we had some accumulation occur
		if (this->AccumulationBuffer)
		{
			double num;
			unsigned char *p2 = new unsigned char[3 * size[0] * size[1]];

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
					*p2 = static_cast<unsigned char>(*p1 / num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1 / num);
					p1++;
					p2++;
					*p2 = static_cast<unsigned char>(*p1 / num);
					p1++;
					p2++;
				}
			}

			delete[] this->AccumulationBuffer;
			this->AccumulationBuffer = NULL;
		}

		this->CopyResultFrame();
	}

	delete[] this->ResultFrame;
	this->ResultFrame = NULL;

	this->InRender = 0;
	this->InvokeEvent(vtkCommand::EndEvent, NULL);
}