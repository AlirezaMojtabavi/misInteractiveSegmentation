#pragma once

#define m_PI 3.1415926535897932384626433832795
#include <itkVector.h>

struct misSimplePointType
{
	double  data[3];
	bool	validity;

	typedef itk::Point<double,3> itkPointType;
	typedef itk::Vector<double,3> itkVectorType;

	itkPointType GetItkPoint() const
	{
		itkPointType point(data);
		return point;
	}

	itkVectorType GetItkVector() const
	{
		itkVectorType vec(data);
		return vec;
	}

	void Reset()
	{
		data[0] = -1;
		data[1] = -1;
		data[2] = -1;
		validity = false;
	}

	misSimplePointType(void)
	{
		this->Reset();
	}

	double& operator [](int index)
	{
		return data[index]; 
	}

	void Normalize (void)
	{
		if (this->validity)
		{
			double length = this->GetLength();

			if (0 == length )
			{
				length = 0.0000000000001;
			}
			if (length > 0)
			{
				this->data[0] = this->data[0] / length;
				this->data[1] = this->data[1] / length;
				this->data[2] = this->data[2] / length;
			}
		}
	}

	//Returns the length of vector
	double GetLength(void)
	{
		double length = -1;
		if (this->validity)
		{
			length = this->data[0] * this->data[0]+ this->data[1] * this->data[1]+ this->data[2] * this->data[2];
			length = sqrt( length);
		}
		return length;
	}

	//sets data of point
	void SetPoint (const double* point)
	{
		if (point)
		{
			this->data[0] = point[0];
			this->data[1] = point[1];
			this->data[2] = point[2];
			this->validity = true;
		}
	}

	//sets data of point
	void SetPoint (double x, double y, double z)
	{
		this->data[0] = x;
		this->data[1] = y;
		this->data[2] = z;
		this->validity = true;
	}

	void GetPoint (double* point) const
	{
		bool res = false;
		if (this->validity)
		{
			point[0] = this->data[0];
			point[1] = this->data[1];
			point[2] = this->data[2];
			res = true;
		}
		else
		{
			point[0] = -1.0;
			point[1] = -1.0;
			point[2] = -1.0;
		}
 
	}

	void DoAbsolute()
	{
		double temp[3];
		this->GetPoint(temp);
		for (int i = 0; i < 3; i ++)
		{
			this->data[i] = abs(temp[i]);
		}
	}

	void operator = (misSimplePointType right)
	{
		this->data[0] = right.data[0];
		this->data[1] = right.data[1];
		this->data[2] = right.data[2];
		this->validity = right.validity;
	}

	bool operator == (misSimplePointType right)
	{
		for (int i = 0; i < 3; i++)
		{
			if (this->data[i] != right.data[i])
			{
				return false;
			}
		}
		return true;
	}

	void operator += (misSimplePointType right)
	{
		if (this->validity && right.validity)
		{
			this->data[0] = this->data[0] + right.data[0];
			this->data[1] = this->data[1] + right.data[1];
			this->data[2] = this->data[2] + right.data[2];
		}
	}

	void Sum (misSimplePointType right)
	{
		if (this->validity && right.validity)
		{
			this->data[0] = this->data[0] + right.data[0];
			this->data[1] = this->data[1] + right.data[1];
			this->data[2] = this->data[2] + right.data[2];
		}
	}

	void operator -=  (misSimplePointType right)
	{
		if (this->validity && right.validity)
		{
			this->data[0] = this->data[0] - right.data[0];
			this->data[1] = this->data[1] - right.data[1];
			this->data[2] = this->data[2] - right.data[2];
		}
	}

	void Minus (misSimplePointType right)
	{
		if (this->validity && right.validity)
		{
			this->data[0] = this->data[0] - right.data[0];
			this->data[1] = this->data[1] - right.data[1];
			this->data[2] = this->data[2] - right.data[2];
		}
	}

	void Minus (double* rightPointData)
	{
		misSimplePointType right;
		right.SetPoint(rightPointData);
        this->Minus(right);
	}
 	void operator *= (double weight)
 	{
 		if (this->validity )
 		{
 			this->data[0] = weight * this->data[0] ;
 			this->data[1] = weight * this->data[1] ;
 			this->data[2] = weight * this->data[2] ;
 		}
 		else
 		{
 			_ASSERT(false == true);
 		}
 	}

