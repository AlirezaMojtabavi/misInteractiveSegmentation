#include "StdAfx.h"
#include "misCompeleteImageDependensies.h"

#include "misStringTools.h"

misCompeleteImageDependencies ::misCompeleteImageDependencies ( void )
{
	m_Image =0;
	this->opacity = 255;
	this->Visibility =1;
	this->objectUID = misStringTools::GenerateNewUID();
}


const misCompeleteImageDependencies& misCompeleteImageDependencies ::operator=( misCompeleteImageDependencies  right )
{
	//	this->name         = right.name;

	this->m_Image = right.m_Image;
	this->opacity       = right.opacity;;
	this->objectUID     = right.objectUID;;
	this->Visibility    = right.Visibility;;
	return *this;
}

std::shared_ptr<IImage> misCompeleteImageDependencies::GetImage() const
{
	return m_Image;
}

void misCompeleteImageDependencies::SetImage( std::shared_ptr<IImage> val )
{
	m_Image = val;
}

std::string misCompeleteImageDependencies::GetName() const
{
	return name;
}

void misCompeleteImageDependencies::SetName(std::string val)
{
	name = val;
}

double misCompeleteImageDependencies::GetOpacity() const
{
	return opacity;
}

void misCompeleteImageDependencies::SetOpacity(double val)
{
	opacity = val;
}

misUID misCompeleteImageDependencies::GetObjectUID() const
{
	return objectUID;
}

void misCompeleteImageDependencies::SetObjectUID(misUID val)
{
	objectUID = val;
}

bool misCompeleteImageDependencies::GetVisibility() const
{
	return Visibility;
}

void misCompeleteImageDependencies::SetVisibility(bool val)
{
	Visibility = val;
}
