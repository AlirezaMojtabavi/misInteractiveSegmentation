#pragma once
#include "VisualizationGeneralTypes.h"

//this object makes a cube with six faces and 19 handles.
//each cube consists of 8 points that are located on vertexes. the handles are calculated based on the coordinates of these vertexes.
//suppose that the center of cube is (0 , 0 , 0), and bound of cube is [-1 , 1]. so, the vertexes are :

//(-0.5 , -0.5 , -0.5 ) -->point[0]
//(0.5 , -0.5 , -0.5 )  -->point[1]
//(0.5 , 0.5 , -0.5 )   -->point[2]
//(-0.5 , 0.5 , -0.5 )  -->point[3]
//(-0.5 , -0.5 , 0.5 )  -->point[4]
//(0.5 , -0.5 , 0.5 )   -->point[5]
//(0.5 , 0.5 , 0.5 )    -->point[6] 
//(-0.5 , 0.5 , 0.5 )   -->point[7]

//as it mentioned, cube has 19 handles. 6 of them is on the faces and 12 of them is on the edges and the last one is in center.
//handles are defined in PositionHandles() Function.in regard to vertexes the handles of faces are :
//(-0.5 , 0 , 0 )  -->point[8]    --> handles[0]
//(0.5 , 0 , 0 )   -->point[9]    --> handles[1]
//(0 , -0.5 , 0 )  -->point[10]  --> handles[2]
//(0 , 0.5 , 0 )   -->point[11]  --> handles[3]
//(0 , 0 , -0.5 )  -->point[12]  --> handles[4]
//(0 , 0 , 0.5)    -->point[13]  --> handles[5]

//the handle of the center is :
//(0 , 0 , 0)	  --> point [14] -->handles[6]

//and the handles of the edges are :
//(-0.5 , 0 , 0.5 )  -->point[15]    --> handles[7]
//(-0.5 , 0 , -0.5)  -->point[16]    --> handles[8]
//(0.5 , 0 , -0.5 )  -->point[17]    --> handles[9]
//(0.5 , 0 , 0.5 )  -->point[18]    --> handles[10]
//(0 , -0.5 , 0.5 )  -->point[19]    --> handles[11]
//(0 , -0.5 , -0.5 )  -->point[20]    --> handles[12]
//(0 , 0.5 , 0.5 )  -->point[21]    --> handles[13]
//(0 , 0.5 , -0.5 )  -->point[22]    --> handles[14]
//(-0.5 , 0.5 , 0 )  -->point[23]    --> handles[15]
//(-0.5 , -0.5 , 0 )  -->point[24]    --> handles[16]
//(0.5 , 0.5 , 0 )  -->point[25]    --> handles[17]
//(0.5 , -0.5 , 0 )  -->point[26]    --> handles[18]

//the handles are used for changing the size of cube.according to orientation , sutable functions are set to the handles in OnMouse() function. 
//in general, the functions which are set to handles of faces are fixed as follow:
//handles[0] --> MoveMinusXFace()
//handles[1] -->MovePlusXFace()
//handles[2] --> MoveMinusYFace()
//handles[3] -->MovePlusYFace()
//handles[4] --> MoveMinusZFace()
//handles[5] -->MovePlusZFace()

//in Axial Orientation :
//handles[7] and handles[8]  --> MoveMinusXFace()
//handles[9] and handles[10]  -->MovePlusXFace()
//handles[11] and handles[12]  --> MoveMinusYFace()
//handles[13] and handles[14]  -->MovePlusYFace()

//in Coronal Orientation : 
//handles[12] and handles[14]  --> MoveMinusZFace()
//handles[11] and handles[13]  -->MovePlusZFace()
//handles[15] and handles[16]  --> MoveMinusXFace()
//handles[17] and handles[18]  -->MovePlusXFace()

//in Sagittal Orientation :
//handles[8] and handles[10]  --> MoveMinusZFace()
//handles[7] and handles[9]  -->MovePlusZFace()
//handles[16] and handles[18]  --> MoveMinusYFace()
//handles[15] and handles[17]  -->MovePlusYFace()

