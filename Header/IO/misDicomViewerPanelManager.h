#pragma once

/*ref*/ class misDicomViewerPanelManager
{
public:
	misDicomViewerPanelManager(void *rendererWinPannel);
	void ShowImage(vtkImageData *imgData);
	void ResetContrast(vtkImageData *imgData);
private:
	vtkRenderWindow*			m_RenderWin;
	vtkImageViewer2*			m_ImageViewer2;
	vtkRenderWindowInteractor*	m_InteractorRenderer;
	vtkRenderer*				m_Renderer;
};

