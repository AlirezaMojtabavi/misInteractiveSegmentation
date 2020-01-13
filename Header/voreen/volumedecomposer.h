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

#ifndef VRN_VOLUMEDECOMPOSER_H
#define VRN_VOLUMEDECOMPOSER_H

#include "voreen/core/processors/renderprocessor.h"

#include "voreen/core/properties/intproperty.h"

#include "voreen/core/ports/volumeport.h"

namespace voreen {

class ImageSequence;

/**
 * Decomposes a volume into slices that are put out as image sequence.
 */
class VolumeDecomposer : public RenderProcessor {
public:
    VolumeDecomposer();
    ~VolumeDecomposer();
    virtual Processor* create() const;

    virtual std::string getClassName() const  { return "VolumeDecomposer";  }
    virtual std::string getCategory() const   { return "Volume Processing"; }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE;   }
    virtual std::string getProcessorInfo() const;

    virtual bool isReady() const;

protected:
    virtual void process();
    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    void decomposeVolume();
    void clearSliceSequence();
    void adjustToInputVolume();

    void startSliceChanged();
    void endSliceChanged();

    VolumePort inport_;
    ImageSequencePort outport_;

    IntProperty startSlice_;
    IntProperty endSlice_;

    ImageSequence* sliceSequence_;

    static const std::string loggerCat_; ///< category used in logging
};

}

#endif //VRN_VOLUMEDECOMPOSER_H
