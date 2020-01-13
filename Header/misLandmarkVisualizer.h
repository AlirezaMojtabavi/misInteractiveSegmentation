#pragma once
#include "IRepresentation.h"
#include "ILandmarkPointerRepresentation.h"
#include "misCamera.h"
#include "BusinessEntities\Point.h"
#include "misViewerTypeDirection.h"
#include "LandmarkLablePositionCalculator.h"

class misLandmarkVisualizer
{
public:
	typedef std::vector<std::shared_ptr<ILandmarkPointerRepresentation>> LandmarkListType;

	misLandmarkVisualizer(itk::BoundingBox<double, 3, double>::Pointer bounding, misCamera camera,
		LandmarkListType& landMarkList, misLandmarkType category,
		LANDMARKLABLETYPE lableType, bool showLabel, parcast::Point<double, 3> position,
		misViewerTypeDirection const& viewerDirection, double labelRadius);

	void CreateRepresentation(double labelRadius);
	void CalculateIndexes(int &index, int &HitCounter);
	std::shared_ptr<IRepresentation> GetRepresenTation();

	int GetIndex() const;
private:

	itk::BoundingBox<double, 3, double>::Pointer m_BoundingBox;
	misCamera m_Camera;
	LandmarkListType& m_landMarkList;
	misLandmarkType m_Category;
	LANDMARKLABLETYPE m_LableType;
	bool m_ShowLabel = true;
	parcast::Point<double, 3> m_Position;
	std::shared_ptr<ILandmarkPointerRepresentation> m_Representation;
	int m_Index = -1;
	std::unique_ptr<parcast::LandmarkLablePositionCalculator> m_LandmarkPositionCalculator;
	misViewerTypeDirection m_ViewerDirection;
};

