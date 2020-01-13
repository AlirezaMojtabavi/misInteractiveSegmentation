#pragma once

#include "IParametricSpline.h"
#include "ITextureGenerator.h"

// The misPanoramicTextureGenerator class implements the ITextureGenerator interface and is used for creating a panoramic view
// 2D texture. The created 2D texture will map panoramic coordinates (S, N) to their corresponding image coordinates (X, Y)
// The Z image coordinate is shared by both panoramic and image space. The created texture is used by the shader to render the
// panoramic view.
class misPanoramicTextureGenerator : public ITextureGenerator
{
public:
	class Injector
	{
	public:
		std::shared_ptr<IParametricSpline> CreateParametricSpline(std::vector<PointType> splinePoints, double precision ) const;
	};

	// The class will takes set of a spline points that define the panoramic curve 
	// dS is the step size along tangent of the spline and has same unit with curve length
	// dN is the step size along normal of the spline and has same unit with curve length
	// intervalN is the maximum distance along the curve normal that should be covered by the texture.
	misPanoramicTextureGenerator(const std::vector<PointType>& points, double dS, double dN, double intervalN, 
		const double& imageWidth,const double& imageHeight, double precision, std::shared_ptr<Injector> injector = nullptr);

	virtual std::shared_ptr<TextureData> GetPanoramicTexture() const override;

	void FillTextureElements( int elementIndex, const itk::Point<double, 3> point ) const;

	

	

private:
	// Find number of Samples along Tangent and normal of the spline according to the class data
	void FindNumOfSamples();

	// Find Spline Parameter Step Size Along based on number of sample along the spline tangent
	double FindSplineParamStepSize( const std::shared_ptr<IParametricSpline> displacedSpline,
		int numberOfSamplesAlongCurveTangent ) const;

	// Original curve is the central curve which is given by user and other curve created by displacing this curve along it's 
	// normalVector
	std::shared_ptr<IParametricSpline> m_OriginalCurveSpline;
	
	double m_StepSizeAlongCurveTangent, m_StepSizeAlongCurveNormal;

	// Defies min and max curve displacement along curve normal
	double m_CurveDisplacementRange;
	std::shared_ptr<Injector> m_Injector;
	double m_ImageWidth;
	double m_ImageHeight;
	double m_LengthPrecision;
	int m_NumberOfSamplesAlongCurveTangent, m_NumberOfSamplesAlongCurveNormal ;
	std::shared_ptr<TextureData> m_PanoramicToImageTexture;

};