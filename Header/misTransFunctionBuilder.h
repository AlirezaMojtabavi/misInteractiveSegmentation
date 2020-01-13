#pragma once

#include "misOpenglTexture.h"
#include "misStrctColorData.h"
#include "misWindowLevelStr.h"
#include "Colormap.h"

enum ColorMap
{
	AUTUMN,
	BONE,
	//COLORCUBE,
	COOL,
	COPPER,
	FLAG,
	GRAY,
	HOT,
	HSV,
	JET,
	//LINES,
	//PINK,
	//PRISM,
	SPRING,
	SUMMER,
	WHITE,
	WINTER,
	NUMCOLORMAPS
};

class misTransFunctionBuilder
{
public:

	~misTransFunctionBuilder(void);
	misTransFunctionBuilder(void);

	//Maps a value between 0~1
	//@Param val is the value which is going to be mapped to 0~1 interval
	//@Param TableRange determines the min and max of range
	static 	float ConvertIntensityToKeyValue( const double* TableRange , double val );
	
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( double* TableRange , misImageDataModality modality);
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( double* TableRange , misImageDataModality modality , misColorStruct color , 
		double opacity );
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( misDoubleColorListTypedef opacityColorList ,double* TableRange );
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( std::vector<misColorStruct> colorStruct );
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( misWindowLevelStr wlStr , bool showErased , double* TableRange ,
		misColorStruct ColorStr);
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( double* TableRange , double threshold );
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction(misColorListTypedef colorList, double* TableRange);
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction(Colormap colorList);
	static std::shared_ptr<TransFuncIntensity> GenerateTransferFunction( misWindowLevelStr wlStr);


	std::shared_ptr<TransFuncIntensity> GetnerateSkinTransferFunction( double* TableRange );
	std::shared_ptr<TransFuncIntensity> GenerateOpaceBone( double* TableRange ,double normalizedOpacity);
	std::shared_ptr<TransFuncIntensity> GenerateImageFMRITransferFunction( double* TableRange );
	std::shared_ptr<TransFuncIntensity> GetnerateVolumeFMRITransferFunction( double* TableRange );
	std::shared_ptr<TransFuncIntensity> GenerateDentalTransferFunction();

private:
	 std::vector< unsigned char*> colormap[NUMCOLORMAPS];
	 bool colormapInitialized;
	 void ColormapInit();
	 unsigned char* vec_init(unsigned char,unsigned char,unsigned char,unsigned char);

};
