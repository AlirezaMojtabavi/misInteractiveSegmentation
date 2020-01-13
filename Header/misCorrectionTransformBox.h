#pragma once
#ifndef __MISBOXWIDGET__
#define __MISBOXWIDGET__


#include "ICorrectionTransformBox.h"
#include "misitkTypdef.h"

#define  misIncorrectSelectedFaceEvent 1002
#define  misSelectedFaceEvent 1001
#define  misTestBtnClickEvent 1003

class misROI;

// ComputeNormals create a box poly data for rendering textured plan and using a misBoxWidget for managing interactions for 
// correcting a transform by rotating a coefficient of 90 transforms

class misCorrectionTransformBox : public ICorrectionTransformBox
{

public:
	misCorrectionTransformBox();
	~misCorrectionTransformBox();

	void On();
	void Off();
	int  GetLastSelectedFaceID();
	void Reset();
	void UpdateFacesTexture();
	void UseDefaultFacesInformation();
	int GetDefalutCellID(misTextureEnum textureName);
	void InitilizeTransformCorrectionBox(vtkRenderWindowInteractor* interactor, vtkProp3D* VolumeRep, const misROI& roi);
	void AddActorToBoxWidget(vtkRenderWindowInteractor* interactor, vtkProp3D* VolumeRep, const misROI& roi);
	void UpdateOrientationCorrectionBox(vtkProp3D* VolumeRep, misROI roi);
	void UpdateBoxWidgetFacesInformation(misFaceInformation newFaceInformation);
	void ResetTexture();
	misFaceInformation GetFaceInformation1st() const;
	misFaceInformation GetFaceInformation2nd() const;
	void UpdateFaceSelection(misTextureEnum appliedTexture);
	vtkSmartPointer<vtkMatrix4x4> CalculatePrimeryMatrix();
	vtkSmartPointer<vtkMatrix4x4> CalculatedSecondryMatrix();
	bool GetSecondFaceIsSelected() const;
	faceInformationListTypdef GetFacesInformationApplied() const;
	virtual bool CheckNewFaceSelectedValidity();
	void SetAppliedFaceInformation(faceInformationListTypdef facesInformationApplied);
	void  SetBounding(double  bounds[6]);
	void SetVolume(vtkProp3D * volume);
	void SetInteractor(vtkRenderWindowInteractor* interactor);

private:

	double * GetFaceNormal(int cellId);
	void SetFacesInformationApplied(faceInformationListTypdef val);
	misTextureEnum GetDefaultTextureName(int cellID);
	misTextureEnum GetOppositeTexture(misTextureEnum text);
	int GetOppositeCellId(int CellId);
	void SetOutlineFaceWires(int newValue);
	virtual void PlaceWidget(double bounds[6]);
	void EnabledOn();
	void EnabledOff();
	void AddDefaultTexture();
	void SetEnabled(int enabling);
	misFloatPointsListTypdef  GetCoordinate(misTextureEnum Text);
	misFloatPointsListTypdef  GetCoordinateA();
	misFloatPointsListTypdef  GetCoordinateP();
	misFloatPointsListTypdef  GetCoordinateS();
	misFloatPointsListTypdef  GetCoordinateI();
	misFloatPointsListTypdef  GetCoordinateR();
	misFloatPointsListTypdef  GetCoordinateL();
	misFloatPointsListTypdef  GetCoordinateBlank();
	misFloatPointsListTypdef  GetCoordinateStrip();
	vtkFloatArray * m_pTextureCoordinates;
	int m_lastCellId;
	void ReadDefalutCubeTexture(void);
	void SetDefaultSelectedFace(int LastcellId);
	void AddTexture(misIntPointStrct pointstr, misFloatPointsListTypdef coordinateLst);
	misIntPointStrct GetFacePoints(int cellId);
	// Handles the events
	static void ProcessEvents(vtkObject* object,
		unsigned long event,
		void* clientdata,
		void* calldata);

	virtual void OnLeftButtonDown();
	int HighlightHandle(vtkProp *prop); //returns cell id
	void ComputeNormals();
	virtual void SizeHandles();
	void GetDirection(const double Nx[3], const double Ny[3],
		const double Nz[3], double dir[3]);
	void CreateDefaultProperties();
	void FillDefaultFaceInformation(void);
	void UpdateFacesTexture(int cellId);

	vtkSmartPointer<vtkFloatArray> ExtractCubeTextureCoordinate();

	void FillFaceTextureDefault(vtkFloatArray * pTextureCoordinates, int cellID);
	void FillFaceTexture(vtkFloatArray * pTextureCoordinates, int cellID, misTextureEnum textureName);
	void SetBlankTextureToAllFaces();
	bool m_FaceSelect;
	int m_ThirdSelectedId;
	int m_FaceSelectCounter;
	misTextureEnum m_FirstTexture;
	misTextureEnum m_SecondTexture;
	misTextureEnum m_ThirdTexture;
	vtkProp3D * m_volume;
	double m_bounds[6];
	vtkTexture * m_DefaultCubeTexture;
	vtkSmartPointer<vtkPolyData> m_HexPolyData;
	vtkSmartPointer<vtkPoints> m_Points;  //used by others as well
	double             N[6][3]; //the normals of the faces
	// A face of the hexahedron
	vtkActor          *HexFace;
	vtkPolyDataMapper *HexFaceMapper;
	vtkPolyData       *HexFacePolyData;

	// glyphs representing hot spots (e.g., handles)
	std::vector<vtkSmartPointer<vtkActor>> m_Handles;
	std::vector<vtkSmartPointer<vtkPolyDataMapper>> HandleMapper;
	std::vector<vtkSmartPointer<vtkSphereSource>>   HandleGeometry;
	// wireframe outline
	vtkActor          *HexOutline;
	vtkPolyDataMapper *OutlineMapper;
	vtkPolyData       *OutlinePolyData;
	vtkCellPicker *HandlePicker;
	vtkCellPicker *HexPicker;
	vtkSmartPointer<vtkActor> m_SelectedFaceActor;
	vtkSmartPointer<vtkRenderer> m_Renderer;
	vtkSmartPointer<vtkRenderWindowInteractor> m_Interactor;
	vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() const;

	vtkProperty *HandleProperty;
	vtkProperty *SelectedHandleProperty;
	vtkProperty *FaceProperty;
	vtkProperty *SelectedFaceProperty;
	vtkProperty *OutlineProperty;
	vtkProperty *SelectedOutlineProperty;
	vtkActor *m_HexActor;
	int m_CurrentHexFace;
	int InsideOut;
	int OutlineFaceWires;
	int OutlineCursorWires;
	void GenerateOutline();
	int TranslationEnabled;
	int ScalingEnabled;
	int RotationEnabled;
	faceInformationListTypdef m_FacesInformationDefault;
	faceInformationListTypdef m_FacesInformationApplied;
	misFaceInformation m_FaceInformation1st;
	misFaceInformation m_FaceInformation2nd;
	double LastPickPosition[3];
	bool m_Enabled;
	vtkCallbackCommand* m_CallBack;
	bool m_SecondFaceIsSelected;
};

#endif
