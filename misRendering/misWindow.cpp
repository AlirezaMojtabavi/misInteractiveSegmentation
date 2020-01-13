#include "StdAfx.h"
#include "misWindow.h"
#include "mis3dRenderer.h"
#include "misWin32Interactor.h"
#include "misRenderWindow.h"

misWindow::~misWindow()
{
	SetPropA(m_ParentWindowHandle, "RenderWindow", NULL);
}

HWND misWindow::get_m_Handle() const
{
	return m_ParentWindowHandle;
}

void misWindow::set_m_Handle(HWND left)
{
	m_ParentWindowHandle = left;
}

std::string misWindow::get_m_Name() const
{
	return m_Name;
}

void misWindow::set_m_Name(std::string left)
{
	m_Name = left;
}

int misWindow::GenerateRenderWindow(Iwindows::ViewerType type, misViewPort viewport)
{
	if (!m_RenderWindow)
	{
		m_RenderWindow = vtkSmartPointer<misRenderWindow>::New();
		if (m_UseWindowAsParent)
		{
			m_RenderWindow->SetParentId(m_ParentWindowHandle);
			m_pInteractor = vtkSmartPointer<vtkWin32RenderWindowInteractor>::New();
		}
		else
		{
			m_RenderWindow->SetWindowId(m_ParentWindowHandle);
			SetPropA(m_ParentWindowHandle, "RenderWindow", m_RenderWindow.GetPointer());
			m_pInteractor = vtkSmartPointer<misWin32Interactor>::New();
		}
		RECT rc;
		GetClientRect(m_ParentWindowHandle, &rc);
		m_RenderWindow->SetSize(rc.right - rc.left, rc.bottom - rc.top - m_ToolbarHeight);
		m_RenderWindow->SetInteractor(m_pInteractor);
		m_pInteractor->SetRenderWindow(m_RenderWindow);
		m_pInteractor->Initialize();

	}
	vtkSmartPointer<vtkRenderer> renderer;

	if (type == VolumeViewer)
	{
		renderer = vtkSmartPointer<mis3dRenderer>::New();
	}
	else
	{
		renderer = vtkSmartPointer<vtkRenderer>::New();
	}
	renderer->SetViewport(viewport.GetStart().x, viewport.GetStart().y, viewport.GetEnd().x,
		viewport.GetEnd().y);
	m_RenderWindow->AddRenderer(renderer);
	m_RendererList.push_back(renderer);
	return static_cast<int>(m_RendererList.size() - 1);
}

misStrctWindowSize misWindow::GetWindowSize() const
{
	RECT rc;
	GetClientRect(m_ParentWindowHandle, &rc);
	m_RenderWindow->SetSize(rc.right - rc.left, rc.bottom - rc.top);
	misStrctWindowSize  sizeWindow;
	sizeWindow.width = static_cast<int> (rc.right - rc.left);
	sizeWindow.height = static_cast<int> (rc.bottom - rc.top);
	return sizeWindow;
}

int misWindow::GetWindowIndex() const
{
	return m_WindowIndex;
}

void misWindow::SetWindowIndex(int val)
{
	m_WindowIndex = val;
}

void misWindow::Start()
{
	m_pInteractor->Initialize();
	m_pInteractor->Start();
}

std::string misWindow::GetParentTabName() const
{
	return m_ParentTabName;
}

void misWindow::SetParentTabName(std::string val)
{
	m_ParentTabName = val;
}

std::string misWindow::GetParentSubTabName() const
{
	return m_ParentSubTabName;
}

void misWindow::SetParentSubTabName(std::string val)
{
	m_ParentSubTabName = val;
}

bool misWindow::GetActive() const
{
	return m_Active;
}

void misWindow::SetActive(bool val)
{
	m_Active = val;
}

void misWindow::SetProvidedWindowAsParent(bool value)
{
	m_UseWindowAsParent = value;
}

void misWindow::MakeCurrent()
{
	wglMakeCurrent(GetDC(m_ParentWindowHandle), GetContextId());
}

HGLRC misWindow::GetContextId()
{
	return  static_cast<HGLRC>(m_RenderWindow->GetGenericDisplayId());
}

int* misWindow::GetRenderWindowSize()
{
	auto size = new int[2];
	size[0] = 0;
	size[1] = 0;
	if (m_RenderWindow)
	{
		auto sz = m_RenderWindow->GetSize();
		size[0] = sz[0];
		size[1] = sz[1];
	}
	return  size;
}

void misWindow::Show()
{
	ShowWindow(m_ParentWindowHandle, SW_SHOW);
}

void misWindow::Hide()
{
	ShowWindow(m_ParentWindowHandle, SW_HIDE);
}

void misWindow::Destroy()
{
	DestroyWindow(m_ParentWindowHandle);
}

vtkRenderWindow* misWindow::GetRenderWindow()
{
	return m_RenderWindow;
}

vtkSmartPointer<vtkRenderWindowInteractor> misWindow::GetInterActor()
{
	return m_pInteractor;
}

vtkSmartPointer<vtkRenderer> misWindow::GetRenderer(int index)
{
	return m_RendererList[index];
}

void misWindow::GenerateFormWindowModel(misWindowModel model)
{
	set_m_Handle(static_cast<HWND>(model.GetHandle()));
	set_m_Name(model.GetName());
	m_ParentSubTabName = model.GetParentSubSequenceName();
	m_ParentTabName = model.GetParentSequenceName();
	m_WindowIndex = model.GetWindowIndex();
	m_ToolbarHeight = model.GetToolbarHeight();
}

void misWindow::AddRenderer(misRenderer::Pointer renderer)
{
	m_RenderWindow->AddRenderer(renderer->GetRenderer());
}

void misWindow::CheckActivation(RECT &rc) const
{
	RECT  parentClient;
	auto handle = GetParent(m_ParentWindowHandle);
	GetClientRect(handle, &parentClient);

	if (true)
	{
		SetActiveWindow(m_ParentWindowHandle);
		SendMessageW(m_ParentWindowHandle, WM_ACTIVATE, 0, 0);
		SendMessageW(m_ParentWindowHandle, WM_MOUSEACTIVATE, 0, 0);
		SendMessageW(m_ParentWindowHandle, WM_MBUTTONDOWN, 0, 0);
		SendMessageW(m_ParentWindowHandle, WM_MBUTTONUP, 0, 0);
	}
}