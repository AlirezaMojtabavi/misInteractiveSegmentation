#pragma once

struct misColorStruct :public Serializable
{
	// range between 0:255
	//jalal:keep them integer due to serialization problem
	int red;
	int green;
	int blue;

	//  0: means completely clear( invisible), 1 completely Visible
	double alpha;

	void  ChangeColor(int addRed, int addGreen, int addBlue) 
	{
		red = red + addRed;
		green = green + addGreen;
		blue = blue + addBlue;

		if (red + addRed > 255)
			red = 255;
		else if (red + addRed < 0)
			red = 0;

		if (green + addGreen > 255)
			green = 255;
		else if (green + addGreen < 0)
			green = 0;

		if (blue + addBlue > 255)
			blue = 255;
		else if (blue + addBlue < 0)
			blue = 0;
		
	}
	misColorStruct(void)
	{
		this->Reset();
	};
	misColorStruct(unsigned char r, unsigned char g, unsigned char b, double  a)
	{
		red = r;
		green = g;
		blue = b;
		alpha = a;

	}

	void InVisible(void)
	{
		red = 0;
		green = 0;
		blue = 0;

		alpha = 0;
	};

	bool IsVisible(void) const
	{
		bool res = false;

		if (this->alpha != 0)
		{
			res = true;
		}

		return res;
	}
	bool operator ==(const misColorStruct right) const
	{
		if ((this->red == right.red) && (this->green == right.green) && (this->blue == right.blue) && (this->alpha == right.alpha))
			return true;
		else
			return false;
	};

	void ComplementColor(void)
	{

		this->red = 255 - this->red;
		this->green = 255 - this->green;
		this->blue = 255 - this->blue;
	};

	void SetBlackColor(void)
	{
		red = 0;
		green = 0;
		blue = 0;

		alpha = 1.0;
	};
	void SetRedColor(void)
	{
		red = 255;
		green = 0;
		blue = 0;

		alpha = 1.0;
	};
	void SetGreenColor(void)
	{
		red = 0;
		green = 255;
		blue = 0;

		alpha = 1.0;
	};
	void SetBlueColor(void)
	{
		red = 0;
		green = 0;
		blue = 255;

		alpha = 1.0;
	};
	void SetGrayColor(void)
	{
		red = 125;
		green = 125;
		blue = 125;

		alpha = 1.0;
	};
	void Reset()
	{
		this->SetGrayColor();
	};

	void SetWhiteColor(void)
	{
		red = 255;
		green = 255;
		blue = 255;

		alpha = 1.0;
	};

	bool operator !=(misColorStruct right) const
	{
		if ((this->red == right.red) && (this->green == right.green) && (this->blue == right.blue) && (this->alpha == right.alpha))
			return false;
		else
			return true;
	};


	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("Red", (unsigned int)red);
		s.serialize("Green", green);
		s.serialize("Blue", blue);
		s.serialize("Alpha", alpha);
	}
	virtual void deserialize(XmlDeserializer& s)
	{
		try
		{
			s.deserialize("Red", (unsigned int&)red);
			s.deserialize("Green", (unsigned int&)green);
			s.deserialize("Blue", (unsigned int&)blue);
			s.deserialize("Alpha", alpha);
		}
		catch (...)
		{
			std::cout << "failed in deserialize of ColorStruct" << std::endl;
		}
	}


};

typedef  std::vector<misColorStruct>      misColorVector;
typedef  std::map<float, misColorStruct> misColorListTypedef;
