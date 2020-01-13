/*

The Frgament shader of 2D image viewer are rewrited for supporting either of ATI and Nvidia graphic cards.

The below modifications are applyed to the previous code:

** In ATI card Mode, struct or arrays with SAMPLER type members result in runtime errors,So All of the structured type
variables are reformed to the simple type variables.

** Instead of using the structure type definition, some macros are defined for declaring the uniform variables similar to
the previous shader program.

** In ATI cards unused uniform SAMPLERs resulted in some runtime problems, so if any SAMPLER is not used in the shader,
in the current verison, it will not be declared. This is performed by defining of GROUPS_NUM_(index) for main image groups
and GroupContainedColorMap_(index1)_(index2)_isActive for active colormaps.

** The previous version has a function named TFselection was defined in <mod_transferFunctionSelecting.frag> which is
writed based on the structure data type. Now it is converted to ColorDecoderForSegmentedAreas macro and all
structured data types are converted to simple type variables.

** Some of the color mixing functions are simipified.

** The video texture is not tested for this version of shader.

*/


varying vec4 vTexCoord1;
varying vec4 vTexCoord2;


#include "glsl\\modules\\mod_transferFunctionSelecting.frag"


//========================================================================
#define GroupProperties(index) \
uniform	sampler3D grProp_##index##_baseTexture; \
uniform	sampler3D grProp_##index##_segmentedTexture; \
uniform	sampler3D grProp_##index##_fmriTexture; \
uniform	sampler1D grProp_##index##_TransferFuncofColorMap;\
uniform	sampler1D grProp_##index##_TransferFuncofWindowLevel;\
uniform	sampler1D grProp_##index##_TransferFuncofFmri;\
uniform	float grProp_##index##_CurrentWindowCenterOfMT;\
uniform	float grProp_##index##_CurrentWindowWidthOfMT;\
uniform	float grProp_##index##_TexColorRedPart;\
uniform	float grProp_##index##_TexColorGreenPart;\
uniform	float grProp_##index##_TexColorBluePart;\
uniform	float grProp_##index##_OpacityOfMT;\
uniform	bool  grProp_##index##_mainImageIsColored;\
uniform	bool  grProp_##index##_UseAlphaForMainBlending;\
uniform	bool  grProp_##index##_UseColorForMT;\

//========================================================================
#define StrObjectColorMap(index,objIndex) \
uniform int GroupContainedColorMap_##index##_##objIndex##_startBit;\
uniform int GroupContainedColorMap_##index##_##objIndex##_numberOfBits;\
uniform sampler1D GroupContainedColorMap_##index##_##objIndex##_TransferFunction;
//========================================================================

#ifdef GROUPS_NUM_2
#define GROUPS_NUM_1
#endif

#ifdef GROUPS_NUM_3
#define GROUPS_NUM_1
#define GROUPS_NUM_2
#endif

#ifdef GROUPS_NUM_4
#define GROUPS_NUM_1
#define GROUPS_NUM_2
#define GROUPS_NUM_3
#endif

//========================================================================

