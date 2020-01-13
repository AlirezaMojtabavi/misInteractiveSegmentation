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

#ifndef VRN_FLOWREENPROCESSOR_H
#define VRN_FLOWREENPROCESSOR_H

#include "voreen/core/ports/allports.h"
#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/cameraproperty.h"
#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/vectorproperty.h"
#include "voreen/core/datastructures/volume/volumehandle.h"
#include "tgt/camera.h"

#include "voreen/modules/flowreen/volumeflow3d.h"
#include <ostream>
#include <fstream>

namespace voreen {

class VolumeHandle;

class FlowreenProcessor {
public:
    FlowreenProcessor();
    virtual ~FlowreenProcessor() = 0;

protected:
    /**
     * Checks whether the passed VolumeHandle contains a Volume of the
     * type of the given template parameter. If so, the return value is non-NULL
     * otherwise NULL will be returned.
     * Besides, this method assigns the passed VolumeHandle* (usually obtained from
     * a LocalPortMapping structure within a processor's proces() method) as the
     * current one in the local attribute currentVolumeHandle_.
     * The passed bool indicates, whether the passed VolumeHandle differs from the
     * one being held previously by currentVolumeHandle_.
     */
    template<class FlowVolume>
    FlowVolume* checkVolumeHandleForFlowData(VolumeHandle* const candidate, bool& changed) {

        if (currentVolumeHandle_ != 0) {
            // If the given VolumeHandle* is not identical to the current one,
            // (that is especially if handle is 0!), set the given one as current.
            //
            if (currentVolumeHandle_ != candidate) {
                currentVolumeHandle_ = candidate;
                changed = true;
            } else {
                changed = false;
            }
        } else {
            currentVolumeHandle_ = candidate;
            changed = true;
        }

        // As the current handle might have changed above and it may be NULL, perform
        // the NULL-check a second time and return the result.
        //
        if (!currentVolumeHandle_)
            return 0;

        return dynamic_cast<FlowVolume*>(currentVolumeHandle_->getVolume());
    }

    std::vector<tgt::vec3> getTransformedCircle(const tgt::mat4& transformation) const;

    /**
     * Scales the given vertex so that its maximum extends fit into a
     * cube of [-1, -1, -1] - [1, 1, 1].
     * Usually the vertex is in range of [0, 0, 0] - flowDimensions.
     */
    tgt::vec3 mapToFlowBoundingBox(const tgt::vec3& vertex) const;

    /**
     * Renders an arrow consisting of a cylinder and a cone, centered
     * around (0, 0, 0) in coordinates of the flow volumes boundaries.
     * It is pointing along the positive z-axis, starting at -0.5 and
     * ending at 0.5. Its length is 1.0, the radius of the cone is 0.2.
     */
    void renderArrow(const tgt::mat4& transformation, const float length = 1.0f) const;

    void renderBoundingBox(const tgt::vec4& color) const;

    /**
     * Renders a coordinate system consisting of three perpendicular
     * lines ranking from min to max for the three main axis X, Y and Z.
     * The lines for are colored in red, green and blue.
     */
    void renderCoordinateAxis(const tgt::vec3& min = tgt::vec3(0.0f),
        const tgt::vec3& max = tgt::vec3(1.0f)) const;

    void init();

protected:
    enum { NUM_COLORS = 10, NUM_CIRCLE_VERTICES = 36 };   // enum hack
    static const tgt::vec4 fancyColors_[NUM_COLORS];
    static const tgt::vec3 planeCircleXY[NUM_CIRCLE_VERTICES];

    FloatProperty maxStreamlineLengthProp_;
    FloatVec2Property thresholdProp_;
    BoolProperty useBoundingBoxProp_;
    FloatVec4Property boundingBoxColorProp_;
    BoolProperty useCoordinateAxisProp_;

    VolumeHandle* currentVolumeHandle_;
    tgt::ivec3 flowDimensions_;

private:
    void onThresholdChange();

private:
    static bool initialized_;
};

}   // namespace

#endif
