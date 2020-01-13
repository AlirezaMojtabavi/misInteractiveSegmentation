#pragma once

#include "misObject.h"
#include "misColorStruct.h"

class misTransferFunction : public misOldObject
{
private:

	GLint	m_TfIndex;
	double* m_TableRange;
	float	m_Threshold;
	TransFuncIntensity *m_TransferFunc;
	int		m_WidthExpansionScale;
	void	UpdateKeyDist();
	void	InitializeGL();
	inline float	CalculateFloatValue(double intensity);

public:

	typedef misTransferFunction					Self;
	typedef misOldObject							 Superclass;
	typedef ::itk::SmartPointer< Self >			 Pointer;
	typedef ::itk::SmartPointer< const Self >	 ConstPointer;

	static Pointer					New(double* TableRange);
	void							Reset();
	void							setThresholds(float lower, float upper);
	void							setTableRange(double* tableRange);
	void							GenerateKey(double i , misColorStruct colorstruct);
	void							GenerateKey(float intensity, misColorStruct colorstruct ,float alpha);
	void							GenerateKey(double i , float red , float green , float blue , float alpha);
	void							CreateTexture();
	void							CreateTexturefromTransferFunction(TransFuncIntensity* transferFunc);
	double*							getTableRange(){return m_TableRange; }
	GLint							getTextureIndex(){return m_TfIndex;}
	 TransFuncIntensity*		getTransferFunction();
	misTransferFunction(double* TableRange);
	~misTransferFunction(void);
	void AddZeroIntensityKey();
};
