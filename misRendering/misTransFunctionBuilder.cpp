#include "StdAfx.h"
#include "misTransFunctionBuilder.h"

#include "misEnums.h"
#include "misTransferFunction.h"
#include "misWindowLevelStr.h"
#include "misfMRIColorTable.h"
#include "misTFILoader.h"
#include "misDebug.h"

using namespace std;

misTransFunctionBuilder::misTransFunctionBuilder(void)
{
	colormapInitialized = false;
	ColormapInit();
}

misTransFunctionBuilder::~misTransFunctionBuilder(void)
{
}

float misTransFunctionBuilder::ConvertIntensityToKeyValue(const double* TableRange , double val )
{
	if (TableRange)
	{
		float key = static_cast<float> ( (val - TableRange[0] )/(TableRange[1] - TableRange[0]));
		return key;
	}
	return -1.0;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction( double* TableRange , misImageDataModality modality )
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();


	if (modality == CT)
	{
		// threshold = -450 for vtkImageData
		// threshold = 2000 for dcmtkImage
		float skinthresholdvalue = ConvertIntensityToKeyValue(TableRange,-450.0f);
		float bonethresholdvalue = ConvertIntensityToKeyValue(TableRange,500.0f);
		TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::vec4(0,0,0,0));
		IntensityFunc->addKey(key0);
		TransFuncMappingKey *skin0 = new TransFuncMappingKey( skinthresholdvalue , tgt::col4(247,222,166,0));
		IntensityFunc->addKey(skin0);
		TransFuncMappingKey *skin1 = new TransFuncMappingKey( skinthresholdvalue + 0.03f , tgt::col4(247,222,166,50));
		IntensityFunc->addKey(skin1);	
		TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(255,255,255,255));
		IntensityFunc->addKey(key1);
	}

	if (modality == MRI)
	{

		float skinthresholdvalue = ConvertIntensityToKeyValue(TableRange,100.0);;
		TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::vec4(0,0,0,0));
		IntensityFunc->addKey(key0);
		TransFuncMappingKey *skin0 = new TransFuncMappingKey( skinthresholdvalue , tgt::col4(247,222,166,0));
		IntensityFunc->addKey(skin0);
		TransFuncMappingKey *skin1 = new TransFuncMappingKey( skinthresholdvalue + 0.05f , tgt::col4(247,0,166,50));
		IntensityFunc->addKey(skin1);
		TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(255,255,255,255));
		IntensityFunc->addKey(key1);
	}
	return IntensityFunc;

}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction( double* TableRange , misImageDataModality modality  ,
	misColorStruct color , double opacity )
{
	float threshold;
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();

	if (modality == CT)
		threshold = ConvertIntensityToKeyValue(TableRange,-450);
	else if (modality == MRI)
		threshold=ConvertIntensityToKeyValue(TableRange,100);
	else
	{
		threshold= ConvertIntensityToKeyValue(TableRange,-450);;
		cout<<endl<<"UNKNOWN MODALITY!! UNABLE TO CALCULATE TRANSFER FUNCTION CT  assumed."<<endl;
		_ASSERT(true == false);
	}

	TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::vec4(0,0,0,0));
	IntensityFunc->addKey(key0);
	TransFuncMappingKey *skin0 = new TransFuncMappingKey( threshold , tgt::col4(color.red,color.green,color.blue,0));
	IntensityFunc->addKey(skin0);
	TransFuncMappingKey *skin1 = new TransFuncMappingKey( threshold + 0.03f , tgt::col4(static_cast<uint8_t> (color.red),
		static_cast<uint8_t> (color.green),static_cast<uint8_t> (color.blue), static_cast<uint8_t> (opacity*255)));
	IntensityFunc->addKey(skin1);
	TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(255,255,255,0));
	IntensityFunc->addKey(key1);

	return IntensityFunc;

}