#define CalculateFmriImageColor(index) \
{\
	finalColor = vec4(1.0,1.0,0.0,1.0);\
	vec4 newCoord;\
	newCoord = vTexCoord##index##;\
	vec3 texc3 = vec3(newCoord.x, newCoord.y,newCoord.z);\
	vec4 color1 =vec4(0.0);\
	color1 = texture(grProp_##index##_fmriTexture,texc3);\
	finalColor = texture(grProp_##index##_TransferFuncofFmri, color1.x);\
}

//========================================================================
#define CalculateMainImageColor(index) \
{\
	finalColor =vec4(0.0,1.0,1.0,1.0);\
	vec4 newCoord;\
	newCoord = vTexCoord##index##;\
	vec3 texc3 = vec3(newCoord.x, newCoord.y,newCoord.z);\
	vec4 initialcolor = texture(grProp_##index##_baseTexture, texc3);\
	if(grProp_##index##_mainImageIsColored)\
{\
	finalColor =vec4(initialcolor.x, initialcolor.y, initialcolor.z, initialcolor.w);\
}\
else\
{\
	vec4 RayCastingColor = texture(grProp_##index##_TransferFuncofWindowLevel, initialcolor.x);\
	if ((!grProp_##index##_UseAlphaForMainBlending) && (!grProp_##index##_UseColorForMT))\
{\
	finalColor = vec4(0 , 0 , 1, 1);\
}\
	else if ((!grProp_##index##_UseAlphaForMainBlending) && (grProp_##index##_UseColorForMT))\
{\
	finalColor = vec4( 0 , 1 , 0 , 1);\
}\
	else if ((grProp_##index##_UseAlphaForMainBlending) && (!grProp_##index##_UseColorForMT))\
{\
	finalColor = vec4(1 , 0 , 0 , 1);\
}\
	else\
{\
	float redPart   = RayCastingColor.x * grProp_##index##_TexColorRedPart;\
	float greenPart = RayCastingColor.y * grProp_##index##_TexColorGreenPart;\
	float bluePart  = RayCastingColor.z * grProp_##index##_TexColorBluePart;\
	finalColor = vec4(redPart,greenPart,bluePart,grProp_##index##_OpacityOfMT);\
}\
}\
}

//========================================================================

#define	CalculateColorMapResult(index) \
 {\
	finalColor=vec4(0.0);\
 	vec4 Coord=vTexCoord##index##;\
 	vec3	texc3 = vec3(Coord.x, Coord.y,Coord.z);\
  	vec4	initialcolor  =	texture(grProp_##index##_baseTexture,texc3);\
    vec4	ColorMapOutput   =	texture(grProp_##index##_TransferFuncofColorMap, initialcolor.x);\
 	finalColor=ColorMapOutput;\
 }
//========================================================================

#define BlendSegmentedTextures(c1 , c2) \
	vec4(c1.r + c2.r , c1.g + c2.g , c1.b + c2.b , max(c1.a , c2.a)); 


#define BlendFmriTextures(c1 , c2) \
	vec4(c1.r + c2.r,c1.g + c2.g,c1.b + c2.b,max(c1.a , c2.a)); 

//========================================================================
//--->>

//---------------Color Mixing Functions Definition
vec4	BlendMainTextures(vec4 c1, vec4 c2)
{
	float Y_NEW_INTENSITY_R = c2.a * c2.r;
	float X_NEW_INTENSITY_R = c1.a * c1.r;

	float Total_INTENSITY_R = max(X_NEW_INTENSITY_R, Y_NEW_INTENSITY_R);

	float Y_NEW_INTENSITY_G = c2.a * c2.g;
	float X_NEW_INTENSITY_G = c1.a * c1.g;

	float Total_INTENSITY_G = max(X_NEW_INTENSITY_G, Y_NEW_INTENSITY_G);

	float Y_NEW_INTENSITY_B = c2.a * c2.b;
	float X_NEW_INTENSITY_B = c1.a * c1.b;

	float Total_INTENSITY_B = max(X_NEW_INTENSITY_B, Y_NEW_INTENSITY_B);

	vec4 result = vec4(Total_INTENSITY_R, Total_INTENSITY_G, Total_INTENSITY_B, 1.0);
	return result;
}


vec4	MixImageAndColor(vec4 IMAGE, vec4 SEGMENTEDCOLOR)
{
	float SegmentedOpacity = SEGMENTEDCOLOR.a;
	float MainImageOpacity = 1 - SegmentedOpacity;
	vec4 out1, out2, result;

	out1 = SegmentedOpacity*SEGMENTEDCOLOR;
	out1.a = SegmentedOpacity;

	out2 = MainImageOpacity * IMAGE;
	out2.a = MainImageOpacity;

	result = out1 + out2;

	return result;
}




#ifdef GROUPS_NUM_1
GroupProperties(1)

#ifdef GroupContainedColorMap_1_1_isActive
StrObjectColorMap(1, 1)
#endif						  
#ifdef GroupContainedColorMap_1_2_isActive
StrObjectColorMap(1, 2)
#endif						  
#ifdef GroupContainedColorMap_1_3_isActive
StrObjectColorMap(1, 3)
#endif						  
#ifdef GroupContainedColorMap_1_4_isActive
StrObjectColorMap(1, 4)
#endif						  
#ifdef GroupContainedColorMap_1_5_isActive
StrObjectColorMap(1, 5)
#endif
#ifdef GroupContainedColorMap_1_6_isActive
StrObjectColorMap(1, 6)
#endif	

#endif

#ifdef GROUPS_NUM_2
GroupProperties(2)


#ifdef GroupContainedColorMap_2_1_isActive
StrObjectColorMap(2, 1)
#endif						  
#ifdef GroupContainedColorMap_2_2_isActive
StrObjectColorMap(2, 2)
#endif						  
#ifdef GroupContainedColorMap_2_3_isActive
StrObjectColorMap(2, 3)
#endif						  
#ifdef GroupContainedColorMap_2_4_isActive
StrObjectColorMap(2, 4)
#endif						  
#ifdef GroupContainedColorMap_2_5_isActive
StrObjectColorMap(2, 5)
#endif
#ifdef GroupContainedColorMap_2_6_isActive
StrObjectColorMap(2, 6)
#endif

#endif

#ifdef GROUPS_NUM_3
GroupProperties(3)

#ifdef GroupContainedColorMap_3_1_isActive
StrObjectColorMap(3, 1)
#endif						  
#ifdef GroupContainedColorMap_3_2_isActive
StrObjectColorMap(3, 2)
#endif						  
#ifdef GroupContainedColorMap_3_3_isActive
StrObjectColorMap(3, 3)
#endif						  
#ifdef GroupContainedColorMap_3_4_isActive
StrObjectColorMap(3, 4)
#endif						  
#ifdef GroupContainedColorMap_3_5_isActive
StrObjectColorMap(3, 5)
#endif
#ifdef GroupContainedColorMap_3_6_isActive
StrObjectColorMap(3, 6)
#endif	

#endif

#ifdef GROUPS_NUM_4
GroupProperties(4)

#ifdef GroupContainedColorMap_4_1_isActive
StrObjectColorMap(4, 1)
#endif						  
#ifdef GroupContainedColorMap_4_2_isActive
StrObjectColorMap(4, 2)
#endif						  
#ifdef GroupContainedColorMap_4_3_isActive
StrObjectColorMap(4, 3)
#endif						  
#ifdef GroupContainedColorMap_4_4_isActive
StrObjectColorMap(4, 4)
#endif						  
#ifdef GroupContainedColorMap_4_5_isActive
StrObjectColorMap(4, 5)
#endif
#ifdef GroupContainedColorMap_4_6_isActive
StrObjectColorMap(4, 6)
#endif	

#endif



void main(void)
{
	vec4	MainColor0 = vec4(0.0);
	vec4	PolyColor1 = vec4(0.0);
	vec4	FmriColor0 = vec4(0.0);
	vec4	MainColor1 = vec4(0.0);
	vec4	PolyColor2 = vec4(0.0);
	vec4	FmriColor1 = vec4(0.0);
	vec4	ColorMapOutput0 = vec4(0.0);
	vec4	ColorMapOutput1 = vec4(0.0);
	vec4	finalColor = vec4(0.0);
	vec4    segmentedColor = vec4(0.0);
	//	~~~~~~~~~~~~~~~~~~~      Main Textures     ~~~~~~~~~~~~~~~~~~~  //			

#ifdef GROUPS_NUM_1
#ifdef grProp_1_VisiblityOfMT

	CalculateMainImageColor(1);
	MainColor0 = finalColor;

#endif
#endif

#ifdef GROUPS_NUM_2
#ifdef grProp_2_VisiblityOfMT

	CalculateMainImageColor(2);
	MainColor1 = finalColor;

#endif
#endif
	//  ~~~~~~~~~~~~~~~~~~~        ColorMap        ~~~~~~~~~~~~~~~~~~~  //
#ifdef GROUPS_NUM_2
#ifdef grProp_1_VisiblityOfColorMap
	CalculateColorMapResult(1);
	ColorMapOutput0 = finalColor;
#endif
#endif

#ifdef GROUPS_NUM_3
#ifdef grProp_2_VisiblityOfColorMap

	CalculateColorMapResult(2);
	ColorMapOutput1 = finalColor;

#endif
#endif

	//	~~~~~~~~~~~~~~~~~~~   Segmented Textures   ~~~~~~~~~~~~~~~~~~~  //	


	bool calc_flag = false;
	segmentedColor = vec4(0.0);
	vec3 texc3;
	vec4 color1;

#ifdef GROUPS_NUM_1
#ifdef grProp_1_VisiblityofSegmentedImage
	texc3 = vec3(vTexCoord1.x, vTexCoord1.y, vTexCoord1.z);
	color1 = texture(grProp_1_segmentedTexture, texc3);
#ifdef GroupContainedColorMap_1_1_isActive
	ColorDecoderForSegmentedAreas(1, 1)
#endif						  
#ifdef GroupContainedColorMap_1_2_isActive
		ColorDecoderForSegmentedAreas(1, 2)
#endif						  
#ifdef GroupContainedColorMap_1_3_isActive
		ColorDecoderForSegmentedAreas(1, 3)
#endif						  
#ifdef GroupContainedColorMap_1_4_isActive
		ColorDecoderForSegmentedAreas(1, 4)
#endif						  
#ifdef GroupContainedColorMap_1_5_isActive
		ColorDecoderForSegmentedAreas(1, 5)
#endif
#ifdef GroupContainedColorMap_1_6_isActive
		ColorDecoderForSegmentedAreas(1, 6)
#endif
		PolyColor1 = segmentedColor;
#endif	
#endif


#ifdef GROUPS_NUM_2
#ifdef grProp_2_VisiblityofSegmentedImage
	 texc3 = vec3(vTexCoord2.x, vTexCoord2.y, vTexCoord2.z);
	 color1 = texture(grProp_2_segmentedTexture, texc3);
#ifdef GroupContainedColorMap_2_1_isActive
	ColorDecoderForSegmentedAreas(2,1)		   
#endif						   
#ifdef GroupContainedColorMap_2_2_isActive
	ColorDecoderForSegmentedAreas(2,2)		  
#endif						  
#ifdef GroupContainedColorMap_2_3_isActive
	ColorDecoderForSegmentedAreas(2,3)		  
#endif						  
#ifdef GroupContainedColorMap_2_4_isActive
	ColorDecoderForSegmentedAreas(2,4)		  
#endif						  
#ifdef GroupContainedColorMap_2_5_isActive
	ColorDecoderForSegmentedAreas(2,5)		  
#endif						  
#ifdef GroupContainedColorMap_2_6_isActive
	ColorDecoderForSegmentedAreas(2,6)
#endif
	PolyColor2 = segmentedColor;
#endif	
#endif


	//	~~~~~~~~~~~~~~~~~~~~~~   FMRI Textures   ~~~~~~~~~~~~~~~~~~~~~  //	

#ifdef GROUPS_NUM_2
#ifdef grProp_1_VisiblityofFmriImage
	CalculateFmriImageColor(1);
	FmriColor0 = finalColor;
#endif
#endif

#ifdef GROUPS_NUM_3
#ifdef grProp_2_VisiblityofFmriImage
	CalculateFmriImageColor(2);
	FmriColor1 = finalColor;
#endif
#endif
	//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  //	
	vec4	Mains = BlendMainTextures(MainColor0, MainColor1);
	vec4	Segments = BlendSegmentedTextures(PolyColor1, PolyColor2);
	vec4	Fmri = BlendFmriTextures(FmriColor0, FmriColor1);

	vec4  res0 = MixImageAndColor(Mains, ColorMapOutput0);
	vec4  res1 = MixImageAndColor(res0, ColorMapOutput1);
	vec4  res2 = MixImageAndColor(res1, Segments);
	vec4  res3 = MixImageAndColor(res2, Fmri);

	//	vec4  Mains =	BlendMainTextures(MainColor0,MainColor1);
	//	vec4  res2	=	MixImageAndColor(MainColor0,PolyColor0);
	// 					
#ifdef VideoTextureExisted 
	//gl_FragColor = BlendResultWithVideo(res2);
	gl_FragColor = BlendResultWithVideo(res3);
#else

	gl_FragColor = res3;

#endif

}
