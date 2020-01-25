#pragma once
#include "misPlanarRepresentation.h"
#include "IPanImage.h"

class PanImage : public IPanImage
{
public:
	PanImage(std::shared_ptr<ICornerProperties> cornerproperties);
	void SetMainRepresentation(std::shared_ptr<misPlanarRepresentation>) override;
	void SetInteractor(vtkRenderWindowInteractor*) override;
 	void Pan()override;
private:
	std::shared_ptr<misPlanarRepresentation> m_MainRrepresenation;
	vtkRenderWindowInteractor* m_RenderWindowInteractor;
	boost::optional<int> m_LastMouseEventX;
	boost::optional<int> m_LastMouseEventY;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
};

