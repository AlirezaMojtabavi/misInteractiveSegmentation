#pragma once


/** Point

basic data type  for point- that supports algebra operations like +,- ,....
 *\see also   misSimplePointType!!
 */
template<class TCoordRep = double>
class mis3DPoint :	public itk::Point<TCoordRep, 3>
{
public:

	using itk::Point<TCoordRep, 3>::operator+;
	
	// Add  point to a point. Return a new point. */
	mis3DPoint operator+(const mis3DPoint &point) const
	{
		mis3DPoint result;
		for( unsigned int i = 0; i < 3; i++) 
		{
			result[i] = (*this)[i] + point[i];
		}
		return result;
	}

	mis3DPoint(const itk::Point<TCoordRep, 3>& point)
	{
		for( unsigned int i=0; i<3; i++) 
		{
			(*this)[i] = point[i];
		}
	}
	mis3DPoint(TCoordRep x, TCoordRep y , TCoordRep z)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}

	mis3DPoint()
	{

	}
};

 

