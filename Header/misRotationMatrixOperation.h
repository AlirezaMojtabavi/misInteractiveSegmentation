#pragma once
#include "vtkMatrix4x4.h"
#include "misTransformEquality.h"
class misRotationMatrixOperation
{
private:
	 double** m_OriginalMatrix;

	void FillInternalMatrix(vtkMatrix4x4* originalMatrix)
	{
		if(!m_OriginalMatrix)
		{
			m_OriginalMatrix = new double*[3];
			for (int i =0 ; i < 3; i++)
			{
				m_OriginalMatrix[i] = new double[3];
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j< 3; j++)
			{
				m_OriginalMatrix[i][j] = originalMatrix->GetElement(i , j);
			}
		}
	}

	double CalculateBeta()
	{
		double arg1 = -m_OriginalMatrix[2][0];
		double arg2 = sqrt(pow(m_OriginalMatrix[0][0] , 2) + pow(m_OriginalMatrix[1][0] , 2));
		double beta = atan2(arg1 , arg2);
		return beta;
	}

	double CalculateAlpha(double beta)
	{
		double cosBeta = cos(beta);
		double arg1 = m_OriginalMatrix[2][1] / cosBeta;
		double arg2 = m_OriginalMatrix[2][2] / cosBeta;
		double alpha = atan2(arg1 , arg2);
		return alpha;
	}

	double CalculateGama(double beta)
	{
		double cosBeta = cos(beta);
		double arg1 = m_OriginalMatrix[1][0] / cosBeta;
		double arg2 = m_OriginalMatrix[0][0] /cosBeta;
		double gama = atan2(arg1 , arg2);
		return gama;
	}
	double** CalculateRotationAlpha(double alpha)
	{
		double** Rz = new double*[3];
		for (int i = 0; i < 3; i++)
		{
			Rz[i] = new double[3];
		}

		Rz[0][0] = cos(alpha);
		Rz[0][1] = -sin(alpha);
		Rz[0][2] = 0;

		Rz[1][0] = sin(alpha);
		Rz[1][1] = cos(alpha);
		Rz[1][2] = 0;

		Rz[2][0] = 0;
		Rz[2][1] = 0;
		Rz[2][2] = 1;
		
		return Rz;
	}

	double** CalculateRotationBeta(double beta)
	{
		double** Ry = new double*[3];
		for (int i = 0; i < 3; i++)
		{
			Ry[i] = new double[3];
		}
		Ry[0][0] = cos(beta);
		Ry[0][1] = 0;
		Ry[0][2] = sin(beta);

		Ry[1][0] = 0;
		Ry[1][1] = 1;
		Ry[1][2] = 0;

		Ry[2][0] = -sin(beta);
		Ry[2][1] = 0;
		Ry[2][2] = cos(beta);

		return Ry;
	}

	double** CalculateRotationGama(double gama)
	{
		double** Rx = new double*[3];
		for (int i = 0; i < 3; i++)
		{
			Rx[i] = new double[3];
		}
		Rx[0][0] = 1;
		Rx[0][1] = 0;
		Rx[0][2] = 0;

		Rx[1][0] = 0;
		Rx[1][1] = cos(gama);
		Rx[1][2] = -sin(gama);

		Rx[2][0] = 0;
		Rx[2][1] = sin(gama);
		Rx[2][2] = cos(gama);

		return Rx;
	}

	void CalculateRzRyMatrix(double** Rz , double** Ry , vtkMatrix4x4* resultMatrix)
	{
		for (int m = 0; m<3; m++)
		{
			for (int n = 0; n<3; n++)
			{
				double element = 0;
				for (int i = 0; i < 3; i++)
				{
					element = element + (Rz[m][i] * Ry[i][n]);
				}
				resultMatrix->SetElement(m , n , element);
			}
		}		
	}

	vtkMatrix4x4* TestResult(double** Rz , double** Ry , double **Rx)
	{

		vtkMatrix4x4* RyRx = vtkMatrix4x4::New();
		CalculateRzRyMatrix(Ry , Rx , RyRx);

		vtkMatrix4x4* result = vtkMatrix4x4::New();
		for (int m = 0; m<3; m++)
		{
			for (int n = 0; n<3; n++)
			{
				double element = 0;
				for (int i = 0; i < 3; i++)
				{
					element = element + (Rz[m][i] * RyRx->GetElement(i,n));
				}
				result->SetElement(m , n , element);
			}
		}		

		return result;
	}

public:
	misRotationMatrixOperation()
	{
		m_OriginalMatrix = 0;
	}
	~misRotationMatrixOperation()
	{
		delete m_OriginalMatrix;
	}
	vtkMatrix4x4*   operator()(vtkMatrix4x4* OriginalRotationMatrix)
	{
		vtkMatrix4x4* ResultRotationMatrix = 0;
		if (!OriginalRotationMatrix)
		{
			_ASSERT( 0 == 1);
			return ResultRotationMatrix;
		}
		this->FillInternalMatrix(OriginalRotationMatrix);

		ResultRotationMatrix = vtkMatrix4x4::New();
		
		double beta = this->CalculateBeta();
		double alpha = this->CalculateAlpha(beta);
		double gama = this->CalculateGama(beta);

		double** RzAlpha = this->CalculateRotationAlpha(alpha);
		double** RyBeta = this->CalculateRotationBeta(beta);
		double** RxGama = this->CalculateRotationGama(gama);

		this->CalculateRzRyMatrix(RzAlpha , RyBeta , ResultRotationMatrix);

		for (int i = 0; i< 4 ; i++)
		{
			ResultRotationMatrix->SetElement(i , 3 , OriginalRotationMatrix->GetElement(i , 3));
		}
		//TEST PROCEDURE
		vtkMatrix4x4* calculateMatrix = this->TestResult(RzAlpha , RyBeta, RxGama);
		for (int i = 0; i< 4 ; i++)
		{
			calculateMatrix->SetElement(i , 3 , OriginalRotationMatrix->GetElement(i , 3));
		}
		bool res =  misTransformEquality::EqualMatrix(calculateMatrix , OriginalRotationMatrix);
		//TEST PROCEDURE
		//if(res == true)
		return ResultRotationMatrix;
// 		else
// 			_ASSERT( 0 == 1);
// 		return 0;
	}
};
