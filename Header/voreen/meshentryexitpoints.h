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

#pragma  once
#include "renderprocessor.h"
 
#include "meshlistgeometry.h"

#include "floatproperty.h"
#include "cameraproperty.h"

#include "shadermanager.h"
#include "exception.h"
#include "vector.h"
#include "VoreenMacroes.h"
#include "boolproperty.h"

namespace tgt {
 	            class RenderTarget;
              }
namespace voreen {

class CameraInteractionHandler;

/**
 * Calculates the entry and exit points for GPU raycasting and stores them in textures.
 *
 * @see CubeMeshProxyGeometry, SingleVolumeRaycaster
 */


class  VOREENEXPORTS  MeshEntryExitPoints : public RenderProcessor {
public:
    MeshEntryExitPoints();
    virtual ~MeshEntryExitPoints();
    virtual Processor* create() const;

    virtual std::string getClassName() const    { return "MeshEntryExitPoints"; }
    virtual std::string getCategory() const     { return "EntryExitPoints"; }
    virtual CodeState getCodeState() const      { return CODE_STATE_STABLE; }

    virtual std::string getProcessorInfo() const;
    virtual bool isReady() const;
 
	virtual void SetCamera(tgt::Camera cam);
	virtual void manageRenderTargets();
	void SetTestWithoutCheckPort(bool val);	
	void  SetRenderEntyToScene(bool val);
 	void  SetRenderExitToScene(bool val);
	tgt::RenderTarget* GetExitRenderTarget() const;
	tgt::RenderTarget* GetEntryRenderTarget() const;

 
	virtual void beforeProcess();
    virtual void process();
    void initialize(tgt::ivec3 size) throw (VoreenException);
	virtual void SetWindowSize(tgt::ivec2 wsize);
	bool GetCLipWithARbitaryPlane() const;
	void SetCLipWithARbitaryPlane(bool val);
	tgt::vec4 GetPlane() const;
	void SetPlane(tgt::vec4 val);
protected:
   	tgt::Texture* errorTex_;
	bool m_TestWithoutCheckPort;
	bool m_RenderEntyToScene;
	bool  m_RenderExitToScene;
 	bool  m_CLipWithARbitaryPlane;
	tgt::vec4   m_ClipingPlane;

	virtual void deinitialize() throw (VoreenException);
	

    MeshListGeometry geometry_;

    tgt::Shader* shaderProgram_;

    // processor properties
    BoolProperty supportCameraInsideVolume_;
    BoolProperty useFloatRenderTargets_;
  


 
    GeometryPort inport_;
	tgt::RenderTarget*   entryRenderTarget;
 	tgt::RenderTarget*   exitRenderTarget;


    /// Category used for logging.
    static const std::string loggerCat_;


private:
	  tgt::Camera camera_;  ///< camera used for rendering the proxy geometry
};

} // namespace voreen


