#pragma once

//Advanced, Normal, BiopsyRobot,  Spine, Unkwnon
enum misApplicationType
{
	Normal,
	Advanced,
	ENT,
	NeroSurgery,
	Biopsy,
	Spine,
	CMF,
	Dental,
	AnimalImaging,
	Unkwnon
};//Notice:Syncronize with clr enum misWorkFlowButtonSet

enum GenderEnum
{
	female = 1,
	male,
	undefined
};

enum misPatientPosition
{
	HFS = 0, //= Head-First Supine
	HFP, //= Head-First Prone
	FFP, //= Feet-First Prone
	FFS, //= Feet-First Supine
	HFDR, //= Head-First Decubitus Right
	HFDL, //= Head-First Decubitus Left
	FFDR, //= Feet-First Decubitus Right
	FFDL, //= Feet-First Decubitus Left
	UserDefinedpatientPosition,
	UnKnownPatientPosition,
};

enum ParityType
{
	NoParity = 'N',
	OddParity = 'O',
	EvenParity = 'E'
};

enum misCursorType
{
	CompleteCursor = 0,
	SimpleCursor,
	PreciseCursor,
	ThickCursorSize1,
	ThickCursorSize2,
	ThickCursorSize3,
	NoCursor
};

enum misZoomState
{
	ResetZoom = 0,
	ZoomIn,
	ZoomOut
};

enum misSaveSolutionMode
{
	saveSolutionComplete = 0,
	saveSolutionModifiedParts,
	saveSolutionToExport_Import
};

enum  MisObjectType
{
	misImageType = 0,
	misPolyDataType,
	misVolumeDataType,
	misHybridPackageType,
	misCompositePackageType,
	misImageAnalysisType,
	misImageByteAnalysisType,
	misImageContainedPolydataType,
	misPlanDataType,
	misPlanDataGeneralType,
	misScrewPlanDataType,
	General,
	misUnKnowObjectType,
};

enum misRegistationStatus
{
	NoRegistartion,
	landmarkBasedRegistration,
	surfaceBasedRegistration
};

enum  ImageListViewingType
{
	Complete = 0,
	OnlyConfirmedDirection
};


enum ImageColorTableType
{
	GrayScaleImage,
	BoneColorMapType,
	GEColorMapType,
	HotColorMapType,
	UnkownColorTable
};

enum misImageViewingType
{
	CustomViewingType,
	CTAbdomen,
	CTLung,
	CTTumor,
	CTBone,
	CTBrain,
	CTPelvis,
	CTMediastinum,
	CTPossteriorFossa,
	CTCerebrum,
	CTChest,
	CTBrainSoftTissue,
	CTSpineSoftTissue,
	USLowContrast,
	MRGeneralT1,
	MRGeneralT2,
	UnKnownViewingType
};

enum PlanningPointType
{
	None = 0,
	TragetPoint = 10,
	EntryPoint,
	ScrewStartPoint,
	ScrewEndPoint
};

enum misGeneralToolbarState
{
	INITIALSTATE = -1,
	PANSTATE = 0,
	ZOOMSTATE,
	CONTRASTSTATE,
	MEASURMENTSTATE,
	SNAPSHOTSTATE
};

enum misImageStatus
{
	Regular,
	HeadRestRemoved
};

enum misRGObjectType
{
	misBackground = 0,
	misMarginalRegion = 80,
	misObjectBorder = 160,
	misSegmentedObject = 250,
	unKownObjectType = -1
};

enum misImageCorreltionType
{
	// If the result compute by image to image correlation the type is misDirectCalculatedCorrelation
	//  if we compute the corr. between 1-2 and 1-3, the corr between 2-3 could be estimated
	misDirectCalculatedCorrelation,
	misEstimatedCorrelation,
	misUnsetCorrelationType
};

enum misCorrelationPatternOverlay
{
	Uniform,
	CheckBoard
};

enum misCorrelationWarningState
{
	Init = 0,
	ImageLoaded,
	DuringCorrelation,
	AfterCorrelation,
	DenyCorrelation,
	AcceptCorrelation,
};

enum misImageWithDifficultiesForUploadingEnum
{
	DiffrentPatientUID,
	WrongImageComponent,
	wrongImageNumberForUploading,
	InsufficientImageSpacing,
	InAcceptedImageProblem,
	wrongScalerRange,
	NoProblemInImage
};

typedef std::vector<misImageWithDifficultiesForUploadingEnum> misImgeProblemList;

enum misCorrelationImageType
{
	FixedImage,
	MovingImage,
	FixedAndMoving,
	UnSetImageType
};

enum misRegistrationMode
{
	Automatic,
	Manual,
	FreeFusion
};

enum misTreeViewType
{
	PackageItem,
	ImagesItem,
	ImageItem,
	ModelsItem,
	PolydataItem,
	PlansItem,
	PlanItem,
	UnSetItem
};

enum misPresentationDimension
{
	twoDimension,
	threeDimension
};

enum AppMode
{
	RunNormal,
	Profiling,
	Testing
};

enum ColormapTypes
{
	AnimalImagingColormap,
	DentalColormap,
	OtherColormap
};

enum Dimention
{
	_2D,
	_3D
};