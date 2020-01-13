varying vec4 vTexCoord0;
varying vec4 vTexCoord1;


struct GroupProperties
{

	uniform sampler3D TEX0; 
	uniform sampler3D TEX1; 
	uniform sampler1D TransferFuncofSegmentedImage;
	uniform sampler1D TransferFuncofColorMap;
	uniform sampler1D TransferFuncofWindowLevel;

	uniform	float CurrentWindowCenterOfMT;
	uniform	float CurrentWindowWidthOfMT;
	uniform	float TexColorRedPart;
	uniform	float TexColorGreenPart;
	uniform	float TexColorBluePart;
	uniform	float OpacityOfMT;

	uniform bool  UseAlphaForMainBlending;
	uniform bool  UseColorForMT;
	uniform	bool  VisiblityofSegmentedImage;
	uniform	bool  VisiblityOfMT;
	uniform	bool  VisiblityOfColorMap;
};
	
uniform GroupProperties  grProp[4];

vec4	CalculateSegmentedImageColor(int index);
vec4	CalculateMainImageColor(int index);
vec4	CalculateColorMapResult(int index);

vec4	MixImageAndColor(vec4 IMAGE, vec4 SEGMENTEDCOLOR);
vec4	BlendSegmentedTextures(vec4 xx , vec4 yy);
vec4	BlendMainTextures(vec4 xx , vec4 yy);
float	Max(float x, float y);

vec4 CalculateSegmentedImageColor(int index)
{
	vec4 newCoord;
 	if(index== 0)
	{
		newCoord = vTexCoord0;
	}
 	else if( index == 1)
	{
		newCoord = vTexCoord1;
	}
	else
			return vec4(1.0,1.0,0.0,1.0);
	
	vec3 texc3 = vec3(newCoord.x, newCoord.y,newCoord.z);
	vec4 color1 =vec4(0.0);
	color1 = texture3D(grProp[index].TEX1,texc3);
	vec4 color = texture1D(grProp[index].TransferFuncofSegmentedImage, color1.x);

	return color;
}
   
vec4	CalculateMainImageColor(int index)
{
 /*		vec4 newCoord;
 		float widthHalf = grProp[index].CurrentWindowWidthOfMT / 2.0;
 		float start     = grProp[index].CurrentWindowCenterOfMT-widthHalf;
 		float end       = grProp[index].CurrentWindowCenterOfMT+widthHalf;
 	
 		if(index== 0)
 		{
 			newCoord = vTexCoord0;
 		}
 		else if( index == 1)
 		{
 			newCoord = vTexCoord1;
 		}
 		else
 			return vec4(0.0,1.0,1.0,1.0);
 
 		vec3 texc3 = vec3(newCoord.x, newCoord.y,newCoord.z);
 		vec4 initialcolor = texture3D(grProp[index].TEX0,texc3);
 
 		
 		vec4 RayCastingColor = vec4(0.0,0.0,0.0,1.0);
 
 		if (initialcolor.x > end) 
 		{
 			RayCastingColor = vec4(1.0,1.0,1.0,1.0);
 		}
 		else if (initialcolor.x > start)
 		{
 			float stip = 1/(end - start);    
 			float value = (initialcolor.x - start) * stip;
 			RayCastingColor = vec4(value,value,value,1.0);
 		}*/
	    vec4 FinalColor = vec4(0.0,0.0,0.0,0.0);
		vec4 newCoord;
		if(index== 0)
 		{
 			newCoord = vTexCoord0;
 		}
 		else if( index == 1)
 		{
 			newCoord = vTexCoord1;
 		}
 		else
 			return vec4(0.0,1.0,1.0,1.0);

		vec3 texc3 = vec3(newCoord.x, newCoord.y,newCoord.z);
		vec4 initialcolor = texture3D(grProp[index].TEX0,texc3);
		vec4 RayCastingColor = texture1D(grProp[index].TransferFuncofWindowLevel, initialcolor.x);


		if ((!grProp[index].UseAlphaForMainBlending) && (!grProp[index].UseColorForMT))
		{
			FinalColor = RayCastingColor;
		}
		else if ((!grProp[index].UseAlphaForMainBlending) && (grProp[index].UseColorForMT))
		{
			float redPart   =  RayCastingColor.x * grProp[index].TexColorRedPart;
			float greenPart =  RayCastingColor.y * grProp[index].TexColorGreenPart;
			float bluePart  =  RayCastingColor.z * grProp[index].TexColorBluePart;

			FinalColor = vec4(redPart,greenPart,bluePart,1.0); 
		}
		else if ((grProp[index].UseAlphaForMainBlending) && (!grProp[index].UseColorForMT))
		{
			FinalColor = vec4(RayCastingColor.x, RayCastingColor.y, RayCastingColor.z, grProp[index].OpacityOfMT); 		
		}
		else 
		{
			float redPart   = RayCastingColor.x * grProp[index].TexColorRedPart;
			float greenPart = RayCastingColor.y * grProp[index].TexColorGreenPart;
			float bluePart  = RayCastingColor.z * grProp[index].TexColorBluePart;
			FinalColor = vec4(redPart,greenPart,bluePart,grProp[index].OpacityOfMT); 
		}
		return FinalColor;
}

