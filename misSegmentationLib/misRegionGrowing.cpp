#include "StdaFx.h"

#include "misRegionGrowing.h"

using namespace std;

misRegionGrowing::misRegionGrowing(void)
	: m_mutex(CreateMutex(NULL, FALSE, NULL)), m_CancelSegmentation(false), m_BufferInputImage(0),
	m_BufferOutputImage(0), m_OutputSegmentedImage(vtkSmartPointer<vtkImageData>::New()),
	m_MaximumPrimarySeedSize(1000), 
	m_ThresholdChecking(true), m_NumberOfObjectSeed(0), m_IsMargineActive(false), m_HigherThreshold(0)
	
{
	
	int neighbor[27] = {0,17,0,17,17,17,0,17,0,17,17,17,17,17,17,17,17,0,17,0,17,17,17,0,17,0,26};
	SetNeighborNumber(neighbor);
	LookupTableDefinition();
	ResetSetting();
	m_NeighborType = 6;
	m_Border = misObjectBorder;
	m_Percentage = 80;
}

 
int misRegionGrowing::InitialPrimerySeeds(void)
{
	m_OldSeeds.clear();
	m_Newseeds.clear();

	int volumeSize = m_SizeX * m_SizeY * m_SizeZ;
	int neighborNumbers = m_NeighborType;
	int currentSeedX, currentSeedY, currentSeedZ;

	m_NumberOfNewSeeds = 0;
	for (int i=0; i < m_NumberOfPrimerySeeds; i++)
	{
		currentSeedX = m_PrimarySeeds[i].x;
		currentSeedY = m_PrimarySeeds[i].y;
		currentSeedZ = m_PrimarySeeds[i].z;
		CheckAndAddNewNeighbor(currentSeedX, currentSeedY, currentSeedZ,neighborNumbers);
	}

	int accptedSeedNo = MoveNewSeedsToOldPosition();

	return accptedSeedNo;
};

bool misRegionGrowing::Calculation( void )
{
	if(!m_BufferInputImage || !m_BufferOutputImage )
		return false;
	if((0 >= m_SizeX) || (0 >= m_SizeY) || (0 >= m_SizeZ) )
		return false;
	
	bool res = CheckSegmentationValues();
	if (!res)
		return false;

	int seed_numbers = InitialPrimerySeeds();

	misRGSeed temp_seed [50]; 
	int itt_counter = 0;
	int Ncounter = 0;
	int currentSeedX, currentSeedY, currentSeedZ;
	int seedNeighborX,seedNeighborY,seedNeighborZ;
	int neighborNumbers = m_NeighborType;
	//int neighborNumbers = 26; // Must correct

	int iter =0;
	if (seed_numbers == 0)
	{
		m_State = WrongROI;
		return false;
	}

	while ((iter <= m_MaxIter) &&(seed_numbers != 0) && (m_CancelSegmentation != true))
	{ 
		//while seed_number
		m_NumberOfNewSeeds  = 0;
		
		for (int seedNO = 0 ; seedNO <seed_numbers ; seedNO++)
		{ //for n
			
 			currentSeedX = m_OldSeeds[seedNO].x; 
 			currentSeedY = m_OldSeeds[seedNO].y; 
 			currentSeedZ = m_OldSeeds[seedNO].z;
			Ncounter++;

			// convert current seed to object or border
			FinilaizeSeedType(currentSeedX, currentSeedY, currentSeedZ);

			for (int neighborNO = 0 ; neighborNO < neighborNumbers ; neighborNO++ )
			{
				int neighorType = m_NeighborType;
				int index;

				if (neighborNumbers == 26)
					index = 0;
				else if(neighborNumbers == 6)
					index = 1;
				else if(neighborNumbers == 18)
					index = 2;

				int i2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][0];
				int j2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][1];
				int k2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][2];
				int t2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][3];

				int seedType = m_NeighborType;
				//int seedType = 26;//color[neighorType];
				seedNeighborX = currentSeedX +i2;
				seedNeighborY = currentSeedY +j2;
				seedNeighborZ = currentSeedZ +k2;

				CheckAndAddNewNeighbor(seedNeighborX, seedNeighborY, seedNeighborZ,seedType);
			}
		}
		seed_numbers = MoveNewSeedsToOldPosition();
		iter++;
		m_State = OKRG;
		//return true;
	}//end while(termination condition)	

#pragma endregion SeedCondition
	if (m_CancelSegmentation == false)
	{
		vtkTimerLog *cTime = vtkTimerLog::New();
		cTime->StartTimer();
		UpdateBorderVoxels();
		ApplyMarginalBorder();
		cTime->StopTimer();
		double BorderExtraction = cTime->GetElapsedTime();
	}
	else if(m_CancelSegmentation == true)
	{
		// TODO: must check JHB
		//delete outputImage;
		m_BufferOutputImage = NULL;
		return false;
	}
	return true;
}

int misRegionGrowing::MoveNewSeedsToOldPosition(void )
{
	// move newSeeds to OldSeeds
	if (m_NumberOfNewSeeds > (m_NumberOfMaximumSeeds * .8))
	{
		m_NumberOfMaximumSeeds = m_NumberOfMaximumSeeds * 1.2;
		// TODO: complte
		// resize old seed array
		// copy new to old
		// resize new seed array
	}
	m_OldSeeds.clear();
 	for ( int i = 0 ; i < m_NumberOfNewSeeds  ; i++)
 	{ 
 		m_OldSeeds.push_back(m_Newseeds[i]);
 	} 
	int seed_numbers = m_NumberOfNewSeeds;
	m_NumberOfNewSeeds = 0;

	return seed_numbers;
}

void misRegionGrowing::SetNeighborNumber( int neighbor[] )
{
	for (int i = 0; i<27 ; i++)
		Neighbor_number[i] = neighbor[i];
}

bool misRegionGrowing::PercentCheck(int& i , int& j , int& k )
{
	int coordinate;
	int neighborX,neighborY,neighborZ;
	int counter = 0;
	int neighborNumbers = m_NeighborType;
	double percentage = (double)(m_Percentage * neighborNumbers)/100;
	int index;
	if (neighborNumbers == 26)
		index = 0;
	else if(neighborNumbers == 6)
		index = 1;
	else if(neighborNumbers == 18)
		index = 2;
	for (int neighborNO = 0 ; neighborNO < neighborNumbers ; neighborNO++ )
	{            
		int i2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][0];
		int j2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][1];
		int k2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][2];
		int t2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][3];
		if ((counter < percentage)){
			neighborX = i+i2;
			neighborY = j+j2;
			neighborZ = k+k2;
			if(InMargin(neighborX, neighborY , neighborZ))
			{
				coordinate = CalculateIndex(neighborX, neighborY , neighborZ);
				if (coordinate != -1 )
				{
					if ((m_BufferInputImage[coordinate] > GetLowerThreshold())&&(m_BufferInputImage[coordinate] < GetHigherThreshold() ))
						counter++;
				}				
// 				else
// 					_ASSERT( 0 == 1);
			}
		}
	}
	if (counter > percentage)
		return true;
	else
		return false;
}

