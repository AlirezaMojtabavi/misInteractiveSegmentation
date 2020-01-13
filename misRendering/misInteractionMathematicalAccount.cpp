#include "stdafx.h"
#include "misInteractionMathematicalAccount.h"

misInteractionMathematicalAccount::misInteractionMathematicalAccount(void)
{
	this->stepsNumber=STEPNUMBER  ;
}

misInteractionMathematicalAccount::~misInteractionMathematicalAccount(void)
{
}
//////////-------------    Object  ----------------///////////

doubleListTypeDef misInteractionMathematicalAccount::FastSlowMotion()
{
	//--------------------
	double start =  -(vtkMath::Pi())/2.5;
	double stop  = -1 * start ; 
	double step=(stop-start)/this->stepsNumber;
	//--------------------
	double theta=start;
	double currentPoint;
	double distance=0, sumdis=0, nordis=0,sumnor=0;
	int n = static_cast<int>(stepsNumber);
	double pointarray[100];
	//----------------------
	for (int i=0; i<n;i++)
	{
		theta+=step;
		if (theta==stop)
		{
			break;
		}
		currentPoint =pow(sin(theta),1);
		pointarray[i]=currentPoint;
	}
	//-----------------------
	doubleListTypeDef distanceList;
	for (int j=1; j<n;j++)
	{
		double d=(pointarray[j]-pointarray[j-1]);
		distance=pow(d,3);
		sumdis+=distance;
		distanceList.push_front(distance);
	}
	//-------------------------
	doubleListTypeDef returnList;
	doubleListTypeDef::iterator ret_iter;
	double dis;
	for (ret_iter=distanceList.begin();ret_iter!=distanceList.end();ret_iter++)
	{
		dis=*(ret_iter);
		nordis=dis/sumdis;
		sumnor+=nordis;
		returnList.push_front(nordis);
	}
	//----------------------------
	return returnList;
  
}
//-------------------------
vtkMatrix4x4 * misInteractionMathematicalAccount::RoundTransformElemnt( vtkMatrix4x4 * inMatrix )
{
	inMatrix->SetElement(0,0,vtkMath::Round(inMatrix->GetElement(0,0)));
	inMatrix->SetElement(0,1,vtkMath::Round(inMatrix->GetElement(0,1)));
	inMatrix->SetElement(0,2,vtkMath::Round(inMatrix->GetElement(0,2)));
	inMatrix->SetElement(0,3,vtkMath::Round(inMatrix->GetElement(0,3)));

	inMatrix->SetElement(1,0,vtkMath::Round(inMatrix->GetElement(1,0)));
	inMatrix->SetElement(1,1,vtkMath::Round(inMatrix->GetElement(1,1)));
	inMatrix->SetElement(1,2,vtkMath::Round(inMatrix->GetElement(1,2)));
	inMatrix->SetElement(1,3,vtkMath::Round(inMatrix->GetElement(1,3)));

	inMatrix->SetElement(2,0,vtkMath::Round(inMatrix->GetElement(2,0)));
	inMatrix->SetElement(2,1,vtkMath::Round(inMatrix->GetElement(2,1)));
	inMatrix->SetElement(2,2,vtkMath::Round(inMatrix->GetElement(2,2)));
	inMatrix->SetElement(2,3,vtkMath::Round(inMatrix->GetElement(2,3)));

	inMatrix->SetElement(3,0,vtkMath::Round(inMatrix->GetElement(3,0)));
	inMatrix->SetElement(3,1,vtkMath::Round(inMatrix->GetElement(3,1)));
	inMatrix->SetElement(3,2,vtkMath::Round(inMatrix->GetElement(3,2)));
	inMatrix->SetElement(3,3,vtkMath::Round(inMatrix->GetElement(3,3)));

	return inMatrix;
}

misAngle misInteractionMathematicalAccount::accountantPhiAndTheta( double start[3],double end[3] )
{
	double theta1,theta2;
	double phi1,phi2;
	// angle between vector and z axis
	theta1=acos(start[2]/(sqrt(pow(start[0],2)+pow(start[1],2)+pow(start[2],2))));
	theta2=acos(end[2]/(sqrt(pow(end[0],2)+pow(end[1],2)+pow(end[2],2))));

	//if (startPoint[0]>=0)
	//{
	//	phi1=asin(startPoint[1]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2))));
	//}
	//else if (startPoint[0]<0)
	//{
	//	phi1=asin(startPoint[1]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2))))+vtkMath::Pi();
	//}
	////---------------------		
	//if (endPoint[0]>=0)
	//{
	//	phi2=asin(endPoint[1]/(sqrt(pow(endPoint[0],2)+pow(endPoint[1],2))));
	//}
	//else if (endPoint[0]<0)
	//{
	//	phi2=asin(endPoint[1]/(sqrt(pow(endPoint[0],2)+pow(endPoint[1],2))))+ vtkMath::Pi();
	//}
	//phi1=asin(startPoint[1]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2))));
	//phi2=asin(endPoint[1]/(sqrt(pow(endPoint[0],2)+pow(endPoint[1],2))));


	if (start[0]==0)
	{
		if(start[1]>0)	
		{
			phi1=vtkMath::Pi()/2;
		}
		else
		{
			phi1=-vtkMath::Pi()/2;
		}
	}
	else if (start[0]<0)
	{
		if (start[1]>=0)
		{
			phi1=atan(start[1]/start[0])+ vtkMath::Pi();

		}
		else if(start[1]<0)
		{
			phi1=atan(start[1]/start[0])- vtkMath::Pi();

		}
	}
	else if (start[0]>0)
	{
		phi1=atan(start[1]/start[0]);
	}
	//*----------------------------	
	if (end[0]==0)
	{
		if(end[1]>0)	
		{
			phi2=vtkMath::Pi()/2;
		}
		else
		{
			phi2=-vtkMath::Pi()/2;
		}
	}
	else if (end[0]<0)
	{
		if (end[1]>=0)
		{
			phi2=atan(end[1]/end[0])+ vtkMath::Pi();
		}
		else if(end[1]<0)
		{
			phi2=atan(end[1]/end[0])- vtkMath::Pi();
		}
	}
	else if(end[0]>0)
	{
		phi2=atan(end[1]/end[0]);
	}
	
	misAngle angleStr;
	angleStr.theta1=theta1;
	angleStr.thetha2=theta2;
	angleStr.phi1=phi1;
	angleStr.phi2=phi2;

	return angleStr;

	//phiDistance2vector=(phi2-phi1);
	//thetaDistance2Vector=(theta2-theta1);

	//phiPart=phiDistance2vector/this->stepsNumber;
	//thetaPart=thetaDistance2Vector/this->stepsNumber;

	//tempPhi=phi1;
	//tempTheta=theta1;

}
