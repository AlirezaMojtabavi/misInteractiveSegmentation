#include "StdAfx.h"
#include "misStandardMatrix.h"

misStandardMatrix::misStandardMatrix(void)
{
}

misStandardMatrix::~misStandardMatrix(void)
{
}

vtkMatrix4x4* misStandardMatrix::GetTranformMatrix( misPatientPosition patientPosition )
{
	vtkMatrix4x4* outMatrix = vtkMatrix4x4::New(); 
	outMatrix->Identity();

	switch (patientPosition)
	{
	case HFS :
        outMatrix->Identity();
		break;

	case HFP :
		outMatrix->Identity();
		outMatrix->SetElement(0,0,-1);
		outMatrix->SetElement(1,1,-1);
		break;

	case FFS :
		outMatrix->Identity();
		outMatrix->SetElement(2,2,-1);
		break;

	case FFP :
		outMatrix->Identity();
		outMatrix->SetElement(0,0,-1);
		outMatrix->SetElement(1,1,-1);
		outMatrix->SetElement(2,2,-1);
		break;

	case HFDR :
		outMatrix->Identity();
		outMatrix->SetElement(0,0,0);
		outMatrix->SetElement(0,1,1);
		outMatrix->SetElement(1,0,-1);
		outMatrix->SetElement(1,1,0);
		break;

	case HFDL :
		outMatrix->Identity();
		outMatrix->SetElement(0,0,0);
		outMatrix->SetElement(0,1,-1);
		outMatrix->SetElement(1,0,1);
		outMatrix->SetElement(1,1,0);
		break;

	case FFDR :
		outMatrix->Identity();
		outMatrix->SetElement(0,0,0);
		outMatrix->SetElement(0,1,1);
		outMatrix->SetElement(1,0,-1);
		outMatrix->SetElement(1,1,0);
		outMatrix->SetElement(2,2,-1);
		break;

	case FFDL :
		outMatrix->Identity();
		outMatrix->SetElement(0,0,0);
		outMatrix->SetElement(0,1,-1);
		outMatrix->SetElement(1,0,1);
		outMatrix->SetElement(1,1,0);
		outMatrix->SetElement(2,2,-1);
		break;

	default:
       outMatrix->Identity();
	}

	return outMatrix;
}

vtkMatrix4x4* misStandardMatrix::GetInvTranformMatrix( misPatientPosition patientPosition )
{
  vtkMatrix4x4 *outMatrix, *priMatrix; 
  priMatrix = misStandardMatrix::GetTranformMatrix(patientPosition);
  
  outMatrix = vtkMatrix4x4::New();
  vtkMatrix4x4::Invert(priMatrix,outMatrix);

  return outMatrix;
}

bool misStandardMatrix::CompareTransform( vtkMatrix4x4* firstMatrix, vtkMatrix4x4* secondMatrix )
{
	//  return True if they are equal

	bool res = true;

	if ((!firstMatrix) || (!firstMatrix) )
	{
		res = false;
		return res;
	}

	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			double element1, element2;
			element1 = firstMatrix->GetElement(i,j) ;
			element2 = secondMatrix->GetElement(i,j) ;
			if ( element1 != element2 )
			{
				res = false;
				return res;
			}
		}
	}
	return res;
}