bool misRegionGrowing::IsObject( int& i , int& j , int& k )
{
	int coordinate;
	int neighborX,neighborY,neighborZ;
	int neighborNumbers = m_NeighborType;
	int index;
	if (neighborNumbers == 26)
		index = 0;
	else if(neighborNumbers == 6)
		index = 1;
	else if(neighborNumbers == 18)
		index = 2;
	for (int neighborNO = 0 ; neighborNO < neighborNumbers ; neighborNO++ )
	{            
		int i2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][0];
		int j2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][1];
		int k2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][2];
		int t2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][3];

		neighborX = i+i2;
		neighborY = j+j2;
		neighborZ = k+k2;
		if(true == InMargin(neighborX, neighborY , neighborZ))
		{
			coordinate = CalculateIndex(neighborX, neighborY , neighborZ);
			if (coordinate != -1)
			{
				if ( (m_BufferInputImage[coordinate] < GetLowerThreshold()) || (m_BufferInputImage[coordinate] > GetHigherThreshold()) )
				{
					return false;
				}
			}
		}
	}
	return true;
}

int misRegionGrowing::CalculateIndex( int& i, int& j, int& k )
{

	if ((m_SizeX == -1) || (m_SizeY == -1) || (m_SizeZ == -1))
	{
		_ASSERT(0);
		return -1;
	}
	if ((i < 0) || ( i >= m_SizeX))
	{
		_ASSERT(0);
		return -1;
	}
	if ((j < 0) || ( j >= m_SizeY))
	{
		_ASSERT(0);
		return -1;
	}
	if ((k < 0) || ( k >= m_SizeZ))
	{
		_ASSERT(0);
		return -1;
	}

	int CalculateedIndex = (k * m_SizeX * m_SizeY) + (j * m_SizeX) + i;

	int volumeSize = m_SizeX*m_SizeY*m_SizeZ;
	// Note : it is a double check
	if (CalculateedIndex >= volumeSize)
	{
		return  -1;
	}
	return CalculateedIndex;
}

bool misRegionGrowing::InMargin( int& i , int& j , int& k )
{
	if ( (i > m_MaximumObjectValidRange[0]) && (i < m_MaximumObjectValidRange[1]))
	{
		if ( (j > m_MaximumObjectValidRange[2]) && (j < m_MaximumObjectValidRange[3]))
		{
			if ( (k > m_MaximumObjectValidRange[4]) && (k < m_MaximumObjectValidRange[5]))
			{
				return true;
			}
		}
	}
	return false;
}

void misRegionGrowing::SetSeedColor( int color[] )
{
	for(int i = 0; i<27; i++)
		color[i] = 100 + i;
}

