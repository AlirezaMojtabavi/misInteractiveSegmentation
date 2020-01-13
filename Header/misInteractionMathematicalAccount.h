#pragma once

#define  STEPNUMBER  100;

typedef std::list<double> doubleListTypeDef;

struct misAngle
{
	double theta1;
	double thetha2;
	double phi1;
	double phi2;
};

class  misInteractionMathematicalAccount
{
public:

	 double stepsNumber;
	 //object
	 doubleListTypeDef FastSlowMotion();
	 vtkMatrix4x4 * RoundTransformElemnt(vtkMatrix4x4 * );
	 //-----------------------
	 //camera
	 misAngle accountantPhiAndTheta(double start[3],double end[3]);
	 //-----------------------

	misInteractionMathematicalAccount(void);
	~misInteractionMathematicalAccount(void);
};