float	Max(float x, float y)
{
	if( x <= y )
		return y;
	else
		return x;
}

vec4	BlendSegmentedTextures(vec4 xx , vec4 yy)
{
	if(xx == vec4(0.0) && yy == vec4(0.0))
		return xx;
	else
	{
		vec4 output = vec4(0.0);
		float redPart	= xx.x + yy.x;
		float greenPart	= xx.y + yy.y;
		float bluePart	= xx.z + yy.z;
		float opacity	= Max(xx.w , yy.w);
		output = vec4(redPart,greenPart,bluePart,opacity); 
		return output;
	}
}

vec4	BlendMainTextures(vec4 xx , vec4 yy)
{	
	float Y_NEW_INTENSITY_R  = yy.w * yy.x;
	float X_NEW_INTENSITY_R  = xx.w * xx.x;

	float Total_INTENSITY_R = Max (X_NEW_INTENSITY_R,Y_NEW_INTENSITY_R);

	float Y_NEW_INTENSITY_G  = yy.w * yy.y;
	float X_NEW_INTENSITY_G  = xx.w * xx.y;

	float Total_INTENSITY_G = Max (X_NEW_INTENSITY_G,Y_NEW_INTENSITY_G);
	
	float Y_NEW_INTENSITY_B  = yy.w * yy.z;
	float X_NEW_INTENSITY_B  = xx.w * xx.z;

	float Total_INTENSITY_B = Max (X_NEW_INTENSITY_B,Y_NEW_INTENSITY_B);

	vec4 result = vec4(Total_INTENSITY_R,Total_INTENSITY_G,Total_INTENSITY_B,1.0);
	return result;
}

 vec4	CalculateColorMapResult(int index)
 {
 	vec4 Coord;
 	
 		if(index== 0)
 		{
 			Coord = vTexCoord0;
 		}
 		else if( index == 1)
 		{
 			Coord = vTexCoord1;
 		}
 	
 
  	vec3	texc3 = vec3(Coord.x, Coord.y,Coord.z);
  	vec4	initialcolor  =	texture3D(grProp[index].TEX0,texc3);
     vec4	ColorMapOutput   =	texture1D(grProp[index].TransferFuncofColorMap, initialcolor.x);		
 
 	return ColorMapOutput;
 }

vec4	MixImageAndColor(vec4 IMAGE, vec4 SEGMENTEDCOLOR)
{
		float SegmentedOpacity = SEGMENTEDCOLOR.w;
		float MainImageOpacity = 1 - SegmentedOpacity; 
		vec4 out1,out2,result;
	
		out1   = SegmentedOpacity*SEGMENTEDCOLOR;
		out1.w = SegmentedOpacity;

		out2   = MainImageOpacity * IMAGE;
		out2.w = MainImageOpacity;

		result = out1 + out2;

		return result;
}
void main(void)
{
		vec4	MainColor0		= vec4(0.0);
		vec4	PolyColor0		= vec4(0.0);
 		vec4	MainColor1		= vec4(0.0);
 		vec4	PolyColor1		= vec4(0.0);
		vec4	ColorMapOutput0 = vec4(0.0);
		vec4	ColorMapOutput1 = vec4(0.0);

			//	~~~~~~~~~~~~~~~~~~~      Main Textures     ~~~~~~~~~~~~~~~~~~~  //			
    
					if (grProp[0].VisiblityOfMT )
    				{
						MainColor0 = CalculateMainImageColor(0);
    				}
   					if (grProp[1].VisiblityOfMT)
   					{
  						//MainColor1 = vec4(1,0,0,1);
						MainColor1 = CalculateMainImageColor(1);
   					}

			//  ~~~~~~~~~~~~~~~~~~~        ColorMap        ~~~~~~~~~~~~~~~~~~~  //
 	
  					if (grProp[0].VisiblityOfColorMap)
   					{
						ColorMapOutput0 = CalculateColorMapResult(0);	
   					}
  					if (grProp[1].VisiblityOfColorMap)
   					{
   						ColorMapOutput1 = CalculateColorMapResult(1);	
   					}

			//	~~~~~~~~~~~~~~~~~~~   Segmented Textures   ~~~~~~~~~~~~~~~~~~~  //	

  					if (grProp[0].VisiblityofSegmentedImage)
 					{
   						PolyColor0 = CalculateSegmentedImageColor(0);			
					}	
 					if (grProp[1].VisiblityofSegmentedImage)
 					{
   						PolyColor1 = CalculateSegmentedImageColor(1);
 					}


			//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  //	

	 
 				vec4	Mains		=	BlendMainTextures(MainColor0,MainColor1);
				vec4	Segments	=	BlendSegmentedTextures(PolyColor0,PolyColor1);
 	
  					vec4  res0	=	MixImageAndColor(Mains ,ColorMapOutput0);
  					vec4  res1	=	MixImageAndColor(res0  ,ColorMapOutput1);
 					vec4  res2	=	MixImageAndColor(res1  ,Segments);
				//	vec4  Mains =	BlendMainTextures(MainColor0,MainColor1);
				//	vec4  res2	=	MixImageAndColor(MainColor0,PolyColor0);
// 		
		gl_FragColor = Vec4(1, 0, 0, 1);
 		
}
