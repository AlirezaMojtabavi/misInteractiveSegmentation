#pragma once
#include "vtkMatrix4x4.h"
#include "misTransformEquality.h"
#include "matrix.h"
#include "vector.h"
class misRemoveRollFromRotationMatrix
{

private:
	vtkMatrix4x4* GetRotatedMatrix( vtkMatrix4x4* NewToolTransform, double angle ) 
	{
		tgt::Vector::Vector3 direction = tgt::Vector::Vector3(NewToolTransform->GetElement(0 , 2) , NewToolTransform->GetElement(1,2), NewToolTransform->GetElement(2,2));
		tgt::mat4::Matrix4 rotatedMatrix1 = tgt::mat4::Matrix4::createRotation(angle , direction);
		vtkMatrix4x4* RotatedMat = vtkMatrix4x4::New();
		for (int i = 0; i< 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				double element = rotatedMatrix1[i][j];
				RotatedMat->SetElement(i , j , element);
			}
		}	
		vtkMatrix4x4* finalResult = vtkMatrix4x4::New();
		vtkMatrix4x4::Multiply4x4(RotatedMat ,NewToolTransform,finalResult);
		for (int i = 0; i < 3; i++)
		{
			finalResult->SetElement(i , 3 , NewToolTransform->GetElement(i , 3));
		}
		RotatedMat->Delete();
		return finalResult;
	}

public:
// 	misRemoveRollFromRotationMatrix()
// 	{
// 	}



	vtkMatrix4x4*   operator()(vtkMatrix4x4* NewToolTransform)
	{
		if (!NewToolTransform)
			return 0;

		misSimplePointType CurrentFirstColumn;
		misSimplePointType CurrentSecondColumn;
		misSimplePointType CurrentThirdColumn;

		misSimplePointType YAuxiliary;
		
		CurrentFirstColumn.SetPoint(NewToolTransform->GetElement(0 , 0),NewToolTransform->GetElement(1 , 0),NewToolTransform->GetElement(2 ,0));
		CurrentSecondColumn.SetPoint(NewToolTransform->GetElement(0 , 1),NewToolTransform->GetElement(1 , 1),NewToolTransform->GetElement(2 ,1));
		CurrentThirdColumn.SetPoint(NewToolTransform->GetElement(0 , 2),NewToolTransform->GetElement(1 , 2),NewToolTransform->GetElement(2 ,2));

		YAuxiliary.SetPoint(0.0,1.0,0.0);
	
		if (YAuxiliary == CurrentThirdColumn)
		{
			_ASSERT( 0 == 1);
			return NewToolTransform;
		}

		if (CurrentSecondColumn.data[1] < 0)
		{
			auto rotated180 =  this->GetRotatedMatrix(NewToolTransform , m_PI);
			NewToolTransform->DeepCopy(rotated180);
			rotated180->Delete();
		}

		CurrentFirstColumn.SetPoint(NewToolTransform->GetElement(0 , 0),NewToolTransform->GetElement(1 , 0),NewToolTransform->GetElement(2 ,0));
		CurrentSecondColumn.SetPoint(NewToolTransform->GetElement(0 , 1),NewToolTransform->GetElement(1 , 1),NewToolTransform->GetElement(2 ,1));
		CurrentThirdColumn.SetPoint(NewToolTransform->GetElement(0 , 2),NewToolTransform->GetElement(1 , 2),NewToolTransform->GetElement(2 ,2));

		misSimplePointType FinalFirstColumn = misSimplePointType::CrossProduct(YAuxiliary , CurrentThirdColumn);
		misSimplePointType FinalSecondColumn = misSimplePointType::CrossProduct(CurrentThirdColumn , FinalFirstColumn);

		vtkMatrix4x4* correctedMatrix1 = vtkMatrix4x4::New();
		for (int i = 0; i < 3; i++)
		{			
			correctedMatrix1->SetElement(i , 0 , FinalFirstColumn.data[i]);
			correctedMatrix1->SetElement(i , 1 , FinalSecondColumn.data[i]);
			correctedMatrix1->SetElement(i , 2 , CurrentThirdColumn.data[i]);
			correctedMatrix1->SetElement(i , 3 , NewToolTransform->GetElement(i , 3));
		}

		return correctedMatrix1;
	}


	 
	
};