void misRegionGrowing::LookupTableDefinition()
{
	m_TypeCoordination[0][0]=-1; m_TypeCoordination[0][1]=1; m_TypeCoordination[0][2]=-1; m_TypeCoordination[0][3]=0;
	m_TypeCoordination[1][0] =0; m_TypeCoordination[1][1] =1; m_TypeCoordination[1][2]=-1;m_TypeCoordination[1][3]=1;
	m_TypeCoordination[2][0]=1; m_TypeCoordination[2][1]=1;m_TypeCoordination[2][2]=-1;m_TypeCoordination[2][3]=2;
	m_TypeCoordination[3][0]=-1;m_TypeCoordination[3][1]=0; m_TypeCoordination[3][2]=-1; m_TypeCoordination[3][3]=3;
	m_TypeCoordination[4][0]=0;m_TypeCoordination[4][1]=0; m_TypeCoordination[4][2]=-1; m_TypeCoordination[4][3]=4;
	m_TypeCoordination[5][0]=1; m_TypeCoordination[5][1]=0; m_TypeCoordination[5][2]=-1; m_TypeCoordination[5][3]=5;
	m_TypeCoordination[6][0]=-1;m_TypeCoordination[6][1]=-1;m_TypeCoordination[6][2]=-1;m_TypeCoordination[6][3]=6;
	m_TypeCoordination[7][0]=0;m_TypeCoordination[7][1]=-1;m_TypeCoordination[7][2]=-1;m_TypeCoordination[7][3]=7;
	m_TypeCoordination[8][0]=1;m_TypeCoordination[8][1]=-1;m_TypeCoordination[8][2]=-1;m_TypeCoordination[8][3]=8;
	m_TypeCoordination[9][0]=-1;m_TypeCoordination[9][1]=1;m_TypeCoordination[9][2]=0;m_TypeCoordination[9][3]=9;
	m_TypeCoordination[10][0]=0;m_TypeCoordination[10][1]=1;m_TypeCoordination[10][2]=0;m_TypeCoordination[10][3]=10;
	m_TypeCoordination[11][0]=1;m_TypeCoordination[11][1]=1;m_TypeCoordination[11][2]=0;m_TypeCoordination[11][3]=11;
	m_TypeCoordination[12][0]=-1;m_TypeCoordination[12][1]=0;m_TypeCoordination[12][2]=0;m_TypeCoordination[12][3]=12;
	//TypeCoordination[13]= {0,0,0,13}; center of cube
	m_TypeCoordination[13][0]=1;m_TypeCoordination[13][1]=0;m_TypeCoordination[13][2]=0;m_TypeCoordination[13][3]=13;
	m_TypeCoordination[14][0]=-1;m_TypeCoordination[14][1]=-1;m_TypeCoordination[14][2]=0;m_TypeCoordination[14][3]=14;
	m_TypeCoordination[15][0]=0;m_TypeCoordination[15][1]=-1;m_TypeCoordination[15][2]=0;m_TypeCoordination[15][3]=15;
	m_TypeCoordination[16][0]=1;m_TypeCoordination[16][1]=-1;m_TypeCoordination[16][2]=0;m_TypeCoordination[16][3]=16;
	m_TypeCoordination[17][0]=-1;m_TypeCoordination[17][1]=1;m_TypeCoordination[17][2]=1;m_TypeCoordination[17][3]=17;
	m_TypeCoordination[18][0]=0;m_TypeCoordination[18][1]=1;m_TypeCoordination[18][2]=1;m_TypeCoordination[18][3]=18;
	m_TypeCoordination[19][0]=1;m_TypeCoordination[19][1]=1;m_TypeCoordination[19][2]=1;m_TypeCoordination[19][3]=19; 
	m_TypeCoordination[20][0]=-1;m_TypeCoordination[20][1]=0;m_TypeCoordination[20][2]=1;m_TypeCoordination[20][3]=20;
	m_TypeCoordination[21][0]=0;m_TypeCoordination[21][1]=0;m_TypeCoordination[21][2]=1;m_TypeCoordination[21][3]=21;
	m_TypeCoordination[22][0]=1;m_TypeCoordination[22][1]=0;m_TypeCoordination[22][2]=1;m_TypeCoordination[22][3]=22;
	m_TypeCoordination[23][0]=-1;m_TypeCoordination[23][1]=-1;m_TypeCoordination[23][2]=1;m_TypeCoordination[23][3]=23;
	m_TypeCoordination[24][0]=0;m_TypeCoordination[24][1]=-1;m_TypeCoordination[24][2]=1;m_TypeCoordination[24][3]=24;
	m_TypeCoordination[25][0]=1;m_TypeCoordination[25][1]=-1;m_TypeCoordination[25][2]=1;m_TypeCoordination[25][3]=25;
	//NeighborTable[0] = {};
	m_NeighborTable[1][0]=0;m_NeighborTable[1][1]=1;m_NeighborTable[1][2]=2;m_NeighborTable[1][3]=3;m_NeighborTable[1][4]=4;
	m_NeighborTable[1][5]=5;m_NeighborTable[1][6]=6;m_NeighborTable[1][7]=7;m_NeighborTable[1][8]=8;m_NeighborTable[1][9]=9;
	m_NeighborTable[1][10]=10;m_NeighborTable[1][11]=11;m_NeighborTable[1][12]=12;m_NeighborTable[1][13]=13;m_NeighborTable[1][14]=17;
	m_NeighborTable[1][15]=18;m_NeighborTable[1][16]=19;
	//NeighborTable[2]= {};
	m_NeighborTable[3][0]=0;m_NeighborTable[3][1]=1;m_NeighborTable[3][2]=2;m_NeighborTable[3][3]=3;m_NeighborTable[3][4]=4;
	m_NeighborTable[3][5]=5;m_NeighborTable[3][6]=6;m_NeighborTable[3][7]=7;m_NeighborTable[3][8]=8;m_NeighborTable[3][9]=9;
	m_NeighborTable[3][10]=10;m_NeighborTable[3][11]=12;m_NeighborTable[3][12]=14;m_NeighborTable[3][13]=15;m_NeighborTable[3][14]=17;
	m_NeighborTable[3][15]=20;m_NeighborTable[3][16]=23;

	m_NeighborTable[4][0]=0;m_NeighborTable[4][1]=1;m_NeighborTable[4][2]=2;m_NeighborTable[4][3]=9;m_NeighborTable[4][4]=10;
	m_NeighborTable[4][5]=11;m_NeighborTable[4][6]=17;m_NeighborTable[4][7]=18;m_NeighborTable[4][8]=19;m_NeighborTable[4][9]=3;
	m_NeighborTable[4][10]=4;m_NeighborTable[4][11]=5;m_NeighborTable[4][12]=12;m_NeighborTable[4][13]=13;m_NeighborTable[4][14]=20;
	m_NeighborTable[4][15]=21;m_NeighborTable[4][16]=22;

	m_NeighborTable[5][0]=0;m_NeighborTable[5][1]=1;m_NeighborTable[5][2]=2;m_NeighborTable[5][3]=3;m_NeighborTable[5][4]=4;
	m_NeighborTable[5][5]=5;m_NeighborTable[5][6]=6;m_NeighborTable[5][7]=7;m_NeighborTable[5][8]=8;m_NeighborTable[5][9]=10;
	m_NeighborTable[5][10]=11;m_NeighborTable[5][11]=13;m_NeighborTable[5][12]=15;m_NeighborTable[5][13]=16;m_NeighborTable[5][14]=19;
	m_NeighborTable[5][15]=22;m_NeighborTable[5][16]=25;
	//NeighborTable[6] = {};
	m_NeighborTable[7][0]=0;m_NeighborTable[7][1]=1;m_NeighborTable[7][2]=2;m_NeighborTable[7][3]=3;m_NeighborTable[7][4]=4;
	m_NeighborTable[7][5]=5;m_NeighborTable[7][6]=6;m_NeighborTable[7][7]=7;m_NeighborTable[7][8]=8;m_NeighborTable[7][9]=12;
	m_NeighborTable[7][10]=13;m_NeighborTable[7][11]=14;m_NeighborTable[7][12]=15;m_NeighborTable[7][13]=16;m_NeighborTable[7][14]=23;
	m_NeighborTable[7][15]=24;m_NeighborTable[7][16]=25;
	//NeighborTable[8] = {};
	m_NeighborTable[9][0]=0;m_NeighborTable[9][1]=1;m_NeighborTable[9][2]=2;m_NeighborTable[9][3]=3;m_NeighborTable[9][4]=4;
	m_NeighborTable[9][5]=6;m_NeighborTable[9][6]=9;m_NeighborTable[9][7]=10;m_NeighborTable[9][8]=11;m_NeighborTable[9][9]=12;
	m_NeighborTable[9][10]=14;m_NeighborTable[9][11]=17;m_NeighborTable[9][12]=18;m_NeighborTable[9][13]=19;m_NeighborTable[9][14]=20;
	m_NeighborTable[9][15]=21;m_NeighborTable[9][16]=23;

	m_NeighborTable[10][0]=0;m_NeighborTable[10][1]=1;m_NeighborTable[10][2]=2;m_NeighborTable[10][3]=9;m_NeighborTable[10][4]=10;
	m_NeighborTable[10][5]=11;m_NeighborTable[10][6]=3;m_NeighborTable[10][7]=4;m_NeighborTable[10][8]=5;m_NeighborTable[10][9]=12;
	m_NeighborTable[10][10]=13;m_NeighborTable[10][11]=6;m_NeighborTable[10][12]=7;m_NeighborTable[10][13]=8;m_NeighborTable[10][14]=14;
	m_NeighborTable[10][15]=15;m_NeighborTable[10][16]=16;

	m_NeighborTable[11][0]=0;m_NeighborTable[11][1]=1;m_NeighborTable[11][2]=2;m_NeighborTable[11][3]=4;m_NeighborTable[11][4]=5;
	m_NeighborTable[11][5]=8;m_NeighborTable[11][6]=9;m_NeighborTable[11][7]=10;m_NeighborTable[11][8]=11;m_NeighborTable[11][9]=12;
	m_NeighborTable[11][10]=13;m_NeighborTable[11][11]=16;m_NeighborTable[11][12]=17;m_NeighborTable[11][13]=18;m_NeighborTable[11][14]=19;
	m_NeighborTable[11][15]=21;m_NeighborTable[11][16]=25;

	m_NeighborTable[12][0]=0;m_NeighborTable[12][1]=1;m_NeighborTable[12][2]=9;m_NeighborTable[12][3]=10;m_NeighborTable[12][4]=17;
	m_NeighborTable[12][5]=18;m_NeighborTable[12][6]=3;m_NeighborTable[12][7]=4;m_NeighborTable[12][8]=12;m_NeighborTable[12][9]=20;
	m_NeighborTable[12][10]=21;m_NeighborTable[12][11]=6;m_NeighborTable[12][12]=7;m_NeighborTable[12][13]=14;m_NeighborTable[12][14]=15;
	m_NeighborTable[12][15]=23;m_NeighborTable[12][16]=24;

	m_NeighborTable[13][0]=1;m_NeighborTable[13][1]=2;m_NeighborTable[13][2]=4;m_NeighborTable[13][3]=5;m_NeighborTable[13][4]=7;
	m_NeighborTable[13][5]=8;m_NeighborTable[13][6]=10;m_NeighborTable[13][7]=11;m_NeighborTable[13][8]=13;m_NeighborTable[13][9]=15;
	m_NeighborTable[13][10]=16;m_NeighborTable[13][11]=18;m_NeighborTable[13][12]=19;m_NeighborTable[13][13]=21;m_NeighborTable[13][14]=22;
	m_NeighborTable[13][15]=24;m_NeighborTable[13][16]=25;

	m_NeighborTable[14][0]=4;m_NeighborTable[14][1]=21;m_NeighborTable[14][2]=0;m_NeighborTable[14][3]=9;m_NeighborTable[14][4]=17;
	m_NeighborTable[14][5]=3;m_NeighborTable[14][6]=12;m_NeighborTable[14][7]=20;m_NeighborTable[14][8]=6;m_NeighborTable[14][9]=14;
	m_NeighborTable[14][10]=23;m_NeighborTable[14][11]=7;m_NeighborTable[14][12]=15;m_NeighborTable[14][13]=24;m_NeighborTable[14][14]=8;
	m_NeighborTable[14][15]=16;m_NeighborTable[14][16]=25;

	m_NeighborTable[15][0]=3;m_NeighborTable[15][1]=4;m_NeighborTable[15][2]=5;m_NeighborTable[15][3]=6;m_NeighborTable[15][4]=7;
	m_NeighborTable[15][5]=8;m_NeighborTable[15][6]=12;m_NeighborTable[15][7]=13;m_NeighborTable[15][8]=14;m_NeighborTable[15][9]=15;
	m_NeighborTable[15][10]=16;m_NeighborTable[15][11]=20;m_NeighborTable[15][12]=21;m_NeighborTable[15][13]=22;m_NeighborTable[15][14]=23;
	m_NeighborTable[15][15]=24;m_NeighborTable[15][16]=25;

	m_NeighborTable[16][0]=4;m_NeighborTable[16][1]=21;m_NeighborTable[16][2]=2;m_NeighborTable[16][3]=11;m_NeighborTable[16][4]=19;
	m_NeighborTable[16][5]=5;m_NeighborTable[16][6]=13;m_NeighborTable[16][7]=22;m_NeighborTable[16][8]=8;m_NeighborTable[16][9]=16;
	m_NeighborTable[16][10]=25;m_NeighborTable[16][11]=7;m_NeighborTable[16][12]=24;m_NeighborTable[16][13]=6;m_NeighborTable[16][14]=14;
	m_NeighborTable[16][15]=23;m_NeighborTable[16][16]=15;
	//NeighborTable[17] = {};
	m_NeighborTable[18][0]=0;m_NeighborTable[18][1]=1;m_NeighborTable[18][2]=2;m_NeighborTable[18][3]=9;m_NeighborTable[18][4]=10;
	m_NeighborTable[18][5]=11;m_NeighborTable[18][6]=12;m_NeighborTable[18][7]=13;m_NeighborTable[18][8]=17;m_NeighborTable[18][9]=18;
	m_NeighborTable[18][10]=19;m_NeighborTable[18][11]=20;m_NeighborTable[18][12]=21;m_NeighborTable[18][13]=22;m_NeighborTable[18][14]=23;
	m_NeighborTable[18][15]=24;m_NeighborTable[18][16]=25;
	//NeighborTable[19] = {};
	m_NeighborTable[20][0]=0;m_NeighborTable[20][1]=3;m_NeighborTable[20][2]=6;m_NeighborTable[20][3]=9;m_NeighborTable[20][4]=10;
	m_NeighborTable[20][5]=12;m_NeighborTable[20][6]=14;m_NeighborTable[20][7]=15;m_NeighborTable[20][8]=17;m_NeighborTable[20][9]=18;
	m_NeighborTable[20][10]=19;m_NeighborTable[20][11]=20;m_NeighborTable[20][12]=21;m_NeighborTable[20][13]=22;m_NeighborTable[20][14]=23;
	m_NeighborTable[20][15]=24;m_NeighborTable[20][16]=25;

	m_NeighborTable[21][0]=9;m_NeighborTable[21][1]=10;m_NeighborTable[21][2]=11;m_NeighborTable[21][3]=12;m_NeighborTable[21][4]=13;
	m_NeighborTable[21][5]=14;m_NeighborTable[21][6]=15;m_NeighborTable[21][7]=16;m_NeighborTable[21][8]=17;m_NeighborTable[21][9]=18;
	m_NeighborTable[21][10]=19;m_NeighborTable[21][11]=20;m_NeighborTable[21][12]=21;m_NeighborTable[21][13]=22;m_NeighborTable[21][14]=23;
	m_NeighborTable[21][15]=24;m_NeighborTable[21][16]=25;

	m_NeighborTable[22][0]=2;m_NeighborTable[22][1]=5;m_NeighborTable[22][2]=8;m_NeighborTable[22][3]=11;m_NeighborTable[22][4]=13;
	m_NeighborTable[22][5]=16;m_NeighborTable[22][6]=19;m_NeighborTable[22][7]=22;m_NeighborTable[22][8]=25;m_NeighborTable[22][9]=18;
	m_NeighborTable[22][10]=21;m_NeighborTable[22][11]=24;m_NeighborTable[22][12]=17;m_NeighborTable[22][13]=20;m_NeighborTable[22][14]=23;
	m_NeighborTable[22][15]=10;m_NeighborTable[22][16]=15;
	//NeighborTable[23] = {};
	m_NeighborTable[24][0]=6;m_NeighborTable[24][1]=7;m_NeighborTable[24][2]=8;m_NeighborTable[24][3]=12;m_NeighborTable[24][4]=13;
	m_NeighborTable[24][5]=14;m_NeighborTable[24][6]=15;m_NeighborTable[24][7]=16;m_NeighborTable[24][8]=17;m_NeighborTable[24][9]=18;
	m_NeighborTable[24][10]=19;m_NeighborTable[24][11]=20;m_NeighborTable[24][12]=21;m_NeighborTable[24][13]=22;m_NeighborTable[24][14]=23;
	m_NeighborTable[24][15]=24;m_NeighborTable[24][16]=25;
	//NeighborTable[25] = {};
	m_NeighborTable[26][0]=0;m_NeighborTable[26][1]=1;m_NeighborTable[26][2]=2;m_NeighborTable[26][3]=3;m_NeighborTable[26][4]=4;
	m_NeighborTable[26][5]=5;m_NeighborTable[26][6]=6;m_NeighborTable[26][7]=7;m_NeighborTable[26][8]=8;m_NeighborTable[26][9]=9;
	m_NeighborTable[26][10]=10;m_NeighborTable[26][11]=11;m_NeighborTable[26][12]=12;m_NeighborTable[26][13]=13;m_NeighborTable[26][14]=14;
	m_NeighborTable[26][15]=15;m_NeighborTable[26][16]=16;m_NeighborTable[26][17]=17;m_NeighborTable[26][18]=18;m_NeighborTable[26][19]=19;
	m_NeighborTable[26][20]=20;m_NeighborTable[26][21]=21;m_NeighborTable[26][22]=22;m_NeighborTable[26][23]=23;m_NeighborTable[26][24]=24;
	m_NeighborTable[26][25]=25;

	NeighborTable_new[0][0]=0;NeighborTable_new[0][1]=1;NeighborTable_new[0][2]=2;NeighborTable_new[0][3]=3;NeighborTable_new[0][4]=4;
	NeighborTable_new[0][5]=5;NeighborTable_new[0][6]=6;NeighborTable_new[0][7]=7;NeighborTable_new[0][8]=8;NeighborTable_new[0][9]=9;
	NeighborTable_new[0][10]=10;NeighborTable_new[0][11]=11;NeighborTable_new[0][12]=12;NeighborTable_new[0][13]=13;NeighborTable_new[0][14]=14;
	NeighborTable_new[0][15]=15;NeighborTable_new[0][16]=16;NeighborTable_new[0][17]=17;NeighborTable_new[0][18]=18;NeighborTable_new[0][19]=19;
	NeighborTable_new[0][20]=20;NeighborTable_new[0][21]=21;NeighborTable_new[0][22]=22;NeighborTable_new[0][23]=23;NeighborTable_new[0][24]=24;
	NeighborTable_new[0][25]=25;

	NeighborTable_new[1][0]=13;NeighborTable_new[1][1]=12;NeighborTable_new[1][2]=10;NeighborTable_new[1][3]=15;
	NeighborTable_new[1][4]=4;NeighborTable_new[1][5]=21;

	NeighborTable_new[2][0]=10;NeighborTable_new[2][1]=15;NeighborTable_new[2][2]=11;NeighborTable_new[2][3]=16;
	NeighborTable_new[2][4]=13;NeighborTable_new[2][5]=9;NeighborTable_new[2][6]=14;NeighborTable_new[2][7]=12;
	NeighborTable_new[2][8]=21;NeighborTable_new[2][9]=22;NeighborTable_new[2][10]=20;NeighborTable_new[2][11]=18;
	NeighborTable_new[2][12]=3;NeighborTable_new[2][13]=24;NeighborTable_new[2][14]=4;NeighborTable_new[2][15]=5;
	NeighborTable_new[2][16]=1;NeighborTable_new[2][17]=7;
}

