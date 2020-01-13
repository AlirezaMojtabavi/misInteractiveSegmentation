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

#ifndef VRN_IDRAYCASTER_H
#define VRN_IDRAYCASTER_H

#include "voreen/core/datastructures/transfunc/transfunc.h"
#include "voreen/core/processors/volumeraycaster.h"
#include "voreen/core/datastructures/transfunc/transfuncintensity.h"
#include "voreen/core/properties/cameraproperty.h"
#include "voreen/core/properties/floatproperty.h"

#include "voreen/core/ports/volumeport.h"

#include "tgt/shadermanager.h"

namespace voreen {

/**
 * Writes color coded regions of a segmented dataset to the alpha channel of
 * the rendering target. The three color channels are filled with the
 * first-hit-positions.
 */
class IDRaycaster : public VolumeRaycaster {
public:
    IDRaycaster();
    virtual Processor* create() const;

    virtual std::string getClassName() const  { return "IDRaycaster";     }
    virtual std::string getCategory() const   { return "Raycasting";      }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE; }
    virtual std::string getProcessorInfo() const;

protected:
    virtual void process();
    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    virtual void loadShader();
    virtual void compile();

    VolumePort volumePort_;
    RenderPort entryPort_;
    RenderPort exitPort_;
    RenderPort firstHitpointsPort_;
    RenderPort idMapPort_;

    tgt::Shader* raycastPrg_;          ///< The shader program used by this raycaster.

    /// The camera used for raycasting.
    CameraProperty camera_;

    /// Indicates how deep a ray penetrates the volume, if no segment is hit.
    FloatProperty penetrationDepth_;

    /// The id raycasting shader.
    //tgt::Shader* raycastPrg_; //shadowed the raycastPrg_ in VolumeRaycaster

    static const std::string firstHitPointsTexUnit_;
    static const std::string firstHitPointsDepthTexUnit_;
};

} // namespace voreen

#endif //__VRN_IDRAYCASTING_H__
