#pragma once
#include "misViewPort.h"
#include "misRenderer.h"
#include "misWindowModel.h"
struct misStrctWindowSize
{
	int width;
	int height;
};

class misBaseRenderer;
class vtkWin32RenderWindowInteractor;



#pragma warning (push)
#pragma warning (disable : 4800)	 

igstkLoadedEventMacro(misWindwsSizeChangedEvent, misEvent, misStrctWindowSize);
itkEventMacro(misWindowsActivatedEvent, misEvent);

#pragma warning (pop)

class Iwindows
{
public:
	enum  ViewerType
	{
		DefaultBehaviour,
		ImageViewer,
		VolumeViewer,
		NoViewer
	};
	virtual void AddRenderer(misRenderer::Pointer renderer) = 0;
	virtual void CheckActivation(RECT &rc) const = 0;
	virtual void GenerateFormWindowModel(misWindowModel  model) = 0;
	virtual HWND get_m_Handle() const = 0;
	virtual void set_m_Handle(HWND left) = 0;
	virtual std::string get_m_Name() const = 0;
	virtual void set_m_Name(std::string left) = 0;
	virtual vtkRenderWindow* GetRenderWindow() = 0;
	virtual vtkSmartPointer<vtkRenderWindowInteractor> GetInterActor() = 0;
	virtual vtkSmartPointer<vtkRenderer> GetRenderer(int index) = 0;
	virtual HGLRC GetContextId() = 0;
	virtual int GetWindowIndex() const = 0;
	virtual void SetWindowIndex(int val) = 0;
	virtual int* GetRenderWindowSize() = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void Destroy() = 0;
	virtual int GenerateRenderWindow(ViewerType type, misViewPort viewport = misViewPort()) = 0;
	virtual misStrctWindowSize GetWindowSize() const = 0;
	virtual void Start() = 0;
	virtual  std::string GetParentTabName() const = 0;
	virtual  void SetParentTabName(std::string val) = 0;

	virtual std::string GetParentSubTabName() const = 0;
	virtual  void SetParentSubTabName(std::string val) = 0;
	virtual bool GetActive() const = 0;
	virtual void SetActive(bool val) = 0;
	virtual void SetProvidedWindowAsParent(bool value) = 0;
	virtual void MakeCurrent() = 0;
	virtual ~Iwindows()
	{

	}
};