vtkSmartPointer<vtkImageData> misRegionGrowing::GetSegmentedOutputImage()
{
	return m_OutputSegmentedImage;
}


void misRegionGrowing::SetImage(vtkImageData *input_image )
{
	m_BufferInputImage = (signed short*)input_image->GetScalarPointer();
	m_OutputSegmentedImage->SetExtent(input_image->GetExtent());
	m_OutputSegmentedImage->SetSpacing(input_image->GetSpacing());
	m_OutputSegmentedImage->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
 

	SetSpacing(input_image->GetSpacing());
	setImageSize(input_image->GetDimensions()[0] ,input_image->GetDimensions()[1] , input_image->GetDimensions()[2]);

	m_BufferOutputImage = (unsigned char*)m_OutputSegmentedImage->GetScalarPointer();
	int volumeSize = m_SizeX *m_SizeY * m_SizeZ;
	FillMemory(m_BufferOutputImage, volumeSize, m_Background);
 

	m_NumberOfMaximumSeeds =  volumeSize * 0.1; // 10 percent of all object
	//ObjectExtent initialization:
	m_ObjectExtend[0] = input_image->GetDimensions()[0];
	m_ObjectExtend[1] = 0;
	m_ObjectExtend[2] = input_image->GetDimensions()[1];
	m_ObjectExtend[3] = 0;
	m_ObjectExtend[4] = input_image->GetDimensions()[2];
	m_ObjectExtend[5] = 0;

	m_CancelSegmentation = false;
}

