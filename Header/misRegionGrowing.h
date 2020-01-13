#pragma once

#include "misAnalysisStudioTypes.h"
#include "misEnums.h"
#include "misLibraryMacroes.h"
#include "IRegionGrowing.h"

//#define 6-Connected  6
//#define 18-Connected  18
//#define 26-Connected 26

class   misRegionGrowing :public IRegionGrowing
{

public:
	misRegionGrowing(void);
 

	virtual void AddSeed(int i, int j, int k);
	virtual void AddSeedPosition(const double *position);
	bool UpdateMaximumObjectValidityWithoutROI(void);
	bool UpdateMaximumObjectValidityWithROI(void);
	bool Calculation(void);
	bool CancelSegmentationStatus(void);
	void ResetSetting(void);
	void ResetMaximumObjectValidRange();
	void SetImage(vtkImageData *input_image);
	void SetMaximumObjectValidity(double extent[6]);
	void LimitBoundaryPosition(double * spacing);
	void ClearSeeds(void);
	void ExtractBorderOn(void);
	void ExtractBorderOff(void);
	void  SetLowerThreshold(int lowerThreshold);
	void  SetHigherThreshold(int higherThreshold);
	void SetMargineValue(misRGObjectType margineType);
	void RequestCancelSegmentation(void);
	void SetThresholdChecking(bool);
	void SetNumberOfMargineVoxel(int voxelNum);
	int* GetBorders();
	RGState  GetRegionGrowingState(void);
	vtkSmartPointer<vtkImageData> GetSegmentedOutputImage();

	void SetDistanceFromMargine(double distance);



	HANDLE GetMutex() const { return m_mutex; }
	void SetMutex(HANDLE val) { m_mutex = val; }
	int GetLowerThreshold() const { return m_LowerThreshold; }
	int GetHigherThreshold() const;
	void ApplyMarginalBorder();
	void ExtractBorders();
	virtual void ApplyMarginToImage(vtkSmartPointer<vtkImageData> currentImage, double MarginValue);
	
private:
	int CalculateIndex(int& i, int& j, int& k);
	void SetBackgroundValue(misRGObjectType backgroundType);
	void SetObjectValue(misRGObjectType objectType);
	void SetBorderValue(misRGObjectType borderType);
	void SetNeighborType(int neighborType);
	void SetPercentage(int percentage);
	void SetMaxIter(int maxIter);
	void SetSpacing(double *spacing);
	void setImageSize(int a, int b, int c);
	void UpdateBorderVoxels();
	void FinilaizeSeedType(int& currentSeedX, int& currentSeedY, int& currentSeedZ);
	void CheckAndAddNewNeighbor(int& seedNeighborX, int& seedNeighborY, int& seedNeighborZ, int& seedType);
	bool IsObject(int& i, int& j, int& k);
	bool IsBorder(int& i, int& j, int& k);
	bool PercentCheck(int& i, int& j, int& k);
	bool InMargin(int& i, int& j, int& k);
	void SetNeighborNumber(int neighbor[]);
	void UpdateObjectExtent(int& i, int& j, int& k);
	int  MoveNewSeedsToOldPosition(void);
	int  InitialPrimerySeeds(void);
	void	LookupTableDefinition();
	void SetSeedColor(int color[]);
	bool    CheckSegmentationValues(void);
	std::vector<misRGSeed> ExpandSeeds(int& SeedX, int& SeedY, int& SeedZ, double ExpandNum[3]);
	void AddSeedInternally(int i, int j, int k);

	signed short *	m_BufferInputImage;
	unsigned char*	m_BufferOutputImage;
	int			    m_ObjectExtend[6]; //xmin, xmax, ymin, ymax, zmin, zmax--> finding borders	
	misRGObjectType	m_Object, m_Border, m_Margine, m_Background;
	std::vector<misRGSeed> m_OldSeeds;
	std::vector<misRGSeed> m_Newseeds;
	std::vector<misRGSeed> m_PrimarySeeds;
	std::vector<misRGSeed> m_BorderSeeds;
	int				x;
	int				y;
	int				z;
	int				m_SizeX;
	int				m_SizeY;
	int				m_SizeZ;
	int				m_MaximumPrimarySeedSize;
	int				m_NumberOfMaximumSeeds;
	int				m_NumberOfNewSeeds;
	int				m_NumberOfPrimerySeeds;
	int				m_NumberOfBorderSeeds;
	int				m_NumberOfObjectSeed;
	int				m_NeighborType;
	int				m_Percentage;
	int				m_MaxIter;
	int				m_TypeCoordination[26][4];
	int				Neighbor_number[27];
	int				m_NeighborTable[27][26];
	int				NeighborTable_new[3][26];
	bool			m_CancelSegmentation;
	bool			m_ThresholdChecking;
	bool            m_ExtractBorders;
	double			m_Spacing[3];
	double			m_MaximumObjectValidRange[6];
	RGState			m_State;
	vtkSmartPointer<vtkImageData> m_OutputSegmentedImage;
	HANDLE		m_mutex;
	int	m_LowerThreshold;
	int m_HigherThreshold;
	int m_NumberOfExpandedSeeds;
	double m_NumberOfMargineVoxel[3];
	bool m_IsMargineActive;
};
