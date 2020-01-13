#pragma once

#include "misCompeleteImageDependensies.h"
#include "IImage.h"

class misVolumeData;
class misPlanData;

struct ManModelStr
{
	vtkActorCollection* pActors;
	vtkSmartPointer<vtkTransform> transform;
	double opacity;
	bool useable;
	bool Visibility;

	ManModelStr()
	{
		pActors = 0;
		this->transform = vtkSmartPointer<vtkTransform>::New();
		this->transform->Identity();
		this->opacity = 1;
		this->useable = 0;
		this->Visibility = 1;
	};
};

typedef std::vector< std::shared_ptr<IImage>> ImageListTypedef;
typedef std::vector<std::shared_ptr<ICompeleteImageDependencies>> ImageDependencyListTypes;