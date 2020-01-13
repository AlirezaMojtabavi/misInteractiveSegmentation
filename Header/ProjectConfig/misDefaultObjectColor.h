#pragma once

#include "misobjectProperitiesEnums.h"
#include "misColorStruct.h"


typedef std::map<mis3DModelTypes,misColorStruct>    mis3DModelColorTypdef;

class misDefaultObjectColor
{
public:

	static mis3DModelColorTypdef GetDefaultObjectColor()
	{
		mis3DModelColorTypdef default3DModelColor ;
		// TODO: important uncompleted Color
		misColorStruct  misSkinColor;
		misSkinColor.red   = 247;
		misSkinColor.green = 222;
		misSkinColor.blue  = 166;


		misColorStruct  misBoneColor;
		misBoneColor.red   = 226;
		misBoneColor.green = 198;
		misBoneColor.blue  = 137;

		misColorStruct  misTumorColor;
		misTumorColor.red   = 237;
		misTumorColor.green = 220;
		misTumorColor.blue  = 10;

		misColorStruct  misVeinColor;
		misVeinColor.red   = 250;
		misVeinColor.green = 100;
		misVeinColor.blue = 125;

		misColorStruct  misOtherColor;
		misOtherColor.red   = 250;
		misOtherColor.green = 250;
		misOtherColor.blue  = 250;

		misColorStruct  misSteelColor;
		misOtherColor.red   = 125;
		misOtherColor.green = 125;
		misOtherColor.blue  = 125;

		misColorStruct  misAllColor;
        misAllColor = misSkinColor;


		default3DModelColor[misSkin]  = misSkinColor;
		default3DModelColor[misBone]  = misBoneColor;
		default3DModelColor[misTumor] = misTumorColor;
		default3DModelColor[misVein]  = misVeinColor;
		default3DModelColor[misMetal] = misSteelColor;

		default3DModelColor[misAll]   = misAllColor;
		default3DModelColor[misOther] = misOtherColor;


		return default3DModelColor;
	};
};