#pragma once
#ifndef __MISWINOWS__
#define __MISWINOWS__

#include "misRenderer.h"
#include "misViewPort.h"
#include "misWindowModel.h"
#include "IWindows.h"

namespace parcast {
	enum class ViewerType;
}

class vtkRenderWindow;
enum  ViewerType;
// When working with winform as parent ii sis needed to call both WNDPROC old winform and new provided by 
// misWin32Intaercator - because of unknown reason SetWindowsLong does not work on winform handles.
// order of calling mouse_move is also in interacting - when we recreate a renderer with previous used window all set 
// wnd procedure must be reset - VTK set size to 300 * 300 if sizes are equal to zero - this default behaviour is 
// overridden by misRenderWindow

class misWindow : public Iwindows
{
public:
	~misWindow();

	void AddRenderer(misRenderer::Pointer renderer) override;
	void CheckActivation(RECT &rc) const override;
	void GenerateFormWindowModel(misWindowModel  model) override;
	HWND get_m_Handle() const override;
	void set_m_Handle(HWND left)override;
	std::string get_m_Name() const override;
	void set_m_Name(std::string left) override;
	vtkRenderWindow* GetRenderWindow() override;
	vtkSmartPointer<vtkRenderWindowInteractor> GetInterActor() override;
	vtkSmartPointer<vtkRenderer> GetRenderer(int index) override;
	HGLRC GetContextId() override;
	int GetWindowIndex() const override;
	void SetWindowIndex(int val) override;
	int* GetRenderWindowSize() override;
	void Show() override;
	void Hide() override;
	void Destroy() override;
	int  GenerateRenderWindow(Iwindows::ViewerType type, misViewPort viewport = misViewPort()) override;
	misStrctWindowSize GetWindowSize() const override;
	void Start();
	std::string GetParentTabName() const override;
	void SetParentTabName(std::string val)override;
	std::string GetParentSubTabName() const override;
	void SetParentSubTabName(std::string val) override;
	bool GetActive() const override;
	void SetActive(bool val) override;
	void SetProvidedWindowAsParent(bool value) override;
	void MakeCurrent() override;

private:
	vtkSmartPointer<vtkRenderWindow> m_RenderWindow = nullptr;
	vtkSmartPointer<vtkRenderWindowInteractor> m_pInteractor;
	std::vector<vtkSmartPointer<vtkRenderer>>  m_RendererList;
	std::list<misRenderer::Pointer> m_Renderers;
	void* m_pHybridViewer = nullptr;
	HWND  m_ParentWindowHandle = nullptr;
	bool m_UseWindowAsParent = false;
	bool m_Active = false;
	int m_ToolbarHeight = 0;
	int m_WindowIndex = 0;
	std::string m_Name = "none";
	std::string style;
	std::string m_ParentSubTabName;
	std::string m_ParentTabName;

};

#endif
