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

#ifndef VRN_VOLUMEINFORMATION_H
#define VRN_VOLUMEINFORMATION_H

#include "voreen/core/processors/volumeprocessor.h"
#include "voreen/core/properties/buttonproperty.h"
#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/intproperty.h"
#include "voreen/core/properties/floatproperty.h"

namespace voreen {

/**
 * Computes some properties such as the min, max, average voxel intensity
 * of the input volume and displays them by read-only properties.
 */
class VolumeInformation : public VolumeProcessor {
public:
    VolumeInformation();
    Processor* create() const;

    std::string getClassName() const    { return "VolumeInformation"; }
    std::string getCategory() const     { return "Utility"; };
    CodeState getCodeState() const      { return CODE_STATE_STABLE; }
    bool isUtility() const              { return true; }
    std::string getProcessorInfo() const;

protected:
    virtual void process();

private:
    void computeInformation();

    VolumePort volume_;

    ButtonProperty computeButton_;
    BoolProperty computeContinuously_;
    IntProperty numVoxels_;
    IntProperty numSignificant_;
    FloatProperty minValue_;
    FloatProperty maxValue_;
    FloatProperty meanValue_;
    FloatProperty standardDeviation_;
    FloatProperty entropy_;
};

} // namespace

#endif // VRN_VOLUMEINFORMATION_H
