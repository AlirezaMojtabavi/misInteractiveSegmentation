#include "stdafx.h"
#include "..\Header\misDirectionStringConevrtor.h"


misDirectionStringConevrtor::misDirectionStringConevrtor()
{
	stringToDirection["AxialDirection"] = AxialDirection;
	directionToString[AxialDirection] = "AxialDirection";
	stringToDirection["CoronalDirection"] = CoronalDirection;
	directionToString[CoronalDirection] = "CoronalDirection";
	stringToDirection["SagittalDirection"] = SagittalDirection;
	directionToString[SagittalDirection] = "SagittalDirection";
	stringToDirection["ViewerSono"] = ViewerSono;
	directionToString[ViewerSono] = "ViewerSono";
	stringToDirection["Viewer3DSono"] = Viewer3DSono;
	directionToString[Viewer3DSono] = "Viewer3DSono";
	stringToDirection["Viewer2DSono"] = Viewer2DSono;
	directionToString[Viewer2DSono] = "Viewer2DSono";
	stringToDirection["PanormaicView"] = PanormaicView;
	directionToString[PanormaicView] = "PanormaicView";
	stringToDirection["UnSetDirection"] = UnSetDirection;
	directionToString[UnSetDirection] = "UnSetDirection";
	directionToString[Viewer3DLandmark] = "Viewer3DLandmark";
	stringToDirection["Viewer3DLandmark"] = Viewer3DLandmark;
	directionToString[Video] = "Video";
	stringToDirection["Video"] = Video;
}


misViewerTypeDirection misDirectionStringConevrtor::ConvertStringToDirection(std::string direction)
{
	return stringToDirection[direction];
}

std::string misDirectionStringConevrtor::ConvertDirectionToString(misViewerTypeDirection m_ViewerTypeDirection)
{
	return directionToString[m_ViewerTypeDirection];
}
