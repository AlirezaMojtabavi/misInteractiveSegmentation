//-Start of the main fragment shader file
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "modules/vrn_shaderincludes.frag"
#include "modules/mod_transferFunctionSelecting_vol.frag"

////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



vec4 result = vec4(0.0);
vec4 result1 = vec4(0.0);
vec4 result2 = vec4(0.0);
uniform vec3 ToolPosition;
uniform ivec3 ImageDimension;
/*uniform int CropDirection;*/
float yThreshold;
float zThreshold;
float xThreshold;



// declare entry and exit parameters
uniform SAMPLER2D_TYPE entryPoints_;            // ray entry points
uniform SAMPLER2D_TYPE entryPointsDepth_;       // ray entry points depth
uniform TEXTURE_PARAMETERS entryParameters_;
uniform SAMPLER2D_TYPE exitPoints_;             // ray exit points
uniform SAMPLER2D_TYPE exitPointsDepth_;        // ray exit points depth
uniform TEXTURE_PARAMETERS exitParameters_;


#define StrObjectColorMap(index,obj_index)\
uniform int VolumeColorMap_##index##_##obj_index##_startBit;\
uniform int VolumeColorMap_##index##_##obj_index##_numberOfBits;\
uniform sampler1D VolumeColorMap_##index##_##obj_index##_TransferFunction;



#ifdef VOLUME_1_ACTIVE
uniform sampler3D volume_1;
#ifdef VolumeColorMap_1_1_isActive
StrObjectColorMap(1,1)
#endif
#ifdef VolumeColorMap_1_2_isActive
StrObjectColorMap(1,2)
#endif
#ifdef VolumeColorMap_1_3_isActive
StrObjectColorMap(1,3)
#endif
#ifdef VolumeColorMap_1_4_isActive
StrObjectColorMap(1,4)
#endif
#ifdef VolumeColorMap_1_5_isActive
StrObjectColorMap(1,5)
#endif
#ifdef VolumeColorMap_1_6_isActive
StrObjectColorMap(1,6)
#endif

#endif


#ifdef VOLUME_2_ACTIVE
uniform sampler3D volume_2;

#ifdef VolumeColorMap_2_1_isActive
StrObjectColorMap(2,1)
#endif
#ifdef VolumeColorMap_2_2_isActive
StrObjectColorMap(2,2)
#endif
#ifdef VolumeColorMap_2_3_isActive
StrObjectColorMap(2,3)
#endif
#ifdef VolumeColorMap_2_4_isActive
StrObjectColorMap(2,4)
#endif
#ifdef VolumeColorMap_2_5_isActive
StrObjectColorMap(2,5)
#endif
#ifdef VolumeColorMap_2_6_isActive
StrObjectColorMap(2,6)
#endif

#endif


#ifdef VOLUME_3_ACTIVE
uniform sampler3D volume_3;

#ifdef VolumeColorMap_3_1_isActive
StrObjectColorMap(3,1)
#endif
#ifdef VolumeColorMap_3_2_isActive
StrObjectColorMap(3,2)
#endif
#ifdef VolumeColorMap_3_3_isActive
StrObjectColorMap(3,3)
#endif
#ifdef VolumeColorMap_3_4_isActive
StrObjectColorMap(3,4)
#endif
#ifdef VolumeColorMap_3_5_isActive
StrObjectColorMap(3,5)
#endif
#ifdef VolumeColorMap_3_6_isActive
StrObjectColorMap(3,6)
#endif

#endif


#ifdef VOLUME_4_ACTIVE
uniform sampler3D volume_4;

#ifdef VolumeColorMap_4_1_isActive
StrObjectColorMap(4,1)
#endif
#ifdef VolumeColorMap_4_2_isActive
StrObjectColorMap(4,2)
#endif
#ifdef VolumeColorMap_4_3_isActive
StrObjectColorMap(4,3)
#endif
#ifdef VolumeColorMap_4_4_isActive
StrObjectColorMap(4,4)
#endif
#ifdef VolumeColorMap_4_5_isActive
StrObjectColorMap(4,5)
#endif
#ifdef VolumeColorMap_4_6_isActive
StrObjectColorMap(4,6)
#endif

