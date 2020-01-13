/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2010 The Voreen Team. <http://www.voreen.org>   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#include "modules/vrn_shaderincludes.frag"
 vec4 result = vec4(0.0);
 vec4 result1 = vec4(0.0);
 vec4 result2 = vec4(0.0);
 uniform vec3 ToolPosition;
uniform vec3 ImageDimension;
uniform int CropDirection;
float yThreshold;
float zThreshold;
float xThreshold;
bool   Crop(vec3  pos)
{

	vec4  voxelRes;
	
		if (CropDirection == 1)
		{
			if ((pos.y > yThreshold) && (pos.y > 0.0))
			{
				return false; 
			}
		}

		else if (CropDirection == 2)
		{
			if ((pos.y > yThreshold) && (pos.z < zThreshold))
			{
				return false;
			}
		}

		else if (CropDirection == 3)
		{
			if ((pos.y > yThreshold) && (pos.z > zThreshold))
			{
			return false;
			}
		}

		

		else if (CropDirection == 4)
		{
			if ((pos.z < zThreshold) && (pos.z > 0.0))
			{
				return false;
			}
		}

		else if (CropDirection == 5)
		{
			if ((pos.z > zThreshold) && (pos.z < 1.0))
			{
				return false;
			}
		}

		else if (CropDirection == 6)
		{
			if ((pos.x < xThreshold) && (pos.x > 0.0))
			{
				return false;
			}
		}

		else if (CropDirection == 7)
		{
			if ((pos.x > xThreshold) && (pos.x < 1.0))
			{
				return false;
			}
		}
		return true;

}



// declare entry and exit parameters
uniform SAMPLER2D_TYPE entryPoints_;            // ray entry points
uniform SAMPLER2D_TYPE entryPointsDepth_;       // ray entry points depth
uniform TEXTURE_PARAMETERS entryParameters_;
uniform SAMPLER2D_TYPE exitPoints_;             // ray exit points
uniform SAMPLER2D_TYPE exitPointsDepth_;        // ray exit points depth
uniform TEXTURE_PARAMETERS exitParameters_;
// declare volume
uniform sampler3D volume1_;                      // volume data set
uniform VOLUME_PARAMETERS volumeParameters1_;    // texture lookup parameters for volume1_
uniform TF_SAMPLER_TYPE_1 transferFunc_;


 
#ifdef VOLUME_2_ACTIVE
uniform sampler3D volume2_;                      // volume data set
uniform VOLUME_PARAMETERS volumeParameters2_;    // texture lookup parameters for volume2_
uniform TF_SAMPLER_TYPE_2 transferFunc2_;
#endif

#ifdef VOLUME_3_ACTIVE
uniform sampler3D volume3_;                      // volume data set
uniform VOLUME_PARAMETERS volumeParameters3_;    // texture lookup parameters for volume3_
uniform TF_SAMPLER_TYPE_3 transferFunc3_;
#endif

#ifdef VOLUME_4_ACTIVE
uniform sampler3D volume4_;                      // volume data set
uniform VOLUME_PARAMETERS volumeParameters4_;    // texture lookup parameters for volume4_
uniform TF_SAMPLER_TYPE_4 transferFunc4_;
#endif



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

/***
 * Performs the ray traversal
 * returns the final fragment color.
 ***/