std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction(misDoubleColorListTypedef opacityColorList, double* TableRange)
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();
	for ( auto it = opacityColorList.begin() ; it != opacityColorList.end(); it++ )
	{
		uint8_t red    = static_cast<uint8_t> (it->second.Red * 255); 
		uint8_t green  = static_cast<uint8_t> (it->second.Green * 255) ;
		uint8_t blue   = static_cast<uint8_t> (it->second.Blue * 255);
		uint8_t alpha  = static_cast<uint8_t> (it->second.Alpha * 255);
		auto color =  tgt::col4(red, green, blue, alpha);
		auto val = ConvertIntensityToKeyValue(TableRange, it->first);
		TransFuncMappingKey *key0 = new TransFuncMappingKey( val , color);
		IntensityFunc->addKey(key0);
	}
	return IntensityFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction(misColorListTypedef colorList,
	double* TableRange)
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();
	for ( auto it = colorList.begin() ; it != colorList.end(); it++ )
	{
		uint8_t red    = static_cast<uint8_t> (it->second.red); 
		uint8_t green  = static_cast<uint8_t> (it->second.green);
		uint8_t blue   = static_cast<uint8_t> (it->second.blue);
		uint8_t alpha  = static_cast<uint8_t> (it->second.alpha);
		auto color =  tgt::col4(red, green, blue, alpha);
		auto val = ConvertIntensityToKeyValue(TableRange, it->first);
		auto key = new TransFuncMappingKey(val , color);
		IntensityFunc->addKey(key);
	}
	IntensityFunc->updateTexture();
	return IntensityFunc;
}


std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction( vector<misColorStruct> colorStruct )
{
	if (0 == colorStruct.size())
	{
		cout<<"\n\n	Empty Color Struct !!!!  \n";
		_ASSERT(true == false);
	}

	//	important : THE DIMENSION OF TRANSFER FUNCTION TEXTURE IS THE SAME AS COLORSTRUCT.size()
	//  MEANING IF THE COLORS ARE 0-255 , THIS VALUE SHOULD BE 256.
	int TexSize = static_cast<int> (colorStruct.size());
	double TableRange[2];
	TableRange[0] = 0 ;
	TableRange[1] = static_cast<double> (TexSize-1); // max intensity of the colormap 

	auto transferFunc = std::make_shared<TransFuncIntensity>(TexSize);
	transferFunc->clearKeys();

	TransFuncMappingKey *key;
	int i=0;
	tgt::col4 color;
	tgt::col4 blackColor = tgt::col4(0,0,0,0);
	misColorStruct colorStr;	


	// the inner 'for' is for adding two surrounding pure_black keys to surround
	//	a colored key. it is essential to do this, because we don't want the values
	//	between one object and the next to have any color ( i.e. margin values )

	// it 's either this or that we would have to have a key for every possible intensity of colormap.


	for(int i = 0 ; i < colorStruct.size() ; i++)
	{
		colorStr = colorStruct[i];
		auto val=ConvertIntensityToKeyValue(TableRange, i);
		color = tgt::col4(static_cast<uint8_t> (colorStr.red), static_cast<uint8_t> (colorStr.green), 
			static_cast<uint8_t> (colorStr.blue), static_cast<uint8_t> (colorStr.alpha*255));
		key = new TransFuncMappingKey( val , color);
		transferFunc->addKeysInOrder(key);	
	}
	transferFunc->updateTexture();
	return transferFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction( misWindowLevelStr wlStr , bool showErased ,
	double* tableRange , misColorStruct colorStr )
{
	if (0 == tableRange)
	{
		cout<<endl<<"Table Range is Empty. It's very much necessary for duplicating WindowLevel transfer function."<<endl;
		_ASSERT(true == false);
	}		

	tgt::col4 blackColor = tgt::col4(0, 0, 0, 255);
	tgt::col4 whiteColor = tgt::col4(255, 255, 255, 255);
	tgt::col4 erasedcolor = tgt::col4(static_cast<uint8_t>(colorStr.red), static_cast<uint8_t>(colorStr.green),
		static_cast<uint8_t>(colorStr.blue), static_cast<uint8_t>(colorStr.alpha));
	float t, first, last;

	int Texsize = static_cast<int>(tableRange[1] - tableRange[0] + 1);
	auto transferFunc = std::make_shared<TransFuncIntensity>(Texsize);
	transferFunc->clearKeys();

	TransFuncMappingKey * key = new TransFuncMappingKey( 0.0 , blackColor );
	transferFunc->addKey(key);
	
	float center = static_cast<float>(wlStr.GetWindowCenter());
	float width = static_cast<float>(wlStr.GetWindowWidth());
	t = center - width / 2 ;
	first = ConvertIntensityToKeyValue(tableRange, t);
	key = new TransFuncMappingKey(first , blackColor );
	transferFunc->addKey(key);

	t = center + width / 2 ;
	last = ConvertIntensityToKeyValue(tableRange, t);
	key = new TransFuncMappingKey(last , whiteColor );
	transferFunc->addKey(key);

	// If there was a high intensity as a noise it can be filtered here by set a black threshold for that specific intensity

	if (showErased)
	{
		key = new TransFuncMappingKey(first + 0.5f , blackColor );
		transferFunc->addKey(key);

		key = new TransFuncMappingKey( last + 0.5f , erasedcolor );
		transferFunc->addKey(key);

		key = new TransFuncMappingKey( 1.0f , erasedcolor );
		transferFunc->addKey(key);
	}

	return transferFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction( double* TableRange , double threshold )
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();
	float normthreshold = ConvertIntensityToKeyValue(TableRange,threshold);

	TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::col4(0,0,0,0));
	IntensityFunc->addKey(key0);
	TransFuncMappingKey *skin0 = new TransFuncMappingKey( normthreshold , tgt::col4(247,222,166,0));
	IntensityFunc->addKey(skin0);
	TransFuncMappingKey *skin1 = new TransFuncMappingKey( normthreshold + 0.03f , tgt::col4(247,222,166,50));
	IntensityFunc->addKey(skin1);	
	TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(255,255,255,255));
	IntensityFunc->addKey(key1);
	return IntensityFunc;

}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction( misWindowLevelStr wlStr )
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();

	TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::col4(0,0,0,0));
	IntensityFunc->addKey(key0);
	TransFuncMappingKey *skin0 = new TransFuncMappingKey( 0.33f , tgt::col4(0,0,0,1));
	IntensityFunc->addKey(skin0);
	TransFuncMappingKey *skin1 = new TransFuncMappingKey( 0.66f , tgt::col4(255,255,255,255));
	IntensityFunc->addKey(skin1);	
	TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(255,255,255,255));
	IntensityFunc->addKey(key1);



	return IntensityFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateTransferFunction(Colormap colorList)

