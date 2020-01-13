#pragma once

#include "misDejitterizedValue.h"
#include "misMacros.h"

class misSmoothToolData
{
	typedef ::itk::Vector<double, 3>	VectorType;
	typedef ::itk::Versor<double>		VersorType;
	enum toolDataGatheringStatus
	{
		ContineusGhadering,
		FirstJitterHappend,
		MovingTool
	};
public:
	misSmoothToolData(void);
	~misSmoothToolData(void);
	void UpdatelastTransformInformations(vtkMatrix4x4*  finalRegistredRelativeMatrix);
private:
	misCreateVariableWithGetMacro(KernelSize,int);
	misCreateVariableWithSetGetMacro(MinDistanseofJitter,double);
	misCreateVariableWithSetGetMacro(MinRotationofJitter,double);
 	double          m_PreviousTipPosition[3];
	double          m_TipPosition[3];
	VersorType      m_PreviosTipQuternion;
	toolDataGatheringStatus    m_JitterStatus;
	bool                m_ToolHasBeenFixed;
	// Note : for performance consideration the std::vector not used
	vtkMatrix4x4**     	m_LastInitialTransforms;
	double                  m_LastMovement;
	double                  m_LastRotation;
	std::vector<double>					m_SmoothingWeights;
	int                     m_startIDofKernel;
	void    UseDefaultWeights(void);
	vtkMatrix4x4* UpdateLastSmoothedMatrix(vtkMatrix4x4* lastRaw,vtkMatrix4x4* prevSmoothedMatrix);
	void CheckToolHasBeenFixed( vtkMatrix4x4* lastRawMatrix);
	void   NormalizedWeights(int startID=0);
	void   UpdateTransitionKernelWeight(void);
	void            SetDefaultKernel(int kernelSize);
	double          GetLastMovement(void){return this->m_LastMovement;};
	double          GetLastRotation(void){return this->m_LastRotation;};
	void ResetSmoohingKernel( void );
	
};


