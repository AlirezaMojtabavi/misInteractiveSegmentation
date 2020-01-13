#pragma  once

template<class TCoordRep>
class mis3DVector : public itk::Vector<TCoordRep, 3>
{

public:
	mis3DVector() { }

	mis3DVector(TCoordRep x, TCoordRep y, TCoordRep z)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}

	mis3DVector(const tgt::Vector3<TCoordRep>& vec)
	{
		(*this)[0] = vec.x;
		(*this)[1] = vec.y;
		(*this)[2] = vec.z;
	}

	mis3DVector(const itk::Vector<TCoordRep, 3>& vec)
	{
		for(unsigned int i = 0; i < 3; i++) 
		{
			(*this)[i] = vec[i];
		}
	}

};
