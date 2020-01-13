#include "stdafx.h"
#include "misImageContainedPolyDataStructs.h"

using std::cout;
using std::fstream;

void ImagePolyDataContenStrct::WriteToFile( fstream& file )
{
	file<<"<ImagePolyDataContenStrct>"<<std::endl;

	file<<"<ParrentImageUID>"<<std::endl;
	file<< this->ParrentImageUID <<std::endl;
	file<<"</ParrentImageUID>"<<std::endl;

	file<<"<ParrentImageUID>"<<std::endl;
	file<< this->ParrentImageUID <<std::endl;
	file<<"</ParrentImageUID>"<<std::endl;

	file<<"<PolyDataUID>"<<std::endl;
	file<< this->PolyDataUID <<std::endl;
	file<<"</PolyDataUID>"<<std::endl;

	file<<"<IndexRepresentObject>"<<std::endl;
	file<< this->IndexRepresentObject <<std::endl;
	file<<"</IndexRepresentObject>"<<std::endl;

	file<<"<PolyDataColor>"<<std::endl;
	//			this->PolyDataColor.WriteToFile(file);
	file<<"</PolyDataColor>"<<std::endl;

	file<<"</ImagePolyDataContenStrct>"<<std::endl;
}

bool ImagePolyDataContenStrct::GetShowMargin() const
{
	return m_ShowMargin;
}

void ImagePolyDataContenStrct::SetShowMargin(const bool Showmargin)
{
	m_ShowMargin = Showmargin;
}

ImagePolyDataContenStrct::ImagePolyDataContenStrct( void )
{
	IndexRepresentObject				= -1;
	OpacityProp.visibilityIn2DScene     = true;
	OpacityProp.SetVisibilityIn3DScene(true);
	OpacityProp.SetOpacityIn2DScene(1);
	OpacityProp.OpacityIn3DScene		= 1;
	ObjectVolume						= -1;
}
