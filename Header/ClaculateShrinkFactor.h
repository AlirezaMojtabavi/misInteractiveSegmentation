#pragma once

#pragma warning (push, 0)

class  ClaculateShrinkFactor
{
public:

	typedef float PixelType;
	typedef itk::Image<PixelType, 3 > InputImage;

	itk::FixedArray<unsigned int,3> GetShrinkFactor(std::vector<double>  spacing , int numberOfLevel)
	{
		int dimension = spacing.size(); // TInputImage::ImageDimension;
		itk::Vector<double,3> SpaceFactors;

		for(int i = 0 ; i< dimension ; i++)
		{
			SpaceFactors[i] = spacing[i];
		}

		itk::Array2D<double> factors;
		itk::Array2D<double> temp( numberOfLevel + 1, 3 );
		temp.Fill(1.0);

		factors = temp;

		double MaxSpace = 0;
		int MaxSpaceIdx = 0;
		for (int idx=0;idx<dimension;idx++)
		{
			if (SpaceFactors[idx]>MaxSpace)
			{
				MaxSpace = SpaceFactors[idx];
				MaxSpaceIdx = idx;
			}
		}

		for (int levelIdx = numberOfLevel-2; levelIdx>=0; levelIdx--)
		{
			bool allOnes = true;
			for (int dimIdx = 0;dimIdx<dimension;dimIdx++)
			{
				if ((SpaceFactors[MaxSpaceIdx] * factors[levelIdx+1][MaxSpaceIdx]) /
					(SpaceFactors[dimIdx] * factors[levelIdx+1][dimIdx])>=2)
				{
					factors[levelIdx][dimIdx] = 2;
					allOnes = false;
				}
			}
			if (allOnes)
			{
				for (int dimIdx = 0;dimIdx<dimension;dimIdx++)
				{
					factors[levelIdx][dimIdx] = 2;
				}
			}
		}

		itk::FixedArray<unsigned int, InputImage::ImageDimension> ShrinkArray;

		for (int shrIdx = 0; shrIdx<InputImage::ImageDimension; shrIdx++)
		{
			int shrFactor = 1;
			for (int LevelIndx = 0; LevelIndx<numberOfLevel; LevelIndx++)
			{
				shrFactor = shrFactor * factors[LevelIndx][shrIdx];
			}
			ShrinkArray[shrIdx] = shrFactor;
		}

		return ShrinkArray;
	}
};

#pragma warning (pop)
