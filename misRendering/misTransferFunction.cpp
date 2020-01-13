#include "StdAfx.h"
#include "misTransferFunction.h"

#include "misColorStruct.h"

misTransferFunction::misTransferFunction(double *TableRange)
{
	InitializeGL();
	m_Threshold = 0.0;
	m_TableRange = NULL;
	this->setTableRange(TableRange);
	this->m_WidthExpansionScale =3;
//	TODO : why width = TR[1]*3 : BECAUSE THE TRANSFER FUNCTION STRUCTURE IS   
// WRITTEN IN A WAY THAT IT CAN"T SHOW RODS<SINGLE RODS< SO WE HAVE TO CHANGE
//  THE ROD (1-pixel width section of tf) TO SOME SORT OF RECTANGLE TO MAKE 
//	THE TF HAPPEN. 3 WAS THE MAGNIFICATION SCALE THAT WE CAME UPON. IT'S NOT
//  EXACT.COULD BE ANY OTHER VALUE
	m_TransferFunc = new TransFuncIntensity(static_cast<int> (m_WidthExpansionScale * TableRange[1]));
	this->Reset();
}

misTransferFunction::Pointer misTransferFunction::New( double* TableRange )
{
	Pointer smartPtr; 
	Self *rawPtr = new Self(TableRange);
	smartPtr = rawPtr;
	rawPtr->UnRegister(); 
	return smartPtr;
}

misTransferFunction::~misTransferFunction(void)
{
}

float misTransferFunction::CalculateFloatValue( double intensity )
{
	float val = -1;
	if (m_TableRange)
	{
		val = static_cast<float>(double(intensity) / ( m_TableRange[1] -  m_TableRange[0]));
	}
	
	return val;
}

void misTransferFunction::setTableRange( double* tableRange )
{
	if (tableRange[1] > tableRange[0])
	{
		if (0 == m_TableRange)
		{
			m_TableRange = new double[2];
		}
		
		m_TableRange[0] =tableRange[0];
		m_TableRange[1] =tableRange[1];
	}
	else
	{
		if (m_TableRange)
		{
			delete m_TableRange;
			m_TableRange = NULL;
		}
	}
	
	this->UpdateKeyDist();
}

void misTransferFunction::GenerateKey( double i , misColorStruct colorstruct)
{
	if (0 ==  m_TableRange)
	{
		return;
	}

	TransFuncMappingKey *key = NULL;
//	THE TABLE RANGE DOESNOT REALLY NEED TO BE MAGNIFIED. SINCE WE DON'T WANT A
//	DIFFERENT TRANSFER FUNCTION. ALL WE WANT TO DO IS TO SCALE IT IN A WAY THAT
//	NOTHING CHANGES OTHER THAN A SINGLE ROD TURNNING INTO A BAR. SO TABLE RANGE 
//	STAYES UNCHANGED.

	float val = CalculateFloatValue(i);
	
	key = new TransFuncMappingKey( val , tgt::col4(static_cast<uint8_t> (colorstruct.red), static_cast<uint8_t> (colorstruct.green)
		,static_cast<uint8_t> (colorstruct.blue), static_cast<uint8_t> (colorstruct.alpha*255)));
	m_TransferFunc->addKey(key);
}

void misTransferFunction::GenerateKey(float intensity, misColorStruct colorstruct ,float alpha )
{
	TransFuncMappingKey *key = NULL;
	tgt::col4 color(static_cast<uint8_t> (colorstruct.red),  static_cast<uint8_t> (colorstruct.green), 
		static_cast<uint8_t> (colorstruct.blue),static_cast<uint8_t> (alpha*255));
	key = new TransFuncMappingKey(intensity ,color);
	m_TransferFunc->addKey(key);
}

void misTransferFunction::CreateTexture()
{
	m_TransferFunc->updateTexture();
	m_TransferFunc->bind();
	tgt::Texture * tf_tex = m_TransferFunc->getTexture();
	m_TfIndex = tf_tex->getId();
}

void misTransferFunction::Reset()
{
	m_TransferFunc->clearKeys();
}

void misTransferFunction::InitializeGL()
{
	int argc = 1;
	char* argv[1];
	argv[0] = "rama";
 tgt::init();
 tgt::initGL();
}

void misTransferFunction::AddZeroIntensityKey()
{
	misColorStruct zeroIntensity ;
    zeroIntensity.InVisible();
	if (m_TransferFunc )
	{
		this->GenerateKey(0.0,zeroIntensity,0.0);
	}
	else
	{
		_ASSERT( true == false);
	}
}
void misTransferFunction::UpdateKeyDist()
{
	if (m_TableRange)
	{
		m_Threshold = static_cast<float> (1.0 / ( m_TableRange[1] - m_TableRange[0])) ;
	}
	else
	{
		m_Threshold = 0.0;
		_ASSERT( true == false);
	}
}

TransFuncIntensity * misTransferFunction::getTransferFunction()
{
	return m_TransferFunc;
}

void misTransferFunction::setThresholds( float lower, float upper )
{
	this->m_TransferFunc->setThresholds(lower,upper);
}

void misTransferFunction::GenerateKey( double i , float red , float green , float blue , float alpha )
{
	if (0 ==  m_TableRange)
	{
		_ASSERT(true == false);
	}

	float val = CalculateFloatValue(i);
	TransFuncMappingKey *key = NULL;
	key = new TransFuncMappingKey( val , tgt::vec4(red,green,blue,alpha));
	m_TransferFunc->addKey(key);
}