{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();
	for (auto elemnt : colorList)
	{
		uint8_t red = static_cast<uint8_t> (elemnt.second.r);
		uint8_t green = static_cast<uint8_t> (elemnt.second.g);
		uint8_t blue = static_cast<uint8_t> (elemnt.second.b);
		uint8_t alpha = static_cast<uint8_t> (elemnt.second.a);
		auto color = tgt::col4(red, green, blue, alpha);
		auto key = new TransFuncMappingKey(elemnt.first, color);
		IntensityFunc->addKey(key);
	}
	IntensityFunc->updateTexture();
	return IntensityFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GetnerateSkinTransferFunction( double* TableRange )
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();


	// threshold = -450 for vtkImageData
	// threshold = 2000 for dcmtkImage
	float normthreshold=ConvertIntensityToKeyValue(TableRange,-450.0f);

	TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::vec4(0,0,0,0));
	IntensityFunc->addKey(key0);
	TransFuncMappingKey *skin0 = new TransFuncMappingKey( normthreshold , tgt::col4(247,222,166,0));
	IntensityFunc->addKey(skin0);
	TransFuncMappingKey *skin1 = new TransFuncMappingKey( normthreshold + 0.03f , tgt::col4(247,222,166,50));
	IntensityFunc->addKey(skin1);	
	TransFuncMappingKey *skin2 = new TransFuncMappingKey( normthreshold + 0.06f , tgt::col4(247,222,166,0));
	IntensityFunc->addKey(skin2);	
	TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(0,0,0,0));
	IntensityFunc->addKey(key1);



	return IntensityFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateDentalTransferFunction()
{
	return std::make_shared<TransFuncIntensity>();
}