void misRegionGrowing::SetSpacing(double *spacing)
{
	m_Spacing[0] = spacing[0];
	m_Spacing[1] = spacing[1];
	m_Spacing[2] = spacing[2];
}

void misRegionGrowing::setImageSize( int a, int b, int c )
{
	m_SizeX = a; m_SizeY = b; m_SizeZ = c;
}

void misRegionGrowing::AddSeedInternally( int i , int j , int k )
{
	if (m_NumberOfPrimerySeeds < m_MaximumPrimarySeedSize)
	{
		misRGSeed s;
		s.x = i;
		s.y = j;
		s.z = k;
		m_PrimarySeeds.push_back(s);
		m_NumberOfPrimerySeeds++;
	}
}

void misRegionGrowing::AddSeedPosition( const double *position )
{
	//misImageGeoProperties  proGeo(m_vtkOutputImage);
	double*  spacing=m_OutputSegmentedImage->GetSpacing();
	double* origion=m_OutputSegmentedImage->GetOrigin();
	int imageIndexes[3];
	imageIndexes[2]=(position[2]-origion[2])/spacing[2];
	imageIndexes[1]=(position[1]-origion[1])/spacing[1];
	imageIndexes[0]=(position[0]-origion[0])/spacing[0];

	AddSeed(imageIndexes[0] , imageIndexes[1] , imageIndexes[2]);
}