	void Multiply (double weight)
	{
		if (this->validity )
		{
			this->data[0] = weight * this->data[0] ;
			this->data[1] = weight * this->data[1] ;
			this->data[2] = weight * this->data[2] ;
		}
	}

 	void operator *= (misSimplePointType point)
 	{
 		if (this->validity & point.validity)
 		{
 			this->data[0] = point.data[0] * this->data[0] ;
 			this->data[1] = point.data[1] * this->data[1] ;
 			this->data[2] = point.data[2] * this->data[2] ;
 		}
 	}

	void Multiply (misSimplePointType point)
	{
		if (this->validity & point.validity)
		{
			this->data[0] = point.data[0] * this->data[0] ;
			this->data[1] = point.data[1] * this->data[1] ;
			this->data[2] = point.data[2] * this->data[2] ;
		}
	}

	double DotProduct (misSimplePointType point)
	{
		double dotProduct= 0;
		if (this->validity & point.validity)
		{
			dotProduct = point.data[0] * this->data[0] ;
			dotProduct = point.data[1] * this->data[1] + dotProduct;
			dotProduct = point.data[2] * this->data[2] + dotProduct;
		}
		return dotProduct;
	}

	void operator /= (double weight)
	{
		if (0 != weight )
		{
			this->data[0] = this->data[0] /  weight ;
			this->data[1] = this->data[1] /  weight ;
			this->data[2] = this->data[2] /  weight ;
		}
	}

	void Divide(double weight)
	{
		if (0 != weight )
		{
			this->data[0] = this->data[0] /  weight ;
			this->data[1] = this->data[1] /  weight ;
			this->data[2] = this->data[2] /  weight ;
		}
	}

	void operator /= (misSimplePointType point)
	{
		if (point[0]&& point[1]&& point[2] )
		{
			this->data[0] = this->data[0] /  point.data[0] ;
			this->data[1] = this->data[1] /  point.data[1];
			this->data[2] = this->data[2] /  point.data[2];
		}
	}

	void Divide(misSimplePointType point)
	{
		if (point[0]&& point[1]&& point[2] )
		{
			this->data[0] = this->data[0] /  point.data[0] ;
			this->data[1] = this->data[1] /  point.data[1];
			this->data[2] = this->data[2] /  point.data[2];
		}
	}

	misSimplePointType PlaneProjection(misSimplePointType baseVector)
	{
		//Project base vector on the plane with Normal vector "this".
		misSimplePointType normalVector;
		normalVector.SetPoint(this->data);
		return misSimplePointType::PlaneProjection(baseVector , normalVector);
	}

	double GetAngle(misSimplePointType VectorB)
	{
		misSimplePointType VectorA;
		VectorA.SetPoint(this->data);
		return misSimplePointType::GetAngle(VectorA,VectorB);
	}

	static misSimplePointType PlaneProjection(misSimplePointType baseVector , misSimplePointType normalVector)
	{
		misSimplePointType normalProjection  = normalVector;
		double factor = normalProjection.DotProduct(baseVector)/normalVector.GetLength();
		normalProjection.Multiply(factor);
		misSimplePointType projectionVector = misSimplePointType::Minus(baseVector,normalProjection);
		return projectionVector;
	}

	//Returns the Angle between two vectors in degree
	static double GetAngle(misSimplePointType VectorA , misSimplePointType VectorB)
	{
		//Hint:
		//										  v1 . v2
		//	cos(Angle between v1 and v2) = -----------------
		//										|v1| x |v2|
		//
		
		double CosinusViewUp = VectorA.DotProduct(VectorB) / (VectorA.GetLength() * VectorB.GetLength());
		if (CosinusViewUp < 1.01 && CosinusViewUp > 1.0)
		{
			CosinusViewUp = 1.0;
		}
		if (CosinusViewUp< -1.0 && CosinusViewUp> -1.01)
		{
			CosinusViewUp = -1.0;
		}
		 
		if (CosinusViewUp <= 1.0 || CosinusViewUp >= -1.0)
		{
			double TargetAngle = acos(CosinusViewUp)* (180.0 / m_PI);
			return TargetAngle;			
		}
		return -1;
		
	}

