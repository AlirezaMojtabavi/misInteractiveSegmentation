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

#ifndef VRN_RENDERSTORE_H
#define VRN_RENDERSTORE_H

#include "voreen/core/processors/renderprocessor.h"

namespace voreen {

/**
 * \brief A RenderStore stores a copy of its input image and makes it available to other processors via a render outport.
 * It provides the rendering that had been assigned to its inport during the previous rendering pass. Its
 * outport may be connected to a predecessing processor, allowing it to access a previous rendering result.
 *
 * Furthermore, the input image is stored in a persistent render target and can therefore be accessed at any time,
 * not necessarily during a rendering pass.
 */
class RenderStore : public RenderProcessor {
public:
    RenderStore();
    virtual Processor* create() const;

    virtual std::string getClassName() const  { return "RenderStore";     }
    virtual std::string getCategory() const   { return "Utility";         }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE; }
    virtual bool isUtility() const            { return true; }
    virtual std::string getProcessorInfo() const;

    /**
     * By definition, the RenderStore is an EndProcessor, i.e. no processors
     * have to render after it. It is important to flag this, as the RenderStore has an outport
     * that may be connected to a predecessing processor.
     */
    virtual bool isEndProcessor() const       { return true; }

    /**
     * Returns true, if the inport is connected and the internal RenderTarget contains data.
     */
    virtual bool isReady() const;

    /**
     * Returns the content of the stored input image at the pixel position \param pos.
     */
    tgt::vec4 getStoredTargetPixel(const tgt::ivec2 &pos);

protected:
    virtual void process();
    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    virtual void portResized(RenderPort* p, tgt::ivec2 newsize);
    virtual void sizeOriginChanged(RenderPort* p);
    virtual bool testSizeOrigin(const RenderPort* p, void* so) const;

    RenderPort inport_;
    RenderPort privatePort_;
    RenderPort outport_;

    /// The shader program used by this \c RenderStore
    tgt::Shader* shaderPrg_;

    /// category used in logging
    static const std::string loggerCat_;
};

} // namespace voreen

#endif // VRN_RENDERSTORE_H