std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateImageFMRITransferFunction( double* TableRange )
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();
	tgt::col4 blackColor(0, 0, 0, 0);
	TransFuncMappingKey *key1 = new TransFuncMappingKey( 0 , blackColor );
	IntensityFunc->addKey(key1);

	tgt::col4  Red1(255, 0, 0, 125);
	TransFuncMappingKey *key2 = new TransFuncMappingKey( 0.1f , Red1 );
	IntensityFunc->addKey(key2);

	tgt::col4 redColor(255, 125, 0, 125);
	TransFuncMappingKey *key9 = new TransFuncMappingKey( 0.15f , redColor );
	IntensityFunc->addKey(key9);

	tgt::col4 redColor3(255, 125, 0, 255);
	TransFuncMappingKey *key5 = new TransFuncMappingKey( 0.2f , redColor3 );
	IntensityFunc->addKey(key5);

	tgt::col4 orrange1(255, 200, 0, 255);
	TransFuncMappingKey *key10 = new TransFuncMappingKey( 0.37f , orrange1 );
	IntensityFunc->addKey(key10);

	tgt::col4 yellow(255, 255, 0, 255);
	TransFuncMappingKey *key4 = new TransFuncMappingKey( 0.45f , yellow );
	IntensityFunc->addKey(key4);

	tgt::col4 midYellow(255, 255, 125, 255);
	TransFuncMappingKey *key8 = new TransFuncMappingKey( 0.60f , midYellow );
	IntensityFunc->addKey(key8);

	tgt::col4 white2(255, 255, 255, 255);
	TransFuncMappingKey *key6 = new TransFuncMappingKey( 0.69f , white2 );
	IntensityFunc->addKey(key6);

	tgt::col4 white(255, 255, 255, 255);
	TransFuncMappingKey *key7 = new TransFuncMappingKey( 1.0f , white );
	IntensityFunc->addKey(key7);

	return IntensityFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GetnerateVolumeFMRITransferFunction( double* TableRange )
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();

	std::ifstream f;
	f.exceptions ( ifstream::failbit | ifstream::badbit );
	try
	{
		f.open("fMRIColorTable.xml", std::ios::in);
	}
	catch(fstream::failure   E)
	{
		cout<<" error  in opening file :ApplicationSetting.xml"<<std::endl;
	}	
	XmlDeserializer s;
	s.read(f);
	misfMRIColorTable fMRIColorTable;
	s.deserialize("misfMRIColorTable", fMRIColorTable);
	f.close();
	//
	double range = TableRange[1] / 1000;
	size_t  numofKeys = static_cast<size_t> (256 / range);
	for (size_t i = 0; i < numofKeys; i++)
	{
		float greyLevel = static_cast<float> ((double)i / 255);
		tgt::col4 rgb = fMRIColorTable.ImageIndexToRGB(static_cast<int> (i));
		rgb[0] *= 255;
		rgb[1] *= 255;
		rgb[2] *= 255;
		rgb[3] *= 0;
		TransFuncMappingKey *key = new TransFuncMappingKey( greyLevel , rgb );
		IntensityFunc->addKey(key);
	}
	TransFuncMappingKey *key = new TransFuncMappingKey( 0.000196f , tgt::vec4(0.0, 0.0, 0.0, 0.0) );
	IntensityFunc->addKey(key);

	return IntensityFunc;
}

std::shared_ptr<TransFuncIntensity> misTransFunctionBuilder::GenerateOpaceBone( double* TableRange  ,double normalizedOpacity)
{
	auto IntensityFunc = std::make_shared<TransFuncIntensity>();
	float normthreshold = ConvertIntensityToKeyValue(TableRange,100);
	TransFuncMappingKey *key0 = new TransFuncMappingKey( 0.0f , tgt::col4(0,0,0,0));
	IntensityFunc->addKey(key0);
	TransFuncMappingKey *skin0 = new TransFuncMappingKey( normthreshold , tgt::col4(247,222,166,0));
	IntensityFunc->addKey(skin0);
	TransFuncMappingKey *skin1 = new TransFuncMappingKey( normthreshold + 0.03f , 	tgt::col4(247, 222, 166, 
		static_cast<uint8_t>  (normalizedOpacity*255)));
	IntensityFunc->addKey(skin1);	
	TransFuncMappingKey *skin2 = new TransFuncMappingKey( normthreshold + 0.06f , tgt::col4(247,222,166,0));
	IntensityFunc->addKey(skin2);	
	TransFuncMappingKey *key1 = new TransFuncMappingKey( 1.0f , tgt::col4(0,0,0,0));
	IntensityFunc->addKey(key1);

	return IntensityFunc;
}

