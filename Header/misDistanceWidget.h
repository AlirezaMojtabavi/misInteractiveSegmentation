#ifndef __misDistanceWidget_h
#define __misDistanceWidget_h

#include "VisualizationGeneralTypes.h"

class vtkDistanceRepresentation;
class vtkHandleWidget;
class misDistanceWidgetCallback;


class misDistanceWidget : public vtkDistanceWidget
{
public:
  // Description:
  // Instantiate this class.
  static misDistanceWidget *New();

 
  
  // Description:
  // Create the default widget representation if one is not set.
  void CreateDefaultRepresentation();
  void SetAutoPoint1(double pos[3]);
  void GetAutoPoint1(double pos[3]);
  void SetMeasurmentMode(MEASURMENTMODE type);
  void SetImageOrientation(IMAGEORIENTATION);
  IMAGEORIENTATION GetImageOrientation();
  void init();

 
protected:
  misDistanceWidget();
  ~misDistanceWidget();

  // The state of the widget
//BTX
  enum {Start=0,Define,Manipulate};
//ETX
  int WidgetState;
  int CurrentHandle;
   double AutoPoint1[3];

  MEASURMENTMODE m_MeasurmentMode; //auto:1/normal:0
  IMAGEORIENTATION m_Orientation;
  

  misDistanceWidgetCallback *DistanceWidgetCallback1;
  misDistanceWidgetCallback *DistanceWidgetCallback2;
  // Callback interface to capture events when
  // placing the widget.
  static void AddPointAction(vtkAbstractWidget*);
  static void MoveAction(vtkAbstractWidget*);
  static void EndSelectAction(vtkAbstractWidget*);

  //// The positioning handle widgets
  //vtkHandleWidget *Point1Widget;
  //vtkHandleWidget *Point2Widget;
  //misDistanceWidgetCallback *DistanceWidgetCallback1;
  //misDistanceWidgetCallback *DistanceWidgetCallback2;

  //// Methods invoked when the handles at the
  //// end points of the widget are manipulated
  void StartDistanceInteraction(int handleNum);
  void DistanceInteraction(int handleNum);
  void EndDistanceInteraction(int handleNum);
  MEASURMENTMODE GetMeasurmentMode();
 

//BTX
   friend class misDistanceWidgetCallback;
//ETX

private:
  
  misDistanceWidget(const misDistanceWidget&);  //Not implemented
  void operator=(const misDistanceWidget&);  //Not implemented
};

#endif
