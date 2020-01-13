#pragma once

class misTransformEquality
{
public:
	static bool EqualTransforms(vtkTransform* transform1 , vtkTransform* transform2)
	{
		bool res = EqualMatrix(transform1->GetMatrix() , transform2->GetMatrix());
		return res;
	}

	static bool EqualMatrix(vtkMatrix4x4* matrix1, vtkMatrix4x4* matrix2)
	{
		bool res = true;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (matrix1->GetElement(i , j) != matrix2->GetElement(i,j))
				{
					return false;
				}
			}
		}
		return res;
	}

	static bool IdentityTransform(vtkTransform* pTransform)
	{
		bool res = true;
		vtkTransform* identityTransform = vtkTransform::New();
		res = EqualTransforms(pTransform, identityTransform);
		identityTransform->Delete();
		return res;
	}

	static bool IdentityMatrix(vtkMatrix4x4* pMatrix)
	{
		bool res = true;
		vtkMatrix4x4* identityMatrix = vtkMatrix4x4::New();
		res = EqualMatrix(identityMatrix, pMatrix);
		identityMatrix->Delete();
		return res;
	}

	static bool IdentityRotationMatrix(vtkMatrix4x4* pMatrix)
	{
		bool res = true;
		vtkMatrix4x4* identityMatrix = vtkMatrix4x4::New();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (identityMatrix->GetElement(i , j) != pMatrix->GetElement(i,j))
				{
					return false;
				}
			}
		}
		return res;

	}

	static bool ZeroMatrix(vtkMatrix4x4* pMatrix)
	{
		bool res = false;
		if(!pMatrix)
			return res;

		int counter = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (abs(pMatrix->GetElement(i , j)) < 0.00000001)
					counter++;
			}
		}
		if(counter == 16)
			res = true;
		return res;
	}

	static bool CheckMatrixValidity(vtkMatrix4x4* pMatrix)
	{
		bool res = false;
		if(!pMatrix)
			return res;

		bool res1 = ZeroMatrix(pMatrix);

		bool res2 = true;
		if (pMatrix->GetElement(3 ,3) != 1)
			res2 = false;
		res = !res1 & res2;
		return res;
	}
};