void misRegionGrowing::ClearSeeds(void)
{
	m_NumberOfPrimerySeeds = 0;

	m_Newseeds.clear();
	m_OldSeeds.clear();
	m_PrimarySeeds.clear();
	m_BorderSeeds.clear();
}

void misRegionGrowing::CheckAndAddNewNeighbor( int& seedNeighborX, int& seedNeighborY, int& seedNeighborZ , int& seedType )
{
	if (!InMargin(seedNeighborX, seedNeighborY, seedNeighborZ))
		return;
	int index = CalculateIndex(seedNeighborX, seedNeighborY, seedNeighborZ);
	if (index != -1)
	{
		if (m_Background == m_BufferOutputImage[index])
		{
			bool a = GetLowerThreshold() < m_BufferInputImage[index];
			bool b = GetHigherThreshold() > m_BufferInputImage[index];
			bool c = PercentCheck(seedNeighborX, seedNeighborY, seedNeighborZ);
			if (a && b && c)
			{
				// add to seed list
				if (m_NumberOfNewSeeds < m_Newseeds.size())
				{
					m_Newseeds[m_NumberOfNewSeeds].x = seedNeighborX;
					m_Newseeds[m_NumberOfNewSeeds].y = seedNeighborY;
					m_Newseeds[m_NumberOfNewSeeds].z = seedNeighborZ;
				}
				else
				{
					misRGSeed s;
					s.x = seedNeighborX;
					s.y = seedNeighborY;
					s.z = seedNeighborZ;
					m_Newseeds.push_back(s);
				}

				m_NumberOfNewSeeds++;
				// add to the out image
				m_BufferOutputImage[index] = seedType;
			}//end if a&b
		}
	}
 
}

void misRegionGrowing::SetMaximumObjectValidity( double extent[6] )
{
	// with this setting the object region limit to specific area
	m_MaximumObjectValidRange[0] = extent[0];
	m_MaximumObjectValidRange[1] = extent[1];
	m_MaximumObjectValidRange[2] = extent[2];
	m_MaximumObjectValidRange[3] = extent[3];
	m_MaximumObjectValidRange[4] = extent[4];
	m_MaximumObjectValidRange[5] = extent[5];
	int maxVal = extent[1];
	if(extent[3] > maxVal)
		maxVal = extent[3];
	if(extent[5] > maxVal)
		maxVal = extent[5];

	m_BorderSeeds.clear();
}

void misRegionGrowing::ResetSetting( void )
{
	ResetMaximumObjectValidRange();
	m_ObjectExtend[0] = m_ObjectExtend[2] = m_ObjectExtend[4] =  10000;
	m_ObjectExtend[1] = m_ObjectExtend[3] = m_ObjectExtend[5] = -1;

	m_SizeX = -1;
	m_SizeY = -1;
	m_SizeZ = -1;

	m_Object = misSegmentedObject;
	m_Border = misObjectBorder;
	m_Background = misBackground;
	m_Margine = misMarginalRegion;

	SetLowerThreshold(1); //threshold1
	SetHigherThreshold(150); //threshold2

	m_NumberOfNewSeeds =0;
	m_NumberOfPrimerySeeds = 0;
	m_NumberOfBorderSeeds = 0;

	m_NeighborType = 26;
	m_Percentage = 100;
	m_MaxIter = 1000*1000*1000;

	ExtractBorderOff();
}

void misRegionGrowing::ExtractBorderOn( void )
{
	m_ExtractBorders =true;
}

void misRegionGrowing::ExtractBorderOff( void )
{
	m_ExtractBorders = false;
}

void misRegionGrowing::FinilaizeSeedType( int& currentSeedX, int& currentSeedY, int& currentSeedZ )
{
	int calculatedindex = CalculateIndex(currentSeedX ,currentSeedY,currentSeedZ);
	if (calculatedindex != -1)
	{
		if (true == m_ExtractBorders)
		{		
			//  convert seed to border or object
			if (true == IsObject(currentSeedX,currentSeedY,currentSeedZ))
			{
				m_BufferOutputImage[calculatedindex]= m_Object;
				m_NumberOfObjectSeed++;
			} 
			else
			{
				m_BufferOutputImage[calculatedindex]= m_Border;
				misRGSeed s ;
				s.x = currentSeedX;
				s.y = currentSeedY;
				s.z = currentSeedZ;
				m_BorderSeeds.push_back(s);
				m_NumberOfBorderSeeds++;
			}
		} 
		else
		{
			m_BufferOutputImage[calculatedindex]= m_Object;
		}
		UpdateObjectExtent(currentSeedX, currentSeedY, currentSeedZ);
	}
}

void misRegionGrowing::SetLowerThreshold( int lowerThreshold )
{
	m_LowerThreshold = lowerThreshold;
}

void misRegionGrowing::SetHigherThreshold( int higherThreshold )
{
	m_HigherThreshold = higherThreshold;
}

void misRegionGrowing::SetObjectValue( misRGObjectType objectType )
{
	m_Object = objectType;
}

void misRegionGrowing::SetBackgroundValue( misRGObjectType backgroundType )
{
	m_Background = backgroundType;
}

void misRegionGrowing::SetBorderValue( misRGObjectType borderType )
{
	m_Border = borderType;
}

void misRegionGrowing::SetMargineValue( misRGObjectType margineType )
{
	m_Margine = margineType;
}

void misRegionGrowing::SetNeighborType(int neighborType)
{
	m_NeighborType = neighborType;
}

void misRegionGrowing::SetPercentage(int percentage)
{
	m_Percentage = percentage;
}

bool misRegionGrowing::CheckSegmentationValues( void )
{
	// TODO: complete
	// check m_HigherThreshold must be really higher than m_lower and ... 
	return true;
}

void misRegionGrowing::SetMaxIter( int maxIter )
{
	m_MaxIter = maxIter;
}

void misRegionGrowing::LimitBoundaryPosition(double *spacing)
{
	m_MaximumObjectValidRange[0] = (m_MaximumObjectValidRange[0]/spacing[0]);
	m_MaximumObjectValidRange[1] = (m_MaximumObjectValidRange[1]/spacing[0]);
	
	m_MaximumObjectValidRange[2] = (m_MaximumObjectValidRange[2]/spacing[1]);
	m_MaximumObjectValidRange[3] = (m_MaximumObjectValidRange[3]/spacing[1]);
	
	m_MaximumObjectValidRange[4] = (m_MaximumObjectValidRange[4]/spacing[2]);
	m_MaximumObjectValidRange[5] = (m_MaximumObjectValidRange[5]/spacing[2]);
	
}

