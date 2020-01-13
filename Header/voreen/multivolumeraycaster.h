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

#ifndef VRN_MULTIVOLUMERAYCASTER_H
#define VRN_MULTIVOLUMERAYCASTER_H


#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

#include "volumeraycaster.h"

#include "transfuncproperty.h"
#include "optionproperty.h"
#include "cameraproperty.h"
#include "floatproperty.h"

#include "volumeport.h" 
#include "rendertarget.h"
#include "exception.h"
#include "misCroppingDirectionInVR.h"
#include "TransferFuncs3D.h"
#include "misRaycastingShaderHeaderGenerator.h"

namespace voreen {

/**
 * Performs a single-pass multi-volume raycasting of up to four volumes,
 * providing several shading and compositing modes.
 *
 * @see MultiVolumeProxyGeometry, MeshEntryExitPoints
 */
using namespace tgt;




class VOREENEXPORTS MultiVolumeRaycaster : public VolumeRaycaster 
{

public:

	bool  testMode;
	tgt::Texture* testTexure;
	MultiVolumeRaycaster();
	~MultiVolumeRaycaster();
	virtual Processor* create() const;

	void MultiVolumeRaycaster::GenerateShaderHeader(VolumeHandle* volumeHandle,int numfVolume);


	virtual std::string getClassName() const    { return "MultiVolumeRaycaster"; }
	virtual std::string getCategory() const     { return "Raycasting"; }
	virtual CodeState getCodeState() const      { return CODE_STATE_STABLE; }
	virtual std::string getProcessorInfo() const;

	/**
	 * All inports and at least one outport need to be connected.
	 */
	virtual bool isReady() const;

	//RAMA Added
	void SetToolPosition(tgt::vec3);
	void SetCroppingDirection(misCroppingDirectionInVR CropDirection);
	misCroppingDirectionInVR  GetCroppingDirection()const ;
	VolumePort* getVolumePort(int id);
	void SetEntryPort(tgt::RenderTarget* val);
	void SetExitPort(tgt::RenderTarget* val) { exitPort_ = val; }
	//RAMA Added
	virtual void process();
	virtual void initialize(/*int numberOfVolume,*/tgt::ivec3 size) throw (VoreenException); 	
	void SetVolumeHandle( int index,VolumeHandle* val );
	void SetTransferFunction(int id, ImageContainedTransferFuncs3D transferFunction);

	void SetCamera(CameraProperty cam);
	void SetSampleRate(double sampleRate);
	tgt::RenderTarget* GetOutPort() const;
	
	void ResetMapInShader();
	void CompileVolumeShader(int numberOfVol);
	int GetNumofActiveVolumes() const;
	void SetNumofActiveVolumes(int val);

protected:


	virtual void deinitialize() throw (VoreenException);
	
	virtual void compile(/*VolumeHandle* volumeHandle*/int numberOfVol , bool forcedCompile = false);

	virtual void SetWindowSize(tgt::ivec2 wsize);
	

private:
	
	void setTextureParameters(tgt::Shader* shader, const std::string& uniform,tgt::RenderTarget* target);
	std::string ConvertTransferFunctionIndexToString( int volumeIndex , int TfIndex );
	std::string ConvertVolumeIndexToString( int volumeIndex );
	std::string ConvertVolumeParameterToString( int volumeIndex );
	
	std::shared_ptr<IShaderHeaderGenerator> m_ShaderHeaderGenerator;	
	int m_NumofActiveVolumes;
	std::vector< VolumeHandle*> volumehandles;
	tgt::RenderTarget* entryPort_;
	tgt::RenderTarget* exitPort_;
	tgt::RenderTarget* outPort_;

	tgt::Shader* raycastPrg_;               ///< shader program used by this raycaster (rc_multivolume.frag)
	std::vector<ImageContainedTransferFuncs3D> GroupTransferFunctions;
	IntOptionProperty texFilterMode1_;      ///< filter mode for volume 1
	IntOptionProperty texFilterMode2_;      ///< filter mode for volume 2
	IntOptionProperty texFilterMode3_;      ///< filter mode for volume 3
	IntOptionProperty texFilterMode4_;      ///< filter mode for volume 4

	GLEnumOptionProperty texClampMode1_;    ///< clamp mode for volume 1
	GLEnumOptionProperty texClampMode2_;    ///< clamp mode for volume 2
	GLEnumOptionProperty texClampMode3_;    ///< clamp mode for volume 3
	GLEnumOptionProperty texClampMode4_;    ///< clamp mode for volume 4
	FloatProperty texBorderIntensity_;      ///< border intensity for all volumes

	CameraProperty camera_;                 ///< the camera used for lighting calculations

	StringOptionProperty compositingMode1_;   ///< What compositing mode should be applied for second outport
	StringOptionProperty compositingMode2_;   ///< What compositing mode should be applied for third outport

	tgt::vec3 m_ToolPosition;
	misCroppingDirectionInVR m_cropDirection;
	

};


} // namespace voreen

#endif // VRN_MULTIVOLUMERAYCASTER_H
