#pragma once

// The ITextureGenerator provides an abstract interface for creating raw data for a texture. The created texture will be
// used for creating an OpenGL texture. 
// Author: Mohsen Rahimimoghaddam
// Date: Aug 2016
class ITextureGenerator
{
public:
	typedef itk::Point<double, 3> PointType;	// Type used for representing spatial points

	typedef float TextureDataType;

	struct TextureData
	{
		TextureData(int width, int height, int depth, int channelSize)
			: Width(width), Height(height), Depth(depth), ChannelSize(channelSize),
			Data(width * height * depth * channelSize, 0.0)
		{
		}

		int Width, Height, Depth;
		int ChannelSize;
		std::vector<TextureDataType> Data;
	};

	// Returns Texture data structure which contains all pixel data values flatten in a 1D vector. For more details see TextureData
	virtual std::shared_ptr<TextureData> GetPanoramicTexture() const = 0;

	virtual ~ITextureGenerator(void) { }
};