//in visualization, some handles must be invisible based on orientation.
//in Axial Orientation :
//handles[15] , handles[16] , handles[17] , handles[18]
//in Coronal Orientation :
//handles[7] , handles[8] , handles[9] , handles[10]
//in Sagittal Orientation :
//handles[11] , handles[12] , handles[13] , handles[14]
////////////////////////////////////////////////////////////////////////////////

class misLogger;
class misROIWidget;
class vtkActor;
class vtkCellPicker;
class vtkPlanes;
class vtkPoints;
class vtkPolyData;
class vtkPolyDataMapper;
class vtkProp;
class vtkProperty;
class vtkSphereSource;
class vtkTransform;

class MyCallback : public vtkCommand
{
public:

	misROIWidget*   ROIwidget;
	static MyCallback *New() 
	{ return new MyCallback; }
	virtual void Execute(vtkObject *caller, unsigned long, void*);
};

#define AXIAL_LEFT_FRONT	 7
#define AXIAL_LEFT_BACK		 8
#define AXIAL_RIGHT_FRONT	 9
#define AXIAL_RIGHT_BACK	 10
#define AXIAL_BOTTOM_FRONT	 11
#define AXIAL_BOTTOM_BACK	 12
#define AXIAL_UP_FRONT		 13
#define AXIAL_Up_BACK		 14
#define AXIAL_FACE_FRONT     5
#define AXIAL_FACE_BACK      4

#define CORONAL_LEFT_FRONT	 15
#define CORONAL_LEFT_BACK	 16
#define CORONAL_RIGHT_FRONT	 17
#define CORONAL_RIGHT_BACK	 18
#define CORONAL_BOTTOM_FRONT 11
#define CORONAL_BOTTOM_BACK	 13
#define CORONAL_UP_FRONT	 12
#define CORONAL_Up_BACK		 14
#define CORONAL_FACE_FRONT   2
#define CORONAL_FACE_BACK    3

#define SAGITTAL_LEFT_FRONT	 16
#define SAGITTAL_LEFT_BACK	 8
#define SAGITTAL_RIGHT_FRONT 15
#define SAGITTAL_RIGHT_BACK	 17
#define SAGITTAL_BOTTOM_FRONT 7
#define SAGITTAL_BOTTOM_BACK 9
#define SAGITTAL_UP_FRONT	 8
#define SAGITTAL_Up_BACK	 10
#define SAGITTAL_FACE_FRONT  0
#define SAGITTAL_FACE_BACK    1

#define  misROIWidgetChangeEvent  vtkCommand::UserEvent+100
class  misROIWidget : public vtkBoxWidget
{
	const int numberOfHandel = 19;
public:
  // Description:
  // Instantiate the object.
	static misROIWidget *New(void);
  
  vtkPoints         *Points;  //used by others as well
  
//  vtkTypeRevisionMacro(misROIWidget,vtkBoxWidget);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  vtkPoints* GetPoints();
  double * GetCompressData(vtkPoints* p);
  void SetPoints(vtkPoints *p);

  // Description:
  // Methods that satisfy the superclass' API.
  virtual void SetEnabled(int);
  void On();
  void Off();
  virtual void PlaceWidget(double bounds[6]);
  void PlaceWidget()
	{this->Superclass::PlaceWidget();}
  void PlaceWidget(double xmin, double xmax, double ymin, double ymax, 
				   double zmin, double zmax)
	{this->Superclass::PlaceWidget(xmin,xmax,ymin,ymax,zmin,zmax);}

  // Description:
  // Get the planes describing the implicit function defined by the box
  // widget. The user must provide the instance of the class vtkPlanes. Note
  // that vtkPlanes is a subclass of vtkImplicitFunction, meaning that it can
  // be used by a variety of filters to perform clipping, cutting, and
  // selection of data.  (The direction of the normals of the planes can be
  // reversed enabling the InsideOut flag.)
  void GetPlanes(vtkPlanes *planes);

  // Description:
  // Set/Get the InsideOut flag. When off, the normals point out of the
  // box. When on, the normals point into the hexahedron.  InsideOut
  // is off by default.
  vtkSetMacro(InsideOut,int);
  vtkGetMacro(InsideOut,int);
  vtkBooleanMacro(InsideOut,int);