#endif


uniform VOLUME_PARAMETERS volumeParameters[4];


bool   Crop(vec3  pos)
{
	if (pos.y > yThreshold)
	{
	#ifdef CUT_ANTERIORUP_ACTIVE
		if(pos.z < zThreshold)
			return true;
	#endif

	#ifdef CUT_ANTERIORDOWN_ACTIVE
		if(pos.z > zThreshold)
			return true;
	#endif
	}
	return false;
// 
// 
// 	vec4  voxelRes;
//  		if (CropDirection == 0)
//  		{
//  			return false;
//  		}
// 
//  		if (CropDirection == 1)
//  		{
// 			if ((pos.y > yThreshold) && (pos.y > 0.0))
// 			{
// 				return true; 
// 			}
// 		}
// 
//  		else if (CropDirection == 2)
//  		{
//  			if ((pos.y > yThreshold) && (pos.z < zThreshold))
//  			{
//  				return true;
//  			}
//  		}
//  
//  		else if (CropDirection == 3)
//  		{
//  			if ((pos.y > yThreshold) && (pos.z > zThreshold))
//  			{
//  			return true;
//  			}
//  		}
//  
//  		
//  
//  		else if (CropDirection == 4)
//  		{
//  			if ((pos.z < zThreshold) && (pos.z > 0.0))
//  			{
//  				return true;
//  			}
//  		}
//  
//  		else if (CropDirection == 5)
//  		{
//  			if ((pos.z > zThreshold) && (pos.z < 1.0))
//  			{
//  				return true;
//  			}
//  		}
//  
//  		else if (CropDirection == 6)
//  		{
//  			if ((pos.x < xThreshold) && (pos.x > 0.0))
//  			{
//  				return true;
//  			}
//  		}
//  
//  		else if (CropDirection == 7)
//  		{
//  			if ((pos.x > xThreshold) && (pos.x < 1.0))
//  			{
//  				return true;
//  			}
//  		}
// 		return false;

}

bool inUnitCube(vec3 sample) {
	if(any(greaterThan(sample, vec3(1.0))) || any(lessThan(sample, vec3(0.0))))
		return false;
	return true;
}

vec3 worldToTex(vec3 worldSamplePos, VOLUME_PARAMETERS volumeParameters) {
	//From world space to object space:
	vec3 samplePos = (volumeParameters.volumeTransformationINV_ * vec4(worldSamplePos, 1.0)).xyz;

	//From object space to texture space:
	samplePos = (samplePos + (volumeParameters.volumeCubeSize_ * 0.5)) * volumeParameters.volumeCubeSizeRCP_;
	return samplePos;
}

