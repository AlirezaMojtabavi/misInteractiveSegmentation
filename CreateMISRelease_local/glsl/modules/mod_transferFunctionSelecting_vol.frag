

#define ColorDecoderForSegmentedAreas(index,obj_index) \
if(!calc_flag)\
{\
	if(VolumeColorMap_##index##_1_numberOfBits == 0)\
	{\
	color=texture(VolumeColorMap_##index##_1_TransferFunction,voxel##index##.x);\
	}\
	else\
	{\
		color = vec4(0.0,0.0,0.0,0.0);\
		int deNormalize = int(voxel##index##.x * 65535);/*convert normalized value to unsigned integer value. */\
		int maxBit = VolumeColorMap_##index##_##obj_index##_startBit + VolumeColorMap_##index##_##obj_index##_numberOfBits-1;\
		int maskVal = CalculatePower2(maxBit);/*// form of this value is: XXXX10XXXX and it depends on alocated bits.*/\
		int marginMaskVal = CalculatePower2(maxBit-1);\
		int andVal = deNormalize & (maskVal | marginMaskVal);\
		if(andVal>0)\
		{\
			int minExponent = VolumeColorMap_##index##_##obj_index##_startBit;\
			int tempVal2 = ShiftRight(deNormalize ,minExponent);\
			float coord =float((tempVal2)&int(3))/3;\
			color = texture(VolumeColorMap_##index##_##obj_index##_TransferFunction, coord);\
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