bool misRegionGrowing::UpdateMaximumObjectValidityWithoutROI( void )
{

	if (m_MaximumObjectValidRange[0] < 1)
		m_MaximumObjectValidRange[0] =0;

	if (m_MaximumObjectValidRange[2] < 1)
		m_MaximumObjectValidRange[2] =0;

	if (m_MaximumObjectValidRange[4] < 1)
		m_MaximumObjectValidRange[4] =0;

	if (0 >= m_MaximumObjectValidRange[1])
	{
		m_MaximumObjectValidRange[1] = m_SizeX;
	}
	else if (m_MaximumObjectValidRange[1] >= (m_SizeX-1) )
	{
		m_MaximumObjectValidRange[1] = m_SizeX-2;
	}

	if (0 >= m_MaximumObjectValidRange[3])
	{
		m_MaximumObjectValidRange[3] = m_SizeY;
	}
	else if (m_MaximumObjectValidRange[3] >= (m_SizeY-1) )
	{
		m_MaximumObjectValidRange[3] = m_SizeY-2;
	}

	if (0 >= m_MaximumObjectValidRange[5])
	{
		m_MaximumObjectValidRange[5] = m_SizeZ;
	}
	else if (m_MaximumObjectValidRange[5] >= (m_SizeZ-1) )
	{
		m_MaximumObjectValidRange[5] = m_SizeZ-2;
	}

	if (m_MaximumObjectValidRange[0] < m_MaximumObjectValidRange[1])
	{
		if (m_MaximumObjectValidRange[2] < m_MaximumObjectValidRange[3])
		{
			if (m_MaximumObjectValidRange[4] <m_MaximumObjectValidRange[5])
			{
				int maxVal = m_MaximumObjectValidRange[1];
				if(m_MaximumObjectValidRange[3] > maxVal)
					maxVal = m_MaximumObjectValidRange[3];
				if(m_MaximumObjectValidRange[5] > maxVal)
					maxVal = m_MaximumObjectValidRange[5];

				//m_BorderSeeds.clear();

				return true;
			}
		}
	}

	return false;
}

bool misRegionGrowing::UpdateMaximumObjectValidityWithROI( void )
{
	if (m_MaximumObjectValidRange[0] < 1)
		m_MaximumObjectValidRange[0] =1;

	if (m_MaximumObjectValidRange[2] < 1)
		m_MaximumObjectValidRange[2] =1;

	if (m_MaximumObjectValidRange[4] < 1)
		m_MaximumObjectValidRange[4] =1;
	int temp;

	if (m_MaximumObjectValidRange[0] > m_MaximumObjectValidRange[1])
	{
		temp = m_MaximumObjectValidRange[0];
		m_MaximumObjectValidRange[0] = m_MaximumObjectValidRange[1];
		m_MaximumObjectValidRange[1] = temp;
	}

	if (m_MaximumObjectValidRange[2] > m_MaximumObjectValidRange[3])
	{
		temp = m_MaximumObjectValidRange[2];
		m_MaximumObjectValidRange[2] = m_MaximumObjectValidRange[3];
		m_MaximumObjectValidRange[3] = temp;
	}

	if (m_MaximumObjectValidRange[4] > m_MaximumObjectValidRange[5])
	{
		temp = m_MaximumObjectValidRange[4];
		m_MaximumObjectValidRange[4] = m_MaximumObjectValidRange[5];
		m_MaximumObjectValidRange[5] = temp;
	}
	// check correct region
	if (m_MaximumObjectValidRange[0] < m_MaximumObjectValidRange[1])
	{
		if (m_MaximumObjectValidRange[2] < m_MaximumObjectValidRange[3])
		{
			if (m_MaximumObjectValidRange[4] < m_MaximumObjectValidRange[5])
			{
				return true;
			}
		}

	}
	return false;
}

void misRegionGrowing::RequestCancelSegmentation(void)
{
	WaitForSingleObject( GetMutex(), INFINITE );
	m_CancelSegmentation = true;
	ReleaseMutex( GetMutex() );
}

bool misRegionGrowing::CancelSegmentationStatus(void)
{
	WaitForSingleObject( GetMutex(), INFINITE );
	bool CancelSegmentationStatus = m_CancelSegmentation;
	ReleaseMutex( GetMutex() );
	return CancelSegmentationStatus;
}

RGState misRegionGrowing::GetRegionGrowingState(void)
{
	return m_State;
}

void misRegionGrowing::SetThresholdChecking( bool thresholdCheck )
{
	m_ThresholdChecking = thresholdCheck;
}

int* misRegionGrowing::GetBorders()
{
	return m_ObjectExtend;
}

void misRegionGrowing::UpdateObjectExtent( int& i , int& j , int& k )
{
	if (i < m_ObjectExtend[0])
		m_ObjectExtend[0] = i;
	else if(i > m_ObjectExtend[1])
		m_ObjectExtend[1] = i;
	
	if (j < m_ObjectExtend[2])
		m_ObjectExtend[2] = j;
	else if(j > m_ObjectExtend[3])
		m_ObjectExtend[3] = j;

	if (k < m_ObjectExtend[4])
		m_ObjectExtend[4] = k;
	else if(k > m_ObjectExtend[5])
		m_ObjectExtend[5] = k;
}

void misRegionGrowing::UpdateBorderVoxels()
{
	for (int i = m_ObjectExtend[0]; i <= m_ObjectExtend[1]; i++)
	{
		for (int j = m_ObjectExtend[2] ; j <= m_ObjectExtend[3]; j++)
		{
			for (int k = m_ObjectExtend[4] ; k <= m_ObjectExtend[5]; k++)
			{
				int index = CalculateIndex(i ,j,k);
				if (index != -1)
				{
					if (m_BufferOutputImage[index] == m_Object)
					{
						if (true == IsBorder(i, j , k))
						{
							m_BufferOutputImage[index] = m_Border;
							misRGSeed s;
							s.x =i;
							s.y =j;
							s.z = k;
							m_BorderSeeds.push_back(s);
							//m_BorderSeeds[m_NumberOfBorderSeeds] = s;
							m_NumberOfBorderSeeds++;
						}
					}
				}	
 				else
 					_ASSERT( 0 );
			}
		}
	}
}

