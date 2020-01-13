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

#ifndef VRN_CANVASRENDERER_H
#define VRN_CANVASRENDERER_H

#include "renderprocessor.h"
#include "exception.h"
#include "vectorproperty.h"
#include "boolproperty.h"
#include "cameraproperty.h"
#include "rendertarget.h"
#include "VoreenMacroes.h"
namespace tgt {
class GLCanvas;  // forward declaration
class Texture;
class RenderTarget;
}

namespace voreen {

/**
 * A CanvasRenderer is a terminating element in a network. Its purpose is to copy
 * its input to the associated canvas and to issue canvas updates on invalidations.
 * Additionally, the CanvasRenderer can take snapshots of arbitrary dimensions.
 */
 

class VOREENEXPORTS CanvasRenderer : public RenderProcessor {
public:
	friend class misVoreenStepByStep;

    CanvasRenderer();
    ~CanvasRenderer();
	friend class misVoreenStepByStep;
    virtual std::string getClassName() const    { return "Canvas"; }
    virtual std::string getCategory() const     { return "View"; }
    virtual CodeState getCodeState() const      { return CODE_STATE_STABLE; }

    virtual std::string getProcessorInfo() const;
    virtual Processor* create() const;

    virtual void invalidate(int inv = INVALID_RESULT);
    virtual bool isEndProcessor() const;
    virtual bool isReady() const;



    /**
     * Returns the current color texture part of the rendered image. The
     * return value may be 0.
     *
     * @note If the returned texture is not 0, you probably need to call
     *      <code>downloadTexture()</code> on it, in order to access the pixels.
     *      Otherwise, no memory is allocated for the pixels and no rendered data
     *      are contained.
     */
    const tgt::Texture* getImageColorTexture() const;

    /// @overload
    tgt::Texture* getImageColorTexture();

    /**
     * Returns the current depth texture part of the rendered image. The
     * return value may be 0.
     *
     * @note If the returned texture is not 0, you probably need to call
     *      <code>downloadTexture()</code> on it, in order to access the pixels.
     *      Otherwise, no memory is allocated for the pixels and no rendered data
     *      are contained.
     */
    const tgt::Texture* getImageDepthTexture() const;

    /// @overload
    tgt::Texture* getImageDepthTexture();

   
    /**
     * Returns a description of the error that has occurred
     * during the last \c renderToImage() call.
     *
     * If the last render-to-image operation was successful, an empty string is returned.
     */
    std::string getRenderToImageError() const;
	 

    /**
     * Resizes the associated PropertyWidget (if available) and the inport to the
     * passed dimensions.
     */
    void resizeCanvas(tgt::ivec2 newsize);

    /**
     * To be called by VoreenPainter if the associated canvas has been resized,
     * but may also be called from the outside.
     */
    void canvasResized(tgt::ivec2 newsize);

	//RAMA
	virtual void SetWindowSize(tgt::ivec2  wsize); 

	//RAMA
    virtual void process();

	void SteTextureParameteres();

	virtual void initialize() throw (VoreenException);
	void SetInport(tgt::RenderTarget* val);
protected:
    virtual void deinitialize() throw (VoreenException);

     

    /// Stores thee current canvas size and may be used for adjusting it.
    IntVec2Property canvasSize_;

    BoolProperty showCursor_;

    /// Pointer to the associated OpenGL canvas
    tgt::GLCanvas* canvas_;

    /// Shader program used for rendering the input texture onto the canvas.
    tgt::Shader* shader_;

    /// Inport whose rendering is mapped to the frame buffer.
    tgt::RenderTarget* inport_;
	
	
    /// Texture that is shown when the inport_ is not ready.
    tgt::Texture* errorTex_;

    /// Flag to set when the input rendering should be to written to an image file.
    bool renderToImage_;

    /// Filename of the image file to write to.
    std::string renderToImageFilename_;

    /// Description of the error occurred during last renderToImage
    std::string renderToImageError_;

private:
	//RAMA 
	int *m_WindowSize;
	//RAMA

    /// Calls resizeCanvasWidget() with the value currently assigned to the size property.
    void sizePropChanged();

    void cursorVisibilityChanged();

    static const std::string loggerCat_; ///< category used in logging

	//RAMA
	//CameraProperty camera_;  ///< camera used for rendering the proxy geometry
	//RAMA

};

} // namespace voreen

#endif // VRN_CANVASRENDERER_H
