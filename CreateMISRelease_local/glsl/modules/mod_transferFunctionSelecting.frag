#extension GL_EXT_gpu_shader4 : enable
/*
The macro defined in this file is the deformed version of the TFselection function which was used in the previous
version of the fragment shader for applying special colormaps in the segmented areas. In the kernel of this code is a
decoding from float type values in a 3D texture to a special colormap for each of the segmented areas.

** In the ATI graphic card there are some differences in calculating colormap values from GroupContainedColorMap_ texture.

*/

#define ColorDecoderForSegmentedAreas(index,obj_index) \
if(color1.x != 0 && !calc_flag)\
{\
	if(GroupContainedColorMap_##index##_1_numberOfBits == 0)\
	{\
		segmentedColor=texture(GroupContainedColorMap_##index##_1_TransferFunction, color1.x);\
	}\
	else\
	{\
		segmentedColor = vec4(0.0,0.0,0.0,0.0);\
		int deNormalize = int(color1.x * 65535);/*convert normalized value to unsigned integer value. */\
		int maxBit = GroupContainedColorMap_##index##_##obj_index##_startBit + GroupContainedColorMap_##index##_##obj_index##_numberOfBits-1;\
		int maskVal = CalculatePower2(maxBit);/*// form of this value is: XXXX10XXXX and it depends on alocated bits.*/\
		int marginMaskVal = CalculatePower2(maxBit-1);\
		int andVal = deNormalize & (maskVal | marginMaskVal);\
		if(andVal>0)\
		{\
			int minExponent = GroupContainedColorMap_##index##_##obj_index##_startBit;\
			int tempVal2 = ShiftRight(deNormalize ,minExponent);\
			float coord =float((tempVal2)&int(3))/3;/*Here is some <??ambiguous> differences between ATI  and Nvidia cards. */ \
			/*If the tempVal2 in the above line not subtracted by one results in a small <alpha> value for ATI card.*/\
			segmentedColor = texture(GroupContainedColorMap_##index##_##obj_index##_TransferFunction, coord);\
			calc_flag=true;\
		}\
		else\
		{\
		calc_flag=false;\
		}\
	}\
}



//-----------------Functions Related to the Segmented Image Colormap
int CalculatePower2(int exponent)
{
	int firstVAl = 1;
	int res = firstVAl << exponent;

	return res;
}

int ShiftRight(int originVal, int repeatNumber)
{
	int res = originVal >> repeatNumber;
	return res;
}

int BitWiseAnd(int val1, int val2)
{
	int res = 0;
	res = val1 & val2;
	return res;
}