  // Description:
  // Retrieve a linear transform characterizing the transformation of the
  // box. Note that the transformation is relative to where PlaceWidget
  // was initially called. This method modifies the transform provided. The
  // transform can be used to control the position of vtkProp3D's, as well as
  // other transformation operations (e.g., vtkTranformPolyData).
  virtual void GetTransform(vtkTransform *t);

  // Description:
  // Set the position, scale and orientation of the box widget using the
  // transform specified. Note that the transformation is relative to 
  // where PlaceWidget was initially called (i.e., the original bounding
  // box). 
  virtual void SetTransform(vtkTransform* t);

  // Description:
  // Grab the polydata (including points) that define the box widget. The
  // polydata consists of 6 quadrilateral faces and 15 points. The first
  // eight points define the eight corner vertices; the next six define the
  // -x,+x, -y,+y, -z,+z face points; and the final point (the 15th out of 15
  // points) defines the center of the hexahedron. These point values are
  // guaranteed to be up-to-date when either the InteractionEvent or
  // EndInteractionEvent events are invoked. The user provides the
  // vtkPolyData and the points and cells are added to it.
  void GetPolyData(vtkPolyData *pd);

  // Description:
  // Get the handle properties (the little balls are the handles). The 
  // properties of the handles when selected and normal can be 
  // set.
  vtkGetObjectMacro(HandleProperty,vtkProperty);
  vtkGetObjectMacro(SelectedHandleProperty,vtkProperty);

  // Description:
  // Switches handles (the spheres) on or off by manipulating the actor
  // visibility.
  void HandlesOn();
  void HandlesOff();
  void OneHandleOff(int);
  void SetBoxDeactive();
  void SetBoxActive();
  
  // Description:
  // Get the face properties (the faces of the box). The 
  // properties of the face when selected and normal can be 
  // set.
  vtkGetObjectMacro(FaceProperty,vtkProperty);
  vtkGetObjectMacro(SelectedFaceProperty,vtkProperty);
  
  // Description:
  // Get the outline properties (the outline of the box). The 
  // properties of the outline when selected and normal can be 
  // set.
  vtkGetObjectMacro(OutlineProperty,vtkProperty);
  vtkGetObjectMacro(SelectedOutlineProperty,vtkProperty);
  
  // Description:
  // Control the representation of the outline. This flag enables
  // face wires. By default face wires are off.
  void SetOutlineFaceWires(int);
  vtkGetMacro(OutlineFaceWires,int);
  void OutlineFaceWiresOn();
  void OutlineFaceWiresOff();

  // Description:
  // Control the representation of the outline. This flag enables
  // the cursor lines running between the handles. By default cursor
  // wires are on.
  void SetOutlineCursorWires(int);
  vtkGetMacro(OutlineCursorWires,int);
  void OutlineCursorWiresOn() {this->SetOutlineCursorWires(1);}
  void OutlineCursorWiresOff() {this->SetOutlineCursorWires(0);}

  // Description:
  // Control the behavior of the widget. Translation, rotation, and
  // scaling can all be enabled and disabled.
  vtkSetMacro(TranslationEnabled,int);
  vtkGetMacro(TranslationEnabled,int);
  vtkBooleanMacro(TranslationEnabled,int);
  vtkSetMacro(ScalingEnabled,int);
  vtkGetMacro(ScalingEnabled,int);
  vtkBooleanMacro(ScalingEnabled,int);
  vtkSetMacro(RotationEnabled,int);
  vtkGetMacro(RotationEnabled,int);
  vtkBooleanMacro(RotationEnabled,int);
   //int Enabled;
   //BTX - manage the state of the widget
   int State;
   enum WidgetState
   {
	   Start=0,
	   Moving,
	   Scaling,
	   Outside
   };
   //ETX

   void SetOrientation(IMAGEORIENTATION orientation);
   IMAGEORIENTATION GetOrientation();
   double GetHandlePosition();	//return the  staple value of each face in axial, sagittal and coronal-->for visibility check!
   double GetThirdDimensionValue();
   void UpdateWidgetData();

