#pragma once

typedef std::string misUID;

struct misImageViewingItemsStruct :public Serializable
{
	std::string viewingName;
	std::string name;
	std::string description;
	std::string numberofImages;
	std::string modality;
	tgt::ivec3 Dimention;
	tgt::vec3 Spacing;

	misUID objectUID;
	misUID packageUID;
	misUID parentImageUID;

	bool directionSataus;
	int correlationSatus;
	bool visibilitySatus;
	bool makeCompleteName;

	misImageViewingItemsStruct()
	{
		makeCompleteName = true;
		directionSataus  =  false;
		correlationSatus =  -1;
		visibilitySatus  =  false;
	};

	void Update()
	{
		if ( true == makeCompleteName)
		{
			viewingName.clear();
			viewingName.append(name);
			viewingName.append(" ");
			viewingName.append("<");
			viewingName.append(modality);
			viewingName.append("::");
			viewingName.append(numberofImages);
			viewingName.append(">");
		}
		else
		{
			viewingName = name;
		}
	}

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("viewingName",this->viewingName);
		s.serialize("name",this->name);
		s.serialize("description",this->description);
		s.serialize("numberofImages",this->numberofImages);
		s.serialize("modality",this->modality);
		s.serialize("objectUID",this->objectUID);
		s.serialize("packageUID",this->packageUID);
		s.serialize("directionSataus",this->directionSataus);
		s.serialize("correlationSatus",this->correlationSatus);
		s.serialize("visibilitySatus",this->visibilitySatus);
		s.serialize("makeCompleteName",this->makeCompleteName);
		s.serialize("imageSpacing",this->Spacing);
		s.serialize("imageDimentions",this->Dimention);
	};

	virtual void deserialize(XmlDeserializer& s)
	{
		s.deserialize("viewingName",this->viewingName);
		s.deserialize("name",this->name);
		s.deserialize("description",this->description);
		s.deserialize("numberofImages",this->numberofImages);
		s.deserialize("modality",this->modality);
		s.deserialize("objectUID",this->objectUID);
		s.deserialize("packageUID",this->packageUID);
		s.deserialize("directionSataus",this->directionSataus);
		s.deserialize("correlationSatus",this->correlationSatus);
		s.deserialize("visibilitySatus",this->visibilitySatus);
		s.deserialize("makeCompleteName",this->makeCompleteName);
		s.deserialize("imageSpacing",this->Spacing);
		s.deserialize("imageDimentions",this->Dimention);
	};
};