void rayTraversal(in vec3 first, in vec3 last) {

	

    // calculate the required ray parameters
    float t     = 0.0;
    float tIncr = 0.0;
    float tEnd  = 1.0;
    vec3 rayDirection;
    raySetup(first, last, rayDirection, tIncr, tEnd);

    vec3 vol1first = worldToTex(first, volumeParameters1_);
    vec3 vol1dir = worldToTex(last, volumeParameters1_) - vol1first;
 #ifdef VOLUME_2_ACTIVE
    vec3 vol2first = worldToTex(first, volumeParameters2_);
    vec3 vol2dir = worldToTex(last, volumeParameters2_) - vol2first;
#endif
#ifdef VOLUME_3_ACTIVE
    vec3 vol3first = worldToTex(first, volumeParameters3_);
    vec3 vol3dir = worldToTex(last, volumeParameters3_) - vol3first;
#endif
#ifdef VOLUME_4_ACTIVE
    vec3 vol4first = worldToTex(first, volumeParameters4_);
    vec3 vol4dir = worldToTex(last, volumeParameters4_) - vol4first;
#endif
    float realT;
 
    float tDepth = -1.0;                                      
    bool finished = false;                                     
       for (int loop=0; !finished ; loop++)
	     
	{

		realT = t / tEnd;
		
		vec3 worldSamplePos = first + t * rayDirection;
		//--------------VOLUME 1---------------------
		//vec3 samplePos1 = worldToTex(worldSamplePos, volumeParameters1_);
		vec3 samplePos1 = vol1first + realT * vol1dir;

		vec4 voxel1;
		bool cropVec=Crop(samplePos1);
		if(!cropVec)
		{
			voxel1=vec4(0,0,0,0);
			//finished=true;
			//break;
			
		}
		else
		{
			voxel1 = texture3D(volume1_, samplePos1);


			vec4 color = applyTF(transferFunc_, voxel1);

			/*if(color.x&1)
			color=vec4(0,1,0,1); */
			if (color.a > 0.0)
			{

				voxel1.xyz = RC_CALC_GRADIENTS(voxel1.xyz, samplePos1, volume1_, volumeParameters1_, t, rayDirection, entryPoints_, entryParameters_);
				color.rgb = RC_APPLY_SHADING_1(voxel1.xyz, samplePos1, volumeParameters1_, color.rgb, color.rgb, vec3(0.1,0.1,0.1));
				result = RC_APPLY_COMPOSITING_1(result, color, worldSamplePos, voxel1.xyz, t, tDepth);


			}
		}

	
                                     
    	
#ifdef VOLUME_2_ACTIVE
        //second sample:
        //vec3 samplePos2 = worldToTex(worldSamplePos, volumeParameters2_);
        vec3 samplePos2 = vol2first + realT * vol2dir;

        vec4 voxel2;
		cropVec=Crop(samplePos2);
		if(!cropVec)
		{
			voxel2=vec4(0,0,0,0);
			//finished=true;
			//break;
			
		}
		else
		{
			voxel2 = texture3D(volume2_, samplePos2);

			vec4 color2 = applyTF(transferFunc2_, voxel2);

			int val=int (voxel2.x*255);
			bool checkEras=bool(val&2);
			if(checkEras)
			{
				color2.b=1;
				color2.r=0.0;
			}


			if (color2.a > 0.0) {

				// calculate gradients
				voxel2.xyz = RC_CALC_GRADIENTS(voxel2.xyz, samplePos2, volume2_, volumeParameters2_, t, rayDirection, entryPoints_, entryParameters_);

				// apply classification

				// apply shading
				color2.rgb = RC_APPLY_SHADING_2(voxel2.xyz, samplePos2, volumeParameters2_, color2.rgb, color2.rgb, vec3(0.1,0.1,0.1));

				// if opacity greater zero, apply compositing

				result = RC_APPLY_COMPOSITING_1(result, color2, worldSamplePos, voxel2.xyz, t, tDepth);
			}
           
        }
#endif

  
	


// gl_FragDepth= textureLookup2D(exitPointsDepth_, exitParameters_, gl_FragCoord.xy).z;
#ifdef VOLUME_3_ACTIVE
        //second sample:
        //vec3 samplePos3 = worldToTex(worldSamplePos, volumeParameters3_);
        vec3 samplePos3 = vol3first + realT * vol3dir;

        vec4 voxel3;
		 cropVec=Crop(samplePos3);
		if(!cropVec)
		{
			voxel3=vec4(0,0,0,0);
			//finished=true;
			//break;
			
		}
		else
		{
			voxel3 = texture3D(volume3_, samplePos3);

			vec4 color3 = applyTF(transferFunc3_, voxel3);
			if (color3.a > 0.0) {

				// calculate gradients
				voxel3.xyz = RC_CALC_GRADIENTS(voxel3.xyz, samplePos3, volume3_, volumeParameters3_, t, rayDirection, entryPoints_, entryParameters_);

				// apply classification

				// apply shading
				color3.rgb = RC_APPLY_SHADING_3(voxel3.xyz, samplePos3, volumeParameters3_, color3.rgb, color3.rgb, vec3(0.1,0.1,0.1));

				// if opacity greater zero, apply compositing
				RC_BEGIN_COMPOSITING
					result = RC_APPLY_COMPOSITING_1(result, color3, worldSamplePos, voxel3.xyz, t, tDepth);
				//   result1 = RC_APPLY_COMPOSITING_2(result1, color3, worldSamplePos, voxel3.xyz, t, tDepth);
				//result2 = RC_APPLY_COMPOSITING_3(result2, color3, worldSamplePos, voxel3.xyz, t, tDepth);
				RC_END_COMPOSITING
			}
        }
#endif

#ifdef VOLUME_4_ACTIVE
        //second sample:
        //vec3 samplePos4 = worldToTex(worldSamplePos, volumeParameters4_);
        vec3 samplePos4 = vol4first + realT * vol4dir;

        vec4 voxel4;
		 cropVec=Crop(samplePos4);
		if(!cropVec)
		{
			voxel4=vec4(0,0,0,0);
			//finished=true;
			//break;
			 
		}
		else
		{
			voxel4 = texture3D(volume4_, samplePos4);

			vec4 color4 = applyTF(transferFunc4_, voxel4);
			if (color4.a > 0.0) {

				// calculate gradients
				voxel4.xyz = RC_CALC_GRADIENTS(voxel4.xyz, samplePos4, volume4_, volumeParameters4_, t, rayDirection, entryPoints_, entryParameters_);

				// apply classification

				// apply shading
				color4.rgb = RC_APPLY_SHADING_4(voxel4.xyz, samplePos4, volumeParameters4_, color4.rgb, color4.rgb, vec3(0.1,0.1,0.1));

				// if opacity greater zero, apply compositing
				RC_BEGIN_COMPOSITING
					result = RC_APPLY_COMPOSITING_1(result, color4, worldSamplePos, voxel4.xyz, t, tDepth);
				// result1 = RC_APPLY_COMPOSITING_2(result1, color4, worldSamplePos, voxel4.xyz, t, tDepth);
				// result2 = RC_APPLY_COMPOSITING_3(result2, color4, worldSamplePos, voxel4.xyz, t, tDepth);
				RC_END_COMPOSITING
			}
		}
#endif
   	 finished = earlyRayTermination(result.a, EARLY_RAY_TERMINATION_OPACITY);
	t += tIncr;                                            
	finished = finished || (t > tEnd);
 
 		 
	  
 
	}  
		
	gl_FragDepth = getDepthValue(tDepth, tEnd, entryPointsDepth_, entryParameters_, exitPointsDepth_, exitParameters_);
	//gl_FragDepth = 0.0;
 
}

/***
 * The main method.
 ***/
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
	

        FragData0 =result;
		//	gl_FragDepth = textureLookup2Dnormalized(entryPoints_, exitParameters_, gl_FragCoord.xy).z; 
}