bool misRegionGrowing::IsBorder( int& i , int& j , int& k )
{
	int coordinate;
	int neighborX,neighborY,neighborZ;
	int neighborNumbers = m_NeighborType;
	int index;
	if (neighborNumbers == 26)
		index = 0;
	else if(neighborNumbers == 6)
		index = 1;
	else if(neighborNumbers == 18)
		index = 2;
	for (int neighborNO = 0 ; neighborNO < neighborNumbers ; neighborNO++ )
	{            
		int i2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][0];
		int j2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][1];
		int k2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][2];
		int t2 = m_TypeCoordination[NeighborTable_new[index][neighborNO]][3];

		neighborX = i+i2;
		neighborY = j+j2;
		neighborZ = k+k2;
		if(true == InMargin(neighborX, neighborY , neighborZ))
		{
			coordinate = CalculateIndex(neighborX, neighborY , neighborZ);
			if (coordinate != -1)
			{
				if ( m_BufferOutputImage[coordinate] == m_Background )
				{
					return true;
				}
			}	
		}
		else 
		{
			return true;
		}
	}
	return false;
}

void misRegionGrowing::ResetMaximumObjectValidRange()
{
	m_MaximumObjectValidRange[0] = -1;
	m_MaximumObjectValidRange[1] = -1;
	m_MaximumObjectValidRange[2] = -1;
	m_MaximumObjectValidRange[3] = -1;
	m_MaximumObjectValidRange[4] = -1;
	m_MaximumObjectValidRange[5] = -1;
}

void misRegionGrowing::ApplyMarginalBorder()
{
	m_IsMargineActive = true;
	
	for (int i = 0; i < m_BorderSeeds.size()/*= m_NumberOfBorderSeeds*/; i++)
	{
		ExpandSeeds(m_BorderSeeds[i].x, m_BorderSeeds[i].y, m_BorderSeeds[i].z, m_NumberOfMargineVoxel);
	}
	m_IsMargineActive = false;
}

void misRegionGrowing::SetNumberOfMargineVoxel(int voxelNum)
{
	m_NumberOfMargineVoxel[0] = voxelNum;
	m_NumberOfMargineVoxel[1] = voxelNum;
	m_NumberOfMargineVoxel[2] = voxelNum;
}

void misRegionGrowing::SetDistanceFromMargine(double distance)
{
	m_NumberOfMargineVoxel[0] = distance / m_Spacing[0];
	m_NumberOfMargineVoxel[1] = distance / m_Spacing[1];
	m_NumberOfMargineVoxel[2] = distance / m_Spacing[2];
}

void misRegionGrowing::ExtractBorders()
{
	if ((0 == m_BufferInputImage) || (0 == m_BufferOutputImage))
	{
		return;
	}
	if ((0 >= m_SizeX) || (0 >= m_SizeY) || (0 >= m_SizeZ))
	{
		return;
	}
	UpdateMaximumObjectValidityWithoutROI();
	m_ObjectExtend[0] = m_ObjectExtend[2] = m_ObjectExtend[4] = 0;
	m_ObjectExtend[1] = m_SizeX - 1;
	m_ObjectExtend[3] = m_SizeY - 1;
	m_ObjectExtend[5] = m_SizeZ - 1;

	for (int i = m_ObjectExtend[0]; i <= m_ObjectExtend[1]; i++)
	{
		for (int j = m_ObjectExtend[2]; j <= m_ObjectExtend[3]; j++)
		{
			for (int k = m_ObjectExtend[4]; k <= m_ObjectExtend[5]; k++)
			{
				int index = CalculateIndex(i, j, k);
				if (index != -1)
				{
					if (m_BufferInputImage[index] == m_Object)
						m_BufferOutputImage[index] = m_Object;
					else if (m_BufferInputImage[index] == m_Border)
					{
						m_BufferOutputImage[index] = m_Border;
						misRGSeed s;
						s.x = i;
						s.y = j;
						s.z = k;
						m_BorderSeeds.push_back(s);
						m_NumberOfBorderSeeds++;
					}
				}
			}
		}
	}
}

void misRegionGrowing::ApplyMarginToImage(vtkSmartPointer<vtkImageData> currentImage, double MarginValue)
{
	SetImage(currentImage);
	ExtractBorders();
	SetDistanceFromMargine(MarginValue);
	ApplyMarginalBorder();
}

int misRegionGrowing::GetHigherThreshold() const
{
	return m_HigherThreshold;
}

vector<misRGSeed> misRegionGrowing::ExpandSeeds(int& SeedX, int& SeedY, int& SeedZ, double ExpandNum[3])
{
	int counter = 0;
	int count1 = 0;
	vector<misRGSeed> expandedSeeds;
	expandedSeeds.clear();
	if (!m_BufferOutputImage)
		return expandedSeeds;

	m_NumberOfExpandedSeeds = 0;
	for (int i = -ExpandNum[0]; i <= ExpandNum[0]; i++)
	{
		for (int j = -ExpandNum[1]; j <= ExpandNum[1]; j++)
		{
			for (int k = -ExpandNum[2]; k <= ExpandNum[2]; k++)
			{
				int x_temp = SeedX + i;
				int y_temp = SeedY + j;
				int z_temp = SeedZ + k;
				if (true == InMargin(x_temp, y_temp, z_temp))
				{
					int index = CalculateIndex(x_temp, y_temp, z_temp);
					if (index != -1)
					{

						if (m_BufferOutputImage[index] == m_Background)
						{
							if (m_NumberOfExpandedSeeds < m_MaximumPrimarySeedSize)
							{
								if (m_IsMargineActive == false)
								{
									misRGSeed s;
									s.x = x_temp;
									s.y = y_temp;
									s.z = z_temp;
									expandedSeeds.push_back(s);
									m_NumberOfExpandedSeeds++;
								}

								else if (m_IsMargineActive)
								{
									if (m_Margine == m_Object)
									{
										if (m_BufferInputImage[index] > -5000)	//[]<5000 in the case of +10000
											m_BufferInputImage[index] -= 10000;
									}
									else if (m_Margine == misMarginalRegion)
									{
										m_BufferOutputImage[index] = m_Margine;
										((unsigned char*)m_OutputSegmentedImage->GetScalarPointer())[index] = m_Margine;
									}

									count1++;
								}
							}
						}
					}
				}
				else counter++;
			}
		}
	}
	if (m_NumberOfExpandedSeeds == 0)
	{
		//delete expandedSeeds;
	}
	return expandedSeeds;
}

void misRegionGrowing::AddSeed(int i, int j, int k)
{
	if (m_ThresholdChecking == true)
	{
		AddSeedInternally(i, j, k);
	}
	else if (m_ThresholdChecking == false)
	{
		double val[3] = { 2,2,2 };
		m_PrimarySeeds = ExpandSeeds(i, j, k, val);
		m_NumberOfPrimerySeeds = m_NumberOfExpandedSeeds;
	}
}





