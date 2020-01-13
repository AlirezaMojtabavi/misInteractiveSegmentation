#pragma once

#include "misInteractionMathematicalAccount.h"

struct misPositionStr
{
	double XPoint;
	double YPoint;
	double ZPoint;
};

typedef std::list<misPositionStr>   CameraLineListTypedef;
typedef std::list<misPositionStr>   PositionListTypedef;

//enum mismoveMode
//{
//	Linear
//
//
//};
//enum misMoveKind
//{
//	Circle,
//	Line
//};
//
class    misIntractionCameraStyle
{
private:

	double m_cameraPosition[3];
	double m_focalPoint[3];
	double m_stepsNumber;

	double m_phiPart;
	double m_thetaPart;
	double m_tempPhi;
	double m_tempTheta;

	double m_tempPoint[3];

	double m_cameraViewUp[3];
	double m_ScaleCameraPosition;

	//void accountantPhiAndTheta(double startPoint[3],double endPoint[3]);

	vtkRenderer* render;

public:
	double m_endViewUp[3];
	double m_endPoint[3];
	double m_radius;
	double m_StartPoint[3];

	void SetRender(vtkRenderer*);

	void SetFocalPoint(double *);
	double GetFocalPoint();

	void   SetCameraPosition(double *);
	double GetCameraPosition();
	void   SetScaleCameraPosition(double  scaleCameraPosition);
	double GetScaleCameraPosition(void);

	//virtual void Rotate();
	//void Rotate();

	void Azimuth(double);
	void Elevation(double);
	void FlyINCamera();
	void SetPhiTheta(misAngle);
	void GetCurrentPoint();

	//void AnteriorView();
	//void PosteriorView();
	//void InferiorView();
	//void SupriorView();
	//void LleftView();
	//void RRightView();

	void CameraXPoint2(){}
	void CameraYPoint2(){}
	void CameraZPoint2(){}

	void accountantRadius(double*);
	PositionListTypedef NextPointLocateList();

	CameraLineListTypedef ComputeCameraLinerPointList(double start[3], double end[3]);
	//		void CameraMove(misMoveKind);
	void CameraLineMove();

	void PageUPCamera();
	void PageDownCamera();
	void UPCamera();
	void DownCamera();
	void RightCamera();
	void LeftCamera();

	//--------------------------
	misIntractionCameraStyle(void);
	~misIntractionCameraStyle(void);
};
