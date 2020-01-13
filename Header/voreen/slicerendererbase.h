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

#ifndef VRN_SLICERENDERERBASE_H
#define VRN_SLICERENDERERBASE_H

#include <cstring>

#include "tgt/vector.h"
#include "tgt/matrix.h"
#include "tgt/shadermanager.h"

#include "voreen/core/processors/processor.h"
#include "voreen/core/processors/volumerenderer.h"
#include "voreen/core/datastructures/transfunc/transfunc.h"

#include "voreen/core/properties/transfuncproperty.h"
#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/optionproperty.h"

#include "voreen/core/ports/volumeport.h"

namespace tgt {
    class TextureUnit;
}

namespace voreen {

/**
 * Base class for all SliceRendering sub classes.
 * Provides basic functionality.
 */
class SliceRendererBase : public VolumeRenderer {
public:
    SliceRendererBase();

protected:
    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    /**
     * Returns <kbd>true</kbd> if all necessary data have been initialized so rendering can be started,
     * <kbd>false</kbd> otherwise.
     */
    bool ready() const;

    /**
     * Initializes the shader if applicable and sets all uniforms.
     */
    virtual bool setupShader(VolumeGL* volume = 0, tgt::TextureUnit* volUnit = 0, tgt::TextureUnit* transferUnit = 0,
        const tgt::Camera* camera = 0, const tgt::vec4& lightPosition = tgt::vec4(0.f));

    /**
     * Generates the header for the shader depending on the choice of
     * features to be used.
     */
    virtual std::string buildShaderHeader();

    /**
     * Recompiles the shader.
     */
    bool rebuildShader();

    /**
     * Deactivates the shader
     */
    void deactivateShader();

protected:
    TransFuncProperty transferFunc_;

    IntOptionProperty texFilterMode_;         ///< texture filtering mode to use for volume access
    GLEnumOptionProperty texClampMode_;       ///< texture clamp mode to use for the volume
    FloatProperty texBorderIntensity_;        ///< clamp border intensity

    tgt::Shader* sliceShader_;

    static const std::string transFuncTexUnit_;
    static const std::string volTexUnit_;

    RenderPort outport_;
    VolumePort inport_;

private:
    void adjustPropertyVisibilities();

};

// ----------------------------------------------------------------------------

} // namespace voreen

#endif // VRN_SLICERENDERERBASE_H