unsigned char* misTransFunctionBuilder::vec_init(unsigned char p, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char* v = new unsigned char[4];
	v[0] = r;
	v[1] = g;
	v[2] = b;
	return v;
}

void misTransFunctionBuilder::ColormapInit()
{
	if(colormapInitialized)
	{
		colormapInitialized = true;

		//ATTENTION it is not RGBA! see below
		//vec codes : (position,red,green,blue)
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AUTUMN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[AUTUMN].push_back(vec_init(0  ,255,0,0));
		colormap[AUTUMN].push_back(vec_init(255,255,255,0));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BONE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[BONE].push_back(vec_init(0  ,0  ,0  ,1  ));
		colormap[BONE].push_back(vec_init(85 ,81 ,81 ,113));
		colormap[BONE].push_back(vec_init(170,166,198,198));
		colormap[BONE].push_back(vec_init(255,255,255,255));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COLORCUBE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//colormap[COLORCUBE].push_back(vec_init(1,2,3));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COOL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[COOL].push_back(vec_init(0  ,0  ,255,255));
		colormap[COOL].push_back(vec_init(255,255,0  ,255));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COPPER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[COPPER].push_back(vec_init(0  ,0  ,0  ,0  ));
		colormap[COPPER].push_back(vec_init(204,255,161,103));
		colormap[COPPER].push_back(vec_init(255,255,192,127));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FLAG ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//	colormap[FLAG].push_back(vec_init(1,2,3));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GRAY ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[GRAY].push_back(vec_init(0  ,0  ,0  ,0  ));
		colormap[GRAY].push_back(vec_init(255,255,255,255));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HOT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[HOT].push_back(vec_init(0  ,11 ,0  ,0  ));
		colormap[HOT].push_back(vec_init(96 ,255,0  ,0  ));
		colormap[HOT].push_back(vec_init(192,255,255,0  ));
		colormap[HOT].push_back(vec_init(192,255,255,255));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HSV ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[HSV].push_back(vec_init(0  ,255,0  ,0  ));
		colormap[HSV].push_back(vec_init(42 ,255,255,0  ));
		colormap[HSV].push_back(vec_init(85 ,0  ,255,0  ));
		colormap[HSV].push_back(vec_init(127,0  ,255,255));
		colormap[HSV].push_back(vec_init(170,0  ,0  ,255));
		colormap[HSV].push_back(vec_init(212,255,0  ,255));
		colormap[HSV].push_back(vec_init(255,255,0  ,0  ));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[JET].push_back(vec_init(0  ,0  ,0  ,127));
		colormap[JET].push_back(vec_init(32 ,0  ,0  ,255));
		colormap[JET].push_back(vec_init(96 ,0  ,255,255));
		colormap[JET].push_back(vec_init(159,255,255,0  ));
		colormap[JET].push_back(vec_init(223,255,0  ,0  ));
		colormap[JET].push_back(vec_init(255,127,0  ,0  ));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//colormap[LINES].push_back(vec_init(1,2,3));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PINK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//colormap[PINK].push_back(vec_init(1,2,3));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PRISM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//colormap[PRISM].push_back(vec_init(1,2,3));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SPRING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[SPRING].push_back(vec_init(255,255,0  ,255));
		colormap[SPRING].push_back(vec_init(255,255,255,0  ));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SUMMER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[SUMMER].push_back(vec_init(0  ,0  ,127,102));
		colormap[SUMMER].push_back(vec_init(255,255,255,102));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ WHITE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[WHITE].push_back(vec_init(0  ,255,255,255));
		colormap[WHITE].push_back(vec_init(255,255,255,255));
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ WINTER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		colormap[WINTER].push_back(vec_init(0  ,0,0  ,255));
		colormap[WINTER].push_back(vec_init(255,0,255,127));
	}
}
