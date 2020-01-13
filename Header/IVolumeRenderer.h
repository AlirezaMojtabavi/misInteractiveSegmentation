#pragma once
#include "IRepresentation.h"
#include "I3DViewer.h"
#include "VisualizationGeneralTypes.h"
#include "ICornerProperties.h"
#include "misLandmarkenums.h"
#include "ICursorService.h"
#include "IScrewCompound.h"
#include "ILandmarkPointerRepresentation.h"
#include "ITransform.h"

class IVolumeRenderer
{
public:
	typedef std::vector < std::shared_ptr < ILandmarkPointerRepresentation >> LandmarkListType;

	virtual void SetMainRepresentation(std::shared_ptr<IRepresentation> pMainRep, IMAGEORIENTATION) = 0;
	virtual void Reset() = 0;
	virtual void MakeCurrentRenderer() = 0;
	virtual void InitializeWidget(misCursorType widgetType, double pickingTolerance) = 0;
	virtual std::shared_ptr<I3DViewer> Get3DViewer() const = 0;
	virtual std::shared_ptr<ICornerProperties> GetCornerProperties() const = 0;
	virtual void RemoveRepresentationByName(std::string name) = 0;
	virtual void SetCurrentLandmarkType(misLandmarkType val) = 0;
	virtual void RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent) = 0;
	virtual void HideLandmarks() = 0;
	virtual void SetViewPort(const misViewPort& val) = 0;
	virtual void SetShowManModel(bool val) = 0;
	virtual void Render() = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual std::shared_ptr<ICursorService> GetCursorService() = 0;
	virtual void ResetLandMarks(void) = 0;
	virtual void ResetLandMarks(misLandmarkType lndType) = 0;
	virtual void InvalidateLandmark(int index) = 0;
	virtual void SetCurrentLandmark(misLandmarkType val, int index) = 0;
	virtual void SetCurrentLandmarkLableType(LANDMARKLABLETYPE val) = 0;
	// Processes the received event and responds accordingly.
	virtual bool ProcessRequest(const itk::EventObject* event) = 0;
	virtual void SetDentalSurgeryType(DentalSurgeryType surgeryType) = 0;
	virtual void DeleteScrew(misUID screwUID) = 0;
	virtual void HighlightScrew(misUID screwUID, bool highlight) = 0;
	virtual void DeleteAllScrews() = 0;
	virtual void OnScrew(misUID screwUID) = 0;
	virtual void OffScrew(misUID screwUID) = 0;
	virtual void RemoveAllScrewServices() = 0;
	virtual void InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation) = 0;

	virtual misViewerTypeDirection GetTypeDirection(void) const = 0;
	virtual void AddLandmark(int index, const double position[3], misLandmarkType category = GeneralSeed,
		LANDMARKLABLETYPE lableType = NUMERICALLANDMARK) = 0;
	virtual std::shared_ptr<IScrewCompound> GetScrewWidgetService(misUID uid) = 0;
	virtual void SetROI(misROI data) = 0;
	virtual void ResetROI() = 0;
	virtual void ROIWidgetActivation(bool activation) = 0;
	virtual void SetDentalSpecialViewsEnable(bool enabled) = 0;
	virtual void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter) = 0;
	virtual void SetCaptureLandmarkFlag(bool val) = 0;
	virtual void SetCurrentLandmarkIndex(int val) = 0;
	virtual void SetUpdateLandmarkFlag(bool val) = 0;

	// Remove all landmark representations from rendering scene
	virtual void RemoveLandMarkRepresentations() = 0;
	virtual vtkRenderer* GetRenderer() = 0;
	virtual int	AddNextLandmark(const double position[3], misLandmarkType category = GeneralSeed,
		LANDMARKLABLETYPE lableType = NUMERICALLANDMARK) = 0;

	// Once upon a time these two methods were made virtual because a subclass (ImageViewer) has methods of the same signature.
	// This proved to be a fatal mistake. The subclass defined methods are entirely different methods which only happen to have the
	// same name!!! Be warned!
	virtual LandmarkListType GetLandmarkList(void) = 0;
	virtual misSimplePointListType GetLandmarkList(misLandmarkType seedType /*= seedCatergory::GeneralSeed*/) = 0;
	virtual void SetToolPosition(double xCoord, double yCoord, double zCoord) = 0;	//double *GetBounds();
	virtual bool HasRepresentationByName(const std::string& name) = 0;
	virtual void SetToolTransform(std::shared_ptr<ITransform> transform) = 0;
	virtual void AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation) = 0;
	virtual void AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer) = 0;
	virtual std::shared_ptr<Iwindows> GetWindow() const = 0;	// Gets the render window = 0.
	virtual void SetState(int val) = 0;
	virtual void UpdateWindowSize(misStrctWindowSize &size) = 0;
	virtual double*	GetLandmarkPosition(int index, misLandmarkType category) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual double*	GetLandmarkPosition(int index) = 0;
	virtual std::shared_ptr<IRepresentation>  GetMainRepresentation() = 0;
	virtual void SetObliqueFlag(bool isOblique) = 0;
	virtual ~IVolumeRenderer() = default;
};