	double EuclideanDistance(const double point[3])
	{
		return misSimplePointType::EuclideanDistance(this->data,point);
	}

	double EuclideanDistance(misSimplePointType  point)
	{
		return misSimplePointType::EuclideanDistance(this->data,point.data);
	}

	static double EuclideanDistance(misSimplePointType  point1,const double point2[3])
	{
		return misSimplePointType::EuclideanDistance(point1.data,point2);
	}

	static double EuclideanDistance(misSimplePointType  point1, misSimplePointType  point2)
	{
		return misSimplePointType::EuclideanDistance(point1.data,point2.data);
	}

	static double EuclideanDistance(double point1[3], misSimplePointType  point2)
	{
		return misSimplePointType::EuclideanDistance(point1,point2.data);
	}

	static double EuclideanDistance(const double point1[3], const double point2[3])
	{
		double distance = -1;
		double PowerDist;

		PowerDist =  pow(point1[0]- point2[0],2) + pow(point1[1]- point2[1],2) + pow(point1[2]- point2[2],2);
		distance = sqrt(PowerDist);

		return distance;
	}

	static misSimplePointType Sum(misSimplePointType point1, misSimplePointType point2)
	{
		misSimplePointType res;
		res = point1;
		res.Sum(point2);
		return res;
	}

	//returns the vector which is  obtained from connecting point1 to point2
	//its start is on point1 and its ends up on point2. Or you could assume that a 
	//simple minus on 2 points
	static misSimplePointType Minus(misSimplePointType point1, misSimplePointType point2)
	{
		misSimplePointType res;
		res = point1;
		res.Minus(point2);
		return res;
	}

	static misSimplePointType Multiply(misSimplePointType point1, misSimplePointType point2)
	{
		misSimplePointType res;
		if (point1.validity && point2.validity)
		{
			res.data[0] = point1.data[0] * point2.data[0];
			res.data[1] = point1.data[1] * point2.data[1];
			res.data[2] = point1.data[2] * point2.data[2];
		}

		return res;
	}

	static double DotProduct(misSimplePointType point1, misSimplePointType point2)
	{
		double dotProduct = 0;
		if (point1.validity && point2.validity)
		{
			dotProduct = point1.data[0] * point2.data[0];
			dotProduct = point1.data[1] * point2.data[1] + dotProduct;
			dotProduct = point1.data[2] * point2.data[2] + dotProduct;
		}
		return dotProduct;
	}

	static misSimplePointType CrossProduct(misSimplePointType point1 , misSimplePointType point2)
	{
		misSimplePointType result;
		if (point1.validity && point2.validity)
		{
			double xFactor = point1.data[1]*point2.data[2] - point1.data[2]*point2.data[1];
			double yFactor = point1.data[2]*point2.data[0] - point1.data[0]*point2.data[2];
			double zFactor = point1.data[0]*point2.data[1] - point1.data[1]*point2.data[0];
			result.SetPoint(xFactor , yFactor , zFactor);
		}
		result.Normalize();
		return result;
	}

	static double DistancePointFromLine(double p[3], misSimplePointType l1, misSimplePointType l2) //Distance p from line<l1,l2>
	{
		double distance = -1;
		if (l1.validity && l2.validity)
		{
			misSimplePointType LineDirection  = misSimplePointType::Minus(l2 , l1);
			double temp1 = sqrt(pow(p[0]-l1.data[0] , 2)+ 
								pow(p[1]-l1.data[1] , 2)+
								pow(p[2]-l1.data[2] , 2));
			double temp2 = (p[0]-l1.data[0])*LineDirection.data[0] + (p[1]-l1.data[1])*LineDirection.data[1] + (p[2]-l1.data[2])*LineDirection.data[2];

			distance = temp1 * sin(acos((temp2/(temp1 * LineDirection.GetLength()))));
		}
		return distance;
	}

};
typedef std::vector<misSimplePointType> misSimplePointListType;