   bool m_Activate;
   int m_centerTranslate[2];
   int m_cornerHandle[2];
   int m_edgeHandle[8];
	
protected:
  misROIWidget();
  ~misROIWidget();
  IMAGEORIENTATION m_orientation;

	
  // Handles the events
  static void ProcessEvents(vtkObject* object, 
							unsigned long event,
							void* clientdata, 
							void* calldata);

  // ProcessEvents() dispatches to these methods.
  virtual void OnMouseMove();
  virtual void OnLeftButtonDown();
  virtual void OnLeftButtonUp();
  virtual void OnMiddleButtonDown();
  virtual void OnMiddleButtonUp();
  virtual void OnRightButtonDown();
  virtual void OnRightButtonUp();
  
  // the hexahedron (6 faces)
  vtkActor          *HexActor;
  vtkPolyDataMapper *HexMapper;
  vtkPolyData       *HexPolyData;
//  misSeedViewer *m_seedViewer;
  double             N[6][3]; //the normals of the faces

  // A face of the hexahedron
  vtkActor          *HexFace;
  vtkPolyDataMapper *HexFaceMapper;
  vtkPolyData       *HexFacePolyData;

  // glyphs representing hot spots (e.g., handles)
  std::vector<vtkSmartPointer<vtkActor>>  m_SphereHandles;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> m_SphereHandlesMapper;
  std::vector<vtkSmartPointer<vtkSphereSource>>    m_SphereHandlesGeometry;
  virtual void PositionHandles();
  int HighlightHandle(vtkProp *prop); //returns cell id
  void HighlightFace(int cellId);
  void HighlightOutline(int highlight);
  void ComputeNormals();
  virtual void SizeHandles();
  
  // wireframe outline
  vtkActor          *HexOutline;
  vtkSmartPointer<vtkPolyDataMapper> OutlineMapper;
  vtkPolyData       *OutlinePolyData;

  // Do the picking
  vtkCellPicker *HandlePicker;
  vtkCellPicker *HexPicker;
  vtkActor *CurrentHandle;
  int      CurrentHexFace;
  
  // Methods to manipulate the hexahedron.
  virtual void Translate(double *p1, double *p2);
  virtual void Scale(double *p1, double *p2, int X, int Y);
  virtual void Rotate(int X, int Y, double *p1, double *p2, double *vpn);
  void MovePlusXFace(double *p1, double *p2);
  void MoveMinusXFace(double *p1, double *p2);
  void MovePlusYFace(double *p1, double *p2);
  void MoveMinusYFace(double *p1, double *p2);
  void MovePlusZFace(double *p1, double *p2);
  void MoveMinusZFace(double *p1, double *p2);

  //"dir" is the direction in which the face can be moved i.e. the axis passing
  //through the center
  void MoveFace(double *p1, double *p2, double *dir, 
				double *x1, double *x2, double *x3, double *x4,
				double *x5);
  //Helper method to obtain the direction in which the face is to be moved.
  //Handles special cases where some of the scale factors are 0.
  void GetDirection(const double Nx[3],const double Ny[3], 
					const double Nz[3], double dir[3]);

  // Transform the hexahedral points (used for rotations)
  vtkTransform *Transform;
  
  // Properties used to control the appearance of selected objects and
  // the manipulator in general.
  vtkProperty *HandleProperty;
  vtkProperty *SelectedHandleProperty;
  vtkProperty *FaceProperty;
  vtkProperty *SelectedFaceProperty;
  vtkProperty *OutlineProperty;
  vtkProperty *SelectedOutlineProperty;
  vtkProperty *DeactivedOutLineProperty;
  void CreateDefaultProperties();
  
  // Control the orientation of the normals
  int InsideOut;
  int OutlineFaceWires;
  int OutlineCursorWires;
  void GenerateOutline();
  
  // Control whether scaling, rotation, and translation are supported
  int TranslationEnabled;
  int ScalingEnabled;
  int RotationEnabled;
  std::map<int, int> m_HandleFaceMap;
private:
  misROIWidget(const misROIWidget&);  //Not implemented

  vtkSmartPointer<vtkCellArray> CreateBoxCell();

  void operator=(const misROIWidget&);  //Not implemented


  
};