void rayTraversal(vec3 first,  vec3 last) 
{
	// calculate the required ray parameters
	float t     = 0.0;
    float tIncr = 0.0;//samplingStepSize_;
    float tEnd  = 1.0;
    vec3 rayDirection;
    raySetup(first, last, rayDirection, tIncr, tEnd);
	
#ifdef VOLUME_1_ACTIVE
    vec3 vol1first = worldToTex(first, volumeParameters[0]);
    vec3 vol1dir = worldToTex(last, volumeParameters[0]) - vol1first;
#endif

#ifdef VOLUME_2_ACTIVE
    vec3 vol2first = worldToTex(first, volumeParameters[1]);
    vec3 vol2dir = worldToTex(last, volumeParameters[1]) - vol2first;
#endif

#ifdef VOLUME_3_ACTIVE
    vec3 vol3first = worldToTex(first, volumeParameters[2]);
    vec3 vol3dir = worldToTex(last, volumeParameters[2]) - vol3first;
#endif

#ifdef VOLUME_4_ACTIVE
    vec3 vol4first = worldToTex(first, volumeParameters[3]);
    vec3 vol4dir = worldToTex(last, volumeParameters[3]) - vol4first;
#endif

    float realT;
    float tDepth  = -1.0;
    bool finished = false; 
	int test = 0;

    while(!finished)
	{
		realT = t / tEnd;
		vec4 color = vec4(0.0,0.0,0.0,1.0);
		vec3 worldSamplePos = first + t * rayDirection;
		bool cropVec = false;
		bool calc_flag=false;
		
	#ifdef VOLUME_1_ACTIVE	
		vec3 samplePos1 = vol1first + realT * vol1dir;
		vec4 voxel1;
		#ifdef CUT_ACTIVE
			cropVec=Crop(samplePos1);
 			if(cropVec)
  			{  		
 				voxel1=vec4(0,0,0,0);
  				color.a=0;
  			}
 			else
  			{
 				voxel1 = texture3D(volume_1, samplePos1);
				calc_flag=false;
				#ifdef VolumeColorMap_1_1_isActive
					ColorDecoderForSegmentedAreas(1,1)
				#endif
				#ifdef VolumeColorMap_1_2_isActive
					ColorDecoderForSegmentedAreas(1,2)
				#endif
				#ifdef VolumeColorMap_1_3_isActive
					ColorDecoderForSegmentedAreas(1,3)
				#endif
				#ifdef VolumeColorMap_1_4_isActive
					ColorDecoderForSegmentedAreas(1,4)
				#endif
				#ifdef VolumeColorMap_1_5_isActive
					ColorDecoderForSegmentedAreas(1,5)
				#endif
				#ifdef VolumeColorMap_1_6_isActive
					ColorDecoderForSegmentedAreas(1,6)
				#endif
				
 			}
		#else
			voxel1 = texture3D(volume_1, samplePos1);
			calc_flag=false;
			#ifdef VolumeColorMap_1_1_isActive
				ColorDecoderForSegmentedAreas(1,1)
			#endif
			#ifdef VolumeColorMap_1_2_isActive
				ColorDecoderForSegmentedAreas(1,2)
			#endif
			#ifdef VolumeColorMap_1_3_isActive
				ColorDecoderForSegmentedAreas(1,3)
			#endif
			#ifdef VolumeColorMap_1_4_isActive
				ColorDecoderForSegmentedAreas(1,4)
			#endif
			#ifdef VolumeColorMap_1_5_isActive
				ColorDecoderForSegmentedAreas(1,5)
			#endif
			#ifdef VolumeColorMap_1_6_isActive
				ColorDecoderForSegmentedAreas(1,6)
			#endif
	#endif	

		
 		 if (color.a > 0.0)
 		 {
 		 voxel1.xyz = RC_CALC_GRADIENTS(voxel1.xyz, samplePos1, volume_1, volumeParameters[0], t, rayDirection, entryPoints_, entryParameters_);
 		 color.rgb = RC_APPLY_SHADING(voxel1.xyz, samplePos1, volumeParameters[0], color.rgb, color.rgb, vec3(0.1,0.1,0.1));

		 result = compositeDVR(result, color,  t, tDepth);	
 
 		 }				

	#endif
		
	#ifdef VOLUME_2_ACTIVE
      
        vec3 samplePos2 = vol2first + realT * vol2dir;
        vec4 voxel2;
		#ifdef CUT_ACTIVE
			cropVec=Crop(samplePos2);
			if(cropVec)
			{  		
				voxel2=vec4(0,0,0,0);
				color.a=0;
			}
			else
			{
				voxel2 = texture3D(volume_2, samplePos2);
				calc_flag=false;
				#ifdef VolumeColorMap_2_1_isActive
					ColorDecoderForSegmentedAreas(2,1)
				#endif
				#ifdef VolumeColorMap_2_2_isActive
					ColorDecoderForSegmentedAreas(2,2)
				#endif
				#ifdef VolumeColorMap_2_3_isActive
					ColorDecoderForSegmentedAreas(2,3)
				#endif
				#ifdef VolumeColorMap_2_4_isActive
					ColorDecoderForSegmentedAreas(2,4)
				#endif
				#ifdef VolumeColorMap_2_5_isActive
					ColorDecoderForSegmentedAreas(2,5)
				#endif
				#ifdef VolumeColorMap_2_6_isActive
					ColorDecoderForSegmentedAreas(2,6)
				#endif
			
			}
		#else
			voxel2 = texture3D(volume_2, samplePos2);
			calc_flag=false;
			#ifdef VolumeColorMap_2_1_isActive
				ColorDecoderForSegmentedAreas(2,1)
			#endif
			#ifdef VolumeColorMap_2_2_isActive
				ColorDecoderForSegmentedAreas(2,2)
			#endif
			#ifdef VolumeColorMap_2_3_isActive
				ColorDecoderForSegmentedAreas(2,3)
			#endif
			#ifdef VolumeColorMap_2_4_isActive
				ColorDecoderForSegmentedAreas(2,4)
			#endif
			#ifdef VolumeColorMap_2_5_isActive
				ColorDecoderForSegmentedAreas(2,5)
			#endif
			#ifdef VolumeColorMap_2_6_isActive
				ColorDecoderForSegmentedAreas(2,6)
			#endif
		
		#endif

 		if (color.a > 0.0)
 		{
			voxel2.xyz = RC_CALC_GRADIENTS(voxel2.xyz, samplePos2, volume_2, volumeParameters[1], t, rayDirection, entryPoints_, entryParameters_);
  			color.rgb = RC_APPLY_SHADING(voxel2.xyz, samplePos2, volumeParameters[1], color.rgb, color.rgb, vec3(0.1,0.1,0.1));
  			result = compositeDVR(result, color, t, tDepth);		 
 		}				

	#endif

	#ifdef VOLUME_3_ACTIVE
      
        vec3 samplePos3 = vol3first + realT * vol3dir;
        vec4 voxel3;
	#ifdef CUT_ACTIVE
		 cropVec=Crop(samplePos3);
		if(cropVec)
 		{  		
			voxel3=vec4(0,0,0,0);
 			color.a=0;
 		}
		else
 		{
 			voxel3 = texture3D(volume_3, samplePos3);
			calc_flag=false;
 			#ifdef VolumeColorMap_3_1_isActive
				ColorDecoderForSegmentedAreas(3,1)
			#endif
			#ifdef VolumeColorMap_3_2_isActive
				ColorDecoderForSegmentedAreas(3,2)
			#endif
			#ifdef VolumeColorMap_3_3_isActive
				ColorDecoderForSegmentedAreas(3,3)
			#endif
			#ifdef VolumeColorMap_3_4_isActive
				ColorDecoderForSegmentedAreas(3,4)
			#endif
			#ifdef VolumeColorMap_3_5_isActive
				ColorDecoderForSegmentedAreas(3,5)
			#endif
			#ifdef VolumeColorMap_3_6_isActive
				ColorDecoderForSegmentedAreas(3,6)
			#endif
 		}
	#else
		voxel3 = texture3D(volume_3, samplePos3);
		calc_flag=false;
 		#ifdef VolumeColorMap_3_1_isActive
			ColorDecoderForSegmentedAreas(3,1)
		#endif
		#ifdef VolumeColorMap_3_2_isActive
			ColorDecoderForSegmentedAreas(3,2)
		#endif
		#ifdef VolumeColorMap_3_3_isActive
			ColorDecoderForSegmentedAreas(3,3)
		#endif
		#ifdef VolumeColorMap_3_4_isActive
			ColorDecoderForSegmentedAreas(3,4)
		#endif
		#ifdef VolumeColorMap_3_5_isActive
			ColorDecoderForSegmentedAreas(3,5)
		#endif
		#ifdef VolumeColorMap_3_6_isActive
			ColorDecoderForSegmentedAreas(3,6)
		#endif
		
		
	#endif
 		if (color.a > 0.0)
 		{
 			voxel3.xyz = RC_CALC_GRADIENTS(voxel3.xyz, samplePos3, volume_3, volumeParameters[2], t, rayDirection, entryPoints_, entryParameters_);
 			color.rgb = RC_APPLY_SHADING(voxel3.xyz, samplePos3, volumeParameters[2], color.rgb, color.rgb, vec3(0.1,0.1,0.1));
 			result = compositeDVR(result, color, t, tDepth);		 
 		}				
	#endif

	#ifdef VOLUME_4_ACTIVE
      
        vec3 samplePos4 = vol4first + realT * vol4dir;
        vec4 voxel4;
		#ifdef CUT_ACTIVE
			 cropVec=Crop(samplePos4);
			if(cropVec)
 			{  		
				voxel4=vec4(0,0,0,0);
 				color.a=0;
 			}
			else
 			{
 				voxel4 = texture3D(volume_4, samplePos4);
				calc_flag=false;
				#ifdef VolumeColorMap_4_1_isActive
					ColorDecoderForSegmentedAreas(4,1)
				#endif
				#ifdef VolumeColorMap_4_2_isActive
					ColorDecoderForSegmentedAreas(4,2)
				#endif
				#ifdef VolumeColorMap_4_3_isActive
					ColorDecoderForSegmentedAreas(4,3)
				#endif
				#ifdef VolumeColorMap_4_4_isActive
					ColorDecoderForSegmentedAreas(4,4)
				#endif
				#ifdef VolumeColorMap_4_5_isActive
					ColorDecoderForSegmentedAreas(4,5)
				#endif
				#ifdef VolumeColorMap_4_6_isActive
					ColorDecoderForSegmentedAreas(4,6)
				#endif
 			}

		#else
			voxel4 = texture3D(volume_4, samplePos4);
			calc_flag=false;
			#ifdef VolumeColorMap_4_1_isActive
				ColorDecoderForSegmentedAreas(4,1)
			#endif
			#ifdef VolumeColorMap_4_2_isActive
				ColorDecoderForSegmentedAreas(4,2)
			#endif
			#ifdef VolumeColorMap_4_3_isActive
				ColorDecoderForSegmentedAreas(4,3)
			#endif
			#ifdef VolumeColorMap_4_4_isActive
				ColorDecoderForSegmentedAreas(4,4)
			#endif
			#ifdef VolumeColorMap_4_5_isActive
				ColorDecoderForSegmentedAreas(4,5)
			#endif
			#ifdef VolumeColorMap_4_6_isActive
				ColorDecoderForSegmentedAreas(4,6)
			#endif
			
		#endif

 		if (color.a > 0.0)
 		{
 			voxel4.xyz = RC_CALC_GRADIENTS(voxel4.xyz, samplePos4, volume_4, volumeParameters[3], t, rayDirection, entryPoints_, entryParameters_);
 			color.rgb = RC_APPLY_SHADING(voxel4.xyz, samplePos4, volumeParameters[3], color.rgb, color.rgb, vec3(0.1,0.1,0.1));
 			result = compositeDVR(result, color, t, tDepth);		 
 		}
	#endif
	
	 finished = earlyRayTermination(result.a, EARLY_RAY_TERMINATION_OPACITY);
	 t += tIncr;                                            
	 finished = finished || (t > tEnd);

	}  
		
	gl_FragDepth = getDepthValue(tDepth, tEnd, entryPointsDepth_, entryParameters_, exitPointsDepth_, exitParameters_);

}

void main() {
	 
	if (ImageDimension.y!=0)
		 yThreshold = ToolPosition.y / ImageDimension.y;
	else
		yThreshold=0;
	
	if (ImageDimension.z!=0)
		  zThreshold = ToolPosition.z / ImageDimension.z;
	else
		zThreshold=0;
	
	if (ImageDimension.x!=0)
		xThreshold =  ToolPosition.x / ImageDimension.x;
	else
		xThreshold=0;


	vec3 frontPos = textureLookup2D(entryPoints_, entryParameters_, gl_FragCoord.xy).rgb;
	vec3 backPos = textureLookup2D(exitPoints_, exitParameters_, gl_FragCoord.xy).rgb;
 
 
	
	// determine whether the ray has to be casted
	if (frontPos == backPos)
		// background needs no raycasting
		 discard;
	else {
		// fragCoords are lying inside the bounding box
		rayTraversal(frontPos, backPos);
	}
	gl_FragColor =result;
}
